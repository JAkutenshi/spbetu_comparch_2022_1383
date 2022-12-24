#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

extern "C" void counter(int* array, int array_size, int* LGrInt, int NInt, int* result_array);

int main()
{
	srand(time(0));
	int NumRanDat, Xmin, Xmax, NInt;
	cin >> NumRanDat >> Xmin >> Xmax >> NInt;
	int* arr = new int[NumRanDat];
	for (int i = 0; i < NumRanDat; ++i)
	{
		arr[i] = Xmin + rand() % abs(Xmax - Xmin+1);
	}
	
	int* LGrInt = new int[NInt];
	LGrInt[0] = Xmin;
	for (int i = 0; i < NInt; ++i)
	{
		cin >> LGrInt[i];
	}
	int* ans = new int[NInt] {0};
	counter(arr, NumRanDat, LGrInt, NInt, ans);
	//freopen("out.txt", "w", stdout);
	for (int i = 0; i < NInt; ++i)
	{
		cout << i + 1 << "	" << LGrInt[i] << "	" << ans[i] << endl;;
	}
	for (int i = 0; i < NumRanDat; ++i)
	{
		cout << arr[i] << " ";
	}
	return 0;
}
