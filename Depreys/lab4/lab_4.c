#include <stdio.h>

int main(){
    printf ("Группа 1383. Депрейс Александр. Вариант 7. Задание:\n\tИнвертирование введенных во входной строке цифр в восьмеричной СС\n\tи преобразование заглавных русских букв в строчные,\n\tостальные символы входной строки передаются в выходную строку непосредственно.\n");

    char input[81];
    char output[81];

    fgets(input,81,stdin);

    asm(

        "letter_check: \n"
        "lodsb \n"
        "cmp al, 0\n"
        "je finish \n"
        "cmp al, 48 \n"
        "jl isnt_num \n"
        "cmp al, 55 \n"
        "jg isnt_num \n"

        "is_num: \n"
        "mov bl, 103 \n"
        "sub bl, al \n"
        "mov al, bl \n"
        "stosb \n"
        "jmp letter_check \n"

        "isnt_num: \n"
        "cmp al, 168 \n"
        "je weird_rus_letter \n"
        "cmp al, 192 \n"
        "jl isnt_rus_up \n"
        "cmp al, 223 \n"
        "jg isnt_rus_up \n"

        "is_rus_up: \n"
        "add al, 32 \n"
        "stosb \n"
        "jmp letter_check \n"

        "weird_rus_letter: \n"
        "mov al, 184 \n"
        "stosb \n"
        "jmp letter_check \n"

        "isnt_rus_up: \n" 
        "stosb \n"
        "jmp letter_check \n"   

        "finish: \n"
        "stosb \n"


        // : "=m"(output) : "S"(input)
        : // Output
        : "D"(output), "S"(input) // Input
        : // Clobber list
    );



    printf("%s", &output);
    FILE * file = fopen ("out.txt", "w");
    fprintf(file, "%s", output);
    fclose (file);
};