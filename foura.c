#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>

#define host "127.0.0.1"
#define port 31337

int main() {
	struct sockaddr_in clientaddr, servaddr;
	char filename[20], buffer[1024];
	int fd;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(host);
	connect(fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	printf("Enter filename:");
	scanf("%s", filename);
	send(fd, filename, strlen(filename),0);
	while(recv(fd, buffer, sizeof(buffer), 0)) {
		printf("%s", buffer);
	}
	close(fd);
	return 0;
}