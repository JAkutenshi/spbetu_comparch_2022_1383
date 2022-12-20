#include "pch.h"
#include <iostream>
#include <locale>
#include <fstream>
 
using namespace std;
 
char input[85];
char output[170];
int num_count = 0;
int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    wprintf(L"Чернякова Александра, гр. 1383\nВариант 24\nИнвертирование введенных во входной строке цифр в шестнадцатиричной СС и преобразование строчных русских букв в заглавные.");
    cin.getline(input, 80);
    __asm {
        mov esi, offset input
        mov edi, offset output
        start :
        lodsb
            cmp al, '\0'
            je final
 
            from_0_to_5 :
            cmp al, '0'
            jl symbols_check
            cmp al, '5'
            jg more_5_less_A
            mov ah, 'F'
            sub ah, al
            add ah, 48
            mov al, ah
            stosb
            jmp start
 
            more_5_less_A :
        cmp al, '9'
            jg more_than_9
            mov ah, 'F'
            sub ah, al
            add ah, 41
            mov al, ah
			jmp inc_if_even
 
            more_than_9 :
        cmp al, 'F'
            jg symbols_check
            mov ah, 'F'
            sub ah, al
            add ah, 48
            mov al, ah
			jmp inc_if_even
 
            symbols_check :
        cmp al, 224
            jl yo_check
            cmp al, 255
            jg yo_check
            sub al, 32
            stosb
            jmp start
 
            yo_check:
        	cmp al, 184
            jne other
            mov al, 168
            stosb
            jmp start
 
 		inc_if_even:
			push ax
			and al, 00000001b
			cmp al, 0
			jne inc_end
			inc num_count
		inc_end:
			pop ax
            stosb
            jmp start
 
            other :
        stosb
            jmp start
 
            final:
        stosb
    };
    cout << output;
	cout << num_count;
    return 0;
}
