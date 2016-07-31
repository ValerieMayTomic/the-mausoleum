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
const int LED_PIN = 8; //LED control

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
  Serial.println(piezoV); // Print the voltage.
  unsigned long last_time = millis();
  if(piezoV > 0.05){
  delay(50);
    while(millis() - last_time < 1000){
      piezoADC = analogRead(PIEZO_PIN);
      piezoV = 3 + (piezoADC / 1023.0 * 5.0);
      //Serial.println("waiting for second knock");
      Serial.println(piezoV); // Print the voltage.
      if(piezoV > 3.05){
        if(digitalRead(LED_PIN)==LOW){
          digitalWrite(LED_PIN, HIGH);
        }
        else{
          digitalWrite(LED_PIN, LOW);
        }
          delay(500);
      }
    }
 delay(100);
  }
}


