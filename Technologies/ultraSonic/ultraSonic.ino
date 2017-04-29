/*https://www.google.gr/search?q=how+to+connect+ultrasonic+sensor+arduino+analog&domains=http://playground.arduino.cc&biw=1440&bih=799&tbm=isch&imgil=JmwChtBo54wSDM%253A%253BJ3B_IjCAYG0JvM%253Bhttp%25253A%25252F%25252Farduino.sundh.com%25252F&source=iu&pf=m&fir=JmwChtBo54wSDM%253A%252CJ3B_IjCAYG0JvM%252C_&usg=__OewENTA8FTiKf-Qcznw_KaIvXiQ%3D&ved=0ahUKEwiDpqqf2ZXMAhXEXCwKHdxkARMQyjcIPQ&ei=uIQTV4PqJ8S5sQHcyYWYAQ#imgrc=9iEbzrvhA85UwM%3A
 * 
 * In this script trig and echo pins are attached correspondigly at Analog 0 and Analog 1 (A0 -A1)
 */
//Libraries
#include "Ultrasonic.h"

//Define pins ultrasonic(trig,echo)
Ultrasonic ultrasonic(A0,A1);

//Variables
int distance,led=7;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop()
{ 
  digitalWrite(led,LOW);
  distance = ultrasonic.Ranging('CM'); //Use 'CM' for centimeters or 'INC' for inches
  //Print distance...
  Serial.print("Object found at: ");
  Serial.print(distance);
  Serial.println("cm");  
  if (distance<10) digitalWrite(led,HIGH);
  delay(1000);
}
