#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 81

int main()
{
    int vowels_num = 0;
    char vowels[] = "УЕЫАОЭЯИЮуеыаоэяиюЁё\0";
    char *input_str = (char *)malloc((MAXLEN) * sizeof(char));
    char *res = (char *)malloc((MAXLEN) * sizeof(char));
    printf("Малых Андрей, группа 1383.\nИсключение латинских букв и цифр, введенных во входной строке при формировании выходной строки.\n");
    fgets(input_str, MAXLEN, stdin);
    input_str[strlen(input_str) - 1] = '\0';
    __asm__ volatile(
        "\tmov rsi, %[inp_str]\n"
        "\tmov rdi, %[res]\n"
        "\tstr_loop:\n"
        "\tlodsb\n" // Load symbol
        "\tcmp al, 0\n"
        "\tje end\n"
        "\tcmp al, -48\n"
        "\tje vowel_check\n"
        "\tcmp al, -47\n"
        "\tje vowel_check\n"
        "\tcmp al, '0'\n"
        "\tjl set_symbol \n"
        "\tcmp al, '9'\n"
        "\tjle str_loop \n"
        "\tcmp al, 'A'\n"
        "\tjl set_symbol \n"
        "\tcmp al, 'Z'\n"
        "\tjle str_loop \n"
        "\tcmp al, 'a'\n"
        "\tjl set_symbol\n"
        "\tcmp al, 'z'\n"
        "\tjle str_loop\n  "

        "\tset_symbol:\n" // Symbol insertion in res
        "\tstosb\n"
        "\tjmp str_loop\n"

        "\tvowel_check:\n"
        "\tstosb\n"
        "\tmov bl, al\n"
        "\tlodsb\n"
        "\tstosb\n"
        "\tmov bh, al\n"
        "\tmov rdx, rsi\n"
        "\tmov rsi, %[vowels]\n"

        "\tsearch:\n"
        "\tlodsw\n"
        "\tcmp ax, 0\n"
        "\tje recovery\n"
        "\tcmp ax, bx\n"
        "\tjne search\n"

        "\tinc %[vowels_num]\n"

        "\trecovery:\n"
        "\tmov rsi, rdx\n"
        "\tjmp str_loop\n"

        "\tend:\n"
        "\tstosb\n"
        : [res] "=m"(res), [vowels_num] "=m"(vowels_num)
        : [inp_str] "m"(input_str), [vowels] "c"(vowels));
    printf("%s\n", res);
    printf("%d\n", vowels_num);
    return 0;
}