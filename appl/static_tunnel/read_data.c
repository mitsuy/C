/*

  Input parameters from any files, then As and Bs are defined.


  Note that :
              Since I dont know why but stored number in array nj 
	     change [4,0,4,0] to [1,0,-1,-1] around being defined As,
	     temporarily, nj is stored to new local variable Nj declared in read_data function.
 


    Written by M.YAYGU, 22 April, 2019

    Modified :
              26 April, 2019 by M.YAGYU
              Modified how to read parameters for generating loop matrix Bs. 
             Change static readig to dynamic reading.

 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MX 20
#define MXB 100

int read_data(FILE *fp, char *argv[],double *Ar,double *Lr,double *Dr,\
	      double *mm,double *mt,double *vt,double *vth,double *gma,double *Am,\
	      double *zeta_out,double *zeta_in,double *Aj,double *Kj,double *vj,\
	      double *nj,int *irf,int *irt,int *M,int *N,char (*memo)[MXB],char *name,\
	      double (*As)[MX],double (*Bs)[MX],double *Qe)
{
  
  static int i=0,it,idb[MX],ida[MX];
  int cnt=0,cnt2=0;
  char str[MXB]={'\0'};
  char str2[MXB]={'\0'};
  static int j,k,l,r,s,dammy,dammy2,dammy3;
  char buf[MXB];
  //  int ss;
  double Nj[MX]={0.0};
  char ctmp,cstr[MXB],cstr2[MXB];
  
  j=1;

  fgets(str,MXB,fp);
  strcpy(name,str);
  //printf("%s",name);
  
  while((fgets(str,MXB,fp)) !=NULL){

    sscanf(str,"%d ,%d ,%d ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%s",
	   &j,&k,&l,&Lr[i],&Ar[i],&Dr[i],&mt[i],&vth[i],&gma[i],&nj[i],&vj[i],
	   &Aj[i],&Kj[i],&Qe[i],&zeta_in[i],buf);

    Nj[i]=nj[i];
    //   printf("nj=%lf \n",nj[i]);
    strcpy(memo[i],buf);
    
    if(j==0){
      *M=cnt2;      // section number;
      break;
    }

    /*
      printf("%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%s\n\n",
      j,k,l,Lr[i],Ar[i],Dr[i],mt[i],vth[i],gma[i],nj[i],vj[i],
      Aj[i],Kj[i],Qe[i],zeta_in[i],buf);
    */
   
    /*for(ss=0;ss<*M;ss++){
      printf("nj=%lf ",nj[ss]);
      }
      printf("\n");
    */


    // Parameters setting
    irf[i]=k, irt[i]=l;
    
    if(Qe[i] != 0){
      idb[k-2]=i+1;
      //      printf("idb=%d\n",idb[0]);
    }

    vt[i]=vth[i]/3.6;

    mm[i]=mt[i]/3600. * Lr[i]/vt[i];

    Am[i]=0.78+9.1/Ar[i]+(4.21+137.0/Ar[i])*gma[i];

    As[k-2][j-1]=1;
    As[l-2][j-1]=-1;

    nj[i]=Nj[i];
    //    printf("nj=%lf ",nj[i]);
   
    cnt2++;
    i++;
  }
  /*
    for(i=0;i<4;i++){
    printf("nj=%lf ",nj[i]);
    }
  */

  
  for(i=0;i<MX;i++){
    As[i][*M]=idb[i];
  }
  
  while((fgets(str,MXB,fp)) !=NULL){


    /*
      
     */
    it=0;j=0;k=0;
    while((cstr[j]=str[it]) != '\0'){

      if(cstr[j] != ' ')j++;
      it++;

      /*
      if(cstr[j] == ' '){
	it++;
	cstr[j]=str[it];
      }
      it++;
      j++;
      */
    }

    it=0,j=0;k=0;
    while((ctmp=cstr[it])!='\0'){
      cstr2[k]=ctmp;
      if(ctmp==','){
	cstr2[k]='\0';
	ida[j]=atoi(cstr2);
	j++;
	k=-1;
      }
      it++;
      k++;
    }
    
  
    //  sscanf(str,"%d ,%d ,%d ,%d ,%d",&ida[0],&ida[1],&ida[2],&ida[3],&ida[4]);

    /*
    if(ida[0]==0){
      *N=cnt;      // period number;
      // printf("%d\n",n);
      break;
    }
    */
    /*
      for(it=0;it<5;it++)printf("%d ",ida[it]);
      printf("\n");
    */

    for(it=1;it<*M;it++){
      if(ida[it]>0){
	Bs[ida[0]-1][ida[it]-1]=1.;
      }else{
	Bs[ida[0]-1][-ida[it]-1]=-1.;
      }
    }
    
    cnt++;
    i++;
  }
  *N=cnt-1;


  for(i=0;i<*N;i++){
    for(j=0;j<*M;j++){
      Bs[i+*N][j]=Bs[i][j];   
      //     printf("%lf ",Bs[i][j]);
    }
    //   printf("\n");
  }
  //   printf("M=%d\n",*M);

  return 0;
}
