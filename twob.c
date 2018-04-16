#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

#define PERM 0666

void server(int rfd, int wfd) {
	char filename[20], buffer[1024];
	int ffd, n;
	n = read(rfd, filename, sizeof(filename));
	filename[n] = '\0';
	ffd = open(filename, O_RDONLY);
	while(n=read(ffd, buffer, sizeof(buffer))) {
		write(wfd, buffer, n);
	}
	close(rfd);
	close(wfd);
}

int main() {
	int rfd, wfd;
	rfd = mkfifo(FIFO1, PERM);
	wfd = mkfifo(FIFO2, PERM);
	rfd = open(FIFO1, O_RDONLY);
	wfd = open(FIFO2, O_WRONLY);
	puts("server calling");
	server(rfd, wfd);
	unlink(FIFO1);
	unlink(FIFO2);
	return 0;
}