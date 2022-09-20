#include <stdio.h>
#define MAX_EL 1024

char input[MAX_EL];

int main()
{
  int cur, count = 0;
  while ((cur=getchar()) != EOF) {
    if (count == MAX_EL) {
      fprintf(stderr, "tm");
      return 1;
    } else {
      input[count++] = cur;
    }
  }
  for (int i=count-1; i>=0; --i) {
    putchar(input[i]);
  }
  
  return 0;
}
