#include "ovencontroller.h"

OvenController::OvenController(Config *C) {

  c = C;
}

OvenController::~OvenController() {

  // Close serial if open
  serial.close();
}

float OvenController::getTemp() {

  float temp = -1.0;

  QString response = sendMessage("b");

  if(response.contains("b")) {

    QStringList l = response.split("b");
    temp = l[0].toFloat();
  }

  return 25.0;
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

bool OvenController::initialise() {

  // Set serial parameters
  serial.setPortName(c->getSerialPort());
  serial.setBaudRate(c->getBaudRate());

  // Try to open the port
  if (!serial.open(QIODevice::ReadWrite)) {

    qDebug() << "Cant open " << c->getSerialPort() << ", error code " << serial.error();
    return false;
  }

  // Send test message
  QString response = sendMessage("a");

  if(!response.contains("a") || response.contains("z")) {

    qDebug() << "Received bad response from oven controller";
    return false;
  }

  return true;
}

void OvenController::openConnection() {


}

void OvenController::closeConnection() {


}

QString OvenController::sendMessage(QString message) {

  QString response = "z";
  int timeOut = 500;

  QByteArray data = message.toLocal8Bit();
  serial.write(data);

  if (serial.waitForBytesWritten(timeOut)) {
    // read response
    if (serial.waitForReadyRead(timeOut)) {
        QByteArray responseData = serial.readAll();
        while (serial.waitForReadyRead(10))
            responseData += serial.readAll();

        response = QString(responseData);

    } else {
        qDebug() << "Wait read response timeout";
    }
  } else {
      qDebug() << "Wait write request timeout %1";
  }

  return response;
}

