
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
	std::cout<<"����� ������ 1383. \n������� 15: ��������� ������� ���� � ����, ��������� \n�� ������� ������, ��� ������������ �������� ������."<<std::endl;
	std::cin.getline(input, 81);

	__asm {
		push ds
		pop es
		mov esi, offset input
		mov edi, offset output

		start :
		lodsb
			cmp al, '�'
			je next
			cmp, '�'
			je next
			cmp al, '�' // < A
			jl save
			cmp al, '�'
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