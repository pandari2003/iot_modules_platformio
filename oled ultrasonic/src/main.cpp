#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display TWI/I2C configuration
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 // Reset pin shared with Arduino reset pin
#define SCREEN_ADDRESS 0x3C /// Find your OLED I2C address (usually 0x3C or 0x3D)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Ultrasonic Sensor Pins
const int trigPin = 9;
const int echoPin = 10;

// Variables for calculation
long duration;
int distance;

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);

  // Define pin modes for the sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Clear the buffer and present startup text
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 20);
  display.println("Initializing...");
  display.display();
  delay(2000);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigger pin HIGH for 10 microseconds to send pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin bounce duration in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  // Speed of sound wave divided by 2 (go and back)
  distance = duration * 0.034 / 2;

  // Print results to Serial Monitor for verification
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Refresh and update the OLED Display
  display.clearDisplay();
  
  // Draw header block
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("--- DISTANCE METER ---");
  
  // Display the actual numeric reading
  display.setTextSize(2); // Larger font size for reading
  display.setCursor(10, 30);
  display.print(distance);
  display.print(" cm");
  
  // Push the data to the physical screen
  display.display();
  
  // Wait 300 milliseconds before taking the next reading
  delay(300);
}
