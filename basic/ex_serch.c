/*

         Optimilization problem.

    There are 5 villages. Those positions are described by 
   x and y coordinate, that is, 2D Cartesian one.
    For example, a village coordinate is desbribed as (xi,yi).

    Now, fire station is built in (x,y) but this (x,y) have to be 
   satisfied that under equation is minimum value;

            z=Sigma_i [ sqrt( {x-xi}^2 + {y-yi}^2 ) ]  ---(i)
   
    In short, Summation of distance of between fire station and each village 
   has to be minimum. 

   Solve this problem by exhaustive search.
   Limiting conditions : 0 <= x <= NX, 0 <= y <= NY

   Written by M.Yagyu, 24 April 2019

 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5     // Village number
#define NX 8    // Limiting condition for x
#define NY 10   // Limiting condition for y

int main(int argc,char *argv[])
{
  int i,j,k;
  double x=0.,y=0.,z=0.;
  double xx[N]={1,4,15,11,5},yy[N]={12,14,10,2,5}; // village coordinate
  int nx,ny;
  double dx,dy;
  double tmp=0.,tmp2=0.;
  double min=0.,min2=0,mx,my,my2,mx2;


  dx=0.01,dy=0.01;  // step width for x and y.
  nx=NX/dx;
  ny=NY/dy;

  
  for(i=0;i<nx;i++){
    y=0.;

    for(k=0;k<ny;k++){
      z=0.;
      
      for(j=0;j<N;j++){
	z+=sqrt((x-xx[j])*(x-xx[j])+(y-yy[j])*(y-yy[j]));
      }
      
      if(tmp>z){
	tmp2=z;
	mx=i*dx;
	my=k*dy;
	tmp=tmp2;   
      }else{
	tmp=z;
      }
      
      y+=dy;
    }
    
    if(min>tmp2){
      min2=tmp2;
      mx2=mx;
      my2=my;
      min=min2;
    }else{
      min=tmp2;
    }
        
    x+=dx;

    //   printf("z(%lf,%lf)=%lf\n",i*dx,k*dy,ls[i]);    	
  }

  printf("Optimal solution\n");
  printf("(x,y)=(%.1lf,%.1lf)\n",mx2,my);
  printf("    z=%9.3lf\n",min2);
  
  return EXIT_SUCCESS;
}
