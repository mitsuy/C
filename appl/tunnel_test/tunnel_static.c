/*

     Static velocity calculation in tunnel

            As*Q = -Qe  ----(i)
	    Bs*p = 0    ---(ii)

     where As, Q=Av, Qe, B and p are term of connection matrix, 
     flow, loop matrix and pressure in tunnel,respectively.
     A and v are area and velocity withn tunnel,respectively. 
     p is function of v.
      Solve Eqs.(i) and (ii) as simultaneous equations for v 
      by Newton-Raphson method since Eq.(ii) is included nonlinear term for v.



     Written by M.Yagyu, 19 April 2019

 */






#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MX 20
#define MXB 100



double v[MX]={0.};                     // velocity in each period.
double As[MX][MX],Qe[MX],Q[MX];             // a:terms of connection matrix, Qe: exhaust fan flow
double Bs[MX][MX],p[MX],dp[MX]={0.};              // b:loop matrix, p:pressure gradient
double Ar[MX]={0.0};                    // Area
double J_inv[MX][MX]={0.},J[MX][MX]={0.};           // Inverse matrix of Jacobi for test
double f[MX];                          // test func.

double rho=1.2;                           // Air density
double pT[MX],pr[MX],pj[MX];
double dpT[MX],dpr[MX],dpj[MX];
double mm[MX],mt[MX],vt[MX],vth[MX],gma[MX];                   // Number of existence of car, velocity of car and ??.
double Am[MX]={0.};
double zeta_out[MX]={0.},zeta_in[MX],lambda=0.025,Lr[MX],Dr[MX];
double Aj[MX],vj[MX],nj[MX];
int irf[MX],irt[MX];                     // Period From and Period To
double Kj[MX],Zr[MX];                       // effective, coefficient of entrance loss.
int M,N,node;
char name[MXB];
char memo[MXB][MXB];


void read_data(FILE *fp,char *argv[]);
void print_data();
double function();
double jacobian();
double newton_raphson();

