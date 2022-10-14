#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/uio.h>

int main(int argc, char *argv[])
{
  int pid;

  /* Q1 */
  // int x = 0;

  /* Q2 */
  // close(STDOUT_FILENO);
  // open("./output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  // char *myargs[3];
  // myargs[0] = "echo";
  // myargs[2] = NULL;

  /* Q4 */
  // char *myargs[3];
  // myargs[0] = "/bin/ls";
  // myargs[1] = "./";
  // myargs[2] = NULL;

  /* Q5 */
  // int wait_ret;

  /* Q1 ~ 7 */
  // if ((pid = fork()) < 0) {
  //   fprintf(stderr, "fork failed");
  //   exit(1);
  // }

  // if (pid == 0) {
    // child

    /* Q1 */
    // printf("child has x previously: %d\n", x);
    // x = 100;
    // printf("child has x: %d\n", x);

    /* Q2 */
    // myargs[1] = "child!";
    // execvp(myargs[0], myargs);

    /* Q3 */
    // printf("hello!\n");

    /* Q4 */
    // execl(myargs[0], "./"); // l: listing arguments explictly(not as a given array of strings)
    // execle(myargs[0], "./"); // e: specifies the environment of the executed process
    // execlp(myargs[0], "./"); 
    // p: duplicate the actions of the shell in searching for an executable file, if
    // the specified file name does not contian a slash "/" character
    // execv(myargs[0], myargs); // v: listing arguments as a given array of strings
    // execvp(myargs[0], myargs);

    /* Q5 */
    // wait_ret = wait(NULL);
    // printf("child - wait_ret: %d\n", wait_ret);

    /* Q7 */
  //   close(STDOUT_FILENO);
  //   printf("child!!\n");

  //   exit(0);
  // } else {
    // parent

    /* Q1 */
    // printf("parent has x previously: %d\n", x);
    // x = 200;
    // printf("parent has x now: %d\n", x);
    
    /* Q2 */
    // myargs[1] = "parent!";
    // execvp(myargs[0], myargs);

    /* Q3 */
    // sleep(1); 
    // printf("goodbye!\n");

    /* Q5 */
    // wait_ret = wait(NULL);
    // printf("parent - wait_ret: %d / child pid: %d\n", wait_ret, pid);

    /* Q6 */
    // wait_ret = waitpid(pid, NULL, 0);
    // printf("parent - wait_ret: %d / child pid: %d\n", wait_ret, pid);
    
  // }

  /* Q8 */
  int pid2;
  int p[2];
  pipe(p); // p[0] => output(to be read) / p[1] => input(to be written)

  pid = fork();
  pid2;

  if (pid < 0) {
    fprintf(stderr, "fork failed");
    exit(1);
  }

  if (pid > 0) {
    // parent process
    if ((pid2 = fork()) < 0) {
      fprintf(stderr, "fork failed");
      exit(1);
    }

    if (pid2 == 0) {
      
      // first, wait for the pid
      waitpid(pid, NULL, 0);

      char buf[16];
      if (read(p[0], buf, 16) < 0) {
        fprintf(stderr, "read error");
        exit(1);
      }
      printf("response from pid2 - reading: %s\n", buf);
      exit(0);
    }
  } else {
    // child process
    // write to the pipe
    char *buf = "this is pid1 \n"; 
    write(p[1], buf, 16);
    exit(0);

  }
  return 0;
}
