#include <stdio.h>
#include <stdlib.h>

long power(long x, long y) {
  /* Compute x^y, using recursion */
  if (y == 0) {
      return 1;
  }
  return x*power(x, y-1);
}

int main(void) {
  /* Loop to read a line from stdin using getline, of format x^y
   * print out the result. Repeat process until EOF
   *
   * If format of the line is not correct, print error msg to stderr,
   * ignore the input, and read another line.
   * Stricktly require "number^number\n" for input strings. 
   */
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *line2 = NULL;
  char *line3 = NULL;
  while ((read = getline(&line, &len, stdin)) != -1) {
      long int n1 = strtol(line, &line2, 10);
      if (line2 == line) {
         fprintf(stderr, "No numbers have been found!\n");
         continue;
      }
      if (*line2 == '\0') {
          fprintf(stderr, "Only 1 number has been detected!\n");
          continue;
      }
      if (*line2 != '^') {
          fprintf(stderr, "No exponent sign detected!\n");
          continue;
      }
      long int n2 = strtol(line2+1, &line3, 10);
      if (line3 == line2+1) {
         fprintf(stderr, "No numbers have been found!\n");
         continue;
      }
      if (*line3 != '\n') {
          fprintf(stderr, "Extra characters has been inputed!\n");
          continue;
      }
      if (n2 < 0) {
          printf("%d\n", 0);
          continue;
      }
      long int ans = power(n1, n2);
      printf("%ld\n", ans);
  }
  if (line != NULL) {
      free(line);
      line = NULL;
      line2 = NULL;
      line3 = NULL;
  }
  
  return EXIT_SUCCESS;
}
