#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct messageq
{
	long int type;
	char text[1024];
}msg_buf;


int main() {
	key_t key1, key2, newk;
	int sid, rid;
	key1 = ftok("an0ne", 32); //1234
	key2 = ftok("an0ne", 64); //5678
	printf("%d %d\n", key1, key2);
	rid = msgget(key1, 0666 | IPC_CREAT);
	sid = msgget(key2, 0666 | IPC_CREAT);
	printf("%d %d\n", rid, sid);
	msg_buf.type = 1;
	puts("block");
	printf("%d\n", rid);
	int n = msgrcv(rid, (void *)&msg_buf, sizeof(msg_buf.text), 1, 0);
	puts("recvd");
	int ffd;
	msg_buf.text[n] = '\0';
	printf("%s\n", msg_buf.text);
	ffd = open(msg_buf.text, O_RDONLY);
	while(n=read(ffd, msg_buf.text, sizeof(msg_buf.text))) {
		printf("%d\n", n);
		msgsnd(sid, (void *)&msg_buf, n, 0);
	}
	return 0;
}