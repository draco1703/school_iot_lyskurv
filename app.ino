#include <stdint.h>

#define RED_LEFT 2
#define YELLOW_LEFT 3
#define GREEN_LEFT 4

#define RED_RIGHT 8
#define YELLOW_RIGHT 9
#define GREEN_RIGHT 10

/*
	struct state options:
	0: red
	1: red + yellow
	2: yellow
	3: green
*/

typedef struct Light {
	uint8_t state;
	bool active;
} light;

void nextState(light input){
	Serial.printf(input.state);
}

uint16_t stamp;

void ledOn(int led) {
	digitalWrite(led, HIGH);
}
void ledOff(int led) {
	digitalWrite(led, LOW);
}

void setup() {
	Serial.begin(9600);

	stamp = millis();

	pinMode(RED_LEFT, OUTPUT);
	pinMode(YELLOW_LEFT, OUTPUT);
	pinMode(GREEN_LEFT, OUTPUT);

	pinMode(RED_RIGHT, OUTPUT);
	pinMode(YELLOW_RIGHT, OUTPUT);
	pinMode(GREEN_RIGHT, OUTPUT);
}

void loop(){

}