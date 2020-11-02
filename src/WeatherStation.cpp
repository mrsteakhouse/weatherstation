#include <ESP8266WiFi.h>

#include <Thing.h>
#include <WebThingAdapter.h>

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

#include <SetWifiCredentials.h>
#include <PubSubClient.h>
#include <sstream>

Adafruit_BME280 bme;
Adafruit_BMP280 bmp;

WiFiClient espClient;
PubSubClient client(espClient);

const IPAddress mqttServer = IPAddress(192, 168, 0, 59);

static const char *const TEMPARTURE_NODE = "temperature";
static const char *const TEMP_PROPERTY = "temp";
static const char *const HUMIDITY_PROPERTY = "hum";
static const char *const PRESSURE_PROPERTY = "p";
static const char *const ALARM_PROPERTY = "alarm";
static const char *const PUMP_NODE = "pump";
uint64_t sleepTime = 3600e6L;

void setupNetwork();

void setupSensors();

void setupAdapter(const IPAddress &ip);

void connectMqtt();

void updateValues();

void sendValue(const char* node, const char* property, const char* value);

void setupSleep();

std::string doubleToString(double number);

void setup(void)
{
    Serial.begin(115200);
    setupNetwork();
    IPAddress ip = WiFi.localIP();
    Serial.print(FPSTR("IP="));
    Serial.println(ip);

    setupSensors();
    connectMqtt();
}

void setupNetwork()
{
    setWifiCredentials();
    delay(20);

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(false);
    WiFi.disconnect();
    IPAddress ip(192, 168, 0, 227);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, gateway, subnet);

    WiFi.begin(Ssid, Password);

    int retryCounter = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        if (retryCounter >= 20)
        {
            ESP.restart();
        }

        retryCounter++;
    }

    Serial.println("");
    Serial.println(FPSTR("WiFi connected"));
}

void setupSensors()
{
    Wire.begin(0, 2);

    delay(1000);

    if (!bmp.begin(0x77))
    {
        Serial.println(FPSTR("Could not find a valid BMP280 sensor"));
        ESP.restart();
    }
    if (!bme.begin(0x76))
    {
        Serial.println(FPSTR("Could not find a valid BME280 sensor"));
        ESP.restart();
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_NONE,
                    Adafruit_BMP280::SAMPLING_X1,
                    Adafruit_BMP280::FILTER_OFF,
                    Adafruit_BMP280::STANDBY_MS_1);
    delay(20);
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X16,
                    Adafruit_BME280::SAMPLING_X1,
                    Adafruit_BME280::SAMPLING_X8,
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_10);
    delay(20);
}

void connectMqtt()
{
    client.setServer(mqttServer, 1883);
    int retryCounter = 0;
    String clientId = "living-room-weatherstation";
    Serial.println(FPSTR("Connect to MQTT Broker"));
    while(!client.connected() && retryCounter < 5)
    {
        if (client.connect(clientId.c_str()))
        {
            Serial.println(FPSTR("connection established"));
            return;
        }

        Serial.println(FPSTR("Connection failed, retry in 1s"));
        retryCounter++;
        delay(1000);
    }

    Serial.println(FPSTR("No connection to MQTT Broker"));
}

void loop(void)
{
    updateValues();

//    Serial.print(FPSTR("Sleeping for "));
//    Serial.println(sleepTime);
    setupSleep();
}

void updateValues()
{
    bme.takeForcedMeasurement();
    double temp = bme.readTemperature() - 2;
    double hum = bme.readHumidity();
    double pr = bme.readPressure() / 100.0F;
    double pp = bmp.readPressure() / 100.0F;

    bool isAlarm = pp - pr > 5;

    sendValue(TEMPARTURE_NODE, TEMP_PROPERTY, doubleToString(temp).c_str());
    delay(20);
    sendValue(TEMPARTURE_NODE, HUMIDITY_PROPERTY, doubleToString(hum).c_str());
    delay(20);
    sendValue(TEMPARTURE_NODE, PRESSURE_PROPERTY, doubleToString(pr).c_str());
    delay(20);
    sendValue(PUMP_NODE, ALARM_PROPERTY, isAlarm ? "true" : "");
    delay(20);
    

#ifdef DEBUG
    Serial.print(FPSTR("Temperature = "));
    Serial.print(temp);
    Serial.println(" *C");

    Serial.print(FPSTR("Pressure = "));
    Serial.print(pr);
    Serial.println(FPSTR(" hPa"));

    Serial.print(FPSTR("Humidity = "));
    Serial.print(hum);
    Serial.println(FPSTR(" %"));

    Serial.print(FPSTR("Pump Pressure = "));
    Serial.print(pp);
    Serial.println(FPSTR(" hPa"));
#endif
}

void sendValue(const char* node, const char* property, const char* value)
{
    char topicBuffer[128];
    sprintf(topicBuffer, "homie/living-room-temp/%s/%s", node, property);
#ifdef DEBUG
    Serial.print(FPSTR("Publishing to: "));
    Serial.println(topicBuffer);
#endif
    client.publish(topicBuffer, value, true);
}

void setupSleep()
{
    bmp.setSampling(Adafruit_BMP280::MODE_SLEEP);
    bme.setSampling(Adafruit_BME280::MODE_SLEEP);
    Wire.flush();

    Serial.println(FPSTR("Sleeping now"));
    ESP.deepSleep(sleepTime, RFMode::RF_NO_CAL);
    delay(100);
}

std::string doubleToString(double number)
{
    std::ostringstream stream;
    stream << number;
    return stream.str();
}

