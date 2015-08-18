
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

void setup() {

  // wait for MAX chip to stabilize
  delay(1000);

  temp = 0.0;
  
  // Setup heating & cooling output pins
  pinMode(HEATINGPIN, OUTPUT);
  pinMode(COOLINGPIN, OUTPUT);

  // Start the serial connection
  Serial.begin(9600); 

  Timer1.initialize(100*1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void parseSerialRequest() {
  
}

void sendTemp() {
  Serial.print("b");
  Serial.print(temp);
}

void setHeating(bool state) {
}

void setCooling(bool state) {

}

void sendAlive() {
  Serial.print("a");
}

