#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
	printf("Fdorova Oksana - 1383\nconvert letter into number in order\n");

	char *input_str = (char *) calloc(81, sizeof(char));
	fgets(input_str, 80, stdin);
	input_str[80] = '\0';
	for(int i = 0; i < 80; i++) {
		input_str[i] = tolower(input_str[i]);
	}

	char *res = (char *) calloc(81, sizeof(char));

	asm volatile(
		"mov rsi, %[str]				\n\t"//lodsb будет считывать с str
		"mov rdi, %[res]				\n\t"//stosb для заиси из ах в res
		"mov rcx, 80  					\n\t"
		"for:							\n\t"
		"	mov rax, 0					\n\t"
		"	lodsb						\n\t"
		"	cmp al, 0					\n\t"
		"	jne find					\n\t"
		"	mov rcx, 1					\n\t"
		"	jmp print					\n\t"
		"find:							\n\t"
		"	cmp al, 122					\n\t"
		"	ja print					\n\t"
		"	cmp al, 97					\n\t"
		"	jb print					\n\t"
		"	sub ax, 97					\n\t"
		"	mov bl, 16					\n\t"
		"	div bl						\n\t"
		"	add al, 48					\n\t"
		"	stosb						\n\t"
		"	mov al, ah					\n\t"
		"	cmp al, 9					\n\t"
		"	ja letter					\n\t"
		"	add al, 48					\n\t"
		"	jmp print					\n\t"
		"letter:						\n\t"
		"	sub al, 10					\n\t"
		"	add al, 65					\n\t"
		"	jmp print 					\n\t"
		"print:							\n\t"
		"	stosb						\n\t"
		"	loop for 					\n\t"
		:[res] "=m"(res)
		:[str] "r"(input_str)
		:"rax", "rbx", "rcx", "rdx", "rdi", "rsi", "memory", "cc"
	);
	res[80] = '\0';
	printf("%s\n", res);

	free(input_str);
	free(res);
	return 0;
}

