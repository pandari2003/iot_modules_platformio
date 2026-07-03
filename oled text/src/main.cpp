#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define your ESP32-S3 I2C Pins (Change these numbers if your board uses different pins)
#define I2C_SDA 8
#define I2C_SCL 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // 1. Initialize I2C with ESP32-S3 specific pins
  Wire.begin(I2C_SDA, I2C_SCL);

  // 2. Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // If initialization fails, stop execution
    while(true); 
  }
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE); // Updated to standard library macro
}

void loop() {
  // 3. Moved the infinite animation loop into the loop() function where it belongs
  for(int i = 64; i >= -50; i--) { 
    display.clearDisplay();
    
    // Set the cursor BEFORE printing text
    display.setCursor(10, i); 
    
    display.println("WELCOME");
    display.println(" PANDARI");
    display.println("JAI BHEEM");
    
    display.display();
    delay(30); // Faster delay for a smoother scrolling effect
  }
  
  display.clearDisplay();
  display.display();
  delay(1000); // Pause before restarting the scroll
}
