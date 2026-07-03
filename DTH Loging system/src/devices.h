#ifndef DEVICES_H
#define DEVICES_H

#include <Arduino.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define LED 2

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot()
{
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    String html;

    html += "<!DOCTYPE html><html>";
    html += "<head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>ESP32 DHT11</title>";
    html += "<style>";
    html += "body{font-family:Arial;text-align:center;background:#f2f2f2;padding:40px;}";
    html += ".card{background:white;padding:20px;border-radius:10px;"
            "box-shadow:0 0 10px rgba(0,0,0,.2);display:inline-block;}";
    html += "h1{color:#0066cc;}";
    html += "h2{color:#333;}";
    html += "</style>";
    html += "</head><body>";

    html += "<div class='card'>";
    html += "<h1>ESP32 DHT11 Sensor</h1>";

    if (isnan(t) || isnan(h))
    {
        html += "<h2>Sensor Error!</h2>";
    }
    else
    {
        html += "<h2>Temperature : ";
        html += String(t, 1);
        html += " &deg;C</h2>";

        html += "<h2>Humidity : ";
        html += String(h, 1);
        html += " %</h2>";
    }

    html += "</div>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void deviceInit()
{
    pinMode(LED, OUTPUT);

    dht.begin();

    server.on("/", handleRoot);

    server.begin();

    Serial.println("Web Server Started");
}

#endif