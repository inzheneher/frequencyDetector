
int actPin = 2;
int ledPin = 13;    // LED connected to digital pin 9
int sensorPin = A0;
int lowest = 5;
int highest = 255;
unsigned int t_delay = 1;
int loopStep = 1;
int fadeValue = 0;
int counter = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 3;           // 1/0,000349 - детектируемая частота

unsigned long detectedPreviousMillis = 0;
const long detectedInterval = 5;
 
unsigned long basePreviousMillis = 0;
int detectedPulseAmountLowRange = 14;
int detectedPulseAmountHighRange = 20; //high range of detected pulses 32767
const long baseInterval = 100;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(actPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  unsigned long baseCurrentMillis = millis();
  
  fadeUp();
  
  if (pickDetector()){
    counter++;
  }
  
  fadeDown();

  if (baseCurrentMillis - basePreviousMillis >= baseInterval) {

    basePreviousMillis = baseCurrentMillis;
    
    if (counter >= detectedPulseAmountLowRange && counter <= detectedPulseAmountHighRange) {
      digitalWrite(actPin, HIGH);
      counter = 0;
    } else {
      counter = 0;
    }
  }
}

void fadeUp(){
    while(fadeValue < 255) {
    unsigned long currentMillis = micros();
    
    if (currentMillis - previousMillis >= interval) {
      
      previousMillis = currentMillis;
  
      analogWrite(ledPin, fadeValue);
      Serial.println(analogRead(A0));
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
      Serial.println(analogRead(A0));
      fadeValue--;
    }
  }
}

boolean pickDetector(){
  if (analogRead(A0) > 900) {
    if (analogRead(A0) > 900) {
      return true; 
    }
  }
}

void zeroDetector(){
  if (analogRead(A0) < 100) {
    digitalWrite(2, LOW);
  }
}

void intervalDetector (int count) {
  unsigned long currentMillis = millis();
    
  if (currentMillis - detectedPreviousMillis >= detectedInterval) {
    
    detectedPreviousMillis = currentMillis;

    if (count >= 500 && count <= 700) {
      digitalWrite(2, HIGH);
    }
  }
}

