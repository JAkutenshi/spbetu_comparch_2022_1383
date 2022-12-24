#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

extern "C" void func(int* array, int arr_size, int* raspr_arr, int Xmin, int* arr2, int* res, int raspr_len, int index);

int main() {
	system("chcp 1251 > nul");
	setlocale(LC_CTYPE, "rus");

	int N, X_min, X_max, N_int;
	cout << "Введите количество чисел:" << endl;
	cin >> N;
	cout << "Введите диапазон генерации:" << endl;
	cin >> X_min >> X_max;
	cout << "Введите количество интервалов:" << endl;
	cin >> N_int;


	cout << "Введите левые границы:" << endl;
	auto intervals = new int[N_int + 1];
	for (int i = 0; i < N_int; ++i) {
		cin >> intervals[i];
	}

	for (int i = 0; i < N_int; i++) {
		for (int j = i; j < N_int; j++) {
			if (intervals[i] > intervals[j]) {
				swap(intervals[i], intervals[j]);
			}
		}
	}


	auto numbers = new int[N];
	for (int i = 0; i < N; i++)
	{
		numbers[i] = rand() % (X_max - X_min + 1) + X_min;
		cout << numbers[i] << ' ';
	}

	cout << endl;

	auto final_answer = new int[N_int];

	/*for (int i = 0; i < N_int; i++) {
		final_answer[i] = 0;
	}*/
	int len_raspr = X_max - X_min + 1;
	int* raspr_arr = new int[len_raspr];
	int* arr3 = new int[N_int + 1];

	for (int i = 0; i < len_raspr; i++)
	{
		raspr_arr[i] = 0;
		arr3[i] = 0;
	}

	func(numbers, N, raspr_arr, X_min, intervals, arr3, len_raspr, N_int);

	for (int i = 0; i < len_raspr; i++)
	{
		cout << raspr_arr[i] << ' ';
	}
	cout << "\n\n";

	for (int i = 0; i < N_int; i++)
	{
		cout << intervals[i] << ": " << arr3[i] << "\n";
	}

	/*
	ofstream file("output.txt");
	for (int i = 0; i < N; i++) {
		cout << numbers[i] << ' ';
		file << numbers[i] << ' ';
	}
	file << endl;
	cout << endl;
	auto str = "N\tГраницы\tКоличество чисел";
	file << str << endl;
	cout << str << endl;
	for (int i = 0; i < N_int; i++) {
		auto str_res = to_string(i + 1) + "\t" + to_string(intervals[i]) + "\t\t" + to_string(final_answer[i]) + "\n";
		file << str_res;
		cout << str_res;
	}
	*/
	system("Pause");
	return 0;
}