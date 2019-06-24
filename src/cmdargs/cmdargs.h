#include "../boolean.h"

#ifndef CMDARGS_H_
#define CMDARGS_H_

struct CommandlineArguments {
    bool        enableRed;
    bool        enableBlue;
    bool        enableGreen;

    bool        sweepActivated;
    int         intensity;
    int         blinkInterval;

    bool        verbose;
};

typedef struct CommandlineArguments CommandlineArguments;


void    printCommandlineArguments   (CommandlineArguments *cmdArgs);
int     parseCommandlineArguments   (int argc, char *argv[], CommandlineArguments *cmdArgs);

#endif