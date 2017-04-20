void drawWelcome() {

  GLCD.FillRect( 0, 0, X_MAX, Y_MAX, WHITE);
  GLCD.SelectFont(DRAW_DESCRIPTION_FONT_MEDIUM);
  GLCD.DrawString_P(welcome_1, 10, 10);
  GLCD.DrawString_P(welcome_2, 10, 25);
  GLCD.DrawString_P(welcome_4, 90, 48);

  GLCD.SelectFont(DRAW_DESCRIPTION_FONT_SMALL);
  GLCD.DrawString_P(welcome_3, 4, 54);
}

void drawPleaseAttach() {

  GLCD.FillRect( 0, 0, X_MAX, Y_MAX, WHITE);
  // Select the font for the default text area
  GLCD.SelectFont(DRAW_DESCRIPTION_FONT_MEDIUM);
  GLCD.DrawString_P(attach_1, 42, 15);
  GLCD.DrawString_P(attach_2, 15, 30);


}

void drawMeasurmentScale() {

  GLCD.FillRect( 0, 0, X_MAX, Y_MAX, WHITE);

  GLCD.SelectFont(descritionFont);

  if (readerX.measureAttached) {
    GLCD.DrawString("X", posX.xAxis, posX.yAxis);
    GLCD.DrawString("mm", posX.xMeasur, posX.yMeasur);
  }

  if (readerY.measureAttached) {
    GLCD.DrawString("Y", posY.xAxis, posY.yAxis);
    GLCD.DrawString("mm", posY.xMeasur, posY.yMeasur);
  }

  if (readerZ.measureAttached) {
    GLCD.DrawString("Z", posZ.xAxis, posZ.yAxis);
    GLCD.DrawString("mm", posZ.xMeasur, posZ.yMeasur);
  }

  // Select the font for the default text area
  GLCD.SelectFont(caliperFont);

}

void drawReader(Reader *reader, struct drawPosition *pos) {
  char convert[9];
  dtostrf((((float)(*reader).value) / 100), 8, 2, convert);
  drawString((*pos).xMin, (*pos).xMax, (*pos).yMin, (*pos).yMax, convert);
}


/**
  draws the measurement chars
**/
void drawString(int xMin, int xMax, int yMin, int yMax, char cArray[]) {
  GLCD.FillRect( xMin, yMin, xMax - xMin, yMax - yMin, WHITE);
  GLCD.DrawString(cArray, xMax - GLCD.StringWidth(cArray), yMin);
}
