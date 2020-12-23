//
// Copyright (c) 2020, Fabian Frey
// All rights reserved.
//

#include "WiFiConnectionService.h"

WiFiConnectionService::WiFiConnectionService(const IPAddress& ip, const IPAddress& gateway, const IPAddress& dns, const IPAddress& subnet, String ssid, String password)
    : ip(ip), gateway(gateway), dns(dns), subnet(subnet), ssid(std::move(ssid)), password(std::move(password))
{
    LittleFS.begin();
}

void WiFiConnectionService::configureWifi()
{
    WiFi.persistent(true);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.config(ip, gateway, subnet, gateway);
}

bool WiFiConnectionService::needsConfiguration()
{
    return LittleFS.exists(wifiConfiguredFilePath);
}

void WiFiConnectionService::writeFile()
{
    File handle = LittleFS.open(wifiConfiguredFilePath, "w");
    handle.close();
}

bool WiFiConnectionService::connect()
{
    if (needsConfiguration())
    {
        configureWifi();
        writeFile();
        WiFi.begin(ssid, password);
    }

    // TODO: check if this works without WiFi.begin();

    int retryCounter = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        if (retryCounter >= 20)
        {
            return false;
        }

        retryCounter++;
    }

    return true;
}
