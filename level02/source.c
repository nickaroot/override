#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)

{
  int passwords_cmp;
  size_t rd;
  long i;
  char e_password [14];
  char password [6];
  char username [12];
  int iRd;
  FILE *fd;
  char *zero;
  
  zero = (char *)username;
  for (i = 12; i != 0; i = i + -1) {
    *zero = 0;
    zero = zero + 1;
  }
  *(char *)zero = 0;
  zero = password;
  for (i = 5; i != 0; i = i + -1) {
    *zero = 0;
    zero = zero + 1;
  }
  *(char *)zero = 0;
  zero = e_password;
  for (i = 12; i != 0; i = i + -1) {
    *zero = 0;
    zero = zero + 1;
  }
  *(char *)zero = 0;
  fd = fopen("/home/users/level03/.pass","r");
  if (fd == (FILE *)0) {
    fwrite("ERROR: failed to open password file\n",1,36,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  rd = fread(password,1,41,fd);
  iRd = (int)rd;
  rd = strcspn((char *)password,"\n");
  *(char *)((long)password + rd) = 0;
  if (iRd != 41) {
    fwrite("ERROR: failed to read password file\n",1,36,stderr);
    fwrite("ERROR: failed to read password file\n",1,36,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  fclose(fd);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(username,100,stdin);
  rd = strcspn(username,"\n");
  username[rd] = '\0';
  printf("--[ Password: ");
  fgets((char *)e_password,100,stdin);
  rd = strcspn((char *)e_password,"\n");
  *(char *)((long)e_password + rd) = 0;
  puts("*****************************************");
  passwords_cmp = strncmp((char *)password,(char *)e_password,41);
  if (passwords_cmp == 0) {
    printf("Greetings, %s!\n",username);
    system("/bin/sh");
    return 0;
  }
  printf("%s",username);
  puts(" does not have access!");
                    /* WARNING: Subroutine does not return */
  exit(1);
}
