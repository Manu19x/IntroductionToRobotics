#include <EEPROM.h>

const int trigPin = 2;
const int echoPin = 3;
const int ldrPin = A0;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int sensorSamplingInterval = 5;
int ultrasonicThreshold = 100;
int ldrThreshold = 500;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  while (!Serial) { }

  sensorSamplingInterval = EEPROM.read(0);
  ultrasonicThreshold = EEPROM.read(1);
  ldrThreshold = EEPROM.read(2);

  Serial.println("Smart Environment Monitor and Logger");
  Serial.println("Press 'm' to access the main menu");
}

#define MAIN_MENU 0
#define SENSOR_SETTINGS_MENU 1
#define RESET_LOGGER_MENU 2
#define SYSTEM_STATUS_MENU 3
#define RGB_LED_CONTROL_MENU 4

int currentMenu = MAIN_MENU;

void loop() {
  char userChoice = ' ';

  while (Serial.available() > 0) {
    userChoice = Serial.read();
    
    switch (currentMenu) {
      case MAIN_MENU:
        switch (userChoice) {
          case 'm':
            Serial.println("Main Menu");
            Serial.println("1. Sensor Settings");
            Serial.println("2. Reset Logger Data");
            Serial.println("3. System Status");
            Serial.println("4. RGB LED Control");
            Serial.println("Enter your choice:");
            break;

          case '1':
            currentMenu = SENSOR_SETTINGS_MENU;
            break;

          case '2':
            currentMenu = RESET_LOGGER_MENU;
            break;

          case '3':
            currentMenu = SYSTEM_STATUS_MENU;
            break;

          case '4':
            currentMenu = RGB_LED_CONTROL_MENU;
            break;

          default:
            Serial.println("Invalid choice. Please try again.");
            break;
        }
        break;

      case SENSOR_SETTINGS_MENU:
        handleSensorSettings(userChoice);
        break;

      case RESET_LOGGER_MENU:
        handleResetLoggerData(userChoice);
        break;

      case SYSTEM_STATUS_MENU:
        handleSystemStatus(userChoice);
        break;

      case RGB_LED_CONTROL_MENU:
        handleRGBLEDControl(userChoice);
        break;

      default:
        break;
    }
  }
}

void handleSensorSettings(char userChoice) {
  switch (userChoice) {
    case '1':
      setSamplingInterval();
      break;
    case '2':
      setUltrasonicThreshold();
      break;
    case '3':
      setLDRThreshold();
      break;
    case '4':
      Serial.println("Returning to Main Menu");
      currentMenu = MAIN_MENU;
      break;
    case '5':
      Serial.println("Returning to Main Menu");
      currentMenu = MAIN_MENU;
      break;
    default:
      Serial.println("Invalid choice. Please try again.");
      break;
  }
}

void handleResetLoggerData(char userChoice) {
  switch (userChoice) {
    case '1':
      resetLoggerDataConfirmation();
      break;
    case '2':
      Serial.println("Returning to Main Menu");
      currentMenu = MAIN_MENU;
      break;
    case '3':
      Serial.println("Returning to Main Menu");
      currentMenu = MAIN_MENU;
      break;
    default:
      Serial.println("Invalid choice. Please try again.");
      break;
  }
}

void handleSystemStatus(char userChoice) {
  switch (userChoice) {
    case '1':
      displayCurrentSensorReadings();
      break;
    case '2':
      displayCurrentSensorSettings();
      break;
    case '3':
      displayLoggedData();
      break;
    case '4':
      Serial.println("Returning to Main Menu");
      currentMenu = MAIN_MENU;
      break;
    default:
      Serial.println("Invalid choice. Please try again.");
      break;
  }
}

void handleRGBLEDControl(char userChoice) {
  switch (userChoice) {
    case '1':
      manualColorControl();
      break;
    case '2':
      toggleAutomaticMode();
      break;
    case '3':
      Serial.println("Returning to Main Menu");
      currentMenu = MAIN_MENU;
      break;
    default:
      Serial.println("Invalid choice. Please try again.");
      break;
  }
}


void setSamplingInterval() {
  int interval = 0;
  while (interval < 1 || interval > 10) {
    Serial.println("Choose a value between 1 and 10 for the sampling interval:");
    while (!Serial.available()) {}  // asteapta pana se introduce o valoare
    interval = Serial.parseInt();   // citeste valoarea introdusa
    if (interval < 1 || interval > 10) {
      Serial.println("Invalid input. Please choose a value between 1 and 10.");
    }
  }

  //valoarea intervalului
  sensorSamplingInterval = interval;

  //salvam in adresa 0
  if (interval != EEPROM.read(0)) {
    EEPROM.update(0, sensorSamplingInterval);
    Serial.print("Sampling interval set to ");
    Serial.print(sensorSamplingInterval);
    Serial.println(" seconds.");
  } else {
    Serial.println("Sampling interval is already set to this value.");
  }
}

