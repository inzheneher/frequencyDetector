// Pin constant declaration
const int nextStagePin =  8; //output
const int triggerPin   =  7; //input
const int sparkPin     = 10; //output
const int pulsePin     = A4; //19 output
const int buzzerPin    = A0; //output
const int recivePin    = A5; //28 input
//***

// Program enable trigger
boolean trigger = false;
//***

// Buzzer configurations:
const int frequency =  1000;
const int duration  = 500;
//***

// Timers vsriables
unsigned long count        = 0;
unsigned long currentCount = 0;
unsigned long sparkCount   = 0;

unsigned long previousMillis      = 0;
unsigned long countPreviousMillis = 0;
const long interval       =   50; // pulse generator period (us)
const long countInterval  = 1000; // count pulse interval (ms)
long sparkInterval  =  100; // start time between sparks (ms)

//***    

// Pulses settings
int lowRange = 500; // Amount of counting pulses
int ledState = LOW;  // Default pulse state
int sparkLedState = LOW; // Default spark state
int pulseDetectionLevel = 600; // Detect pulses higher level, than this
//***

// Next stage settings
const int nextStageDelay = 3000;
//***

// Random settings
const int lowRangeRandom  =  0;
const int highRangeRandom = 25;
//***

void setup() {
  //Serial.begin(9600);
  pinMode(pulsePin, OUTPUT);
  pinMode(triggerPin,INPUT_PULLUP);
  pinMode(nextStagePin, OUTPUT);
  pinMode(sparkPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(recivePin, INPUT);
}

void loop() {

  // Wait for signal from main controller
  if (digitalRead(triggerPin) == LOW) {
    trigger = true;
  }
  
  // Program starts from here after signal from main controller
  if (trigger) {
      //analogWrite(sparkPin, random(lowRangeRandom, highRangeRandom));

  
  unsigned long currentMillis = micros();
  unsigned long countCurrentMillis = millis();
  unsigned long sparkPreviousMillis = millis();

  if (sparkPreviousMillis - sparkCount >= sparkInterval) {
    
    sparkCount = sparkPreviousMillis;
    
        if (sparkLedState == LOW) {
          sparkLedState = HIGH;
        } else {
          sparkLedState = LOW;
        }
        digitalWrite(sparkPin, sparkLedState);
        sparkInterval = random(150);
      }

  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(pulsePin, ledState);
    //Serial.println(analogRead(recivePin));
    if (analogRead(recivePin) > pulseDetectionLevel) {
      
      count++;
      //Serial.println(digitalRead(recivePin));
      tone(buzzerPin, frequency, duration);
      //analogWrite(buzzerPin, random(35, 65));
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
      analogWrite(buzzerPin, 0);
    }
  }

    if (countCurrentMillis - countPreviousMillis >= countInterval) {
      countPreviousMillis = countCurrentMillis;
      
      if (count >= lowRange) {
        digitalWrite(sparkPin, LOW);
        digitalWrite(nextStagePin, HIGH);
        delay(nextStageDelay);
        digitalWrite(nextStagePin, LOW);
        count = 0;
        trigger = false;
      }
      if (count == currentCount) {
        count = 0;
      }
      currentCount = count;
    }  
  }
}

