
const int LED1 = A7;
const int LED2 = A6;
const int LED3 = A5;
const int LED4 = A2;  

void setup() {
  // Set each LED pin as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
   // Turn on LED1 for 2 seconds, then turn it off
  digitalWrite(LED1, HIGH);  
  delay(2000);
  digitalWrite(LED1, LOW);   

   // Turn on LED2 for 1 seconds, then turn it off
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED2, LOW);

  // Turn on LED3 for 0.5 seconds, then turn it off
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);

  // Turn on LED4 for 0.25 seconds, then turn it off
  digitalWrite(LED4, HIGH);
  delay(250);
  digitalWrite(LED4, LOW);

  // Blink each LED quickly (0.1 sec) in sequence (from LED1 to LED4)
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);

  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);

  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);

  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED4, LOW);

  // Blink LED3 again quickly
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);

  // Blink LED2 again quickly
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);

  delay(500);
}
