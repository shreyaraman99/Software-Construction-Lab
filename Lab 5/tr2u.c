#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int func(char* from, char* to) {
  size_t fromLength = strlen(from);
  char ch;
  int count = 0;
  ssize_t r;
  while(1) {
    r = read(STDIN_FILENO, &ch, 1);
    if (r < 0) {
      fprintf(stderr, "Error in input string!");
      exit(1);
    }
    if (r == 0)
      break;

    for (size_t i = 0; i < fromLength; i++) {
      if(from[i] == ch){
	ch = to[i];
      }
    }
    r = write(STDOUT_FILENO, &ch, 1);

    if (r < 0) {
      fprintf(stderr, "Error in output string!");
      exit(1);
    }
    fprintf("%d", count++);
  }
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect number of arguments! Input 2 arguments!");
    exit(1);
  }

  char* from = argv[1];
  char* to = argv[2];

  if(strlen(from) != strlen(to)) {
    fprintf(stderr, "Inputs from and to must be the same length!");
    exit(1);
  }

  size_t i, j;
  for (i = 0; i < strlen(from); i++) {
    for (j = i + 1; j < strlen(from); j++) {
      if (from[i] == from[j]) {
	fprintf(stderr, "The from input should not contain any duplicate bytes!");
	exit(1);
      }
    }
  }

  return func(argv[1], argv[2]);
}
