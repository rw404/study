#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

double omp_get_wtime(void);

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
	int i, j, k, threads = omp_get_num_procs();
	if(argc < 3) {
		printf("Error exec. Not enough args "); exit(1);
	}
	i=sscanf(argv[1],"%d", &N);
	if(i<1) {
		printf("Wrong run. Try ./test N threads"); exit(2);
	}
	i=sscanf(argv[2],"%d", &threads);
	if(i<1) {
		printf("Wrong run. Try ./test N threads"); exit(2);
	}
	
	omp_set_num_threads(threads);
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

	/* elimination */

	time0 = omp_get_wtime();
	for (i=0; i<N-1; i++) {
		if (A(i, i) != 0) {
			++rank;
		} else {
			break;
		}

		#pragma omp parallel for default(none) private(k, j) shared(i, N, A) if (N > threads)
		for (k=i+1; k <= N-1; k++) {
			for (j=i+1; j <= N; j++)
				A(k,j) = A(k,j)-A(k,i)*A(i,j)/A(i,i);
		}
	}
	/* reverse substitution */
	time1 = omp_get_wtime();
	printf("Time in seconds=%gs\n", time1 - time0);
	printf("Threads num is %d\n", threads);
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
