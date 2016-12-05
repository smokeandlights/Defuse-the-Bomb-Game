#include <Adafruit_NeoPixel.h>



#include <SevenSegmentExtended.h>
#include <SevenSegmentFun.h>
#include <SevenSegmentTM1637.h>

const byte PIN_CLK = 3;   // define CLK pin (any digital pin)
const byte PIN_DIO = 2;   // define DIO pin (any digital pin)
SevenSegmentExtended      countdown(PIN_CLK, PIN_DIO);


int minutes = 1;
int startTime = ((minutes * 600) + 1);
int winner = 0;
int wires[] = {A0, A1, A2};
int buzzer = A3;
int pitch = 100;
bool youWIN = false;
bool youLOSE = false;
int randNumber = 0;
int ledPIN = 4;
int ledoff = 0; //led switch cases
int ledarmed = 1;
int ledwin = 2;
int ledlose = 3;
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;

//Countdown Timer stuff, so it's available elswhere
static unsigned long timer = millis();
static int deciSeconds = startTime;

Adafruit_NeoPixel led = Adafruit_NeoPixel(1, ledPIN, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);     //Comment out the LEDs if you uncomment this.

  countdown.begin();            // initializes the display
  countdown.setBacklight(100);  // set the brightness to 100 %
  countdown.setColonOn(true);
  countdown.setCursor(0, 1);

  led.begin();


  randomSeed(analogRead(A5));//floating analog pin
  randNumber = random(0, 3);
  winner = wires[randNumber];

  Serial.print("randNumber: "); //This won't work unless you
  Serial.println(randNumber);   //comment out the LED functions in setup
  Serial.print("winner: ");     //AND UNCOMMENT the Serial.begin command.
  Serial.println(winner);       //
}

void loop() {
  smartLED(ledarmed);
  if (youWIN == false && youLOSE == false) {


    if (digitalRead(winner) == LOW) {
      YOUWON();

    }
    else {
      if (winner == A0) {
        if (digitalRead(A1 ) == LOW || digitalRead(A2) == LOW) {
          YOULOST();
        }
      }
      if (winner == A1) {
        if (digitalRead(A0 ) == LOW || digitalRead(A2) == LOW) {
          YOULOST();
        }
      }
      if (winner == A2) {
        if (digitalRead(A0 ) == LOW || digitalRead(A1) == LOW) {
          YOULOST();
        }
      }
    }


   void loop() {
  if (youWIN == false && youLOSE == false) {
    for (int i = 1; i > 0; i--) {
      for (int minutes = (startTime - 1); minutes >= 00; minutes--) {
        for (int seconds = 59; seconds >= 00; seconds--) {
          int currentMillis = millis();
          if (currentMillis >= (previousMillis + 10)) {
            previousMillis = currentMillis;
            currentMillis = millis();
            for (int hundreths = 99; hundreths >= 00; hundreths --) {

              if (minutes >= 1) {
                Serial.print(minutes);
                Serial.print(":");
                Serial.println(seconds);
              }
              if (minutes == 0) {
                if (hundreths == 0) {
                  youLOSE = true;
                  Serial.print("TIMES UP, BOOM!");
                  break;
                }

                if (hundreths <= 9) {
                  Serial.print(seconds);
                  Serial.print(":0");
                  Serial.println(hundreths);
                }
                else {
                  Serial.print(seconds);
                  Serial.print(":");
                  Serial.println(hundreths);
                }
              }
            }
          }
        }
      }
    }
  }
}

    else {
      YOULOST();
    }
  }
}

void winTUNE() {//mario 1-up
  tone(buzzer, 659, 120);//E5
  tone(buzzer, (659 / 2), 120);
  delay(120);//try to eliminate the delays and extend the notes - which sounds better?
  tone(buzzer, 784, 120);//G5
  delay(130);
  tone(buzzer, 1397, 120);//F6
  delay(130);
  tone(buzzer, 1175, 120);//D6
  delay(130);
  tone(buzzer, 1319, 120);//E6
  delay(130);
  tone(buzzer, 1760, 120);//A6
}

void YOUWON() {
  digitalWrite(winner, LOW);     // Once the wire is cut, it's cut.
  smartLED(ledwin);
  youWIN = true;
  Serial.print("YOU WIN!");
  countdown.print(deciSeconds - 1);
  winTUNE();
}

void YOULOST() {
  youLOSE = true;
  smartLED(ledlose);
  Serial.print("YOU LOST!");
  countdown.setColonOn(false);
  countdown.print("LOSE");
  tone(buzzer, pitch, 2000);

}
void smartLED(int i) {
  //"neopixel" led showing different colors & patterns for different conditions
  int ledState = (0, 0, 0);
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  unsigned int rate = 500;  //armed blink rate is 2Hz
  if (deciSeconds <= 300) {     //armed blink rate under 30 seconds
    rate = 250;                 //is 4Hz
  }

  switch (i) {
    case 0:
      // off: dark
      led.setPixelColor(0, (0, 0, 0));
      led.show();

    case 1:

      // armed: blinking yellow

      if (currentMillis - previousMillis >= rate) {
        if (ledState == (0, 0, 0)) {
          ledState = (127, 127, 0);
        } else {
          ledState = (0, 0, 0);
        }
      }
      led.setPixelColor(0, ledState);
      led.show();

    case 2:
      // win: full green
      led.setPixelColor(0, (0, 255, 0));
      led.show();

    case 3:
      // lose:full red
      led.setPixelColor(0, (255, 0, 0));
      led.show();
  }

}
