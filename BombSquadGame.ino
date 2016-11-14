#include "SevSeg.h"
SevSeg sevseg;

int winLED = 1;
int boomLED = 0;
int minutes = 1;
int startTime = ((minutes *600)+1);
int winner=0;
int wires[]= {14,15,16};

//Countdown Timer stuff, so it's available elswhere
static unsigned long timer = millis();
static int deciSeconds = startTime; 

void setup() {
//    Serial.begin(9600);     //Comment out the LEDs if you uncomment this.
    
    pinMode(winLED, OUTPUT);  //Comment these 4 lines about LEDs out if you want to enable Serial
    pinMode(boomLED, OUTPUT); //functions . They interfere with each other.
    digitalWrite(winLED,LOW); //
    digitalWrite(boomLED,LOW);//
       
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
            
            Serial.print("randNumber: "); //This won't work unless you 
            Serial.println(randNumber);   //comment out the LED functions in setup
            Serial.print("winner: ");     //AND UNCOMMENT the Serial.begin command.
            Serial.println(winner);       //
                  }
           if(winner==14){
            if (digitalRead(15 )==LOW||digitalRead(16)==LOW){
              deciSeconds=0;
              digitalWrite(boomLED, HIGH);
              sevseg.setNumber(8888,5);
              sevseg.refreshDisplay();
            }
            if (digitalRead(14)==LOW){
            digitalWrite(winLED,HIGH);
            sevseg.setNumber(deciSeconds-1, 1);
            sevseg.refreshDisplay();
     }
           }
          if(winner==15){
            if (digitalRead(14 )==LOW||digitalRead(16)==LOW){
              deciSeconds=0;
              digitalWrite(boomLED, HIGH);
              sevseg.setNumber(8888,5);
              sevseg.refreshDisplay();
            }
                if (digitalRead(15)==LOW){
            digitalWrite(winLED,HIGH);
            sevseg.setNumber(deciSeconds-1, 1);
            sevseg.refreshDisplay();
                  }
           }
           if(winner==16){
            if (digitalRead(14 )==LOW||digitalRead(15)==LOW){
              deciSeconds=0;
              digitalWrite(boomLED, HIGH);
              sevseg.setNumber(8888,5);
              sevseg.refreshDisplay();
                }
            if (digitalRead(16)==LOW){
              digitalWrite(winLED,HIGH);
              sevseg.setNumber(deciSeconds-1, 1);
              sevseg.refreshDisplay();
                }
           }    
 else {
//     static unsigned long timer = millis();
//     static int deciSeconds = startTime; 
   
  
    
    if(deciSeconds>=0){
      if (millis() >= timer) {
        deciSeconds--; // 100 milliSeconds is equal to 1 deciSecond
        timer += 100; 
         
        sevseg.setNumber(deciSeconds, 1);
      }
      sevseg.refreshDisplay();
    }
    else{
     digitalWrite(boomLED,HIGH);
     sevseg.setNumber(8888, 5);
     sevseg.refreshDisplay();
     }   
    
 sevseg.refreshDisplay();
 }
 }
