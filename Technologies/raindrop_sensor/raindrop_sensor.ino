void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
}
int analogPin = 5;

void loop() {
    // read the input on analog pin 0:
    int sensorValue = analogRead(analogPin); 
    Serial.println(sensorValue);
    delay(500);
}
