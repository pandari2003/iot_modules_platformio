#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "Telezer_J";
const char* password = "Telezer12";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot()
{
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    String html = "<!DOCTYPE html><html>";
    html += "<head>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>ESP32 DHT Sensor</title>";
    html += "</head><body>";

    html += "<h1>ESP32 Sensor Data</h1>";

    if (isnan(t) || isnan(h))
    {
        html += "<p>Sensor Error!</p>";
    }
    else
    {
        html += "<h2>Temperature : ";
        html += String(t);
        html += " &deg;C</h2>";

        html += "<h2>Humidity : ";
        html += String(h);
        html += " %</h2>";
    }

    html += "</body></html>";

    server.send(200, "text/html", html);
}

void setup()
{
    Serial.begin(115200);

    dht.begin();

    WiFi.begin(ssid, password);

    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);

    server.begin();
}

void loop()
{
    server.handleClient();
}