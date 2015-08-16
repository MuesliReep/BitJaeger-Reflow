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

private:
  void loadDefaultConfig();

  QString profileFileName;

  float P;
  float I;
  float D;
  float sampleRate;
  float windUpPercent;
};

#endif // CONFIG_H
