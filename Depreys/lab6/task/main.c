#include <stdio.h>
#include <stdlib.h>

int* rand_nums_setup(int Xmin, int Xmax, int NumRandDat){
    int* nums_array = calloc(NumRandDat, sizeof(int));
    for (int i = 0; i < NumRandDat; i++)
    {
        nums_array[i] = Xmin + rand() % (Xmax - Xmin + 1);
    }
    return nums_array;
}

extern void asm_function(int* left_borders, int* rand_nums, int* result, int NumRandDat, int Nint, int* interval_sum);

int main(){
    int NumRanDat = 0;
    int Xmin = 0;
    int Xmax = 0;
    int Nint = 0;
    int* left_borders;
    int* interval_sum;

    printf("Enter NumRanDat, Xmin, Xmax, Nint\n");
    scanf("%d %d %d %d", &NumRanDat, &Xmin, &Xmax, &Nint);

    if(NumRanDat < 0 || NumRanDat > (1024*16)){
        printf("Wrong number of random numbers\n");
        return 0;
    }

    if(Nint < 0 || Nint > 24){
        printf("Wrong number of intervals\n");
        return 0;
    }

    if(Xmin > Xmax){
        printf("Wrong range of random numbers\n");
        return 0;
    }

    left_borders = (int*)calloc(Nint, sizeof(int));
    interval_sum = (int*)calloc(Nint, sizeof(int));
    printf("Enter left borders\n");
    for (int i = 0; i < Nint; i++)
    {
        scanf("%d", left_borders + i);
        if (left_borders[i] < Xmin || left_borders[i] > Xmax)
        {
            printf("Wrong interval boundary\n");
            free(left_borders);
            return 0;
        }
        
    }


    int* rand_nums = rand_nums_setup(Xmin,Xmax,NumRanDat);
    printf("Array of random numbers\n[");
    for (int i = 0; i < NumRanDat - 1; i++)
    {
        printf("%d, ", rand_nums[i]);
    }
    printf("%d]\n", rand_nums[NumRanDat - 1]);
    
    int* result = calloc(Nint, sizeof(int));

    asm_function(left_borders, rand_nums, result, NumRanDat, Nint, interval_sum);

    for (int i = 0; i < Nint; i++)
    {
        printf("Interval num) %d     Left border) %d     Nums in interval) %d     Sum in interval) %d\n",i + 1, left_borders[i], result[i], interval_sum[i]);
    }

    FILE *file = fopen("result.txt","w");
    for (int i = 0; i < Nint; i++)
    {
        fprintf(file, "Interval num) %d     Left border) %d     Nums in interval) %d     Sum in interval) %d\n",i + 1, left_borders[i], result[i], interval_sum[i]);
    }
    fclose(file);


    free(result);
    free(interval_sum);
    free(left_borders);
    free(rand_nums);
}