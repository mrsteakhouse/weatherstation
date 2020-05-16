/**
   Simple server compliant with Mozilla's proposed WoT API
   Based on the RGBLamp example
   Tested on Arduino Mega with Ethernet Shield
   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <ESP8266WiFi.h>

#include <Thing.h>
#include <WebThingAdapter.h>

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

#include <SetWifiCredentials.h>

#define uS_TO_S_FACTOR 1000000

Adafruit_BME280 bme;
Adafruit_BMP280 bmp;

const char *temperature[] = {"TemperatureSensor", "MultiLevelSensor", "Sensor", nullptr};
const char *pressure[] = {"Alarm", "MultiLevelSensor", "Sensor", nullptr};
ThingDevice weatherStation("WeatherStation", "Weather station", temperature);
ThingDevice pumpPressure("PumpPressure", "Pressure from Airpump", pressure);
ThingProperty temperatureProp("temperature", "Temperature", NUMBER, "TemperatureProperty");
ThingProperty humidityProp("humidity", "Humidity", NUMBER, "LevelProperty");
ThingProperty pressureProp("pressure", "Air Pressure", NUMBER, "LevelProperty");
ThingProperty pumpPressureProp("pressure", "Air Pressure", NUMBER, "LevelProperty");
ThingProperty alarmProperty("alarm", "Danger", BOOLEAN, "AlarmPropery");
WebThingAdapter *adapter = nullptr;

long sleepTime = 18e5;

void setupNetwork();

void setupSensors();

void setupAdapter(const IPAddress &ip);

void updateValues();

void setupSleep();


void setup(void)
{
    Serial.begin(115200);
    setupNetwork();
    IPAddress ip = WiFi.localIP();
    Serial.print(FPSTR("log: IP="));
    Serial.println(ip);
    delay(3000);
    Serial.println(FPSTR("Starting HTTP server"));

    setupSensors();
    setupAdapter(ip);
    Serial.print(FPSTR("http://"));
    Serial.print(ip);
    Serial.print(FPSTR("/things/"));
    Serial.println(weatherStation.id);
    Serial.println(pumpPressure.id);
}

void setupNetwork()
{
    setWifiCredentials();

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
    Wire.setClock(100000L);
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
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X4,
                    Adafruit_BMP280::STANDBY_MS_250);
    bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X2,
                    Adafruit_BME280::SAMPLING_X16,
                    Adafruit_BME280::SAMPLING_X2,
                    Adafruit_BME280::FILTER_X4,
                    Adafruit_BME280::STANDBY_MS_250);
}

void setupAdapter(const IPAddress &ip)
{
    adapter = new WebThingAdapter(FPSTR("weatherstation"), ip);

    weatherStation.addProperty(&humidityProp);
    weatherStation.addProperty(&pressureProp);
    weatherStation.addProperty(&temperatureProp);

    pumpPressure.addProperty(&alarmProperty);
    pumpPressure.addProperty(&pumpPressureProp);

    adapter->addDevice(&weatherStation);
    adapter->addDevice(&pumpPressure);

    adapter->begin();
    delay(10000);
}

void loop(void)
{
    updateValues();
    Serial.print(FPSTR("Sleeping for "));
    Serial.println(sleepTime);
    setupSleep();
}

void updateValues()
{
    ThingPropertyValue tempPropValue;
    ThingPropertyValue humdityPropValue;
    ThingPropertyValue pressurePropValue;
    ThingPropertyValue pumpPressurePropValue;
    ThingPropertyValue alarmPropertyValue;

    double temp = bme.readTemperature() - 2;
    double hum = bme.readHumidity();
    double pr = bme.readPressure() / 100.0F;
    double pp = bmp.readPressure() / 100.0F;
    tempPropValue.number = temp;
    humdityPropValue.number = hum;
    pressurePropValue.number = pr;
    pumpPressurePropValue.number = pp;

    alarmPropertyValue.boolean = pp - pr <= 5;

    humidityProp.setValue(humdityPropValue);
    adapter->update();
    pressureProp.setValue(pressurePropValue);
    adapter->update();
    temperatureProp.setValue(tempPropValue);
    adapter->update();
    pumpPressureProp.setValue(pumpPressurePropValue);
    adapter->update();
    alarmProperty.setValue(alarmPropertyValue);
    adapter->update();

    Serial.print(FPSTR("Temperature = "));
    Serial.print(temp);
    Serial.println(" *C");

    Serial.print(FPSTR("Pressure = "));
    Serial.print(pr);
    Serial.println(FPSTR(" hPa"));

    Serial.print("Humidity = ");
    Serial.print(hum);
    Serial.println(FPSTR(" %"));

    Serial.print(FPSTR("Pump Pressure = "));
    Serial.print(pp);
    Serial.println(FPSTR(" hPa"));
}

void setupSleep()
{
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED);
    bme.setSampling(Adafruit_BME280::MODE_FORCED);
    Wire.flush();

    delay(3000);
    WiFi.disconnect();

    Serial.println(FPSTR("Sleeping now"));
    ESP.deepSleep(sleepTime * uS_TO_S_FACTOR, RFMode::RF_DISABLED);

}

