#define lightPin 7
#define lockPin 2
#define piezoPin A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lightPin, OUTPUT);
  pinMode(lockPin, OUTPUT);
}

void loop() {
  blinkLights(lightPin, 3);
  delay(1000);
  blinkLights(lightPin, 1);
  delay(1000);
  blinkLights(lightPin, 2);

unsigned long t = millis();
while(millis() - t < 5000){
  if(knocks(3)){
    if(knocks(1)){
      if(knocks(2)){
        digitalWrite(lockPin, HIGH);
        delay(10000);
      }
    }
  }
}
  digitalWrite(lockPin, LOW);
}

void blinkLights(int pin, int times){
  for(int i=0;i<times;i++){
    digitalWrite(pin, HIGH);
    delay(200);
    digitalWrite(pin, LOW);
    delay(200);
  }
}

boolean knocks(int reps){
  if(reps == 0){
    Serial.println("DONE");
    delay(50);
    return(true);
  }
  else{
    //boolean knocked = false;
    unsigned long t = millis();
    while(millis() - t < 1000){
      // Read Piezo ADC value in, and convert it to a voltage
      int piezoADC = analogRead(piezoPin);
      float piezoV = piezoADC / 1023.0 * 5.0;
      //Serial.println(piezoV); // Print the voltage.
      if(piezoV > 0.2){
        Serial.println("KNOCK!!!!!!!!!!");
        Serial.println(reps);
        delay(500);
        return(knocks(reps-1));
      }
    }
    return(false);
  }
}
