/*
 Type DHT11
Measures both temperature and humitidy
*/

#include "DHT.h"

#define DHTPIN 11     // what pin we're connected to

#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup(void) {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  
  float temperature, humidity;

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  delay(2000); 

 char tempF[6]; 
 char humF[6];
 dtostrf(temperature, 5, 1, tempF); // conversion to string from float
 dtostrf(humidity, 2, 0, humF);

 Serial.print("T:"); 
 Serial.print(tempF);
 //Serial.print((char)223);
 Serial.print("C ");
 Serial.print("H: ");
 Serial.print(humF);
 Serial.println("%");
}
