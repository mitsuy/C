#include <stdio.h>
#include <stdlib.h>

int output(FILE *fp,double t,double x_old,double v_old)
{
  fprintf(fp,"%6.2lf %6.2lf %6.2lf\n",t,x_old,v_old);
  
  return EXIT_SUCCESS;
}
