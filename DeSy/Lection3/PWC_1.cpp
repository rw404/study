#include <iostream>


int
main()
{
  float A[5][5];
  struct event s[5][5]; //События

  for (i=0; i<5; ++i) {
    for (j=0; j<5; ++j) {
      clear(s[i][j]);
    }
  }
  for (j=0; j<5; ++j) {
    post(s[0][j]);
  }

  parfor(i=1; i< 5-1; ++i) {// Ветки цикла могут выполняться разными нитями
    parfor(j = 1; j< 5-1; ++j) {
      wait(s[i-1][j]);
      wait(s[i][j-1]);
      A[i][j] = (A[i-1][j]+A[i][j-1]+A[i+1][j]+A[i][j+1])/4;
      post(s[i][j]);
    } 
  }

  return 0;
}
