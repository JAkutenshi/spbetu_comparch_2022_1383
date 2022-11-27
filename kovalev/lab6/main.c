#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void funcAsm1(int *, int64_t *, int, int, int);
void funcAsm2(int64_t *, int *, int *, int, int, int, int);

static int cmp(const void *first, const void *second) {
  int *left = (int *)first;
  int *right = (int *)second;

  if (*left > *right) {
    return 1;
  }
  if (*left < *right) {
    return -1;
  }
  return 0;
}

int main(void) {
  int NumRanDat, Xmin, Xmax, NInt;

  if (isatty(0)) {
    printf("Введите NumRanDat, Xmin, Xmax, NInt: ");
  }
  scanf("%d %d %d %d", &NumRanDat, &Xmin, &Xmax, &NInt);

  if (NumRanDat > 16384 || NumRanDat < 0) {
    fprintf(stderr, "Error: wrong NumRanDat");
    exit(EXIT_FAILURE);
  }

  if (Xmin >= Xmax) {
    fprintf(stderr, "Error: Xmin > Xmax");
    exit(EXIT_FAILURE);
  }

  if (NInt > 24 || NInt < 0) {
    fprintf(stderr, "Error: wrong NInt");
    exit(EXIT_FAILURE);
  }

  if (isatty(0)) {
    printf("Введите массив границ: ");
  }
  int *borders = (int *)calloc(NInt, sizeof(int));
  for (int i = 0; i < NInt; ++i) {
    scanf("%d", &borders[i]);
  }
  qsort(borders, NInt, sizeof(int), cmp);

  if (borders[0] < Xmin || borders[NInt - 1] > Xmax + 1) {
    fprintf(stderr,
            "Error: wrong borders, Xmin = %d, borders[0] = %d, Xmax = %d, "
            "borders[NInt] = %d\n",
            Xmin, borders[0], Xmax, borders[NInt - 1]);

    free(borders);

    exit(EXIT_FAILURE);
  }

  int *arr = (int *)calloc(NumRanDat, sizeof(int));
  dnk_randomize();
  for (int i = 0; i < NumRanDat; ++i) {
    arr[i] = Xmin + (int)(dnk_random() * (Xmax - Xmin + 1));
    /* arr[i] = Xmin + (int)(dnk_normal(0.0, 1.0) * (Xmax - Xmin) / 2); */
  }

  size_t tmpLen = Xmax - Xmin + 1;
  int64_t *tmp = (int64_t *)calloc(tmpLen, sizeof(int64_t));

  funcAsm1(arr, tmp, tmpLen, NumRanDat, Xmin);

  free(arr);

  for (size_t i = 0; i < tmpLen; ++i) {
    printf("%3ld ", tmp[i]);
  }
  printf("\n");

  int *result = (int *)calloc(NInt, sizeof(int));

  funcAsm2(tmp, borders, result, tmpLen, NInt, Xmin, Xmax);

  free(tmp);

  FILE *f = fopen("result.txt", "w");

  fprintf(f, "------------------------------------\n");
  for (int i = 0; i < NInt - 1; ++i) {
    fprintf(f, " %4d | %10d | %14d \n", i + 1, borders[i], result[i]);
    fprintf(f, "------------------------------------\n");
  }

  fclose(f);

  free(borders);
  free(result);
  return EXIT_SUCCESS;
}
