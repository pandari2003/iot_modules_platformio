#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

const int ledPin = 2;

// Initialize device
void initDevice()
{
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

// Register all device control APIs
void setupDeviceRoutes(AsyncWebServer &server)
{
    // LED ON
    server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        digitalWrite(ledPin, HIGH);
        request->send(200, "text/plain", "LED ON");
    });

    // LED OFF
    server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        digitalWrite(ledPin, LOW);
        request->send(200, "text/plain", "LED OFF");
    });
}

#endif