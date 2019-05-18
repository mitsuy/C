#include <stdio.h>
#include <stdlib.h>
#include "rk4.h"


double rk4(FILE *fp,double time,double dt, double N_old)
{
  int i;
  double max_time=100;
  int n;
  double N;
  double k1,k2,k3,k4,tmp;

  tmp=1./6.;
  
  n=(int)max_time/dt;

    for(i=0;i<n;i++)
    {

      output(fp,time,N_old);
      printf("%16.5lf %16.5lf\n",time,N_old);
      
      k1=func(time,N_old);
      k2=func(time+0.5*dt,N_old+0.5*k1);
      k3=func(time+0.5*dt,N_old+0.5*k2);
      k4=func(time+dt,N_old+k3);

      //      printf("%16.5lf %16.5lf %16.5lf %16.5lf\n",k1,k2,k3,k4);
      N=N_old+dt*(k1+2.0*k2+2.0*k3+k4)*tmp;

      // Update
      time=dt+time;
      N_old=N;
      
    }
    
}
