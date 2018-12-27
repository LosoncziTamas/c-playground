#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void checkError(const int result)
{
    if (result == -1)
    {
        perror("The following error occurred");
        exit(1);
    }
}

int main() 
{
    // Creates an IPv4 TCP socket.
    int fd = socket(AF_INET, SOCK_STREAM, PF_UNSPEC);
    checkError(fd);

    // Setup server protocol, address, portnumber.
	struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // htons converts the port number into a Big Endian short integer.
    serverAddress.sin_port = htons(2045);

    int result = connect(fd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    checkError(result);

    char* message = "Hello from client";
    ssize_t bytesSent = send(fd, message, strlen(message), 0);
    checkError(bytesSent);

    char buffer[256];
    ssize_t bytesRead = read(fd, buffer, 256);
    checkError(bytesRead);
    puts(buffer);

    close(fd);

    return 0;
}