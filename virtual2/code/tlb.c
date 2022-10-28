#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define PAGESIZE (1 << 12) // 4KB

int main(int argc, char** argv)
{
  struct timeval tv;
  int num_page = atoi(argv[1]), num_trial = atoi(argv[2]);
  int jump = PAGESIZE / sizeof(int);
  int a[num_page * jump];
  unsigned int before, after, total = 0;
  volatile int j;
  
  for (j = 0; j < num_trial; ++j) {
    if (gettimeofday(&tv, 0) == 0) {
      before = tv.tv_usec;
    }

    for (int i = 0; i < num_page * jump; i += jump) {
      a[i] += 1;
    }

    if (gettimeofday(&tv, 0) == 0) {
      after = tv.tv_usec;
    }
    total += (after - before); 
  }
  printf("%lf\n", (float)total / num_trial);

  return 0;
}