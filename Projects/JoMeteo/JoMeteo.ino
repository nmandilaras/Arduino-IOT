#include "DHT.h"
#include "LowPower.h"
#define DHTTYPE DHT11  
#define DHTPIN 3     // what pin we're connected to
//#define Bluetooth 4
 
DHT dht(DHTPIN, DHTTYPE);

float humidity,sensorValue;
char humF[6];
int rainPin = A5,pResistor = A4,tempPin = A3;
void setup() {
  analogReference(INTERNAL);
  dht.begin(); 
  //pinMode(Bluetooth, OUTPUT); 
  Serial.begin(9600); // communication rate of the Bluetooth module
}

void loop() {
  /*delay(100);
  for(int i=0;i<5;i++) 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  delay(100);*/    
  analogRead(tempPin); // we throw some measurements, they get affected by each other
  sensorValue= analogRead(tempPin);
  sensorValue=((1.08*sensorValue/1023.0)*100); // first number is the voltage number with which we compare our measurement
  //sensorValue=((5*sensorValue/1023.0)*100);
  dht.readHumidity();  
  humidity = dht.readHumidity();
  dtostrf(humidity, 2, 0, humF);
  //digitalWrite(Bluetooth,HIGH);
  //delay(500);
  Serial.print("Temperature: ");
  Serial.print(sensorValue);
  Serial.println("*C");

  Serial.print("Humidity: ");
  Serial.print(humF);
  Serial.println("%");   
  
  //digitalWrite(Bluetooth,LOW);
  delay(500);
  /*analogRead(pResistor);
  sensorValue = analogRead(pResistor); 
  Serial.print("Brightness: "); 
  Serial.print(sensorValue/1023.0*100);
  Serial.println("%");  
  analogRead(rainPin);  
  sensorValue = analogRead(rainPin);
  Serial.print("Rain: "); 
  Serial.print(sensorValue/1023.0*100);
  Serial.println("%");*/   
}
