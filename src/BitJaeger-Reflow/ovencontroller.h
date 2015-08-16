#ifndef OVENCONTROLLER_H
#define OVENCONTROLLER_H


class OvenController
{
public:
  OvenController();

  float getTemp();
  void setHeating(bool state);
};

#endif // OVENCONTROLLER_H
