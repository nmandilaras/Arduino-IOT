//#include <SoftwareSerial.h> // βιβλιοθήκη για προγραμματιζόμενη σειριακή
#include <string.h> // βιβλιοθήκη για συμβολοσειρές

void dump();          // Συνάρτηση καθαρισμού σειριακής (Buffer)
void SendPageHigh(); // Συνάρτηση όταν είναι αναμμένο το φως
void SendPageLow(); // Συνάρτηση όταν δεν είναι αναμμένο το φως

//SoftwareSerial esp(3,2); //rx=3, tx=2
char data[50];
int ledPin=13;
int state=LOW;
int index;

void setup() {
 //Serial.begin(9600);
 Serial.begin(9600);
 pinMode(ledPin,OUTPUT);
 Serial.println("AT+RST");
 delay(6000);
 Serial.println("AT+CWMODE=1");
 delay(100);
 Serial.println("AT+CWJAP=\"COSMOTE-D813E4\",\"Uennkenmoywn16\"");
 delay(5000);
// Serial.println("AT+CIPSTA=\"192.168.1.11\""); //orismos statikis IP
 //delay(5000);
 Serial.println("AT+CIPMUX=1");
 delay(100);
 Serial.println("AT+CIPSERVER=1,80");
 delay(100);
 dump();
 //SendPageLow();
} 

void loop() {
  index=0;
  while(Serial.available() && index<499){
    data[index]=Serial.read();
    index++;
    delay(2);  
  }
  data[index]='\0';
  if (index>0){
    if(strstr(data,"/on")){
      state=HIGH;
      digitalWrite(ledPin,state);
    }
    else if (strstr(data,"/off")){
      state=LOW;
      digitalWrite(ledPin,state);
    }
    if (state==HIGH)SendPageHigh(); else SendPageLow();  
  }
}


void dump () {
  while (Serial.available())
        Serial.read();
}

void SendPageHigh(){
 Serial.println("AT+CIPSEND=0,100");
  delay(100);
  Serial.println("<h1>Welcome to Home Automation</h1><br>Lamp is ON</br><a href=\"/off\"><button>Lamp Off</button></a>");
  delay(500);
 Serial.println("AT+CIPCLOSE=0");
  delay(100);
  //Serial.println("Led On");
  dump();
}

void SendPageLow(){
  Serial.println("AT+CIPSEND=0,99");
  delay(100);
  Serial.println("<h1>Welcome to Home Automation</h1><br>Lamp is OFF</br><a href=\"/on\"><button>Lamp On</button></a>");
  delay(500);
  Serial.println("AT+CIPCLOSE=0");
  delay(100);
  //Serial.println("Led Off");
  dump();
}

