#include <iostream>
#include <windows.h>
#include <fstream>
#include <random>

using namespace std;

extern "C" void(func1(int* arr, int NumRanDat, int* res, int Xmin));
extern "C" void(func2(int* res, int* LGrInt, int* result, int interval, int NInt, int Xmin, int* prov_mas));

int cmp(const void* num1, const void* num2) {
    int* first = (int*)num1;
    int* second = (int*)num2;
    if (*first > *second)
        return 1;
    else if (*first < *second)
        return -1;
    else
        return 0;
}

void print_arr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int NumRanDat, Xmin, Xmax, NInt;
    printf("Enter NumRanDat, Xmin, Xmax, NInt:");
    scanf_s("%d %d %d %d", &NumRanDat, &Xmin, &Xmax, &NInt);

    if (NumRanDat < 0 || NumRanDat>16384) {
        printf("Wrong NumRanDat");
        return 0;
    }
    if (Xmin > Xmax) {
        printf("Wrong Xmin and Xmax");
        return 0;
    }
    if (NInt > 24 || NInt < 0) {
        printf("Wrong NInt");
        return 0;
    }

    printf("Enter left borders: ");
    int* LGrInt = new int[NInt];
    for (int i = 0; i < NInt; i++)
    {
        cin >> LGrInt[i];
    }
    qsort(LGrInt, NInt, sizeof(int), cmp);
    if (LGrInt[0] < Xmin || (LGrInt[NInt - 1] > Xmax && NInt > 0)) {
        printf("Wrong border");
        delete[] LGrInt;
        return 0;
    }

    int* arr = new int[NumRanDat];
    srand(time(NULL));
    for (int i = 0; i < NumRanDat; i++)
        arr[i] = Xmin + rand() % (Xmax - Xmin + 1);

    printf("Random numbers array: \n");
    print_arr(arr, NumRanDat);
    int interval = Xmax - Xmin + 1;
    int* res = new int[interval];
    for (int i = 0; i < interval; i++)
    {
        res[i] = 0;
    }
    func1(arr, NumRanDat, res, Xmin);
    print_arr(res, interval);

    int* result = new int[NInt];
    int* prov_mas = new int[NInt];
    for (int i = 0; i < NInt; i++)
    {
        result[i] = 0;
        prov_mas[i] = 0;
    }
    func2(res, LGrInt, result, interval, NInt, Xmin, prov_mas);
    printf("result: \n");
    ofstream out;
    out.open("res.txt");
    for (int i = 0; i < NInt; i++) {
        if (prov_mas[i] == 0) {
            cout << LGrInt[i] << ": no value" << '\n';
            out << LGrInt[i] << ": no value" << '\n';
        }
        else {
            cout << LGrInt[i] << ": " << result[i] << "\n";
            out << LGrInt[i] << " - " << result[i] << "\n";
        }
    }
    out.close();
    delete[] arr;
    delete[]LGrInt;
    delete[]res;
    delete[]result;
    return 0;



}