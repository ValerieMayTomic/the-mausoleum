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
const int PIEZO_PIN = A5; // Piezo output
const int LED_PIN = 7; //LED control
const int samples = 5;

int counter = 0;
float avgs[] = {0.0,0.0,0.0,0.0,0.0};
float average = 0.0;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  int piezoADC = analogRead(PIEZO_PIN);
  float piezoV = piezoADC / 1023.0 * 5.0;
//  if(counter < samples){
//    avgs[counter] = piezoV;
//    counter++;
//  }
//  else if(counter == samples){
//    float sum = 0.0;
//    for(int i=0;i<counter; i++){
//      sum = sum + avgs[i];
//    }
//    average = sum/counter;
    Serial.println(piezoV); // Print the voltage.
    if(piezoV > 0.1){
      if(digitalRead(LED_PIN) == HIGH){
        digitalWrite(LED_PIN, LOW);
      }
      else{
        digitalWrite(LED_PIN, HIGH);
      }
      delay(100);
    }
//    average = 0.0;
//    counter = 0;
//  }
//  delay(10);
}


