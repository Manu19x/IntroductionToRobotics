const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

const int potentiometerPinRed = A0;
const int potentiometerPinGreen = A1;
const int potentiometerPinBlue = A2;

void setup() {
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // citeste valorile de pe potentiometru
  int redValue = analogRead(potentiometerPinRed);
  int greenValue = analogRead(potentiometerPinGreen);
  int blueValue = analogRead(potentiometerPinBlue);

  //mapeaza valorile de pe potentiometru(0-1023) la valorile brightness-ului LED-ului (0-255)
  int redBrightness = map(redValue, 0, 1023, 0, 255);
  int greenBrightness = map(greenValue, 0, 1023, 0, 255);
  int blueBrightness = map(blueValue, 0, 1023, 0, 255);

  // updateaza led-ul RBG la valorile ajutate de brightness
  analogWrite(redPin, redBrightness);
  analogWrite(greenPin, greenBrightness);
  analogWrite(bluePin, blueBrightness);
}
