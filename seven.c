#include <stdio.h>
#define PLEN 4
#define N 100

void add(int a[], int b[], int n) {
	int i;
	for(i=0;i<n;i++) {
		a[i] = a[i] ^ b[i];
	}
}

void calc_crc(int poly[], int ip[], int op[], int len) {
	int i, j, off=0, newlen;
	newlen = len + PLEN - 1;
	for(i=0;i<len;i++) op[i]=ip[i];
	for(i=len;i<len+PLEN-1;i++) ip[i] = 0;
	while(off+PLEN<=newlen) {
		if(ip[off]==0) {
			off++;
			continue;
		}
		add(ip+off, poly, PLEN);
		off++;
	}
	for(i=len;i<len+PLEN-1;i++) op[i] = ip[i];
}

int main() {
	int ip[N] = {1, 0, 0, 1, 0, 0};
	int op[N], i;
	int poly[N] = {1, 1, 0, 1};
	calc_crc(poly, ip, op, 6);
	for(i=0;i<9;i++) printf("%d", op[i]);
	puts("");
}