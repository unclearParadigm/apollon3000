#include <wiringPi.h>
#include <softPwm.h>

#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <stdio.h>

#define SERVER_PORT 8080

int main() {
	int redPinPhysical = 25; // geht net
	int bluePinPhysical = 13; // geht - WiringPi pin2
	int greenPinPhysical = 5; // geht ah - WiringPi pin9
	int redPinWiringPi = 0;
	int bluePinWiringPi = 23;
	int greenPinWiringPi = 21;

if (wiringPiSetup() == -1)
    return 1;

  pinMode(bluePinWiringPi, OUTPUT);
  digitalWrite(bluePinWiringPi, 1);
  delay(5000);

  softPwmCreate(bluePinWiringPi, 0, 100);
  softPwmWrite(bluePinWiringPi, 50);
  delay(30000);

  // Schalte GPIO 17 (=WiringPi Pin 0) auf Ausgang
  // Wichtig: Hier wird das WiringPi Layout verwendet (Tabelle oben)
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

    // Warte 100 ms
    delay(100);
  }
}