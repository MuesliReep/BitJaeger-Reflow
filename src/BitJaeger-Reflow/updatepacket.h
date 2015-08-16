#ifndef UPDATEPACKET_H
#define UPDATEPACKET_H

#include <QString>
#include <QList>
#include <QMetaType>

class UpdatePacket{

public:

  UpdatePacket(){}

  UpdatePacket( float Target, float Temp, float Time, bool Relay, QList <float>MeasuredData );

  float getTarget() const;

  float getTemp() const;

  float getTime() const;

  bool getRelay() const;

  QList<float> getMeasuredData() const;

private:
  float target;
  float temp;
  float time;
  bool relay;
  QList <float>measuredData;
};

Q_DECLARE_METATYPE(UpdatePacket);

#endif // UPDATEPACKET_H
