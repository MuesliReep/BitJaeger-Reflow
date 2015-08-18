#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setupPlot();

  connect(ui->pushButtonStart, SIGNAL(pressed()), this, SLOT(startStopButtonPressed()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setupPlot() {

  QColor red(255,0,0);
  QColor green(0,255,0);
  QColor yellow(255,255,0);
  QColor blue(0,0,255);
  QColor black(0,0,0);

  // Set initial ranges, these are updated when new data arrives
  ui->temperaturePlot->xAxis->setRange(0, 1000);
  ui->temperaturePlot->yAxis->setRange(0, 1000);

  ui->temperaturePlot->setBackground(black);

  // Set axis colours
  ui->temperaturePlot->xAxis->setBasePen(QPen(yellow, 1));
  ui->temperaturePlot->yAxis->setBasePen(QPen(yellow, 1));
  ui->temperaturePlot->xAxis->setTickPen(QPen(yellow, 1));
  ui->temperaturePlot->yAxis->setTickPen(QPen(yellow, 1));
  ui->temperaturePlot->xAxis->setSubTickPen(QPen(yellow, 1));
  ui->temperaturePlot->yAxis->setSubTickPen(QPen(yellow, 1));
  ui->temperaturePlot->xAxis->setTickLabelColor(yellow);
  ui->temperaturePlot->yAxis->setTickLabelColor(yellow);
  ui->temperaturePlot->xAxis->grid()->setPen(QPen(yellow, 1, Qt::DotLine));
  ui->temperaturePlot->yAxis->grid()->setPen(QPen(yellow, 1, Qt::DotLine));

  // Add graphs
  profileData =  ui->temperaturePlot->addGraph(ui->temperaturePlot->xAxis, ui->temperaturePlot->yAxis);
  measuredData = ui->temperaturePlot->addGraph(ui->temperaturePlot->xAxis, ui->temperaturePlot->yAxis);

  profileData->setPen(QPen(green, 2));
  measuredData->setPen(QPen(red, 2));

  // Add time indicator line
  timeIndicator = new QCPItemLine(ui->temperaturePlot);
  timeIndicator->setPen(QPen(yellow, 1));
  ui->temperaturePlot->addItem(timeIndicator);

  timeIndicator->start->setCoords(30,0);
  timeIndicator->end->setCoords(30,300);

  ui->temperaturePlot->replot();
}

void MainWindow::startStopButtonPressed() {

  emit startProgram();
}

void MainWindow::updateProfile(QString profileName, QList<float> profilePoints) {

  // Set profile name
  ui->labelProfileName->setText(profileName);

  // Set profile plot
  profileData->clearData();

  float key = 0;

  for(int i = 0; i < profilePoints.size(); i++) {

    key = (float)i;

    profileData->addData(key, profilePoints[i]);
  }

  scaleTempPlot(profilePoints);

  ui->temperaturePlot->replot();
}

void MainWindow::error(QString error)
{

}

void MainWindow::scaleTempPlot(QList<float> plotPoints) {

  int maxTime = plotPoints.size();
  float maxTemp = 0.0;

  for(int i = 0; i < maxTime; i++) {

    if (plotPoints[i] > maxTemp)
      maxTemp = plotPoints[i];
  }

  ui->temperaturePlot->xAxis->setRange(0, maxTime);
  ui->temperaturePlot->yAxis->setRange(0, maxTemp);
}

void MainWindow::updateUI(UpdatePacket packet) {

  // Set new values to labels
  ui->labelTargetValue->setText(QString::number(packet.getTarget()) + "°C");
  ui->labelTempValue->setText(QString::number(packet.getTemp()) + "°C");
  ui->labelTimeValue->setText(QString::number(packet.getTime()));
  ui->labelHeatValue->setText(packet.getRelay() ? "ON" : "OFF");

  // Update time line indicator
  timeIndicator->start->setCoords(packet.getTime(),0);
  timeIndicator->end->setCoords(packet.getTime(),300);

  // Plot measured temperature
  measuredData->clearData();

  float key = 0.0;

  for(int i = 0; i < packet.getMeasuredData().size(); i++) {

    key = (float)i;

    measuredData->addData(key, packet.getMeasuredData()[i]);
  }

  ui->temperaturePlot->replot();
}

