
const int LED1 = A7;
const int LED2 = A6;
const int LED3 = A5;
const int LED4 = A2;
const int potentiometerPin = A0; 

// Create an array to hold all LED pins for easier looping
int leds[] = {LED1, LED2, LED3, LED4};

void setup() {
  // Set each LED pin as an OUTPUT so we can turn them on/off
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Read the analog value from the potentiometer 
  int potentiometerValue = analogRead(potentiometerPin);

  // Map potentiometer reading to a delay range
  int ledDelay = map(potentiometerValue, 0, 1023, 600, 50);

  // Loop through each LED, turning it on and off one by one
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
    delay(ledDelay);
    digitalWrite(leds[i], LOW);
  }
}
