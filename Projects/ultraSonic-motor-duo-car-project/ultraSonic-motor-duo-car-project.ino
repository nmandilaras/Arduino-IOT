//Libraries
#include "Ultrasonic.h"
#include <IRremote.h>

//Constants
#define centerButton 45973631
#define bottomButton 45981791
#define leftButton 45940991
#define rightButton 45957311
#define upButton 45983831

//Variables
int leftMotorPin = 5;  // pin for trigger the transistor
int rightMotorPin = 6; // pin for trigger second motor
int flag=0;
int IRpin = 7;  // pin for the IR sensor
int LED = 13;    // LED pin  
int distance;    // distance that ultrasonic calculate
int speed=255,val=190 ;

IRrecv irrecv(IRpin);
decode_results results;  
Ultrasonic ultrasonic(A0,A1); //Define pins ultrasonic(trig,echo)

void rotateLeft(int speedOfRotate, int length){
  digitalWrite(LED, HIGH);
  analogWrite(rightMotorPin, speedOfRotate); //rotates motor
  digitalWrite(leftMotorPin, LOW);    // set the Pin motorPin2 LOW
  delay(length); //waits
  digitalWrite(rightMotorPin, LOW);    // set the Pin motorPin1 LOW
  digitalWrite(LED, LOW);
  delay(2000);  
}

void rotateRight(int speedOfRotate, int length){
  digitalWrite(LED, HIGH);  
  analogWrite(leftMotorPin, speedOfRotate); //rotates motor
  digitalWrite(rightMotorPin, LOW);    // set the Pin rightmotorPin LOW
  delay(length); //waits
  digitalWrite(leftMotorPin, LOW);    // set the Pin leftmotorPin LOW
  digitalWrite(LED, LOW);
  delay(2000);
}

void moveForward (){
      digitalWrite(LED, HIGH);
      analogWrite(leftMotorPin,speed);
      analogWrite(rightMotorPin,speed);           
      flag=1;
      delay(5);      // keeps the transistion smooth  
   }


void immobilize(){
       digitalWrite(LED, LOW);
       analogWrite(leftMotorPin,0 );
       analogWrite(rightMotorPin,0);
       flag=0;
       delay(2000);    
  }  

bool watch_out(){

  distance = ultrasonic.Ranging(CM);   //Use 'CM' for centimeters or 'INC' for inches
  Serial.print("Object found at: ");   //Print distance...
  Serial.print(distance);
  Serial.println("cm");
  if (distance<20) { immobilize(); return true;} 
  else if (distance<40 && flag==1) { analogWrite(leftMotorPin,val); analogWrite(rightMotorPin,val); }
  return false;    
}

void IRemote() {

    if (irrecv.decode(&results)){
    Serial.println(results.value, DEC); // Print the Serial 'results.value'
    irrecv.resume();   // Receive the next value
   }  
}

void aimlessly_wanderer() {

        while (results.value != bottomButton) {
             IRemote();
             while (watch_out()) rotateLeft(255,600);   
             if (flag==0) moveForward();
          //   results.value =0;
          }
        immobilize();
  }
  
void setup() {
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop(){

  IRemote();

  //watch_out();

  if (results.value == upButton)  // change zero to your IR remote button number
            moveForward();
  else if (results.value == leftButton)
            rotateLeft(255,600);
  else if (results.value == rightButton)
            rotateRight(255,600);
  else if (results.value == bottomButton)
            immobilize();          
  else if (results.value == centerButton)
            aimlessly_wanderer();  
                               
  results.value =0;
}
