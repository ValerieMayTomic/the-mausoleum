//LED library init
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED 13

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed
Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, LED, NEO_GRB + NEO_KHZ800);

//multiplexing pin init
#define x0 8
#define x1 9
#define x2 10
#define x3 11
#define x4 12
#define y0 3
#define y1 4
#define y2 5
#define y3 6
#define y4 7

//maze init
int move_num = 0;
int pos = 0;
//maze path coordinates array
int path[] = {2,1,0,15,14,23,16,17,18,3,4,5,6,19,24,21,22,13,12,11,10};
//bool array for lighting lights
boolean lit[] = {false, false, false, false, false, false, false, false, false, false,false, false, false, false, false,false, false, false, false, false, false, false, false, false, false};

void setup() {
  Serial.begin(9600);
  strip.begin();
  for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++){
    strip.setPixelColor(i, strip.Color(0,0,255)); //start all letters blue
  }
  //Optional: Start first and last letter of maze lit green
  strip.setPixelColor(2, strip.Color(0,255,0));
  //strip.setPixelColor(10, strip.Color(0,255,0));
  strip.show();

  //init multiplexing pins
   pinMode(x0, INPUT_PULLUP);
   pinMode(x1, INPUT_PULLUP);
   pinMode(x2, INPUT_PULLUP);
   pinMode(x3, INPUT_PULLUP);
   pinMode(x4, INPUT_PULLUP);
   pinMode(y0, INPUT_PULLUP);
   pinMode(y1, INPUT_PULLUP);
   pinMode(y2, INPUT_PULLUP);
   pinMode(y3, INPUT_PULLUP);
   pinMode(y4, INPUT_PULLUP);
}

void loop() {
  pos = getPos(); //check which hall sensors are triggered
  if(pos == path[move_num]){ //if on correct position
    lit[pos] = true; //light current letter
    move_num++; //go to next move
  }
  else if (pos != -1){ //If they're on a position
    if((move_num > 0 && pos != path[move_num-1]) || move_num == 0){ //and it's different from the prev pos, if there is a prev pos
        reset(); //then reset, becuase position is wrong
     }
    }  
  light(); //light green/blue LEDs as appropriate based on current lit array
  
  if(move_num == (sizeof(path)/sizeof(int))){//if path finished
    winSeq(); //go to winSequence
  }
 delay(200);
}

/*
 * Using the lit boolean array, turn lights green
 * and blue as appropriate.
 */
void light(){
  for(int i=0; i<(sizeof(lit)/sizeof(boolean));i++){
    if(lit[i]){
      strip.setPixelColor(i, strip.Color(0,255,0));
      //Serial.println("lit");
    }    
    else{
      strip.setPixelColor(i, strip.Color(0,0,255));
      //Serial.println("unlit");
    }
  }
  //leave first letter andd last lit if so desired
  strip.setPixelColor(2, strip.Color(0,255,0));
  //strip.setPixelColor(10, strip.Color(0,255,0));
  strip.show();
}

/*
 * Reset function flashes all lights red,
 * changes all values in lit array to false,
 * and sets current move to zero
 */
void reset(){
  for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++)
    lit[i] = false;
  move_num = 0;
  
  for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++)
    strip.setPixelColor(i, strip.Color(255,0,0));
  strip.show();
  delay(500); 
}

/*
 * winSeq function flashes
 * the ccode specified in the
 * code array
 */
void winSeq(){
  int code[] = {8,19,21,11,14};
  while(true){
  flashFive(10, code);
  } 
}

/*
 * The getPos function checks which arduino pins 
 * are being triggered, and returns which 
 * coordinate on the board this represents, or -1
 * for no coordinate
 */
int getPos(){;
  if(digitalRead(x0) == 0){
    Serial.println("x=0");
    if(digitalRead(y0) == 0)
      return(4);
    if(digitalRead(y1) == 0)
      return(3);
    if(digitalRead(y2) == 0)
      return(2);
    if(digitalRead(y3) == 0)
      return(1);
    if(digitalRead(y4) == 0)
      return(0);
  }
  else if(digitalRead(x1) == 0){
    Serial.println("x=1");
    if(digitalRead(y0) == 0)
      return(5);
    if(digitalRead(y1) == 0)
      return(18);
    if(digitalRead(y2) == 0)
      return(17);
    if(digitalRead(y3) == 0)
      return(16);
    if(digitalRead(y4) == 0)
      return(15);    
  }
  else if(digitalRead(x2) == 0){
    Serial.println("x=2");
    if(digitalRead(y0) == 0)
      return(6);
    if(digitalRead(y1) == 0)
      return(19);
    if(digitalRead(y2) == 0)
      return(24);
    if(digitalRead(y3) == 0)
      return(23);
    if(digitalRead(y4) == 0)
      return(14);    
  }
  else if(digitalRead(x3) == 0){
    Serial.println("x=3");
    if(digitalRead(y0) == 0)
      return(7);
    if(digitalRead(y1) == 0)
      return(20);
    if(digitalRead(y2) == 0)
      return(21);
    if(digitalRead(y3) == 0)
      return(22);
    if(digitalRead(y4) == 0)
      return(13);    
  }
  else if(digitalRead(x4) == 0){
    Serial.println("x=4");
    if(digitalRead(y0) == 0)
      return(8);
    if(digitalRead(y1) == 0)
      return(9);
    if(digitalRead(y2) == 0)
      return(10);
    if(digitalRead(y3) == 0)
      return(11);
    if(digitalRead(y4) == 0)
      return(12);    
  } 
  else{
    return(-1);
  }
}

