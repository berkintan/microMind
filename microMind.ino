#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>

#define LED_PIN 13
#define MZ80_PIN 6   
#define NUM_SENSORS 6

//Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;

unsigned int obstacle;
//unsigned int reload = 0xB71B;
unsigned long time;
unsigned long x;


// Define an array for holding sensor values.
unsigned int sensorValues[NUM_SENSORS];
unsigned int positionVal = 0;
void setup() {

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  attachInterrupt(MZ80_PIN, obstacleDetected , RISING); // newly added

/////////////////////////////////TIMER////////////////////

  //TCCR1A = 0;
  //TCCR1B = 0; 
  //OCR1A = reload;
  //TCCR1A = 1<<WGM21 // donno
  //TCCR1B = (1<<CS10) | (1<<CS12); 
  //TIMSK1 = (1<<OCIE1A); 

//////////////////////////////////////////////////////////////


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
  motors.setSpeeds(150, -150); 
}

void turnLeft() {
  motors.setSpeeds(-200, 200);
}

void goBack() {
  motors.setSpeeds(-225, -225);
}

void go() {
  motors.setSpeeds(600, 600); 
}
  
void blinkLED(int obstacleNumber) { 
    for(int i = 0; i <= obstacleNumber; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(600);
      digitalWrite(LED_PIN, LOW);
      delay(600);
  }
}

void obstacleDetected() {
  if(time < 20000) {
    go();
    delay(1);
    incrementObstacleNumber();
    delay(1);
  } else {
    stop();
    delay(1);
    blinkLED(obstacle);
    delay(1);
}
}

void incrementObstacleNumber() {
  obstacle++;
}

  void stop() {
    motors.setSpeeds(0, 0);
  }

void loop() {
  
  time = millis();
  positionVal = reflectanceSensors.readLine(sensorValues);

  if (mostLeftSensor() == 1 || mostRightSensor() == 1 || midLeftSensor() == 1 || midRightSensor() == 1) {
    goBack();
    delay(750);
    turnRight();
    delay(100); 
  } else {
    go();
  }

    if(digitalRead(MZ80_PIN)) {
      turnRight();
       } 

    if(time >= 20000) {
      obstacleDetected();
      delay(500000); // not to run again and again...
    }

      } 

      

    
    
  