#include "program.h"

Program::Program(MainWindow *W) {

  w = W;
}

void Program::startProgram() {

  time = 0;

  // Load config
  c.loadConfig();

  // Initialise oven connection
  oven = new OvenController(&c);
  if(!oven->initialise()) {

    qDebug() << "Could not initiate communication";
    return;
  }

  // Create PID controller
  pid = PID(&c);
  pid.initialise();

  // Create & connect timer
  timer = new QTimer(this);
  connect(timer,  SIGNAL(timeout()), this, SLOT(updateTick()));
  timer->start((1 / c.getSampleRate()) * 1000);
}

void Program::loadProfile() {

  // Load profile
  p.loadProfile(c.getProfileFileName());

  // Update UI
  emit updateProfile(p.getProfileName(), createProfileData());
}

void Program::stopProgram() {

  timer->stop();
  delete timer;
}

void Program::run() {

  loadProfile();
}

void Program::updateTick() {

  time++; // Add a second to the time // TODO: should be from samplerate

  // Get new data
  float temp = oven->getTemp();
  measuredData.append(temp);

  // Update PID
  float target = p.getTemp((float)time);
  bool heating = pid.update(target, temp);

  // Save to log
  log.append(); // TODO

  // Set relay state to oven controller
  oven->setHeating(heating);

  // Update UI
  UpdatePacket packet(target, temp, time, heating, measuredData);
  emit updateUI(packet);
}

QList<float> Program::createProfileData() {

  //float resolution = 1;  // TODO: this should be in the config

  QList<float> profileData;
  for(int i = 0; i < p.getTotalTime(); i++) {

    profileData.append(p.getTemp((float)i));
  }

  return profileData;
}
