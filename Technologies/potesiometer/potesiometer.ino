/* https://www.arduino.cc/en/Tutorial/AnalogReadSerial
 * 
 * According to potesiometer's value it lights a led
 * 
 */
 
int pin=0; // read potesiometer midle pin from A0
int led=6;

void setup() {
    Serial.begin(9600);
    pinMode(led,OUTPUT);
}

void loop() {

   int val = map(analogRead(pin),0,1023,0,255); // read and map the value
   Serial.println(val);
   analogWrite(led,val); // light the led with the value measured
   delay(50);
}
   
