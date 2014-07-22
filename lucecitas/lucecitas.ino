

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
long debounceDelay = 50; // velocidad de debounce

// ESTADO LEDS
int ledState = 0;
long previousMillis = 0;
long delayVel = 2000; // velocidad de prendido de los leds

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
  //leer el estado de los botones
  int readingStep = digitalRead(buttonPinStep);
  int readingReset = digitalRead(buttonPinReset);

  // ver si el estado ha cambiado
  if (readingStep != lastStepButtonState || readingReset != lastResetButtonState) {
    lastDebounceTime = millis();
  }

  //ver si ya paso el tiempo de bounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // logica para el boton de aumentar la velocidad
    if (readingStep != buttonStepState) {
      //asignar el nuevo valor
      buttonStepState = readingStep;
      // verificar que se presiono el boton
      if (buttonStepState == HIGH) {        
        // rebajar la velocidad de los leds
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
    // logica para el boton de reset
    if (readingReset != buttonResetState) {
      buttonResetState = readingReset;
      if (buttonResetState == HIGH) {
        // resetear la velocidad de los leds si se presiono
        delayVel = 2000;
      }
    }
  }
  // guardar el valor leido
  lastStepButtonState = readingStep;
  lastResetButtonState = readingReset;
}

void loop() {

  // verificar el estado de los botones
  CheckButtons();
  
  // Obtener la cantidad de milisegundos pasados desde que se inicio el programa
  unsigned long currentMillis = millis();

  // si ya ha pasado mas tiempo que el establecido como velocidad
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




