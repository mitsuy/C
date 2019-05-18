/*

  Matrix multiplication for regular matrix.


  Written by M.Yagyu, 2 April 2019
  
  Question : How is n-dimensional array dynamically stored 
             in C language ??

  Answer   : Must use pointer ... ?

 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 3   // Problem size


int main(int argc, char *argv[]){

  //  double a[2][2],b[2][2],c[2][2]={0.};
  double a[N][N]={0.},b[N][N]={0.},c[N][N];
  int i,j,k,n;
  double rnd,rnd2;
  unsigned int T=(unsigned int)time(NULL);

  srand(T);

  //  printf("Please input matrix dimension (regular matrix): ");
  //  scanf("%d",&n);
  printf("Calculate %d * %d matrix multiplication\n",N,N);



  /// Initialization ///
  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      rnd=((double)rand()+1.)/((double)RAND_MAX+2.)*10;
      rnd2=((double)rand()+1.)/((double)RAND_MAX+2.)*10;
      //      printf("%lf\n",rnd);
      a[j][i]=rnd;
      b[j][i]=rnd2;
    }
    //    printf("%lf\n",a[j][i]);
  }


  printf("\n");
  
  for(i=0;i<N;i++){
    
    for(j=0;j<N;j++){
   
      printf("a[%d][%d]=%lf ",j,i,a[j][i]);
    }
    printf("\n");
  }
  
  printf("\n");
  
  for(i=0;i<N;i++){
    
    for(j=0;j<N;j++){
      
      printf("b[%d][%d]=%lf ",j,i,b[j][i]);
    }
    printf("\n");
  }
  
  printf("\n");

  /*
  a[0][0]=1.,a[1][0]=2.,a[0][1]=3.,a[1][1]=4.;
  b[0][0]=5.,b[1][0]=6.,b[0][1]=7.,b[1][1]=8.;
  */

  
  // Main calculation
  for(i=0;i<N;i++){
    
    for(j=0;j<N;j++){
      c[j][i]=0.;
      for(k=0;k<N;k++){
	
	c[j][i]=a[k][i]*b[j][k]+c[j][i];
	
      }
      printf("c[%d][%d]=%lf ",j,i,c[j][i]);
    }
    printf("\n");
  }

  

  return EXIT_SUCCESS;
}
