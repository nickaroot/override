#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char *login,unsigned int pass)
{
  size_t len;
  int result;
  long isTraced;
  int i;
  unsigned int hash;
  
  len = strcspn(login,"\n");
  login[len] = '\0';
  len = strnlen(login,0x20);
  if ((int)len < 6) {
    result = 1;
  }
  else {
    isTraced = ptrace(PTRACE_TRACEME);
    if (isTraced == -1) {
      puts("\x1b[32m.---------------------------.");
      puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
      puts("\x1b[32m\'---------------------------\'");
      result = 1;
    }
    else {
      hash = ((int)login[3] ^ 0x1337U) + 0x5eeded;
      for (i = 0; i < (int)len; i = i + 1) {
        if (login[i] < ' ') {
          return 1;
        }
        hash = hash + ((int)login[i] ^ hash) % 0x539;
      }
      if (pass == hash) {
        result = 0;
      }
      else {
        result = 1;
      }
    }
  }
  return result;
}

int main(int argc,char **argv)

{
  int authResult;
  unsigned int pass;
  char login [32];
  int local_14;

  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(login,0x20,stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  scanf("");
  authResult = auth(login,pass);
  if (authResult == 0) {
    puts("Authenticated!");
    system("/bin/sh");
  }
  return (unsigned int)(authResult != 0);
}
