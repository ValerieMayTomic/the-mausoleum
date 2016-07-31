
int sunPin = 9;
int sunInitialBrightness = 125;
int sunBrightness = sunInitialBrightness;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sunPin, OUTPUT);
}

void loop() {
    //  digitalWrite(sunPin, HIGH);
    //  delay(5000);
    //  digitalWrite(sunPin, LOW);
    //  delay(5000);
    //Serial.println(sunBrightness);
  while(sunBrightness<255){
    analogWrite(sunPin, sunBrightness);
    sunBrightness = sunBrightness+1;
    Serial.println(sunBrightness);
    delay(19200); //1800
  }
      
     // digitalWrite(sunPin, HIGH);
      //delay(2000); 

}
