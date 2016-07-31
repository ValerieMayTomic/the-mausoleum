#define voltPin A5
#define lockPin 8

int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(voltPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
  if(voltage > 2.0)
    counter++;
  if(counter > 7){
    digitalWrite(lockPin, LOW);
    //while(true);
  }
  delay(100);

}
