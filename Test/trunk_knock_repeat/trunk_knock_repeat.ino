#define lightPin 7
#define lockPin 2
#define piezoPin A0

const int ROUNDS = 4; //total number of rounds
const int curr_lights[] = {2, 3, 1, 3};
int curr_round;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(lightPin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH);
  curr_round = 1;
}

void loop() 
{
  //Serial.println("ROUND:");
  //Serial.println(curr_round);
  if(curr_round-1 == ROUNDS){
    digitalWrite(lockPin, LOW);
    digitalWrite(lightPin, HIGH);
    while(true);
  }
  else{
    //Serial.println("Blinking:");
    //Serial.println(curr_lights[curr_round-1]);
    blinkLights(lightPin, curr_lights[curr_round-1]);
    unsigned long t = millis();
    Serial.println("Waiting on knocks");
    int pre_knock_round = curr_round;
    while(millis() - t < 4000 && curr_round == pre_knock_round){
      if(knocks(curr_lights[curr_round-1])){
       delay(500);
       curr_round++;
      }
    }
  }
}

void blinkLights(int pin, int times){
  for(int i=0;i<times;i++){
    digitalWrite(pin, HIGH);
    delay(150);
    digitalWrite(pin, LOW);
    delay(700);
  }
}

boolean knocks(int reps){
  if(reps == 0){
    //Serial.println("DONE");
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
     Serial.println(piezoV); // Print the voltage.
      if(piezoV > 0.1){
      //  Serial.println("KNOCK!!!!!!!!!!");
      //  Serial.println(reps);
        delay(500);
        return(knocks(reps-1));
      }
    }
    return(false);
  }
}


