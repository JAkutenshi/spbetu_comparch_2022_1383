#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <windows.h>

extern "C" void func1(int* array, int* res, int len, int min, int* mass);
extern "C" void func2(int* boards, int* intervals, int* distribution, int difference, int Nint, int X_min, int* mass, int* sum);

int main() {
	std::cout << "Input len array\n";
	int len = 0;
	std::cin >> len;
	if (len > 16384 || len <= 0) {
		std::cout << "error\n";
		return 0;
	}
	int* array = new int[len];
	int X_min = 0;
	int X_max = 0;
	std::cout << "Input left and right border\n";
	std::cin >> X_min >> X_max;
	if ((X_max - X_min) <= 0) {
		std::cout << "Error input borders\n";
		return 0;
	}
	int Nint = 0;
	std::cout << "Input number of intervals\n";
	std::cin >> Nint;
	if (Nint > 24 || Nint <= 0) {
		std::cout << "Error input number of intervals\n";
		return 0;
	}
	int* boards = new int[Nint];
	std::cout << "Input boards intervals\n";
	for (int i = 0; i < Nint; i++) {
		std::cin >> boards[i];
	}

	int difference = X_max - X_min + 1;
	srand(time(NULL));
	for (int i = 0; i < len; i++) {
		array[i] = X_min + rand() % (difference);
	}

	int* distribution = new int[difference];
	int* mass = new int[difference];
	for (int i = 0; i < difference; i++) {
		distribution[i] = 0;
		mass[i] = 0;
	}
	func1(array, distribution, len, X_min, mass);
	std::cout << "Array\n";
	for (int i = 0; i < len; i++) {
		std::cout << array[i] << ' ';
	}
	std::cout << '\n';
	for (int i = 0; i < difference; i++) {
		std::cout << mass[i] << " ";
	}
	
	std::cout << '\n';
	std::cout << "Distribution array\n";
	for (int i = 0; i < difference; i++) {
		std::cout << distribution[i] << ' ';
	}
	std::cout << '\n';


	int* intervals = new int[Nint];
	int* sum = new int[Nint];
	for (int i = 0; i < 0; i++) {
		intervals[i] = 0;
		sum[i] = 0;
	}
	func2(boards, intervals, distribution, difference, Nint, X_min, mass, sum);
	std::ofstream out;
	out.open("result.txt");
	for (int i = 0; i < Nint; i++) {
		std::cout << i << ' ' << boards[i] << ' ' << intervals[i] << ' ' << sum[i] << '\n';
		out << i << ' ' << boards[i] << ' ' << intervals[i] << ' ' << sum[i] << '\n';
	}
	out.close();
	delete intervals;
	delete boards;
	delete distribution;
	delete array;
	return 0;
}