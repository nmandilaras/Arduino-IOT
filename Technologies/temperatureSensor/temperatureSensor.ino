/* http://www.instructables.com/id/ARDUINO-TEMPERATURE-SENSOR-LM35/ */

int val;
int tempPin = 3;
char text[20];
void setup(){
 // analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(tempPin);  // read sensor's value
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;    // final temp
  //float farh = (cel*9)/5 + 32;

  //Serial.print("TEMPRATURE = ");
  dtostrf(cel, 2, 2, text); //dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf)
  Serial.println(text);
  //Serial.println("*C");
  delay(10); // metrhsh ana 10 lepta

/* uncomment this to get temperature in farenhite 
Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();
*/
}

