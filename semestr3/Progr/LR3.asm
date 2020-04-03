model small
.stack 100h
.data
    a dw ?
    b dw ?
    c dw ?
    d dw ?
    delimoe dw ?
    delitel dw ?
    result dw ?
    ostatok dw ?
    minus db ?
    endl db 0dh, 0ah, '$'
    er db 'Bad input$'
    zero db 'Zero division$'
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

    mov ax, a
    cmp ax, b
    jl Internal
    jz Internal

    mov ax, c
    sub ax, d
    add ax, a 

    call Output
    jmp Finish

    ZeroDivision:
    mov ah, 09h
    mov dx, offset zero
    int 21h
    jmp Finish

    Internal:
    cmp d, 0
    jz ZeroDivision
    mov cx, a
    sub cx, b
    mov ax, c
    mov bx, d
    call Division
    mov ax, result
    cmp cx, ax
    jg InternalElse
    jz InternalElse

    cmp a, 0
    jz ZeroDivision
    mov ax, c
    mov bx, a
    call Division
    mov dx, ostatok
    mov ax, b
    sub ax, dx

    call Output
    jmp Finish

    InternalElse:
    mov ax, c
    sub ax, a
    add ax, d

    call Output
    Finish:
    mov al, 0
    mov ah, 4ch
    int 21h

Output proc
    test ax, ax
    jns Skip
    mov bx, ax
    neg bx
    mov ah, 02h
    mov dl, '-'
    int 21h
    mov ax, bx
    Skip:
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

Input proc
    mov bx, 10
    xor dx, dx

    mov ah, 01h
    int 21h
    cmp al, '-'
    jnz Digits
    mov minus, '-'

    DigitsIn:
    mov ah, 01h
    int 21h
    cmp al, 0dh
    jz Final
    cmp al, 0ah
    jz Final
    Digits:
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
    cmp minus, '-'
    jnz Exit
    neg ax
    Exit:
    mov minus, 0
    ret
    Input endp

Division proc; r = a - [a/b] * b
    mov delimoe, ax
    mov delitel, bx

    cwd
    idiv bx
    test bx, delimoe
    js Other
    cmp ax, 0;если в результате деления чисел разных знаков 0, то делаем -1
    jz Nol
    test ax, ax
    jns Other
    cmp dx, 0
    jz Other
    Nol:
    dec ax
    Other:
    imul bx
    neg ax
    add ax, delimoe
    mov ostatok, ax
    
    mov ax, delimoe
    sub ax, ostatok
    cwd 
    idiv delitel
    mov result, ax
    Fin:
    ret
    Division endp
end main