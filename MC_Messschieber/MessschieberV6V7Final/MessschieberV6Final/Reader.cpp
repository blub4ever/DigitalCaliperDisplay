#include "Reader.h"
#include "Arduino.h"


Reader::Reader(int dataPin) {
  Reader::dataPin = dataPin;
}

void Reader::init(int interrupt , void (*userFunc)(void)) {
  attachInterrupt(interrupt, userFunc, RISING);
  pinMode(Reader::dataPin, INPUT);

  Reader::wasAttached = false;
  Reader::cAttached = false;
  Reader::valueChanged = true;
}


void Reader::update() {

  cli();
  long mill = millis();

  if (mill - Reader::time > 80) {

      if (Reader::pulseCount >= 23) {

        if (Reader::value != Reader::tmpValue) {
          Reader::value = Reader::tmpValue;
          Reader::valueChanged = true;
          Serial.println(Reader::tmpValue);
        }
        Reader::tmpValue = 0;
        Reader::time = mill;
        Reader::pulseCount = 0;
      } else {
        
        int tmpRead = digitalRead(Reader::dataPin) ;
        if (tmpRead == HIGH) {
          if (Reader::pulseCount < 20)
            Reader::tmpValue |= 1L << Reader::pulseCount;
          else if (Reader::pulseCount == 20)
            Reader::tmpValue *= -1;
        }
        Reader::pulseCount++;
      }
  }
  sei();
}


boolean Reader::isAttached(int timeout) {
  long time = millis();
  long readerTime = Reader::time;
  if ( (time - readerTime) >= timeout) {
    Reader::cAttached = false;
    return false;
  }else{
    Reader::cAttached = true;
  }
  return true;
}


