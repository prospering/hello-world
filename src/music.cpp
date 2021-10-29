
#include <Arduino.h>
#include <M5Stack.h>

void playNote(float freq, float ms, float delayNextNote = 0) {
  M5.Speaker.tone(freq, ms);
  delay(freq);
  M5.Speaker.end();
  delay(delayNextNote);
}

void playRickRoll() {
   playNote(207.65,100);
   playNote(233.08,100);
   playNote(277.18,100);
   playNote(233.08,100);
   playNote(349.23,250,150);
   playNote(349.23,250,150);
   playNote(311.13,400);

   delay(400);

   playNote(207.65,100);
   playNote(233.08,100);
   playNote(277.18,100);
   playNote(233.08,100);
   playNote(311.13,250,150);
   playNote(311.13,250,150);
   playNote(277.18,400);

   delay(150);
   
   playNote(261.63,50);
   playNote(233.08,50);

   delay(150);

   playNote(207.65,100);
   playNote(233.08,100);
   playNote(277.18,100);

   delay(100);

   playNote(277.18,400);
   playNote(311.13,100);
   playNote(261.63,100);
   playNote(233.08,50);
   playNote(207.65,50);
}