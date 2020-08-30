#include <Servo.h> 

Servo myservo;
int pos = 0;  
int i =0;
void setup() 
{ 
   Serial.begin(9600);
 // pinMode(2, OUTPUT);
  pinMode(5,INPUT);
 
  digitalWrite(5,LOW);
  //digitalWrite(2,HIGH);
  //myservo.write(0);
 
 delay(150);
} 

void loop() {
  
   //Serial.print(myservo.read());
 
    Serial.print(digitalRead(5));
  if(digitalRead(5)){
    i++;
    myservo.attach(9);
    //myservo.writeMicroseconds(1000);
    myservo.write(0);
    delay(1000);
    myservo.detach();
  }
  else{
    //myservo.write(0);
  }
  //
}

    /*
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    pos++; 
    // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
