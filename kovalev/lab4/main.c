#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2. Формирование выходной строки только из цифр
// и латинских букв входной строки.

char *solveASM(char *str);

void checkAsmWithC();

int main(void) {
  checkAsmWithC();

  char userInput[81];
  printf("Ковалев Павел, вариант 2; Введите строку: ");
  fgets(userInput, 80, stdin);
  userInput[80] = '\0';

  char *res = solveASM(userInput);

  FILE *f = fopen("result.txt", "w");
  fprintf(f, "%s\n", res);
  fclose(f);

  free(res);

  return EXIT_SUCCESS;
}

char *solveASM(char *str) {
  char *res = calloc(81, sizeof(char));
  asm volatile("    cld                         \n\t"
               "    mov rsi, %[str]             \n\t"
               "    mov rdi, %[res]             \n\t"
               "    mov rcx, 80                 \n\t"
               "mainLoop:                       \n\t"
               "    lodsb                       \n\t"
               "    cmp al, 0                   \n\t"
               "    jne check                   \n\t"
               "    mov rcx, 1                  \n\t"
               "    jmp write                   \n\t"
               "check:                          \n\t"
               "    cmp al, '0'                 \n\t"
               "    jl mainLoop                 \n\t"
               "    cmp al, '9'                 \n\t"
               "    jle write                   \n\t"
               "    mov bl, al                  \n\t"
               "    or bl, 0x20                 \n\t"
               "    cmp bl, 'a'                 \n\t"
               "    jl mainLoop                 \n\t"
               "    cmp bl, 'z'                 \n\t"
               "    jg mainLoop                 \n\t"
               "write:                          \n\t"
               "    stosb                       \n\t"
               "    loop mainLoop               \n\t"

               ::[str] "r"(str),
               [res] "r"(res)
               : "rax", "rbx", "rcx", "rdi", "rsi", "memory", "cc");
  return res;
}

void checkAsmWithC() {
  struct test {
    char *str;
    char *res;
  } tests[] = {
      {"test1", "test1"},
      {"$test2", "test2"},
      {"##te#&#st3^^^^", "test3"},
      {"t0estПРЛИ", "t0est"},
      {"test((478%%%", "test478"},
      {"THis is test string000---)))", "THisisteststring000"},
  };

  const size_t testCount = sizeof(tests) / sizeof(struct test);
  for (size_t i = 0; i < testCount; ++i) {
    char *res = solveASM(tests[i].str);

    if (strncmp(res, tests[i].res, 80)) {
      printf("Failed test: solveASM(\"%s\"). Got = \"%s\"; expected = \"%s\"\n",
             tests[i].str, res, tests[i].res);

      free(res);

      exit(EXIT_FAILURE);
    }

    free(res);
  }
}
