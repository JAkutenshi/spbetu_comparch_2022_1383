#include <iostream>
#include <fstream>
#include <random>

extern "C" void inter(int* arr, int len, int* LGrInt, int NInt, int* res, int* count_even);

int main() {
	int NumRanDat;

	int NInt;
	int Xmin;
	int Xmax;
	puts("Total amount of numbers");
	std::cin >> NumRanDat;
	int* arr = new int[NumRanDat];
	puts("Min number");
	std::cin >> Xmin;
	puts("Max number");
	std::cin >> Xmax;
	puts("Number of intervals");
	std::cin >> NInt;
	puts("Left borders");
	int* LGrInt = new int[NInt];
	for (int i = 0; i < NInt; i++) {
		std::cin >> LGrInt[i];
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(Xmin, Xmax);

	for (int i = 0; i < NumRanDat; i++) {
		arr[i] = distrib(gen);
	}

	for (int i = 0; i < NumRanDat; i++) {
		printf("%d ", arr[i]);
	}
	puts("");

	int* res = new int[NInt];
	for (int i = 0; i < NInt; i++) {
		res[i] = 0;
	}
	int* count_even = new int[NInt];
;
	for (int i = 0; i < NInt; i++) {
		count_even[i] = 0;
	}

	inter(arr, NumRanDat, LGrInt, NInt, res, count_even);
	
	for (int i = 0; i < NInt; i++) {
		printf("%d ", res[i]);
	}
	puts("\nEven numbers");

	for (int i = 0; i < NInt; i++) {
		printf("%d ", count_even[i]);
	}
	puts("");
}