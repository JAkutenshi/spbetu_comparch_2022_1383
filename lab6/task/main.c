#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp (const void * first, const void * second) {
    int * a = (int *) first;
    int * b = (int *) second;

    if (*a > *b) 
        return 1;
    else if (*a == *b)
        return 0;
    return -1;
}

void print_array (int * array, int n) {
    for (int i = 0; i < n; i ++) {
        printf ("%d ", array[i]);
    }
    printf ("\n");
}

void asmfunc1 (int *, int n, int *, int Min);
void asmfunc2 (int * borders, int * result, int n, int * tmp, int m, int Min);

int main () {
    int NumRanDat, Xmin, Xmax, NInt;

    printf ("Enter NumRanDat, Xmin, Xmax, NInt \n");
    scanf ("%d %d %d %d", &NumRanDat, &Xmin, &Xmax, &NInt);
    
    //check  input
    if (NumRanDat > 16384 || NumRanDat < 0) {
        printf ("Error: NumRanDat in wrong interval\n");
        return 0;
    }
    if (Xmin > Xmax) {
        printf ("Error: Xmin > Xmax \n");
        return 0;
    }
    if (NInt > 24 || NInt < 0) {
        printf ("Error: wrong NInt\n");
        return 0;
    }

    printf ("Enter borders\n");
    int * borders = calloc (NInt, sizeof (int));
    for (int i = 0; i < NInt; i++) {
        scanf ("%d", &borders[i]);
    }
    qsort (borders, NInt, sizeof (int), cmp);
    if (borders[0] < Xmin || (NInt > 0 && borders[NInt - 1] > Xmax)) {
        printf ("Error: wrong border\n");
        free(borders);
        return 0;
    }

    int * array = calloc (NumRanDat, sizeof (int));
    
    srand (time(NULL));
    for (int i = 0; i < NumRanDat; i++) {
        array[i] = Xmin + rand() % (Xmax - Xmin + 1);
    }

    printf ("Array of random numbers:\n");
    print_array (array, NumRanDat);

    int arrange = abs(Xmax - Xmin) + 1;
    int * tmp = calloc (arrange, sizeof (int));
    
    int * result = calloc ((NInt + 1) * 2, sizeof (int));

    asmfunc1 (array, NumRanDat, tmp, -Xmin);
    
    printf ("Intermediate rusult after asmfunc1:\n");
    print_array (tmp, arrange);

    asmfunc2 (borders, result, NInt, tmp, arrange, -Xmin);

    printf ("Result:\n");
    FILE * file = fopen ("result.txt", "w");
    int i = 1;
    int k = 0;
    if (result[0] != -1) {
        printf ("%d %d %d %d\n", 1, Xmin, result[0], result[1]);
        fprintf (file, "%d %d %d %d\n", 1, Xmin, result[0], result[1]);
        k = 1;
    }
    for (int j = 0; j < NInt; j++) {
        printf ("%d %d %d %d\n", j + k + 1, borders[j], result[2 * i], result[2*i + 1]);
        fprintf (file, "%d %d %d %d\n", j + k + 1, borders[j], result[2 * i], result[2 * i + 1]);
        i++;
    }
    fclose(file);
    free (array);
    free(borders);
    free (tmp);
    return 0;
}