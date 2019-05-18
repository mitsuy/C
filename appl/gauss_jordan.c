/*
  Solve the inverse matrix of N*N matrix A by Gauss-Jordan Method.
  

  Written by M.Yaygu  17 April, 2019

  Modified by M.Yagyu 7 May, 2019
   Change how to allocate memories from static to dynamic.


 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>




int main(int argc, char *argv[])
{

  int i,j,k,N;
  double tmp,tmp2,tmp3;

  double *a;
  double *inv_a;
  
  double max_pv=0.;
  int pivot_row=0;

  printf("Input dimensional number N = ");
  scanf("%d",&N);

  a=(double *)malloc(sizeof(double)*N*N);
  inv_a=(double *)malloc(sizeof(double)*N*N);
    
  
  double rnd;
  unsigned int T=(unsigned int)time(NULL);
  srand(T);

  /// Generate random numbers and initilization of matrix A with rnd ///
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      rnd=((double)rand()+1.0)/((double)RAND_MAX+2.0)*10;
      a[i*N+j]=rnd;
    }
  }

  
  // Generate Unit matrix ******************
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(j==i){
	inv_a[i*N+j]=1.0;
      }else{
	inv_a[i*N+j]=0.;
      }
    }
  }
  
  //*****************************************
  
  printf("Matrix A=\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%9.2lf ",a[i*N+j]);
    }
    printf("\n");
  }
  printf("\n");

  
  // Gauss Jordan Method**************************
  for(i=0;i<N;i++){

    
    // Search maximum value in pivot row.
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
   

    // Switch line with max pivot to current line.
    if(i != pivot_row){
      for(j=0;j<N;j++){
	tmp3=a[i*N+j];
	a[i*N+j]=a[pivot_row*N+j];
	a[pivot_row*N+j]=tmp3;

	tmp3=inv_a[i*N+j];
	inv_a[i*N+j]=inv_a[pivot_row*N+j];
	inv_a[pivot_row*N+j]=tmp3;

      }
    }
    
  
    // Diagonal components = 1
    tmp=1./a[i*N+i];
    for(j=0;j<N;j++){
      a[i*N+j]=a[i*N+j]*tmp;
      inv_a[i*N+j] =inv_a[i*N+j]*tmp;
      
    }

    // Non-diagonal componets = 0
    for(k=0;k<N;k++){
      if(k==i)continue;
      tmp2=a[k*N+i];
      for(j=0;j<N;j++){
	a[k*N+j]=a[k*N+j]-a[i*N+j]*tmp2;
	inv_a[k*N+j]=inv_a[k*N+j]-inv_a[i*N+j]*tmp2;
      }
    }
  }



  printf("Invers matrix A^{-1}=\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%9.2lf ",inv_a[i*N+j]);
    }
    printf("\n");
  }

  free(a);
  free(inv_a);
  
  return EXIT_SUCCESS;
}
