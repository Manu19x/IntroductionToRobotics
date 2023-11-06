// Declare all the joystick pins
const int pinSW = 2; // Digital pin for joystick
const int pinX = A0; // Analog pin connected to X output
const int pinY = A1; // Analog pin connected to Y output

// Declare all the segments pins
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;

byte state = HIGH;
byte swState = HIGH;
byte lastSwState = HIGH;

int xAxisValue = 0; 
int yAxisValue = 0; 

bool joyMoved = false;
int minThreshold = 400;
int maxThreshold = 600;
const int directions = 4;
int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
int currentSegment = 7;
unsigned long restartTimer = 1000;
unsigned long lastBlinkTime = 0;
const int blinkInterval = 250;
const int restartInterval = 1000;

bool segmentStates[segSize] = {false, false, false, false, false, false, false, false};

int neighborSegments[segSize][directions] = {
  // Up Down Left Right
  {-1, 6, 5, 1 }, // a - 0
  {0, 6, 5, -1 }, // b - 1
  {6, 3, 4, -1 }, // c - 2
  {6, -1, 4, 2 }, // d - 3
  {6, 3, -1, 2 }, // e - 4
  {0, 6, -1, 1 }, // f - 5
  {0, 3, -1, -1 }, // g - 6
  {-1, -1, 2, -1 }  // dp - 7
};

const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;

void setup() {
  // Initialize pins
  Serial.begin(9600);
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
}

void loop() {
  swState = digitalRead(pinSW);
  yAxisValue = analogRead(pinY); 
  xAxisValue = analogRead(pinX); 

// Check joystick movement (up, down, left, right)
  if (yAxisValue < minThreshold && !joyMoved) {
    moveSegment(up);
  } else if (yAxisValue > maxThreshold && !joyMoved) {
    moveSegment(down);
  } else if (xAxisValue > maxThreshold && !joyMoved) {
    moveSegment(right);
  } else if (xAxisValue < minThreshold && !joyMoved) {
    moveSegment(left);
  }


  // Check for a short press on the joystick button
  if (swState == LOW && swState != lastSwState) {
    // Toggle the state of the current segment
    segmentStates[currentSegment] = !segmentStates[currentSegment];
    restartTimer = millis();
  }
  lastSwState = swState;

   // Implement blinking for the current segment (DP)
  if (millis() - lastBlinkTime > blinkInterval) {
    lastBlinkTime = millis();
    state = !state;
    digitalWrite(segments[currentSegment], state);
  }

  // Reset on long press
  if (swState == LOW && lastSwState == LOW) {
    if (millis() - restartTimer > restartInterval) {
      resetDisplay();
    }
  }

  // Check to stop movement when joystick returns to the center position
  if (yAxisValue > minThreshold && yAxisValue < maxThreshold && xAxisValue > minThreshold && xAxisValue < maxThreshold) {
    joyMoved = false;
  }

  delay(20);  // A small delay between readings to prevent multiple movements
}

void moveSegment(int direction) {
  if (neighborSegments[currentSegment][direction] != -1) {
    digitalWrite(segments[currentSegment], segmentStates[currentSegment]);
    currentSegment = neighborSegments[currentSegment][direction];
  }
}

void resetDisplay() {
  for (int i = 0; i < segSize; i++) {
    digitalWrite(segments[i], LOW);
    segmentStates[i] = false;
  }
  currentSegment = 7;
}
