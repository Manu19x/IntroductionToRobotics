const int floorLEDPins[] = {10, 11, 12}; // pinurile etajelor - (rosii) 
const int operationalLEDPin = 13;      // Pinul operational (verde)
const int buttonPins[] = {4, 5, 6};     // Pinurile pentru call buttons
const int buzzerPin = 3;                // pinul pentru buzzer

int currentFloor = 0;   // Inițializam liftul la etajul 0
int desiredFloor = -1;  // Initializam etajul dorit
bool isMoving = false;    // Starea liftului (stationare / miscare)
bool isBlinking = false;  // Flag pentru ledul verde
bool lastMovementStatus = false;  // urmarim statusul de miscare anterior
unsigned long lastMovementChangeTime = 0;  // Urmărim timpul când starea miscarii s-a schimbat ultima data

unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 500; // 
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
      stopMovingSound(); 
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
    stopMovingSound(); 
    tone(buzzerPin, 1000, 100);  
  } else {
    if (isMoving != lastMovementStatus) {
      lastMovementStatus = isMoving;
      lastMovementChangeTime = millis();
      if (isMoving) {
        playMovingSound();  
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
    // Liftul stationeaza, aprinde LED-ul la etajul curent sau dorit
    for (int i = 0; i < 3; i++) {
      digitalWrite(floorLEDPins[i], (currentFloor == i || desiredFloor == i));
    }
  }
}

void playMovingSound() {
  tone(buzzerPin, 700, 1000);
}

void stopMovingSound() {
  noTone(buzzerPin);
}
/// am incercat in update floor led sa fac si trecerea prin nivelul 1 (led-ul din mijloc) fara succes :'(
