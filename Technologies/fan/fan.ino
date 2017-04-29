/* http://www.electroschematics.com/9540/arduino-fan-speed-controlled-temperature/
 *  Read input from Serial and writes accordingly a motor

 circuit: 
 * fan on pin 5
 * NPN transistor 
 * 220 ohm resistor
 */

int motorPin = 11;
 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{  
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed > 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
    }
  }
} 