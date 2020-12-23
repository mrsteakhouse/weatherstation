//
// Copyright (c) 2020, Fabian Frey
// All rights reserved.
//

#ifndef WEATHERSTATION_MQTTSERVICE_H
#define WEATHERSTATION_MQTTSERVICE_H

#include <WString.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

class MqttService
{
private:
    PubSubClient client;
    String clientId;
    IPAddress serverAddress;
    int port;

public:
    MqttService(String clientId, const IPAddress& serverAddress, int port);

    bool connect();

    void publish(const char* topic, const char* payload, bool retain);
};


#endif //WEATHERSTATION_MQTTSERVICE_H
