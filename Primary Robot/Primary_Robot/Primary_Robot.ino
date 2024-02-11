#include "HC4051.h"

HC4051 mp(11, 12, 13);

#define LF 3
#define LB 4

#define RF 2
#define RB 5

#define L1 7
#define L2 8

#define IRpin A3

float vals[8];
float maxs[8]={340,558,170,410,206,155,99,103};
float mins[8]={42,213,37,100,38,37,3,4};
float w_th[8]={100,300,100,250,110,92,50,50};
float b_th[8]={300,430,100,600,300,300,35,49};
float err=0;

void setup() {
  for(int i=2;i<14;i++){
    pinMode(i,OUTPUT);
  }
  for(int i=2;i<14;i++){
    digitalWrite(i,LOW);
  }

Serial.begin(9600);
Serial.println("calibration begin");
int s= millis();/*
while((millis()-s)<5000){
calibrate();
}
//Serial.println("calibration end");*/
}


float kp=3;
float kd=1;
float ki=0;

int lstval=0;
long total_err=0;
int M=80;

int whiteThreshold = 80;
int t_3cm = 10;

void loop() {
  //FORWARD(50);
 
  readsensor();
 err=(vals[0]+vals[1]/2+vals[2]/4)-(vals[4]/4+vals[5]/2+vals[6]); 
 // err=(vals[0]+vals[1]/2+vals[2]/4)-(vals[3]/4+vals[4]/2+vals[5]); 
//Serial.print(err);Serial.print("\t\t");

int PIDval=PIDcontroll(err);
 //Serial.println(PIDval);
TURN(M+PIDval/2,M-PIDval/2);
/*
if(err<0){
left90(100);
}
if(err>300){
right90(100);
}*/
/*
 if(inJunction()==1){
    Serial.println("T");
 STOP();
 delay(1000);
 }
 */
 
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
  if(LSpeed>150){
    LSpeed=150;
  }
  if(LSpeed<0){
    LSpeed=0;
  }
  if(RSpeed>150){
    RSpeed=150;
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

void left90(int Speed){
  digitalWrite(LF,LOW);
  digitalWrite(LB,LOW);
  digitalWrite(RF,Speed);
  digitalWrite(RB,LOW);
  delay(10);
  STOP();

}

void right90(int Speed){
  digitalWrite(LF,Speed);
  digitalWrite(LB,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(RB,LOW);
    delay(10);
  STOP();

}

void STOP(){
  digitalWrite(LF,LOW);
  digitalWrite(LB,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(RB,LOW);

}

void readsensor(){
  for (uint8_t channel = 0; channel < 8; channel++){
   digitalWrite(L1,HIGH);
 digitalWrite(L2,HIGH);
   
   
  mp.setChannel(channel);
  int val=0;
  for(int i=0;i<10;i++){
    val=val+analogRead(IRpin);
  }
  val=val/10;
  vals[channel]=val;
  map(val,mins[channel],maxs[channel],0,1023);
  Serial.print(vals[channel]);Serial.print("\t\t");

  }
  Serial.println(" ");
  
}



void calibrate(){
  digitalWrite(L1,HIGH);
  digitalWrite(L2,HIGH);
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

int inJunction(){
  readsensor();
if((vals[0]<w_th[0])&&(vals[1]<w_th[1])&&(vals[2]<w_th[2])&&(vals[3]<w_th[3])&&(vals[4]<w_th[4])&&(vals[5]<w_th[5])){ return 1;} ;  //return 1 if T junction

if((vals[0]<w_th[0])&&(vals[1]<w_th[1])&&(vals[2]<w_th[2])&&(vals[3]<w_th[3])&&(vals[4]>w_th[4])&&(vals[5]>w_th[5])){ return 2;};   //return 1 if L left junction

if((vals[0]>w_th[0])&&(vals[1]>w_th[1])&&(vals[2]>w_th[2])&&(vals[3]>w_th[3])&&(vals[4]<w_th[4])&&(vals[5]<w_th[5])){ return 3;} ;  //return 1 if L right junction
return 0;

}




