#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>

#include "qcustomplot.h"
#include "updatepacket.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QCPGraph *profileData;
  QCPGraph *measuredData;
  QCPItemLine *timeIndicator;

  void setupPlot();

  void updateMeasuredData(float dataPoint);
  void scaleTempPlot(QList<float> plotPoints);

public slots:
  void updateUI(UpdatePacket packet);
  void updateProfile(QString profileName, QList<float> profilePoints);
  void error(QString error);

private slots:
  void startStopButtonPressed();

signals:
  void startProgram();
  void stopProgram();
};

#endif // MAINWINDOW_H
