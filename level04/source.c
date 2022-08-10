#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <signal.h>

int main(void)
{
  int i;
  char *zero;
  int status;
  char inp [128];
  int w_status;
  int c_status;
  long ptrace_var;
  __pid_t fpid;
  
  fpid = fork();
  zero = inp;
  for (i = 32; i != 0; i = i + -1) {
    zero = zero + (int)4;
    *(char *)zero = 0;
    zero = zero;
  }
  ptrace_var = 0;
  status = 0;
  if (fpid == 0) {
    prctl(1,1);
    ptrace(0,0,0,0);
    puts("Give me some shellcode, k");
    gets(inp);
  }
  else {
    do {
      wait(&status);
      w_status = status;
      if (((status & 127) == 0) || (c_status = status, '\0' < (char)(((char)status & 127) + 1) >> 1)
         ) {
        puts("child is exiting...");
        return 0;
      }
      ptrace_var = ptrace(3,fpid,44,0);
    } while (ptrace_var != 11);
    puts("no exec() for you");
    kill(fpid,9);
  }
  return 0;
}
