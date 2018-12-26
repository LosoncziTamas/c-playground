#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>

int main() {

    // Creates an IPv4 TCP socket.
    int fd = socket(AF_INET, SOCK_STREAM, PF_UNSPEC);
    assert(fd != -1);

    // Setup server protocol, address, portnumber.
	struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // htons converts the port number into a Big Endian short integer.
    serverAddress.sin_port = htons(2045);

    int result = connect(fd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    assert(result != -1);

    char buff[256];
    // Receive data in buffer.
    size_t len = recv(fd, buff, 255, 0);
    buff[255] = '\0';

    close(fd);

    return 0;
}