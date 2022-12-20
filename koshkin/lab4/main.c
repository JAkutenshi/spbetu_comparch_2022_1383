#include <stdio.h>
#include <stdlib.h>

int main () {

    printf ("Группа 1383. Кошкин Евгений\nВариант 12.\n\
Формирование номера введенной латинской буквы по алфавиту и номера позиции его \
первого вхождения во входной строке и выдача их на экран.\n");

    char str[81];
    char alph[26] = {0};

    fgets (str, 81, stdin);

    asm volatile(
        "   mov cl, 0 \n "
        "   sub rax, rax \n"

        "mainloop: \n"
        "   inc cl \n"
        "   lodsb \n"
        "   cmp al, 0 \n"
        "   je finish \n"
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

        "replace: \n"
        "   mov [%0 + rax], cl \n"
        "   jmp mainloop \n"

        "finish: "

    : "=m"(alph) : "S"(str));

    FILE * file = fopen ("out.txt", "w");

    for (int i = 0; i < 26; i ++) {
        if (alph[i] != 0) {
            printf ("%d %d\n", i + 1, alph[i]);
            fprintf(file, "%d %d\n", i + 1, alph[i]);
        }
    }

    fclose (file);
    
    return 0;
}