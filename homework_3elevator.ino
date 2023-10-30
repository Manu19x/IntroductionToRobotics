const int floorLEDPins[] = {10, 11, 12}; // Pins for floor LEDs pinurile
const int operationalLEDPin = 13;      // Pin for operational state LED
const int buttonPins[] = {4, 5, 6};     // Pins for call buttons
const int buzzerPin = 3;                // Pin for the buzzer

int currentFloor = 0;   // Initialize the elevator at floor 0
int desiredFloor = -1;  // Initialize desired floor
bool isMoving = false;    // Elevator state (moving or stationary)
bool isBlinking = false;  // Flag for LED blinking
bool lastMovementStatus = false;  // Track the previous movement status
unsigned long lastMovementChangeTime = 0;  // Track the time when the movement status last changed

unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 500; // 0.5 seconds
unsigned long moveStartTime = 0;
const unsigned long moveDuration = 2000;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(floorLEDPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(operationalLEDPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  checkButtonPresses();
  if (isMoving) {
    manageElevatorMovement();
  } else {
    elevatorIdle();
  }
}

void checkButtonPresses() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (i != currentFloor) {
        initiateElevatorMovement(i);
        playMovingSound(); 
      }
    }
  }
}

void initiateElevatorMovement(int destinationFloor) {
  if (currentFloor < destinationFloor) {
    for (int i = currentFloor; i <= destinationFloor; i++) {
      currentFloor = i;
      isMoving = true;
      moveStartTime = millis();
      desiredFloor = destinationFloor;
      stopMovingSound();  // Oprește sunetul de miscare
      delay(500);  // Mic delay între niveluri
      if (i == 1) {
        tone(buzzerPin, 1500, 100);  // Sunet pentru trecerea prin nivelul 1
      }
      startBlinkingLED();
    }
  } else {
    for (int i = currentFloor; i >= destinationFloor; i--) {
      currentFloor = i;
      isMoving = true;
      moveStartTime = millis();
      desiredFloor = destinationFloor;
      stopMovingSound();  // Oprește sunetul de miscare
      delay(500);  // Mic delay între niveluri
      if (i == 1) {
        tone(buzzerPin, 1500, 100);  // Sunet pentru trecerea prin nivelul 1
      }
      startBlinkingLED();
    }
  }
}

void manageElevatorMovement() {
  updateOperationalLED();
  if (millis() - moveStartTime >= moveDuration) {
    isMoving = false;
    stopBlinkingLED();
    updateFloorLEDs();
    stopMovingSound(); // Oprește sunetul de miscare
    tone(buzzerPin, 1000, 100);  // Sunet pentru sosire
  } else {
    if (isMoving != lastMovementStatus) {
      lastMovementStatus = isMoving;
      lastMovementChangeTime = millis();
      if (isMoving) {
        playMovingSound();  // Sunet pentru începutul deplasării
      }
    }
  }
}

void elevatorIdle() {
  digitalWrite(operationalLEDPin, HIGH);
}

void startBlinkingLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkTime >= blinkInterval) {
    isBlinking = !isBlinking;
    digitalWrite(operationalLEDPin, isBlinking);
    lastBlinkTime = currentMillis;
  }
}

void stopBlinkingLED() {
  digitalWrite(operationalLEDPin, HIGH);
}

void updateOperationalLED() {
  if (isMoving) {
    startBlinkingLED();
  } else {
    stopBlinkingLED();
  }
}

void updateFloorLEDs() {
  if (isMoving) {
    for (int i = 0; i < 3; i++) {
      if (i == currentFloor) {
        digitalWrite(floorLEDPins[i], HIGH);
        if (i == 1) {
          delay(500);  // Așteaptă puțin timp pentru a indica trecerea prin etajul 1
        }
      } else {
        if ((currentFloor == 1 && (desiredFloor == 0 || desiredFloor == 2)) || (desiredFloor == 1 && (currentFloor == 0 || currentFloor == 2))) {
          digitalWrite(floorLEDPins[1], LOW);  // Stinge nivelul 1 înainte de a trece la nivelul 0 sau 2
          digitalWrite(floorLEDPins[i], HIGH);
          if (i == 1) {
            delay(500);  // Așteaptă puțin timp pentru a indica trecerea prin etajul 1
          }
        } else {
          digitalWrite(floorLEDPins[i], LOW);
        }
      }
    }
  } else {
    // Elevator stationary, aprinde LED-ul la etajul curent sau dorit
    for (int i = 0; i < 3; i++) {
      digitalWrite(floorLEDPins[i], (currentFloor == i || desiredFloor == i));
    }
  }
}

void playMovingSound() {
  // Sunet continuu pentru miscare
  tone(buzzerPin, 700, 1000);
}

void stopMovingSound() {
  // Oprește sunetul de miscare
  noTone(buzzerPin);
}
/// am incercat in update floor led sa fac si trecerea prin nivelul 1 (led-ul din mijloc) fara succes :'(