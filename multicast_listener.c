#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<stdlib.h>

#define GROUP "225.0.0.38"
#define port 1337

int main() {
	struct sockaddr_in addr;
	struct ip_mreq mreq;
	char buf[1024];

	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int fd;
	int yes=1;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0) {
		puts("error fd");
		exit(0);
	}

	if(bind(fd, (struct sockaddr *)&addr, sizeof(addr))) {
		puts("error");
		exit(0);
	}

      mreq.imr_multiaddr.s_addr = inet_addr(GROUP);         
      mreq.imr_interface.s_addr = htonl(INADDR_ANY); 
	if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq))<0) {
		puts("multicast error");
		exit(0);
	}
	int addrlen, n;
	addrlen = sizeof(addr);
	while(1) {
		addrlen = sizeof(addr);
		n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addrlen);
		if(n<0) {
			puts("error");
			exit(0);
		} else if(n==0) {
			break;
		}
		buf[n] = '\0';
		printf("%s\n", buf);
	}
	return 0;
}