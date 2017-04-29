/*
 * brown is gnd
 * red is vcc
 * orange is signal which goes to d8
 */

#include <Servo.h>

Servo servo;
int angle = 10;

void setup() {
  Serial.begin(9600);
  servo.attach(8);
  servo.write(90);
}


void loop() 
{ 
  if(Serial.available()>0){
    angle = Serial.parseInt();
    if (angle>0) servo.write(angle);
  }
 // scan from 0 to 180 degrees
 /* for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  }*/ 
} 
