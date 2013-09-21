#include <Servo.h>

Servo myservo;

int sensorPin = A0;    // select the input pin for the potentiometer
int potPin = 13;
int ledPin = 22; // select the pin for the LED
int potAngle = 0;
int angle = 0;


int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  myservo.attach(13);
 
 }

void loop() {
  if(angle==180){
    angle = 0;
  }
  angle++;
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  //Serial.println(sensorValue);  

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // resister value: 2 
  float voltage = sensorValue * (5.0 / 1023.0);
  
  if(voltage<=2){
    myservo.write(angle);
    delay(15);
  }
        
  potAngle = map(sensorValue, 0, 1023, 0, 179);
  
  // turn the ledPin on
  if(voltage > 2){
    digitalWrite(ledPin, HIGH);  
  }else{
    // turn the ledPin off:        
    digitalWrite(ledPin, LOW);   
  }
}
