#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MX 20
#define MXB 100


double function(int *N,int *M,double (*As)[MX],double (*Bs)[MX],double *v,\
		double *Qe,double *f,double *pT,double *pr,double *pj,double *p,\
		double rho,double *Ar,double *Am,double *mm,double *vt,\
		double *zeta_out,double *zeta_in,double lambda,double *Lr,\
		double *Dr,double *vj,double *Kj,double *nj,double *Aj)
{
  int i,j;

  for(i=0;i<*N;i++){
    f[i]=0.;
    for(j=0;j<*M;j++){
      //      f[i]+=As[i][j]*Ar[j]*v[j]-Qe[j+1];
      f[i]+=As[i][j]*Ar[j]*v[j];
      //     printf("%lf ",As[i][j]);
    }
    f[i]+=Qe[i+1];
    //printf("\n");
    //printf("f[%d]=%lf\n",i,f[i]);
  }
  
  for(i=*N;i<*M;i++){
    f[i]=0.;
    for(j=0;j<*M;j++){
      //      pT[j]=-rho*1/Ar[j]*(0.78+9.1/Ar[j]+(4.21+137/Ar[j])*gma[j])*(mm[j]*(vt[j]-v[j])*(vt[j]-v[j]));
      pT[j]=0.5*rho/Ar[j]*Am[j]*mm[j]*(vt[j]-v[j])*fabs((vt[j]-v[j]));
      pr[j]=-(zeta_out[j]+zeta_in[j]+lambda*Lr[j]/Dr[j])*0.5*rho*fabs(v[j])*v[j];
      pj[j]=Kj[j]*nj[j]*rho*Aj[j]/Ar[j]*fabs(vj[j])*(vj[j]-v[j]);
      p[j]=pT[j]+pr[j]+pj[j];

      //      printf("p=%lf ",pj[j]);
      f[i]+=Bs[i][j]*p[j];
      //  printf("%lf ",Bs[i][j]);
    }
    //    printf("\n");
    // printf("f[%d]=%lf\n",i,f[i]);
  }

}
