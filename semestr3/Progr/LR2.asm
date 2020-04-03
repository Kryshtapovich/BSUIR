model small
.stack 100h
.data
    a dw ?
    b dw ?
    c dw ?
    d dw ?
    endl db 0dh, 0ah, '$'
    er db 'Bad input$'
.code
main:
    mov ax, @data
    mov ds, ax
    
    call Input
    mov a, ax

    call Input
    mov b, ax

    call Input
    mov c, ax

    call Input
    mov d, ax

    xor ax, ax
    mov bx, b
    add bx, a
    mov dx, d
    add dx, c
    cmp bx, dx
    jz ExternalEqual
    jmp ExternalNotEqual

    ExternalEqual:
    mov ax, a
    xor ax, b
    mov cx, c
    and cx, d
    add ax, cx

    call Output
    jmp Fin

    ExternalNotEqual:
    mov ax, a
    or ax, b
    mov cx, c
    and cx, d
    cmp ax, cx
    jz InternalEqual
    jmp InternalNotEqual

    InternalEqual:
    xor bx, bx
    mov bx, b
    add bx, a
    xor cx, cx
    mov cx, c
    xor cx, d
    and bx, cx
    xor ax, ax
    mov ax, bx
   
    call Output
    jmp Fin

    InternalNotEqual:
    xor ax, ax
    mov ax, a
    add ax, d
    xor bx, bx
    mov bx, b
    add bx, c
    or ax, bx
    
    call Output

    Fin:
    mov al, 0
    mov ah, 4ch
    int 21h

Input proc
    mov bx, 10
    xor dx, dx

    DigitsIn:
    mov ah, 01h
    int 21h
    xor ah, ah
    cmp al, 0dh
    jz Final
    cmp al, 0ah
    jz Final
    cmp al, '0'
    jb Error
    cmp al, '9'
    ja Error
    mov cl, al
    sub cl, '0'
    mov ax, dx
    mul bx
    add ax, cx
    mov dx, ax
    jmp DigitsIn

    Error:
    mov ah, 09h
    mov dx, offset endl
    int 21h
    mov ah, 09h
    mov dx, offset er
    int 21h
    mov al, 0
    mov ah, 4ch
    int 21h

    Final:
    mov ax, dx
    ret
    Input endp

Output proc
    mov bx, 10
    mov cx, 0

    DigitsOut:
    mov dx, 0
    div bx
    push dx
    inc cx
    cmp ax, 0
    jnz DigitsOut    

    mov ah, 02h
    print:
    pop dx
    add dl, '0'
    int 21h
    loop print

    ret
    Output endp

end main