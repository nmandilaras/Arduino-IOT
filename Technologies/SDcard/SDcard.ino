/*
MISO -> PIN 12
MOSI ->  PIN 11
SCK -> PIN 13
CS -> PIN 10 (our choice)

*/

#include <SD.h>
#include <SPI.h>

int CS_PIN = 10;

File file;
char text[] = "This is sample text!";

void setup()
{

  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);

  if (!SD.begin()) {
		 Serial.println("SD failed to initialize. Aborting....");
		 return;		
	}
	Serial.println("SD card is ready to use.");	

	file = SD.open("TEST.txt", FILE_WRITE);
	if (file){
		//text = "This is sample text!"
		Serial.println("Writing to file: ");
    Serial.println(text);
 		file.println(text); 	
		file.close();
	}
	else Serial.println("Error while creating file. Aborting");

  file = SD.open("prefs.txt");
	if (file){
  	Serial.println(readLine());
  	Serial.println(readLine());
  	file.close();
	}
}

void loop()
{
}
/*
boolean initializeSD(){

  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
	  return true;
  } else
  {
    Serial.println("SD card initialization failed");
    return false;
  }
}

int createFile(char filename[])
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[])
{
  file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return 1;
  } else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}

int writeToFile(char text[])
{
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}*/

String readLine()
{
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return "";
}





