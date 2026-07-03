#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "Telezer_J";
const char* password = "Telezer12";

WebServer server(80);
Servo servo;

const int servoPin = 18;

String webpage()
{
    String html;

    html += "<!DOCTYPE html><html>";
    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>ESP32 Servo Control</title>";
    html += "<style>";
    html += "body{font-family:Arial;text-align:center;background:#f2f2f2;margin-top:40px;}";
    html += ".card{background:white;padding:20px;width:350px;margin:auto;border-radius:10px;box-shadow:0 0 10px gray;}";
    html += "input[type=range]{width:300px;}";
    html += "</style>";
    html += "</head>";

    html += "<body>";
    html += "<div class='card'>";
    html += "<h2>ESP32 Servo Control</h2>";

    html += "<input type='range' min='0' max='180' value='90' id='servoSlider' ";
    html += "oninput='updateServo(this.value)'>";

    html += "<h3>Angle: <span id='angle'>90</span>°</h3>";

    html += "</div>";

    html += "<script>";
    html += "function updateServo(value){";
    html += "document.getElementById('angle').innerHTML=value;";
    html += "fetch('/servo?angle='+value);";
    html += "}";
    html += "</script>";

    html += "</body></html>";

    return html;
}

void handleRoot()
{
    server.send(200, "text/html", webpage());
}

void handleServo()
{
    if(server.hasArg("angle"))
    {
        int angle = server.arg("angle").toInt();

        angle = constrain(angle, 0, 180);

        servo.write(angle);

        Serial.print("Servo Angle: ");
        Serial.println(angle);
    }

    server.send(200, "text/plain", "OK");
}

void setup()
{
    Serial.begin(115200);

    servo.attach(servoPin);
    servo.write(90);

    WiFi.begin(ssid, password);

    Serial.print("Connecting");

    while(WiFi.status()!=WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/servo", handleServo);

    server.begin();

    Serial.println("Web Server Started");
}

void loop()
{
    server.handleClient();
}