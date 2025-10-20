
const int LED1 = A7;
const int LED2 = A6;
const int LED3 = A5;
const int LED4 = A2;

const int leftButtion  = 2;
const int rightButton = 3; 

int direction = 0;  
int currentLED = 0;  
unsigned long lastUpdate = 0; 
const int interval = 200;  

// Store all LED pins in an array for easy looping
int leds[] = {LED1, LED2, LED3, LED4};

void setup() {
  // Set all LED pins as outputs
  for (int i = 0; i < 4; i++){
    pinMode(leds[i], OUTPUT);
  }

  pinMode(leftButtion, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
}

void loop() {
  // Check if the LEFT button is pressed
  if (digitalRead(leftButtion) == LOW) {
    direction = 0; 
  } 
  // Check if the RIGHT button is pressed
  else if (digitalRead(rightButton) == LOW) {
    direction = 1; 
  }

  unsigned long now = millis();

  // Update LED position only if the set interval time has passed
  if (now - lastUpdate >= interval) {
    lastUpdate = now;

    // Turn off all LEDs before lighting the next one
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
    
    // Turn on the current LED
    digitalWrite(leds[currentLED], HIGH);

    // Move to the next LED based on direction
    if (direction == 0) {
      currentLED++;
      if (currentLED > 3){
        currentLED = 0;
      }
    } 
    else {
      currentLED--;
      if (currentLED < 0){
        currentLED = 3;
      }
    }
  }
}

