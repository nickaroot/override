#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  unsigned int mask;
  char *transform;
  char input [100];
  unsigned int i;
  char trans_char;
  
  i = 0;
  fgets((char *)input,100,stdin);
  i = 0;
  do {
    mask = 0xffffffff;
    transform = input;
    do {
      if (mask == 0) break;
      mask = mask - 1;
      trans_char = *transform;
      transform = transform + (unsigned int)1;
    } while (trans_char != 0);
    if (~mask - 1 <= i) {
      printf("%s", (char *)input);
      exit(0);
    }
    if (('@' < (char)input[i]) && ((char)input[i] < '[')) {
      input[i] = input[i] ^ 32;
    }
    i = i + 1;
  } while(1);

  return (1);
}
