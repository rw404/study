#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *pInp = NULL;

#define MAX_EL 1024

char input[MAX_EL];

int main()
{
  size_t cur, count = 0;
  pInp = (char*)calloc(1, sizeof(char));

  while (fgets(input, sizeof input, stdin)) {
    int oldCount = count;
    cur = strlen(input);
    count += cur;
    pInp = (char*)realloc(pInp, count+1);
    if (!pInp) { 
      fprintf(stderr, "tm");
      return 1;
    } else {
      for (int i=0; i<cur; ++i) { 
        pInp[count-cur+i] = input[i];
      }
    }
  }
  for (int i=count-1; i>=0; --i) {
    putchar(pInp[i]);
  }

  free(pInp);
  
  return 0;
}
