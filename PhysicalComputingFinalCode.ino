// Potentiometer
const int potPin = A0;

// LED #1 connected to pin D9 
const int led1 = 9;    

// LED #2 connected to pin D10
const int led2 = 10;  

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // Reading potentiometer value (0 to 1023)
  int potVal = analogRead(potPin);         

  // Convert 0–1023 range to Pulse Width Modulation (PWM) range 0–255
  int pwmVal = map(potVal, 0, 1023, 0, 255);

  // Set brightness of LED #1 using PWM
  analogWrite(led1, pwmVal);

  // Set brightness of LED #2 using PWM
  analogWrite(led2, pwmVal);

  delay(5);
}
