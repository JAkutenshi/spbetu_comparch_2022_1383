#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 81

int main()
{
    char *input_str = (char *)malloc((MAXLEN) * sizeof(char));
    char *res = (char *)malloc((MAXLEN) * sizeof(char));
    printf("Малых Андрей, группа 1383.\nИсключение латинских букв и цифр, введенных во входной строке при формировании выходной строки.\n");
    fgets(input_str, MAXLEN, stdin);
    input_str[strlen(input_str) - 1] = '\0';
    __asm__ volatile(
        "mov rsi, %[inp_str]\n" //
        "\tmov rdi, %[res]\n"
        "\tstr_loop:\n"
        "\tlodsb\n"  // Load symbol
        "\tcmp al, '0'\n" 
        "\tjl set_symbol \n"            
        "\tcmp al, '9'\n"                 
        "\tjle check_null_terminator \n"  
        "\tcmp al, 'A'\n"                 
        "\tjl set_symbol \n"             
        "\tcmp al, 'Z'\n"                 
        "\tjle check_null_terminator \n"  
        "\tcmp al, 'a'\n"                 
        "\tjl set_symbol\n"              
        "\tcmp al, 'z'\n"                
        "\tjle check_null_terminator\n  " 
        "\tset_symbol:\n" // Symbol insertion in res
        "\tstosb\n"  
        "\tcheck_null_terminator:\n"
        "\tcmp al, 0\n"
        "\tjne str_loop\n"
        : [res] "=m"(res)
        : [inp_str] "m"(input_str));
    printf("%s\n", res);
    return 0;
}