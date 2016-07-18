
const int actuatorPin = 2;
const int ledPin =  12;

boolean trigger = false;

unsigned long count = 0;
unsigned long currentCount = 0;

int ledState = LOW;        

int lowRange = 5000;

unsigned long previousMillis = 0;
unsigned long countPreviousMillis = 0;

const long interval = 50;
const long countInterval = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(3,INPUT_PULLUP);
}

void loop() {
  if (digitalRead(3) == LOW) {
    trigger = true;
  }

  if (trigger) {
      analogWrite(11, random(0, 25));
    
  unsigned long currentMillis = micros();
  unsigned long countCurrentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
    
    if (analogRead(A0) >= 450) {
      count++;
      tone(13, 35, 500);
    } 
  }

    if (countCurrentMillis - countPreviousMillis >= countInterval) {
      countPreviousMillis = countCurrentMillis;

      
      if (count >= lowRange) {
        digitalWrite(2, HIGH);
        delay(3000);
        digitalWrite(2, LOW);
        count = 0;
      }
      if (count == currentCount) {
        count = 0;
      }
      currentCount = count;
    }  
  }
}

