#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

unsigned long time = 0;

const int buttonPinRight = 2;    // the number of the pushbutton pin
const int buttonPinLeft = 3;    // the number of the pushbutton pin

int song = 0;    // the number of the pushbutton pin
int reading;

bool synth_mode=false;

  long t = 0; 
int v0 = 0; 
int v1 = 0; 

unsigned int c3 = 2000;
unsigned int c4 = 6;

const int noSongs = 4;    // the number of the pushbutton pin
char* myPlaylist[]=
{
  "1", 
  "2", 
  "3",
  "4", 
  "5",
  "6"};


void setup(){
pinMode(buttonPinLeft,INPUT);
pinMode(buttonPinRight,INPUT);
digitalWrite(buttonPinLeft,HIGH);
digitalWrite(buttonPinRight,HIGH);

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
  tmrpcm.play(myPlaylist[0]); //the sound file "music" will play each time the arduino powers up, or is reset
}



void loop(){  



while(synth_mode){
  tmrpcm.stopPlayback();
for (int i=0; i < 3000; i++){
  

  v0 = t * ((t>>15|t>>c4)&83&t>>(c4>>3));
    v1 = t * ((t>>14|t>>c4)&83&t>>(c4>>3));

     analogWrite (9, v0);
      analogWrite (10, v1);

     delayMicroseconds(c3);
     t++;

       if(digitalRead(buttonPinRight) == HIGH)c3++;
       if(digitalRead(buttonPinLeft) == HIGH)c3--;



       
}
}



  //blink the LED manually to demonstrate music playback is independant of main loop
 /* if(tmrpcm.isPlaying() && millis() - time > 50 ) {      
      digitalWrite(2,!digitalRead(2));
      time = millis();    
  }else
  if(millis() - time > 500){     
    digitalWrite(2,!digitalRead(2)); 
    time = millis(); 
  }
  */

  if(!tmrpcm.isPlaying())
  {song++;
   if (song>(noSongs-1)) song=0;
   tmrpcm.play(myPlaylist[song]);}

  reading = digitalRead(buttonPinRight);
  if (reading==LOW) {
    song++;
    if (song>(noSongs-1)) song=noSongs-1;
    tmrpcm.play(myPlaylist[song]);
    Serial.println(song);  
    Serial.println(myPlaylist[song]);   
    reading = digitalRead(buttonPinRight);
    if ((reading==LOW)&&(digitalRead(buttonPinLeft)==LOW)) synth_mode=true;
    while(reading==LOW) reading = digitalRead(buttonPinRight);
  };

    reading = digitalRead(buttonPinLeft);
  if (reading==LOW) {
    song--;
     if (song<0) song=0;
    tmrpcm.play(myPlaylist[song]);
    Serial.println(song);  
    Serial.println(myPlaylist[song]);   
    reading = digitalRead(buttonPinLeft);
    while(reading==LOW) reading = digitalRead(buttonPinLeft);
  };


  

  if(Serial.available()){    
    switch(Serial.read()){
    case 'd': tmrpcm.play("music"); break;
    case 'P': tmrpcm.play("temple"); break;
    case 't': tmrpcm.play("catfish"); break;
    case 'p': tmrpcm.pause(); break;
    case '?': if(tmrpcm.isPlaying()){ Serial.println("A wav file is being played");} break;
    case 'S': tmrpcm.stopPlayback(); break;
    case '=': tmrpcm.volume(1); break;
    case '-': tmrpcm.volume(0); break;
    case '0': tmrpcm.quality(0); break;
    case '1': tmrpcm.quality(1); break;
    default: break;
    }
  }

}
