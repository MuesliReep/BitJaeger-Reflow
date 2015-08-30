#include "pid.h"

PID::PID() {


}

PID::PID(Config *C) {

  c = C;
}

void PID::initialise() {

  Kp = c->getP();
  Ki = c->getI();
  Kd = c->getD();

  windUpPercent = c->getWindUpPercent();
}

bool PID::update(float target, float temp, bool *heating, bool *cooling) {

  float MV;    // Manipulated Variable (ie. whether to turn on or off the relay!)
  float Error; // how off we are
  float Slope; // the change per second of the error

  Error = target - temp;
  Slope = tempPrevious - temp;

  // Sum the error over time
  Summation += target - temp;

  if ( (temp < (target * (1.0 - windUpPercent))) ||
     (temp > (target * (1.0 + windUpPercent))) ) {

    // to avoid windup, we only integrate within 5%
    Summation = 0;
  }

  // proportional-derivative controller only
  MV = Kp * Error + Ki * Summation + Kd * Slope;

  // Save the current temperature
  tempPrevious = temp;

  *heating = MV >= 1.0 ? true : false;
  *cooling = MV <= -1.0 ? true : false;

  return MV >= 1.0 ? true : false;
}



