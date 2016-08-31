/* PCrazy shit 8-bit symphony generator                   */
/*     */
 
/*
 * inspired by:
 *  http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
 *
 *  http://wurstcaptures.untergrund.net/music/
 *
 */

int speakerPin = 9;
int speakerPin2 = 13;
int buttonPin = 2;

int pot0 = 0;
int pot3 = 1;

int buttonState = 0; 
int lastButtonState = 0;
int count = -1;
 
long t = 0; 

unsigned int p0 = 10;
unsigned int p1 = 4;
unsigned int p2 = 4;
unsigned int delta_T = 4;

int v = 0; 
 
void setup () {
 
  //TCCR0B = TCCR0B & 0b11111001; //no timer pre-scaler, fast PWM
  TCCR1B = TCCR0B & 0b11111001; //no timer pre-scaler, fast PWM

  //TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

  //2CCR1B = TCCR1B & B11111000 | B00000001;
 
  pinMode (speakerPin, OUTPUT);
  pinMode (speakerPin2, OUTPUT);
    
  //pinMode(buttonPin, INPUT);
  //digitalWrite(buttonPin, HIGH);
  
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode (pot0, INPUT);
  pinMode (pot3, INPUT);
}
 
void loop ()
{
  
// read the state of the switch into a local variable:
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != lastButtonState && buttonState == HIGH) {
    // if the state has changed, increment the counter
    count++;
    t = 0; 
    delay(20); 
    
    if (count > 4) {
      count = 0;
    } 
      
     
    
  } 
  
  lastButtonState = buttonState;
    
  switch(count) {
    
  case 0: // siech
 
    p0 = ((analogRead(pot0)>>7)+0);
    delta_T = ((1023 - (analogRead(pot3)))>>0);
     
    v = (t|7) * ((t>>5|t>>9)&83&t>>p0);    
    //v = t>>p0&13?t>>7:-t>>6;


    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break; 
  
  case 1: // dubStep
 
    p0 = (analogRead(pot0)>>7);
    delta_T = ((1023 - (analogRead(pot3)))<<0);
    
    //v = t * ((t>>13|t>>p0)&77&t>>(p0>>3));
    //v = t*(t^t+(t>>15|1)^(t-(p0-(7/2))^t)>>(10-(pot0/5)));
    //v = t*(((t>>(12+(p0/2)))|(t>>8))&((p0-(p0/2))&(t>>4)));
    v = t>>p0&1?t>>2:-t>>5;

    analogWrite (speakerPin, v);
    digitalWrite (speakerPin2, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
    
  case 2: // a classic
 
    p0 = ((analogRead(pot0)>>6)+0);
    delta_T = ((1023 - (analogRead(pot3)))>>0);
     
    v = t * ((t>>p0|t>>p0)&13&t>>(13>>3));

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  
  case 3: // a single
 
    p0 = ((analogRead(pot0)>>5)+0);
    delta_T = ((1023 - (analogRead(pot3)))>>0);
     
    v = (t|3) * ((t>>1|t>>6)&p0&t>>3);

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  }  
 
}

/*
     v = (t|3) * ((t>>1|t>>6)&c4&t>>3);
   v = t * ((t>>12|t>>7)&47&t>>(13>>3))  
     
     //v = (t*(t>>8|t>>4))>>(t>>p0);
     
     v = t * ((t>>p1|t>>p0)&p2&t>>(p0>>3));
     
     
     
     //v = (t|p0) * ((t>>p0|t>>11)&47&t>>3);
     
   // v = t * ((t>>p0|t>>p1)&p2&t>>5);
     
     //v = t * ((t>>p0|t>>3)&p1&t>>p2);
     
     //v =    t * ((t>>12|t>>p0)&p1&t>>p2);
    
    //v = t * ((t>>p0|t>>7)&p1&t>>(p2>>3));
    
    //v = t * ((t>>p1|t>>3)&17&t>>9);
    
    //v = (t|p1) * ((t>>p2|t>>11)&p0&t>>3);
    
    //v = t>>p0&1?t>>p2:-t>>p1;
    
    //v = (t|p0) * ((t>>1|t>>p1)&47&t>>p2);
    
    //v = t*t/p0;
    
    //v = t * ((t>>p0|t>>83)&7&t>>5);

    analogWrite (speakerPin2, v);
    digitalWrite (speakerPin, v);

    //delayMicroseconds(delta_T);
    
    delayMicroseconds((delta_T+1));
    
*/    
