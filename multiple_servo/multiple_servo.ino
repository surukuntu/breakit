#include <Servo.h>

Servo myservo;
Servo myservo1;

int sensorPin = A0; // select the input pin for the potentiometer
int transistorPin = A1;
int transistorPin1 = A2;
int potPin = 13;
int potPin1=12;
int ledPin = 22; // select the pin for the LED
int ledPin1 = 25;
int potAngle = 0;
int angle = 0;
boolean servoShouldRun = true;

int sensorValue = 0;  // variable to store the value coming from the sensor
int transistorValue = 0;
int transistorValue1=0;

void setup() {
  Serial.begin(9600);
  
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT); 
  pinMode(ledPin1,OUTPUT); 
  myservo.attach(13);
  myservo1.attach(12);
 
 }

void loop() {
  if(angle>100){
    angle = 0;
  }
  angle++;
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  //Serial.println(sensorValue);  

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // resister value: 3.3K ohms
  float voltage = sensorValue * (5.0 / 1023.0);
  
  transistorValue = analogRead(transistorPin);
  transistorValue1 = analogRead(transistorPin);
  float transistorVoltage = transistorValue * (5.0 / 1023.0);
  float transistorVoltage1 = transistorValue1 * (5.0 / 1023.0);
  //Serial.println(transistorVoltage);
  //Serial.println(transistorVoltage1);
  //Serial.println(servoShouldRun);
  
  if(servoShouldRun && transistorVoltage<=2 && transistorVoltage1<=2){
    myservo.write(angle);
     myservo1.write(angle);
    delay(60);
  }else{
      servoShouldRun = false;
  }
        
  potAngle = map(sensorValue, 0, 1023, 0, 179);
  
  // turn the ledPin on
  if(voltage > 3){
    digitalWrite(ledPin, HIGH);  
    digitalWrite(ledPin1, HIGH);
  }else{
    //turn the ledPin off:        
    digitalWrite(ledPin, LOW);   
    digitalWrite(ledPin1, LOW);
  }
}
