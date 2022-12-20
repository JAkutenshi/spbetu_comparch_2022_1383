#include <iostream>
#include <fstream>
#include <stdio.h>


char input_string[81];
char output_string[81];

int main() {
    setlocale(LC_CTYPE, "rus");
    std::cout << "Валиев Р.Р.\nВариант 2. Формирование выходной строки только из цифр и латинских букв входной строки\n";

    fgets(input_string, 81, stdin);
    input_string[strlen(input_string)] = '\0';

    __asm {
        push ds
        pop es
        mov esi, offset input_string
        mov edi, offset output_string
        read :
        lodsb

            cmp al, '0'
            jl next
            cmp al, '9'
            jle write

            cmp al, 'A'
            jl next
            cmp al, 'Z'
            jle write

            cmp al, 'a'
            jl next
            cmp al, 'z'
            jg next

            write :
        stosb
            next :
        cmp[esi], '\0'
            jne read
    };

    std::cout << output_string << std::endl;
    std::ofstream file("output.txt");
    file << output_string;
    std::cin;
    return 0;
}