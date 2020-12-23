//
// Copyright (c) 2020, Fabian Frey
// All rights reserved.
//

#ifndef WEATHERSTATION_WIFICONNECTIONSERVICE_H
#define WEATHERSTATION_WIFICONNECTIONSERVICE_H


#include <IPAddress.h>
#include "LittleFS.h"
#include <ESP8266WiFi.h>

class WiFiConnectionService
{
private:
    const char* wifiConfiguredFilePath = "/wificonfigured";
    IPAddress ip;
    IPAddress gateway;
    IPAddress dns;
    IPAddress subnet;
    String ssid;
    String password;

    void configureWifi();

    bool needsConfiguration();
    void writeFile();

public:
    WiFiConnectionService(const IPAddress& ip, const IPAddress& gateway, const IPAddress& dns, const IPAddress& subnet, String ssid, String password);

    bool connect();

};

#endif //WEATHERSTATION_WIFICONNECTIONSERVICE_H
