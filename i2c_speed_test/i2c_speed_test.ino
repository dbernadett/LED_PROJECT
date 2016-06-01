#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <TimerOne.h>
#define PIN 6
#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
char red;
char green;
char blue;
char receivingState = 0;
char frame_size = 50;
char strip_index = 0;
boolean swap_ready = 0;
int last_time = 0;
void setup() {
 pinMode(13, OUTPUT);
 Serial.begin(9600);
 strip.begin();
 //Timer1.initialize(33333);
 //Timer1.initialize(500000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
 //Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}

 
void loop() {
  last_time = millis();
  for(int i  = 0; i <= 225; i+=15){
      //Serial.print(i);
    
      char color = i;
      colorWipe(strip.Color(color,color,color),0);
      strip.show();
      delay(19);
      delayMicroseconds(407);
      digitalWrite( 13, digitalRead( 13 ) ^ 1 );
  }
  for(int i  = 225; i >= 0 ; i-=15){
      //Serial.print(i);
    
      char color = i;
      colorWipe(strip.Color(color,color,color),0);
      strip.show();
      delay(19);
      delayMicroseconds(407);
      digitalWrite( 13, digitalRead( 13 ) ^ 1 );
  }
  
   Serial.println(millis() - last_time);
   
}
 
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i< frame_size; i++) {
      strip.setPixelColor(i, c);
  }
}


void timerIsr()
{
    
    strip.show();
    swap_ready = 1;
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
}
