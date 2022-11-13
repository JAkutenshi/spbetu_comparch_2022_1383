#include <iostream>
#include <clocale>
#include <fstream>


char input[81];
char output[81];

int main(){
    std::ofstream file("output.txt");
    setlocale(LC_ALL, "RUS");
    std::cout << "Манучарова Ангелина\nГруппа 1383\nВариант 14\nИсключение латинских букв и цифр, введенных во входной строке при формировании выходной строки.\n";
    std::cout << "Введите строку: ";
    std::cin.getline(input, 81);
    __asm
    {
    mov esi, offset input
    mov edi, offset output
    start:
    lods
    cmp al, 48
    jl save

    cmp al, 122
    jg save


    cmp al, 57
    jg check1
    jmp next


    check1:
    cmp al, 65
    jl save
    cmp al, 90
    jg check2
    jmp next

    check2:
    cmp al, 97
    jl save
    jmp next

    save:
    stosb

    next:
    cmp [esi], '\0'
    jne start
    }
    std::cout<<"Результат: "<<output;
    file<<output;
    file.close();
    return 0;
}



