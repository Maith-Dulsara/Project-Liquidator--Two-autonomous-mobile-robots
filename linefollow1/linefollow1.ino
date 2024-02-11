#include "HC4051.h"

HC4051 mp(11, 12, 13);

#define LF 2
#define LB 3

#define RF 4
#define RB 5

float vals[8];
float maxs[8]={0,0,0,0,0,0,0,0};
float mins[8]={1024,1024,1024,1024,1024,1024,1024,1024};
float err=0;

void setup() {
  for(int i=2;i<12;i++){
    pinMode(i,OUTPUT);
  }
  for(int i=2;i<12;i++){
    digitalWrite(i,LOW);
  }

Serial.begin(9600);
Serial.println("calibration begin");
int s= millis();
while((millis()-s)<5000){
calibrate();
}
Serial.println("calibration end");
}


float kp=5;
float kd=0;
float ki=0;

int lstval=0;
long total_err=0;
int M=50;


void loop() {
  //FORWARD(100);

  readsensor();
 err=vals[0]+vals[1]/2+vals[2]/4+vals[3]/8-(vals[4]/8+vals[5]/4+vals[6]/2+vals[7]); 
//Serial.print(err);Serial.print("\t\t");

int PIDval=PIDcontroll(err);
 // Serial.println(PIDval);

    TURN(M+PIDval,M-PIDval);
 
  
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

void readsensor(){
  for (uint8_t channel = 0; channel < 8; channel++){
  
   if((channel%2)==0){
      digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
   }else{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
   }
   
  mp.setChannel(channel);
  int val=0;
  for(int i=0;i<10;i++){
    val=val+analogRead(A0);
  }
  val=val/10;
  vals[channel]=val;
  //map(val,mins[channel],maxs[channel],1000,0);
  Serial.print(vals[channel]);Serial.print("\t\t");

  }
  Serial.println(" ");
  
}


void calibrate(){
  digitalWrite(2,HIGH);
 digitalWrite(3,HIGH);
  for (uint8_t channel = 0; channel < 8; channel++){

   
  mp.setChannel(channel);
  vals[channel]=analogRead(A0);
  if(vals[channel]<mins[channel]){
    mins[channel]=vals[channel];
  }
  if(vals[channel]>maxs[channel]){
    maxs[channel]=vals[channel];
  }
  }
  
}
