#ifndef _FUNC_H_
#define _FUNC_H_


double func_f(double v_old,double x_old);
double func_g(double v_old);
double exEuler(FILE *fp,double t,double dt,double v_old,double x_old);
double rk4(FILE *fp2,double t,double dt,double v_old,double x_old);
int output(FILE *fp,double t,double x_old,double v_old);


#endif // _FUNC_H_
