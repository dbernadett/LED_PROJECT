// Written by Nick Gammon
// February 2011
/**
 * Send arbitrary number of bits at whatever clock rate (tested at 500 KHZ and 500 HZ).
 * This script will capture the SPI bytes, when a '\n' is recieved it will then output
 * the captured byte stream via the serial.
 */
#include <TimerOne.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
char buf [300];
volatile byte pos;
volatile boolean process_it;
char receivingState = 0;
volatile int tail = -1;
volatile int head = 0;
void setup (void)
{
  strip.begin();
  Serial.begin (115200);   // debugging

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();
  Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  ringAdd(c);
    
}  // end of interrupt routine SPI_STC_vect
int buffed = 0;
void ringAdd(char toAdd){
  int temp = head;
  head++;
  head = head % 300;
  if(tail == head){
    head = temp;
    digitalWrite( 3, digitalRead( 3 ) ^ 1 );
  } else {
    buffed++;
    buf[temp] = toAdd;
  }
}

int ringRemove(){
  int temp = tail;
  tail ++;
  tail = tail % 300;
  if(tail == head){
     tail = temp;
     digitalWrite( 3, digitalRead( 3 ) ^ 1 );
     return -1;
  } 
  buffed--;
  return buf[tail];
}
// main loop - wait for flag set in interrupt routine
int index = 0;
int strip_index = 0;
void loop (void)
{
  if(buffed > 2){
          strip.setPixelColor(strip_index, strip.Color(ringRemove(),ringRemove(),ringRemove()));
          strip_index++;
          //strip.show();
          //if(strip_index >= frame_size){
           // strip_index = 0;
           // swap_ready = 0;
            //while(swap_ready == 1){
               //do nothing
            //}
            
          //}
          //receivingState = 0; 
          if(strip_index >= 50){
              strip_index = 0;
          }  
  }
    
}  // end of loop

void timerIsr()
{
    
    strip.show();
    
}
