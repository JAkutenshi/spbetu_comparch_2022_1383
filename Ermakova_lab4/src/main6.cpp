#include <iostream>
#include <fstream>
using namespace std;
char input_str[81];
char output_str[81];

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_CTYPE, "rus");

    cout << "Ермакова Василиса 1383\nЗадание: формирование строки только из цифр и латинских букв.\n";

    cout << "Введите строку\n";
    cin.getline(input_str, 81);
    char max;
    ofstream file;
    file.open("result.txt");

    __asm {
        push ds
        pop es
        mov bl, 0 // max
        mov esi, offset input_str
        mov edi, offset output_str

        checking :
        lodsb
            cmp al, '\0'
            je finish
            cmp al, '9'
            jle checking_digit
            cmp al, 'Z'
            jle checking_upper
            cmp al, 'z'
            jle checking_lower
            jmp checking

            checking_digit :
        cmp al, '0'
            jge checking_max
            jge write 
            jmp checking

             checking_max :
        cmp al, bl
            jnl write_max
            stosb
            jmp checking

            write_max :
        mov bl, al
            stosb 
            jmp checking

            checking_upper :
        cmp al, 'A'
            jge write
            jmp checking

            checking_lower :
        cmp al, 'a'
            jge write
            jmp checking

            write :
        stosb
            jmp checking

            finish :       
        mov max, bl

    };

    cout << "Строка только из цифр и латинских букв.\n";
    cout << output_str << std::endl;;
    cout << "Найти максимальную цифру в выходной строке\n";
    std::cout << max << std::endl;
    file << output_str;
    file.close();

    return 0;
}