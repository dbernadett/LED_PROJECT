# Syncronized_LED_Strip
The purpose of this project is to sync LED Strip colors to music. I wanted this to be portable and small, so I chose to design it for the Raspberry PI. The end goal is that given a mp3, and a file of led timings, the led will change color when the music reaches the specified time. This project used a lot of different things, and I highly suggest trying each one on its own before combining them to make the final project.

## Raspberry PI
Pinout:
http://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/06/Raspberry-Pi-GPIO-Layout-Model-B-Plus-rotated-2700x900.png

The raspberry pi is a small computer that runs a non-real time operating system. This means that timings of changing the led strip cannot be garenteed and will fluctuate. In order to handle this, the timing is enforced by the Arduino. Data will be buffered on some level, so that the jitters of the Raspberry pi do not cause pauses or bursts in the visual playback. 

The operating system of choice is Raspbian, specifically the lite version as a gui is not needed. All code can either be typed into the terminal, or transfered to the pi using things such as git or rsync. 

## Arduino

Arduino is an atmel microprocessor that is easily programmed at a higher level thanks to the abstractions provided by the Arduino language. The processor is single threaded and can be interupted by timers which make it a good candidate for handling the timings of the led strip.

To work on the arduino, the Arduino IDE must be installed. Once this is done, you can find the "sketchbook" folder for your development computer (not the rpi). In this there is a libraries folder, and installing new libraries is as easy as dropping an unzipped library folder into this folder. When the Arduino IDE is restarted, your libraries will be there. 

## Light Strip
The light strip is a fairly generic one with three wires, 5v+, GND and Data. These can be purchased for cheap off of ebay with a really long shipping wait. If you neeed it sooner, you can also look at Adafruit and Sparkfun, they will have them in stock.

To test the light strip, you need a fairly beefy 5v power supply, an arduino, and a computer to program said arduino. 
Simply add the neopixel library to your libraries folder underneath "sketchbook". You should then be able to import the library from the Arduino IDE, which will add a line of code to your sketch allowing you to use the library.

There is also example code in the library that can allow you to test and play with the led strip easily.

Hello World Tutorial: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library
## HIFI Berry Dac

The raspberry PI has a PWM audio output which is garbage, especially at low volumes when the PWM doesn't have enough resolution. To fix this, one can use an external DAC. The HIFI Berry Dac+ is the one I used and it works well.

Setup Tutorial: https://www.hifiberry.com/guides/configuring-linux-3-18-x/
A couple of notes on the setup tutorial. First, some lines that need to be deleted from files do not exist. This is fine, just procede normaly. If the entire file doesn't exist, don't worry about it.
Secondly, to test that it is working, play music using anything. If you want to change volume, use Amixer. When I used a mixer, I got a ton of possible "mixers" the only important really is the "Digital" control, which shows it has values up to 2XX (two-hundred and something). This is the right volume control, but it does seem to break the ability to change volume from XMMS2

## XMMS2
XMMS2 is program which runs in the background and plays audio files. It is an alternative to MPD. To install it, use apt-get install xmms2.
The following tutorial will help you use it. I suggest trying this seperately from the HIFI Berry and just use the HDMI audio output or the PWM output to test that it is working properly.

Hello World Turorial: https://xmms2.org/wiki/Using_the_application
## I2C

I2C is a way for the raspberry pi and Arduino to talk to each other. It allows a master to talk to many slave devices. Each slave has a unique address, that the master can talk to.  For this project I had a hard time sending a lot of data to the arduino at once, and need to look into ways to make the connection very reliable and fast. 

Hello World Tutorial: https://blog.retep.org/2014/02/15/connecting-an-arduino-to-a-raspberry-pi-using-i2c/
## SPI

SPI is another way for the raspberry pi and arduino to talk to each other. This one has sepeate wires for data in and data out. The master decides which device to talk to using a seperate wire for each device. This is different from the addressing scheme of i2c. I also had problems getting this to be fast and reliable. 

Hello World Tutorial: http://mitchtech.net/raspberry-pi-arduino-spi/
## Timing

The arduino has a timer on it that can cause an interrupt. To get access to this timer from arduino code, you need to add this library. 

Documentation of TimerOne: http://playground.arduino.cc/Code/Timer1

# State of the Project
currently, my code contains the arduino libraries I was using and the c code for the raspberry pi. A lot of the files are testing differnet aspects of the connection between the arduino and raspberry pi. Nothing can really pass as the end project and there is a lot of commented out code that was switch on and off for debugging purposes.  


