#include <stdio.h>

#include "../boolean.h"
#include "hal.h"

#ifdef BUILD_RASPBERRY

// wiringPi & softPwm are only available on RaspberryPIs
#include <wiringPi.h>
#include <softPwm.h>

int REDPINVALUE = DIGITAL_OFF;
int BLUEPINVALUE = DIGITAL_OFF;
int GREENPINVALUE = DIGITAL_OFF;
PinConfiguration *GLOBALPINCONFIG;

void initializeHal(PinConfiguration *pinConfiguration) {
    GLOBALPINCONFIG = pinConfiguration; /* Set pinConfiguration globally */
    softPwmCreate(GLOBALPINCONFIG->redPin, 0, 100);
    softPwmCreate(GLOBALPINCONFIG->bluePin, 0, 100);
    softPwmCreate(GLOBALPINCONFIG->greenPin, 0, 100);
    if (wiringPiSetup() == -1) {
        printf("Initialization of wiringPi failed!");
    }
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

    softPwmWrite(pinNumber, value);
}

void togglePin(int pinNumber) {
    if(getPin(pinNumber) == DIGITAL_ON) {
        setPin(pinNumber, DIGITAL_OFF);
    } else {
        setPin(pinNumber, DIGITAL_ON);
    }
}

#endif