#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int JOY_X_PIN = A0; 

int playerX = 60;              
const int playerY = 50;        
const int carWidth = 10;
const int carHeight = 12;

int obstacleX = 0;             
int obstacleY = 0;             
const int obsWidth = 12;
const int obsHeight = 8;
int gameSpeed = 2;             

int score = 0;
bool gameOver = false;

// 1. Custom Functions (Placed first so setup/loop can see them)
void generateObstacle() {
  obstacleY = -obsHeight;
  obstacleX = random(12, SCREEN_WIDTH - 12 - obsWidth);
}

void readJoystick() {
  int xVal = analogRead(JOY_X_PIN);
  if (xVal < 400) {
    playerX -= 3; 
  } else if (xVal > 600) {
    playerX += 3; 
  }
  playerX = constrain(playerX, 12, SCREEN_WIDTH - 12 - carWidth);
}

void moveObstacle() {
  obstacleY += gameSpeed;
  if (obstacleY > SCREEN_HEIGHT) {
    score++;
    generateObstacle();
    if (score % 5 == 0 && gameSpeed < 7) {
      gameSpeed++;
    }
  }
}

void checkCollision() {
  if (playerX < obstacleX + obsWidth &&
      playerX + carWidth > obstacleX &&
      playerY < obstacleY + obsHeight &&
      playerY + carHeight > obstacleY) {
    gameOver = true;
  }
}

void drawGame() {
  display.clearDisplay();
  display.drawLine(10, 0, 10, SCREEN_HEIGHT - 1, SSD1306_WHITE);
  display.drawLine(SCREEN_WIDTH - 10, 0, SCREEN_WIDTH - 10, SCREEN_HEIGHT - 1, SSD1306_WHITE);
  
  display.fillRect(playerX, playerY, carWidth, carHeight, SSD1306_WHITE);
  display.fillRect(playerX - 2, playerY + 2, 2, 3, SSD1306_WHITE);  
  display.fillRect(playerX + carWidth, playerY + 2, 2, 3, SSD1306_WHITE); 
  display.fillRect(playerX - 2, playerY + 8, 2, 3, SSD1306_WHITE);  
  display.fillRect(playerX + carWidth, playerY + 8, 2, 3, SSD1306_WHITE); 
  
  display.fillRect(obstacleX, obstacleY, obsWidth, obsHeight, SSD1306_WHITE);
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(score);
  display.display();
}

void drawGameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.print("GAME OVER");
  
  display.setTextSize(1);
  display.setCursor(15, 35);
  display.print("Final Score: ");
  display.print(score);
  display.setCursor(10, 50);
  display.print("Hold Joystick to Restart");
  display.display();
}

void readReset() {
  int xVal = analogRead(JOY_X_PIN);
  if (xVal < 100 || xVal > 900) {
    playerX = 60;
    score = 0;
    gameSpeed = 2;
    gameOver = false;
    generateObstacle();
    delay(500); 
  }
}

// 2. Main Entry Points (Placed last)
void setup() {
  pinMode(JOY_X_PIN, INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }
  display.clearDisplay();
  randomSeed(analogRead(A1)); 
  generateObstacle();
}

void loop() {
  if (!gameOver) {
    readJoystick();
    moveObstacle();
    checkCollision();
    drawGame();
  } else {
    drawGameOver();
    readReset();
  }
  delay(30); 
}
