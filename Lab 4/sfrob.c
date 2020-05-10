#include <stdio.h>
#include <stdlib.h>

int frobcmp (const char* a, const char* b) {
  for (;; a++, b++) {
    if (*a == ' ' && *b == ' ')
      return 0;
    else if (*a == ' ' || (*a ^ 42) < (*b ^ 42))
      return -1;
    else if (*b == ' ' || (*b ^ 42) < (*a ^ 42))
      return 1;
  }
}

int cmp(const void* a, const void* b) {
  return frobcmp(*(const char**)a, *(const char**)b);
}

void fileError() {
  if(ferror(stdin)) {
    fprintf(stderr, "Cannot read file!");
    exit(1);
  }
}

void memoryError(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "Error in reallocating memory!");
    exit(1);
  }
}

int main(void) {
  char* word = (char*)malloc(sizeof(char));
  char** words = (char**)malloc(sizeof(char*));

  int countL = 0;
  int countW = 0;

  char current = getchar();
  fileError();
  char nextChar = getchar();
  fileError();

  while(!ferror(stdin) && current != EOF) {
    word[countL] = current;
    char* temp = realloc(word, (countL + 2)*sizeof(char));
    if(temp != NULL) {
      word = temp;
    }
    else {
      memoryError(word);
    }

    if(current == ' ') {
      words[countW] = word;
      char** temp2 = realloc(words, (countW + 2)*sizeof(char*));
      if(temp2 != NULL) {
	words = temp2;
	countW++;
	word = NULL;
	word = (char*)malloc(sizeof(char));
	countL = -1;
      }
      else {
	memoryError(words);
      }
    }

    if (nextChar == EOF && current == ' ') {
	break;
    }

    else if (current ==  ' ' && nextChar == ' ') {
      while(current == ' ') {
	current = getchar();
	fileError();
      }
      nextChar = getchar();
      fileError();
      countL++;
      continue;
    }
    else if (nextChar == EOF) {
      current = ' ';
      countL++;
      continue;
    }
    current = nextChar;
    nextChar = getchar();
    countL++;
    fileError();
  }

  qsort(words, countW, sizeof(char*), cmp);

  for(size_t i = 0; i < countW; i++) {
    for(size_t j = 0; ; j++) {
      if(putchar(words[i][j]) == EOF) {
	fprintf(stderr, "Error occured for  writing character!");
	exit(1);
      }
      if(words[i][j] == ' ') {
	break;
      }
    }
  }
  for(size_t k = 0; k < countW; k++) {
    free(words[k]);
  }
  free(words);
  exit(0);
}
