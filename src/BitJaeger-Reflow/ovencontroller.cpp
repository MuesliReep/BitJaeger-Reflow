#include "ovencontroller.h"

OvenController::OvenController(QObject *parent) : QObject(parent)
{
  serial = new QSerialPort(this);

  connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

  state = OFF;
}

bool OvenController::openSerial() {

  serial->setPortName(c->getSerialPort());
  serial->setBaudRate(QSerialPort::Baud115200);
  serial->setDataBits(QSerialPort::Data8);
  serial->setParity(QSerialPort::NoParity);
  serial->setStopBits(QSerialPort::OneStop);
  serial->setFlowControl(QSerialPort::NoFlowControl);

  if (serial->open(QIODevice::ReadWrite)) {

  } else {
    qDebug() << serial->errorString();
    return false;
  }

  qDebug() << "Serial open, waiting for alive byte...";

  // Wait for device
  QThread::sleep(4);
  serial->clear();

  sendMessage("a");

  return true;
}

void OvenController::closeSerial()
{
  if(serial->isOpen())
    serial->close();

  state = OFF;
}

void OvenController::setConfig(Config *c)
{
  this->c = c;
}
DeviceState OvenController::getState() const
{
  return state;
}

void OvenController::readData() {

  char next;
  //QByteArray data = serial->readLine(20); // readAll;

  bool ready = false;
  bool ok = true;

  while(ok) {

    ok = serial->getChar(&next);
    if(ok)
      data.append(next);

    if(next == ';') {
      ready = true;
      ok = false;
    }
  }

  if(ready) {

    qDebug() << data;

    QString response(data);

    QStringList list = response.split(";");

    if(list[0].contains("a")) {

      state = ON;
      qDebug() << "Alive byte received";
    } else if(list[0].contains("b")) {
      qDebug() << "Temperature received";
      parseTemp(list[0]);
    } else if(list[0].contains("c")) {
      qDebug() << "Heating ON received";
    } else if(list[0].contains("d")) {
      qDebug() << "Heating OFF received";
    } else if(list[0].contains("e")) {
      qDebug() << "Cooling ON received";
    } else if(list[0].contains("f")) {
      qDebug() << "Cooling OFF received";
    } else if(list[0].contains("z")) {
      qDebug() << "Bad input received";
    }

    data.clear();
  }
}

void OvenController::getTemp() {
  sendMessage("b");
}

void OvenController::setHeating(bool state) {

  // c = heating ON
  // d = heating OFF

  sendMessage(state ? "c" : "d");
}

void OvenController::setCooling(bool state) {

  // e = cooling ON
  // f = cooling OFF

  sendMessage(state ? "e" : "f");
}

void OvenController::parseTemp(QString message) {

  bool ok;

  QStringList f = message.split("b");

  float temp = f[1].toFloat(&ok);

  if(!ok)
    temp = -1.0;

  emit updateTemp(temp);
}

void OvenController::sendMessage(const QString message)
{
  serial->write(message.toLocal8Bit());
}
