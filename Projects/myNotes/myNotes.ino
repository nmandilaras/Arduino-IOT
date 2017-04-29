/*
 Plays Jingle Bells and blinks corresponately 10 Leds

 circuit:
 * 8-ohm speaker on digital pin 12!
 * 10 leds in pins 2-11 classic configiration with 220 ohms resistors

 http://www.arduino.cc/en/Tutorial/Tone
 */
#include "pitches.h"

int melody[]={NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_G5,NOTE_C5,NOTE_D5,
NOTE_E5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_D5,NOTE_D5,NOTE_E5,
NOTE_D5,NOTE_G5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_G5,NOTE_C5,NOTE_D5,
NOTE_E5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_E5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_F5,NOTE_D5,
NOTE_C5}; // notes in the melody: pinakas me tis notes tou kommatioy

// note durations: 4 = quarter note, 8 = eighth note, 2 = half note. etc:
float noteDurations[] = {4, 4, 2, 4, 4, 2, 4, 4,4,4,1,4,4,4,4,4,4,2,4,4,4,4,2,2,4,4,2,4,4,2,4,4,
4,4,1,4,4,4,4,4,4,2,4,4,4,4,1.33
}; // pinakas me tis diarkeies twn notwn, antistoixei me ton apopanw

void setup() {
  
 for(int led=2; led<12; led++)
         pinMode(led,OUTPUT); // arxikopoihsh ws exodo twn led
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 47; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    float noteDuration = 1000.0 / noteDurations[thisNote];
    for(int led=2; led<12; led++) digitalWrite(led,HIGH); //anama led
    tone(12, melody[thisNote], noteDuration); // prwto orisma pin hxeiou
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    for(int led=2; led<12; led++) digitalWrite(led,LOW); svhsimo twn led
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes); 

    noTone(12);     // stop the tone playing:
  }
}
void loop() {
  // no need to repeat the melody.
}
