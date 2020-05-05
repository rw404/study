#include <stdio.h>
#include "threefuncs.h"
#include <getopt.h>

float root(float (*f)(), float (*g)(), float a, float b, float eps1){
  if((g==(&f2) || f == (&f2))&& a<0.5){ 
    printf("The point does not belong to the scope of the function definition\n");
    return (float)-1;
  }
  float r = 0.0;
  return r;
}

int main(int argc, char *argv[])
{ 
  const float eps1 = 0.001;
  static char TESTING_FUNCTION=-1;                                                                        //number of testing function
  
  const struct option long_options[]={                                                                    //structure for getopt_long
    {"help", no_argument, NULL, 'h'},                                                                     //name, number of args, &flag, val
    {"test", optional_argument, NULL, 't'},
    {"absc", no_argument, NULL, 'a'},
    {"iters", no_argument, NULL, 'i'},
    {NULL, 0, NULL, 0}                                                                                    //end of structure
  };

  const char* short_options = "ht::ai";                                                                   //option string
  int r = 0;       
  int option_index=-1;
  while((r=getopt_long(argc, argv, short_options, long_options, &option_index))!=-1)
  {
    switch(r)
      {
        case 'h': {
          if(option_index==-1) 
            printf("Please enter --help to get more information\n");
          else  
            printf("Commands:\n\t\
            --test=(NUMBER_OF_NEEDED_FUNCTION or r for root or i for integrlal) to enter testing mode\n\t\
            --absc to allow abscissa's printing\n\t\
            --iters to print number of iterations to solve root\n\t");
                                           
            return 0;
        }
        case 't': {
            if(optarg==NULL) {
              printf("You need to enter the function number, r or i\n");
              printf("Which function want to test(1, 2, 3, r, i)?: ");
              scanf("%c", &TESTING_FUNCTION);
              switch (TESTING_FUNCTION){
                case 'r':;//ROOT TEST
                case 'i':;//INTEGRAL TEST
                case '1':;//F1 TEST
                case '2':;//F2 TEST
                case '3':;//F3 TEST
                default:break;//SMTH
              }
            }
            return 0;
        }
        case '?': {
          printf("This option is not provided. Please enter --help to get information about available options.\n");
          return 0;
        }
      
     }
     option_index=-1;
  }
  float a = 1.0;
  float b = -1.0;
  printf("%f\n%f\n", root(&f1, &f3,b, a, eps1), root(&f2, &f1, b, a, eps1));
  
  printf("%f\n%f\n%f\n%f\n%f\n%f\n",f1(a), f2(a), f3(a), df1(a), df2(a), df3(a));
  return 0;
}
