#include <Servo.h>

Servo servo0, servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8, servo9, servo10, servo11;

// Odd number indexes will be for 1 player, even number index for the other
int photoTransistorPins[12] = {A11, A10, A9, A8, A7, A6, A5, A4, A3, A2, A1, A0};

// Servo indexes 0-3 are up-down servos
// Servo indexes 4-11 are left-right servos
Servo servos[12] = {servo0, servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8, servo9, servo10, servo11};

int servoAngles[12];
int servoDirections[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int upDownServoTime[4];

boolean photoTransistorHit[12];
unsigned long timePhotoHit[12]; 

// constants
const int photoTransisterThreshold = 2;
const unsigned long millisToStayStill = 5000;
const int maxServoAngle = 120;
const int maxUpDownServoAngle = 90;


void setup() {
  Serial.begin(9600);
  
  // assign servo output pins, an set starting position
  int i = 0;
  for(i = 0; i < 12; i++) {
    int servoPin = i + 2;
    Serial.print("servoPin");
    Serial.println(servoPin);
    servos[i].attach(servoPin);
    servos[i].write(0);
  }
  
}

void loop() {
  int i = 0;
  for(i = 0; i < 12; i++) {
    delay(10);
    setPhotoTransitorHitStatus(i);
    setNextAngle(i);    
  }
   
}

void setPhotoTransitorHitStatus(int index) {
  if(photoTransistorHit[index]) {
    return;
  }
 
  int transistorValue = analogRead(photoTransistorPins[index]);
  float transistorVoltage = transistorValue * (5.0 / 1023.0); 
  if(transistorVoltage > 2) {
    Serial.println("hit");
    photoTransistorHit[index] = true;
    timePhotoHit[index] = millis();   
  }  
}

void setNextAngle(int index) {
  //Serial.println(index);
  // determine if it should be moving
  if(photoTransistorHit[index]) {
    Serial.print("Knows it's hit ");
    Serial.println(index);
    return;       
  }
  
  int maxAngle = maxServoAngle;
  if(index == 11 || index == 6 || index == 4 || index == 2){
    maxAngle = maxUpDownServoAngle;
  }
   
  if(servoAngles[index] == maxAngle || servoAngles[index] == 0){
      servoDirections[index] =  servoDirections[index] * -1; // flip direction (1 or -1)
  }

  servoAngles[index] += servoDirections[index];
  servos[index].write(servoAngles[index]);    
}
