#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	int p1[2], p2[2];
	pipe(p1);
	pipe(p2);
	if(fork()==0) {
		close(p1[1]);
		close(p2[0]);
		client(p1[0], p2[1]);
	}
	else {
		close(p1[0]);
		close(p2[1]);
		server(p2[0], p1[1]);		
	}
	return 0;
}