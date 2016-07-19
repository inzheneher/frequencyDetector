// Pin constant declaration
const int nextStagePin =  2;
const int triggerPin   =  3;
const int sparkPin     = 11;
const int pulsePin     = 12;
const int buzzerPin    = 13;
const int recivePin    = A0;
//***

// Program enable trigger
boolean trigger = false;
//***

// Buzzer configurations:
const int frequency =  35;
const int duration  = 500;
//***

// Timers vsriables
unsigned long count        = 0;
unsigned long currentCount = 0;
unsigned long previousMillis      = 0;
unsigned long countPreviousMillis = 0;
const long interval       =   50;
const long countInterval  = 1000;
//***    

// Pulses settings
int lowRange = 5000; // Amount of counting pulses
int ledState = LOW;  // Default pulse state
int pulseDetectionLevel = 450; // Detect pulses higher level, than this
//***

// Next stage settings
const int nextStageDelay = 3000;
//***

// Random settings
const int lowRange  =  0;
const int highRange = 25;
//***

void setup() {
  pinMode(pulsePin, OUTPUT);
  pinMode(triggerPin,INPUT_PULLUP);
}

void loop() {

  // Wait for signal from main controller
  if (digitalRead(triggerPin) == LOW) {
    trigger = true;
  }
  
  // Program starts from here after signal from main controller
  if (trigger) {
      analogWrite(sparkPin, random(lowRange, highRange));

  // 
  unsigned long currentMillis = micros();
  unsigned long countCurrentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(pulsePin, ledState);
    
    if (analogRead(recivePin) >= pulseDetectionLevel) {
      count++;
      tone(buzzerPin, frequency, duration);
    } 
  }

    if (countCurrentMillis - countPreviousMillis >= countInterval) {
      countPreviousMillis = countCurrentMillis;
      
      if (count >= lowRange) {
        digitalWrite(nextStagePin, HIGH);
        delay(nextStageDelay);
        digitalWrite(nextStagePin, LOW);
        count = 0;
      }
      if (count == currentCount) {
        count = 0;
      }
      currentCount = count;
    }  
  }
}

