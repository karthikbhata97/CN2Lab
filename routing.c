#include <stdio.h>

#define INF 99
#define N 100
int dup[N][N], mat[N][N], v[N], p[N][N];

void dijkstra(int s, int n) {
	int i, j, min, node;
	for(i=0;i<n;i++) v[i]=0;
	v[s] = 1;
	for(i=0;i<n;i++) {
		min = INF;
		for(j=0;j<n;j++) {
			if(!v[j] && min>mat[s][j])
				min = mat[s][j], node=j;
		}
		v[node] = 1;
		for(j=0;j<n;j++) {
			if(mat[s][j]>mat[s][node]+mat[node][j])
				mat[s][j]=mat[s][node]+mat[node][j], p[s][j]=node;
		}
	}
}

int main(void) {
	int n, i, j, x, y;
	scanf("%d", &n);
	for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%d", &mat[i][j]);
	
	for(i=0;i<n;i++) {
		dijkstra(i, n);
	}
	for(i=0;i<n;i++) {
		printf("Source %d\n", i);
		printf("Destination NextHop Distance\n");
		for(j=0;j<n;j++) {
			if(j==i) continue;
			printf("%d\t%d\t%d\n", j, (p[j][i]==i?j:p[i][j]), mat[i][j]);
		}
		puts("");
	}
	return 0;
}