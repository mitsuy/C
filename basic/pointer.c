/*
  How to use pointer.

  Written by M.Yagyu
  11 April, 2019

 */



#include <stdio.h>
#include <stdlib.h>

int main()
{

  int i;
  int *h;

  i=1;
  h=&i;

  *h=2;
  
  printf("i=%d\n",i);
  printf("h=%d\n",*h);

  

  
  return 0;
}
