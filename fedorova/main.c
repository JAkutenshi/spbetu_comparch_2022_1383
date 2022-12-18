#include <stdio.h>
#include <stdlib.h>
/*
 1. Длина массива псевдослучайных целыхчисел - NumRanDat (<= 16K, К=1024)
2. Диапазон изменения массива псевдослучайных целых чисел [Xmin, Xmax] , значения
могут быть биполярные;
13
3. Количество интервалов, на которые разбивается диапазон
 изменения
 массива
псевдослучайных целых чисел - NInt ( <=24 )
4. Массив левых границ интервалов разбиения LGrInt (должны принадлежать интервалу
[Xmin, Xmax]).

1. Текстовый файл, строка которого содержит:
- номер интервала,
- левую границу интервала,
- количество псевдослучайных чисел, попавших в интервал.
Количество строк равно числу интервалов разбиения.
2. График, отражающий распределение чисел по интервалам.
(необязательный результат)

*/
int modul(int a) {
  return a > 0 ? a : -a;
}


void module(int*, int*, int*, int, int);

int * sort(int * a, int size) {
  for(int i = 0; i < size - 1; i ++) {
    for(int j = i + 1; j < size; j++) {
      if(a[i] > a[j]) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
      }
    }
  }
}

int main () {

    int NumRanDat, Xmin, Xmax, NInt;

    //                  длинa массива, мин, макс, количество интервалов
    scanf("%d %d %d %d", &NumRanDat, &Xmin, &Xmax, &NInt);

    int* LGrInt = calloc(NInt, sizeof(int));

    //Введ левых границ интервалов
    for (int i = 0; i < NInt; i++){
        scanf("%d", &LGrInt[i]);
    }
    //сортировка пузырьком)))
    sort(LGrInt, NInt);

    int* arr = calloc(NumRanDat, sizeof(int));

    //Заолнение массивa рандомом чисел
    for (int i = 0; i < NumRanDat; i++){
        arr[i] = Xmin + modul(rand() % (Xmax - Xmin));
        printf("%d ", arr[i]);
    }
    printf("\n");

    int* res = calloc(NInt, sizeof(int));
    //result
    module(arr, LGrInt,res, NumRanDat, NInt);

    for (int i = 0; i < NInt ; i++){
        printf("%d\t%d\t%d\n", i, LGrInt[i], res[i]);
    }
    free(LGrInt);
    free(arr);
    free(res);
    return 0;
}
