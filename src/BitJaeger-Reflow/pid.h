#ifndef PID_H
#define PID_H

#include "config.h"

class PID
{
public:
  PID();
  PID(Config *c);

  bool update(float temp, float time);
};

#endif // PID_H
