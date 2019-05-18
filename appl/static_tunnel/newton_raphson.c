/*
        Newton Raphson Method (NRM) for nonlinear equation.
  
     Solve velocity within tunnel as below eq.

          v_new = v_old - J^{-1} * f


    Written by M.YAGYU, 22 April, 2019


 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MX 20
#define MXB 100


double newton_raphson(int *M,double *v,double (*J_inv)[MX],double *f)
{
  int i,j;
  double temp[*M],max_err=0.,ierr=0.;


  for(i=0;i<*M;i++){
      temp[i]=v[i];

      for(j=0;j<*M;j++){
	v[i]+=-J_inv[i][j]*f[j];
      }

      //  printf("v[%d]=%lf\n",i+1,v[i]);
            
    }

    for(i=0;i<*M;i++){
      ierr=fabs(temp[i]-v[i]);

      if(ierr>max_err){
	max_err=ierr;
      }
    }

     
    return max_err;

}
