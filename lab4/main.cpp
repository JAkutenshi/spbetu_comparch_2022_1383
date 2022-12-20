#include <iostream>
#include <clocale>
#include <fstream>

char input[81];
char output[81];
int count = 0;

int main() {

    std::string str1 = "Харитонов Никита\nГруппа 1383\nВариант 22\nПреобразование всех заглавных латинских букв входной строки в строчные, а \n"
                       "десятичных цифр в инверсные, остальные символы входной строки передаются в выходную \n"
                       "строку непосредственно\n";

    std::ofstream file("output.txt");
    std::cout << str1;
    std::cout << "Введите строку: ";
    char ab[81];
    std::cin.getline(ab, 81);
    for (int i = 0; i < 81; ++i) {
        input[i] = ab[i];

        if (ab[i] == '\0') break;
    }
    std::cout << '\n';

    int a = 0;
    __asm{
        mov esi, offset input
        mov edi, offset output
        mov ecx, count
        start:
            add ecx, 1
            lods
            cmp al, 65
            jl second
            cmp al, 90
            jg second
            add al, 32
            jmp next
        second:
            cmp al, 48
            jl next
            cmp al, 57
            jg next
            mov bl, al
            sub bl, 48
            mov dl, 9
            sub dl, bl
            add dl, 48
            mov al, dl
        next:
            stosb
            cmp [esi], '\0'
            jne start
            mov count, ecx

    }
    std::cout << "Результат: ";
    std::cout << output;
    file<<output;
    file.close();
    return 0;
}
