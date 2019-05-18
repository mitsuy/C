/*

  //////////////////////////////////
  /                                /
  /   Gauss Elimination Method     /
  /                                /
  //////////////////////////////////

   Solver linear simultaneous equations with
  Gauss Elimination Method.

  Show the equation to solve as follows.
  
              A.x = b

  Where A and b are N*N matrix and N-dim vector. 
  x (N-dim) is the independent variable.


  Written by M.Yaygu  7 May, 2019

 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char *argv[])
{

  int i,j,k,N;
  double tmp,tmp2,tmp3;
  
  double *a,*b;
  
  double max_pv=0.;
  int pivot_row=0;


  printf("Input dimensional number N = ");
  scanf("%d",&N);

  a=(double *)malloc(sizeof(double)*N*N);
  b=(double *)malloc(sizeof(double)*N);
  

  /// Generate random numbers and initilization of matrix A with rnd ///
  double rnd,rnd2;
  unsigned int T=(unsigned int)time(NULL);
  srand(T);

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      rnd=((double)rand()+1.0)/((double)RAND_MAX+2.0)*10;
      a[i*N+j]=rnd;
    }
    rnd2=((double)rand()+1.0)/((double)RAND_MAX+2.0)*10;
    b[i]=rnd2;
  }

  /*****************************************************/
  /*                                                   */
  /*           Display problem equation                */
  /*                                                   */
  /*****************************************************/  

  printf("\n\n");

  printf("                   A.x = b \n\n");
  for(i=0;i<N;i++){
    printf(" [");    
    for(j=0;j<N;j++){
      printf("%7.2lf ",a[i*N+j]);
    }

    printf(" ]  ");
    printf("[  x_%3d  ]  ",i+1);
    if(i==N/2){
      printf("=   [%7.2lf  ]\n",b[i]);
    }else{
      printf("    [");
      printf("%7.2lf ",b[i]);
      printf(" ]");
      printf("\n");
    }
  }
  printf("\n");
  

  /////////////////////////////////////////////
  /*                                         */                                        
  /*          Forward Elimination            */
  /*                                         */
  /////////////////////////////////////////////
  for(i=0;i<N;i++){
  
    // Searching maximum value in pivot row.
    max_pv=0.0;
    for(j=i;j<N;j++){
      if(fabs(a[j*N+i])>max_pv){
	max_pv=fabs(a[j*N+i]);
	pivot_row=j;
      }
    }
    
    if(max_pv ==0.0){
      printf("This matrix is not regular one !!\n\n");
      return 0;
    }
   

    // Switching line with max pivot to current line.
    if(i != pivot_row){
      for(j=0;j<N;j++){
	tmp=a[i*N+j];
	a[i*N+j]=a[pivot_row*N+j];
	a[pivot_row*N+j]=tmp;
      }
      tmp=b[i];
      b[i]=b[pivot_row];
      b[pivot_row]=tmp;
    }
  
    /// Diagonal components 
    tmp=1./a[i*N+i];
    b[i]=b[i]*tmp;
    for(j=i;j<N;j++){
      a[i*N+j]=a[i*N+j]*tmp;
    }
    
   /// Low non-diagonal components  = 0
    for(k=i;k<N;k++){
      if(k==i)continue;
      
      tmp=a[k*N+i];

      for(j=i;j<N;j++){
	a[k*N+j]=a[k*N+j]-a[i*N+j]*tmp;
      }
      
      b[k]=b[k]-b[i]*tmp;
    }
  }

  /////////////////////////////////////////////
  /*                                         */                                        
  /*          Backward Substitution          */
  /*                                         */
  /////////////////////////////////////////////

  for(i=N-1;i>0;i--){
    
    for(k=i;k>=0;k--){
      if(k==i)continue;
      tmp=a[k*N+i];

      for(j=0;j<N;j++){
	a[k*N+j]=a[k*N+j]-a[i*N+j]*tmp;
      }
      
      b[k]=b[k]-b[i]*tmp;  // Solution
    }
  }
  
  /// Check ///
  /*
  printf("matrix A=\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%9.2lf ",a[i][j]);
    }
    printf("\n");

  }
  */
  
  /////////////////////////////////////////////
  /*                                         */                                        
  /*          Show results                   */
  /*                                         */
  /////////////////////////////////////////////

  printf("---------- Solution -------\n\n");  
  for(i=0;i<N;i++){
    printf(" x%d=%9.2lf ",i+1,b[i]);
    printf("\n");
  }
  printf("---------------------------\n\n");
  
  free(a);
  free(b);
  
  return EXIT_SUCCESS;
  
}
