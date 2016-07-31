/******************************************************************************
Piezo_Vibration_Sensor.ino
Example sketch for SparkFun's Piezo Vibration Sensor
  (https://www.sparkfun.com/products/9197)
Jim Lindblom @ SparkFun Electronics
April 29, 2016

- Connect a 1Mohm resistor across the Piezo sensor's pins.
- Connect one leg of the Piezo to GND
- Connect the other leg of the piezo to A0

Vibrations on the Piezo sensor create voltags, which are sensed by the Arduino's
A0 pin. Check the serial monitor to view the voltage generated.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int PIEZO_PIN = A0; // Piezo output
const int BLINK_PIN = 8; //LED control
const int END_PIN = 10; //LED control

const int ROUNDS = 3; //total number of rounds
int curr_round;

void setup() 
{
  Serial.begin(9600);
  pinMode(BLINK_PIN, OUTPUT);
  pinMode(END_PIN, OUTPUT);
  curr_round = 1;
}

void loop() 
{
  if(curr_round-1 == ROUNDS){
    digitalWrite(END_PIN, HIGH);
    delay(10000);
    digitalWrite(END_PIN, LOW);
    curr_round = 1;
  }
  else{
    Serial.println("Blinking");
    blinkLights(BLINK_PIN, curr_round);
    unsigned long t = millis();
    Serial.println("Waiting on knocks");
    while(millis() - t < 4000){
      if(knocks(curr_round)){
       delay(500);
       curr_round++;
      }
    }
  }
}

void blinkLights(int pin, int times){
  for(int i=0;i<times;i++){
    digitalWrite(pin, HIGH);
    delay(100);
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
      int piezoADC = analogRead(PIEZO_PIN);
      float piezoV = piezoADC / 1023.0 * 5.0;
      //Serial.println(piezoV); // Print the voltage.
      if(piezoV > 0.05){
        Serial.println("KNOCK!!!!!!!!!!");
        Serial.println(reps);
        delay(500);
        return(knocks(reps-1));
      }
    }
    return(false);
  }
}


