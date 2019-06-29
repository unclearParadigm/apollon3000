# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

#include "boolean.h"
#include "constants.h"
#include "hal/hal.h"


void startListeningForCommands();


int main(int argc, char **argv) {
    /* Configure PIN-Assignment */
    PinConfiguration *pinConfig = malloc(sizeof(PinConfiguration));
    pinConfig->redPin = REDPIN;
    pinConfig->bluePin = BLUEPIN;
    pinConfig->greenPin = GREENPIN;

    /* Initialize Hardware Abstraction Layer */
    initializeHal(pinConfig);

    while(1) {
        startListeningForCommands();
        printf("Restart Listening on TCP-Socket");
    }

    return(0);
}


void startListeningForCommands() {
    fd_set input_fdset;
    int sock_fd, client_fd, length;
    static char buffer[sizeof(int)];
    struct sockaddr_in my_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1) printf("socket-creation failed");

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(TCPPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) == -1) {
        printf("bind() failed");
        return;
    }
    
    if (listen(sock_fd, 1) == -1)  {
        printf("listen() failed");
        return;
    }
    client_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &addr_size);
    if (client_fd == -1) {
        printf("accept() failed");
        return;
    }

    printf("Remote-Controller connected from: %s\n", inet_ntoa(client_addr.sin_addr));

    while (1) { /* Client connected - start "receive"-loop */
        FD_ZERO(&input_fdset);
        FD_SET(client_fd, &input_fdset);
        FD_SET(STDIN_FILENO, &input_fdset);
  
        if (select(client_fd+1, &input_fdset, NULL, NULL, NULL) == -1) {
            printf("select() failed");
            break;
        }
        
        length = recv(client_fd, buffer, sizeof(int), 0);
        if (length == 0) {
            printf("Connection closed by remote host.\n");
            break;
        }

        int pinValue = atoi(buffer);
        setPin(REDPIN, pinValue);
        setPin(BLUEPIN, pinValue);
        setPin(GREENPIN, pinValue);
    }

    close(client_fd);
    close(sock_fd);
}