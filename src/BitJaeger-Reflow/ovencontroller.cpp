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

  qDebug() << "Sending temp request";
  QString response = sendMessage("b");

  if(response.contains("b")) {

    QStringList l = response.split("b");
    temp = l[0].toFloat();
    qDebug() << "Received temp: " << temp;
  } else {

    qDebug() << "Bad response from temperature request: " << response;
  }

  return temp;
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

  // Wait for the arduino to initialise
  QThread::sleep(4); // Seconds

  // Send test message & wait a little
  sendMessage("qqqqqqqqqqqqqqqqqq");
  QThread::msleep(100);
  QString response = sendMessage("a", 4000);

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

QString OvenController::sendMessage(QString message, int timeOut, bool waitResponse) {

  QString response = "x";

  serial.clear();

  QByteArray data = message.toLocal8Bit();
  qDebug() << "Bytes written: " << serial.write(data);
  serial.flush();

//  if (serial.waitForBytesWritten(timeOut)) {
//    // read response
//    if (serial.waitForReadyRead(timeOut)) {
//        QByteArray responseData = serial.readAll();
//        while (serial.waitForReadyRead(500))
//            responseData += serial.readAll();

//        response = QString(responseData);

//    } else {
//        //qDebug() << "Read timeout";
//    }
//  } else {
//      //qDebug() << "Write timeout";
//  }

  if(serial.waitForBytesWritten(6000)) { //timeOut
    qDebug() << "Write timeout";
  } else {
    qDebug() << "Message sent";
  }

  while(!serial.canReadLine()) {}

  QByteArray responseData = serial.readAll();
  response = QString(responseData);

  return response;
}

