#include <stdio.h>
#include <stdlib.h>
#include "rk4.h"


int main(int argc, char *argv[])
{

  int i,n;
  double N_old;
  double dt,time=0.;

  FILE *fp;

  if((fp=fopen("rk4.dat","w"))==NULL)
    {
    printf("Cant open file.\n");
    exit(1);
    }


  // Initialization //////////////////////////
  printf("Input time step delt_t=: ");
  scanf("%lf",&dt);

  N_old=100.;


  // Main: calcu with rk4 /////////////////
  rk4(fp,time,dt,N_old);

  fclose(fp);

  //  return EXIT_SUCCESS;
  return EXIT_SUCCESS;

}

