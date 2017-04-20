void drawWelcome() {

  GLCD.FillRect( 0, 0, DISPLAY_X_MAX, DISPLAY_Y_MAX, WHITE);
  GLCD.SelectFont(DRAW_DESCRIPTION_FONT_MEDIUM);
  GLCD.DrawString_P(welcome_1, 10, 10);
  GLCD.DrawString_P(welcome_2, 10, 25);
  GLCD.DrawString_P(welcome_4, 90, 48);

  GLCD.SelectFont(DRAW_DESCRIPTION_FONT_SMALL);
  GLCD.DrawString_P(welcome_3, 4, 54);
}

void drawPleaseAttach() {

  GLCD.FillRect( 0, 0, DISPLAY_X_MAX, DISPLAY_Y_MAX, WHITE);
  // Select the font for the default text area
  GLCD.SelectFont(DRAW_DESCRIPTION_FONT_MEDIUM);
  GLCD.DrawString_P(attach_1, 42, 15);
  GLCD.DrawString_P(attach_2, 15, 30);


}
boolean readerXAttached;
boolean readerYAttached;
boolean readerZAttached;

  
void drawMeasurmentScale() {

  // clear display
  GLCD.FillRect( 0, 0, DISPLAY_X_MAX, DISPLAY_Y_MAX, WHITE);

  GLCD.SelectFont(descritionFont);

  if (readerX.cAttached) {
    GLCD.DrawString("X", unitX.name_x, unitX.name_y);
    GLCD.DrawString("mm", unitX.unit_x, unitX.unit_y);
  }

  if (readerY.cAttached) {
    GLCD.DrawString("Y", unitY.name_x,  unitY.name_y);
    GLCD.DrawString("mm", unitY.unit_x, unitY.unit_y);
  }

  if (readerZ.cAttached) {
    GLCD.DrawString("Z", unitZ.name_x, unitZ.name_y);
    GLCD.DrawString("mm", unitZ.unit_x, unitZ.unit_y);
  }

  // Select the font for the default text area
  GLCD.SelectFont(caliperFont);

}

void drawReader(Reader *reader, DisplayUnit *unit, boolean force) {

  char convert[9];
  dtostrf((((float)(*reader).value) / 100), 9, 2, convert);
 
  // Max 7 chars
  for(byte i = 8 ; i > 1; i--){
          
    if((convert[i] != (unit->value[i])) || force){
      (*unit).value[i] = convert[i];
      
     // if(force){
     //    Serial.print(convert[i]);
     //   Serial.println(" - r");  
     // } 
       
    
      byte x_s;  
      if(i < 7){
        x_s = unit->x_start+ (i-2)*(unit->char_width)+ (i-2)*2 ;
      }else
        x_s = unit->x_start+ (i-2)*(unit->char_width)+ (i-2)*2 - (unit->char_width-unit->point_width);
        
      if(convert[i] ==' '){
        GLCD.FillRect(  x_s,  unit->y_start, unit->char_width, unit->char_hight, WHITE);
      }else if(convert[i] == '.'){
        GLCD.FillRect(  x_s,  unit->y_start+unit->char_hight-unit->point_width, unit->point_width, unit->point_width, BLACK);
      }else  
        drawChar(x_s, unit->y_start, unit->char_width, unit->char_hight, convert[i] );
    }
    
  }
  //Serial.println("----");
  //Serial.println((*reader).value);
  //drawString(unit, (*pos).xMax, (*pos).yMin, (*pos).yMax, convert);
}

void drawChar(int x_start, int y_start, int char_width, int char_hight, char text) {
  GLCD.CursorToXY(x_start, y_start);
  GLCD.print(text);
}

/**
  draws the measurement chars
**/
void drawString(int xMin, int xMax, int yMin, int yMax, char cArray[]) {
  //GLCD.FillRect( xMin, yMin, xMax - xMin, yMax - yMin, WHITE);
  GLCD.DrawString(cArray, xMin, yMin);
}
