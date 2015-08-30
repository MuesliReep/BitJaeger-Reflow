#ifndef OVENCONTROLLER_H
#define OVENCONTROLLER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QThread>

#include "config.h"

enum DeviceState { OFF, ON };

class OvenController : public QObject
{
  Q_OBJECT
public:
  explicit OvenController(QObject *parent = 0);

  bool openSerial();
  void closeSerial();

  void setConfig(Config *c);

  DeviceState getState() const;

  void setHeating(bool state);
  void setCooling(bool state);
  void getTemp();
private:
  QSerialPort *serial;
  Config *c;

  QByteArray data;

  DeviceState state;

  void parseTemp(QString message);
signals:
  void updateTemp(float temp);

public slots:

private slots:
  void sendMessage(const QString message);
  void readData();
};

#endif // OVENCONTROLLER_H
