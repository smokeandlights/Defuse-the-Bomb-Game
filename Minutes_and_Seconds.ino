
int startTime = 1;


bool youWIN = false;
bool youLOSE = false;

int previousMillis = 0;

void setup() {
  Serial.begin(9600);

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
