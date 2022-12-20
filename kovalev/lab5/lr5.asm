intNum EQU 08h
BEEP_TONE EQU 20
BEEP_DURATION EQU 500

ASTACK SEGMENT STACK
  DB 2048 DUP(?)
ASTACK ENDS

DATA SEGMENT

keep_cs DW 0
keep_ip DW 0
msgHello DB 'Program enables sound.', 10, 13, '$'
msgBye   DB 'Program finished.', 10, 13, '$'
check DW 300

DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:ASTACK

MAIN PROC FAR
    push ds                     ; Initialize program
    xor ax, ax                  ;
    push ax                     ;
    mov ax, DATA                ;
    mov ds, ax                  ; ---

    mov dx, OFFSET msgHello
    mov ah, 09h
    int 21h

    call SET_USER_TABLE

endlessness:
    cmp BYTE PTR [check], 0
    jne endlessness

    call RESTORE_TABLE

    mov dx, OFFSET msgBye
    mov ah, 09h
    int 21h

    ret
MAIN ENDP

SUBR_INT PROC FAR
    push ax
    push cx

    mov al, 20h
    out 20h, al

    dec WORD PTR [check]

    mov al, BEEP_TONE
    out 42h, al
    in al, 61h
    or al, 3
    out 61h, al

    mov cx, BEEP_DURATION
sound:
    loop sound

    xor al, 3
    out 61h, al

    pop cx
    pop ax
    iret
SUBR_INT ENDP

RESTORE_TABLE PROC NEAR
    push dx
    push ax

    cli                         ; Interrupt protection; Clear Interrupt Flag
    push ds                     ; Save ds
    mov  dx, keep_ip            ; Restore original ip and cs values
    mov  ax, keep_cs            ;
    mov  ds, ax                 ;
    mov  ah, 25h                ; ---
    mov  al, intNum             ; Restore original handler
    int  21h                    ; ---
    pop  ds                     ; Restore ds
    sti                         ; Interrupt protection; -> cli

    pop ax
    pop dx
    ret
RESTORE_TABLE ENDP

SET_USER_TABLE PROC NEAR
    push ax
    push dx

    mov  ah, 35h                ; Save ip and cs values
    mov  al, 1ch                ; before registering a new one
    int  21h                    ;
    mov  keep_ip, bx            ;
    mov  keep_cs, es            ; ---

    push ds                     ; Set interruption handler
    mov  dx, OFFSET subr_int    ; proc offset
    mov  ax, SEG subr_int       ; ax = proc segment
    mov  ds, ax                 ; ds = ax
    mov  ah, 25h                ; Set function
    mov  al, intNum             ; Set int handler number
    int  21h                    ; Change handler
    pop  ds                     ; Restore original ds

    pop dx
    pop ax
    ret
SET_USER_TABLE ENDP
CODE ENDS
END MAIN
