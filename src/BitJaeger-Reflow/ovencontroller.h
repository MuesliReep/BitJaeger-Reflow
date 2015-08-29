#ifndef OVENCONTROLLER_H
#define OVENCONTROLLER_H

#include <QtSerialPort/QtSerialPort>
#include <QDebug>
#include <QStringList>
#include <QString>

#include "config.h"

class OvenController
{
public:
  OvenController() {}
  OvenController(Config *C);
  ~OvenController();

  float getTemp();
  void setHeating(bool state);
  void setCooling(bool state);
  bool initialise();

  QSerialPort serial;
private:
  Config *c;

  void openConnection();
  void closeConnection();
  QString sendMessage(QString message, int timeOut = 700, bool waitResponse = true);
};

#endif // OVENCONTROLLER_H
