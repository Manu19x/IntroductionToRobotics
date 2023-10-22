const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

const int potentiometerPinRed = A0;
const int potentiometerPinGreen = A1;
const int potentiometerPinBlue = A2;

void setup() {
  // Set the RGB LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Read values from the potentiometers
  int redValue = analogRead(potentiometerPinRed);
  int greenValue = analogRead(potentiometerPinGreen);
  int blueValue = analogRead(potentiometerPinBlue);

  // Map the potentiometer values (0-1023) to the LED brightness (0-255)
  int redBrightness = map(redValue, 0, 1023, 0, 255);
  int greenBrightness = map(greenValue, 0, 1023, 0, 255);
  int blueBrightness = map(blueValue, 0, 1023, 0, 255);

  // Update the RGB LED with the adjusted brightness values
  analogWrite(redPin, redBrightness);
  analogWrite(greenPin, greenBrightness);
  analogWrite(bluePin, blueBrightness);
}