#include <stdio.h>
#include <stdlib.h>


int main(){

  char str[20]="1,2,3,4,5";
  char c,tmp[20]={'\0'};
  int data[20]={0.};
  int i=0,j=0,k=0;

  while((tmp[i]=str[j]) != '\0'){
    //tmp[i]=c;
    if(tmp[i]==','){
      tmp[i]='\0';
      data[k]=atoi(tmp);
      printf("%d",data[k]);
      i=-1;
      k++;
    }

    i++;
    j++;
  }
  printf("\n");




  return 0;
}
