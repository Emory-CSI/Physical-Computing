#include <Servo.h>


const int potPin  = A0;
const int servoPin = 10;
const int ledPins[] = {A7, A6, A5, A2};
const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);


Servo myServo;


void setup() {
 myServo.attach(servoPin);
 for (int i = 0; i < numLEDs; i++) {
   pinMode(ledPins[i], OUTPUT);
   digitalWrite(ledPins[i], LOW);
 }
}


void loop() {
 int raw = analogRead(potPin);


 // Reverse direction safely
 int angle = map(raw, 0, 1023, 180, 0);
 angle = constrain(angle, 0, 180);
 myServo.write(angle);


 // Reverse LED logic to match servo direction
 int step = 1023 / numLEDs;
 for (int i = 0; i < numLEDs; i++) {
   if (raw < step * (numLEDs - i))
     digitalWrite(ledPins[i], HIGH);
   else
     digitalWrite(ledPins[i], LOW);
 }


 delay(15);
}


