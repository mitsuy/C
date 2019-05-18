#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;

  fp=fopen("line_break.dat","w");

  fprintf(fp,"carriage return *\r*");
  fprintf(fp,"line feed *\n*");
  fprintf(fp,"carriage return + line feed *\r\n*");
  fprintf(fp,"EOF");

  fclose(fp);


  return EXIT_SUCCESS;
}
