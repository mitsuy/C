#include <stdio.h>
#include <stdlib.h>
#include <time.h>



double randf(){
  return rand()/((double)RAND_MAX+1);
}



int init_matrix(int n, double *mat){

  int i,j;
  double diag=1.;

  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  mat[i*n+j]=randf();
	}
      mat[i*n+i]=diag;
    }

  return EXIT_SUCCESS;

}



int init_problem_random(int n, double *a, double *b){

  srand((unsigned)time(NULL));
  init_matrix(n,a);
  init_matrix(n,b);
  
  return EXIT_SUCCESS;

}


int print_matrix(int n, double *mat){

  int i,j;

  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  printf("%24.16lf",mat[i*n+j]);
	}
      printf("\n");
    }

  return EXIT_SUCCESS;

}

//   MAIN //////////////////////////////////////////////////////

int main(int argc, char *argv[]){

  int i,j,k;
  double *a,*b,*c;
  int n;

  printf("Dimension? \n");
  scanf("%d",&n);
  printf("Dimension is %d\n\n",n);


  // allocate arrays

  a=(double *)malloc(sizeof(double)*n*n);
  b=(double *)malloc(sizeof(double)*n*n);
  c=(double *)malloc(sizeof(double)*n*n);


  init_problem_random(n,a,b);
  print_matrix(n,a);
  print_matrix(n,b);

  
  


  return EXIT_SUCCESS;
}
