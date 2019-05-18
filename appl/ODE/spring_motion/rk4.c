#include <stdio.h>
#include <stdlib.h>
#include "func.h"


double rk4(FILE *fp2,double t,double dt,double v_old,double x_old)
{

  double v_new;      // velocity of spring
  double x_new;       // position of spring
  double k1,k2,k3,k4;
  double h1,h2,h3,h4;
  int i,N;
  double max_time=200.;

  N=(int)max_time/dt;

  for(i=0;i<N;i++)
    {
      printf("%6.2lf %6.2lf %6.2lf\n",t,x_old,v_old);
      output(fp2,t,x_old,v_old);
      
      k1=func_f(v_old,x_old);
      k2=func_f(v_old+0.5*dt*k1,x_old+0.5*dt*k1);
      k3=func_f(v_old+0.5*dt*k2,x_old+0.5*dt*k2);
      k4=func_f(v_old+dt*k3,x_old+dt*k3);

      h1=func_g(v_old);
      h2=func_g(v_old+0.5*dt*h1);
      h3=func_g(v_old+0.5*dt*h2);
      h4=func_g(v_old+dt*h3);
    
      v_new=v_old+dt*(k1+2*k2+2*k3+k4)/6;
      x_new=x_old+dt*(h1+2*h2+2*h3+h4)/6;
    
      //      E=0,5*m*v_old*v_old+0.5*k*x_old;
      // update every data
      t=t+dt;
      v_old=v_new;
      x_old=x_new;
    }
}
