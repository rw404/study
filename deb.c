#include <stdio.h>
#include "threefuncs.h"
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

static int printx = 0;
static int iters = 0;
static int printiters = 0;

static float root(float (*f)(), float (*g)(), float a, float b, float eps1)
{
  if(a>b)
  {
    float helper = a;
    a = b;
    b = helper;
  }  
  if((g==(&f2) || f==(&f2)) && a<-0.5){ 
    printf("The point %f does not belong to the scope of the function definition\n", a);
    return -10;
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
    return -10;
  } 
  printf("Yes");
  float ans = a;//starting position
 
  while(((*f)(ans)-(*g)(ans))*((*f)(ans+eps1)-(*g)(ans+eps1))>0)
  {
    //ans = (float*)realloc(ans, (iters+2)*sizeof(float));
    float tmp = ans;
    ans = ans - ((*f)(ans)-(*g)(ans))/((*df)(ans)-(*dg)(ans));
    iters++;
    if(ans<tmp)
    {
      iters = 0;
      printf("The root cannot be calculated on this segment\n");
      return -10;
    }
    
  }

  return ans;
}

static float integral(float (*f)(), float a, float b, float eps2)
{
  if(eps2<=0)
  {
    printf("Epsilon does not meet the condition\n");
    return 0;
  }
  if(a>b)
  {
    float helper = a;
    a = b;
    b = helper;
  }
  if(f==(&f2) && a<-0.5)
  { 
    printf("The point %f does not belong to the scope of the function definition\n", a);
    return 0;
  }
  
  //(b-a)^3/24n^2 d2f(x) <= eps2 => n = sqrt((b-a)^3 d2f(x)/eps2 * 24)
  float (*d2f)();
  if(f==(&f1)) d2f=(&d2f1);
  else if(f==(&f2)) d2f=(&d2f2);
  else d2f=(&d2f3);

  float d2 = (*d2f)((a+b)/2);
  float y = (a+b)/2;
  float res = y;
  while(d2 == 0)
  {
    y = y / 2;
    d2 = (*d2f)(res + y);
  }
  if(d2<0) d2 = -d2;

  
  float rezult = (b-a)*(b-a)*(b-a)*d2;
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
    {"test", no_argument, NULL, 't'},
    {"absc", no_argument, NULL, 'a'},
    {"iters", no_argument, NULL, 'i'},
    {NULL, 0, NULL, 0}                                                                                    //end of structure
  };

  const char* short_options = "htai";                                                                   //option string
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
        case 'a': printx = 1;
        case 't': 
          {
              printf("You need to enter the function number, r or i\n");
              do
                {
              printf("Which function you want to test(1, 2, 3, r, i)?: ");
              scanf("%c", &TESTING_FUNCTION);
              switch (TESTING_FUNCTION){
                case 'r':
                {
                  do
                  {
                    float (*testingfunction1)(), (*testingfunction2)();
                    int num1 = 0;
                    printf("Enter the number of the first function(f): ");
                    scanf("%d\n", &num1);
                    switch(num1)
                    {
                      case 1: 
                      {
                        testingfunction1 = (&f1);
                        break;
                      }
                      case 2:
                      {
                        testingfunction1 = (&f2);
                        break;
                      }
                      case 3:
                      {
                        testingfunction1 = (&f3);
                        break;
                      }
                      default:
                      {
                        printf("Function number %d does not exist.\n");
                        testingfunction1 = NULL;
                        break;
                      }
                    }
                    int num2 = 0;
                    printf("Enter the number of the second function(g): ");
                    scanf("%d\n", num2);
                    switch(num2)
                    {
                      case 1: 
                      {
                        testingfunction2 = (&f1);
                        break;
                      }
                      case 2:
                      {
                        testingfunction2 = (&f2);
                        break;
                      }
                      case 3:
                      {
                        testingfunction2 = (&f3);
                        break;
                      }
                      default:
                      {
                        printf("Function number %d does not exist.\n");
                        testingfunction2 = NULL;
                        break;
                      }
                    }
                    float testinga, testingb;
                    printf("Enter the first border of the segment(a): ");
                    scanf("%f\n", &testinga);
                    printf("Enter the second border of the segment(b): ");
                    scanf("%f\n", &testingb);
                    float testingeps;
                    printf("Enter the epsilon: ");
                    scanf("%f\n", &testingeps);
                    if(testingfunction2 != NULL && testingfunction1 != NULL)
                    {
                      iters = 0;
                      printf("The root is %f\nThe number of iterations is %f\n", root(testingfunction1, testingfunction2, testinga, testingb, testingeps), iters);
                    }
                    char rep = 'n';
                    printf("Repeat (y/n)? ");
                    scanf("%c\n", &rep);
                    while(rep != 'n' && rep != 'y')
                    {
                      printf("Enter only y or n: ");
                      scanf("%c\n", rep);
                    }
                  } while(rep != 'n');
                  break;               
                }//ROOT TEST
                case 'i':
                {
                  do
                  {
                    float (*testingfunction)();
                    int num = 0;
                    printf("Enter the function number(f): ");
                    scanf("%d\n", &num);
                    switch(num)
                    {
                      case 1: 
                      {
                        testingfunction = (&f1);
                        break;
                      }
                      case 2:
                      {
                        testingfunction = (&f2);
                        break;
                      }
                      case 3:
                      {
                        testingfunction = (&f3);
                        break;
                      }
                      default:
                      {
                        printf("Function number %d does not exist.\n");
                        testingfunction = NULL;
                        break;
                      }
                    } 
                    float testing_integral_a, testing_integral_b;
                    printf("Enter the first border of the segment(a): ");
                    scanf("%f\n", &testing_integral_a);
                    printf("Enter the second border of the segment(b): ");
                    scanf("%f\n", &testing_integral_b);
                    float testing_integral_eps;
                    printf("Enter the epsilon: ");
                    scanf("%f\n", &testing_integral_eps);
                    if(testingfunction != NULL)
                    {
                      printf("The integral is equal to %f\n", integral(testingfunction, testing_integral_a, testing_integral_b, testing_integral_eps));
                    }
                    char repint = 'n';
                    printf("Repeat (y/n)? ");
                    scanf("%c\n", &repint);
                    while(repint != 'n' && repint != 'y')
                    {
                      printf("Enter only y or n: ");
                      scanf("%c\n", repint);
                    }
                  } while(repint != 'n');
                  break;                
                }//INTEGRAL TEST
                case '1':
                {
                  do
                  { 
                    float testing_argument1;
                    printf("Enter the function argument: ");
                    scanf("%f\n", &testing_argument1);
                    printf("The function value is equal to %f\n", f1(testing_argument1)); 
                    char repf1 = 'n';
                    printf("Repeat (y/n)? ");
                    scanf("%c\n", &repf1);
                    while(repf1 != 'n' && repf1 != 'y')
                    {
                      printf("Enter only y or n: ");
                      scanf("%c\n", repf1);
                    }
                  } while(repf1 != 'n');
                  break;                
                }//F1 TEST
                case '2':
                {
                  do
                  { 
                    float testing_argument2;
                    printf("Enter the function argument: ");
                    scanf("%f\n", &testing_argument2);
                    if(testing_argument2<-0.5)
                    {
                      printf("The point %f does not belong to the scope of the function definition\n", testing_argument2);
                    }
                    else printf("The function value is equal to %f\n", f2(testing_argument2)); 
                    char repf2 = 'n';
                    printf("Repeat (y/n)? ");
                    scanf("%c\n", &repf2);
                    while(repf2 != 'n' && repf2 != 'y')
                    {
                      printf("Enter only y or n: ");
                      scanf("%c\n", repf2);
                    }
                  } while(repf2 != 'n');
                  break;                
                }//F2 TEST
                case '3':
                {
                  do
                  { 
                    float testing_argument3;
                    printf("Enter the function argument: ");
                    scanf("%f\n", &testing_argument3);
                    printf("The function value is equal to %f\n", f3(testing_argument3)); 
                    char repf3 = 'n';
                    printf("Repeat (y/n)? ");
                    scanf("%c\n", &repf3);
                    while(repf3 != 'n' && repf3 != 'y')
                    {
                      printf("Enter only y or n: ");
                      scanf("%c\n", repf3);
                    }
                  } while(repf3 != 'n');
                  return 0;                
                }//F3 TEST
                default:
                {
                  printf("Testing of this function is not provided\n");
                  break;
                }//SMTH
              }
            char globalrep = 'n';
            printf("Test again (y/n)? ");
            scanf("%c\n", globalrep);
            while(globalrep != 'n' && globalrep != 'y')
            {
              printf("Enter only y or n: ");
              scanf("%c\n", globalrep);
            }
            } while(globalrep != 'n');
          }   
        case 'i': printiters = 1;
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
  float ans = 0;
  iters = 0;
  ans = root(&f1, &f2, b, a, eps1);
  if(printx==1) printf("Functions f1 and f2 are equal at the point %f\n", ans);
  if(printiters == 1) printf("It took %d iterations to find the root", iters);
  float a1 = ans;
  iters = 0;
  float ans2 = root(&f1, &f3, -1.0, 1.0, eps1);
  if(printx == 1)printf("Functions f1 and f3 are equal at the point %f\n", ans2);
  if(printiters == 1)printf("it took %d iterations to find the root", iters);
  //float b1 = ans2[iters];
  iters = 0;
  float res; //= (float)integral((&f3), -1.0, 1.0, eps1);
  float ans3 = root(&f2, &f3, 0, 1, eps1);
  if(printx == 1)printf("Functions f2 and f3 are equal at the point %f\n", ans3);
  if(printiters == 1) printf("it took %d iterations to find the root", iters);
  
  res = integral((&f1), ans, ans2, eps1);
  //res = res - integral(&f2, ans, ans3, eps1);
  //res = res - integral(&f3, ans2, ans3, eps1);

  printf("%f\n%f\n%f\n%f\n%f\n%f\n\n%f\n%f\n%f\n%f\n",f1(a), f2(a), f3(a), df1(a), df2(a), df3(a), a1, res, ans2, ans3);
  return 0;
}
