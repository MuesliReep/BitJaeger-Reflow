#ifndef PID_H
#define PID_H

#include "config.h"

class PID
{
public:
  PID();
  PID(Config *C);

  bool update(float target, float temp, bool *heating, bool *cooling);
  void initialise();

private:

  float Kp;
  float Ki;
  float Kd;

  float Summation;
  float tempPrevious;
  float windUpPercent;

  Config *c;
};

#endif // PID_H
