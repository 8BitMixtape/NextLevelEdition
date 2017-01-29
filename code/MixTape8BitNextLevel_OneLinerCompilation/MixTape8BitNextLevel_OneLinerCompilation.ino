// 8-Bit Mixtape Next-Level Edition by GaudiLabs

// one-line algorithmic music
// see viznut's blog http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
// and http://www.youtube.com/watch?v=GtQdIYUtAHg&feature=related

// Player ported to arduino by stimmer


#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

unsigned long time = 0;

const int buttonPinRight = 2;    // the number of the pushbutton pin
const int buttonPinLeft = 3;    // the number of the pushbutton pin
const int potPinRight = A0;    // the number of the pushbutton pin
const int potPinLeft = A1;    // the number of the pushbutton pin

int RXLED = 17;  // The RX LED has a defined Arduino pin


const int outPinR = 9;
const int outPinL = 10;


uint8_t song = 1; 
int reading;

int aL;
int aR;

bool synth_mode=false;
bool intro=true;
static int del = 0; 
  long t = 0; 
byte v0 = 0; 
byte v1 = 0; 

unsigned int c3 = 1;
unsigned int c4 = 130;

const uint8_t noSongs = 84;    // the number of the pushbutton pin
char* myPlaylist[]=
{
  "1", 
  "2", 
  "3",
  "4", 
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "11",
  "12",
  "13",
  "14",
  "15",
  "16",
  "17",
  "18",
  "19",
  "20",
  "21"
  };


void setup(){
pinMode(buttonPinLeft,INPUT);
pinMode(buttonPinRight,INPUT);
digitalWrite(buttonPinLeft,HIGH);
digitalWrite(buttonPinRight,HIGH);

 TXLED1; //TX LED is not tied to a normally controlled pin



  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  //Complimentary Output or Dual Speakers:
  // Library angepasst, complementary output entfernt - Urs.

  pinMode(10,OUTPUT); //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45 
  
  Serial.begin(115200);
  pinMode(13,OUTPUT); //LED Connected to analog pin 0
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not

  }
  else{   
    Serial.println("SD ok");   
  }





  pinMode(outPinR, OUTPUT);
  pinMode(outPinL, OUTPUT);

TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10) ;// 161; 
TCCR1B = (1<<CS10);

ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));

  tmrpcm.play("Gaudi"); //the sound file "music" will play each time the arduino powers up, or is reset
intro=true;



}


void putb(byte b)
{
 static long m;
  
 if ((micros()-m)>c4)  digitalWrite(RXLED, HIGH); else digitalWrite(RXLED, LOW);    // set the LED on
 while(micros()-m <c4);
 m=micros();
 
OCR1A=b;
OCR1B=b;

}


