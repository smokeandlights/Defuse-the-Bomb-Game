int winLED = 0;
int boomLED = 1;

#include "SevSeg.h"

SevSeg sevseg;

void setup() {
  // put your setup code here, to run once:
pinMode(winLED, OUTPUT);
pinMode(boomLED, OUTPUT);

//Countdown Timer stuff

 byte numDigits = 4;   
 byte digitPins[] = {2, 3, 4, 5};
 byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);

  //Randomizing the chosen Wire
  randomSeed(analogRead(A5));//floating analog pin
  unsigned int randNumber;
  randNumber = random(0,2);
  int wires[]= {A0,A1,A2};
  int winner = wires[randNumber];
  
  
  Serial.begin(9600);

  Serial.print(winner);
}

void loop() {
  if (digitalRead(wires[randNumber])==LOW){
    
  }
 
}
