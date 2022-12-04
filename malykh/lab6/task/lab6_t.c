#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void getSpread_t(int *rand_arr, int *left_borders, int NumRanDat, int NInt, int *res, int *max);

int *genRandomArray(int length, int x_min, int x_max)
{
    srand(time(0));
    int *arr = (int *)calloc(length, sizeof(int));
    for (int i = 0; i < length; ++i)
    {
        arr[i] = x_min + rand() % (x_max - x_min + 1);
    }
    return arr;
}

int main()
{
    int NumRanDat = 0, x_min = 0, x_max = 0, NInt = 0;
    printf("Enter NumRanDat: ");
    scanf("%d", &NumRanDat);
    printf("Enter x_min, x_range: ");
    scanf("%d %d", &x_min, &x_max);
    printf("Enter NInt: ");
    scanf("%d", &NInt);

    if (NumRanDat < (2 << 14) && x_max > x_min && NInt < 24)
    {

        int *LGrInt = (int *)calloc(NInt, sizeof(int));
        if (LGrInt)
        {
            printf("Enter left borders: ");
            for (int i = 0; i < NInt; i++)
            {
                scanf("%d", LGrInt + i);
                if (LGrInt[i] < x_min || LGrInt[i] > x_max)
                {
                    printf("Incorrect value of border!\n");
                    free(LGrInt);
                    return 0;
                }
            }

            int *rand_arr = genRandomArray(NumRanDat, x_min, x_max);
            printf("Array of random nums: ");
            for (int i = 0; i < NumRanDat; ++i)
            {
                printf("%d ", *(rand_arr + i));
            }
            putchar('\n');

            int *res = (int *)calloc(NInt, sizeof(int));
            int *max = (int *)calloc(NInt, sizeof(int));
            for (int i = 0; i < NInt; i++)
            {
                max[i] = x_min;
            }

            getSpread_t(rand_arr, LGrInt, NumRanDat, NInt, res, max);
            printf("Results: ");
            for (int i = 0; i < NInt; i++)
            {
                printf("%d ", res[i]);
            }
            putchar('\n');
            printf("Max value in intervals: ");
            for (int i = 0; i < NInt; i++)
            {
                printf("%d ", max[i]);
            }
            putchar('\n');

            FILE *file;
            file = fopen("results.txt", "w");
            for (int i = 0; i < NInt; i++)
            {
                fprintf(file, "%d %d %d\n", i + 1, LGrInt[i], res[i]);
            }
            fclose(file);
            free(res);
            free(rand_arr);
            free(LGrInt);
        }
    }
    else
    {
        printf("The values you entered are incorrect!\n");
    }

    return 0;
}