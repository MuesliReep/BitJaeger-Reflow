#ifndef PROGRAM_H
#define PROGRAM_H

#include <QThread>
#include <QObject>
#include <QTimer>

#include "mainwindow.h"
#include "profile.h"
#include "config.h"
#include "pid.h"
#include "updatepacket.h"
#include "ovencontroller.h"
#include "logging.h"

class Program : public QThread {

  Q_OBJECT

public:
  Program(MainWindow *W);

  void run();

private:
  MainWindow *w;
  Profile p;
  Config c;
  PID pid;
  OvenController *oven;
  Logging log;
  QTimer *timer;

  int time;

  QList<float> measuredData;

  QList<float> createProfileData();
  void loadProfile();

public slots:
  void startProgram();
  void stopProgram();

private slots:
  void updateTick();

signals:
  void updateUI(UpdatePacket packet);
  void updateProfile(QString profileName, QList<float> profileData);
  void error(QString errorString);
};

#endif // PROGRAM_H
