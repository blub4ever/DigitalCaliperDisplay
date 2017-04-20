#include "Reader.h"
#include <glcd.h>
#include "fonts/Arial18.h"         // system and arial14 fonts are used
#include "fonts/Arial28.h"         // system and arial14 fonts are used
#include "fonts/Arial38.h"         // system and arial14 fonts are used
#include "fonts/Arial_bold_14.h"       // all images in the bitmap dir 
#include "fonts/SystemFont5x7.h"



/** max and min coordiantes of the display **/
#define X_MAX 128
#define Y_MAX 64

/** Three calipers attached **/
#define THREE_X_MIN 10
#define THREE_X_MAX 95

#define THREE_Y_LINE_1_MIN 2
#define THREE_Y_LINE_1_MAX 21

#define THREE_X_LINE_1_MEASUR 100
#define THREE_Y_LINE_1_MEASUR 4

#define THREE_X_LINE_1_AXIS 2
#define THREE_Y_LINE_1_AXIS 4

#define THREE_Y_LINE_2_MIN 22
#define THREE_Y_LINE_2_MAX 41

#define THREE_X_LINE_2_MEASUR 100
#define THREE_Y_LINE_2_MEASUR 24

#define THREE_X_LINE_2_AXIS 2
#define THREE_Y_LINE_2_AXIS 24

#define THREE_Y_LINE_3_MIN 42
#define THREE_Y_LINE_3_MAX 61

#define THREE_X_LINE_3_MEASUR 100
#define THREE_Y_LINE_3_MEASUR 44

#define THREE_X_LINE_3_AXIS 2
#define THREE_Y_LINE_3_AXIS 44


/** TWO calipers attached **/
#define TWO_X_MIN 5
#define TWO_X_MAX 110

#define TWO_Y_LINE_1_MIN 5
#define TWO_Y_LINE_1_MAX 30

#define TWO_X_LINE_1_MEASUR 114
#define TWO_Y_LINE_1_MEASUR 16

#define TWO_X_LINE_1_AXIS 114
#define TWO_Y_LINE_1_AXIS 7

#define TWO_Y_LINE_2_MIN 35
#define TWO_Y_LINE_2_MAX 60

#define TWO_X_LINE_2_MEASUR 114
#define TWO_Y_LINE_2_MEASUR 46

#define TWO_X_LINE_2_AXIS 114
#define TWO_Y_LINE_2_AXIS 37

/** One caliper attached **/
#define ONE_X_MIN 5
#define ONE_X_MAX 124

#define ONE_Y_LINE_1_MIN 25
#define ONE_Y_LINE_1_MAX 64

#define ONE_X_LINE_1_MEASUR 100
#define ONE_Y_LINE_1_MEASUR 2

#define ONE_X_LINE_1_AXIS 2
#define ONE_Y_LINE_1_AXIS 2


// font for description
#define DRAW_DESCRIPTION_FONT_MEDIUM Arial_bold_14
#define DRAW_DESCRIPTION_FONT_SMALL System5x7

// font for measurement
#define DRAW_CALIPER_FONT_BIG Arial38
#define DRAW_CALIPER_FONT_MEDIUM Arial28
#define DRAW_CALIPER_FONT_SMALL Arial18

Reader readerX(1, 23);
Reader readerY(3, 2);
Reader readerZ(17, 13);

struct drawPosition {
  uint8_t xMin;
  uint8_t xMax;
  uint8_t yMin;
  uint8_t yMax;
  
  uint8_t xMeasur;
  uint8_t yMeasur;
  
  uint8_t xAxis;
  uint8_t yAxis;
} posX, posY, posZ;

uint8_t* unitFont = Arial_bold_14;

uint8_t* descritionFont = Arial_bold_14;

uint8_t* caliperFont = Arial18;

int readerAttachedCount = 0;

boolean intteruptFired = false;
long intteruptBounceTime = 0;

prog_char welcome_1[] PROGMEM  = {"Welcome"};
prog_char welcome_2[] PROGMEM  = {"Caliper Display"};
prog_char welcome_3[] PROGMEM  = {"by A. Glatz"};
prog_char welcome_4[] PROGMEM  = {"v3.0"};

prog_char attach_1[] PROGMEM  = {"Please"};
prog_char attach_2[] PROGMEM  = {"attach caliper!"};


void setup() {
  // begin serial
  Serial.begin(9600);
  Serial.println("Starte");

  // Initialize the GLCD
  GLCD.Init();

  drawWelcome();

  delay(5000);
  
  readerX.init();
  readerY.init();
  readerZ.init();

 
  initReaderDisplayPositions();
  initDisplayScreen();

  attachInterrupt(2, buttonInterrupt, RISING);
}


void loop() {


  if (intteruptFired) {
    Serial.println("hallo test");
    initReaderDisplayPositions();
    initDisplayScreen();
    intteruptFired = false;
    intteruptBounceTime = millis();
  } else if (intteruptBounceTime > 0) {
    if (millis() - intteruptBounceTime > 1000) {
      intteruptBounceTime = 0;
      attachInterrupt(2, buttonInterrupt, RISING);
    }
  }

  // X axsis, check if attached
  if (readerX.measureAttached) {
    // udates
    readerX.update();
    // only draw new chars if the value has changed
    if (readerX.valueChanged) {
      drawReader(&readerX, &posX);
      readerX.valueChanged = false;
    }
    // if not attached, draw a line
  } else if (readerX.measureWasAttached) {
    initReaderDisplayPositions();
    initDisplayScreen();
  }
  
  // y axsis
  if (readerY.measureAttached)  {
    readerY.update();
    if (readerY.valueChanged) {
      drawReader(&readerY, &posY);
      readerY.valueChanged = false;
    }
  }else if (readerY.measureWasAttached) {
    initReaderDisplayPositions();
    initDisplayScreen();
  }

  // z axsis
  if (readerZ.measureAttached)  {
    readerZ.update();
    if (readerZ.valueChanged) {
      drawReader(&readerZ, &posZ);
      readerZ.valueChanged = false;
    }
  }else if (readerZ.measureWasAttached) {
    initReaderDisplayPositions();
    initDisplayScreen();
  }

}



void buttonInterrupt() {
  detachInterrupt(2);
  intteruptFired = true;
}







