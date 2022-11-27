#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * translitirate(char * str) {
	char *res = (char *) calloc(81, sizeof(char));
	char translit []= {
		/*
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,*/
		0xD0, 0x90, // A->А
		0xD0, 0x91, // B->Б
		0xD0, 0xA1, // C->С
		0xD0, 0x94, // D->Д
		0xD0, 0x95, // E->Е
		0xD0, 0xA4, // F->Ф
		0xD0, 0x93, // G->Г
		0xD0, 0xA5, // H->Х
		0xD0, 0x98, // I->И
		0xD0, 0x96, // J->Ж
		0xD0, 0x9A, // K->К
		0xD0, 0x9B, // L->Л
		0xD0, 0x9C, // M->М
		0xD0, 0x9D, // N->Н
		0xD0, 0x9E, // O->О
		0xD0, 0x9F, // P->П
		0xD0, 0x9A, // Q->К
		0xD0, 0xA0, // R->Р
		0xD0, 0xA1, // S->С
		0xD0, 0xA2, // T->Т
		0xD0, 0xAE, // U->Ю
		0xD0, 0x92, // V->В
		0xD0, 0x92, // W->В
		0xD0, 0xA5, // X->Х
		0xD0, 0xA3, // Y->У
		0xD0, 0x97, // Z->З
		/*
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0xD0, 0xB0, // a->а
		0xD0, 0xB1, // b->б
		0xD1, 0x81, // c->с
		0xD0, 0xB4, // d->д
		0xD0, 0xB5, // e->е
		0xD1, 0x84, // f->ф
		0xD0, 0xB3, // g->г
		0xD1, 0x85, // h->х
		0xD0, 0xB8, // i->и
		0xD0, 0xB6, // j->ж
		0xD0, 0xBA, // k->к
		0xD0, 0xBB, // l->л
		0xD0, 0xBC, // m->м
		0xD0, 0xBD, // n->н
		0xD0, 0xBE, // o->о
		0xD0, 0xBF, // p->п
		0xD0, 0xBA, // q->к
		0xD1, 0x80, // r->р
		0xD1, 0x81, // s->с
		0xD1, 0x82, // t->т
		0xD1, 0x8E, // u->ю
		0xD0, 0xB2, // v->в
		0xD0, 0xB2, // w->в
		0xD1, 0x85, // x->х
		0xD1, 0x83, // y->у
		0xD0, 0xB7, // z->з
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0
		*/
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
		"	cmp al, 122					\n\t" // > 'z'
		"	ja _write					\n\t"
		"	cmp al, 65					\n\t" // < 'A'
		"	jb _write					\n\t"
		"	sub al, 91					\n\t"
		"	cmp al, 6					\n\t" // 'Z' < [sym] < 'a'
		"	jb _write_btw				\n\t"
		"	add al, 26					\n\t"
		"	mov rdx, rax				\n\t"
		"	mov rbx, rsi				\n\t"
		"	cmp al, 27					\n\t"
		"	jb _transliterate_u			\n\t"
		"	sub rax, 32					\n\t"
		"	jmp _transliterate_l		\n\t"
		"_transliterate_u:				\n\t"
		"	mov rsi, rax				\n\t"
		"	mov rax, [%[tr] + rsi * 2]	\n\t"
		"	jmp _write2					\n\t"
		"_transliterate_l:				\n\t"
		"	mov rsi, rax				\n\t"
		"	mov rax, [%[tr] + rsi * 2]	\n\t"
		"	jmp _write2					\n\t"
		"_write_btw:					\n\t"
		"	add rax, 91					\n\t"
		"_write:						\n\t"
		"	stosb						\n\t"
		"	jmp _next					\n\t"
		"_write2:						\n\t"
		"	mov rsi, rbx				\n\t"
		"	stosw						\n\t"
		"_next:							\n\t"
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
	printf("A.Sapozhnikov - 1383\n");
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
