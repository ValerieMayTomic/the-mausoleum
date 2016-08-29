#define lightPin 7
#define lockPin 2
#define piezoPin A0

const int ROUNDS = 4; //total number of rounds
const int curr_lights[] = {2, 3, 1, 3}; //array representing pattern of lights to blink
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
  if(curr_round-1 == ROUNDS){ //puzzle complete
    digitalWrite(lockPin, LOW); //release maglock
    digitalWrite(lightPin, HIGH); //turn on tail lights
    while(true);
  }
  else{
    blinkLights(lightPin, curr_lights[curr_round-1]); //blink lights based on current round and light pattern array
    unsigned long t = millis();
    int pre_knock_round = curr_round;
    while(millis() - t < 4000 && curr_round == pre_knock_round){//wait 4 seconds for player to knock
      if(knocks(curr_lights[curr_round-1])){//if correc number of knocks detected
       delay(500);
       curr_round++; //move on to next round
      }
    }
  }
}

/*
 * function blinks lights in appropriate rythm, 
 * using specified pin and number of reps
 */
void blinkLights(int pin, int times){
  for(int i=0;i<times;i++){
    digitalWrite(pin, HIGH);
    delay(150);
    digitalWrite(pin, LOW);
    delay(700);
  }
}

/*
 * A recursive function that returns true if the correct number of
 * distinct knocks are detected by the piezo consecutively, and
 * false otherwise
 */
boolean knocks(int reps){
  if(reps == 0){
    delay(50);
    return(true);
  }
  else{
    unsigned long t = millis();
    while(millis() - t < 1000){//wait one second for another knock to be dtected
      // Read Piezo ADC value in, and convert it to a voltage
      int piezoADC = analogRead(piezoPin);
      float piezoV = piezoADC / 1023.0 * 5.0;
      if(piezoV > 0.1){
        delay(500);
        return(knocks(reps-1));//if knock detected, recur with one less rep
      }
    }
    //return false if one second passes without a knock, and reps isn't yet to zero
    return(false); 
  }
}


