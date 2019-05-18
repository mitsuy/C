#ifndef _FUNC_H_
#define _FUNC_H_

int read_data(FILE *,char *argv[],double *Ar,double *Lr,double *Dr,\
	      double *mm,double *mt,double *vt,double *vth,double *gma,double *Am,\
	      double *zeta_out,double *zeta_in,double *Aj,double *Kj,double *vj,double *nj,\
	      int *irf,int *irt,int *M,int *N,char (*memo)[],char *name,\
	      double (*As)[],double (*Bs)[],double *Qe);

int print_data(double *Ar,double *Lr,double *Dr,double *mm,double *mt,double *vt,double *vth,\
	       double *gma,double *Am,double *zeta_out,double *zeta_in,double *Aj,double *Kj,double *vj,\
	       double *nj,int *irf,int *irt,int *M,int *N,char (*memo)[],char *name,\
	       double (*As)[],double (*Bs)[],double *Qe);

double function(int *N,int *M,double (*As)[],double (*Bs)[],double *v,double *Qe,\
		double *f,double *pT,double *pr,double *pj,double *p,double rho,\
		double *Ar,double *Am,double *mm,double *vt,double *zeta_out,double *zeta_in,\
		double lambda,double *Lr,double *Dr,double *vj,double *Kj,double *nj,double *Aj);

double jacobian(int *N,int *M,double (*J)[],double (*J_inv)[],double (*As)[],double (*Bs)[],\
		double *dpT,double *dpr,double *dpj,double *dp,double rho,double *Ar,\
		double *Am,double *mm,double *vt,double *zeta_out,double *zeta_in,\
		double lambda,double *Lr,double *Dr,double *vj,double *Kj,double *nj,double *Aj,double *v);

double newton_raphson(int *M,double *v,double (*J_inv)[],double *f);

#endif // _FUNC_H_
