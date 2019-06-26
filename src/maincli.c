#define _POSIX_C_SOURCE 199309L /* shall be >= 199309L */

#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

#include "constants.h"
#include "boolean.h"
#include "cmdargs/cmdargs.h"
#include "hal/hal.h"

void handleSimpleBlink(CommandlineArguments *cmdArgs);
void handleBlinkWithSweep(CommandlineArguments *cmdArgs);
void handleCommandlineArguments(CommandlineArguments *cmdArgs);

int main(int argc, char *argv[]) {
    /* Configure PIN-Assignment */
    PinConfiguration *pinConfig = malloc(sizeof(PinConfiguration));
    pinConfig->redPin = REDPIN;
    pinConfig->bluePin = BLUEPIN;
    pinConfig->greenPin = GREENPIN;

    /* Parse Commandline Arguments */
    CommandlineArguments *cmdArgs = malloc(sizeof(CommandlineArguments));
    if(parseCommandlineArguments(argc, argv, cmdArgs) != 0) return -1;
    if(cmdArgs->verbose == True) printCommandlineArguments(cmdArgs);

    /* Initialize HAL (=Hardware Abstraction Layer) */
    initializeHal(pinConfig);

    /* Handle commands by CLI */
    handleCommandlineArguments(cmdArgs);

    printf("Goodbye!");
  return 0;
}

void handleCommandlineArguments(CommandlineArguments *cmdArgs) {
    if(cmdArgs->blinkInterval <= 0 && cmdArgs->sweepActivated == False) {
        /* Static Operation, no blinking, no dimming - just turning on LEDs */
        if(cmdArgs->enableRed) setPin(REDPIN, DIGITAL_ON);
        if(cmdArgs->enableBlue) setPin(BLUEPIN, DIGITAL_ON);
        if(cmdArgs->enableGreen) setPin(GREENPIN, DIGITAL_ON);
        return;
    }

    if(cmdArgs->blinkInterval > 0 && cmdArgs->sweepActivated == False) {
        /* Simple Blinking, only on and off */
        handleSimpleBlink(cmdArgs);
        return;
    }

    handleBlinkWithSweep(cmdArgs);
}

void handleSimpleBlink(CommandlineArguments *cmdArgs) {
    // ____|****|____|****|____|****|____
    // blinkIntervalSeconds off / low
    // blinkIntervalSeconds on / high

    long totalSeconds = cmdArgs->blinkInterval / 1000;
    long totalMilliSeconds = (cmdArgs->blinkInterval - (totalSeconds * 1000));
    struct timespec sleepDelay = {0};
    sleepDelay.tv_sec = totalSeconds;
    sleepDelay.tv_nsec = totalMilliSeconds * 1000000;

    while(1) {
        if(cmdArgs->enableRed) togglePin(REDPIN);
        if(cmdArgs->enableBlue) togglePin(BLUEPIN);
        if(cmdArgs->enableGreen) togglePin(GREENPIN);
        nanosleep(&sleepDelay, (struct timespec *)NULL);
    }
}

void handleBlinkWithSweep(CommandlineArguments *cmdArgs) {
    struct timespec sleepDelay = {0};
    long totalSeconds = cmdArgs->blinkInterval / 100000;
    long totalMilliSeconds = (cmdArgs->blinkInterval - (totalSeconds * 1000));
    sleepDelay.tv_sec = totalSeconds;
    sleepDelay.tv_nsec = totalMilliSeconds * 10000L;

    while(1) {
        for(int i = DIGITAL_OFF; i <= DIGITAL_ON; i++) {
            if(cmdArgs->enableRed) setPin(REDPIN, i);
            if(cmdArgs->enableBlue) setPin(BLUEPIN, i);
            if(cmdArgs->enableGreen) setPin(GREENPIN, i);
            nanosleep(&sleepDelay, (struct timespec *)NULL);
        }

        for(int i = DIGITAL_ON; i >= DIGITAL_OFF; i--) {
            if(cmdArgs->enableRed) setPin(REDPIN, i);
            if(cmdArgs->enableBlue) setPin(BLUEPIN, i);
            if(cmdArgs->enableGreen) setPin(GREENPIN, i);
            nanosleep(&sleepDelay, (struct timespec *)NULL);
        }
    }
}
