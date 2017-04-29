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
const int buttonPin0 = 8;    // menu pushbutton pin 
const int buttonPin1 = 2;    // brightness pushbutton pin
const int lampPin = 9;       // transistor base has to be PWM capable 
const int microPin = A0;     // microphone
const int pResistor = A1;    // photo - R 
const int backlight = 13 ;   // control backlight 

int num0 = 0;                // menu button index 
int buttonState0 = 0;        // state of menu button 
int num1 = 0;                // current level of brightness 
int buttonState1 = 0;        // variable for reading the pushbutton status
int val = 0;                 // heat of volume 
bool notInitialised = true;  // flag for printing a message for only one time 
int endIt = 0;               // arranged time for entering sleep mode measured from the begging of times 
bool shmaia = false;         // temporary sleep operation flag 
bool SleepActivated = false; // sleep operation flag 
bool SleepMode = false;      // lock in case of sleep mode 
char *str = "B1 to Start";   // auxilary for strings
int temp = 0;                    // keeps B1 value for normal mode operations  
bool StartFlag = false;      // flag that says if one mode was activated 
long timer = 0;              // keeps time from last pushbutton operation 
bool displayOn = true;       // flag about if we are in power saver mode 
int array[]={0,85,170,255};  // array with values of brightness levels 

void wakeUp(){
  reset();                                    // ATTENTION !! excecuted with ATTACH ??
  buttonWasPressed(buttonPin1,buttonState1);  // Interupt doesn't take care of button bounching
}

void setup() 
{ 
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(lampPin, OUTPUT);
  pinMode(backlight,OUTPUT);
  digitalWrite(backlight,HIGH);
} 
  
void loop() {
  
  if (SleepActivated){
    if(millis()/1000>=endIt){
      attachInterrupt(digitalPinToInterrupt(2),wakeUp,RISING);      // zero is used for interrupt in pin 2 
      printInScreen("Time to Sleep","B1 to Reset");       
      delay(3000);
      digitalWrite(lampPin,LOW);
      digitalWrite(backlight,LOW);      
      lcd.noDisplay();
      SleepMode = true;                                             //seems unnecessary to me !!!!!!          
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      detachInterrupt(digitalPinToInterrupt(2));                    // we disable interrupts cause we need the button for other operations   
    }
  }
  
  if (!SleepMode){
   if (buttonWasPressed(buttonPin0,buttonState0)){ 
    num0++;
    num0=num0%6;
    if (shmaia && num1>0) SleepActivated = true; // to sleep exei dwdei kai me to pathma toy B0 epivevaiwnetai
    notInitialised = true;
    num1=0;
    shmaia = false;
    StartFlag = false;
  }
  
  switch (num0){
    case 0:
      initSrceen("Normal Mode","B1 to Start");
      num1 = temp;  
      analogWrite(lampPin,array[temp]);      
      if (buttonWasPressed(buttonPin1,buttonState1)){
         num1++;
         num1 %= 4;
         switch (num1){
          case 1:
            val = 85; // brightness low    // array implementation ?    
            str = "Brightness low   ";
            break;
          case 2: 
            val = 170; // brightness medium
            str = "Brightness mezzo";         
            break;  
          case 3:
            val = 255; // brightness high
            str = "Brightness high  ";         
            break;
          default:
            val = 0; // lamp off
            str = "Lamp off        ";      
         }
         analogWrite(lampPin,val);            
      }
      lcd.setCursor(0, 1); //colum zero line one      
      lcd.print(str);       
      temp = num1; // we keep brightness value so next time we pass from this mode value stays the same
      break;
      
    case 1:
      initSrceen("Music Mode","B1 to Start");  
      if (checkB1() || StartFlag){                // first checkB1 in order to all modes catch a possible pushbutton operation (mainly useful from returning from displayOff) 
          val = analogRead(microPin);
          val = map(val ,170 , 623 ,0 ,255);
          analogWrite(lampPin,val);
          delay(40);   
          timer+=40;
      }
      break;   
         
   case 2:
    if (!SleepActivated){
      initSrceen("Sleep in","0 minutes");        
      if (buttonWasPressed(buttonPin1,buttonState1)){
         num1++;
         num1=num1%10;
         lcd.setCursor(0,1); 
         lcd.print(num1);
         shmaia=1; 
         endIt=num1*60+millis()/1000;
      }  
    }
    else {
      lcd.setCursor(0,0); 
      lcd.print("Sleep in ");
      int val = endIt-millis()/1000;
      lcd.print(val);
      if (val<100) lcd.print(" ");
      if (val<10) lcd.print(" ");
      lcd.setCursor(0,1);
      lcd.print("B1 to Cancel   ");     
      if (buttonWasPressed(buttonPin1,buttonState1)) reset();    
    }
    break;
    
  case 3:
      initSrceen("Automate Mode","B1 to Start");  
      if (checkB1() || StartFlag){ 
          val = analogRead(pResistor);                    // read sensor's value
          if (val<700) digitalWrite(lampPin,HIGH);        // light on lamp
          else digitalWrite(lampPin,LOW);                 // light off lamp
          delay(100);
          timer+=100;
      }     
      break; 
      
  case 4:
      initSrceen("Random Mode","B1 to Start");
      if(checkB1() || StartFlag){         
      analogWrite(lampPin,random(256));
      val = random(40,200);
      delay(val);
      timer +=val;
      }   
      break;  
      
  case 5:
      initSrceen("Press B1","To Shut down");
      if (buttonWasPressed(buttonPin1,buttonState1)){         
          SleepActivated = true;
          endIt=millis()/1000;
      }   
      break; 
  }  
}
  if (displayOn && timer >= 30000){                                   // power saving mode 
      printInScreen("Power Saver On","Press any Button");
      delay(3000);
      lcd.noDisplay();
      digitalWrite(backlight,LOW);
      displayOn = false;
  } 
  else if (!displayOn && timer < 30000) {
      lcd.display();
      digitalWrite(backlight,HIGH);
      displayOn = true;
      notInitialised = true; 
  }
  delay(1);
  timer +=1;
}

void reset()
{
    num0 = 0;                          // menu button index 
    notInitialised = true;
    shmaia = false;
    SleepActivated = false; 
    SleepMode = false;  
    timer = 0;
    lcd.display();
    digitalWrite(backlight,HIGH); 
    lcd.clear(); 
    analogWrite(lampPin,array[temp]);     
}

bool checkB1(){
   if (buttonWasPressed(buttonPin1,buttonState1)){
      lcd.setCursor(0,1); 
      lcd.print("Activated!!     "); 
      StartFlag = true;
      return true;  
   }
   return false;   
}

void initSrceen(char *str0 , char *str1 ){
      if (notInitialised) {printInScreen(str0,str1); notInitialised = false;}    
}

bool buttonWasPressed(const int buttonPin,int buttonState){
      buttonState = digitalRead(buttonPin);                                                // read the state of the pushbutton value:  
      if (buttonState==HIGH){
         while (buttonState==HIGH) buttonState = digitalRead(buttonPin);                   // we deal with button bouncing 
         timer = 0;                                                                        // a button was pressed timer reset 
         if (!displayOn  ) return false;                                                     // if we return from energy saving mode don't count it as push of a button
         return true; 
      }
      return false;
}

void printInScreen(char *str0, char *str1){
      lcd.clear();
      //lcd.setCursor(0,0);                                                               // not necessary due to clear() command
      lcd.print(str0);
      lcd.setCursor(0,1);      
      lcd.print(str1);    
}
