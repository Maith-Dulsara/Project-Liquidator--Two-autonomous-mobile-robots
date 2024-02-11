#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 2
CRGB leds[NUM_LEDS];
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B



#define LF 21
#define LB 19

#define RF 18
#define RB 5

const int sensorpins[8]={14,27,26,25,33,32,35,34};
#define L1 12
#define L2 13

#define LDR 15

unsigned long tim=0;

int vals[8]={0,0,0,0,0,0};
float maxs[8]={0,0,0,0,0,0,0,0};
float mins[8]={1024,1024,1024,1024,1024,1024,1024,1024};

void setup() {
  
 // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
 // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
   FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(leds, NUM_LEDS); 
  
  Serial.begin(115200);
  analogReadResolution(10);
  
  pinMode(5,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(21,OUTPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);

  pinMode(DATA_PIN,OUTPUT);
  pinMode(LDR,INPUT);

  digitalWrite(L1,HIGH);
  digitalWrite(L2,HIGH);


  for(int i=0;i<8;i++){
    pinMode(sensorpins[i],INPUT);
  }
int s= millis();
/*
while((millis()-s)<5000){
calibrate();
}
leds[0] = CRGB::Black;
 FastLED.show();
  */
tim=millis();
delay(60000);
  FORWARD(255);
  delay(200);
  STOP();
}



float kp=0.2;
float kd=3;
float ki=0;
float err=0;

int lstval=0;
long total_err=0;
int M=100;

int whiteThreshold = 100;
int t_3cm = 10;

void loop() {

 
 //FORWARD(60);
  readsensor();

//if(vals[0]>50 && vals[1]>50 && vals[2]>50 && vals[3]>50 && vals[4]>50 && vals[5]>50){
  
 err=vals[0]+vals[1]/2+vals[2]/4+vals[3]/8-(vals[4]/8+vals[5]/4+vals[6]/2+vals[7]); 
 //Serial.print(err);Serial.print("\t\t");

  int PIDval=PIDcontroll(err);
 //Serial.println(PIDval);
  // isJunction();  

//Serial.println("not a junction");
TURN(M+PIDval,M-PIDval);
//delay(1000);

 


 
 
//colorsense();

/*
leds[0] = CRGB::Blue;
 FastLED.show();
 delay(100);
 leds[0] = CRGB::Green;
 FastLED.show();
 delay(100);
leds[0] = CRGB::Red;
 FastLED.show();
 delay(100);
 leds[0] = CRGB::Yellow;
 FastLED.show();
 delay(100);
 
   /*
if(millis()-tim>100){
  if(index<100){
  t[index]=millis();
  e[index]=err;
  tim=millis();
  index=index+1;
  }
}

if(millis()-tim>60000){
  for(int i=0;i<100;i++){
    Serial.print(t);Serial.print("\t\t");Serial.println(e);
  }
}
*/
}

bool isJunction() {
  if (vals[0] < whiteThreshold && vals[1] < whiteThreshold && vals[2] < whiteThreshold && vals[3] < whiteThreshold && vals[4] < whiteThreshold && vals[5] < whiteThreshold && vals[6] < whiteThreshold && vals[7] < whiteThreshold ) {
    delay(t_3cm);
    readsensor();
    if (vals[0] < whiteThreshold && vals[1] < whiteThreshold && vals[2] < whiteThreshold && vals[3] < whiteThreshold && vals[4] < whiteThreshold && vals[5] < whiteThreshold && vals[6] < whiteThreshold && vals[7] < whiteThreshold ) {
      STOP();
      while (vals[0] < whiteThreshold || vals[1] < whiteThreshold || vals[2] < whiteThreshold || vals[3] < whiteThreshold || vals[4] < whiteThreshold || vals[5] < whiteThreshold || vals[6] < whiteThreshold || vals[7] < whiteThreshold ) {
        readsensor();
      }
      return true;
    }
  }
  return false;
}



int PIDcontroll(int err){
   int Pterm = err*kp;
  int Dterm = (err-lstval)*kd;
  int Iterm = total_err*ki;
  
  int diff=Pterm+Dterm+Iterm;

  lstval=err;
  total_err =+ err;

  return diff;
}

void FORWARD(int Speed){
  digitalWrite(LF,HIGH);
  digitalWrite(LB,LOW);
  digitalWrite(RF,HIGH);
  digitalWrite(RB,LOW);

}

void STOP(){
  digitalWrite(LF,LOW);
  digitalWrite(LB,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(RB,LOW);

}

void TURN(int LSpeed, int RSpeed){
   if(LSpeed>255){
    LSpeed=255;
  }
  if(LSpeed<0){
    LSpeed=0;
  }
  if(RSpeed>255){
    RSpeed=255;
  }
  if(RSpeed<0){
    RSpeed=0;
  }
  analogWrite(LF,LSpeed);
  digitalWrite(LB,LOW);
  analogWrite(RF,RSpeed);
  digitalWrite(RB,LOW);
}





void readsensor(){

  for(int i=0;i<8;i++){
      vals[i]=analogRead(sensorpins[i]);
    // vals[i]=map(vals[i],mins[i],maxs[i],0,1024);
  }



  for(int i=0;i<8;i++){
     Serial.print(vals[i]);Serial.print("\t\t");

  }
  Serial.println(" ");

 
}


void calibrate(){
  digitalWrite(L1,HIGH);
 digitalWrite(L2,HIGH);
  for (int i = 0; i < 8; i++){

     vals[i]=analogRead(sensorpins[i]);
 
  if(vals[i]<mins[i]){
    mins[i]=vals[i];
  }
  if(vals[i]>maxs[i]){
    maxs[i]=vals[i];
  }
  }
  
}

void colorsense(){
  int R;
  int G;
  int B;
  
 leds[0] = CRGB::Green;
 FastLED.show();
delay(10);
R= get10Sample(LDR);

delay(20);
 leds[0] = CRGB::Red;
 FastLED.show();
delay(10);
G= get10Sample(LDR);

delay(20);
 leds[0] = CRGB::Blue;
 FastLED.show();
delay(10);
B= get10Sample(LDR);

delay(20);

leds[0] = CRGB::Black;
 FastLED.show();

}

int get10Sample(int pin){
  int total = 0.0;
  for(int i=0;i<10;i++){
    total += analogRead(pin);
  }
  return total/10;
}