//function to make all lights pulse green
void pulseAllGreen(int reps){
  for(int k = 0; k < reps; k++){
    for(int i=55; i <= 255; i+=5){
      for(int j=0; j < (sizeof(lit)/sizeof(boolean));j++){
        strip.setPixelColor(j, strip.Color(0,i,0));
      }
      strip.show();
      delay(20);
    }
    for(int i=255; i >= 55; i-=5){
      for(int j=0; j < (sizeof(lit)/sizeof(boolean));j++){
        strip.setPixelColor(j, strip.Color(0,i,0));
      }
      strip.show();
      delay(20);
    }
  }
}

//function to make all lights pulse blue
void pulseAllBlue(int reps){
  for(int k = 0; k < reps; k++){
    for(int i=55; i <= 255; i+=5){
      for(int j=0; j < (sizeof(lit)/sizeof(boolean));j++){
        strip.setPixelColor(j, strip.Color(0,0,i));
      }
      strip.show();
      delay(20);
    }
    for(int i=255; i >= 55; i-=5){
      for(int j=0; j < (sizeof(lit)/sizeof(boolean));j++){
        strip.setPixelColor(j, strip.Color(0,0,i));
      }
      strip.show();
      delay(20);
    }
  }
}

/*
 * function to flash arbitrary five digit code,
 * lighting up letters one at a time to indicate order
 */
void flashFive(int reps, int nums[]){
    for(int i=0;i<reps;i++){
    for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++){
      strip.setPixelColor(i, strip.Color(0,0,55));
    }
    strip.setPixelColor(nums[0], strip.Color(0,255,0));
    strip.setPixelColor(nums[1], strip.Color(0,55,0));
    strip.setPixelColor(nums[2], strip.Color(0,55,0));
    strip.setPixelColor(nums[3], strip.Color(0,55,0));
    strip.setPixelColor(nums[4], strip.Color(0,55,0));
    strip.show();
    delay(200);
    
    for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++){
      strip.setPixelColor(i, strip.Color(0,0,55));
    }
    strip.setPixelColor(nums[0], strip.Color(0,55,0));
    strip.setPixelColor(nums[1], strip.Color(0,255,0));
    strip.setPixelColor(nums[2], strip.Color(0,55,0));
    strip.setPixelColor(nums[3], strip.Color(0,55,0));
    strip.setPixelColor(nums[4], strip.Color(0,55,0));
    strip.show();
    delay(200);
    
      for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++){
      strip.setPixelColor(i, strip.Color(0,0,55));
    }
    strip.setPixelColor(nums[0], strip.Color(0,55,0));
    strip.setPixelColor(nums[1], strip.Color(0,55,0));
    strip.setPixelColor(nums[2], strip.Color(0,255,0));
    strip.setPixelColor(nums[3], strip.Color(0,55,0));
    strip.setPixelColor(nums[4], strip.Color(0,55,0));
    strip.show();
    delay(200);
    
      for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++){
      strip.setPixelColor(i, strip.Color(0,0,55));
    }
    strip.setPixelColor(nums[0], strip.Color(0,55,0));
    strip.setPixelColor(nums[1], strip.Color(0,55,0));
    strip.setPixelColor(nums[2], strip.Color(0,55,0));
    strip.setPixelColor(nums[3], strip.Color(0,255,0));
    strip.setPixelColor(nums[4], strip.Color(0,55,0));
    strip.show();
    delay(200);
    
      for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++){
      strip.setPixelColor(i, strip.Color(0,0,55));
    }
    strip.setPixelColor(nums[0], strip.Color(0,55,0));
    strip.setPixelColor(nums[1], strip.Color(0,55,0));
    strip.setPixelColor(nums[2], strip.Color(0,55,0));
    strip.setPixelColor(nums[3], strip.Color(0,55,0));
    strip.setPixelColor(nums[4], strip.Color(0,255,0));
    strip.show();
    delay(200);
  }
  for(int i=0;i<(sizeof(lit)/sizeof(boolean));i++){
    strip.setPixelColor(i, strip.Color(0,0,55));
  }
  strip.setPixelColor(nums[0], strip.Color(0,255,0));
  strip.setPixelColor(nums[1], strip.Color(0,255,0));
  strip.setPixelColor(nums[2], strip.Color(0,255,0));
  strip.setPixelColor(nums[3], strip.Color(0,255,0));
  strip.setPixelColor(nums[4], strip.Color(0,255,0));
  strip.show();
}
