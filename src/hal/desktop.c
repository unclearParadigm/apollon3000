#include <stdio.h>

#include "../boolean.h"
#include "hal.h"

#ifdef BUILD_DESKTOP

int REDPINVALUE = DIGITAL_OFF;
int BLUEPINVALUE = DIGITAL_OFF;
int GREENPINVALUE = DIGITAL_OFF;
PinConfiguration *GLOBALPINCONFIG;

void initializeHal(PinConfiguration *pinConfiguration) {
    GLOBALPINCONFIG = pinConfiguration; /* Set pinConfiguration globally */

    printf("Initialize red LED on PIN: %d\n", pinConfiguration->redPin);
    printf("Initialize blue LED on PIN: %d\n", pinConfiguration->bluePin);
    printf("Initialize green LED on PIN: %d\n", pinConfiguration->greenPin);
}

int getPin(int pinNumber) {
    if(pinNumber == GLOBALPINCONFIG->redPin) return REDPINVALUE;
    if(pinNumber == GLOBALPINCONFIG->bluePin) return BLUEPINVALUE;
    if(pinNumber == GLOBALPINCONFIG->greenPin) return GREENPINVALUE;
    return -1;
}

void setPin(int pinNumber, int value) {
    if(pinNumber == GLOBALPINCONFIG->redPin) REDPINVALUE = value;
    if(pinNumber == GLOBALPINCONFIG->bluePin) BLUEPINVALUE = value;
    if(pinNumber == GLOBALPINCONFIG->greenPin) GREENPINVALUE = value;

    if(value == DIGITAL_ON) {
        printf("Set Pin '%d' to ON\n", pinNumber);
    } else if(value == DIGITAL_OFF) {
        printf("Set Pin '%d' to OFF\n", pinNumber);
    } else  {
        printf("Set Pin '%d' to value dimmed %d\n", pinNumber, value);
    }
}

void togglePin(int pinNumber) {
    if(getPin(pinNumber) == DIGITAL_ON) {
        setPin(pinNumber, DIGITAL_OFF);
    } else {
        setPin(pinNumber, DIGITAL_ON);
    }
}

#endif