int main(int argc, char *argv[])
{

  int itr,i;
  double ierr;
  double eps=1.0e-3,max_err=0.;
  FILE *fp;
  

  if((fp=fopen(argv[1],"r"))==NULL){
    printf("Can't find such as that file.\n");
    exit(1);
  }
  
  /// Input parameters from any data file. ///
  read_data(fp,argv);

 
  
  for(itr=0;itr<30;itr++){

    
    //*** Dicision of function ***
    function();

    //*** Jacobian ***
    jacobian();
    

    //*** Main Calculation ***
    max_err=newton_raphson();
   
    // Error for stopping calculation
    if(max_err<eps){
      printf("======================= Solution v[i]  Converged !! ===========================\n\n");
      break;
    }
  }

  /// Display or output to file input parameters. ///
  print_data();
  
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

void read_data(FILE *fp, char *argv[]){
  
  static int i=0,it,idb[MX],ida[MX];
  int cnt=0,cnt2=0;
  char str[MXB]={'\0'};
  char str2[MXB]={'\0'};
  static int j,k,l,r,s,dammy,dammy2,dammy3;
  char buf[MXB];


  
 j=1;
 


 fgets(str,MXB,fp);
 strcpy(name,str);
 //printf("%s",name);
  
 while((fgets(str,MXB,fp)) !=NULL){
   //  fgets(str,N,stdin);

   sscanf(str,"%d ,%d ,%d ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%s",
	  &j,&k,&l,&Lr[i],&Ar[i],&Dr[i],&mt[i],&vth[i],&gma[i],&nj[i],&vj[i],
	  &Aj[i],&Kj[i],&Qe[i],&zeta_in[i],buf);

   strcpy(memo[i],buf);
   if(j==0){
     M=cnt2;      // period number;
     break;
   }
   /*    
   printf("%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%s\n\n",
	  j,k,l,Lr[i],Ar[i],Dr[i],mt[i],vth[i],gma[i],nj[i],vj[i],
	  Aj[i],Kj[i],Qe[i],Zr[i],buf);
   */

   // Parameters setting
   irf[i]=k, irt[i]=l;
    
   if(Qe[i] != 0){
     idb[k-2]=i+1;
     //      printf("idb=%d\n",idb[0]);
   }
    
   vt[i]=vth[i]/3.6;
   mm[i]=mt[i]/3600. * Lr[i]/vt[i];
    
   Am[i]=0.78+9.1/Ar[i]+(4.21+137.0/Ar[i])*gma[i];
   As[k-2][j-1]=1;
   As[l-2][j-1]=-1;
    
   cnt2++;
   i++;
 }




  
 for(i=0;i<MX;i++){
   As[i][M]=idb[i];
 }
  
 while((fgets(str,MXB,fp)) !=NULL){
    
  
    sscanf(str,"%d ,%d ,%d ,%d ,%d",&ida[0],&ida[1],&ida[2],&ida[3],&ida[4]);


    if(ida[0]==0){
      N=cnt;      // period number;
      // printf("%d\n",n);
      break;
    }

    /*
    for(it=0;it<5;it++)printf("%d ",ida[it]);
    printf("\n");
    */

    for(it=1;it<M;it++){
      if(ida[it]>0){
	Bs[ida[0]-1][ida[it]-1]=1.;
      }else{
	Bs[ida[0]-1][-ida[it]-1]=-1.;
      }
    }
    
    cnt++;
    i++;
 }

 

 for(i=0;i<N;i++){
   for(j=0;j<M;j++){
     Bs[i+N][j]=Bs[i][j];   
     //     printf("%lf ",Bs[i][j]);
   }
   //   printf("\n");
 }
}

void print_data()
{
  int i,j;

  printf("\n\n");
  printf("%s",name);
  printf("Period number m=%d, Basic Loop number n=%d\n",M,N);
  printf("Period  Fm  to      Lr       Ar       Dr      Nt         v/h        v/s     gml       Am        mm       Nj      Vj        Aj      Kj         Qe       zta       memo\n");

  for(i=0;i<M;i++){

      printf("%5d %3d %3d %9.1lf %9.1lf %7.1lf %9.1lf %9.1lf %9.1lf %7.3lf %9.2lf %9.2lf %7.1lf %9.1lf %9.2lf %7.2lf %9.1lf %9.2lf %9s\n",
	     i+1,irf[i],irt[i],Lr[i],Ar[i],Dr[i],mt[i],vth[i],vt[i],gma[i],Am[i],mm[i],nj[i],vj[i],Aj[i],Kj[i],Qe[i],zeta_in[i],memo[i]);
  }
  printf("\n\n");

  
  printf("-------- Term of connection matrix As-----------------\n");
  printf("Brunch :    1       2       3       4       Qe\n");
  for(i=0;i<N;i++){
    printf("As[%2d] =",i+1);
    for(j=0;j<M+1;j++){
      printf("%7.1lf ",As[i][j]);
    }
    printf("  (Node %d)",i+2);
    printf("\n");
  }
  printf("\n");

  printf("-------- Loop matrix Bs-------------------------------\n");
  printf("Brunch :    1       2       3       4\n");
  for(i=0;i<N;i++){
    printf("Bs[%2d] =",i+1);
    for(j=0;j<M;j++){
      printf("%7.1lf ",Bs[i][j]);
    } 
    printf("\n");
  }
  

  printf("\n\n");
}



double function()
{
  int i,j;

  for(i=0;i<N;i++){
    f[i]=0.;
    for(j=0;j<M;j++){
      //      f[i]+=As[i][j]*Ar[j]*v[j]-Qe[j+1];
      f[i]+=As[i][j]*Ar[j]*v[j];
      //     printf("%lf ",As[i][j]);
    }
    f[i]+=Qe[i+1];
    //    printf("\n");
    //printf("f[%d]=%lf\n",i,f[i]);
  }
  
  for(i=N;i<M;i++){
    f[i]=0.;
    for(j=0;j<M;j++){
      //      pT[j]=-rho*1/Ar[j]*(0.78+9.1/Ar[j]+(4.21+137/Ar[j])*gma[j])*(mm[j]*(vt[j]-v[j])*(vt[j]-v[j]));
      pT[j]=0.5*rho/Ar[j]*Am[j]*mm[j]*(vt[j]-v[j])*(vt[j]-v[j]);
      pr[j]=-(zeta_out[j]+zeta_in[j]+lambda*Lr[j]/Dr[j])*0.5*rho*fabs(v[j])*v[j];
      pj[j]=Kj[j]*nj[j]*rho*Aj[j]/Ar[j]*fabs(vj[j])*(vj[j]-v[j]);
      p[j]=pT[j]+pr[j]+pj[j];
      
      printf("p=%lf ",pj[j]);
      f[i]+=Bs[i][j]*p[j];
      //  printf("%lf ",Bs[i][j]);
    }
    printf("\n");
    //printf("f[%d]=%lf\n",i,f[i]);
  }

}

double jacobian()
{
  int i,j,k;
  double tmp,tmp2,tmp3;
  double max_pv=0.;
  int pivot_row=0;
  
  for(i=0;i<N;i++){
    for(j=0;j<M;j++){
      J[i][j]=As[i][j]*Ar[j];

      //printf("%lf ",J[i][j]);
      
    }
    //    printf("\n");
  }
  for(i=N;i<M;i++){
    for(j=0;j<M;j++){
      //      dpT[j]=-rho*1/Ar[j]*(0.78+9.1/Ar[j]+(4.21+137/Ar[j])*gma[j])*(mm[j]*(vt[j]-v[j]));
      dpT[j]=0.5*rho/Ar[j]*Am[j]*mm[j]*(-2.0)*(vt[j]-v[j]);

      if(v[j]>0){
	dpr[j]=-(zeta_out[j]+zeta_in[j]+lambda*Lr[j]/Dr[j])*rho*v[j];
      }else{
	dpr[j]=(zeta_out[j]+zeta_in[j]+lambda*Lr[j]/Dr[j])*rho*v[j];
      }
      
      dpj[j]=-Kj[j]*nj[j]*rho*Aj[j]/Ar[j]*fabs(vj[j]);
      dp[j]=dpT[j]+dpr[j]+dpj[j];

      J[i][j]=Bs[i][j]*dp[j];

      //printf("%lf ",J[i][j]);
    }
    //    printf("\n");
  }

  
  //************* Inverce matrix of Jacobian ***************************************

  // Generate Unit matrix ******************
  for(i=0;i<M;i++){
    for(j=0;j<M;j++){
      if(j==i){
	J_inv[i][j]=1.0;
      }else{
	J_inv[i][j]=0.;
      }
    }
  }

  
  /// Gauss Jordan Method ///
  for(i=0;i<M;i++){

    /// Search maximum value in pivot row. ///
    max_pv=0.0;
    for(j=i;j<M;j++){
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
      for(j=0;j<M;j++){
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
    for(j=0;j<M;j++){
      J[i][j]=J[i][j]*tmp;
      J_inv[i][j] =J_inv[i][j]*tmp;

    }

    /// Non-diagonal components =0 ///
    for(k=0;k<M;k++){
      if(k==i)continue;
      tmp2=J[k][i];
      for(j=0;j<M;j++){
	J[k][j]=J[k][j]-J[i][j]*tmp2;
	J_inv[k][j]=J_inv[k][j]-J_inv[i][j]*tmp2;

	//	printf("%lf",J_inv[k][j]);
      }
      //      printf("\n");
    }

    
  }

  /*
  printf("Invers matrix J^{-1}=\n");
  for(i=0;i<M;i++){
    for(j=0;j<M;j++){
      printf("%9.5lf ",J_inv[i][j]);
    }
    printf("\n");
  }
  */

}

double newton_raphson()
{
  int i,j;
  double temp[M],max_err=0.,ierr=0.;


  for(i=0;i<M;i++){
      temp[i]=v[i];

      for(j=0;j<M;j++){
	v[i]+=-J_inv[i][j]*f[j];
      }

      //  printf("v[%d]=%lf\n",i+1,v[i]);
            
    }

    for(i=0;i<M;i++){
      ierr=fabs(temp[i]-v[i]);

      if(ierr>max_err){
	max_err=ierr;
      }
    }

    return(max_err);

}
