#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>

char input[1000];
char output[1000];
char letters[] = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZбвгджзйклмнпрстфхцчшщБВГДЖЗЙКЛМНПРСТФХЦЧШЩ";
int count = 0;



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Панов Михаил 1383. \nВариант 15: сключение русских букв и цифр, введенных \nво входной строке, при формировании выходной строки." << std::endl;
	std::cin.getline(input, 1000);


	__asm {
		mov ecx, 0
		mov esi, offset input
		mov edi, offset output
		mov edx, offset letters
	

		start :
		lods
			mov ecx, 0
		check :
			mov bl, [edx][ecx]
			cmp al, bl
			je plus
			add ecx, 1
			cmp ecx, 84
			je next
			jmp check
		plus :
			mov ebx, count
			add ebx, 1
			mov count, ebx
		next :
			stosb
			cmp[esi], '\0'
			jne start
	}
	std::cout << count;

	return 0;
}