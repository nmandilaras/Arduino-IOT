/* http://www.instructables.com/id/RGB-LED-Tutorial-using-an-Arduino-RGBL/
 *  
 *  Modify gradually values for each led brightness so , different colors come up
  
 circuit:
 * a common anode piranha led. In order to find Color order starting try to find anode first  
 * classic 220 Ω resistors for each led
 * for common anode leds 255 is when they are off and 0 is maximum brightness
 */

int blue=9, green=10, red=11, wait=50, zero=255;
bool cathode = 0; // if it is a common cathode led or an anode led but transistor is used 

void setup() {

  if (cathode) zero=0;
  Serial.begin(9600);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  analogWrite(blue,zero); // we switch off all the colors
  analogWrite(green,zero);
  analogWrite(red,zero); 
}

void swap(int *p , int *q){
  int *temp;
  temp = p ;
  p = q;
  q = temp;
}

void colors(int colorOne ,int colorTwo){

  if (cathode) swap(&colorOne,&colorTwo);
  for (int i=0; i<256; i++){
   analogWrite(colorOne,255-i);   // we start with colorOne
   analogWrite(colorTwo,i);  // and gradually we increase colorTwo
   delay(wait);
  }
   delay(wait+500);
  
}

void loop() {
   colors(red,green); // start with red and gradually increase green
   colors(green,blue);
   colors(blue,red);      
}
