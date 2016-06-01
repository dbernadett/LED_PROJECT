#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define CLOCK CLOCK_MONOTONIC
 
// The PiWeather board i2c address
#define ADDRESS 0x04
 
// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";
int frame_size = 50;
 
int main(int argc, char** argv) {
 
  if (argc == 1) {
    printf("Supply one or more commands to send to the Arduino\n");
    exit(1);
  }
 
  printf("I2C: Connecting\n");
  int file;
 
  if ((file = open(devName, O_RDWR)) < 0) {
    fprintf(stderr, "I2C: Failed to access %d\n", devName);
    exit(1);
  }
 
  printf("I2C: acquiring buss to 0x%x\n", ADDRESS);
 
  if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
    fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
    exit(1);
  }
 
  int arg;
  int color = 0;
  for (arg = 1; arg < argc; arg++) {
    int val;
    unsigned char cmd[16];
 
    if (0 == sscanf(argv[arg], "%d", &val)) {
      fprintf(stderr, "Invalid parameter %d \"%s\"\n", arg, argv[arg]);
     exit(1);
    }
    struct timespec requestStart, requestEnd, req;
    double elapsed;
    // Pseudo-sleep
    clock_gettime(CLOCK, &requestStart);
    printf("Sending %d\n", val);
    int j;
    for(j = 0; j< frame_size; j++){ 
      
      cmd[0] = 0;
      cmd[1] = 0;
      cmd[2] = 0;
      cmd[color%3] = val;
      write(file,cmd, 3);
      usleep(1000);
    }
    color ++;
    if (1 == 1) {
 
      // As we are not talking to direct hardware but a microcontroller we
      // need to wait a short while so that it can respond.
      //
      // 1ms seems to be enough but it depends on what workload it has
      //usleep(50000);
      //usleep(50000);
      char buf[1];
      //if (read(file, buf, 3) == 3) {
    //int temp = (int) buf[0];
 
   // printf("Received %d\n", temp);
    //  }
    }
    // Now wait else you could crash the arduino by sending requests too fast
    usleep(10000); 
    clock_gettime(CLOCK, &requestEnd);
    elapsed = ( requestEnd.tv_sec - requestStart.tv_sec ) / 1e-6
                 + ( requestEnd.tv_nsec - requestStart.tv_nsec ) / 1e3;
	
    printf("Elapsed: %lf us\n", elapsed);
  }
 
  close(file);
  return (EXIT_SUCCESS);
}
