#include <Arduino.h>

// Use uppercase for constants to follow standard practices
#define LED_PIN 13 

void setup() {
  // CORRECTED: Changed INPUT to OUTPUT so the ESP32 can power the LED
  pinMode(LED_PIN, OUTPUT);
   Serial.begin(115200); 
}

void loop() {
  // Using HIGH and LOW instead of 1 and 0 makes it easier to read
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
}
