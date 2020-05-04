#include <stdio.h>
#include "threefuncs.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
        const struct option long_options[]={
          {"help", no_argument, NULL, 'h'}
        };
        const char* short_options="hs::f::";
        int r =0;
        int option_index=-1;
        while((r=getopt_long(argc, argv, short_options, long_options, &option_index))!=-1)
        {
                switch(r)
                {
                        case 'h': {
                                          printf("here is help\n");
                                          break;
                                  }
                        case '?': printf("nope\n");
                }
                option_index=-1;
        }

        float a = 1.0;
        printf("%f\n%f\n%f\n%f\n%f\n%f\n",f1(a), f2(a), f3(a), df1(a), df2(a), df3(a));
        return 0;
}
