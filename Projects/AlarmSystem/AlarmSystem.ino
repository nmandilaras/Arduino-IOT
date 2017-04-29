//#include "LowPower.h"  should be available for acer also

const int interval = 10; // time given in order to press code
const int doorPin = 3;   
int limit = 0 ;
bool doorOpen = false; 
bool firstTime = true;
bool armed = false;
String code = "890A";

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if (armed){ 
      doorOpen = digitalRead(doorPin); // instead of it ardi could go in deep sleep mode monitoring only interrupt in doorPin when Falling it wakes up knowing we have an entry
      if (doorOpen && firstTime ){
          //light sound
          limit = millis()/1000 + interval;
          firstTime = false; 
      }
      else if (codeWasPressed()) reset(); // maybe we can reset when millis is flerting with overflow
      else if (!firstTime && limit < millis()/1000)  // heavy sound hit the buzzer
      delay(40);  // keeping the prosessor with delaying can cause problems with pushButtons
  }
  else if (triggered) armed = true; // instead of it ardi can monitor only interrupt in trigger button and wakes up knowing we are armed !
}

bool codeWasPressed () {
  ; // check keyboard for code  
}

void reset(){
  firstTime = true;
  doorOpen = false;
  armed = false;
}

bool triggered() { // checks if we press activation button
  ; // it has to give a 20 seconds interval before it is armed
    // light sound during this interval
}