void resetLoggerDataConfirmation() {
  Serial.println("Reset Logger Data");
  Serial.println("Are you sure?");
  Serial.println("1. Yes");
  Serial.println("2. No");

  while (!Serial.available()) {}  

  char userChoice = Serial.read();

  switch (userChoice) {
    case '1':
      ///Functie de reset date-
      Serial.println("Logger data has been reset.");
      break;
    case '2':
      Serial.println("Logger data reset canceled.");
      break;
    default:
      Serial.println("Invalid choice. Please try again.");
      break;
  }
}

void setUltrasonicThreshold() {
  int threshold = 0;
  while (threshold < 1 || threshold > 1000) {
    Serial.println("Enter the ultrasonic threshold value (1-1000):");
    while (!Serial.available()) {}  
    threshold = Serial.parseInt();  

    if (threshold < 1 || threshold > 1000) {
      Serial.println("Invalid input. Please enter a value between 1 and 1000.");
    }
  }

  // prag pentru senzorul ultrasonic
  ultrasonicThreshold = threshold;

  // actualizam daca pragul este diferit de cel salvat
  if (threshold != EEPROM.read(1)) {
    EEPROM.update(1, ultrasonicThreshold);
    Serial.print("Ultrasonic threshold set to ");
    Serial.println(ultrasonicThreshold);
  } else {
    Serial.println("Ultrasonic threshold is already set to this value.");
  }
}

void setLDRThreshold() {
  int threshold = 0;
  while (threshold < 1 || threshold > 1023) {
    Serial.println("Enter the LDR threshold value (1-1023):");
    while (!Serial.available()) {} 
    threshold = Serial.parseInt();  

    if (threshold < 1 || threshold > 1023) {
      Serial.println("Invalid input. Please enter a value between 1 and 1023.");
    }
  }

  // prag LDR
  ldrThreshold = threshold;

  // actualizam daca pragul este diferit de cel salvat
  if (threshold != EEPROM.read(2)) {
    EEPROM.update(2, ldrThreshold);
    Serial.print("LDR threshold set to ");
    Serial.println(ldrThreshold);
  } else {
    Serial.println("LDR threshold is already set to this value.");
  }
}



void manualColorControl() {
  int redValue, greenValue, blueValue;

  Serial.println("Enter values for Red, Green, and Blue (0-255):");
  Serial.print("Red: ");
  while (!Serial.available()) {}
  redValue = Serial.parseInt();
  Serial.println(redValue);

  Serial.print("Green: ");
  while (!Serial.available()) {}
  greenValue = Serial.parseInt();
  Serial.println(greenValue);

  Serial.print("Blue: ");
  while (!Serial.available()) {}
  blueValue = Serial.parseInt();
  Serial.println(blueValue);

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void toggleAutomaticMode() {};

void displayCurrentSensorSettings() {
  Serial.println("Current Sensor Settings:");
  Serial.print("1. Sensor Sampling Interval: ");
  Serial.print(sensorSamplingInterval);
  Serial.println(" seconds");
  Serial.print("2. Ultrasonic Alert Threshold: ");
  Serial.print(ultrasonicThreshold);
  Serial.println(" cm");
  Serial.print("3. LDR Alert Threshold: ");
  Serial.print(ldrThreshold);
  Serial.println(" (analog value)");

  
}

void displayLoggedData() {
  int val;
  val = EEPROM.read(0); 
  Serial.println("Logged Data:");
  Serial.print("data: ");
  Serial.println(val); 
  
}


void displayCurrentSensorReadings() {
  Serial.println("Press any key to stop displaying readings.");
  unsigned long previousMillis = 0;
  const unsigned long interval = sensorSamplingInterval * 1000;

  while (!Serial.available()) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      
      int ultrasonicDistance = getUltrasonicDistance();
      int ldrValue = analogRead(ldrPin);

      Serial.println("Current Sensor Readings:");
      Serial.print("Ultrasonic Sensor: ");
      Serial.println(ultrasonicDistance);
      Serial.print("LDR Sensor: ");
      Serial.println(ldrValue);

      
      EEPROM.put(0, ultrasonicDistance);
      EEPROM.put(25, ldrValue); 
    }
  }
}

//distanta ultrasonic
int getUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
