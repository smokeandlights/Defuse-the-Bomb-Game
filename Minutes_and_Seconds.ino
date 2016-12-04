#include <SevenSegmentExtended.h>
#include <SevenSegmentFun.h>
#include <SevenSegmentTM1637.h>

int startTime = 5;


bool youWIN = false
              bool youLOSE = false

void setup() {
  Serial.begin(9600);
}
void loop() {
  if (youWIN == false && youLOSE == false) {
    for (int minutes = startTime; minutes >= 00; Minutes--) {
      for (int seconds = 59; seconds >= 00; seconds--) {
        for (int hundreths = 99; int hundreths >= 00; int hundreths --) {
          if (minutes >= 1) {
            Serial.println(minutes);
            Serial.print(":");
            Serial.print(seconds);
          }
          if (minutes == 0) {
            Serial.println(seconds);
            Serial.print(":");
            Serial.print(hundreths);
          }
          else {
            youLOSE = true;
            Serial.print("TIMES UP, BOOM!");
          }
        }
      }

