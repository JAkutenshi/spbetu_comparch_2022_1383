#include <iostream>
#include <clocale>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>


char input[81];
char output[81];
int count = 0;

int main() {
    std::ofstream file("output.txt");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");
    std::cout << "Манучарова Ангелина\nГруппа 1383\nВариант 14\nИсключение латинских букв и цифр, введенных во входной строке при формировании выходной строки.\n";
    std::cout << "Введите строку: ";
    std::cin.getline(input, 81);
    //   char ab[30];
    //   std::cin.getline(ab, 81);
    //   for (int i = 0; i < 81; ++i)
//    {
//        input[i] = ab[i];
//        std::cout << (int)input[i] << ' ';
//        if (ab[i] == '\0') break;
//    }
    __asm
    {
    mov esi, offset input
    mov edi, offset output
    mov ecx, count
    start :
    lods
    cmp al, 0
    jl check3

    cmp al, 48
    jl save

    cmp al, 122
    jg save


    cmp al, 57
    jg check1
    jmp next


    check1 :
    cmp al, 65
    jl save
    cmp al, 90
    jg check2
    jmp next

    check2 :
    cmp al, 97
    jl save
    jmp next

    check3 :
    cmp al, -45
    je save
    cmp al, -13
    je save
    cmp al, -59
    je save
    cmp al, -27
    je save
    cmp al, -37
    je save
    cmp al, -5
    je save
    cmp al, -64
    je save
    cmp al, -32
    je save
    cmp al, -50
    je save
    cmp al, -18
    je save
    cmp al, -35
    je save
    cmp al, -3
    je save
    cmp al, -33
    je save
    cmp al, -1
    je save
    cmp al, -56
    je save
    cmp al, -24
    je save
    cmp al, -34
    je save
    cmp al, -2
    je save
    cmp al, -88
    je save
    cmp al, -72
    je save
    inc ecx

    save :
    stosb

    next :
    cmp[esi], '\0'
    jne start
    mov count, ecx
    }
    std::cout << "Результат: " << output;
    std::cout << "\nСогласных букв: " << count;
    std::cout << '\n';
    file << output;
    file.close();
    system("pause");
    return 0;
}



