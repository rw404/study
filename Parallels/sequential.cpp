#include <iostream>
#include <vector>
#include <omp.h>

int
main() {
    int n = 0;
    std::cin >> n;

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
    double start = omp_get_wtime();
    for (int i = 0; i < n; ++i) {
        double tmp = matrix[i][i];
        if (tmp != 0) {
            ++rk;
        }

        for (int j = n-1; j >= i; --j) {
            matrix[i][j] /= tmp;
        }

        for (int j = i+1; j < n; ++j) {
            double row_tmp = matrix[j][i];
            for (int k = n-1; k >= i; --k) {
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

    std::cout << "Answer: " << rk << std::endl;
    std::cout << "Time: " << end-start << std::endl;

    return 0;
}
