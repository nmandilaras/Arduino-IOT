/*https://learn.adafruit.com/adafruit-arduino-lesson-13-dc-motors/breadboard-layout
 *  Read input from Serial and writes accordingly a motor

 circuit: 
 * Motor on pin 5
 * 
 */

int motorPin = 5;
 
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
