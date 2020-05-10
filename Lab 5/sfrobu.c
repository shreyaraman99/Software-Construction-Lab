#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int frobcmp (const char* a, const char* b) {
  for (;; a++, b++) {
    if (*a == ' ' && *b == ' ')
      return 0;
    else if (*a == ' ' || (*a^42) < (*b^42))
      return -1;
    else if (*b == ' ' || (*b^42) < (*a^42))
      return 1;
  }
}

int cmp(const void* a, const void* b) {
  return frobcmp(*(const char**)a, *(const char**)b);
}

int frobFlag (char const* a, char const* b) {
  for (;; a++, b++) {
    char au = *a ^ 42;
    char bu = *b ^ 42;
    if(isalpha(au)) au = toupper((unsigned char) au);
    if(isalpha(bu)) bu = toupper((unsigned char) bu);

    if(*a == ' ' && *b == ' ')
      return 0;
    else if (*a == ' ' || au < bu)
      return -1;
    else if (*b == ' ' || bu < au)
      return 1;
  }
}

int cmpFlag(const void* a, const void* b) {
  return frobFlag(*(char const**)a, *(char const**)b);
}

void memError(void* ptr) {
  if (ptr == 0) {
    fprintf(stderr, "Error in creating memory buffer!");
    exit(1);
  }
}


int main(int argc, char* const argv[]) {
  struct stat fileSt;
  if(fstat(0, &fileSt) < 0) {
    write(2, "Error in reading file!", argc);
    exit(1);
  }

  char* f;
  char* curStr;
  char** indexArr;
 
  int ret = 0;
  size_t bsize = 0;
  int reg = 0;
  if(S_ISREG(fileSt.st_mode)) {
    bsize = fileSt.st_size + 1 + 1;
    indexArr = (char**) malloc(bsize * sizeof(char*));
    f = (char*) malloc(bsize * sizeof(char));
    indexArr[0] = f;
    curStr = indexArr[0];
  }
  else {
    curStr = (char*) malloc(sizeof(char));
    indexArr = (char**) malloc(sizeof(char*));
    if (indexArr == NULL || curStr == NULL) {
      write(2, "Error in memory!", ret);
      exit(1);
    }
    reg = 1;
  }

  int cc = 0;
  char ch[2];
  ret = read(0, ch, 1);
  if (ret < 0) {
    write(2, "Error in reading input!", ret);
    exit(1);
  }

  int wi = 0;
  int ai = 0;

  while (ret > 0) {
    curStr[wi++] = ch[0];
    cc++;

    if(cc > bsize - 2 || reg) {
      char* t = realloc(curStr, sizeof(char)*(wi+2));
      if (t != NULL) 
	curStr = t;
      else {
	free(curStr);
	write(2, "Error in allocating memory!", cc);
	exit(1);
      }
    }

    if(ch[0] == ' ') {
      indexArr[ai++] = curStr;
      if (cc > bsize - 2 || reg) {
	char** t = realloc(indexArr, sizeof(char*)*(ai +2));
	if (t != NULL) {
	  curStr = NULL;
	  curStr= (char*)malloc(sizeof(char));
	  indexArr = t;
	  if (curStr == NULL) {
	    write(2, "Error in allocating memory!", cc);
	    exit(1);
	  }
	}
	else{
	  free(indexArr);
	  write(2, "Error in allocating memory!", cc);
	  exit(1);
	}
      }
      else 
	curStr = &f[cc];
      wi = 0;
    }
    ret = read(0, ch + 1, 1);
    if (ret < 0) {
      write(2, "Error in reading input!", ret);
      exit(1);
    }

    if (ret == 0 && ch[0] == ' ')
      break;
    else if (ret == 0) {
      ch[0] = ' ';
      ret = 1;
    }

    else if(ch[1] == ' ' && ch[0] == ' ') {
      while(ch[0] == ' ') {
	ret = read(0, ch, 1);
	if (ret < 0) {
	  write(2, "Error in reading input!", ret);
	  exit(1);
	}
      }
    }
     else ch[0] = ch[1];
  }

   if (argc == 2 && argv[1][1] == 'f')
     qsort(indexArr, ai, sizeof(char*), cmpFlag);
   else 
     qsort(indexArr, ai, sizeof(char*), cmp);

    for (int i = 0; i < ai; i++) {
      for (int j = 0; ; j++) {
	if (write(1, indexArr[i] + j, 1) <= 0) {
	  write(2, "Error in writing output!", ai);
	  exit(1);
	}
	if(indexArr[i][j] == ' ')
	  break;
      }
    }

    for (int i = 0; i < ai; i++) {
      free (indexArr[i]);
    }
    free(indexArr);
    exit(0);
  }
	  



