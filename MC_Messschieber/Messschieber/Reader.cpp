#include "Reader.h"
#include "Arduino.h"


Reader::Reader(int clk, int data) {
  Reader::clk = clk;
  Reader::data = data;
}

void Reader::init() {
  pinMode(Reader::clk, INPUT);
  pinMode(Reader::data, INPUT);

  Reader::measureWasAttached = true;
  Reader::measureAttached = true;
  Reader::valueChanged = true;
}


void Reader::update() {
  Reader::timeout = millis();
  while (digitalRead(Reader::clk) == HIGH) {
    if (Reader::isTimeout(TIMEOUT_MEASUREMENTS))
      return;
  }

  // savin time to detect the 120ms interval
  Reader::time = micros();

  // Low flank about 120 ms
  Reader::timeout = millis();
  while (digitalRead(Reader::clk) == LOW) {
    if (Reader::isTimeout(TIMEOUT_MEASUREMENTS))
      return;
  }

  // if interval was found
  if (micros() - Reader::time > 500) {

    long value = 0;
    byte tmpHigh;
    
    //23 clock cycles
    for (int i = 0; i < 23; i++) {
      // no data
      Reader::timeout = millis();
      while (digitalRead(Reader::clk) == HIGH) {
        if (Reader::isTimeout(TIMEOUT_MEASUREMENTS))
          return;
      }
      // Low flank = data
      while (digitalRead(Reader::clk) == LOW) {
        if (Reader::isTimeout(TIMEOUT_MEASUREMENTS))
          return;
          
        // because of hardware inversion HIGH equals 0 
        if (digitalRead(Reader::data) == HIGH)
          tmpHigh++;
      }
      
      // no value was HIGH so a bit has to be set (data only untill bit 20
      if (tmpHigh == 0 && i < 20) {
        value |= 1 << i;
      // bit 20 prfix
      } else if (tmpHigh == 0 && i == 20) {
        value *= -1;
      }

      tmpHigh = 0;

    }

    // update object data
    if (Reader::value != value) {
      Reader::value = value;
      Reader::valueChanged = true;
    }

  }
}


boolean Reader::isTimeout(int timeout) {
  if (millis() - Reader::timeout > timeout) {
    Reader::measureAttached = false;
    return true;
  }
  return false;
}