void loop(){  

 for(long t=0;;t++){

c3=analogRead(potPinRight);
c4=analogRead(potPinLeft);
if (c4>300) c4=c4-150; else {t++;c4=c4;};


 switch(song){


// ====== 1ST ITERATION ======


case 1:
if (intro) tmrpcm.play("FIRSTviz"); else {
  if (c3<10) c3=63<<3;
// viznut 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=t*(((t>>12)|(t>>8))&((c3>>3)&(t>>4)));
}
break;

case 2:
if (intro) tmrpcm.play("tejeez"); else {
  if (c3<10) c3=1<<6;
// tejeez 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=((c3>>6)*t*(t>>5|t>>8))>>(t>>16);
}
break;

case 3:
if (intro) tmrpcm.play("visy"); else {
  if (c3<10) c3=25<<5;
// visy 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=t*(((t>>9)|(t>>13))&((c3>>5)&(t>>6)));
}
break;

case 4:
if (intro) tmrpcm.play("tejeez2"); else {
  if (c3<10) c3=123<<2;
// tejeez 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=t*(((t>>11)&(t>>8))&((c3>>2)&(t>>3)));
}
break;

case 5:
if (intro) tmrpcm.play("visy2"); else {
  if (c3<10) c3=20<<5;
// visy 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=t*(t>>8*((t>>15)|(t>>8))&((c3>>5)|(t>>19)*5>>t|(t>>3)));
}
break;

case 6:
if (intro) tmrpcm.play("tejeez3"); else {
  if (c3<10) c3=234<<1;
// tejeez 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=((-t&4095)*(255&t*(t&(t>>13)))>>12)+(127&t*((c3>>1)&t>>8&t>>3)>>(3&t>>14));
}
break;

case 7:
if (intro) tmrpcm.play("spacepo"); else {
  if (c3<10) c3=63<<3;
// visy 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg "Space Invaders vs Pong"
v0=t*(t>>((t>>9)|(t>>8))&((c3>>3)&(t>>4)));
}
break;

// ====== 2ND ITERATION ======

case 8:
if (intro) tmrpcm.play("visy3"); else {
  if (c3<10) c3=10<<6;
// viznut 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
v0=(t>>6|t|t>>(t>>16))*(c3>>6)+((t>>11)&7);
}
break;

case 9:
if (intro) tmrpcm.play("pyryp"); else {
  if (c3<10) c3=69<<3;
// pyryp 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
v0=(v0>>1)+(v0>>4)+t*(((t>>16)|(t>>6))&((c3>>3)&(t>>9)));
}
break;

case 10:
if (intro) tmrpcm.play("red"); else {
  if (c3<10) c3=63<<3;
// red- 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
v0=(t|(t>>9|t>>7))*t&(t>>11|t>>9);
}
break;

case 11:
if (intro) tmrpcm.play("miiro"); else {
  if (c3<10) c3=5<<7;
// miiro 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
v0=t*(c3>>7)&(t>>7)|t*3&(t*4>>10);
}
break;

case 12:
if (intro) tmrpcm.play("varjo"); else {
  if (c3<10) c3=10<<6;
// viznut 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y (xpansive+varjohukka)
v0=(t>>7|t|t>>6)*(c3>>6)+4*(t&t>>13|t>>6);
}
break;

case 13:
if (intro) tmrpcm.play("skurk"); else {
  if (c3<10) c3=8192>>3;
// skurk+raer 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
v0=((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&(c3<<3))?t<<2:t));
}
break;

case 14:
if (intro) tmrpcm.play("lost"); else {
  if (c3<10) c3=46<<3;
// xpansive 2011-09-29 http://pouet.net/topic.php?which=8357&page=2 "Lost in Space"
v0=((t*(t>>8|t>>9)&(c3>>3)&t>>8))^(t&t>>13|t>>6);
}
break;


// ====== 3RD ITERATION ======














case 15:   v0=((t/2*(15&(0x234568a0>>(t>>8&28))))|t/2>>(t>>11)^t>>12)+(t/16&t&24);break;
case 16:   v0=(t&t%255)-(t*3&t>>13&t>>6);break;
case 17:    v0=t>>4|t&((t>>5)/(t>>7-(t>>15)&-t>>7-(t>>15)));break;
case 18:    v0=((t*("36364689"[t>>13&7]&15))/12&128)+(((((t>>12)^(t>>12)-2)%11*t)/4|t>>13)&127) ;break;
case 19:    v0=(t*9&t>>4|t*5&t>>7|t*3&t/1024)-1;break;
case 20:    v0=((t*(t>>12)&(201*t/100)&(199*t/100))&(t*(t>>14)&(t*301/100)&(t*399/100)))+((t*(t>>16)&(t*202/100)&(t*198/100))-(t*(t>>17)&(t*302/100)&(t*298/100)))  ;break;  
case 21:    v0=((t*(t>>12)&(201*t/100)&(199*t/100))&(t*(t>>14)&(t*301/100)&(t*399/100)))+((t*(t>>16)&(t*202/100)&(t*198/100))-(t*(t>>18)&(t*302/100)&(t*298/100)));break;
case 22:    v0=t*(t^t+(t>>15|1)^(t-1280^t)>>10);break;
case 23:    v0=((t>>1%128)+20)*3*t>>14*t>>18 ;break;
case 24:    v0=t*(((t>>9)&10)|((t>>11)&24)^((t>>10)&15&(t>>15)));break;
case 25:    v0=(t*t/256)&(t>>((t/1024)%16))^t%64*(0xC0D3DE4D69>>(t>>9&30)&t%32)*t>>18;break;
case 26:    v0=t*(42&t>>10);break;
case 27:    v0=t&t>>8;break;


case 28:
if (intro) tmrpcm.play("42melody"); else {
  if (c3<10) c3=672;
// "the 42 melody", separately discovered by several people on irc etc
v0=t*((c3>>4)&t>>10);
}

break;



case 29:    
// danharaj 2011-10-03 http://www.reddit.com/r/programming/comments/kyj77/algorithmic_symphonies_from_one_line_of_code_how/ "fractal trees", 216's version
v0=t|t%255|t%257;break;

case 30:    
// droid 2011-10-05 http://pouet.net/topic.php?which=8357&page=10
v0=t>>6&1?t>>5:-t>>4;break;

case 31: 
// Niklas_Roy 2011-10-14 http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
v0= t*(t>>9|t>>13)&16;break;

case 32:
// krcko 2011-10-04 http://rafforum.rs/index.php/topic,123.0.html
v0=(t&t>>12)*(t>>4|t>>8);break;

case 33:
// viznut 2011-10-10 http://www.youtube.com/watch?v=tCRPUv8V22o
v0=(t*5&t>>7)|(t*3&t>>10);break;

case 34:
// tejeez 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=(t*(t>>5|t>>8))>>(t>>16);break;

case 35:
// miiro 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
if (intro) tmrpcm.play("miiro"); else v0=t*5&(t>>7)|t*3&(t*4>>10);
break;

case 36:
// robert 2011-10-11 http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
if (intro) tmrpcm.play("robert"); else v0=(t>>13|t%24)&(t>>7|t%19);
break;

case 37:
if (intro) tmrpcm.play("Niklas"); else v0=(t*((t>>9|t>>13)&15))&129;//the sound file "music" will play each time the arduino powers up, or is reset
// Niklas_Roy 2011-10-14 http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
break;

case 38:
// viznut 2011-10-10 http://www.youtube.com/watch?v=tCRPUv8V22o  
v0=(t&t%255)-(t*3&t>>13&t>>6);break;

case 39:
// krcko 2011-10-04 http://rafforum.rs/index.php/topic,123.0.html
v0=(t&t>>12)*(t>>4|t>>8)^t>>6;break;

case 40:
// blueberry 2011-10-05 http://pouet.net/topic.php?which=8357&page=12 11kHz
v0=t*(((t>>9)^((t>>9)-1)^1)%13);break;

case 41:
// rrola 2011-10-04 http://pouet.net/topic.php?which=8357&page=9 optimized by ryg
v0=t*(0xCA98>>(t>>9&14)&15)|t>>8;break;

case 42:
// tonic 2011-10-01 http://pouet.net/topic.php?which=8357&page=5 "mr. arpeggiator playing a solo"
v0=(t/8)>>(t>>9)*t/((t>>14&3)+4);break;

case 43:
// FreeFull 2011-10-12 http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
v0=(~t/100|(t*3))^(t*3&(t>>5))&t;break;

case 44:
// red- 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
v0=(t|(t>>9|t>>7))*t&(t>>11|t>>9);break;

case 45:
// harism 2011-10-09 http://0xa.kuri.mu/2011/10/09/bitop-videos/
v0=((t>>1%128)+20)*3*t>>14*t>>18 ;break;

case 47:
// viznut 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=t*(((t>>12)|(t>>8))&(63&(t>>4)));break;

case 48:
// visy 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=t*(((t>>9)|(t>>13))&(25&(t>>6)));break;

case 49:
// 216 2011-10-10 http://www.youtube.com/watch?v=tCRPUv8V22o
v0=t*(t^t+(t>>15|1)^(t-1280^t)>>10);break;

case 50:
// tejeez 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg
v0=t*(((t>>11)&(t>>8))&(123&(t>>3)));break;

case 51:
// viznut 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y (xpansive+varjohukka)
v0=(t>>7|t|t>>6)*10+4*(t&t>>13|t>>6);break;

case 52:
// stephth 2011-10-03 http://news.ycombinator.com/item?id=3063359
v0=(t*9&t>>4|t*5&t>>7|t*3&t/1024)-1;break;

case 53:
// visy 2011-09-18 http://www.youtube.com/watch?v=GtQdIYUtAHg "Space Invaders vs Pong"
v0=t*(t>>((t>>9)|(t>>8))&(63&(t>>4)));break;

case 54:
// viznut 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
v0=(t>>6|t|t>>(t>>16))*10+((t>>11)&7);break;

case 55:
// yumeji 2011-10-04 http://pouet.net/topic.php?which=8357&page=9
v0=(t>>1)*(0xbad2dea1>>(t>>13)&3)|t>>5;break;

case 56:
// ryg 2011-10-04 http://pouet.net/topic.php?which=8357&page=8
v0=(t>>4)*(13&(0x8898a989>>(t>>11&30)));break;

case 57:
// marmakoide 2011-10-04 http://pouet.net/topic.php?which=8357&page=8
v0=(t>>(t&7))|(t<<(t&42))|(t>>7)|(t<<5);break;

case 58:
// robert 2011-10-11 http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
v0=(t>>7|t%45)&(t>>8|t%35)&(t>>11|t%20);break;

case 59:
// lucasvb 2011-10-03 http://www.reddit.com/r/programming/comments/kyj77/algorithmic_symphonies_from_one_line_of_code_how/
v0=(t>>6|t<<1)+(t>>5|t<<3|t>>3)|t>>2|t<<1;break;

case 60:
// bear @ celephais
v0=t+(t&t^t>>6)-t*((t>>9)&(t%16?2:6)&t>>9);break;

case 61:
// xpansive 2011-09-29 http://pouet.net/topic.php?which=8357&page=2 "Lost in Space"
v0=((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6);break;

case 63:
// marmakoide 2011-10-03 http://pouet.net/topic.php?which=8357&page=7 "Lemmings March"
v0=(t>>5)|(t<<4)|((t&1023)^1981)|((t-67)>>4);break;

case 64:
// droid 2011-10-04 http://pouet.net/topic.php?which=8357&page=9
v0=t>>4|t&(t>>5)/(t>>7-(t>>15)&-t>>7-(t>>15));break;

case 65:
// rez 2011-10-03 http://pouet.net/topic.php?which=8357&page=7
v0=t*(t/256)-t*(t/255)+t*(t>>5|t>>6|t<<2&t>>1);break;

case 66:
// viznut 2011-10-06 #countercomplex "moon scanner generalization", based on jaffa's formula
v0=((t>>5&t)-(t>>5)+(t>>5&t))+(t*((t>>14)&14));break;

case 67:
// viznut 2011-10-04 http://pouet.net/topic.php?which=8357&page=9
v0=(t*((3+(1^t>>10&5))*(5+(3&t>>14))))>>(t>>8&3);break;

case 69:
// pyryp 2011-09-30 http://www.youtube.com/watch?v=qlrs2Vorw2Y
//v0==(v0=>>1)+(v0=>>4)+t*(((t>>16)|(t>>6))&(69&(t>>9)));break;


case 83:

v0=t*6 & (t>>7|(int)(t*3.5)<<2) | t*4 & ((t>>8|(int)(t*1.5)<<2)) | t*4 & (((int)(t/1.5)>>7)^((int)(t/3)>>8)^((int)(t/6)>>9)); break;


case 84:
// raer 2011-10-07 http://pouet.net/topic.php?which=8357&page=16 stereo 11kHz
v0= ((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t));
v1= t*(((t>>9)^((t>>9)-1)^1)%13);break;

    default: break;
    
 }
  


if (!(tmrpcm.isPlaying())) putb(v0);
intro=false;
 
       if(digitalRead(buttonPinRight) == LOW) {while (digitalRead(buttonPinRight) == LOW); delayMicroseconds(1000); song++; intro=true;if (song>(noSongs-1)) song=noSongs-1;}
       if(digitalRead(buttonPinLeft) == LOW)  {while (digitalRead(buttonPinLeft) == LOW); delayMicroseconds(1000); song--; intro=true;if (song==0)song=1;}





       


 }
}
