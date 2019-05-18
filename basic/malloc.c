#include <stdio.h>
#include <stdlib.h>

int main()
{

  int i;
  int *h;

  h=(int *)malloc(sizeof(int)*(10+2));

  
  if(h==NULL)exit(0);
  
  for(i=0;i<10;i++){
    h[i]=i;
  }
  h[0]=h[9];



  for(i=1;i<10;i++){
    h[i+1]=h[i]+h[i-1];
    printf("%d\n",h[i]);
  }

  
  free(h);
  
  return 0;
}
