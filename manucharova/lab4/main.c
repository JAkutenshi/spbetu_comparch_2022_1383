#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 81

int main () {

    printf("Манучарова Ангелина\nГруппа 1383\nВариант 14\nИсключение латинских букв и цифр, введенных во входной строке при формировании выходной строки.\n");
    char *input= (char *)malloc((MAXLEN) * sizeof(char));
    char *output=(char *)malloc((MAXLEN) * sizeof(char));;
    int count = 0;
    char mas[] = "УЕЫАОЭЯИЮуеыаоэяиюЁё";
    printf("Введите входную строку: ");
    fgets (input, 81, stdin);

    __asm__ volatile(
    "   mov rsi, %[input]\n"
    "   mov rdi, %[output]\n"
    "start:\n"
    "   lodsb\n"
    "   cmp al, 0\n"
    "   je save1\n"
    "   cmp al, -48\n"
    "   je check\n"
    "   cmp al, -47\n"
    "   je check\n"
    "   cmp al, '0'\n"
    "   jl save \n"
    "   cmp al, '9'\n"
    "   jle start \n"
    "   cmp al, 'A'\n"
    "   jl save \n"
    "   cmp al, 'Z'\n"
    "   jle start \n"
    "   cmp al, 'a'\n"
    "   jl save\n"
    "   cmp al, 'z'\n"
    "   jle start\n  "

    "save:\n"
    "   stosb\n"
    "   jmp start\n"

    "check:\n"
    "   stosb\n"
    "   mov bl, al\n"
    "   lodsb\n"
    "   stosb\n"
    "   mov bh, al\n"
    "   mov rdx, rsi\n"
    "   mov rsi, %[mas]\n"

    "compare:\n"
    "   lodsw\n"
    "   cmp ax, 0\n"
    "   je increment\n"
    "   cmp ax, bx\n"
    "   jne compare\n"
    "   jmp recovery\n"


    "increment:\n"
    "   inc %[count]\n"

    "recovery:\n"
    "   mov rsi, rdx\n"
    "   jmp start\n"

    "save1:\n"
    "   stosb\n"
    : [output] "=m"(output), [count] "=m"(count)
    : [input] "m"(input), [mas] "c"(mas));

    printf ("Результат: %sKоличество согласных букв: %d\n", output, count);

    return 0;
}

