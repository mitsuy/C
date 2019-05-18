/*************************************************************************************

      Static velocity calculation in tunnel

            As.Q = -Qe  ----(i)
	    Bs.p = 0    ---(ii)

     where As, Q=Av, Qe, B and p are irreducible incidence matrix, 
     flow, exhaust fan flow, loop matrix and pressure in tunnel,respectively.
     A and v are area and velocity within tunnel,respectively. 
     p is function of v.
      Solve Eqs.(i) and (ii) as simultaneous equations for v 
     by Newton-Raphson method since Eq.(ii) is included nonlinear term for v.



     Written by M.Yagyu, 19 April 2019

**************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "func.h"

#define MX 20
#define MXB 100


int main(int argc, char *argv[])
{

  /// Variables related to function /// 
  double v[MX]={0.};                                    // Section velocity in tunnel
  double As[MX][MX]={0.0},Qe[MX]={0.0},Q[MX]={0.0};     // Irreducible incidence matrix, Exhaust fan flow, flow in tunnel
  double Bs[MX][MX]={0.0},p[MX]={0.0},dp[MX]={0.};      // Loop matrix, The difference of section pressure, differencial value of pressure 
  double pT[MX]={0.0},pr[MX]={0.0},pj[MX]={0.0};        // Forces of transportation ventilation, wall friciton and JF boosting
  double dpT[MX]={0.0},dpr[MX]={0.0},dpj[MX]={0.0};     // differencial values of puressures
  double J[MX][MX]={0.},J_inv[MX][MX]={0.};             // Jacobian and inverse Jacobian matrixes
  double f[MX]={0.0};                                   // nonlinear Function 

  /// Input parameters from any files ///
  double Ar[MX]={0.0},Lr[MX]={0.0},Dr[MX]={0.0};        // Area, Section length and characteristic diameter
  double mm[MX]={0.0},mt[MX]={0.0};                     // Number of existence of vehicle and transportation value of vehicle
  double vt[MX]={0.0},vth[MX]={0.0},gma[MX]={0.0};      // Vehicle velocity [/s] and [/h], Ratio of mixing of large vehicle
  double Am[MX]={0.};                                   // Area of vehicle
  double zeta_out[MX]={0.},zeta_in[MX]={0.0};           // Loss coefficient of exit and entrance
  double Aj[MX]={0.0},Kj[MX]={0.0};                     // Area and efficiency of JF
  double vj[MX]={0.0},nj[MX]={0.0};                     // velocity and number of JF
  int irf[MX]={0.0},irt[MX]={0.0};                      // Section From, to
  int M,N,node;                                         // Section number, Loop number
  char name[MXB];                                       // Data name
  char memo[MXB][MXB];                                  // Section name
  
  /// Constant parames ///
  double rho=1.2,lambda=0.025;                          // Density of air, Coefficient of friction loss



  /// Variables used in main function ///
  int itr,i;
  double ierr;
  double eps=1.0e-6,max_err;
  FILE *fp;
  
  if((fp=fopen(argv[1],"r"))==NULL){
    printf("Can't find such as that file.\n");
    exit(1);
  }
  
  /// *** Input parameters from any data file. ***///
  read_data(fp,argv,Ar,Lr,Dr,mm,mt,vt,vth,gma,Am,\
	    zeta_out,zeta_in,Aj,Kj,vj,nj,irf,irt,&M,&N,memo,name,As,Bs,Qe);
  /*  for(i=0;i<M;i++){
    printf("vj=%lf ",vj[i]);
  }
  printf("\n");
  */
  for(itr=0;itr<30;itr++){

    
    /// *** Dicision of function *** ///
    function(&N,&M,As,Bs,v,Qe,f,pT,pr,pj,p,rho,Ar,Am,mm,vt,\
	     zeta_out,zeta_in,lambda,Lr,Dr,vj,Kj,nj,Aj);

    /// *** Jacobian and inverse Jacobian *** ///
    jacobian(&N,&M,J,J_inv,As,Bs,dpT,dpr,dpj,dp,rho,Ar,Am,mm,vt,\
	     zeta_out,zeta_in,lambda,Lr,Dr,vj,Kj,nj,Aj,v);
    
    /// *** Main Calculation *** ///
    max_err=newton_raphson(&M,v,J_inv,f);
    
    /// *** Error for stopping calculation *** ///
    if(max_err<eps){
      printf("======================= Solution v[i]  Converged !! ===========================\n\n");
      break;
    }
  }
  
  /// *** Display or output to file input parameters. *** ///
  print_data(Ar,Lr,Dr,mm,mt,vt,vth,gma,Am,\
	     zeta_out,zeta_in,Aj,Kj,vj,nj,irf,irt,&M,&N,memo,name,As,Bs,Qe);

  
  /// *** Display simulation results *** ///
  printf("------- Solution -------\n");

  printf("Velocity : \n");
  for(i=0;i<M;i++){
    printf("           v%d=%7.3lf ",i+1,v[i]);
  }
  printf("\n");

  printf("Flow : \n");
  for(i=0;i<M;i++){
    printf("           Q%d=%7.3lf ",i+1,Ar[i]*v[i]);
  }
  printf("\n\n");
  
  printf("iteration time = %d\n",itr);
  printf("Maximum error  = %lf\n\n",max_err*100);

  
  fclose(fp);
  return EXIT_SUCCESS;
}







