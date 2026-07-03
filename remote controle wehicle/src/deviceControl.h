#ifndef DEVICE_CONTROL_H
#define DEVICE_CONTROL_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "webpage.h"

#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12

void stopCar()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}

void forward()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);

    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}

void backward()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);

    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
}

void left()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);

    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}

void right()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);

    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
}

void initDevice()
{
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);

    stopCar();
}

void setupRoutes(AsyncWebServer &server)
{
    server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){

        request->send_P(200,"text/html",index_html);

    });

    server.on("/forward",HTTP_GET,[](AsyncWebServerRequest *request){

        forward();

        request->send(200,"text/plain","OK");

    });

    server.on("/backward",HTTP_GET,[](AsyncWebServerRequest *request){

        backward();

        request->send(200,"text/plain","OK");

    });

    server.on("/left",HTTP_GET,[](AsyncWebServerRequest *request){

        left();

        request->send(200,"text/plain","OK");

    });

    server.on("/right",HTTP_GET,[](AsyncWebServerRequest *request){

        right();

        request->send(200,"text/plain","OK");

    });

    server.on("/stop",HTTP_GET,[](AsyncWebServerRequest *request){

        stopCar();

        request->send(200,"text/plain","OK");

    });

}

#endif