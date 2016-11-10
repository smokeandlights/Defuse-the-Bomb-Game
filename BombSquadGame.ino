const int wire1=3;
const int wire2=8;
const int wire3=13;
const int safeLED=7;
const int warningLED=11;
const int boomLED=2;

void setup() {
  // put your setup code here, to run once:
pinMode(safeLED, OUTPUT);
pinMode(warningLED, OUTPUT);
pinMode(boomLED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

long randNumber;

void setup(){
  Serial.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {
  // print a random number from 0 to 299
  randNumber = random(300);
  Serial.println(randNumber);  

  // print a random number from 1 to 3
  randNumber = random(1, 4);
  Serial.println(randNumber);

  delay(50);
}
}
