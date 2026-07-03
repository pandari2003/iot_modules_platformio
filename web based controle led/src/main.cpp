#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "wifiManager.h"
#include "htmlpage.h"
#include "deviceManager.h"

AsyncWebServer server(80);

void setup()
{
    Serial.begin(115200);

    connectWiFi();

    initDevice();

    // Home Page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send_P(200, "text/html", index_html);
    });

    // Register LED control APIs
    setupDeviceRoutes(server);

    server.begin();

    Serial.println("Server Started");
}

void loop()
{
}