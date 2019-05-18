/*
  Jacobi matrix and inverse one are calculated, which are necessary for Newton Raphson method.


  Written by M.YAGYU, 22 April, 2019

 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MX 20
#define MXB 100



double jacobian(int *N,int *M,double (*J)[MX],double (*J_inv)[MX],double (*As)[MX],double (*Bs)[MX],\
		double *dpT,double *dpr,double *dpj,double *dp,double rho,double *Ar,double *Am,\
		double *mm,double *vt,double *zeta_out,double *zeta_in,double lambda,double *Lr,\
		double *Dr,double *vj,double *Kj,double *nj,double *Aj,double *v)
{
  int i,j,k;
  double tmp,tmp2,tmp3;
  double max_pv=0.;
  int pivot_row=0;
  
  for(i=0;i<*N;i++){
    for(j=0;j<*M;j++){
      J[i][j]=As[i][j]*Ar[j];

      //      printf("%lf ",J[i][j]);
      
    }
    //    printf("\n");
  }
  for(i=*N;i<*M;i++){
    for(j=0;j<*M;j++){
      //      dpT[j]=-rho*1/Ar[j]*(0.78+9.1/Ar[j]+(4.21+137/Ar[j])*gma[j])*(mm[j]*(vt[j]-v[j]));
      //      dpT[j]=0.5*rho/Ar[j]*Am[j]*mm[j]*(-2.0)*(vt[j]-v[j]);
      dpT[j]=0.5*rho/Ar[j]*Am[j]*mm[j]*(-1.)*((vt[j]-v[j])+fabs(vt[j]-v[j]));

      if(v[j]>0){
	dpr[j]=-(zeta_out[j]+zeta_in[j]+lambda*Lr[j]/Dr[j])*rho*v[j];
      }else{
	dpr[j]=(zeta_out[j]+zeta_in[j]+lambda*Lr[j]/Dr[j])*rho*v[j];
      }
      
      dpj[j]=-Kj[j]*nj[j]*rho*Aj[j]/Ar[j]*fabs(vj[j]);
      dp[j]=dpT[j]+dpr[j]+dpj[j];

      J[i][j]=Bs[i][j]*dp[j];

      //      printf("%lf ",J[i][j]);
    }
    //    printf("\n");
  }

  
  /// ************* Inverce matrix of Jacobian *************************************** ///

  // Generate Unit matrix ******************
  for(i=0;i<*M;i++){
    for(j=0;j<*M;j++){
      if(j==i){
	J_inv[i][j]=1.0;
      }else{
	J_inv[i][j]=0.;
      }
    }
  }

  
  /// Gauss Jordan Method ///
  for(i=0;i<*M;i++){

    /// Search maximum value in pivot row. ///
    max_pv=0.0;
    for(j=i;j<*M;j++){
      if(fabs(J[j][i])>max_pv){
	max_pv=fabs(J[j][i]);
	pivot_row=j;
      }
    }

    if(max_pv == 0.0){
      printf("This matrix is not regular one !!\n\n");
      return 0;
    }
    

    /// Switch line with max pivot to current line. ///
    if(i != pivot_row){
      for(j=0;j<*M;j++){
	tmp3=J[i][j];
	J[i][j]=J[pivot_row][j];
	J[pivot_row][j]=tmp3;

	tmp3=J_inv[i][j];
	J_inv[i][j]=J_inv[pivot_row][j];
	J_inv[pivot_row][j]=tmp3;

      }
    }
    
    /// Diagonal components =1 ///
    tmp=1./J[i][i];
    for(j=0;j<*M;j++){
      J[i][j]=J[i][j]*tmp;
      J_inv[i][j] =J_inv[i][j]*tmp;
    }

    /// Non-diagonal components =0 ///
    for(k=0;k<*M;k++){
      if(k==i)continue;
      tmp2=J[k][i];
      for(j=0;j<*M;j++){
	J[k][j]=J[k][j]-J[i][j]*tmp2;
	J_inv[k][j]=J_inv[k][j]-J_inv[i][j]*tmp2;

	//	printf("%lf",J_inv[k][j]);
      }
      //      printf("\n");
    }

    
  }
  /*  
  printf("Invers matrix J^{-1}=\n");
  for(i=0;i<*M;i++){
    for(j=0;j<*M;j++){
      printf("%9.5lf ",J_inv[i][j]);
    }
    printf("\n");
  }
  */

}
