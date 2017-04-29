/* http://www.electroschematics.com/9540/arduino-fan-speed-controlled-temperature/
 *  Read input from Serial and writes accordingly a motor
 *  
 circuit:
 * fork from fan  
 * NPN transistor 
 * 220 ohm resistor // maybe should be 1K
 * 2 push buttons
 * one for menu selection 
 
 * Extension decreace brightness in 15 seconds
 * Extension include also alarm clock
 * IoT adjustment
 */
 
#include <LiquidCrystal.h>
#include "LowPower.h"

LiquidCrystal lcd(12, 11, 6, 5, 4, 3); 
const int buttonPin = 8;     // menu pushbutton pin 
const int tempPin = A0;      // temperature value 
const int humiPin = A1;      // humidity sensor
const int pResistor = A2;    // photo - R
const int rainPin = A3;      // rain drops sensor 
const int backlight = 13 ;   // control backlight 

int num = 0;                 // menu button index 
int buttonState = 0;         // state of menu button 
float temperature = 0;       // temperature value
float humidity = 0;            // value of humidity
float brightness = 0;          // value of brightness
float rain = 0;                // value of rain drops
long timer = 0;              // keeps time from last pushbutton operation 

void wakeUp(){
  reset();                   // ATTENTION !! excecuted with ATTACH ??
  buttonWasPressed();        // Interupt doesn't take care of button bounching
}

void setup() 
{ 
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(backlight,OUTPUT);
  digitalWrite(backlight,HIGH);
} 
  
void loop() {

    if(timer>60000){
      attachInterrupt(digitalPinToInterrupt(2),wakeUp,RISING);      // zero is used for interrupt in pin 2 
      printInScreen("Time to Sleep","B0 to Reset");       
      delay(3000);
      digitalWrite(backlight,LOW);      
      lcd.noDisplay();;            
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      detachInterrupt(digitalPinToInterrupt(2));                    // we disable interrupts cause we need the button for other operations   
    }
    
   if (buttonWasPressed()){ 
    num++;
    num=num%2;
  }
  
  switch (num){
    case 0:
      temperature = analogRead(tempPin);
      temperature = (5.0*temperature*100.0)/1024;      
      lcd.setCursor(0,0); 
      lcd.print("Temperature ");
      lcd.print(temperature);
      lcd.print("C");
      humidity = analogRead(humiPin)* 1.0 /1024;
      // humidity = ;              pending ....      
      lcd.setCursor(0,1);      
      lcd.print("Humidity ");
      lcd.print(humidity); 
      lcd.print("%");         
      break;
      
    case 1:
      brightness = analogRead(pResistor)* 1.0 /1024;    
      lcd.setCursor(0,0); 
      lcd.print("Brightness ");
      lcd.print(brightness);
      lcd.print("%");
      rain = analogRead(rainPin)* 1.0 /1024;  // na ginei pososto      
      lcd.setCursor(0,1);      
      lcd.print("Rain Drops ");
      lcd.print(rain); 
      lcd.print("%");
      break;     
  }  
  delay(1);
  timer +=1;
}

void reset()
{
    num = 0;                          // menu button index 
    timer = 0;
    lcd.display();
    digitalWrite(backlight,HIGH); 
    lcd.clear();     
}

bool buttonWasPressed(){
      buttonState = digitalRead(buttonPin);                                                // read the state of the pushbutton value:  
      if (buttonState==HIGH){
         while (buttonState==HIGH) buttonState = digitalRead(buttonPin);                   // we deal with button bouncing 
         timer = 0;                                                                        // a button was pressed timer reset                              
         return true; 
      }
      return false;
}

void printInScreen(char *str0, char *str1){
      lcd.clear();
      lcd.print(str0);
      lcd.setCursor(0,1);      
      lcd.print(str1);    
}
