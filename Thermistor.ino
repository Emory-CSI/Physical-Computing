

const int thermPin = A1;
const int ledPins[] = {A7, A6, A5, A2};
const int N = sizeof(ledPins) / sizeof(ledPins[0]);




int cut1 = 300; 
int cut2 = 300;  
int cut3 = 300;  
int cut4 = 300;  


void setup() {
 for (int i = 0; i < N; i++) {
   pinMode(ledPins[i], OUTPUT);
   digitalWrite(ledPins[i], LOW);
 }
 Serial.begin(9600);
}


void loop() {
 int reading = analogRead(thermPin); 
 Serial.println(reading);


 int level = 0;
 if (reading > cut1) level = 1;
 if (reading > cut2) level = 2;
 if (reading > cut3) level = 3;
 if (reading > cut4) level = 4;


 for (int i = 0; i < N; i++) {
   digitalWrite(ledPins[i], i < level ? HIGH : LOW);
 }


 delay(100);
}
