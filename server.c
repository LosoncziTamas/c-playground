#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

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
    const int fd = socket(AF_INET, SOCK_STREAM, PF_UNSPEC);
    checkError(fd);

	struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(2045);

    // Binding the socket the the specified port & address.
    int result = bind(fd, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
    checkError(result);

    // Wait for clients, second parameter defines the maximum length
    // to which the queue of pending connections for fd may grow
    result = listen(fd, 1);
    checkError(result);

    socklen_t addressLen = sizeof(serverAddress);
    const int client = accept(fd, (struct sockaddr*) &serverAddress, &addressLen);
    checkError(client);

    char buffer[256];
    // Result is not an error if this number is smaller than the number of bytes requested.
    ssize_t bytesRead = read(client, buffer, 256);
    checkError(bytesRead);
    puts(buffer);

    char* message = "Hello from server";
    ssize_t bytesSent = send(client, message, strlen(message) + 1, 0);
    checkError(bytesSent);

    return 0;
}