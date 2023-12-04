#include "LedControl.h" // Include LedControl library for controlling the LED matrix
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
const int JoyPin = 2;
const int xPin = A0;
const int yPin = A1;
// Create an LedControl object to manage the LED matrix
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER
// Variable to set the brightness level of the matrix
byte matrixBrightness = 2;
// Variables to track the current and previous positions of the joystick-controlled LED
byte xPos = 0;
byte yPos = 0;
byte xLastPos = 0;
byte yLastPos = 0;
// Thresholds for detecting joystick movement
const int minThreshold = 200;
const int maxThreshold = 600;

const byte moveInterval = 100; // Timing variable to control the speed of LED movement
unsigned long long lastMoved = 0; // Tracks the last time the LED moved

const byte matrixSize = 8 ;// Size of the LED matrix
bool matrixChanged = true; // Flag to track if the matrix display needs updating
// 2D array representing the state of each LED (on/off) in the matrix
byte matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}  
};

const float wallDensity = 0.4; 
const int wallThreshold = wallDensity * matrixSize * matrixSize; 

const int playerBlinkInterval = 500; 
unsigned long long lastPlayerBlink = 0; 
bool playerVisible = true; 
const int bombInterval = 3000; 
const int bombBlinkInterval = 200; 
unsigned long long bombPlacedTime = 0; 
unsigned long long lastBombBlink = 0; 
bool isBombPlaced = false; 
byte bombXPos; 
byte bombYPos; 



void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false); 
  lc.setIntensity(0, matrixBrightness); 
  lc.clearDisplay(0); 
  matrix[xPos][yPos] = 1; 
generateWalls();
generatePlayerPosition();

}


void loop() {
  if (millis() - lastMoved > moveInterval) {
    updatePositions();
    lastMoved = millis();
  }

  
  if (millis() - lastPlayerBlink > playerBlinkInterval) {
    playerVisible = !playerVisible; 
    matrix[xPos][yPos] = playerVisible ? 1 : 0; 

    updateMatrix();

    lastPlayerBlink = millis();
  }
}


void generateWalls() {
  int wallCount = 0;

  
  while (wallCount < wallThreshold) {
    
    int x = random(0, matrixSize);
    int y = random(0, matrixSize);

   
    if (matrix[x][y] != 1) {
      
      if (!(x == xPos && y == yPos)) {
        matrix[x][y] = 1; 
        wallCount++;
      }
    }
  }
}

void generatePlayerPosition() {
  while (true) {
    int x = random(0, matrixSize);
    int y = random(0, matrixSize);

    if (matrix[x][y] != 1) {
      xPos = x;
      yPos = y;
      matrix[xPos][yPos] = 1; 
      break;
    }
  }
}


void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, matrix[row][col]);  
    }
  }
}

void placeBomb() {
  
  if (bombPlacedTime == 0 || millis() - bombPlacedTime > bombInterval) {
    
    matrix[xPos][yPos] = 2; // val pt bomba

   
    bombPlacedTime = millis();
    lastBombBlink = 0;

    matrixChanged = true; 
  }
}

void updateBomb() {
  
  if (isBombPlaced && digitalRead(JoyPin) == HIGH) {
    destroyWallsAroundBomb();
    isBombPlaced = false; 
  } else if (!isBombPlaced && digitalRead(JoyPin) == HIGH) {
    placeBomb(); 
  }
}
void destroyWallsAroundBomb() {
 
  if (yPos > 0 && matrix[xPos][yPos - 1] == 1) {
    matrix[xPos][yPos - 1] = 0;
  }
  
  if (yPos < matrixSize - 1 && matrix[xPos][yPos + 1] == 1) {
    matrix[xPos][yPos + 1] = 0;
  }
  
  if (xPos > 0 && matrix[xPos - 1][yPos] == 1) {
    matrix[xPos - 1][yPos] = 0;
  }

  if (xPos < matrixSize - 1 && matrix[xPos + 1][yPos] == 1) {
    matrix[xPos + 1][yPos] = 0;
  }
}


void updatePositions() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  // Store the last positions of the LED
  xLastPos = xPos;
  yLastPos = yPos;
  
  
  int nextXPos = xPos;
  if (xValue < minThreshold) {
    nextXPos = (xPos < matrixSize - 1) ? xPos + 1 : 0;
  } else if (xValue > maxThreshold) {
    nextXPos = (xPos > 0) ? xPos - 1 : matrixSize - 1;
  }
  
  
  int nextYPos = yPos;
  if (yValue > maxThreshold) {
    nextYPos = (yPos < matrixSize - 1) ? yPos + 1 : 0;
  } else if (yValue < minThreshold) {
    nextYPos = (yPos > 0) ? yPos - 1 : matrixSize - 1;
  }
  
  
  if (matrix[nextXPos][nextYPos] != 1) {
    xPos = nextXPos;
    yPos = nextYPos;
    
    if (xPos != xLastPos || yPos != yLastPos) {
      matrixChanged = true;
      matrix[xLastPos][yLastPos] = 0;
      matrix[xPos][yPos] = 1;
    }
  }
  
  
  if (digitalRead(JoyPin) == HIGH) {
    placeBomb(); 
  }

  updateBomb(); 
}

