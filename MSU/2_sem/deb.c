#include <stdio.h>
#include "threefuncs.h"
#include <getopt.h>
#include <stdlib.h>
#include <math.h>


static int printx = 0;                                                                                            //Flag to print roots 
static int iters = 0;                                                                                             //Iterations
static int printiters = 0;                                                                                        //Flag to print iterations


static float root(float (*f)(), float (*g)(), float a, float b, float eps1)                                       //Function for calculating the root
{
  iters = 0;                                                                                                      //Iters initiallization
  float (*df)(),(*dg)();                                                                                          //Two pointers to functions
  float ans;                                                                                                      //The initial value of x
  float tmp;                                                                                                      //Temporary variable-helper

  if(eps1<=0)                                                                                                     //Сhecking that eps1 is positive
  {
    printf("Epsilon does not meet the condition\n");
    return -10;
  }
  if(a>b)                                                                                                         //If the values of the segment ends are mixed up
  {
    a = b;
    b = ans;
  }
  ans = a;                                                                                                        //Updating the ans value
  tmp = ans;  

  if((g==(&f2) || f==(&f2)) && a<-0.5){                                                                           //Сhecking the definition scope
    printf("The point %f does not belong to the scope of the function definition\n", a);
    return -10;                                                                                                   //The root does not belong to the definition area,
                                                                                                                  //so this is an invalid solution flag
  }
  
  if(f==(&f1)) df=(&df1);                                                                                         //The derivative of which function is considered
  else if(f==(&f2)) df=(&df2);
  else df=(&df3);
    
  if(g==(&f1)) dg=(&df1);
  else if(g==(&f2)) dg=(&df2);
  else dg=(&df3);
 
  if((((*df)(a)-(*dg)(a))*((*df)(b)-(*dg)(b)))<=0 || (((*f)(a)-(*g)(a))*((*f)(b)-(*g)(b)))>0)                     //If the function has the same signs at the ends 
  {                                                                                                               //of the segment, or different signs of derivatives
    printf("The root cannot be calculated on this segment and\n");                                                //then the root cannot be found
    return -10;
  }
  
  while(((*f)(ans)-(*g)(ans))*((*f)(ans+eps1)-(*g)(ans+eps1))>0)                                                  //As long as the variable + eps1   
  {                                                                                                               //has the same sign as the variable itselfi,
    ans = ans - ((*f)(ans)-(*g)(ans))/((*df)(ans)-(*dg)(ans));                                                    //the root is not found

    iters++;                                                                                                      //Each time iters grows 
    if(ans<tmp)                                                                                                   //If the derivative has changed its sign, stop working
    {
      iters = 0;
      printf("The root cannot be calculated on this segment\n");
      return -10;
    }
  }
  return ans;
}


static float integral(float (*f)(), float a, float b, float eps2)                                                 //Function for integral calculating
{
  float (*d2f)();                                                                                                 //Pointer to the second derivative
  float d2;                                                                                                       //Value of the second derivative at the point
  float y;                                                                                                        //Variable-helper for the secon derivative calculating 
  float helper = a;                                                                                               //Variable-helper to change a and b
  float rezult;                                                                                                   //Variable for calculating the number of segments
  int n;                                                                                                          //The number of segments
  float ans;                                                                                                      //Answer
  float tmp;                                                                                                      //Half-multiplier in the sum of functions = (b-a)/2n
  int i;                                                                                                          //Loop variable

  if(eps2<=0)                                                                                                     //Checking that eps2 is positive
  {
    printf("Epsilon does not meet the condition\n");
    return -10;
  }

  if(a>b)                                                                                                         //If the values of the segment ends are mixed up 
  {
    a = b;
    b = helper;
  }

  if(f==(&f2) && a<-0.5)                                                                                          //Checking the definition scope
  { 
    printf("The point %f does not belong to the scope of the function definition\n", a);
    return -10;
  }
  
  if(f==(&f1)) d2f=(&d2f1);                                                                                       //The second derivative of which function is considered
  else if(f==(&f2)) d2f=(&d2f2);
  else d2f=(&d2f3);

  d2 = (*d2f)((a+b)/2);                                                                                           //Value of the second derivative at the point (a+b)/2
  y = (a+b)/2;                                                                                                    //Point (a+b)/2
  
  while(d2 == 0)                                                                                                  //Loop to find the second derivative   
  {                                                                                                               //which is not equal to zero
    y += y / 2;
    d2 = (*d2f)(y);
  }

  if(d2<0) d2 = -d2;                                                                                              //Absolute value of the second derivative
  
  rezult = (b-a)*(b-a)*(b-a)*d2;                                                                                  //The value obtained from the equality   
  rezult = rezult/24;                                                                                             //of the residual term in the integral sum and eps2
  rezult = rezult /eps2;                                                                                          //n = sqrt((b-a)^3 * d2/24*eps2)
                                                                                                                  //(b-a)^3 * d2/24n^2 = eps2
  n = (int)f2(rezult-0.5) + 1;                                                                                    //Number of the segments is equal to sqrt of rezult
  
  ans = 0;                                                                                                        //Answer initiallization
  tmp = (b-a)/n;
  tmp = tmp/2;                                                                                                    //Temporary variable initiallization

  for(i = 1; i < 2*n; i+=2)                                                                                       //The method of rectangles
  {
    ans += (*f)(a+tmp*i); 
  }

  ans = ans*tmp*2;                                                                                                //Answer is equal to ((b-a)/n)*Sum f(i)

  return ans;
}


