#include <stdint.h>

const uint8_t LEFT_PINS[3] = {2, 3 ,4};
const uint8_t RIGHT_PINS[3] = {8, 9, 10};
const uint16_t interval = 1000;
const uint8_t R = 0;
const uint8_t Ry = 1;
const uint8_t Y = 2;
const uint8_t G = 3;

typedef struct {
  uint8_t state;
  bool goGreen;
  uint8_t pins[3];
} light;

int16_t timer;
uint16_t lastChange;

light leftLight;
light rightLight;

void setup() {
  Serial.begin(9600);

  pinMode(LEFT_PINS[0], OUTPUT);
  pinMode(LEFT_PINS[1], OUTPUT);
  pinMode(LEFT_PINS[2], OUTPUT);
  pinMode(RIGHT_PINS[8], OUTPUT);
  pinMode(RIGHT_PINS[9], OUTPUT);
  pinMode(RIGHT_PINS[10], OUTPUT);

  lastChange = 0;
  
  leftLight = {
    G,
    false,
    {LEFT_PINS[0],LEFT_PINS[1],LEFT_PINS[2]}
  };

  rightLight = {
    R,
    true,
    {RIGHT_PINS[0],RIGHT_PINS[1],RIGHT_PINS[2]}
  };

}

void loop(){
  timer = millis();

  if(timer - lastChange >= interval){
    nextState(&leftLight);
    nextState(&rightLight);

    handleState(&leftLight);
    handleState(&rightLight);
    
    lastChange = timer;
  }
}

void ledOn(uint8_t led) {
  digitalWrite(led, HIGH);
}

void ledOff(uint8_t led) {
  digitalWrite(led, LOW);
}

void nextState(light* l){
  if((l->state == R && l->goGreen == false) || (l->state == G && l->goGreen == true)){
    l->goGreen = !l->goGreen;
  }

  if(l->goGreen){
    if(l->state == Ry){
      l->state = G;
    } else {
      l->state = Ry;
    }
  } else {
    if(l->state == Y){
      l->state = R;
    } else {
      l->state = Y;
    }
  }
}

void handleState(light* l){
  switch (l->state) {
    case R:
      ledOn(l->pins[0]);
      ledOff(l->pins[1]);
      ledOff(l->pins[2]);
      break;
    case Ry:
      ledOn(l->pins[0]);
      ledOn(l->pins[1]);
      ledOff(l->pins[2]);
      break;
    case Y:
      ledOff(l->pins[0]);
      ledOn(l->pins[1]);
      ledOff(l->pins[2]);
      break;
    case G:
      ledOff(l->pins[0]);
      ledOff(l->pins[1]);
      ledOn(l->pins[2]);
      break;
  }
}