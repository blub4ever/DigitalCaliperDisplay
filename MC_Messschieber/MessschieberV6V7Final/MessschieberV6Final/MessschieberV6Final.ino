#include "DisplayUnit.h"
#include "Reader.h"

#include <openGLCD.h>
#include <include/openGLCD_GLCDv3.h>

#include "Arial18.h"         // system and arial14 fonts are used
#include "Arial28.h"         // system and arial14 fonts are used
#include "Arial38.h"         // system and arial14 fonts are used
#include "Arial_bold_14.h"       // all images in the bitmap dir 
#include "SystemFont5x7.h"

/** Reader timout in ms, one cycle should be done in < 120 ms **/
#define READER_TIME_OUT 500


/** max and min coordiantes of the display **/
#define DISPLAY_X_MAX 128
#define DISPLAY_Y_MAX 64






/** Three calipers attached **/
#define THREE_X_START 40
#define THREE_Y_START_1 2
#define THREE_Y_START_2 22
#define THREE_Y_START_3 42

#define THREE_X_START_UNIT_1 110
#define THREE_Y_START_UNIT_1 4
#define THREE_X_START_UNIT_2 110
#define THREE_Y_START_UNIT_2 24
#define THREE_X_START_UNIT_3 110
#define THREE_Y_START_UNIT_3 44

#define THREE_X_START_NAME_1 4
#define THREE_Y_START_NAME_1 4
#define THREE_X_START_NAME_2 4
#define THREE_Y_START_NAME_2 24
#define THREE_X_START_NAME_3 4
#define THREE_Y_START_NAME_3 44

#define THREE_CHAR_HIGHT 12
#define THREE_POINT_WIDTH 2
#define THREE_CHAR_WIDTH 8

#define THREE_MAX_CHARS 7


/** TWO calipers attached **/
#define TWO_X_START 10
#define TWO_Y_START_1 5
#define TWO_Y_START_2 35

#define TWO_X_START_UNIT_1 114
#define TWO_Y_START_UNIT_1 16
#define TWO_X_START_UNIT_2 114
#define TWO_Y_START_UNIT_2 46

#define TWO_X_START_NAME_1 114
#define TWO_Y_START_NAME_1 7
#define TWO_X_START_NAME_2 114
#define TWO_Y_START_NAME_2 37

#define TWO_POINT_WIDTH 2
#define TWO_CHAR_WIDTH 13
#define TWO_CHAR_HIGHT 20

#define TWO_MAX_CHARS 7


/** One caliper attached **/
#define ONE_X_START 3
#define ONE_Y_START 25

#define ONE_POINT_WIDTH 4
#define ONE_CHAR_WIDTH 17
#define ONE_CHAR_HIGHT 27

#define ONE_MAX_CHARS 7
 
#define ONE_X_START_UNIT 100
#define ONE_Y_START_UNIT 2

#define ONE_X_START_NAME 2
#define ONE_Y_START_NAME 2


// font for description
#define DRAW_DESCRIPTION_FONT_MEDIUM Arial_bold_14
#define DRAW_DESCRIPTION_FONT_SMALL System5x7

// font for measurement
#define DRAW_CALIPER_FONT_BIG Arial38
#define DRAW_CALIPER_FONT_MEDIUM Arial28
#define DRAW_CALIPER_FONT_SMALL Arial18

//x = 23 & port 1 = interrupt 3
Reader readerX(23);
DisplayUnit unitX;

//y = 13 & port 2 = interrupt 1
Reader readerY(13);
DisplayUnit unitY;

//z = 17 & port 3 = interrupt 0
Reader readerZ(17);
DisplayUnit unitZ;

const uint8_t* unitFont = Arial_bold_14;

const uint8_t* descritionFont = Arial_bold_14;

const uint8_t* caliperFont = Arial18;

boolean intteruptFired = false;
long intteruptBounceTime = 0;

const char  welcome_1[] PROGMEM  = {"Welcome"};
const char  welcome_2[] PROGMEM  = {"Caliper Display"};
const char  welcome_3[] PROGMEM  = {"by A. Glatz"};
const char  welcome_4[] PROGMEM  = {"v0.6f"};

const char  attach_1[] PROGMEM  = {"Please"};
const char  attach_2[] PROGMEM  = {"attach caliper!"};

long timeSec = 0;
long timeSec2 = 0;
boolean pleaseAttachDrawn = false;


// int 0 = d3
// int 1 = d2
// int 2 = d0
// int 3 = d1

void setup() {
  // begin serial
  Serial.begin(9600);
  Serial.println("Starte");
  //Initialize the GLCD
  GLCD.Init();
   
  drawWelcome();
  
  delay(1000);
  
  readerX.init(3,interX);
  readerY.init(1,interY);
  readerZ.init(0,interZ);
  
  drawPleaseAttach();
  pleaseAttachDrawn = true;

  Serial.println("Starte 2");
  delay(500);
}



void loop() {

Serial.println("Starte");
    
    if(millis()- timeSec > 1000){
      if(updateDisplay()){
        //Serial.println("update");
        
         if(readerX.cAttached | readerY.cAttached | readerZ.cAttached){
            drawMeasurmentScale();
        
            if(readerX.cAttached)
              drawReader(&readerX, &unitX, true);
            if(readerY.cAttached)
              drawReader(&readerY, &unitY, true);  
            if(readerZ.cAttached)
              drawReader(&readerZ, &unitZ, true); 
            pleaseAttachDrawn =false;
         }else{
            if(!pleaseAttachDrawn){
              drawPleaseAttach();
              pleaseAttachDrawn = true;
            }  
         }
         
          
        timeSec = millis();
      }
    }
    
   
    if(!pleaseAttachDrawn){
      if(millis()- timeSec2 > 50){
   
          if(readerX.valueChanged && readerX.cAttached) {
            drawReader(&readerX, &unitX,false);
            readerX.valueChanged = false;
          }
    
          if (readerY.valueChanged && readerY.cAttached) {
            drawReader(&readerY, &unitY,false);
            readerY.valueChanged = false;
          }
       
          if (readerZ.valueChanged && readerZ.cAttached) {
            drawReader(&readerZ, &unitZ,false);
            readerZ.valueChanged = false;
          }
          
        timeSec2 = millis();
      }
    }
}

void interX() {
  readerX.update();
}

void interY(){
  readerY.update();
}

void interZ(){
  readerZ.update();
}

