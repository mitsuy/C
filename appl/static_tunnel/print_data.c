/*

  Display parameters which are necessary to calculate.


  Written by M.YAGYU,   22 April, 2019
  

 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MX 20
#define MXB 100



int print_data(double *Ar,double *Lr,double *Dr,double *mm,double *mt,double *vt,double *vth,\
	       double *gma,double *Am,double *zeta_out,double *zeta_in,double *Aj,double *Kj,\
	       double *vj,double *nj,int *irf,int *irt,int *M,int *N,char (*memo)[MXB],char *name,\
	       double (*As)[MX],double (*Bs)[MX],double *Qe)
{
  int i,j;

  printf("\n\n");
  printf("%s",name);
  printf("Section number m=%d, Basic Loop number n=%d\n",*M,*N);
  printf("Section  Fm  to      Lr       Ar       Dr      Nt         v/h        v/s     gml       Am        mm       Nj      Vj        Aj      Kj         Qe       zta       memo\n");

  for(i=0;i<*M;i++){

      printf("%6d %3d %3d %9.1lf %9.1lf %7.1lf %9.1lf %9.1lf %9.1lf %7.3lf %9.2lf %9.2lf %7.1lf %9.1lf %9.2lf %7.2lf %9.1lf %9.2lf %9s\n",
	     i+1,irf[i],irt[i],Lr[i],Ar[i],Dr[i],mt[i],vth[i],vt[i],gma[i],Am[i],mm[i],nj[i],vj[i],Aj[i],Kj[i],Qe[i],zeta_in[i],memo[i]);
  }
  printf("\n\n");

  
  printf("-------- Irreducible incidence matrix As-----------------\n");
  printf("Brunch :    1       2       3       4       Qe\n");
  for(i=0;i<*N;i++){
    printf("As[%2d] =",i+1);
    for(j=0;j<*M+1;j++){
      printf("%7.1lf ",As[i][j]);
    }
    printf("  (Node %d)",i+2);
    printf("\n");
  }
  printf("\n");

  printf("-------- Loop matrix Bs-------------------------------\n");
  printf("Brunch :    1       2       3       4\n");
  for(i=0;i<*N;i++){
    printf("Bs[%2d] =",i+1);
    for(j=0;j<*M;j++){
      printf("%7.1lf ",Bs[i][j]);
    } 
    printf("\n");
  }
  

  printf("\n\n");
}

