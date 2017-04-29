/* 
 *  
 */
  int pin = 13;
void setup() {
  pinMode(pin,INPUT);
  // put your setup code here, to run once:
    Serial.begin(9600);
}

 int val = 0;

void loop() {
  val = digitalRead(pin);
  //Serial.print("Alcohol level = ");
  Serial.println(val);
  delay(50);
  //Serial.println("*C");
}

