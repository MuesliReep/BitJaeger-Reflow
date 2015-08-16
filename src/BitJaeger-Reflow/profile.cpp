#include "profile.h"

#include <QFile>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Profile::Profile() {

}

float Profile::getTemp(float time) {

  DataPoint previous;
  DataPoint next;
  float temp = 0.0;

  for(int i = 0; i < dataPoints.size() - 1; i++) {

    if(time == dataPoints[i].getTime()) {
      temp = dataPoints[i].getTemp();
      break;
    }

    if(time > dataPoints[i].getTime() && time < dataPoints[i+1].getTime()) {

      previous = dataPoints[i];
      next     = dataPoints[i+1];

      float dt    = time - previous.getTime();
      float slope = (next.getTemp() - previous.getTemp()) / (next.getTime() - previous.getTime());

      temp = previous.getTemp() + (dt * slope);

      break;
    }
  }

  return temp;
}

bool Profile::loadProfile(QString fileName, bool loadDefault) {

  QFile file(fileName);

  // Check if file exists, if not create default profile
  if(!file.exists()) {

    if(loadDefault) {
      loadDefaultProfile();
      return true;
    }
    else
      return false;
  }

  // Read profile data from file

  dataPoints.clear();

  QJsonDocument json;

  if(file.open(QFile::ReadOnly)) {
    qDebug() << "Loading profile data from " << fileName;

    QJsonParseError error;

    json = QJsonDocument().fromJson(file.readAll(), &error);

    // Check if JSON was correctly parsed
    if (error.error != QJsonParseError::NoError) {

      qDebug() << error.errorString();
      return false;
    }

    // Read JSON values
    QJsonObject object     = json.object();
    QJsonArray profileData = object.value("profileData").toArray();

    profileName = object.value("profileName").toString();

    // Convert the JSON array to a Trade List
    for(int i = 0; i < profileData.size(); i++) {

      // Convert the JSON values
      QJsonObject dataPointObject = profileData[i].toObject();

      float time = dataPointObject.value("time").toDouble();
      float temp = dataPointObject.value("temp").toDouble();

      // Create a trade object from the converted values
      DataPoint dataPoint(time, temp);

      // Append the new trade object to the trade list
      dataPoints.append(dataPoint);
    }
  }

  return true;
}
QString Profile::getProfileName() const
{
  return profileName;
}

float Profile::getTotalTime() {

  return dataPoints[dataPoints.size() - 1].getTime();
}

void Profile::saveProfile(QString fileName) {

  QJsonObject object;
  QJsonArray profileData;

  // Insert the currently stored profile data into the JSON array
  for(int i = 0; i < dataPoints.size(); i++) {

    QJsonObject dataPointObject;
    DataPoint point = dataPoints[i];

    dataPointObject.insert("time", QJsonValue(point.getTime()));
    dataPointObject.insert("temp", QJsonValue(point.getTemp()));

    profileData.append(dataPointObject);
  }

  // Insert the profileData array to the JSON object
  object.insert("profileData", QJsonValue(profileData));
  object.insert("profileName",profileName);

  // Create a JSON document from the newly created JSON object
  QJsonDocument document(object);

  // Save the JSON document to file
  QFile file(fileName);
  file.open(QFile::WriteOnly);
  file.write(document.toJson(QJsonDocument::Indented));
}

void Profile::loadDefaultProfile() {

  QString defaultName = "default.json";

  // Check if default profile exists on disk
  QFile file(defaultName);

  if(file.exists()) {
    loadProfile(defaultName, false);
    return;
  }

  // Default profile does not exist, we need to create one
  profileName = "Default lead free";

  dataPoints.append(DataPoint(0,25));      // Starting temp
  dataPoints.append(DataPoint(90,150));    // Pre Heat
  dataPoints.append(DataPoint(180,217));   // End of soak
  dataPoints.append(DataPoint(225,245));   // Peak temp
  dataPoints.append(DataPoint(270,217));   // End of reflow zone
  dataPoints.append(DataPoint(337.5,25));  // End of profile

  // Save the new default profiel
  saveProfile(defaultName);
}
