int led=3;
void setup() {
  pinMode(led,OUTPUT);
}

void loop() {
    analogWrite(led,0);
    delay(1200);
    analogWrite(led,64);
    delay(1200);
    analogWrite(led,128);
    delay(1200);
    analogWrite(led,192);
    delay(1200);    
    analogWrite(led,255);
    delay(1200); 
}
