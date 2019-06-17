#include <wiringPi.h>
#include <softPwm.h>

#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>

#define   REDPIN    0
#define   BLUEPIN   23
#define   GREENPIN  21

typedef   int       bool;
#define   True      1
#define   False     0

int initializeGPIO();

int main(int argc, char *argv[]) {
  if(initializeGPIO() != 0) {
    printf("Could not initialize GPIOs");
  }


  softPwmCreate(BLUEPIN, 0, 100);
  softPwmWrite(BLUEPIN, 50);
  delay(50);

  int c = 0;
  bool sweepActivated = False;
  bool pwmEnable= False;
  char *colors;
  int blinkInterval = 0;
  int intensity = 100;
  
  while ((c = getopt (argc, argv, "c:i:b:s")) != -1)
    switch (c) {
      case 's':
        sweepActivated = True;
        pwmEnable = True;
        break;
      case 'b':
        blinkInterval = atoi(optarg);
        break;
      case 'c':
        colors = optarg;
        break;
      case 'i':
        intensity = atoi(optarg);
        break;
      default:
        printf("RTFM");
        abort();
    }

  if(intensity != 0 && intensity != 100) {
    pwmEnable = True;
  }
  
  printf("Your Selection: ");
  printf("Intensity      = %d\n", intensity);
  printf("BlinkInterval  = %d\n", blinkInterval);
  printf("SweepActivated = %d\n", sweepActivated);
  printf("Colors         = %s\n", colors);
  printf("UsePWM         = %d\n", pwmEnable);
  printf("==============================");
  
  if (strstr(colors, "r") != NULL) {
    if(pwmEnable == False) {
      pinMode(REDPIN, OUTPUT);
    } else {
      softPwmCreate(REDPIN, 0, 100);
    }
  }
  
  if (strstr(colors, "g") != NULL) {
    if(pwmEnable == False) {
      pinMode(GREENPIN, OUTPUT);
    } else {
      softPwmCreate(GREENPIN, 0, 100);
    }
  }
  
  if (strstr(colors, "b") != NULL) {
    if(pwmEnable == False) {
      pinMode(BLUEPIN, OUTPUT);
    } else {
      softPwmCreate(BLUEPIN, 0, 100);
    }
  }
  
  while(1) {
    if (strstr(colors, "r") != NULL) {
      if(pwmEnable == False) {
          if(intensity == 100) {
            digitalWrite(REDPIN, 1);
          }
          else {
            digitalWrite(REDPIN, 0);
          }
      } else {
        softPwmWrite(REDPIN, intensity);
      }
    }
    
    if (strstr(colors, "g") != NULL) {
      if(pwmEnable  == False) {
          if(intensity == 100) {
            digitalWrite(GREENPIN, 1);
          }
          else {
            digitalWrite(GREENPIN, 0);
          }
      } else {
        printf("GREEN PWM to %d\n", intensity);
        softPwmWrite(GREENPIN, intensity);
      }
    }
    
    if (strstr(colors, "b") != NULL) {
      if(pwmEnable  == False) {
          if(intensity == 100) {
            digitalWrite(BLUEPIN, 1);
          }
          else {
            digitalWrite(BLUEPIN, 0);
          }
      } else {
        printf("BLUE PWM to %d\n", intensity);
        softPwmWrite(BLUEPIN, intensity);
      }
    }
    
    if(blinkInterval == 0) {
      printf("GOODBOY\n");
      return 0;
    }
    
    delay(blinkInterval);
    if(blinkInterval != 0) {
      if(intensity == 100) {
        intensity = 0;
      } else {
        intensity = 100;
      }
    } 
  }
  
  
/*
  softPwmCreate(bluePinWiringPi, 0, 100);
  softPwmCreate(bluePinWiringPi, 0, 100);
  softPwmWrite(bluePinWiringPi, 50);
  delay(30000);

  pinMode(bluePinWiringPi, OUTPUT);
  pinMode(greenPinWiringPi, OUTPUT);

  // Dauerschleife
  while(1) {
    // LED an

    digitalWrite(bluePinWiringPi, 1);
    digitalWrite(greenPinWiringPi, 0);

    // Warte 100 ms
    delay(100);

    // LED aus
    digitalWrite(bluePinWiringPi, 0);
    digitalWrite(greenPinWiringPi, 1);

    delay(100);
  }
  */
  return 0;
}


int initializeGPIO() {
    if (wiringPiSetup() == -1)
      return 1;
    return 0;
}
