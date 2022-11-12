
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>

char input[81];
char output[162];
short int count = 0;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Седова Элла 1383.\nВариант 19.Заменить введенные во входной строке латинские буквы на десятичные числа,\nсоответствующие их номеру по алфавиту, остальные символы входной строки\nпередать ввыходную строку непосредственно.\n";
    std::cout << "Введите строку: ";
    std::cin.getline(input, 81);
    std::ofstream file("out.txt");
    __asm {
        push ds
        pop es
        mov esi, offset input
        mov edi, offset output
     start :
            lodsb
            cmp al, 65     //al<'A'
            jl save_sumbol
            cmp al, 90     //al<='Z'
            jle letter_A_I
            cmp al, 97     //al<'a'
            jl save_sumbol
            cmp al, 122     //al<='z'
            jle letter_lower
     letter_lower:
            and al, 1011111b  //делает строчную букву заглавной
     letter_A_I :
            cmp al, 74      //'J'
            jge letter_J_S      //al>='J'
            sub al, 65     //'A'
            add al, 31h
            jmp save_sumbol
     letter_J_S :
            cmp al, 84      //'T'
            jge letter_T_Z      //al>='T'
            mov ah, al
            sub ah, 74      //'J'
            add ah, 30h
            mov al, '1'
            jmp save_letter
     letter_T_Z :
            mov ah, al
            sub ah, 84      //'T'
            add ah, 30h
            mov al, '2'
            jmp save_letter
     save_letter :
            stosw
            jmp start
     save_sumbol:
            stosb
     next :
            cmp[esi], '\0'
            jne start
    }
    std::cout << "Итог: " << output;
    file << output;
    file.close();
    return 0;
}

  
  
   

   
