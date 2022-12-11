#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
char input_str[81];
char output_str[165];

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "�������� ������ 1383\n�������:\n�������� ��������� �� ������� ������ ������� ����� �� ���������� �����,��������������� �� ������ �� ��������,\n��������� ������� ������� ������ �������� � �������� ������ ���������������.\n";

    cout << "������� ������:\n";
    cin.getline(input_str, 81);

    ofstream fout("result.txt");
    __asm {
        push ds
        pop es
        mov esi, offset input_str
        mov edi, offset output_str

        start:
        lodsb
            mov ah, 0
            cmp al, '�'
            JGE nextB1
            jmp fin1

        nextB1:
            cmp al, '�'
            JLE nextB2
            jmp fin1

        nextB2:
            sub al, '�'
            jmp chang

        fin1:
            cmp al, '�'
            JGE nextS1
            jmp nextS3

        nextS1:
            cmp al, '�'
            JLE nextS2
            jmp nextS3
        nextS2:
            sub al, '�'
            jmp chang

        jmp nextS3
        chang:
            cmp al, 7
            JG some1
            JLE some2

        some1:
            add al,2
            mov bl,10
            div bl
            add al, '0'
            stosb
            mov al,ah
            add al, '0'
            stosb

            jmp start

        some2:
            cmp al, 5
            JG some3
            jmp nextn
            some3:
                add al, 1
            nextn:
                add al, '1'
                stosb

                jmp start

            nextS3:
            cmp al,'�'
            JE change2
            cmp al, '�'
            JE change2
            jmp nextn1
                change2:
                    mov al, '7'
            nextn1:
                stosb

                cmp[esi], '\0'
                jne start
    };


    cout << output_str;
    fout << output_str;
    fout.close();

    return 0;
}
