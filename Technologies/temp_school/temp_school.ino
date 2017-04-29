int tempPin=0,reading;
float temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading=analogRead(tempPin);
  temp=(5.0*reading*100.0)/1024;
  Serial.print("Temprature: ");
  Serial.print(temp-293);
  Serial.println("C");
 // Serial.println();
  delay(1000);
}
