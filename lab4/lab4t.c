#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main () {
    
    printf ("Группа 1383. Кошкин Евгений\nВариант 12.\n\
Формирование номера введенной латинской буквы по алфавиту и номера позиции его \
первого вхождения во входной строке и выдача их на экран.\n");

    char str[81];
    char alph[26] = {0};
    char rus[33] = {0};

    fgets (str, 81, stdin);

    asm volatile(
        "   mov cl, 0 \n "
        "   sub rax, rax \n"

        "mainloop: \n"
        "   inc cl \n"
        "   lodsb \n"
        "   cmp al, 0 \n"
        "   je finish \n"
        "   cmp al, 208 \n"
        "   je russian1 \n"
        "   cmp al, 209 \n"
        "   je russian2 \n"
        "   or al, ' ' \n"
        "   cmp al, 'a' \n"
        "   jl mainloop \n"
        "   cmp al, 'z' \n"
        "   jg mainloop \n"

        "find_letter: \n"
        "   sub al, 97 \n"
        "   mov bl, [%0 + rax] \n"
        "   cmp bl, 0 \n"
        "   je replace \n"
        "   jmp mainloop \n"

        "russian1: \n"
        "   lodsb \n"
        "   cmp al, 1 \n"
        "   je exp \n"
        "   cmp al, 144 \n"
        "   jl mainloop \n"
        "   cmp al, 191 \n"
        "   jg mainloop \n"
        "   cmp al, 176 \n"
        "   jge small1 \n"
        "   sub al, 144 \n"
        "   cmp al, 7 \n"
        "   jg add1 \n"
        "   jmp replace1 \n"
        
        "russian2: \n"
        "   lodsb \n"
        "   cmp al, 145 \n"
        "   je exp \n"
        "   cmp al, 128 \n"
        "   jl mainloop \n"
        "   cmp al, 143 \n"
        "   jg mainloop \n"
        "   sub al, 111 \n"
        "   jmp replace1 \n"

        "small1: \n"
        "   sub al, 176 \n"
        "   cmp al, 7 \n"
        "   jg add1 \n"
        "   jmp replace1 \n"

        "exp: \n"
        "   mov al, 6 \n"
        "   jmp replace1 \n"

        "add1: \n"
        "   add al, 1 \n"

        "replace1: \n"
        "   mov bl, [%1 + rax] \n"
        "   cmp bl, 0 \n"
        "   jne mainloop \n"
        "   mov [%1 + rax], cl \n"
        "   jmp mainloop \n"

        "replace: \n"
        "   mov [%0 + rax], cl \n"
        "   jmp mainloop \n"

        "finish: "

    : "=m"(alph), "=m"(rus) : "S"(str));

    FILE * file = fopen ("out.txt", "w");

    printf ("english\n");
    for (int i = 0; i < 26; i ++) {
        if (alph[i] != 0) {
            printf ("%d %d\n", i + 1, alph[i]);
            fprintf(file, "%d %d\n", i + 1, alph[i]);
        }
    }
    printf ("russian\n");
    for (int i = 0; i < 33; i++) {
        if (rus[i] != 0) {
            printf ("%d %d\n", i + 1, rus[i]);
            fprintf(file, "%d %d\n", i + 1, rus[i]);
        }
    }

    fclose (file);

    return 0;
}