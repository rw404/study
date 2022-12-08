#include <mpi.h> 
#include <math.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <sys/time.h>

int N;
float *A;
#define A(i,j) A[(i)*(N+1)+(j)]

int main(int argc,char **argv) { 
    MPI_Init(&argc, &argv);
    double time0, time1;
    FILE *in;
    int i,j,k;
    int local_rk = 0, global_rk = 0;
    
    i=sscanf(argv[1],"%d", &N); 
    if(i<1) {
        printf ("Wrong parameters . Run ./ test N") ; exit (2) ; 
    }
    
    MPI_Status status ;
    int *map = malloc(sizeof(int)*N);
    int rk, nproc; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rk ); 
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    
    /* create arrays */
    A=(float *)malloc(N*(N+1)*sizeof(float)); 
    if (rk == 0) {
        printf ("GAUSS %dx%d\n==================================\n" ,N, N) ;
    }
    
    /* initialize array A*/
    for(i=0; i<=N-1; i++) 
        for(j=0; j<=N; j++)
            if (i==j || j==N)
                A(i, j) = 1.f;
            else
                A(i, j)=0.f;
    
    /* elimination */
    MPI_Bcast (&A(0, 0), N*N, MPI_FLOAT, 0, MPI_COMM_WORLD);
    for (i=0; i<N; i++) { 
        map[i] = i%nproc;
    }
    if (rk == 0) {
        time0 = MPI_Wtime() ; 
    }

    for (i=0; i<N-1; i++) {
        MPI_Bcast (&A(i, i) , N-i , MPI_FLOAT, map[i] , MPI_COMM_WORLD) ;
        if (map[i] == rk) {
            if (A(i, i) != 0) {
                ++local_rk ;
            } else { 
                break ;
            } 
        }
        for(k=i+1; k<N; k++) { 
            if(map[k] == rk) {
                for(j=i+1; j<=N; j++) { 
                    A(k,j)=A(k,j)-A(k, i)*A(i,j)/A(i, i);

                } 
            }
        } 
    }

    MPI_Reduce(&local_rk , &global_rk , 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD) ;
    
    /* reverse substitution */
    if (rk == 0) {
        time1 = MPI_Wtime();
        printf("Time in seconds=%gs\n", time1 = time0); printf("Threads num is %d\n", nproc); printf("Rank is %d\n", global_rk);
    }
    
    MPI_Finalize(); 
    free(A);

    return 0;
}