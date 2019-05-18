#include <stdio.h>
#include <stdlib.h>

double func_f(double v_old,double x_old){

  double f;
  double m,k,c,mu,omega;  // mass, elastic coefficient, ??, mu=c/m and omega=k/m:frequency, respectively.p
  
  m=1.;      // mass of spring
  c=10.;      // what is this parameter??
  k=1.;      // elestic coefficient

  mu=c/m,omega=k/m;
  
  f=-mu*v_old-omega*x_old;

  return f;

}

double func_g(double v_old){
  double g;

  g=v_old;

  return g;
}
