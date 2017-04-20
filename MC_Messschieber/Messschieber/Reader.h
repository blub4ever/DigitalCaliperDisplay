#ifndef _READER_H
#define _READER_H

#include "Arduino.h"


// time out between measurements in ms
#define TIMEOUT_MEASUREMENTS 150


class Reader{
  public:
    Reader(int,int);
    /**
      declars ports
    **/
    void init();
    /**
      Reads the measure values.
    **/
    void update();
    
    /**
      Checks if a time out occurs
    **/
    boolean isTimeout(int);
    
    /**
      True if caliper is attached
    **/
    boolean measureAttached;
    /**
      True if caliper value has changed
    **/
    boolean valueChanged;
    
    /**
      True if the cliper is not attached and the not attached string has been drawn
    **/
    boolean measureWasAttached;
    
    /**
      Caliper value
    **/
    long value;
  private:
    /**
      CLK Port
    **/
    int clk;
    
    /**
      Data port
    **/
    int data;
    
    /**
      Needed for getting caliper values
    **/
    long time;
    
    /**
      Needed for timeout detection
    **/
    long timeout;
};

#endif
