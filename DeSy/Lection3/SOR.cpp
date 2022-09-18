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
  size_t size = 10;
  float A[10][10];
  
  init(A); // Инициаллизируем массив описанными данными 
  std::cout << "Init:\n";
  out(A);  // Вывод данных

  double start = omp_get_wtime(); // Запуск времени до начала алгоритма
  for (int i = 1; i <size size-1; ++i) {
    for (int j = 1; j < size-1; ++j) {
      A[i][j] = (A[i-1][j]+A[i][j-1]+A[i+1][j]+A[i][j+1])/4;
    }
  }
  double end = omp_get_wtime(); // Конец работы алгоритма

  std::cout << std::endl << "Output:\n";
  out(A);  // Вывод данных после изменений
  std::cout << "Time: " << end-start << std::endl;
  return 0;
}
