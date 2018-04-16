#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

#define PERM 0666

void client(int rfd, int wfd) {
	printf("Enter filename: ");
	char filename[20], buffer[1024];
	int n;
	scanf("%s", filename);
	write(wfd, filename, strlen(filename));
	while(n=read(rfd, buffer, sizeof(buffer))) {
		printf("%s", buffer);
		if(n!=1024) break;
	}
	close(rfd);
	close(wfd);
}

int main() {
	int rfd, wfd;
	wfd = open(FIFO1, O_WRONLY);
	rfd = open(FIFO2, O_RDONLY);
	client(rfd, wfd);
	return 0;
}