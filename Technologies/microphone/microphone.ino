/* 
 *  
 */
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

 int analogPin = 4;
 int val = 0;

void loop() {
  val = analogRead(analogPin);
  //Serial.print("Alcohol level = ");
  Serial.println(val);
  delay(50);
  //Serial.println("*C");
}

