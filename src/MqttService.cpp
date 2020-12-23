//
// Copyright (c) 2020, Fabian Frey
// All rights reserved.
//

#include "MqttService.h"

#include <utility>

MqttService::MqttService(String clientId, const IPAddress& serverAddress, int port)
    : clientId(std::move(clientId)), serverAddress(serverAddress), port(port)
{
    WiFiClient espClient;
    client = PubSubClient(espClient);
    client.setServer(serverAddress, port);
}

bool MqttService::connect()
{
    int retryCounter = 0;
    while(!client.connected() && retryCounter < 5)
    {
        if (client.connect(clientId.c_str()))
        {
            return true;
        }

        retryCounter++;
        delay(1000);
    }

    return false;
}

void MqttService::publish(const char* topic, const char* payload, bool retain)
{
    client.publish(topic, payload, true);
}
