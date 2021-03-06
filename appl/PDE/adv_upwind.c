/*

  Solve linear advection equation with upwind difference Method.

          du/dt + a* (du/dx) = 0 ,   a=const>0    

  Boundary Condision : Periodic

    Written by M.Yagyu, 10 April, 2019


 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{

  int i,j,nx,nt;
  double delt_time,max_time;
  double delt_x,lx;
  double x,t,nu,a;
  double *ux;
  double pi=M_PI,tmp=0.,total=0.,total0=0.;

  FILE *fp,*fp2;

  if((fp=fopen("solution.dat","w"))==NULL){
    printf("Cant open files");
    exit(1);
  }
  if((fp2=fopen("conserv.dat","w"))==NULL){
    printf("Cant open files");
    exit(1);
  }
  
  // Initialization
  
  max_time=100.;      // Max calc time

  // time step
  printf("Time step dt=");
  scanf("%lf",&delt_time);
  
  
  nt=(int)max_time/delt_time; // time grid

  lx=1.0;             // box size


  // space grid
  printf("Grid of x nx=");
  scanf("%d",&nx);
  
  
  delt_x=(double)lx/nx; // space step    

  x=0.;
  t=0.;
  a=1.;              // Advection coefficient
  nu=a*(delt_time/delt_x);     // Courant number

  printf("dt=%lf, nx=%d Courant number nu=%lf\n\n",delt_time,nx,nu);

  
  ux=(double *)malloc(sizeof(double)*(nx+3));  // Dynamically store memories

  // Initial function for ux
  for(i=1;i<nx+2;i++)
    {
     ux[i]=.5*sin(x*pi);
     x=x+delt_x;
    }
  
  for(i=1;i<nx;i++){
    total0=delt_x*(ux[i+1]-ux[i])+total0;
  }
  total0=total0+1.;
  printf("time=%16.5lf, total=%16.5lf\n",t,total0);
  
  
  // Periodic Boundary Condision
  ux[nx+2]=ux[1];
  ux[0]=ux[nx+2];


  
  for(i=0;i<nt;i++)
    {
      x=0.;
      
      for(j=1;j<nx+2;j++)
	{
	  fprintf(fp,"%16.5lf %16.5lf %16.5lf\n",t,x,ux[j]);
		
	  //	  ux[j]=ux[j]-nu*(ux[j]-ux[j-1]);
	  ux[j]=ux[j]-0.5*nu*(3*ux[j]-4*ux[j-1]+ux[j-2]);

	 // printf("%16.5lf %16.5lf %16.5lf\n",t,x,ux[j]);
	 x=x+delt_x;

	}

      fprintf(fp,"\n");
      //printf("\n");
      t=t+delt_time;
      
      // Periodic Boundary Condision
      ux[nx+2]=ux[1];
      ux[0]=ux[nx+1];
      
      
      for(j=1;j<nx;j++){
	total=delt_x*(ux[j+1]-ux[j])+total;
      }
      
      total=total+1.;
      //      printf("time=%16.5lf, total=%16.5lf, difference=%16.5lf [%]\n",t,total,fabs((total0-total)/total0)*100);
      //      printf("%16.5lf %16.5lf %16.5lf\n",t,total,fabs((total0-total)/total0)*100);
      fprintf(fp2,"%16.5lf %16.5lf %16.5lf\n",t,total,fabs((total0-total)/total0)*100);
      total0=total;
      total=0.;
      
    }

  fclose(fp);
  fclose(fp2);
  free(ux);
  
  return EXIT_SUCCESS;
}
