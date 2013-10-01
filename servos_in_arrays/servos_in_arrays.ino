#include <Servo.h>

Servo servo0, servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8, servo9, servo10, servo11;

// Indexes 0-5 are for player 1, indexes 6-11 are for player 2

int photoTransistorPins[12] = {A11, A10, A9, A8, A7, A6, A5, A4, A3, A2, A1, A0};

// Servo indexes 2, 4, 6, and 11 are up-down servos
// All other servo indexes are left-right servos
Servo servos[12] = {servo0, servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8, servo9, servo10, servo11};

int servoAngles[12];
int servoDirections[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int upDownServoTime[4];

boolean photoTransistorHit[12];
unsigned long timePhotoHit[12]; 

// constants
const int photoTransisterThreshold = 2;
const int startingAngle = 30;
const int maxServoAngle = 90;
// not being used unless needs adjusting, all servos have the same angle
//const int maxUpDownServoAngle = 90;


void setup() {
  Serial.begin(9600);
  
  // assign servo output pins, an set starting position
  int i = 0;
  for(i = 0; i < 12; i++) {
    int servoPin = i + 2;
    Serial.print("servoPin");
    Serial.println(servoPin);
    servos[i].attach(servoPin);
    servoAngles[i] = startingAngle;
    servos[i].write(startingAngle);
  }
  
}

void loop() {
  int i = 0;
  for(i = 0; i < 12; i++) {
    delay(5);
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
  if(index == 2) {
    Serial.println(transistorVoltage);
  }
  if(transistorVoltage > 2) {
    //Serial.println("hit");
    photoTransistorHit[index] = true;
    timePhotoHit[index] = millis();   
  }  
}

void setNextAngle(int index) {
  // determine if it should be moving
  if(photoTransistorHit[index]) {
    //Serial.print("Knows it's hit ");
    //Serial.println(index);
    return;       
  }
  
  int maxAngle = maxServoAngle;
  //if(index == 11 || index == 6 || index == 4 || index == 2){
  //  maxAngle = maxUpDownServoAngle;
  //}
   
  if(servoAngles[index] == maxAngle || servoAngles[index] == 15){
      servoDirections[index] =  servoDirections[index] * -1; // flip direction (1 or -1)
  }

  servoAngles[index] += servoDirections[index];
  servos[index].write(servoAngles[index]);    
}
