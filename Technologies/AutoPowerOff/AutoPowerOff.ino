const int transistor =  7; 
void setup(void)
{
  pinMode(transistor, OUTPUT);
  digitalWrite(transistor, HIGH);
  int led=13;
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);

  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);  
  
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);  
    
  digitalWrite(transistor, LOW);
}

void loop() {

}

