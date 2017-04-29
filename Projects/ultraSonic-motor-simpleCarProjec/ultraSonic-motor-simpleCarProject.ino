//Libraries
#include "Ultrasonic.h"
#include <IRremote.h>

//Constants
#define centerButton 45973631
#define bottomButton 45981791

//Variables
int motorPin = 5;  // pin for trigger the transistor
int flag=0;
int IRpin = 7;  // pin for the IR sensor
int LED = 13;    // LED pin  
int distance;    // distance that ultrasonic calculate
boolean LEDon = true; // initializing LEDon as true

IRrecv irrecv(IRpin);
decode_results results;  
Ultrasonic ultrasonic(A0,A1); //Define pins ultrasonic(trig,echo)



void setup() {
  pinMode(motorPin, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{   

  distance = ultrasonic.Ranging(CM);   //Use 'CM' for centimeters or 'INC' for inches
  // Serial.print("Object found at: ");   //Print distance...
  //Serial.print(distance);
  //Serial.println("cm");
  
  int val=190;
  int speed =255; // map(distance,0,2900,120,255);
  
  if (irrecv.decode(&results)){
    Serial.println(results.value, DEC); // Print the Serial 'results.value'
    irrecv.resume();   // Receive the next value
  }
  
  if (distance<20) analogWrite(motorPin,0);
  else if (distance<40 && flag==1)analogWrite(motorPin,val);
    
  if (results.value == centerButton){  // change zero to your IR remote button number
    
       if (LEDon == true) {  // is LEDon equal to true? 
           LEDon = false;   
           digitalWrite(LED, HIGH);
           analogWrite(motorPin,speed);
           flag=1;
           delay(5);      // keeps the transistion smooth  
        }
        else{
            LEDon = true;
            digitalWrite(LED, LOW);
            analogWrite(motorPin,0 );
            flag=0;
            delay(5); 
          }    
     }
    if (results.value == bottomButton){  // change zero to your IR remote button number
       
          if (LEDon == false) {  // is LEDon equal to true? 
            LEDon = true; 
            speed=val;  
            digitalWrite(LED, HIGH);
            analogWrite(motorPin,speed );
            delay(5);      // keeps the transistion smooth  
         }
         else{
            LEDon = false;
            digitalWrite(LED, LOW);
            analogWrite(motorPin,0 );
            delay(5); 
          }    
     
}
results.value =0;
}
