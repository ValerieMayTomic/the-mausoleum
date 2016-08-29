
int sunPin = 9;
int sunInitialBrightness = 110;
int sunBrightness = sunInitialBrightness;

void setup() {
  Serial.begin(9600);
  pinMode(sunPin, OUTPUT);
}

void loop() {
  //increase sunbrightness slowly until it reaches max
  while(sunBrightness<255){
    analogWrite(sunPin, sunBrightness);
    sunBrightness = sunBrightness+1;
    delay(19200);
  }
}
