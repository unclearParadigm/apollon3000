#include <stdio.h>
#include <unistd.h> 
#include <getopt.h>
#include <string.h>
#include <stdlib.h> 

#include "../boolean.h"
#include "cmdargs.h"

void printCommandlineArguments(CommandlineArguments *cmdArgs) {
    
    printf("\nYour Selection: \n");
    printf("*************** \n\n");
    printf("Enable Red LED      =    %d\n", cmdArgs->enableRed);
    printf("Enable Blue LED     =    %d\n", cmdArgs->enableBlue);
    printf("Enable Green LED    =    %d\n\n", cmdArgs->enableGreen);

    printf("LED Intensity       =    %d\n", cmdArgs->intensity);
    printf("Blink Interval      =    %d\n", cmdArgs->blinkInterval);
    printf("Sweep Activated     =    %d\n\n", cmdArgs->sweepActivated);

    printf("Verbose             =    %d\n", cmdArgs->verbose);
    printf("=======================================================\n");
}

void setDefaultArguments(CommandlineArguments *cmdArgs) {
    cmdArgs->enableRed = False;
    cmdArgs->enableBlue = False;
    cmdArgs->enableGreen = False;

    cmdArgs->intensity = 0;
    cmdArgs->blinkInterval = 0;
    cmdArgs->sweepActivated = False;

    cmdArgs->verbose = False;
}

int parseCommandlineArguments(int argc, char *argv[], CommandlineArguments *cmdArgs) {
    int c = 0;
    setDefaultArguments(cmdArgs);

    while ((c = getopt (argc, argv, "c:i:b:sv")) != -1) {
        switch (c) {

            case 'b':
                cmdArgs->blinkInterval = atoi(optarg);
                break;

            case 'c':
                if (strstr(optarg, "r") != NULL) 
                    cmdArgs->enableRed = True;
                if (strstr(optarg, "b") != NULL) 
                    cmdArgs->enableBlue = True;
                if (strstr(optarg, "g") != NULL)
                    cmdArgs->enableGreen = True;
                break;

            case 'i':
                cmdArgs->intensity = atoi(optarg);
                break;

            case 's':
                cmdArgs->sweepActivated = True;
                break;

            case 'v':
                cmdArgs->verbose = True;
                break;

            default:
                printf("Please refer to the documentation.");
                return -1;
        }
    }
    return 0;
}