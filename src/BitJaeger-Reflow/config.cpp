#include "config.h"

#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

Config::Config()
{

}

bool Config::loadConfig() {

  QFile file("config.json");

  // Check if file exists, if not create default profile
  if(!file.exists()) {
    qDebug() << "Config file not found, loading default config...";
    loadDefaultConfig();
    saveConfig();
    return true;
  }

  // Read config data from file
  QJsonDocument json;

  if(file.open(QFile::ReadOnly)) {
    qDebug() << "Loading config data";

    QJsonParseError error;

    json = QJsonDocument().fromJson(file.readAll(), &error);

    // Check if JSON was correctly parsed
    if (error.error != QJsonParseError::NoError) {

      qDebug() << error.errorString();
      return false;
    }

    // Read JSON values
    QJsonObject object     = json.object();

    P               = object.value("P").toDouble();
    I               = object.value("I").toDouble();
    D               = object.value("D").toDouble();
    sampleRate      = object.value("sampleRate").toDouble();
    windUpPercent   = object.value("windUpPercent").toDouble();
    profileFileName = object.value("profileFileName").toString();
  }

  return true;
}

void Config::saveConfig() {

  QJsonObject object;

  // Insert the config values into the JSON object
  object.insert("P", P);
  object.insert("I", I);
  object.insert("D", D);
  object.insert("sampleRate", sampleRate);
  object.insert("windUpPercent", windUpPercent);
  object.insert("profileFileName", profileFileName);

  // Create a JSON document from the newly created JSON object
  QJsonDocument document(object);

  // Save the JSON document to file
  QFile file("config.json");
  file.open(QFile::WriteOnly);
  file.write(document.toJson(QJsonDocument::Indented));
}

void Config::loadDefaultConfig() {

  P = 10;
  I = 0.5;
  D = 100;

  windUpPercent   = 0.05;
  sampleRate      = 1;
  profileFileName = "default.json";
}

float Config::getP() const
{
  return P;
}
float Config::getI() const
{
  return I;
}
float Config::getD() const
{
  return D;
}
float Config::getSampleRate() const
{
  return sampleRate;
}
float Config::getWindUpPercent() const
{
  return windUpPercent;
}
QString Config::getProfileFileName()
{
  return profileFileName;
}
