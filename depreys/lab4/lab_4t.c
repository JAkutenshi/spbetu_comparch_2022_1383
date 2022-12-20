#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(){
    printf ("Группа 1383. Депрейс Александр. Вариант 7. Задание:\n\tИнвертирование введенных во входной строке цифр в восьмеричной СС\n\tи преобразование заглавных русских букв в строчные,\n\tостальные символы входной строки передаются в выходную строку непосредственно.\n");

    char input[81];
    char output[81];
    char sum = 0; 

    fgets(input,81,stdin);

    asm(

        "letter_check: \n"
        "lodsb \n"
        "cmp al, 0\n"
        "je finish \n"
        "cmp al, '0' \n"
        "jl isnt_num \n"
        "cmp al, '9' \n"
        "jg isnt_num \n"

        "check_x_system: \n"
        "cmp al, '7' \n"
        "jle is_num \n"
        "stosb \n"
        "sub al, '0' \n"
        "add %[my_sum], al \n" 
        "jmp letter_check \n"


        "is_num: \n"
        "mov bl, '0' \n"
        "add bl, '7' \n"
        "sub bl, al \n"
        "mov al, bl \n"
        "sub bl, '0' \n"
        "add %[my_sum], bl \n" 
        "stosb \n"
        "jmp letter_check \n"

        "isnt_num: \n"
        "cmp al, 208 \n"
        "je is_rus_1 \n"
        "cmp al, 209 \n"
        "je is_rus_2 \n"

        "isnt_rus_up: \n"
        "stosb \n"
        "jmp letter_check \n"

        "weird_rus_letter: \n"
        "mov al, 209 \n"
        "stosb \n"
        "mov al, 145 \n"
        "stosb \n"
        "jmp letter_check \n"

        "is_rus_1: \n"
        "lodsb \n"
        "cmp al, 129 \n"
        "je weird_rus_letter \n"
        "cmp al, 144 \n"
        "jl letter_check \n"
        "cmp al, 159 \n"
        "jg second_rus_check \n"
        
        "print_rus_1: \n"
        "mov bl, al \n"
        "mov al, 208 \n"
        "stosb \n"
        "mov al, bl \n"
        "add al, 32 \n"
        "stosb \n"
        "jmp letter_check \n"

        "second_rus_check: \n"
        "cmp al, 175 \n"
        "jle print_rus_2 \n"
        "cmp al, 191 \n"
        "jg letter_check \n"

        "print_rus_3: \n"
        "mov bl, al \n"
        "mov al, 208 \n"
        "stosb \n"
        "mov al, bl \n"
        "stosb \n"
        "jmp letter_check \n"

        "print_rus_2: \n"
        "mov bl, al \n"
        "mov al, 209 \n"
        "stosb \n"
        "mov al, bl \n"
        "sub al, 32 \n"
        "stosb \n"
        "jmp letter_check \n"

        "is_rus_2: \n"
        "stosb \n"
        "lodsb \n"
        "stosb \n"
        "jmp letter_check \n"

        "finish: \n"
        "stosb \n"


        // : "=m"(output) : "S"(input)
        : [my_sum] "=m"(sum)
        : "D"(output), "S"(input)  // Input
        : // Clobber list
    );



    printf("%ssum is: %d", &output, sum);
    FILE * file = fopen ("out.txt", "w");
    fprintf(file, "%s, sum is: %d", output, sum);
    fclose (file);
};