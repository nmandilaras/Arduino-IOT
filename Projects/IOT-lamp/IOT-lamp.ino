#include <SoftwareSerial.h> // βιβλιοθήκη για προγραμματιζόμενη σειριακή
#include <string.h> // βιβλιοθήκη για συμβολοσειρές
#define  Arsize 150
const int analogPin = 0;
const int lampPin = 13;            // we need pwm

SoftwareSerial esp(3,2); //rx=3, tx=2

int index;
int val=0;
bool lampOff = false;
bool musicOn = false ;
bool autoOn = false ;
char c;
String str0 = "<html><body bgcolor=\"#E6E6FA\" align=\"center\"><h1>Welcome to Home Automation</h1><br>" ;
String str1 = "</button></a></body></html>";

void setup() {
 Serial.begin(9600);
 esp.begin(9600);
 pinMode(lampPin,OUTPUT);
 esp.println("AT+RST");
 delay(1000);
 //esp.println("AT+CIOBAUD=9600");
 //delay(200);
 esp.println("AT+CWMODE=1");
 delay(100);
 esp.println("AT+CWJAP=\"COSMOTE-D813E4\",\"Uennkenmoywn16\"");
 delay(5000);
 //esp.println("AT+CIPSTA=\"192.168.1.17\""); //orismos statikis IP
 //delay(5000);
 esp.println("AT+CIPMUX=1");
 delay(100);
 esp.println("AT+CIPSERVER=1,80");
 delay(100);
 dump();
 Serial.println("Pame");
} 

void loop() {
  
 char data[Arsize];
  index=0;
  while(esp.available() && index<Arsize-1){
    data[index]=esp.read();
    index++;
    delay(2);  
  }
  data[index]='\0'; //last place in array for this 
  if (index>0){
  c = data[0];   
  Serial.println(data);
  Serial.println("=======");   
    musicOn = false;
    autoOn = false;
    lampOff = false;        
    val = 0;
    if(strstr(data,"/on"))  {         
      val = 255;
      analogWrite(lampPin, val);      
    }
    else if (strstr(data,"/off")){
      lampOff = true;
      analogWrite(lampPin, 0);     
    }
    else if(strstr(data,"/med")){  
      val = 170;
      analogWrite(lampPin, val);
      }
    else if(strstr(data,"/low")){
      val = 85;
      analogWrite(lampPin, val);
    }
    //else if(strstr(data,"/music"))   musicOn = true;
    //else if(strstr(data,"/auto"))    autoOn = true;            
    //analogWrite(lampPin, val);
    
    if (lampOff)SendPageLow(); 
    else if (musicOn) ;//SendPageMusic();
    else if (autoOn) ;//SendPageAuto();    
    else if (val>0)SendPageHigh(); 
  }
  if (musicOn){
    val =analogRead(analogPin);        // read microphone's measure
    val=map(val,0,1023,0,255);
    analogWrite(lampPin,val);           // write it on lamp
    }
    dump();
}

void dump () {
  while (esp.available()){
          esp.read();
        //c=esp.read();
       // Serial.print(c);
  }
}

void SendPageHigh(){
 esp.println("AT+CIPSEND=0,312");
 //esp.print(c);
 //esp.println(",312");
  delay(100);
  esp.println("<html><body bgcolor=\"#E6E6FA\" align=\"center\"><h1>Welcome to Home Automation</h1><br>Lamp is ON</br><a href=\"/off\"><button>Lamp Off</button></a><br><br/><br>Adjust brightness</br><a href=\"/on\"><button>High</button></a><a href=\"/med\"><button>Medium</button></a><a href=\"/low\"><button>Low</button></a></body></html>");
  delay(500);
 esp.println("AT+CIPCLOSE=0");
 //esp.println(c);
  delay(100);
  //dump();
}

void SendPageLow(){
  esp.println("AT+CIPSEND=0,156");
 //esp.print(c);
 //esp.println(",156");  
  delay(100);
  esp.println("<html><body bgcolor=\"#E6E6FA\" align=\"center\"><h1>Welcome to Home Automation</h1><br>Lamp is OFF</br><a href=\"/on\"><button>Lamp On</button></a></body></html>");
  delay(500);
 esp.println("AT+CIPCLOSE=0");
 //esp.println(c);
  delay(100);
  //dump();
}
/*
void SendPageMusic(){
 esp.println("AT+CIPSEND=0,165");
  delay(100);
  esp.println(str0 + "Music Mode On</br><a href=\"/on\"><button>Back To Normal" + str1);
  delay(500);
 esp.println("AT+CIPCLOSE=0");
  delay(100);
  dump();
}

void SendPageAuto(){
 esp.println("AT+CIPSEND=0,165");
  delay(100);
  esp.println(str0 + "Automate Mode On</br><a href=\"/on\"><button>Back To Normal" + str1);
  delay(500);
 esp.println("AT+CIPCLOSE=0");
  delay(100);
  dump();
}*/
