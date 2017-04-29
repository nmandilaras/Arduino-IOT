//2-Way motor control
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A1 
#define ECHO_PIN A0 
#define MAX_DISTANCE 200 
#define motorPin1  5    // One motor wire connected to digital pin 5
#define motorPin2  6    // One motor wire connected to digital pin 6
#define MAX_SPEED 200 // sets speed of DC  motors

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;
int distance = 100;
void setup()   { 
  Serial.begin(9600);               
  // initialize the digital pins as an output:
  pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT);  
  myservo.attach(8);
  myservo.write(90);
  delay(40);  
}

void loop(){
  /*delay(150);
  lookRight();
  delay(300);
  lookLeft();
  delay(150);
  */
  int distanceR = 0;
  int distanceL =  0;
  //delay(40);  
  distance = readPing();
  delay(50);
  if(distance<=45){
     moveStop();
    delay(50);
    distance = readPing();
      if(distance<=18){
           moveBackward();
    delay(300);
           moveStop();
            delay(50); 
      }

    distanceR = lookRight();
    delay(50);
    distanceL = lookLeft();
    delay(50);
    if(distanceR>=distanceL){
      turnRight(235,400);
      //moveStop();
    }
    else{
      turnLeft(200,400);
      //moveStop();
    }
  }
  else moveForward();
  /* 
  rotateRight(255, 400);
  delay(400);
  rotateLeft(255, 400);
  delay(400);
 */
}


void moveStop() {
  digitalWrite(motorPin1, LOW); 
  digitalWrite(motorPin2, LOW); 
}

void moveForward() {
  
   analogWrite(motorPin1, 235);
   analogWrite(motorPin2, 190);
     
   /*for (int speedOfRotate= 80; speedOfRotate < MAX_SPEED; speedOfRotate +=20) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    analogWrite(motorPin1, speedOfRotate);
    analogWrite(motorPin2, speedOfRotate);
    delay(5);
   }*/
}
 
void turnLeft(int speedOfRotate, int interval){
  analogWrite(motorPin1, speedOfRotate); //rotates motor
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
  delay(interval); //waits
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
}

void turnRight(int speedOfRotate, int interval){
  analogWrite(motorPin2, speedOfRotate); //rotates motor
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
  delay(interval); //waits
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
}

void moveBackward(){
  digitalWrite(motorPin2, HIGH);  
  delay(500); //waits
  digitalWrite(motorPin2, LOW);  
}

int lookRight(){
    myservo.write(35); 
    delay(300);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
}

int lookLeft(){
    myservo.write(145); 
    delay(300);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0) cm = 250;
  Serial.println(cm);
  return cm;
}
