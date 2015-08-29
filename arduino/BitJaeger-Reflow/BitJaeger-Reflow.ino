
#include <TimerOne.h>
#include "Adafruit_MAX31855.h"

// The control pins
#define HEATINGPIN A0
#define COOLINGPIN 9

// The SPI pins for the thermocouple sensor
#define MAX_CLK 5
#define MAX_CS 6
#define MAX_DATA 7

Adafruit_MAX31855 thermocouple(MAX_CLK, MAX_CS, MAX_DATA);

volatile float temp;

// Prototypes:
void sendTemp();
void setHeating(bool state);
void setCooling(bool state);
void sendAlive();
void parseSerialRequest();
void sendError();

void setup() {

  // Start the serial connection
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  temp = 12.5;

  // Setup heating & cooling output pins
  pinMode(HEATINGPIN, OUTPUT);
  pinMode(COOLINGPIN, OUTPUT);

  // wait for MAX chip to stabilize
  delay(1000);

  //Timer1.initialize(100*1000);
  sendAlive();
}

char inChar[1024];

// a = request alive
// b = temp request
// c = heating ON
// d = heating OFF
// e = cooling ON
// f = cooling OFF

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0) {

//    inByte = Serial.read();

    // Read 1 char
    Serial.readBytes(inChar, 1);

    switch(inChar[0]) {
      case 'a':
        sendAlive();
        break;
      case 'b':
        sendTemp();
        break;
      case 'c':
        setHeating(true);
        break;
      case 'd':
        setHeating(false);
        break;
      case 'e':
        setCooling(true);
        break;
      case 'f':
        setCooling(false);
        break;
      default:
        //sendError();
        break;
    }
  }
}

void parseSerialRequest() {

}

void sendTemp() {
  Serial.print('b');
  Serial.println(temp);
  
}

void setHeating(bool state) {

  Serial.println(state ? 'c' : 'd');
}

void setCooling(bool state) {

  Serial.println(state ? 'e' : 'f');
}

void sendAlive() {
  Serial.println('a');
}

void sendError() {
  Serial.println('z');
}
