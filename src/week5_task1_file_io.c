
/*
 * Name: Pamir Ali
 * Surname: Koç
 * Student ID: 260ADM044
 * Week 5 - Task 1: File I/O
 */

#include <stdio.h>

int main(int argc, char* argv[]) {
  const char* filename = "data.txt";

  if (argc > 1) {
    filename = argv[1];
  }

  printf("Writing lines to %s...\n", filename);

  FILE* fp = fopen(filename, "w");

  if (fp == NULL) {
    perror("Error opening file for writing");
    return 1;
  }

  fprintf(fp, "Hello, file I/O in C!\n");
  fprintf(fp, "This is another line.\n");

  if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
  }

  printf("Reading contents:\n");

  fp = fopen(filename, "r");

  if (fp == NULL) {
    perror("Error opening file for reading");
    return 1;
  }

  char line[256];
  int lines_read = 0;

  while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
    lines_read++;
  }

  if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
  }

  printf("Lines read: %d\n", lines_read);

  return 0;
}
