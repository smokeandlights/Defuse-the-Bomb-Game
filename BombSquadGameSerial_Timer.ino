#include <SevenSegmentExtended.h>
#include <SevenSegmentFun.h>
#include <SevenSegmentTM1637.h>

const byte PIN_CLK = 3;   // define CLK pin (any digital pin)
const byte PIN_DIO = 2;   // define DIO pin (any digital pin)
SevenSegmentExtended      countdown(PIN_CLK, PIN_DIO);

//#include <SevSeg.h>

//SevSeg sevseg;

int winLED = 1;
int boomLED = 0;
int minutes = 1;
int startTime = ((minutes * 600) + 1);
int winner = 0;
int wires[] = {A0, A1, A2};
int buzzer = A3;
int pitch = 100;
bool youWIN = false;
bool youLOSE = false;


//Countdown Timer stuff, so it's available elswhere
static unsigned long timer = millis();
static int deciSeconds = startTime;

void setup() {
  Serial.begin(9600);     //Comment out the LEDs if you uncomment this.

  countdown.begin();            // initializes the display
  countdown.setBacklight(100);  // set the brightness to 100 %
  countdown.setColonOn(true);
  countdown.setCursor(0, 1);
  pinMode(winLED, OUTPUT);  //Comment these 4 lines about LEDs out if you want to enable Serial
  pinMode(boomLED, OUTPUT); //functions . They interfere with each other.
  digitalWrite(winLED, LOW); //
  digitalWrite(boomLED, LOW); //

}

void loop() {

  if (millis() <= 5) {
    int randNumber;
    randomSeed(analogRead(A5));//floating analog pin
    randNumber = random(0, 3);
    winner = wires[randNumber];

    Serial.print("randNumber: "); //This won't work unless you
    Serial.println(randNumber);   //comment out the LED functions in setup
    Serial.print("winner: ");     //AND UNCOMMENT the Serial.begin command.
    Serial.println(winner);       //
  }
  if (winner == A0) {
    if (digitalRead(A1 ) == LOW || digitalRead(A2) == LOW) {
     YOULOST();
    }
    if (digitalRead(A0) == LOW) {
     YOUWON()
    }
  }
  if (winner == A1) {
    if (digitalRead(A0 ) == LOW || digitalRead(A2) == LOW) {
     YOULOST();
    }
    if (digitalRead(A1) == LOW) {
    YOUWON()
    }
  }
  if (winner == A2) {
    if (digitalRead(A0 ) == LOW || digitalRead(A1) == LOW) {
     YOULOST();
    }
    if (digitalRead(A2) == LOW) {
     YOUWON()
    }
  }
  else {
    if (youWIN == false) {
      if (deciSeconds >= 0) {
        if (deciSeconds != 8888) {
          if (millis() >= timer && millis() > 0) {
            deciSeconds--;
            timer += 100;
            countdown.print(deciSeconds);
          
          }
        }
      }
      else {
        YOULOST();
             }
          }
  }
}
void YOUWON(){
   digitalWrite(winner, LOW);     // Once the wire is cut, it's cut.
   digitalWrite(winLED, HIGH);
   youWIN = true;
   Serial.print("YOU WIN!"); // replaces LED function when Serial is enabled
   countdown.print(deciSeconds - 1);
}
void YOULOST(){
  youLOSE = true;
  digitalWrite(boomLED, HIGH);
  tone(buzzer, pitch, 500);
  Serial.print("YOU LOST!"); // replaces LED function when Serial is enabled
  countdown.print(8888);
  deciSeconds = 8888;
}
