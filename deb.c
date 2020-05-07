#include <stdio.h>
#include "threefuncs.h"
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

static int printx = 0;
static int iters = 0;



static float* root(float (*f)(), float (*g)(), float a, float b, float eps1)
{
  if(a>b)
  {
    float helper = a;
    a = b;
    b = helper;
  }  
  if((g==(&f2) || f==(&f2)) && a<0.5){ 
    printf("The point %f does not belong to the scope of the function definition\n", a);
    return NULL;
  }
  float (*df)(),(*dg)();
  if(f==(&f1)) df=(&df1);
  else if(f==(&f2)) df=(&df2);
  else df=(&df3);
  
  if(g==(&f1)) dg=(&df1);
  else if(g==(&f2)) dg=(&df2);
  else dg=(&df3);
 
  if((((*df)(a)-(*dg)(a))*((*df)(b)-(*dg)(b)))<=0 || (((*f)(a)-(*g)(a))*((*f)(b)-(*g)(b)))>0)
  {
    printf("The root cannot be calculated on this segment\n");
    return NULL;
  } 
  printf("Yes");
  float *ans = (float*)calloc(1,sizeof(float));

  ans[0] = a;//starting position
 
  while(((*f)(ans[iters])-(*g)(ans[iters]))*((*f)(ans[iters]+eps1)-(*g)(ans[iters]+eps1))>0)
  {
    ans = (float*)realloc(ans, (iters+2)*sizeof(float));
    
    ans[iters+1] = ans[iters] - ((*f)(ans[iters])-(*g)(ans[iters]))/((*df)(ans[iters])-(*dg)(ans[iters]));
    iters++;
    if(ans[iters]<ans[iters-1])
    {
      iters = 0;
      free(ans);
      printf("The root cannot be calculated on this segment\n");
      return NULL;
    }
    
  }

  return ans;
}

static float integral(float (*f)(), float a, float b, float eps2)
{
  if(a>b)
  {
    float helper = a;
    a = b;
    b = helper;
  }
  if(f==(&f2) && a<0.5)
  { 
    printf("The point %f does not belong to the scope of the function definition\n", a);
    return 0;
  }
  
  //(b-a)^3/24n^2 d2f(x) <= eps2 => n = sqrt((b-a)^3 d2f(x)/eps2 * 24)
  float (*d2f)();
  if(f==(&f1)) d2f=(&d2f1);
  else if(f==(&f2)) d2f=(&d2f2);
  else d2f=(&d2f3);

  float rezult = (b-a)*(b-a)*(b-a)*(*d2f)((a+b)/2);
  rezult = rezult/24;
  rezult = rezult /eps2;
  int n = (int)f2(rezult-0.5) + 1;
  printf("\n%d\n\n", n);
  float ans = 0;
  float tmp = (b-a)/n;
  tmp = tmp/2;
  for(int i = 1; i < 2*n; i+=2)
  {
    ans += (*f)(a+tmp*i);
    //printf("%f\n\n%f\n\n", (*f)(a+tmp*i), ans); 
  }
  printf("\n");
  ans = ans*tmp*2;
  return ans;
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









  float a = 3.0;
  float b = 1.8;
  //printf("%f\n%f\n", root(&f1, &f3,b, a, eps1), root(&f2, &f1, b, a, eps1));
  float* ans = NULL;
  ans = root(&f1, &f2, b, a, eps1);
  float a1 = ans[iters];
  //iters = 0;
  //float *ans2 = root(&f1, &f3, -1.0, 1.0, eps1);
  //float b1 = ans2[iters];
  float res = (float)integral((&f3), -1.0, 1.0, eps1);

  printf("%f\n%f\n%f\n%f\n%f\n%f\n\n%f\n%f\n",f1(a), f2(a), f3(a), df1(a), df2(a), df3(a), a1, res);
  return 0;
}
