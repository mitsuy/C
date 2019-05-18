#include <stdio.h>
#include <stdlib.h>
#include "func.h"


double exEuler(FILE *fp,double t,double dt,double v_old,double x_old)
{
  double v_new;      // velocity of spring
  double x_new;       // position of spring
  int i,N;
  double max_time=200.;

  N=(int)max_time/dt;
  
  for(i=0;i<N;i++)
    {
      printf("%6.2lf %6.2lf %6.2lf\n",t,x_old,v_old);
      output(fp,t,x_old,v_old);

  
      v_new=v_old+func_f(v_old,x_old)*dt;
      x_new=x_old+func_g(v_old)*dt;

      //E=0,5*m*v_old*v_old+0.5*k*x_old;
      
      // update every data
      t=t+dt;
      v_old=v_new;
      x_old=x_new;
    }

}
