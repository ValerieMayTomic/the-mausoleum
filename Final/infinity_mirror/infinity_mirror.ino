#define buttonPin A1
#define beastPin 7

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); //button pin init
  pinMode(beastPin, OUTPUT); //mirror pin init
}

void loop() {
  int reading = analogRead(buttonPin); //read analog value
  float voltage= reading * (5.0 / 1023.0); //convert to voltage
  if(voltage  > 4.0){ //turn mirror on if voltage goes above 4
    digitalWrite(beastPin, HIGH);
   while(true); //loop until hard reset
  }
  delay(200);
}
