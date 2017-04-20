

// int 0 = d3
// int 1 = d2
// int 2 = d0
// int 3 = d1

void setup() {
  // begin serial
  Serial.begin(9600);

  delay(2000);
  Serial.println("Starte");


// X
 // attachInterrupt(3, interX, RISING);
 // pinMode(23, INPUT);

// Y
//attachInterrupt(1, interX, RISING);
//pinMode(13, INPUT);

// Z
attachInterrupt(0, interX, RISING);
 pinMode(17, INPUT);

}


long timeX = 0;
long resultX = 0;
int countX = 0;

volatile long resultXRDY = 0;

long timeY = 0;
long resultY = 0;
int countY = 0;
volatile long resultYRDY = 0;

volatile long timeSec = 0;


void loop() {
  if (millis() - timeSec > 1000) {
    timeSec = millis();

    char convert[9];
    dtostrf(((float)resultXRDY) / 100, 8, 2, convert);
    Serial.println(convert);
    resultXRDY= -44;
    //Serial.println(resultX);
  // resultX= 0;
    
  //  dtostrf(((float)resultYRDY) / 100, 8, 2, convert);
 //   Serial.println(convert);
  }
}





void interX() {
  cli();
  long mill = micros();

  if (mill - timeX > 100000) {
     if (countX >= 23) {
      timeX = mill;
      resultXRDY = resultX;
      resultX= 0;
      countX = 0;
    }else{
      
      int tmpRead = digitalRead(17) ;

      if (tmpRead == 1) {
        if (countX < 20)
          resultX |= 1 << countX;
        else if (countX == 20)
          resultX *= -1;
      }
      
       countX++;
    }
    
  }
  sei();
}
/*
void interX() {
  long mill = micros();
  if (mill - timeX > 100000) {
     if (countX >= 23) {
       timeX = mill;
       resultX++;
       countX = 0;
     }
    countX++;
   }
}*/

