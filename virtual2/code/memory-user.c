#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
  if (argc != 2) {
    fprintf(stderr, "usage: ./memory-user <n megabytes> <time>");
    exit(1);
  }  

  size_t megabytes = atoi(argv[1]);
  if (megabytes >= ((size_t)1 << 44)) {
    fprintf(stderr, "too big a number to be represented");
  }

  megabytes <<= 20;
  int* arr = (int*)malloc(megabytes);
  return 0;
}
