#include "updatepacket.h"

UpdatePacket::UpdatePacket(float Target, float Temp, float Time, bool Relay, QList<float> MeasuredData) {

  target = Target;
  temp   = Temp;
  time   = Time;
  relay  = Relay;
  measuredData = MeasuredData;
}

float UpdatePacket::getTarget() const
{
  return target;
}
float UpdatePacket::getTemp() const
{
  return temp;
}
float UpdatePacket::getTime() const
{
  return time;
}
bool UpdatePacket::getRelay() const
{
  return relay;
}
QList<float> UpdatePacket::getMeasuredData() const
{
  return measuredData;
}








