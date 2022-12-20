#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
char s[81];
char o[81];
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Богданов-1383.  Формирование выходной строки только из цифр и русских букв входной строки" << endl;
	cin.getline(s,81,'\n');
	_asm
	{
		mov esi, offset s
		mov edi, offset o

		check:
			cmp [esi],'\0'
			je finish

		start:
			lodsb
			cmp al,58
			jl t1
			jmp check

		t1:
			cmp al, -64
			jl y
			jmp t2
		t2:
			cmp al, 48
			jl t3
			jmp norm

		t3:
			cmp al, 0
				jl norm
				jmp check
		y:
			cmp al,-75
			je norm
			cmp al, -88
			je norm
			jmp check

		norm:
			stosb
			jmp check
		finish:
	}
	
	cout << o;
	freopen("output.txt", "w", stdout);
	cout << o;
	return 0;
}
