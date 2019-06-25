# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

void err_exit(char *message){
    perror(message);
    exit(1);
}

int main(int argc, char *argv[]){
    static int buffer[256];
    int sock_fd, client_fd, port, err, length;
    socklen_t addr_size;
    struct sockaddr_in my_addr, client_addr;
    fd_set input_fdset;

    if ((argc != 2) || (strcmp(argv[1], "-h") == 0)){
    fprintf(stderr, "Usage: server port\n");
    return(1);
    }

    if (sscanf(argv[1], "%d", &port) != 1){
    fprintf(stderr, "server: Bad port number.\n");
    return(1);
    }

    /*--- socket() ---*/
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
    err_exit("server: Can not create new socket");

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    /*--- bind() ---*/
    err = bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));
    if (err == -1)
    err_exit("server: bind() failed");

    /*--- listen() ---*/
    err = listen(sock_fd, 1);  
    if (err == -1)
    err_exit("server: listen() failed");

    /*--- accept() ---*/
    addr_size = sizeof(struct sockaddr_in);
    client_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &addr_size);
    if (client_fd == -1)
    err_exit("server: accept() failed");
    printf("I am a SysProg Dude and connected from %s\n",
    inet_ntoa(client_addr.sin_addr));

    while (1) {
        FD_ZERO(&input_fdset);
        FD_SET(client_fd, &input_fdset);

        length = recv(client_fd, buffer, sizeof(int), 0);
        if (length != sizeof(int)) {
            printf("Connection closed by remote host.\n");
            break;
        }
        write(STDOUT_FILENO, buffer, length);
    }
    close(client_fd);
    close(sock_fd);
    return(0);
}







