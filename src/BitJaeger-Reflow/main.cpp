#include "mainwindow.h"
#include <QApplication>
#include <QObject>

#include "updatepacket.h"
#include "program.h"

int main(int argc, char *argv[])
{

  qRegisterMetaType<UpdatePacket>();
  qRegisterMetaType<QList<float> >("QList<float>");

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  Program *p = new Program(&w);


  // Connect UI & Program
  QObject::connect(&w, SIGNAL(startProgram()), p, SLOT(startProgram()));
  QObject::connect(&w, SIGNAL(stopProgram()),  p, SLOT(stopProgram()));
  QObject::connect(p,  SIGNAL(updateUI(UpdatePacket)), &w, SLOT(updateUI(UpdatePacket)));
  QObject::connect(p,  SIGNAL(updateProfile(QString, QList<float>)), &w, SLOT(updateProfile(QString, QList<float>)));
  QObject::connect(p,  SIGNAL(error(QString)), &w, SLOT(error(QString)));

  p->start();

  return a.exec();
}
