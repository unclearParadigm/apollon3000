#ifndef HAL_H_
#define HAL_H_

#define DIGITAL_ON  100
#define DIGITAL_OFF 0

struct PinConfiguration {
    int redPin;
    int bluePin;
    int greenPin;
};

typedef struct PinConfiguration PinConfiguration;

void initializeHal(PinConfiguration *pinConfiguration);

int getPin(int pinNumber);
void setPin(int pinNumber, int value);
void togglePin(int pinNumber);

#endif