#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <TimerOne.h>

#define PIN 6
#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_GRB + NEO_KHZ800);
double temp;
int address;
int red;
int green;
int blue;
int receivingState = 0;
int frame_size = 50;
int strip_index = 0;
int swap_ready = 0;
int count = 0;
void setup() {
 pinMode(13, OUTPUT);
 Serial.begin(9600);
 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 //Wire.setClock(400000L);
 // define callbacks for i2c communication
 Wire.onReceive(receiveData);
 //Wire.onRequest(sendData);
 strip.begin();
 //Timer1.initialize(33333);
 //Timer1.initialize(20000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
 //Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}
 
void loop() {

}
 
// callback for received data
void receiveData(int byteCount){
 while(Wire.available()) {
  number = Wire.read();
  count++;  
    if(number == 193){
      Serial.println(count);
      count = 0;  
    }  
 }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
}
// callback for sending data
void sendData(){
 Wire.write(receivingState);
}

void timerIsr()
{
    strip.show();
    swap_ready = 1;
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
}
