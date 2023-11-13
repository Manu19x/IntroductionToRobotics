const byte latchPin = 11;
const byte clockPin = 10;
const byte dataPin = 12;

const byte segD1 = 4;
const byte segD2 = 5;
const byte segD3 = 6;
const byte segD4 = 7;

const byte startPause = 2;
const byte reset = 3;
const byte lap = 8;

const byte regSize = 8;

byte displayDigits[] = {
  segD1, segD2, segD3, segD4
};
const byte displayCount = 4;
const byte encodingsNumber = 10;

byte byteEncodings[encodingsNumber] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110  // 9
};

const bool displayOn = LOW;
const bool displayOff = HIGH;
bool wasPaused = false;
byte registers[regSize];

unsigned int currentNumber = 0;
unsigned long lastIncrement = 0;
bool isRunning = false;
bool isPaused = false;
unsigned long lapTime = 0;

void initializeDisplay() {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], displayOn);
  }

  for (int i = 0; i < regSize; i++) {
    registers[i] = byteEncodings[0];
  }

  for (int i = 0; i < displayCount; i++) {
    writeReg(registers[i]);
    tunOnDisplay(i);
    delay(5);
  }
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], displayOff);
  }

  pinMode(startPause, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);
  pinMode(lap, INPUT_PULLUP);

  initializeDisplay();
}

void loop() {
  handleButtons();

  if (isRunning && !isPaused) {
    writeNumber(currentNumber);
    if (millis() - lastIncrement > 100) {
      lastIncrement = millis();
      currentNumber++;
    }
  }
}

void handleButtons() {
  bool startPauseState = digitalRead(startPause);
  bool resetState = digitalRead(reset);
  bool lapState = digitalRead(lap);

  if (startPauseState == LOW) {
    handleStartPauseButton();
  }

  if (resetState == LOW) {
    handleResetButton();
  }

  if (lapState == LOW) {
    handleLapButton();
  }
}

void handleStartPauseButton() {
  delay(100);
  static unsigned long lastButtonPress = 0;

  if (millis() - lastButtonPress > 500) {
    if (!isRunning) {
      isRunning = true;
      isPaused = false;
    } else {
      isPaused = !isPaused;
      if (isPaused) {
        displayLapValues();
      }
    }
    lastButtonPress = millis();
  }
}

void handleResetButton() {
  delay(100);
  isRunning = false;
  isPaused = false;
  currentNumber = 0;
  lapTime = 0;
  initializeDisplay();
}

const byte maxLaps = 4;
unsigned int lapValues[maxLaps];
byte currentLapIndex = 0;

void handleLapButton() {
  delay(100);

  bool lapState = digitalRead(lap);  

  if (isRunning && !isPaused && lapState == LOW) {
    lapValues[currentLapIndex] = currentNumber;
    currentLapIndex = (currentLapIndex + 1) % maxLaps;
  } else if (isPaused && lapState == LOW) {
    displayLapValues();
  }
}
void displayLapValues() {
  Serial.println("Lap values:");
  for (int i = 0; i < maxLaps; i++) {
    Serial.println(lapValues[i]);
  }
}
void writeReg(byte encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}

void tunOffDisplays() {
  for (byte i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], displayOff);
  }
}

void tunOnDisplay(byte displayNumber) {
  digitalWrite(displayDigits[displayNumber], displayOn);
}

byte pausedDisplayStates[4];
unsigned int pausedNumber = 0;
byte pausedDisplayValues[4];

void saveDisplayValues() {
  for (byte i = 0; i < displayCount; i++) {
    pausedDisplayValues[i] = currentNumber % 10;
    currentNumber /= 10;
  }
}

void restoreDisplayValues() {
  currentNumber = 0;
  for (byte i = 0; i < displayCount; i++) {
    currentNumber += pausedDisplayValues[i] * pow(10, i);
  }
}

void writeNumber(unsigned int number) {
  byte currentDisplay = 3;

  if (isPaused) {
    for (int i = 0; i < displayCount; i++) {
      byte lastDigit = pausedDisplayValues[i];
      byte encoding = byteEncodings[lastDigit];

      tunOffDisplays();
      writeReg(encoding);
      tunOnDisplay(currentDisplay);

      currentDisplay--;
      delay(5);
      writeReg(B00000000);
    }
  } else {
    for (int i = 0; i < displayCount; i++) {
      byte lastDigit = number % 10;
      byte encoding = byteEncodings[lastDigit];

      tunOffDisplays();
      writeReg(encoding);
      tunOnDisplay(currentDisplay);

      currentDisplay--;
      delay(5);
      writeReg(B00000000);

      number /= 10;
    }
  }
}

