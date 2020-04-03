model small
.stack 100h
.data
    a dw ?
    b dw ?
    c dw ?
    d dw ?
.code
main:
    mov ax, @data
    mov ds, ax

   ;<readABCD>

    mov ax, d
    mov ax, a
    mov bx, b
    or ax, c
    xor bx, d
    cmp ax, bx

    jz ExternalEqual
    jmp ExternalNotEqual

    ExternalEqual:
    mov ax, a
    xor ax, b
    xor ax, c
    add ax, d
    jmp fin

    ExternalNotEqual:
    mov ax, a
    add ax, b
    mov cx, c
    xor cx, d
    cmp ax, cx

    jz InternalEqual
    jmp InternalNotEqual

    InternalEqual:
    mov ax, a
    and ax, d
    mov bx, b
    add bx, c
    or ax, bx
    jmp fin

    InternalNotEqual:
    mov bx, b
    add bx, c
    xor bx, a
    or bx, d
    xor ax, ax
    mov ax, bx
    jmp fin

    fin:
    ;<print>

    mov al, 0
    mov ah, 4ch
    int 21h
end main