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
int wires[] = {14, 15, 16};
int buzzer = A3;
int pitch = 100;
bool youWIN = false;

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

  //Countdown Timer stuff
  //
  //  byte numDigits = 4;
  //  byte digitPins[] = {2, 3, 4, 5};
  //  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  //
  //  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  //  sevseg.setBrightness(90);

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
  if (winner == 14) {
    if (digitalRead(15 ) == LOW || digitalRead(16) == LOW) {
      deciSeconds = 0;
      digitalWrite(boomLED, HIGH);
      tone(buzzer, pitch, 500);
      Serial.print("YOU LOST!"); // replaces LED function when Serial is enabled
      countdown.print(8888);
      deciSeconds = 8888;
      //      sevseg.setNumber(8888, 5);
      //      sevseg.refreshDisplay();
    }
    if (digitalRead(14) == LOW) {
      digitalWrite(14, LOW);      // Once the wire is cut, it's cut.
      digitalWrite(winLED, HIGH);
      youWIN = true;
      Serial.print("YOU WIN!"); // replaces LED function when Serial is enabled
      countdown.print(deciSeconds - 1);
      //      sevseg.setNumber(deciSeconds - 1, 1);
      //      sevseg.refreshDisplay();
    }
  }
  if (winner == 15) {
    if (digitalRead(14 ) == LOW || digitalRead(16) == LOW) {
      deciSeconds = 0;
      digitalWrite(boomLED, HIGH);
      tone(buzzer, pitch, 500);
      Serial.print("YOU LOST!"); // replaces LED function when Serial is enabled
      countdown.print(8888);
      deciSeconds = 8888;
      //      sevseg.setNumber(8888, 5);
      //      sevseg.refreshDisplay();
    }
    if (digitalRead(15) == LOW) {
      digitalWrite(15, LOW);      // Once the wire is cut, it's cut.
      digitalWrite(winLED, HIGH);
      youWIN = true;
      Serial.print("YOU WIN!"); // replaces LED function when Serial is enabled
      countdown.print(deciSeconds - 1);
      //      sevseg.setNumber(deciSeconds - 1, 1);
      //      sevseg.refreshDisplay();
    }
  }
  if (winner == 16) {
    if (digitalRead(14 ) == LOW || digitalRead(15) == LOW) {
      deciSeconds = 0;
      digitalWrite(boomLED, HIGH);
      tone(buzzer, pitch, 500);
      Serial.print("YOU LOST!"); // replaces LED function when Serial is enabled
      countdown.print(8888);
      deciSeconds = 8888;
      //      sevseg.setNumber(8888, 5);
      //      sevseg.refreshDisplay();
    }
    if (digitalRead(16) == LOW) {
      digitalWrite(16, LOW);     // Once the wire is cut, it's cut.
      digitalWrite(winLED, HIGH);
      youWIN = true;
      Serial.print("YOU WIN!"); // replaces LED function when Serial is enabled
      countdown.print(deciSeconds - 1);
      //      sevseg.setNumber(deciSeconds - 1, 1);
      //      sevseg.refreshDisplay();
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
            //sevseg.setNumber(deciSeconds, 1);
          }
          //        sevseg.refreshDisplay();
        }
      }
      else {
        digitalWrite(boomLED, HIGH);
        tone(buzzer, pitch, 500);
        deciSeconds = 8888;
        countdown.print(8888);
        //        sevseg.setNumber(8888, 5);
        //        sevseg.refreshDisplay();
      }
      //      sevseg.refreshDisplay();
    }
  }
}
