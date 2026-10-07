#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;
  int* numbers;
  int sum = 0;

  printf("Enter number of elements: ");

  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  numbers = malloc(n * sizeof(int));

  if (numbers == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);

  for (int i = 0; i < n; i++) {
    if (scanf("%d", &numbers[i]) != 1) {
      printf("Invalid input.\n");
      free(numbers);
      return 1;
    }

    sum += numbers[i];
  }

  printf("Sum = %d\n", sum);
  printf("Average = %.2f\n", (float)sum / n);

  free(numbers);

  return 0;
}