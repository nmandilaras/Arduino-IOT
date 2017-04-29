/* 
 *  https://www.sparkfun.com/datasheets/Sensors/MQ-3.pdf
 *  https://www.youtube.com/watch?v=x0ob4BuTr0E
 *  vcc to vcc 
 *  gnd to gnd 
 *  ad to analog pin
 */
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

 int analogPin = 0;
 int val = 0;

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

  val = analogRead(analogPin);
  Serial.print("V2 = ");
  Serial.println(val);
}

