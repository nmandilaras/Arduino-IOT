int relay = 7;
//int led =13
void setup() {
  //pinMode(led,OUTPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW); // Turns ON Relays 1
  Serial.println("Light ON");
  delay(12000); // Wait 2 seconds
  digitalWrite(relay,HIGH); // Turns Relay Off
  Serial.println("Light OFF");
  delay(12000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
