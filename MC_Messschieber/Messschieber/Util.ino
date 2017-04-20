void initReaderDisplayPositions() {
  readerAttachedCount = 0;

  reCheckReader(&readerX);
  if (readerX.measureAttached){
    readerAttachedCount++;
    Serial.println("X-Attached");
  }else
    readerX.measureWasAttached = false;

  reCheckReader(&readerY);
  if (readerY.measureAttached){
    readerAttachedCount++;
    Serial.println("Y-Attached");
  }else
    readerY.measureWasAttached = false;
    
  reCheckReader(&readerZ);
  if (readerZ.measureAttached){
    readerAttachedCount++;
    Serial.println("Z-Attached");
  }else
    readerZ.measureWasAttached = false;

  setPositionValues(&posX, 0, 0, 0, 0,0,0,0,0);
  setPositionValues(&posY, 0, 0, 0, 0,0,0,0,0);
  setPositionValues(&posZ, 0, 0, 0, 0,0,0,0,0);

  Serial.println("----");
  Serial.println(readerAttachedCount);
  
  switch (readerAttachedCount) {
    case 1:
      {
        caliperFont = Arial38;
        descritionFont = DRAW_DESCRIPTION_FONT_MEDIUM;
        
        if (readerX.measureAttached) {
          setPositionValues(&posX, ONE_X_MIN, ONE_X_MAX, ONE_Y_LINE_1_MIN, ONE_Y_LINE_1_MAX,ONE_X_LINE_1_MEASUR,ONE_Y_LINE_1_MEASUR,ONE_X_LINE_1_AXIS,ONE_Y_LINE_1_AXIS);
        } else if (readerY.measureAttached) {
          setPositionValues(&posY, ONE_X_MIN, ONE_X_MAX, ONE_Y_LINE_1_MIN, ONE_Y_LINE_1_MAX,ONE_X_LINE_1_MEASUR,ONE_Y_LINE_1_MEASUR,ONE_X_LINE_1_AXIS,ONE_Y_LINE_1_AXIS);
        } else {
          setPositionValues(&posZ, ONE_X_MIN, ONE_X_MAX, ONE_Y_LINE_1_MIN, ONE_Y_LINE_1_MAX,ONE_X_LINE_1_MEASUR,ONE_Y_LINE_1_MEASUR,ONE_X_LINE_1_AXIS,ONE_Y_LINE_1_AXIS);
        }
      }
      break;
    case 2:
      {
        boolean  previousAttachedTMP = false;
        
        caliperFont = Arial28;
        descritionFont = DRAW_DESCRIPTION_FONT_SMALL;
        
        if (readerX.measureAttached) {
          setPositionValues(&posX, TWO_X_MIN, TWO_X_MAX, TWO_Y_LINE_1_MIN, TWO_Y_LINE_1_MAX,TWO_X_LINE_1_MEASUR,TWO_Y_LINE_1_MEASUR,TWO_X_LINE_1_AXIS,TWO_Y_LINE_1_AXIS);
          previousAttachedTMP = true;
        }

        if (readerY.measureAttached) {
          if(previousAttachedTMP)
            setPositionValues(&posY, TWO_X_MIN, TWO_X_MAX, TWO_Y_LINE_2_MIN, TWO_Y_LINE_2_MAX, TWO_X_LINE_2_MEASUR, TWO_Y_LINE_2_MEASUR,TWO_X_LINE_2_AXIS,TWO_Y_LINE_2_AXIS);
          else
            setPositionValues(&posY, TWO_X_MIN, TWO_X_MAX, TWO_Y_LINE_1_MIN, TWO_Y_LINE_1_MAX,TWO_X_LINE_1_MEASUR,TWO_Y_LINE_1_MEASUR,TWO_X_LINE_1_AXIS,TWO_Y_LINE_1_AXIS);
        }

        if (readerZ.measureAttached) {
          setPositionValues(&posZ, TWO_X_MIN, TWO_X_MAX, TWO_Y_LINE_2_MIN, TWO_Y_LINE_2_MAX, TWO_X_LINE_2_MEASUR, TWO_Y_LINE_2_MEASUR,TWO_X_LINE_2_AXIS,TWO_Y_LINE_2_AXIS);
        }
      }
      break;
    case 3:
      {
        caliperFont = DRAW_CALIPER_FONT_SMALL;
        descritionFont = DRAW_DESCRIPTION_FONT_MEDIUM;
        
        setPositionValues(&posX, THREE_X_MIN, THREE_X_MAX, THREE_Y_LINE_1_MIN, THREE_Y_LINE_1_MAX, THREE_X_LINE_1_MEASUR,THREE_Y_LINE_1_MEASUR,THREE_X_LINE_1_AXIS,THREE_Y_LINE_1_AXIS);
        setPositionValues(&posY, THREE_X_MIN, THREE_X_MAX, THREE_Y_LINE_2_MIN, THREE_Y_LINE_2_MAX, THREE_X_LINE_2_MEASUR,THREE_Y_LINE_2_MEASUR,THREE_X_LINE_2_AXIS,THREE_Y_LINE_2_AXIS);
        setPositionValues(&posZ, THREE_X_MIN, THREE_X_MAX, THREE_Y_LINE_3_MIN, THREE_Y_LINE_3_MAX, THREE_X_LINE_3_MEASUR,THREE_Y_LINE_3_MEASUR,THREE_X_LINE_3_AXIS,THREE_Y_LINE_3_AXIS);
      }
      break;
  }
}

void initDisplayScreen(){
  if(readerAttachedCount > 0){
    drawMeasurmentScale();
    if (readerX.measureAttached) 
      drawReader(&readerX, &posX);
    if (readerY.measureAttached) 
      drawReader(&readerY, &posY);
    if (readerZ.measureAttached) 
      drawReader(&readerZ, &posZ);
  }else  
    drawPleaseAttach();
}

void setPositionValues(struct drawPosition * poS, int xMin, int xMax, int yMin, int yMax,int xMeasur, int yMeasur, int xAxis, int yAxis) {
  (*poS).xMin = xMin;
  (*poS).xMax = xMax;
  (*poS).yMin = yMin;
  (*poS).yMax = yMax;
  (*poS).xMeasur = xMeasur;
  (*poS).yMeasur = yMeasur;
  (*poS).xAxis = xAxis;
  (*poS).yAxis = yAxis;
}



void reCheckReader(Reader *reader) {
  (*reader).measureAttached = true;
  (*reader).measureWasAttached = true;
  (*reader).update();
}


