

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000


int main(int argc, char *argv[]){

  double score[N]={0.};
  double dammy;
  int i,j;
  clock_t time_start,time_end;
    
  int rnd;
  double rnd2;
  
  unsigned int t=(unsigned int)time(NULL);
  //  unsigned int t=N;
  srand(t);

  printf("------------------------\n");
  printf("Before sorting\n");
  printf("\n");
  
  for(j=0;j<N;j++){

    // rand(); rand(); rand(); rand();
    
    //    rnd=rand();
    rnd2=((double)rand()+1.0)/((double)RAND_MAX+2.0)*100;

    score[j]=rnd2;
    printf("score[%3d]=%6.2lf\n",j,score[j]);
    //    printf("%lf\n",rnd2);
  }

  /*
  for(i=0;i<N;i++){
    printf("score[%d]=",i);
    scanf("%lf",&score[i]);
  }
  */

  time_start=clock()/CLOCKS_PER_SEC;
  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(score[j+1]>score[j]){
	dammy=score[j+1];
	score[j+1]=score[j];
	score[j]=dammy;
      }//if
    }
  }
  time_end=clock()/CLOCKS_PER_SEC;
  
  printf("------------------------\n");
  printf("After sorting\n");
  printf("\n");
  for(i=0;i<N;i++){
    printf("score[%3d]=%6.2lf\n",i,score[i]);
  }
  printf("elapse time=%ld [s]\n",time_end-time_start);
    
  return EXIT_SUCCESS;
}