int main(int argc, char *argv[])
{ 
  const float eps = 0.001;                                                                                        //Epsilon
  static char TESTING_FUNCTION=-1;                                                                                //number or the first letter of testing function
                                                                                                                    
  float (*testingfunction1)(), (*testingfunction2)();                                                             //Functions for testing mode
  int num1 = 0;                                                                                                   //Number of the testing function
  int num2 = 0;                                                                                                   //Number of the (second root) testing function
  float testinga, testingb;                                                                                       //Segment boundaries for testing the function
  float testingeps;                                                                                               //Epsilon for testing thefunction
  char repeat = 'n';                                                                                              //Reply if you want to test  again
  float testing_argument;                                                                                         //Argument of the testing function(1, 2, 3)
  float testing_result;                                                                                           //Testing result
  int flag = 0;                                                                                                   //Flag to determine that loop has already been completed

  float res;                                                                                                      //Result of programm
  float ans1;                                                                                                     //root of f1 = f2
  float ans2;                                                                                                     //root of f1 = f3
  float ans3;                                                                                                     //root of f2 = f3
 
  const struct option long_options[]={                                                                            //Structure for getopt_long
    {"help", no_argument, NULL, 'h'},                                                                             //name, number of args, &flag, val
    {"test", no_argument, NULL, 't'},
    {"absc", no_argument, NULL, 'a'},
    {"iters", no_argument, NULL, 'i'},
    {NULL, 0, NULL, 0}                                                                                            //end of structure
  };

  const char* short_options = "htai";                                                                             //Optional string: help, test, abscissa, iterations
  int r = 0;                                                                                                      //Variable for getting the option value
  int option_index=-1;                                                                                            //Variable for defining the option type: short/long

  while((r=getopt_long(argc, argv, short_options, long_options, &option_index))!=-1)                              //Loop for executing options
  {
    switch(r)
    {
        case 'h': {                                                                                               //--help or -h
          if(option_index==-1)                                                                                    //Please enter a long option
            printf("Please enter --help to get more information\n");
          else                                                                                                    //Describing the options
            printf("Commands:\n\t--test to enter testing mode\n\t--absc to allow abscissa's printing\n\t--iters to print number of iterations to calculate the root\n");
                                           
          return 0;                                                                                               //After --help/-h programm stops
        }
        case 'a': 
        {
          if(option_index != -1)
            printx = 1;                                                                                           //Allowing to print roots
          break;
        }
        case 't':                                                                                                 //Testing mode
        {
          printf("You need to enter the function number, r or i\n");                                              //Please enter the number or the first letter of function
              
          do                                                                                                      //Testing until the user writes 'n' after test
          {   
            printf("Which function you want to test(1, 2, 3, r, i)?: ");
            scanf("%c", &TESTING_FUNCTION);                                                                       //Testing function
            
            if(flag == 1) scanf("%c", &TESTING_FUNCTION);                                                         //TESTING_FUNCTION != \n

              switch (TESTING_FUNCTION)
              {
                case 'r':                                                                                         //Root function
                {
                  do                                                                                              //Repeat, while answer to repeat is 'y'
                  { 
                    printf("Enter the number of the first function(f): ");
                    scanf("%d", &num1);

                    switch(num1)                                                                                  //Defining the function to test
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
                        printf("Function number %d does not exist.\n", num1);                                     //If number is invalid, testing mode returns the error
                        testingfunction1 = NULL;
                        break;
                      }
                    }

                    printf("Enter the number of the second function(g): ");
                    scanf("%d", &num2);
                    
                    switch(num2)                                                                                  //Defying the function to test
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
                        printf("Function number %d does not exist.\n", num2);                                     //If number is invalid, testing mode returns the error
                        testingfunction2 = NULL;
                        break;
                      }
                    }
 
                    printf("Enter the first border of the segment(a): ");                                         //Segment boundaries
                    scanf("%f", &testinga);
                    
                    printf("Enter the second border of the segment(b): ");
                    scanf("%f", &testingb);
                    
                    printf("Enter the epsilon: ");                                                                //Epsilon
                    scanf("%f", &testingeps);
                    
                    if(testingfunction2 != NULL && testingfunction1 != NULL)                                      //If there is no errors, calculate the root
                    {
                      testing_result = root(testingfunction1, testingfunction2, testinga, testingb, testingeps);   

                      if(testing_result != -10)                                                                   //Сhecking for errors
                        printf("The root is %f\nThe number of iterations is %d\n", testing_result, iters);
                    }

                    printf("Repeat (y/n)? ");
                    scanf("%c", &repeat);
                    scanf("%c", &repeat);
        
                    while(repeat != 'n' && repeat != 'y')                                                         //While Reply is not 'n' or 'y', asks to  enter y/n
                    {
                      while(repeat!='\n') scanf("%c", &repeat); 
                      printf("Enter only y or n: ");
                      scanf("%c", &repeat);
                    }

                  } while(repeat != 'n');
                  break;               
                }
                case 'i':                                                                                         //Integral test
                {
                  do                                                                                              //Repeat while answer to repeat is 'y'
                  {
                    printf("Enter the function number(f): ");
                    scanf("%d", &num1);
                    
                    switch(num1)                                                                                   //Defying the function to test
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
                        printf("Function number %d does not exist.\n", num1);                                     //If number is invalid, testing mode returns the error
                        testingfunction1 = NULL;
                        break;
                      }
                    }

                    printf("Enter the first border of the segment(a): ");                                         //Segment boundaries
                    scanf("%f", &testinga);
                    
                    printf("Enter the second border of the segment(b): ");
                    scanf("%f", &testingb);
                                        
                    printf("Enter the epsilon: ");                                                                //Epsilon
                    scanf("%f", &testingeps);

                    if(testingfunction1 != NULL)
                    {
                      testing_result = integral(testingfunction1, testinga, testingb, testingeps);

                      if(testing_result != -10)                                                                    //Checking for errors
                        printf("The integral is equal to %f\n", testing_result);
                    }
                   
                    printf("Repeat (y/n)? ");
                    scanf("%c", &repeat);
                    scanf("%c", &repeat);

                    while(repeat != 'n' && repeat != 'y')                                                         //While Reply is not 'n' or 'y', asks to  enter y/n
                    {
                      while(repeat!='\n') scanf("%c", &repeat); 
                      printf("Enter only y or n: ");
                      scanf("%c", &repeat);

                    }
                  
                  } while(repeat != 'n');
                  break;                
                }
                case '1':                                                                                         //Testing the first function
                {
                  do                                                                                              //Repeat while answer to repeat is 'y'
                  { 
                    printf("Enter the function argument: ");
                    scanf("%f", &testing_argument);
                    
                    printf("The function value is equal to %f\n", f1(testing_argument)); 
                    
                    printf("Repeat (y/n)? ");
                    scanf("%c", &repeat);
                    scanf("%c", &repeat);

                    while(repeat != 'n' && repeat != 'y')                                                         //While Reply is not 'n' or 'y', asks to  enter y/n
                    {
                      while(repeat!='\n') scanf("%c", &repeat);
                      printf("Enter only y or n: ");
                      scanf("%c", &repeat);
                    }
                  
                  } while(repeat != 'n');
                  break;                
                }
                case '2':                                                                                         //Testing the second function
                {
                  do                                                                                              //Repeat while answer to repeat is 'y'
                  { 
                    printf("Enter the function argument: ");
                    scanf("%f", &testing_argument);
                    
                    if(testing_argument<-0.5)                                                                     //Checking that the argument is                     
                    {                                                                                             //in the scope of the function definition
                      printf("The point %f does not belong to the scope of the function definition\n", testing_argument);
                    }                                                                                           
                    else printf("The function value is equal to %f\n", f2(testing_argument));
                                       
                    printf("Repeat (y/n)? ");
                    scanf("%c", &repeat);
                    scanf("%c", &repeat);

                    while(repeat != 'n' && repeat != 'y')                                                         //While Reply is not 'n' or 'y', asks to  enter y/n
                    {
                      while(repeat!='\n') scanf("%c", &repeat);
                      printf("Enter only y or n: ");
                      scanf("%c", &repeat);
                    }
                  
                  } while(repeat != 'n');
                  break;                
                }
                case '3':                                                                                         //Testing the third function
                {
                  do                                                                                              //Repeat while answer to repeat is 'y'
                  {
                    printf("Enter the function argument: ");
                    scanf("%f", &testing_argument);
                    
                    printf("The function value is equal to %f\n", f3(testing_argument)); 
                                       
                    printf("Repeat (y/n)? ");
                    scanf("%c", &repeat);
                    scanf("%c", &repeat);

                    while(repeat != 'n' && repeat != 'y')                                                         //While Reply is not 'n' or 'y', asks to  enter y/n
                    {
                      while(repeat!='\n') scanf("%c", &repeat);
                      printf("Enter only y or n: ");
                      scanf("%c", &repeat);
                    }
                  
                  } while(repeat != 'n');
                  break;                
                }
                default:                                                                                          //If number of the first letter of the testing function
                {                                                                                                 //is invalid, returns error
                  printf("Testing of this function is not provided\n");
                  break;
                }
              }          
            printf("Test another function (y/n)? ");
            scanf("%c", &repeat);
            scanf("%c", &repeat);

            while(repeat != 'n' && repeat != 'y')                                                                 //While Reply is not 'n' or 'y', asks to  enter y/n
            {
              while(repeat!='\n') scanf("%c", &repeat);
              printf("Enter only y or n: ");
              scanf("%c", &repeat);
            }
            flag = 1;
          } while(repeat != 'n');
        }   
        case 'i': 
        {
          if(flag == 0 && option_index!=-1)
            printiters = 1;                                                                                       //Allowing to print the number of iterations
          break;
        }
        case '?':                                                                                                 //If option is not available, returns error and stops
        {
          printf("This option is not provided. Please enter --help to get information about available options.\n");
          return 0;
        }
      
    }
    option_index=-1;                                                                                              //Updating a variable to correctly   
  }                                                                                                               //determine the option type
                                                                                                   
  ans1 = root(&f1, &f2, 1.8, 3.0, eps);                                                                           //f1 = f2 at ans1
  
  if(ans1 == -10) return 0;                                                                                       //Checking for errors

  if(printx==1) printf("Functions 3/((x-1)^2 + 1) and sqrt(x + 0.5) (f1 and f2  are equal at the point %f\n", ans1);//Options
  
  if(printiters == 1) printf("It took %d iterations to find the root of 3/((x-1)^2 + 1) = sqrt(x+0.5)\n", iters);
  

  ans2 = root(&f1, &f3, -1.0, 1.0, eps);                                                                          //f1 = f3 at ans2
  
  if(printx == 1)printf("Functions 3/((x-1)^2 + 1) and e^(-x) (f1 and f3) are equal at the point %f\n", ans2);    //Options
  
  if(printiters == 1)printf("it took %d iterations to find the root 3/((x-1)^2 + 1) = e^-x\n", iters);
  

  ans3 = root(&f2, &f3, 0.0, 1.0, eps);                                                                           //f2 = f3 at ans3
  
  if(ans3 == -10) return 0;
  
  if(printx == 1)printf("Functions sqrt(x + 0.5) and e^(-x) (f2 and f3) are equal at the point %f\n", ans3);
  
  if(printiters == 1) printf("it took %d iterations to find the root sqrt(x+0.5) = e^-x\n", iters);
  
  res = integral(&f1, ans1, ans2, eps);                                                                           //integral of f1 from ans1 to ans2
  res = res - integral(&f2, ans1, ans3, eps);                                                                     //minus integral of f2 from  ans1 to asn3
  res = res - integral(&f3, ans2, ans3, eps);                                                                     //minus integral of f3 from ans2 to ans3

  printf("%f\n", res);

  return 0;
}
