/*
  Test making Header file.

  Written M.Yagyu
  12 April, 2019

 */


#ifndef _RK4_H_
#define _RK4_H_

double rk4(FILE *, double, double,double);
double func(double, double);
int output(FILE *, double, double);

#endif // _RK4_H_
