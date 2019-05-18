#include <stdio.h>
#include <stdlib.h>


int output(FILE *fp,double time,double N_old)
{
  
  fprintf(fp,"%16.5lf %16.5lf\n",time,N_old);
  
  return EXIT_SUCCESS;
}
