#include "DisplayUnit.h"

void DisplayUnit::setUnit(uint8_t x_start,uint8_t y_start,uint8_t char_width, uint8_t point_width,uint8_t char_hight,uint8_t max_chars,uint8_t name_x,uint8_t name_y,uint8_t unit_x,uint8_t unit_y){
     DisplayUnit::x_start = x_start;
     DisplayUnit::y_start = y_start;
     DisplayUnit::char_width = char_width;
     DisplayUnit::point_width = point_width;
     DisplayUnit::char_hight = char_hight;
     DisplayUnit::max_chars = max_chars;
     DisplayUnit::name_x = name_x;
     DisplayUnit::name_y = name_y;
     DisplayUnit::unit_x = unit_x;
     DisplayUnit::unit_y = unit_y;
 
 }
