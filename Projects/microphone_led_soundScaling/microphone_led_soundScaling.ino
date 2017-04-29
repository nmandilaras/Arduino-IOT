/* 
 *  
 */
 
 int const NumberOfLed=7; 
 int led[NumberOfLed];
  
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    for (int i=0; i<NumberOfLed; i++)
      led[i]=i+3;
    for(int i=0; i<NumberOfLed; i++)
      pinMode(led[i],OUTPUT);     
}

 int analogPin = 4;
 int val = 0;

void rest(int j){
  for (int i=0; i<j; i++)
      digitalWrite(led[i],HIGH);  
  for (int i=j; i<NumberOfLed; i++)
      digitalWrite(led[i],LOW);
      
}  

void loop() {
  val = analogRead(analogPin);
  Serial.println(val);
  if (val<350)
    rest(0); // all off              
  else if (val <440)
    rest(1);   
  else if (val <530)
    rest(2);          
  else if (val <620 )
    rest(3);        
  else if (val <710 )
    rest(4);           
  else if (val <800 )
    rest(5);        
  else if (val <910 )
    rest(NumberOfLed-1);                    
  else
    rest(NumberOfLed);
                  
  delay(40);
}

