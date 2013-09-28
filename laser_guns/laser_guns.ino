int laserLightLeftOutPin = 8;
int laserLightRightOutPin = 9;

volatile int state = LOW;
long debouncing_time = 250; //Debouncing Time in Milliseconds

volatile unsigned long lastMicrosLeft;
volatile unsigned long lastMicrosRight;

int laserLeftMidiNote = 0x2E;
int laserRightMidiNote = 0x2F;

void setup() {
  Serial.begin(31250);
  sendNoteOn(laserLeftMidiNote);
  sendNoteOn(laserRightMidiNote);
  pinMode(laserLightLeftOutPin, OUTPUT);
  pinMode(laserLightRightOutPin, OUTPUT);
  attachInterrupt(0, debounceInterruptLeft, RISING);
  attachInterrupt(1, debounceInterruptRight, RISING);
}

void loop() {
  //nothing yet
  
}

void debounceInterruptLeft() {
  if((long)(micros() - lastMicrosLeft) >= debouncing_time * 1000) {
    playLaser(laserLeftMidiNote);
    turnOnLaser(laserLightLeftOutPin);
    lastMicrosLeft = micros();
  }
}

void debounceInterruptRight() {
  if((long)(micros() - lastMicrosRight) >= debouncing_time * 1000) {
    playLaser(laserRightMidiNote);
    turnOnLaser(laserLightRightOutPin);
    lastMicrosRight = micros();
  }
}

void turnOnLaser(int laserPin) {
  digitalWrite(laserPin,HIGH);
  delay(3000);
  digitalWrite(laserPin,LOW);
}

void playLaser(int note) {
  sendNoteOn(note);
  sendNoteOff(note); 
}

void sendNoteOn(int note) {
  // Channel: 0x90, Note (B1flat): 0x2E, Velocity: 0x7E 
  // send note ON
  Serial.write(0x90);
  Serial.write(note);
  Serial.write(0x7E);  
}

void sendNoteOff(int note) {
   // send a note OFF
  Serial.write(0x80);
  Serial.write(note);
  Serial.write(0x00); 
}

