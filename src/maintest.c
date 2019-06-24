#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>

#include "constants.h"
#include "boolean.h"
#include "cmdargs/cmdargs.h"
#include "hal/hal.h"

int main(int argc, char *argv[]) {
    CommandlineArguments *cmdArgs = malloc(sizeof(CommandlineArguments));
    if(parseCommandlineArguments(argc, argv, cmdArgs) != 0) 
        return -1;

    if(cmdArgs->verbose == True) {
        printCommandlineArguments(cmdArgs);
    }


    printf("Goodbye!");
  return 0;
}

