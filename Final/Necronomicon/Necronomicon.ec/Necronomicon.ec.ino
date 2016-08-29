/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */

int led0 = 8;           //Top light LED is on constantly

int led1 = 9;           // the PWM pin the LED is attached to
int led2 = 10;
int led3 = 11;
int brightness = 0;     // how bright the LED is
int fadeAmount = 5;     // how many points to fade the LED by

int maglock = 12;        //output connects maglock ground line to ground
int hallsensor = 13;      //hall sensor/transistor senses keystone
int foo = 0;

void setup() {
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(hallsensor, INPUT_PULLUP);
  pinMode(maglock, OUTPUT);

  digitalWrite(led0, HIGH);

  //Serial.begin(4800);
}

void loop() {
  
  analogWrite(led1, brightness);
    delay(10);
  analogWrite(led1, -brightness);
   delay(10);
  analogWrite(led2, brightness);
    delay(20);
  analogWrite(led2, -brightness);
   delay(20);
  analogWrite(led3, brightness);
    delay(30);
  analogWrite(led3, -brightness);
   delay(30);
   
  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }

  //check to see if the state of the hall sensor has changed
if(digitalRead(hallsensor) == LOW){
  delay(1000);
  digitalWrite(maglock, LOW);
  foo = 1;
}
else{
  digitalWrite(maglock, HIGH);
  foo = 0;
}

// If you want to diagnose:
  //Serial.print(foo);
  //Serial.println();

}
