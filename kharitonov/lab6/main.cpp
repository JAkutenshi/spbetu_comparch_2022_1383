#include <iostream>
#include <windows.h>
#include <fstream>
#include <random>

using namespace std;

extern "C" void(func1(int* array, int arr_size, int* raspr_arr, int Xmin));
extern "C" void(func2(int* arr1, int* arr2, int* res, int arr1_len, int index,int Xmin));

int comparator(const void* v1, const void* v2) {
	int i1 = *((int*)v1);
	int i2 = *((int*)v2);
	return i1 - i2;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int size;
	int count;
	int Xmin;
	int Xmax;
	cout << "Введите размер массива" << '\n';
	cin >> size;
    int* arr = new int[size];
	
	cout << "Введите левую границу массива" << '\n';

	cin >> Xmin;

	cout << "Введите правая граница массива" << '\n';

	cin >> Xmax;

	if (Xmin> Xmax) {
		cout << "Неверные границы массива";
		return 1;
	}


	for (int i = 0; i < size; i++)
	{
		arr[i] = rand()%(Xmax-Xmin+1)+Xmin;
	}
	//работает
	//------------------

	cout << "Введите количество разбиений" << '\n';
	cin >> count;

	int *LGInt = new int[count];
	cout << "Введите разбиения" << '\n';

	for (int i = 0; i < count; i++)
	{
		cin >> LGInt[i];
	}
	qsort(LGInt, count, sizeof(int), comparator);
	// конец ввода
	//-----------------------

	cout << "Сгенерированные числа:" << '\n';
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
	int raspr_len = Xmax - Xmin + 1;
	cout << '\n' << "Массив распределения" << '\n';

	int* mas_raspr = new int[raspr_len];
	for (int i = 0; i < raspr_len; i++)
	{
		mas_raspr[i] = 0;
	}
	func1(arr, size, mas_raspr, Xmin);
	for (int i = 0; i < raspr_len; i++)
	{
		cout << mas_raspr[i] << ' ';
	}
	int* res_mas = new int[count];
	for (int i = 0; i < count; i++)
	{
		res_mas[i] = 0;
	}
	func2(mas_raspr, LGInt, res_mas, raspr_len, count, Xmin);
	cout << "\n\n";
	ofstream out;
	out.open("res.txt");

	for (int i = 0; i < count; i++)
	{
		cout << LGInt[i] << ": " << res_mas[i] << '\n';
		out << LGInt[i] << ": " << res_mas[i] << '\n';
	}
	out.close();
	/*
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
	func(arr, size);
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	*/
	
}


