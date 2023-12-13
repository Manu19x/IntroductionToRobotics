#include <LiquidCrystal.h>

#define LCD_WIDTH 16

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int joyX = A0;
const int joyY = A1;
const int joySW =  2;

int xValue = 0;
int yValue = 0;
int minThreshold = 400;
int maxThreshold = 600;
bool joyMovedX = false;
bool joyMovedY = false;
bool swState = false;
bool lastSwState = false;


byte leftArr[8] = {
  B00100,
  B01100,
  B11100,
  B11111,
  B11100,
  B01100,
  B00100,
  B00000
};
byte rightArr[8] = {
  B00100,
  B00110,
  B00111,
  B11111,
  B00111,
  B00110,
  B00100,
  B00000
};

byte bell[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000

};
byte crown[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};
byte questionmark[8] = {
  B00110,
  B01001,
  B01001,
  B00001,
  B00010,
  B00100,
  B00000,
  B00100
};
int score = 0;
int highscore = 0;
long playMillis = 0;

enum MenuStates {
  START_GAME, HIGH_SCORE, SETTINGS, ABOUT, PLAYING, DETAILS
} menuState;

bool displayAboutText = false;

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, leftArr);
  lcd.createChar(1, rightArr);
  lcd.createChar(2, bell);
  lcd.createChar(3, crown);
  lcd.createChar(4, questionmark);

  pinMode(joySW, INPUT_PULLUP);

  showIntroMessage("PRESS JSW."); // Afiseaza mesajul introductiv cu un text la alegere

  // Setează starea inițială a meniului după ce a fost afișat mesajul introductiv
  menuState = START_GAME;
}

void loop() {
  switch(menuState) {
    case START_GAME:
      lcd.setCursor(1, 0);
      lcd.write(byte(1));
      centerTextOnLcd("Start game", 0);
      lcd.setCursor(14, 0);
      lcd.write(byte(0));
      centerTextOnLcd("JS button=start", 1);
      break;

    case HIGH_SCORE:
        lcd.setCursor(1,0);
        lcd.write(byte(3));
        centerTextOnLcd("HighScore", 0);
        lcd.setCursor(14, 0);
        lcd.write(byte(3));
        centerTextOnLcd("JS button=enter", 1);
        //centerTextOnLcd(String("Your HighScore:") + String(highscore), 1);
        break;

    case SETTINGS:
      lcd.setCursor(1, 0);
      lcd.write(byte(2));
      centerTextOnLcd("Settings", 0);
      lcd.setCursor(14, 0);
      lcd.write(byte(2));
      centerTextOnLcd("JS button=enter", 1);
      break;

    case ABOUT:
      lcd.setCursor(1, 0);
      lcd.write(byte(4));
      centerTextOnLcd("About", 0);
      lcd.setCursor(14, 0);
      lcd.write(byte(4));
      centerTextOnLcd("JS button=enter", 1);
      break;
    
   
    case DETAILS:
      lcd.setCursor(1, 0);
      centerTextOnLcd("Joc creat de", 0);
      centerTextOnLcd("Marian Matea", 1);
      break;

  }
  joystickEventCheck();

}
void showIntroMessage(const char* message) {
  lcd.clear();
  centerTextOnLcd("WELCOME!", 0); // Afiseaza mesajul introductiv centrat pe prima linie
  
  // Afiseaza mesajul primit ca parametru centrat pe a doua linie
  centerTextOnLcd(message, 1);

  while(digitalRead(joySW) == HIGH); 
  delay(500); 

  lcd.clear();
}

void centerTextOnLcd(String text, short line) {   ///afiseaza textul - *text* centrat - la linia -*line*
  short l = text.length();
  short spaces = (LCD_WIDTH - l) / 2; /// LCD width - latimea totala a ecranului lcd --- formula pentru nr spatii necesare pt a centra textul
  lcd.setCursor(spaces, line);
  lcd.print(text);
}

void changeMenuState(bool fw) { /// primim un bool pentru a decide in ce directie mergem -> (true - inainte) -> (false - inapoi)
  if(fw) {
    if(menuState == 3) {
      menuState = 0;   
    } else {
      menuState = menuState + 1;  
    }
  } else {
    if(menuState == 0) {
      menuState = 3;   
    } else {
      menuState = menuState - 1;  
    }
  }
  lcd.clear();
}
void joystickEventCheck() {
  yValue = analogRead(joyY);
  if (yValue > maxThreshold && joyMovedY == false) {
    switch(menuState) {
      case START_GAME:
      case HIGH_SCORE:
      case SETTINGS:
      case PLAYING:
        changeMenuState(true); // inapoi în meniu
        break;
    }
    joyMovedY = true;
  }
  if (yValue < minThreshold && joyMovedY == false) {
    switch(menuState) {
      case START_GAME:
      case HIGH_SCORE:
      case SETTINGS:
      case ABOUT:
        changeMenuState(false); // inainte în meniu
        break;
    }
    joyMovedY = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMovedY = false;
  }
 
  swState= digitalRead(joySW);
  if (swState !=  lastSwState) {
    if (swState == LOW) {
      switch(menuState) {
        case ABOUT:
        menuState=DETAILS;
        lcd.clear();
        break;
        case DETAILS:
        menuState=ABOUT;
        lcd.clear();
        break;
      }
    }
    lastSwState = swState;
  }

}
