#include <iostream>
#include <clocale>
#include <fstream>
#include <windows.h>
char input[81];
char output[81];
int count = 0;
char s[] = "eyuioaEUIOAУЕЫАОЭЯИЮЁёуеыаоэяию";

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
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
        //std::cout << (int)input[i] << ' ';
        if (ab[i] == '\0') break;
    }
    std::cout << '\n';
    //31

    int a = 0;
    __asm {
        mov esi, offset input
        mov edi, offset output
        mov edx, offset s
        mov ecx, 0
        
        start :
        lods
            mov ecx, 0
        check :
            ;---------------
            mov bl, [edx][ecx]
            cmp al, bl
            ;---------------
            je plus
            add ecx, 1
            cmp ecx, 31
            je next
            jmp check
        plus:
            mov ebx, count
            add ebx, 1
            mov count, ebx
        next :
            stosb
            cmp[esi], '\0'
            jne start
    }
    std::cout << "Результат: ";
    //std::cout << output << '\n';
    std::cout << count << '\n';
    file << output;
    file.close();
    return 0;
}