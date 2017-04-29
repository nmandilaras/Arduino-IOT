/*
 * https://www.google.gr/search?q=REceiver+arduino&sa=X&biw=1440&bih=799&tbm=isch&tbo=u&source=univ&ved=0ahUKEwijmZ-V15XMAhWEkywKHWlEBcoQsAQIGQ#imgrc=5kVcpRxrz4NoCM%3A
 Some Sample code of how to use your IR remote
 
 * Lets get started:
 
 The IR sensor's pins are attached to Arduino as so:
 Pin 1 to Vout (pin 11 on Arduino)
 Pin 2 to GND
 Pin 3 to Vcc (+5v from Arduino)

*/
#include <IRremote.h>

#define closeButton 45985871
#define menuButton 46000151
#define centerButton 45973631
#define bottomButton 45981791
#define leftButton 45940991
#define rightButton 45957311
#define upButton 45983831

int IRpin = 7;  // pin for the IR sensor
IRrecv irrecv(IRpin);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)){
    Serial.println(results.value, DEC); // Print the Serial 'results.value'
    irrecv.resume();   // Receive the next value
  }
  if (results.value == centerButton){  // change zero to your IR remote button number

   
     }
   results.value = 0;  
}

