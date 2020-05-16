#ifndef __SET_WIFI_CREDENTIALS_
#define __SET_WIFI_CREDENTIALS_

#include "FS.h"
#include "LittleFS.h"

String Ssid;
String Password;

String readFile(const String& path)
{
    File f = LittleFS.open(path, "r");
    if (!f)
    {
        Serial.print(FPSTR("Error opening file "));
        Serial.println(path);
        return "";
    }

    String value = f.readString();
    f.close();
    return value;
}

bool setWifiCredentials()
{
    if (!LittleFS.begin())
    {
        Serial.println(FPSTR("Error mounting file system"));
        return false;
    }

    Ssid = readFile("/ssid.txt");
    Password = readFile("/pw.txt");

    LittleFS.end();
    return true;
}

#endif
