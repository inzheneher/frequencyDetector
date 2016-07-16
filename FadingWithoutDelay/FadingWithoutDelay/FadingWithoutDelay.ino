
int ledPin = 13;    // LED connected to digital pin 9
int sensorPin = A0;
int lowest = 5;
int highest = 255;
unsigned int t_delay = 1;
int loopStep = 1;
int fadeValue = 0;
int counter = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change :
const long interval = 3;           // 1/0,000349 - детектируемая частота

void setup() {
  // nothing happens in setup
  pinMode(sensorPin, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  fadeUp();
  if (pickDetector()){
    counter++;
  }
  if (counter == 100){
    digitalWrite(2, HIGH);
  }
  if (counter ==200){
    digitalWrite(2, LOW);
    counter = 0;
  }
  fadeDown();
  zeroDetector();
}

void fadeUp(){
    while(fadeValue < 255) {
    unsigned long currentMillis = micros();
    
    if (currentMillis - previousMillis >= interval) {
      
      previousMillis = currentMillis;
  
      analogWrite(ledPin, fadeValue);
      fadeValue++;
    }
  }  
}

void fadeDown(){
    while(fadeValue > 10) {
    unsigned long currentMillis = micros();
    
    if (currentMillis - previousMillis >= interval) {
      
      previousMillis = currentMillis;
  
      analogWrite(ledPin, fadeValue);
      fadeValue--;
    }
  }
}

boolean pickDetector(){
  if (analogRead(A0) > 900) {
    return true;    
  }
}

void zeroDetector(){
  if (analogRead(A0) < 100) {
    digitalWrite(2, LOW);
  }
}

