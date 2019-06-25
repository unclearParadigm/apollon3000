#include <stdio.h>

#include "../boolean.h"
#include "hal.h"

#ifdef BUILD_DESKTOP

void initializeHal(PinConfiguration *pinConfiguration) {
    printf("Initialize red LED on PIN: %d", pinConfiguration->redPin);
    printf("Initialize blue LED on PIN: %d", pinConfiguration->bluePin);
    printf("Initialize green LED on PIN: %d", pinConfiguration->greenPin);
}

void setPin(int pinNumber, int value) {
    if(value == DIGITAL_ON) {
        printf("Set Pin '%d' to ON", pinNumber);
    } else if(value == DIGITAL_OFF) {
        printf("Set Pin '%d' to ON", pinNumber);
    } else  {
        printf("Set Pin '%d' to value dimmed %d", pinNumber, value);
    }
}

#endif