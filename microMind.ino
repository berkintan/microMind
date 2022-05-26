#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>

#define LED_PIN 13
#define MZ80_PIN 6   
#define NUM_SENSORS 6

//Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;

// Define an array for holding sensor values.
unsigned int sensorValues[NUM_SENSORS];
unsigned int positionVal = 0;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // --------------------------- Start Of The Calibration -------------------------
  reflectanceSensors.init();
  unsigned long startTime = millis();
  while (millis() - startTime < 5000)  // make the calibration take 10 seconds
  {
    reflectanceSensors.calibrate();
  }
  // ------------------- End Of The Calibration -----------------------
}

unsigned int mostLeftSensor() {
  if (sensorValues[0] < 600)
    return 1;
  else
    return 0;
}

unsigned int leftSensor() {
  if (sensorValues[1] < 600)
    return 1;
  else
    return 0;
}

unsigned int midLeftSensor() {
  if (sensorValues[2] < 600)
    return 1;
  else
    return 0;
}

unsigned int midRightSensor() {
  if (sensorValues[3] < 600)
    return 1;
  else
    return 0;
}

unsigned int rightSensor() {
  if (sensorValues[4] < 600)
    return 1;
  else
    return 0;
}

unsigned int mostRightSensor() {
  if (sensorValues[5] < 600)
    return 1;
  else
    return 0;
}

void turnRight() {
  motors.setSpeeds(100, -100);
}

void turnLeft() {
  motors.setSpeeds(-200, 200);
}

void go() {
  motors.setSpeeds(550, 550);
}

void loop() {
  
  positionVal = reflectanceSensors.readLine(sensorValues);

  if (mostLeftSensor() == 1 || mostRightSensor() == 1) {
    motors.setSpeeds(-225, -225);
    turnRight();
    delay(300);
  } else {
    go();
  }

  
    if(!digitalRead(MZ80_PIN)) {
     go();
    } else {
      turnRight();
    }
    
  }