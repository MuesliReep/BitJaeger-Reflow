#ifndef CONFIG_H
#define CONFIG_H

#include "QString"

class Config
{
public:
  Config();

  bool loadConfig();
  void saveConfig();

  QString getProfileFileName();

  float getP() const;
  float getI() const;
  float getD() const;
  float getSampleRate() const;
  float getWindUpPercent() const;

  QString getSerialPort() const;

  int getBaudRate() const;

private:
  void loadDefaultConfig();

  QString profileFileName;

  float P;
  float I;
  float D;
  float sampleRate;
  float windUpPercent;

  QString serialPort;
  int baudRate;
};

#endif // CONFIG_H
