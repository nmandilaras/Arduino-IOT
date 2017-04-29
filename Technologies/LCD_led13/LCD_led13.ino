/***********************************
  Code By abrushfx.com
  Started on July 9th 2012
  
************************************/
//
//Used for this particular LCD with these pin specific pin numbers.
//http://www.sparkfun.com/datasheets/LCD/GDM1602K.pdf

#include  <LiquidCrystal.h>

/*Connect LCD to Arduino:
  LCD    -> Arduino
  --------------------------
  1|VSS| -> Arduino GND
  2|VDD| -> Arduino +5v
  3|VO | -> Arduino GND pin + Resistor or Potentiometer
  4|RS | -> Arduino pin 12
  5|RW | -> Arduino GND - pin can be conected to 11. But Ground was used here.
  6|E  | -> Arduino pin 10
  7|D0 | -> Arduino - Not Connected
  8|D1 | -> Arduino - Not Connected
  9|D2 | -> Arduino - Not Connected
 10|D3 | -> Arduino - Not Connected
 11|D4 | -> Arduino pin 5 
 12|D5 | -> Arduino pin 4
 13|D6 | -> Arduino pin 3
 14|D7 | -> Arduino pin 2
 15|A  | -> Arduino Pin 13 + Resistor (Backlight power)
 16|K  | -> Arduino GND (Backlight ground)
*/


//Arduino scrolling text example

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
//  pinMode(backLight, OUTPUT);        	//set pin 13 as output
//  analogWrite(backLight, 150);       	//controls the backlight intensity 0-254
  
  lcd.begin(16,2);                		// columns, rows. size of display
  lcd.clear();                    		// clear the screen
  lcd.setCursor(0,0);             		// set cursor to column 0, row 0 (first row)
  lcd.print("Hello. Is there anybody out there?");       // input your text here
  lcd.setCursor(0,1);             		// move cursor down one
  lcd.print("fuck you john");  		//input your text here
}

void loop()
{
  lcd.setCursor(16,1); // set the cursor outside the display count
  lcd.autoscroll();    // set the display to automatically scroll:
  lcd.print("opa ");      // print empty character
  delay(500);          
} 
