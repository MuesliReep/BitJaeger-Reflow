#ifndef PROFILE_H
#define PROFILE_H


#include <QString>
#include <QList>
#include <QDebug>

class DataPoint {

public:
  DataPoint() { time = 0; temp = 0; }
  DataPoint(float Time, float Temp) {
    time = Time;
    temp = Temp;
  }

  float getTime() { return time; }
  float getTemp() { return temp; }

private:
  float time;
  float temp;

};

class Profile
{
public:
  Profile();

  float getTemp(float time);
  bool loadProfile(QString fileName, bool loadDefault = true);

  QString getProfileName() const;
  float getTotalTime();

private:
  QList <DataPoint>dataPoints;
  QString profileName;

  void loadDefaultProfile();
  void saveProfile(QString fileName);
};

#endif // PROFILE_H
