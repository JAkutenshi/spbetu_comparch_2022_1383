#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
char s[81];
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int ans = 0;
	cout << "Богданов-1383. Формирование выходной строки только из цифр и русских букв входной строки" << endl;
	cin.getline(s, 81, '\n');
	char i = 0;
	_asm
		{
			mov esi, offset s

			check :
				mov dl,49
				mov i,dl
				cmp[esi], '\0'
				je finish
				lodsb
			start :

				cmp al,i
				je norm

				add i,2
				cmp i,59
				je check
				jmp start
			norm:
				add ans,1
				jmp check
			finish :
	}

	
	cout << ans;
	//freopen("output.txt", "w", stdout);
	//cout << o;
	return 0;
}