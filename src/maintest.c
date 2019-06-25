#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

#include "constants.h"
#include "boolean.h"
#include "cmdargs/cmdargs.h"
#include "hal/hal.h"

void handleSimpleBlink(CommandlineArguments *cmdArgs);
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

    handleSimpleBlink(cmdArgs);
}

void handleSimpleBlink(CommandlineArguments *cmdArgs) {
    while(1) {
        if(cmdArgs->enableRed) togglePin(REDPIN);
        if(cmdArgs->enableBlue) togglePin(BLUEPIN);
        if(cmdArgs->enableGreen) togglePin(GREENPIN);
        sleep(cmdArgs->blinkInterval);
    }
}


