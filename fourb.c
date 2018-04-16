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


int main()  {
	struct sockaddr_in servaddr, clientaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(host);
	// servaddr.sin_addr.s_addr = INADDR_ANY;
	int fd;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(fd, 10);
	int cfd;
	int scladdr = sizeof(clientaddr);
	cfd = accept(fd, (struct sockaddr *)&clientaddr, &scladdr);
	char filename[20], buffer[1024];
	int n = recv(cfd, filename, sizeof(filename), 0);
	filename[n] = '\0';
	printf("%s\n", filename);
	int ffd = open(filename, O_RDONLY);
	while(n=read(ffd, buffer, sizeof(buffer))) {
		send(cfd, buffer, n, 0);
	}
	close(cfd);
	close(ffd);
	close(fd);
	return 0;
}