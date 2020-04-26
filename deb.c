#include <stdio.h>

extern float f1();

int main(void)
{
        float a = 1.0;
        printf("%f", f1(a));
        return 0;
}
