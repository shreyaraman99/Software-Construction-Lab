#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(char* from, char* to) {
  size_t fromLength = strlen(from);
  while(1) {
    char ch = getchar();
    if(ferror(stdin)) {
      fprintf(stderr, "Error in input string!");
      exit(1);
    }
    if (feof(stdin))
      break;

    int p = 0;
    for (size_t i; i < fromLength; i++) {
      if(from[i] == ch) {
	putchar(to[i]);
	p = 1;
      }
    }
    if (p == 0)
      putchar(ch);

    if(ferror(stdout)) {
      fprintf(stderr, "Error in output string!");
      exit(1);
    }
  }
  return 0;
}

 
int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect number of arguments! Input 2 arguments!");
    exit(1);
  }

  char* from = argv[1];
  char* to = argv[2];

  if (strlen(from) != strlen(to)) {
    fprintf(stderr, "Inputs from and to must be the same legnth!");
    exit(1);
  }

  size_t i, j;
  for (i = 0; i < strlen(from); i++) {
    for (j = i+1; j < strlen(from); j++) {
      if (from[i] == from[j]) {
	fprintf(stderr, "The from input should not include any duplicate bytes!");
	exit(1);
      }
    }
  }

 return func(argv[1], argv[2]);
}
