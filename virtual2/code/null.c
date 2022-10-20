#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  int *null_int = NULL;

  printf("This crashes: %d\n", *null_int);
  return 0;
}
