
#include<FastLED.h>
CRGB leds[1];
//#include"Talkie.h"
//#include "Vocab_US_Large.h"
//#include "Vocab_US_TI99.h"
//Talkie voice;

void setup() {
  pinMode(34,OUTPUT);
 FastLED.addLeds<WS2811,34, RGB>(leds,1);
Serial.begin(9600);
pinMode(35,INPUT);
//digitalWrite(5,HIGH);
}
int t=500;

void loop() {
  int R;
  int G;
  int B;
 leds[0] = CRGB::Red;
 FastLED.show();
delay(10);
R= get10Sample(35);

delay(t);
 leds[0] = CRGB::Green;
 FastLED.show();
delay(10);
G= get10Sample(35);

delay(t);
 leds[0] = CRGB::Blue;
 FastLED.show();
delay(10);
B= get10Sample(35);

delay(t);

leds[0] = CRGB::Black;
 FastLED.show();

R=map(R,200,510,0,255);
G=map(G,180,500,0,255);
B=map(B,180,455,0,255);

//R = range(R, 0, 255);
//G = range(G, 0, 255);
//B = range(B, 0, 255);

//Serial.print("R  ");Serial.print(R);Serial.print('\t');
//Serial.print("G  ");Serial.print(G);Serial.print('\t');
//Serial.print("B  ");Serial.println(B);

if(R>=230 && G>=230 && B>=230){
//voice.say(spt_WHITE);
Serial.println("White");

}
else if(R>=220 && G<=180 && B<=180){
//voice.say(spt_RED);
Serial.println("Red");
}
else if(R<=180 && G>=200 && B<=180){
//voice.say(spt_GREEN);
Serial.println("Green");
}
else if(R<=120 && G<=150 && B>=170){
//voice.say(spt_BLUE);
Serial.println("Blue");
}
else if(R>=230 && G>=225 && B<=200){
//voice.say(spt_YELLOW);
Serial.println("Yellow");
}
else if(R<=30 && G<=30 && B<=30){
//voice.say(spt_BLACK);  
Serial.println("Black");
}


}




 int get10Sample(int pin){
  int total = 0.0;
  for(int i=0;i<10;i++){
    total += analogRead(pin);
  }
  return total/10;
}

/*void range(int val, int mn, int mx){
  if(val < mn){
    return mn;
  }else if(val > mx){
    return mx;
  }
 return val;
}*/
