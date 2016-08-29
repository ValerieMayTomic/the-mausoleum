#define voltPin A5
#define lockPin 8

int counter = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(lockPin, OUTPUT);
  pinMode(voltPin, INPUT);
  digitalWrite(lockPin, HIGH);

}

void loop() {
  int sensorValue = analogRead(voltPin); //read analog value
  float voltage = sensorValue * (5.0 / 1023.0); //convert to voltage
  if(voltage > 0.4){ //increase counter if voltage greater than .4
    counter++;
  }
  if(counter > 7){ //open lock if counter goes above 7
    digitalWrite(lockPin, LOW);
    counter = 0; //reset counter
  }
    if(voltage < 0.4){ //if voltage not above .4, reset counter
    counter = 0;
    digitalWrite(lockPin, HIGH);
  }
  delay(100);

}
