int previous = 0;
int previous1 = 0;
void setup () {//void setup start
// initialize the serial communication
Serial.begin(9600);
previous=analogRead(A0);
previous1=analogRead(A1);
}//void setup end

void loop () {//void loop start

// read and display first phototransistor
// value on serial monitor

if(analogRead(A0) != previous){
Serial.println(previous);
Serial.println(analogRead(A0));
Serial.print("Difference1 = ");
Serial.println(previous-analogRead(A0));
previous=analogRead(A0);
}
delay(3000);
if(analogRead(A1) != previous1){
Serial.println(previous1);
Serial.println(analogRead(A1));  
Serial.print("Difference2 = ");
Serial.println(previous1-analogRead(A1));
previous1=analogRead(A1);
}



// a short delay
delay(3000);



} //void loop end
