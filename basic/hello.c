/*
  Display Hello, 'any strings' with command line argument.
  
  How to execute

           $ ./a.out any_strings

  For example, if type as follows,

           $ ./a.out world!
  
  get a result as below;
           $  Hello, world!

   Written by M.Yagyu
     2 April 2019

 */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

 

  printf("Hello, %s\n",argv[1]);
  
  return EXIT_SUCCESS;
}
