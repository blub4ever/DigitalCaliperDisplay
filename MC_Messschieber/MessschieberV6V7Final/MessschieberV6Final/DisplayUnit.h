#ifndef _DISPLAYUINT_H
#define _DISPLAYUINT_H

#include "Arduino.h"

class DisplayUnit {
  public:

    uint8_t x_start;
    uint8_t y_start;
    
    uint8_t char_width;
    uint8_t point_width;
    uint8_t char_hight;
    
    uint8_t max_chars;
    
    uint8_t name_x;
    uint8_t name_y;
    
    uint8_t unit_x;
    uint8_t unit_y;
    
    char value[9];
    
    void setUnit(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
};


#endif
