#include "pch.h"
#include <iostream>
#include <locale>
#include <fstream>
 
using namespace std;
 
char input[85];
 
int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
 
	int ans = 0;
	cin.getline(input, 80, '\n');
	char i = 0;
	_asm
	{
		mov esi, offset input
 
		check :
		mov dl, 48
			mov i, dl
			cmp[esi], '\0'
			je finish
			lodsb
			start :
 
		cmp al, i
			je norm
 
			add i, 2
			cmp i, 58
			je check
			jmp start
			norm :
		add ans, 1
			jmp check
			finish :
	}
 
 
	cout << ans;
	return 0;
}