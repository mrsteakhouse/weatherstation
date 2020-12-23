#include <ESP8266WiFi.h>

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

#include <WifiCredentials.h>
#include <PubSubClient.h>
#include <sstream>
#include <MCP342X.h>

#define LSB 0.0000625

Adafruit_BME280 bme;

WiFiClient espClient;
PubSubClient client(espClient);

const IPAddress mqttServer = IPAddress(192, 168, 0, 59);

static const char *const DEVICE = "wintergarten";
static const char *const TEMPERATURE_NODE = "temperature";
static const char *const TEMP_PROPERTY = "temp";
static const char *const HUMIDITY_PROPERTY = "hum";
static const char *const PRESSURE_PROPERTY = "p";
static const char *const BATTERY_PROPERTY = "bat";

uint64_t sleepTime = 3600e6L;

MCP342X adc;

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
    delay(20);

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(false);
    WiFi.disconnect();
    IPAddress ip(192, 168, 0, 228);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, gateway, subnet);

    WifiCredentials credentials;
    WiFi.begin(credentials.getSsid(), credentials.getPassword());

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

    if (!bme.begin(0x76))
    {
        Serial.println(FPSTR("Could not find a valid BME280 sensor"));
        ESP.restart();
    }

    delay(20);
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X16,
                    Adafruit_BME280::SAMPLING_X1,
                    Adafruit_BME280::SAMPLING_X8,
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_125);
    delay(20);

    adc.configure( MCP342X_MODE_ONESHOT |
                     MCP342X_CHANNEL_1 |
                     MCP342X_SIZE_16BIT |
                     MCP342X_GAIN_1X);
}

void connectMqtt()
{
    client.setServer(mqttServer, 1883);
    int retryCounter = 0;
    String clientId = "wintergarten-weatherstation";
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

    setupSleep();
//    delay(2000);
}

void updateValues()
{
    bme.takeForcedMeasurement();
    double temp = bme.readTemperature();
    double hum = bme.readHumidity();
    double pr = bme.readPressure() / 100.0F;

    static int16_t  result;
    adc.startConversion();
    adc.getResult(&result);
    double factor = (470000.0 + 120000.0) / 120000.0;
    double bat = factor * result * (double) (LSB / 1.0);

    sendValue(TEMPERATURE_NODE, TEMP_PROPERTY, doubleToString(temp).c_str());
    delay(20);
    sendValue(TEMPERATURE_NODE, HUMIDITY_PROPERTY, doubleToString(hum).c_str());
    delay(20);
    sendValue(TEMPERATURE_NODE, PRESSURE_PROPERTY, doubleToString(pr).c_str());
    delay(20);
    sendValue(TEMPERATURE_NODE, BATTERY_PROPERTY, doubleToString(bat).c_str());
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
    sprintf(topicBuffer, "homie/%s/%s/%s", DEVICE, node, property);
#ifdef DEBUG
    Serial.print(FPSTR("Publishing to: "));
    Serial.println(topicBuffer);
#endif
    client.publish(topicBuffer, value, true);
}

void setupSleep()
{
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

