
// LEDS
int led1 = 11;
int led2 = 12;
int led3 = 13;
int led4 = 8;
int led5 = 9;

// BOTONES
const int buttonPinStep = 3;
const int buttonPinReset = 4;

// ESTADO BOTONES
int buttonStepState = 0; 
int buttonResetState = 0; 
int lastStepButtonState = LOW;
int lastResetButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;

// ESTADO LEDS
int ledState = 0;
long previousMillis = 0;
long delayVel = 2000;

void setup() {
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT);     
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  pinMode(buttonPinStep, INPUT); 
  pinMode(buttonPinReset, INPUT); 
  Serial.begin(9600);
}

void CheckButtons(){
  int readingStep = digitalRead(buttonPinStep);
  int readingReset = digitalRead(buttonPinReset);

  if (readingStep != lastStepButtonState || readingReset != lastResetButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (readingStep != buttonStepState) {
      buttonStepState = readingStep;
      if (buttonStepState == HIGH) {
        if(delayVel > 500){
          delayVel = delayVel - 500;
        }
        else{
          if(delayVel > 100){
            delayVel = delayVel - 100;
          }
        }
      }

    }
    if (readingReset != buttonResetState) {
      buttonResetState = readingReset;
      if (buttonResetState == HIGH) {
        delayVel = 2000;
      }
    }

  }
  lastStepButtonState = readingStep;
  lastResetButtonState = readingReset;
}

void loop() {

  CheckButtons();
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > delayVel) {
    previousMillis = currentMillis;

    switch (ledState) {
    case 0:
      digitalWrite(led1, HIGH);
      ledState++;
      break;
    case 1:
      digitalWrite(led2, HIGH);
      ledState++;
      break;
    case 2:
      digitalWrite(led3, HIGH);
      ledState++;
      break;
    case 3:
      digitalWrite(led4, HIGH);
      ledState++;
      break;
    case 4:
      digitalWrite(led5, HIGH);
      ledState++;
      break;
    default:
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      ledState = 0;
      break;
    }
  }
}



