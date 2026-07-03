#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "wifimanager.h"
#include "deviceControl.h"

AsyncWebServer server(80);

void setup()
{
    Serial.begin(115200);

    connectWiFi();

    initDevice();

    setupRoutes(server);

    server.begin();

    Serial.println("Server Started");
}

void loop()
{

}