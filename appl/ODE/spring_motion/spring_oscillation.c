/**************************************************************************************

   Ordinary Differential Equation (ODE) Solver.
   Solve numerically 2nd-order ODE as follows.

       m*x'' + c*x' + k*x = 0    ---------(i)

  Since
              x'=v           -------------(ii) 

  , can rewrite Eq.(i) as follows.

        m*v' + c*v +k*x = 0   ------------(iii)

  Thus, solve Eqs.(ii) and (iii) as simultaneous equations

  Where m, c and k are mass of spring, unknown parameter 
  and elastic coefficient, respectively. Eq.(i) means 
  spring motion with resistance that is proportion to velocity.
  


  Written by M.Yagyu. April 5, 2019

  Modified : 
             M.Yagyu, April 8, 2019

******************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "func.h"


int main(int argc, char *argv[]){

  int i,flag;
  double t,dt;    // time and time step
  double v_old;      // velocity of spring
  double x_old;       // position of spring
  FILE *fp,*fp2;
  
  /////////////// Initialization ////////////////////////////////////////////
  
  v_old=0.;  // Initial velocity
  x_old=10.;  // Initial position

  printf("Input time step delt_time=");
  scanf("%lf",&dt);
  //  dt=0.1;     // time step

  
  printf("\n");
  printf("Choose ODE Solver!! \n");
  printf("Explicit Euler Method ----> 1 \n");
  printf("4th Runge-Kutta Method ----> 2 \n");

  scanf("%d",&flag);
    
  if(flag==1){
    if((fp=fopen("result_eem.dat","w"))==NULL){
      printf("Cant open the file.\n");
      exit(1);
    }
  }else{
    if((fp2=fopen("result_rk4.dat","w"))==NULL){
      printf("Cant open the file.\n");
      exit(1);
    }
  }

  // Main calculation //////////////////////////////////////
  
  if(flag==1){
    // Explicit Euler Method ////
    exEuler(fp,t,dt,v_old,x_old);
  }else{
   // 4th Runge-Kutta Method /////
    rk4(fp2,t,dt,v_old,x_old);
  }
  //////////////////////////////////////////////////////////

  
  if(flag==1){
    fclose(fp);
  }else{
    fclose(fp2);
  }

  return EXIT_SUCCESS;

}







