/*
Arduino Hall Effect Sensor Test
*/

#define x0 2
#define x1 3
#define x2 4
#define y0 5
#define y1 6
#define y2 7

 void setup()
 {
   Serial.begin(9600);
   pinMode(x0, INPUT_PULLUP);
   pinMode(x1, INPUT_PULLUP);
   pinMode(x2, INPUT_PULLUP);
   pinMode(y0, INPUT_PULLUP);
   pinMode(y1, INPUT_PULLUP);
   pinMode(y2, INPUT_PULLUP);
 }
 void loop()
 {
  if(digitalRead(x0) == 0){
    if(digitalRead(y0) == 0)
      Serial.println("1,1");
    if(digitalRead(y1) == 0)
      Serial.println("1,2");
    if(digitalRead(y2) == 0)
      Serial.println("1,3");
  }
  delay(200);
 }
