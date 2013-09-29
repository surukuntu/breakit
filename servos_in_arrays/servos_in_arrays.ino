#include <Servo.h>

Servo servo0, servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8, servo9, servo10, servo11;

// Odd number indexes will be for 1 player, even number index for the other
int photoTransistorPins[12] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
// Servo indexes 0-3 are up-down servos
// Servo indexes 4-11 are left-right servos
Servo servos[12] = {servo0, servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8, servo9, servo10, servo11};

int servoAngles[12];
boolean isHit;

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
    //delay(10);
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
  if(index == 11) {
    Serial.println(transistorVoltage);
  }  
  if(transistorVoltage > 2) {
    Serial.println("hit");
    photoTransistorHit[index] = true;
    timePhotoHit[index] = millis();   
     isHit=true; 
  }  
}

void setNextAngle(int index) {
  //Serial.print("setNextAngle index: ");
  //Serial.println(index);
  //Serial.print("photoTransistorHit: ");
  //Serial.println(photoTransistorHit[index]);

  Serial.println(index);
  // determine if it should be moving
  if(photoTransistorHit[index]) {
    Serial.println("Knows it's hit");
    return;       
  }
  
  int maxAngle = maxServoAngle;
  if(index<=3){
    maxAngle = maxUpDownServoAngle;
  }
   
  if(servoAngles[index] == maxAngle || servoAngles[index] == 0){
      //Serial.println("Switching direction");
      servoDirections[index] =  servoDirections[index] * -1; // flip direction (1 or -1)
  }
  //Serial.print("servoDirections[index]: ");
  //Serial.println(servoDirections[index]);
  servoAngles[index] += servoDirections[index];
  
  //Serial.print("servoAngles: ");
  //Serial.println(servoAngles[index]);
  servos[index].write(servoAngles[index]);
  
  //Serial.print("servos[index]");
  if(index == 11){
    //Serial.println(servos[index].read());
  }
    
}
