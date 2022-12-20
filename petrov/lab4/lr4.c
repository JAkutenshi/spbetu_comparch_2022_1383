#include <stdio.h>
#include <wchar.h>
#include <locale.h>
int main(){
    setlocale(LC_ALL, "");
    wprintf (L"Петров Александр\nГруппа 1383\nВариант 16\nПреобразование введенных во входной строке русских букв в латинские в соответствие с правилами транслитерации, остальные символы входной строки передаются в выходную строку непосредственно.\n");
    system("chcp 1251 > nul");
    char input[81];
    char output[81];
    fgets(input,81,stdin);

    char translate[65] = 
        "a\0"//а
        "b\0"//б
        "v\0"//в
        "g\0"//г
        "d\0"//д
        "e\0"//e
        "g\0"//ж
        "z\0"//з
        "i\0"//и
        "j\0"//й
        "k\0"//к
        "l\0"//л
        "m\0"//м
        "n\0"//н
        "o\0"//о
        "p\0"//п
        "r\0"//р
        "s\0"//с
        "t\0"//т
        "u\0"//у
        "f\0"//ф
        "kh"//х
        "ts"//ц
        "ch"//ч
        "sh"//ш
        "sc"//щ
        "\0\0"//ъ
        "y\0"//ы
        "\0\0"//ь
        "e\0"//э
        "iu"//ю
        "ia"//я
    ;



    asm(
        "letter_check: \n"
            "mov eax, 0\n"
            "mov ebx, 0\n"
            "lodsb \n"
            "cmp al, 0\n"
            "je finish \n"

            "cmp al, 223\n"
            "jg check_down \n"
            "cmp al, 191\n"
            "jg check_up \n"
            "jmp out\n"
            

        "check_down:\n"
            "cmp al, 255\n"
            "jle letter_down\n"
            "jmp out\n"

        "check_up:\n"
            "cmp al, 223\n"
            "jle letter_up\n"
            "jmp out\n"


        "letter_down: \n"
            "sub al, 224\n"
            "shl al, 1\n"
            "mov bl, al\n"
            "mov eax, [%[translate] + ebx]\n"
            "cmp al, 0\n"
            "je letter_check\n"
            "stosb\n"
            "mov eax, [%[translate] + ebx + 1]\n"
            "cmp al, 0\n"
            "je letter_check\n"
            "stosb\n"
            "jmp letter_check\n"

        "letter_up: \n"
            "sub al, 192\n"
            "shl al, 1\n"
            "mov bl, al\n"
            "mov eax, [%[translate] + ebx]\n"
            "cmp al, 0\n"
            "je letter_check\n"
            "sub al, 32\n"
            "stosb\n"
            "mov eax, [%[translate] + ebx + 1]\n"
            "cmp al, 0\n"
            "je letter_check\n"
            "sub al, 32\n"
            "stosb\n"
            "jmp letter_check\n"

        "out:\n"
            "stosb\n"
            "jmp letter_check\n"

        "finish: \n"
            "stosb \n"
            "mov al, 0\n"
            "stosb\n"

        :
        : "D"(output), "S"(input), [translate]"r"(translate)
        :
    );



    printf("%s\n", &output);
    FILE * file = fopen ("out.txt", "w");
    fprintf(file, "%s", output);
    fclose (file);
};
