#include "SevSeg.h"
SevSeg sevseg;

int winLED = 1;
int boomLED = 0;
int minutes = 1;
int startTime = ((minutes *600)+1);
int winner=0;
int wires[]= {14,15,16};
  
void setup() {
//    Serial.begin(9600);
    
    pinMode(winLED, OUTPUT);
    pinMode(boomLED, OUTPUT);
    digitalWrite(winLED,LOW);
    digitalWrite(boomLED,LOW);
//    
    //Countdown Timer stuff
     
     byte numDigits = 4;   
     byte digitPins[] = {2, 3, 4, 5};
     byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    
     sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
     sevseg.setBrightness(90);

     }
          
void loop() {
  if(millis()<= 5){
    int randNumber;
    randomSeed(analogRead(A5));//floating analog pin
    randNumber = random(0,3);
    winner = wires[randNumber];
            
//    Serial.print("randNumber: ");
//    Serial.println(randNumber);
//    Serial.print("winner: ");
//    Serial.println(winner);
          }
//           if(winner==14){
//            if (digitalRead(15 )||digitalRead(16)==LOW){
//              digitalWrite(boomLED, HIGH);
//              sevseg.setNumber(8888,5);
//              sevseg.refreshDisplay();
//            }
//           }
//          if(winner==15){
//            if (digitalRead(14 )||digitalRead(16)==LOW){
//              digitalWrite(boomLED, HIGH);
//              sevseg.setNumber(8888,5);
//              sevseg.refreshDisplay();
//            }
//           }
//           if(winner==16){
//            if (digitalRead(14 )||digitalRead(15)==LOW){
//              digitalWrite(boomLED, HIGH);
//              sevseg.setNumber(8888,5);
//              sevseg.refreshDisplay();
//            }
//           }
//           
//  if (digitalRead(wires[winner])==LOW){
//    digitalWrite(winLED,HIGH);
//    sevseg.setNumber(0, 5);
//    sevseg.refreshDisplay();
//     }
//    
// else {
     static unsigned long timer = millis();
     static int deciSeconds = startTime; 
    if(deciSeconds>=0){
      if (millis() >= timer) {
        deciSeconds--; // 100 milliSeconds is equal to 1 deciSecond
        timer += 100; 
            // if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
            // deciSeconds=0;
            //}
        sevseg.setNumber(deciSeconds, 1);
      }
      sevseg.refreshDisplay(); // Must run repeatedly
    }
    else{
     digitalWrite(boomLED,HIGH);
     sevseg.setNumber(8888, 5);
     sevseg.refreshDisplay();
     }   
 }
//}
