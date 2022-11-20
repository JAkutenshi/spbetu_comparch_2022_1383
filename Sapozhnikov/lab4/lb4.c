#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * translitirate(char * str) {
	char *res = (char *) calloc(81, sizeof(char));
	char translit []= {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0x80, 0x81, 0x91, 0x84, 0x85, 0x94, 0x83, 0x95, 0x88, 0x86, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E,
		0x8F, 0x8A, 0x90, 0x91, 0x92, 0x9E, 0x82, 0x82, 0x95, 0x93, 0x87, 0, 0, 0, 0, 0,
		0, 0xA0, 0xA1, 0xE1, 0xA4, 0xA5, 0xE4, 0xA3, 0xE5, 0xA8, 0xA6, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE,
		0xAF, 0xAA, 0xE0, 0xE1, 0xE2, 0xEE, 0xA2, 0xA2, 0xE5, 0xE3, 0xA7, 0, 0, 0, 0, 0
	};

	asm volatile(
		"cld							\n\t"
		"mov rsi, %[str]				\n\t"
		"mov rdi, %[res]				\n\t"
		"mov rcx, 80					\n\t"
		"_loop:							\n\t"
		"	mov rax, 0					\n\t"
		"	lodsb						\n\t"
		"	cmp al, 0					\n\t"
		"	jne _check					\n\t"
		"	mov rcx, 1					\n\t"
		"	jmp _write					\n\t"
		"_check:						\n\t"
		"	cmp al, 127					\n\t"
		"	ja _write					\n\t"
		"	mov rdx, rax				\n\t"
		"	mov rbx, rsi				\n\t"
		"	mov rsi, rax				\n\t"
		"	mov rax, [%[tr] + rsi]		\n\t"
		"	mov rsi, rbx				\n\t"
		"	cmp al, 0					\n\t"
		"	jne _write					\n\t"
		"	mov rax, rdx				\n\t"
		"_write:						\n\t"
		"	stosb						\n\t"
		"	loop _loop					\n\t"
		:[res] "=m"(res)
		:[str] "r"(str),
		[tr] "r"(translit)
		:"rax", "rbx", "rcx", "rdx", "rdi", "rsi", "memory", "cc"
	);
	res[80] = '\0';
	return res;
}

int main() {
	printf("A.Sapozhnikov - 1383");
	printf("Conversion of Latin letters entered in the input string into Russian ones in accordance with the transliteration rules, the remaining characters of the input string are transmitted to the output string directly\n");
	char *inp = (char *) calloc(81, sizeof(char));
	fgets(inp, 80, stdin);
	inp[80] = '\0';

	char *res = translitirate(inp);
	printf("%s\n", res);

	free(inp);
	free(res);
	return 0;
}
