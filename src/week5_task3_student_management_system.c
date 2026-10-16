
/*
 * Name: Pamir Ali
 * Surname: Koç
 * Student ID: 260ADM044
 * Week 5 - Task 3: Student Management System
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
  char name[50];
  int id;
  float gpa;
} Student;

void read_line(const char* prompt, char* buffer, size_t size) {
  printf("%s", prompt);

  if (fgets(buffer, (int)size, stdin) == NULL) {
    buffer[0] = '\0';
    return;
  }

  buffer[strcspn(buffer, "\n")] = '\0';
}

int load_students(Student arr[], int max) {
  FILE* fp = fopen("students.txt", "r");

  if (fp == NULL) {
    return 0;
  }

  char line[256];
  int count = 0;

  while (count < max && fgets(line, sizeof(line), fp) != NULL) {
    Student s;

    if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
      if (s.name[0] != '\0' && strchr(s.name, ',') == NULL && s.gpa >= 0.0f &&
          s.gpa <= 4.0f) {
        arr[count++] = s;
      }
    }
  }

  fclose(fp);
  return count;
}

int save_students(const Student arr[], int count) {
  FILE* fp = fopen("students.txt", "w");

  if (fp == NULL) {
    perror("Error saving students");
    return -1;
  }

  for (int i = 0; i < count; i++) {
    if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
      fclose(fp);
      return -1;
    }
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return 0;
}

void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-6s %-20s %s\n", "ID", "Name", "GPA");

  for (int i = 0; i < count; i++) {
    printf("%-6d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}

void add_student(Student arr[], int* count) {
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  char name[256];
  char id_text[64];
  char gpa_text[64];
  char* end;
  long id;
  float gpa;

  read_line("Enter name: ", name, sizeof(name));
  read_line("Enter ID: ", id_text, sizeof(id_text));
  read_line("Enter GPA: ", gpa_text, sizeof(gpa_text));

  if (name[0] == '\0' || strchr(name, ',') != NULL) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  id = strtol(id_text, &end, 10);

  if (id_text[0] == '\0' || *end != '\0' || id < 0 || id > 2147483647L) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  gpa = strtof(gpa_text, &end);

  if (gpa_text[0] == '\0' || *end != '\0' || gpa < 0.0f || gpa > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  if (strlen(name) >= sizeof(arr[*count].name)) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  strcpy(arr[*count].name, name);
  arr[*count].id = (int)id;
  arr[*count].gpa = gpa;

  (*count)++;
  printf("Student added successfully!\n");
}

int main(void) {
  Student students[MAX_STUDENTS];
  int count = load_students(students, MAX_STUDENTS);
  char choice[32];

  printf("Loaded %d student(s) from students.txt\n", count);

  for (;;) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");

    read_line("Select an option: ", choice, sizeof(choice));

    if (strcmp(choice, "1") == 0) {
      list_students(students, count);
    } else if (strcmp(choice, "2") == 0) {
      add_student(students, &count);
    } else if (strcmp(choice, "3") == 0 || choice[0] == '\0') {
      if (save_students(students, count) != 0) {
        printf("Error saving data.\n");
        return 1;
      }

      printf("Data saved. Goodbye!\n");
      return 0;
    } else {
      printf("Invalid option. Try again.\n");
    }
  }
}
