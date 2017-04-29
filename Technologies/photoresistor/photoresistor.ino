/* http://www.instructables.com/id/How-to-use-a-photoresistor-or-photocell-Arduino-Tu/step2/The-Circuit/ 
 *  
 *  Reading photoresistors value we light accordingly a led
 
 circuit:
 *  classic configuration for led
 *  photoresistor connected with a 10kΩ resistor 
 */

int pResistor = A4; // Photoresistor at Arduino analog pin A4
int led=5;       // Led pin at Arduino pin 5
int brightness;

//Variables
int value;          // Store value from photoresistor (0-1023)

void setup(){
 Serial.begin(9600);
 pinMode(led, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A4 pin as an input (optional)
}

void loop(){
  value = analogRead(pResistor);   // read sensor's value
  Serial.println(value/1023.0*100);
  if (value>800) value=820;  // adjust maximum according to given conditions e.g. max here is 820 instead of 1023
  brightness=map(value,170,820,255,0); // mapping
  //analogWrite(led,brightness); // light led accordingly 
  delay(1000);
}
