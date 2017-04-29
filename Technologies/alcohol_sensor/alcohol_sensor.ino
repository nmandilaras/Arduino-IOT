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

 int analogPin = 5;
 int val = 0;

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);

  val = readAlcohol();
  Serial.print("Alcohol level = ");
  Serial.println(val);
  //Serial.println("*C");
}


 int readAlcohol()
 {
  int val = 0;
  int val1;
  int val2;
  int val3; 

  val1 = analogRead(analogPin); 
  delay(10);
  val2 = analogRead(analogPin); 
  delay(10);
  val3 = analogRead(analogPin);  
  val = (val1+val2+val3)/3;
  return val;
 }
