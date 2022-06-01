#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>

#define LED_PIN 13
#define MZ80_PIN 6   
#define NUM_SENSORS 6

//Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;

unsigned int obstacle = 0;
//unsigned int reload = 0xB71B;
unsigned long time;


// Define an array for holding sensor values.
unsigned int sensorValues[NUM_SENSORS];
unsigned int positionVal = 0;
void setup() {

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);


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
  
void blinkLED(int obstacle) { 
    for(int i = 0; i <= obstacle; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(600);
      digitalWrite(LED_PIN, LOW);
  }
}

  void stop() {
    motors.setSpeeds(0, 0);
  }

void loop() {
  
  time = millis();
  positionVal = reflectanceSensors.readLine(sensorValues);

  if (mostLeftSensor() == 1 || mostRightSensor() == 1 || midLeftSensor() == 1 || midRightSensor() == 1) {
    goBack();
    delay(650);
    turnRight();
    delay(1000); // new removed
  } else {
    go();
  }


    if(!digitalRead(MZ80_PIN)) {
      obstacle = obstacle + 1; 
      go();
       } else if(digitalRead(MZ80_PIN)) {
         turnRight();
         if(time > 20000) {
           stop();
           blinkLED(obstacle);
         }
      } 

      }

    
    
  