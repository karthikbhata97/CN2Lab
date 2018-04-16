#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<stdlib.h>


#define GROUP "225.0.0.38"
#define PORT 1337

int main() {
	int fd, addrlen;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(GROUP);
	addrlen = sizeof(addr);
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	char *message = "Hello from the other side!";
	while(1) {
		sendto(fd, message, strlen(message), 0, (struct sockaddr *)&addr, addrlen);
		puts("Sent");
		sleep(1);
	}
	return 0;
}