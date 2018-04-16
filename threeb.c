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
	key1 = ftok("an0ne", 32);
	key2 = ftok("an0ne", 64);
	printf("%d %d\n", key1, key2);
	sid = msgget(key1, 0666 | IPC_CREAT);
	rid = msgget(key2, 0666 | IPC_CREAT);
	printf("%d %d\n", rid, sid);
	msg_buf.type = 1;
	printf("Enter filename: ");
	scanf("%s", msg_buf.text);
	printf("%s\n", msg_buf.text);
	printf("%d\n", sid);
	printf("%d\n", msgsnd(sid, (void *)&msg_buf, strlen(msg_buf.text), 0));

	int n;
	while(msgrcv(rid, (void *)&msg_buf, sizeof(msg_buf), 1, 0)) {
		n = 
		printf("%s", msg_buf.text);
	}
	return 0;
}