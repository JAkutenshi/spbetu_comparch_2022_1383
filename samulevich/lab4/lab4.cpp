#include <stdio.h>
#include <windows.h>

char input[100];
char output[100];
char lat[] = "ABVGDEZhZIJKLMNOPRSTUFHTsChShShchYEYuYaabvgdezhzijklmnoprstufhtschshshchyeyuya";

int main() {
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
fgets(input, 100, stdin);

_asm {
push ds
pop es
sub cx, cx
mov eax, 0
mov ecx, 0
mov esi, offset input
mov edi, offset output
jmp start

mov0 :
jmp start

mov1 :
lodsb
stosb
jmp start

mov2 :
lodsb
stosb
lodsb
stosb
jmp start

mov4 :
lodsb
stosb
lodsb
stosb
lodsb
stosb
lodsb
stosb
jmp start

start :
mov esi, offset input
add esi, ecx
lodsb
add cx, 1
cmp al, '\0'
je end1

cmp al, 184
jne nYOs
mov al, 101
stosb
jmp start

nYOs:

cmp al, 168
jne nYOb
mov al, 69
stosb
jmp start

nYOb:

sub al, 192

cmp al, 0
jge aA
add al, 192
stosb
jmp start
aA :
cmp al, 63
jle bYa
add al, 192
stosb
jmp start
bYa :

mov bl, al
cmp al, 32
jge sm
jmp read
sm:
add al, 7
sub bl, 32

read:
mov esi, offset lat
add esi, eax

cmp bl, 6
je mov2
jl end
add esi, 1

cmp bl, 22
je mov2
jl end
add esi, 1

cmp bl, 23
je mov2
jl end
add esi, 1

cmp bl, 24
je mov2
jl end
add esi, 1

cmp bl, 25
je mov4
jl end
add esi, 3

cmp bl, 26
je start
jl end
sub esi, 1

cmp bl, 28
je start
jl end
sub esi, 1


cmp bl, 30
je mov2
jl end
add esi, 1

cmp bl, 31
je mov2
jl end

end :
jmp mov1

end1 :

}
printf("%s", output);

}