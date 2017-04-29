/*
TX -> RX of arduino, no conversion needed as bluetooth sends 3.3V and it is recognised by arduino
RX -> TX voltage regulator needed 
*/
#define ledPin 13
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); //  communication rate of the Bluetooth module
}

void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
 }

 if (state == '0') {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ON");;
  state = 0;
 } 
}
