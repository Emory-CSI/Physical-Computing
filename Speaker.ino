const int speakerPin = 8;

void setup() {
  // Note 1
  tone(speakerPin, 262, 400); 
  delay(500);

  // Note 2
  tone(speakerPin, 294, 400);  
  delay(500);

  // Note 3
  tone(speakerPin, 330, 400); 
  delay(500);

  // Note 4
  tone(speakerPin, 392, 600);  
  delay(1000);
}

void loop() {

  setup();
}
