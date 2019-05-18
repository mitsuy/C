#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 500
#define M 20
int main(int argc,char *argv[])
{
  FILE *fp;
  static int i,it,lt,ida[M],idb[M];
  int cnt=0,cnt2=0;
  char str[N]={'\0'};
  char str2[N]={'\0'};
  char test,test2[N]={'\0'},test3[N]={'0.'};
  static  char name[N];

  static int j,k,l,r,s,dammy,dammy2,dammy3;
  static double Lr[N],Ar[N],Dr[N],Am[M];
  static double mt[N],mm[M],vt[M],vth[N],gm[N],nj[N];
  static double vj[N],Aj[N],Kj[N],Qe[N],Zr[N];
  char buf[N];
  static double irf[M],irt[M];
  static double As[M][M],Bs[M][M];

  int m,n;

  j=1;
  if((fp=fopen(argv[1],"r"))==NULL){
    printf("Can't find such as that file.\n");
    exit(1);
  }

  fgets(str,N,fp);
  strcpy(name,str);
  printf("%s",name);
  
  while((fgets(str,N,fp)) !=NULL){

    sscanf(str,"%d ,%d ,%d ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%s",
	   &j,&k,&l,&Lr[i],&Ar[i],&Dr[i],&mt[i],&vth[i],&gm[i],&nj[i],&vj[i],
	   &Aj[i],&Kj[i],&Qe[i],&Zr[i],buf);


    
    if(j==0){
      m=cnt2;      // period number;
      break;
    }
    /*
    printf("%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%s\n\n",
	   j,k,l,Lr[i],Ar[i],Dr[i],mt[i],vth[i],gm[i],nj[i],vj[i],
	   Aj[i],Kj[i],Qe[i],Zr[i],buf);
    */

    // Parameters setting
    irf[i]=k, irt[i]=l;
    
    if(Qe[i] != 0){
      idb[k-2]=i+1;
      //      printf("idb=%d\n",idb[0]);
    }
    
    vt[i]=vth[i]/3.6;
    mm[i]=mt[i]/3600. * Lr[i]/vt[i];
    
    Am[i]=0.78+9.1/Ar[i]+(4.21+137.0/Ar[i])*gm[i];
    As[k-2][j-1]=1;
    As[l-2][j-1]=-1;
    
    cnt2++;
    i++;
  }


  //  j=dammy,k=dammy2,l=dammy3;

  
  for(i=0;i<M;i++){
    As[i][m]=idb[i];
  }

  i=0;
  while((fgets(str,N,fp)) !=NULL){


    it=0;j=0;k=0;
    while((test2[j]=str[it]) != '\0'){
      printf("%c",test2[j]);
      if(test2[j] != ' ')j++;
      it++;

    }

    it=0,j=0;k=0;
    while((test=test2[it])!='\0'){
      test3[k]=test;
      if(test==','){
	test3[k]='\0';
	ida[j]=atoi(test3);
	j++;
	k=-1;
      }
      it++;
      k++;
    }
 
    //  sscanf(str,"%d ,%d ,%d ,%d ,%d",&idb[0],&idb[1],&idb[2],&idb[3],&idb[4]);
	    
    /*
    if(ida[0]==0){
      n=cnt;      // period number;
      // printf("%d\n",n);
      break;
    }
    */

    /*
    for(it=0;it<5;it++)printf("%d ",ida[it]);
    printf("\n");
    */


    
    for(it=1;it<m;it++){
      if(ida[it]>0){
	Bs[ida[0]-1][ida[it]-1]=1.;
      }else{
	Bs[ida[0]-1][-ida[it]-1]=-1.;
      }
    }

    cnt++;
    i++;
  }
  /// Node number definition
  n=cnt-1;
  //  printf("%d\n",n-1);
  

  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      printf("%lf ",Bs[i][j]);
    }
    printf("\n");
  }


  
  //printf("%d %d\n",m,n);
  fclose(fp);

  return EXIT_SUCCESS;
}
