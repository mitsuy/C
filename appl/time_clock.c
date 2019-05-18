#include <stdio.h>
#include <time.h>


int main()
{
  static char *week[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  time_t now, prev;
  struct tm *tm_now;

  printf("\033[2J");
  
  prev=-1;
  

  now=time(NULL);
  prev=now;
  tm_now=localtime(&now);
  
  printf("\033[9;30H");
  //  printf("Date\n");
  printf("%4d, %2d-%2d (%s)\n",tm_now->tm_year+1900,tm_now->tm_mon+1,tm_now->tm_mday
	 ,week[tm_now->tm_wday]);

  //  printf("Time h:m:s\n");
  
  for(;;){

    now=time(NULL);
    if(prev==now)
      continue;
    prev=now;
    tm_now=localtime(&now);
    printf("\033[10;30H");
    printf("%2d:%2d:%2d\n", tm_now->tm_hour,tm_now->tm_min,tm_now->tm_sec);

  }


  return 0;
  
}
