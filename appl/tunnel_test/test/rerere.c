#include <stdio.h>
#include <stdlib.h>

int main(){

  FILE *fp;
  int i,j,k;

  fp=fopen("rere.dat","r");

  fscanf(fp,"%d,%d,%d",&i,&j,&k);

  printf("%d,%d,%d\n",i,j,k);

  return 0;
}
