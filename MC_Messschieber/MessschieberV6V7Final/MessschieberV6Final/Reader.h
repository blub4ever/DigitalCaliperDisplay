#ifndef _READER_H
#define _READER_H

#include "Arduino.h"



class Reader{
  public:
    Reader(int);
    /**
      declars ports
    **/
    void init(int interrupt ,void (*userFunc)(void));
    /**
      Reads the measure values.
    **/
    void update();
    
    /**
      Checks if a time out occurs
    **/
    boolean isAttached(int);
    
    /**
      True if caliper is attached
    **/
    boolean cAttached;

    /**
      True if caliper was attached
    **/
    boolean wasAttached;
    
    /**
      True if caliper value has changed
    **/
    boolean valueChanged;

    /**
      Caliper value
    **/
     long value;
    
  private:
    /**
      Data pin
    **/
    int dataPin;
    
    /**
    **/
    int pulseCount;
    
    /**
    **/
    long  tmpValue;
    
    /**
      Needed for getting caliper values
    **/
    long time;
};

#endif
