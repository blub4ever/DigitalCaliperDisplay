boolean updateDisplay(){
 // move to util
  if(checkReader(&readerX) || checkReader(&readerY) || checkReader(&readerZ)){
    Serial.print("Aktiv: ");
     Serial.print(readerX.cAttached);
      Serial.print(readerY.cAttached);
       Serial.print(readerZ.cAttached);
        Serial.println("");
    calculatePositions(readerX.cAttached, readerY.cAttached, readerZ.cAttached);
    return true;
  }
  return false;
}

boolean checkReader(Reader *reader) {
  boolean update = false;
  
  if((*reader).isAttached(1000)){
    if(!(*reader).wasAttached){
      Serial.println("is at was not");
      update = true;
      (*reader).wasAttached = true;
    }
  }else if((*reader).wasAttached){
    (*reader).wasAttached = false;
    update = true;
    Serial.println("was at is not");
  }
  
  return update;
}


void calculatePositions(boolean x, boolean y, boolean z){
  byte readerCount = (x ? 1 : 0) +(y ? 1 : 0 )+ (z ? 1: 0);
  DisplayUnit *unit = 0;
  
  switch(readerCount){
   case 0:
    break;
   case 1: 
     caliperFont = Arial38;
     descritionFont = DRAW_DESCRIPTION_FONT_MEDIUM;
     
     if(x)
       unit = &unitX;
     else if(y)
       unit = &unitY;
     else 
       unit = &unitZ;
       
     unit->setUnit(ONE_X_START,ONE_Y_START,ONE_CHAR_WIDTH,ONE_POINT_WIDTH,ONE_CHAR_HIGHT,ONE_MAX_CHARS,ONE_X_START_UNIT,ONE_Y_START_UNIT,ONE_X_START_NAME,ONE_Y_START_NAME);
   break;
   case 2:
     caliperFont = Arial28;
     descritionFont = DRAW_DESCRIPTION_FONT_SMALL;
     if(x)
       unitX.setUnit(TWO_X_START,TWO_Y_START_1,TWO_CHAR_WIDTH,TWO_POINT_WIDTH,TWO_CHAR_HIGHT,TWO_MAX_CHARS,TWO_X_START_UNIT_1,TWO_Y_START_UNIT_1, TWO_X_START_NAME_1,TWO_Y_START_NAME_1);
     
     if(y && x){ 
       unitY.setUnit(TWO_X_START,TWO_Y_START_2,TWO_CHAR_WIDTH,TWO_POINT_WIDTH,TWO_CHAR_HIGHT,TWO_MAX_CHARS,TWO_X_START_UNIT_2,TWO_Y_START_UNIT_2, TWO_X_START_NAME_2,TWO_Y_START_NAME_2);
       
       Serial.println("only y");  
     }else if(y){
       unitY.setUnit(TWO_X_START,TWO_Y_START_1,TWO_CHAR_WIDTH,TWO_POINT_WIDTH,TWO_CHAR_HIGHT,TWO_MAX_CHARS,TWO_X_START_UNIT_1,TWO_Y_START_UNIT_1, TWO_X_START_NAME_1,TWO_Y_START_NAME_1);
       Serial.println("x y");
     }
     if(z)
       unitZ.setUnit(TWO_X_START,TWO_Y_START_2,TWO_CHAR_WIDTH,TWO_POINT_WIDTH,TWO_CHAR_HIGHT,TWO_MAX_CHARS,TWO_X_START_UNIT_2,TWO_Y_START_UNIT_2, TWO_X_START_NAME_2,TWO_Y_START_NAME_2);
   break;
   case 3:
     caliperFont = Arial18;
     descritionFont = DRAW_DESCRIPTION_FONT_SMALL;
     
      unitX.setUnit(THREE_X_START,THREE_Y_START_1,THREE_CHAR_WIDTH ,THREE_POINT_WIDTH,THREE_CHAR_HIGHT,THREE_MAX_CHARS, THREE_X_START_NAME_1,THREE_Y_START_NAME_1,THREE_X_START_UNIT_1,THREE_Y_START_UNIT_1);
      unitY.setUnit(THREE_X_START,THREE_Y_START_2,THREE_CHAR_WIDTH ,THREE_POINT_WIDTH,THREE_CHAR_HIGHT,THREE_MAX_CHARS, THREE_X_START_NAME_2,THREE_Y_START_NAME_2,THREE_X_START_UNIT_2,THREE_Y_START_UNIT_2);
      unitZ.setUnit(THREE_X_START,THREE_Y_START_3,THREE_CHAR_WIDTH ,THREE_POINT_WIDTH,THREE_CHAR_HIGHT,THREE_MAX_CHARS, THREE_X_START_NAME_3,THREE_Y_START_NAME_3,THREE_X_START_UNIT_3,THREE_Y_START_UNIT_3);
   break;
  }
}





