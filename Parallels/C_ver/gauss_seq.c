#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

void prt1a(char *t1, float *v, int n,char *t2);
void wtime(double *t) {
	static int sec = -1;
	struct timeval tv;
	gettimeofday(&tv, (void *)0);
	if (sec < 0) sec = tv.tv_sec;
	*t = (tv.tv_sec - sec) + 1.0e-6*tv.tv_usec;
}

int N;
float *A;
#define A(i,j) A[(i)*(N+1)+(j)]
int rank;

int main(int argc,char **argv) {
	double time0, time1;
	FILE *in;
	int i, j, k;
	
	i=sscanf(argv[1],"%d", &N);
	if(i<1) {
		printf("Wrong exec file, run ./test N"); exit(2);
	}
	/* create arrays */
	A=(float *)malloc(N*(N+1)*sizeof(float));
	rank = 0;
	printf("GAUSS %dx%d\n----------------------------------\n",N,N);
	/* initialize array A*/
	for(i=0; i <= N-1; i++)
		for(j=0; j <= N; j++)
			if (i==j || j==N)
				A(i,j) = 1.f;
			else 
				A(i,j)=0.f;
	
	wtime(&time0);
	/* elimination */
	for (i=0; i<N-1; i++) {
		if (A(i, i) != 0) {
			++rank;
		}
		
		for (k=i+1; k <= N-1; k++)
			for (j=i+1; j <= N; j++)
				A(k,j) = A(k,j)-A(k,i)*A(i,j)/A(i,i);
	}
	wtime(&time1);
	/* reverse substitution */	
	printf("Time in seconds=%gs\n", time1-time0);
	printf("Rank is %d\n", rank);
	free(A);
	return 0;
}

void prt1a(char * t1, float *v, int n,char *t2) {
	int j;
	printf("%s",t1);
	for(j=0;j<n;j++)
		printf("%.4g%s",v[j], j%10==9? "\n": ", ");
	printf("%s",t2);
}
