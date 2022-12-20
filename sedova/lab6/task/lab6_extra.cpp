#include <iostream>
#include <fstream>
#include <random>
#include <windows.h>

extern "C" void(func(int* array, int Numbers,
	int* LGrInt, int NInt, int* result, int* maxim)); 

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
	std::ofstream Result;
    Result.open("result.txt", std::ios_base::out);

    int Numbers;
    std::cout << "Длина массива псевдослучайных целых чисел: \n";
    std::cin >> Numbers;
	if (Numbers <= 0 || Numbers > 16 * 1024) {
		printf("Неверная длина массива\n");
		return 1;
	}
    int* array = new int[Numbers];

    int left;
    std::cout << "Левая граница массива: \n";
    std::cin >> left;

    int right;
    std::cout << "Правая граница массива: \n";
    std::cin >> right;
	if (left > right) {
		printf("Неверный диапазон генерации чисел\n");
		return 1;
	}

	for (int i = 0; i < Numbers; ++i) {
		array[i] = rand() % (right - left + 1) + left;
	}

    int NInt;
    std::cout << "Количество интервалов разбиения: ";
    std::cin >> NInt;
	if (NInt <= 0) {
		printf("Неверное количество интервалов разбиения\n");
		return 1;
	}

	int* LGrInt = new int[NInt];
	int tmp;
	for (int i = 0; i < NInt; i++) {
		std::cout << "Введите левую границу интервала[" << i+1 << "]: ";
		std::cin >> tmp;
		LGrInt[i] = tmp;
		if (LGrInt[i] < left || LGrInt[i] > right || 
			i > 0 && LGrInt[i] < LGrInt[i - 1] || LGrInt[i] == LGrInt[i - 1]) {
			printf("Некорректное значение левой границы\n");
			free(LGrInt);
			return 1;
		}
	}
    
	int* maxim = new int[NInt];
	for (int i = 0; i < NInt; i++) {
		maxim[i] = left;
	}

    int* result = new int[NInt] {0};
    func(array, Numbers, LGrInt, NInt, result, maxim);

	std::cout << "Массив: ";
	Result << "Массив: ";
	for (int i = 0; i < Numbers; ++i) {
		std::cout << array[i] << ' ';
		Result << array[i] << ' ';
	}
	std::cout << '\n';
	Result << '\n';
	std::cout << "Номер интервала:\t" << "Левая граница:\t" << "Количество чисел, попавших в интервал:\t" << "Максимум:" << '\n';
	Result << "Номер интервала:\t" << "Левая граница:\t" << "Количество чисел, попавших в интервал:\t"<<"Максимум:"<<'\n';
	for (int i = 0; i < NInt; ++i) {
		std::cout << "    " << i + 1 << "\t        \t" << LGrInt[i] << "\t\t" << result[i] << "\t\t\t\t\t"<<maxim[i]<<'\n';
		Result << "    " << i + 1 << "\t        \t" << LGrInt[i] << "\t\t" << result[i] << '\n';
	}

    delete[] array;
    delete[] LGrInt;
    delete[] result;
    Result.close();
    return 0;
}
