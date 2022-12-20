
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>

char input[80];
char output[1000];
std::string str;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout<<"Панов Михаил 1383. \nВариант 15: сключение русских букв и цифр, введенных \nво входной строке, при формировании выходной строки."<<std::endl;
	std::cin.getline(input, 81);

	__asm {
		push ds
		pop es
		mov esi, offset input
		mov edi, offset output

		start :
		lodsb
			cmp al, 'Ё'
			je next
			cmp, 'ё'
			je next
			cmp al, 'А' // < A
			jl save
			cmp al, 'я'
			jle next
			cmp al, '0' // < 0
			jl save
			cmp al, '9' // >0 && <9
			jle next
			save :
		stosb
			next :
		cmp[esi], '\0'
			jne start
	}
	std::ofstream file("output.txt");
	std::cout << output <<std::endl;
	file << output;
	file.close();

	return 0;
}