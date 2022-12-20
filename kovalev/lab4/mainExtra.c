#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2. Формирование выходной строки только из цифр
// и латинских букв входной строки.

int solveASM(char *str);

void checkAsmWithC();

int main(void) {
  checkAsmWithC();

  char userInput[81];
  printf("Ковалев Павел, вариант 2; Введите строку: ");
  fgets(userInput, 80, stdin);
  userInput[80] = '\0';

  int res = solveASM(userInput);

  FILE *f = fopen("result.txt", "w");
  fprintf(f, "%d\n", res);
  fclose(f);

  return EXIT_SUCCESS;
}

int solveASM(char *str) {
  char *tmp = calloc(81, sizeof(char));
  size_t res = 0;
  asm volatile("    cld                         \n\t"
               "    mov rsi, %[str]             \n\t"
               "    mov rdi, %[tmp]             \n\t"
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
               "    push rcx                    \n\t"
               "    and bl, 0x1f                \n\t"
               "    mov cl, bl                  \n\t"
               "    mov rdx, 0x2208222           \n\t"
               "    sar edx, cl                 \n\t"
               "    and rdx, 1                  \n\t"
               "    add %[res], rdx             \n\t"
               "    pop rcx                     \n\t"
               "write:                          \n\t"
               "    stosb                       \n\t"
               "    loop mainLoop               \n\t"

               : [res] "+r"(res)
               : [str] "r"(str), [tmp] "r"(tmp)
               : "rax", "rbx", "rcx", "rdx", "rdi", "rsi", "memory", "cc");
  return res;
}

void checkAsmWithC() {
  struct test {
    char *str;
    int res;
  } tests[] = {
      {"test1", 1},        {"TEST1", 1},
      {"$test2", 1},       {"##te#&#st3^^^^", 1},
      {"$test*4*9", 1},    {"t0estПРЛИ", 1},
      {"test((478%%%", 1}, {"THis is test string000---)))", 4},
      {"aeiou", 5},        {"aeioufdfstgh", 5},
      {"aeioyu", 6},       {"rraewwwirrrowwywwuwww", 6},
  };

  const size_t testCount = sizeof(tests) / sizeof(struct test);
  for (size_t i = 0; i < testCount; ++i) {
    int res = solveASM(tests[i].str);

    if (res != tests[i].res) {
      printf("Failed test: solveASM(\"%s\"). Got = %d; expected = %d\n",
             tests[i].str, res, tests[i].res);
    }
  }
}
