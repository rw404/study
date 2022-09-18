#include <iostream>
#include <omp.h>

template <size_t rows, size_t cols>
void
init(float (&A)[rows][cols])
{
  for (int i=0; i < rows; ++i) {
    for (int j=0; j < cols; ++j) {
      A[i][j] = (i*j)*(i+j);
    }
  }
}

template <size_t rows, size_t cols>
void
out(float (&A)[rows][cols])
{
  for (int i=0; i < rows; ++i) {
    for (int j=0; j < cols; ++j) {
      std::cout << A[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}


int
main()
{
  size_t size=10;
  float A[10][10];
  int iam, numt, limit;
  int isync[16];

  init(A);
  std:: cout << "Init:\n";
  out(A);

  double start = omp_get_wtime();
  #pragma omp parallel private(iam, numt, limit)
  {
    iam=omp_get_thread_num();
    numt=omp_get_num_threads();
    limit=std::min(numt-1, (int)size-3);
    isync[iam]=0;
    
    #pragma omp barrier
    for (int i=1; i<size-1; ++i) {
      if ((iam>0) && (iam <= limit)) {
        for (; isync[iam-1]==0;);
        isync[iam-1]=0;
      } 
      #pragma omp for schedule(static) nowait
      for (int j=1; j<size-1; ++j) {
        A[i][j] = (A[i-1][j] + A[i][j-1] + A[i+1][j] + A[i][j+1])/4;
      }
      if (iam < limit) {
        for (;isync[iam]==1;);
        isync[iam]=1;
      }
    }
  }
  double end = omp_get_wtime();
  std::cout << std::endl << "Output:\n";
  out(A);

  std::cout << "Time: " << end-start << std::endl;
  return 0;
}
