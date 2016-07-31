#define buttonPin A1
#define beastPin 7

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(beastPin, OUTPUT);
}

void loop() {
  int reading = analogRead(buttonPin);
  float voltage= reading * (5.0 / 1023.0);
  Serial.println(voltage);
  if(voltage  > 4.0){
    digitalWrite(beastPin, HIGH);
   while(true);
   //delay(20000);
  }
  delay(200);
}
