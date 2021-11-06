#include <iostream>
#include <vector>
#include <omp.h>

int
main() {
    int n = 0;
    std::cin >> n;

    omp_set_num_threads(omp_get_num_procs()); 
    
    std::vector<std::vector<double> > matrix(n);
    for (int i = 0; i < n; ++i) {
        matrix[i] = std::vector<double>(n);
    }
    
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int rk = 0;

    int i = 0, j = 0, k = 0;
    double start_time = omp_get_wtime();        

    for (i = 0; i < n; ++i) {
        double tmp = matrix[i][i];
        if (tmp != 0) {
            rk = i;
        }

        #pragma omp parallel for private(j) if(n>=99)
        for (j = n-1; j >= i; --j) {
            matrix[i][j] /= tmp;
        }

        #pragma omp parallel for private(j, k) shared(i) if(n>=99)
        for (j = i+1; j < n; ++j) { 
            double row_tmp = matrix[j][i];
            for (k = n-1; k >= i; --k) {
                matrix[j][k] -= row_tmp*matrix[i][k];
            }
        }
    }
    double end = omp_get_wtime();
 
/*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
*/    

    std::cout << "Answer: " << rk+1 << std::endl;
    std::cout << "Time: " << end-start_time << std::endl;

    return 0;
}
