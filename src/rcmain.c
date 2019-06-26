# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

void err_exit(char *message) {
    perror(message);
    exit(1);
}

int main(int argc, char **argv) {
    fd_set input_fdset;
    int sock_fd, client_fd, length;
    static char buffer[sizeof(int)];
    struct sockaddr_in my_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);;

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) printf("socket-creation failed");

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8080);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) == -1)
        err_exit("bind() failed");

    if (listen(sock_fd, 1) == -1) 
        err_exit("listen() failed");

    client_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &addr_size);
    if (client_fd == -1) 
        err_exit("accept() failed");

    printf("Remote-Controller connected from: %s\n", inet_ntoa(client_addr.sin_addr));

    while (1) {
        FD_ZERO(&input_fdset);
        FD_SET(STDIN_FILENO, &input_fdset);
        FD_SET(client_fd, &input_fdset);

        if (select(client_fd+1, &input_fdset, NULL, NULL, NULL) == -1)
            err_exit("select() failed");
        
        if (FD_ISSET(STDIN_FILENO, &input_fdset)) {
            if (fgets(buffer, 256, stdin) == NULL) {
                printf("Closing socket.\n");
                break;
            }

            length = strlen(buffer);
            send(client_fd, buffer, length, 0);
        }

        else {
            length = recv(client_fd, buffer, sizeof(int), 0);
            if (length == 0) {
                printf("Connection closed by remote host.\n");
                break;
            }

            write(STDOUT_FILENO, buffer, length);
        }
    }
    close(client_fd);
    close(sock_fd);
    return(0);
}