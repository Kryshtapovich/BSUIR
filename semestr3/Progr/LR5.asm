model small
.stack 100h
.data
    dimension dw ?
    arrlength dw ?
    array db 100 dup(?)
    endl db 0dh, 0ah, '$'
    i dw ?
    j dw ?
    temp1 db ?
    temp2 db ?
    min db ?
    lim dw ?
.code
main:
    mov ax, @data
    mov ds, ax

    call ReadNumber
    mov dimension, dx
    mov ax, dimension
    mul dimension
    dec ax
    mov arrlength, ax

    call ReadMatrix

    call ProcessMatrix

    call WriteMatrix

    mov al, 0
    mov ah, 4ch
    int 21h

ReadNumber proc
    mov bx, 10
    xor dx, dx

    DigitsIn:
    mov ah, 01h
    int 21h
    xor ah, ah
    cmp al, ' '
    jz Final
    cmp al, 0dh
    jz Final
    cmp al, 0ah
    jz Final
    mov cl, al
    sub cl, '0'
    mov ax, dx
    mul bx
    add ax, cx
    mov dx, ax
    jmp DigitsIn

    Final:
    ret
ReadNumber endp   

WriteNumber proc
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
    
    mov ax, 0
    ret
WriteNumber endp

ReadMatrix proc
    mov si, 0

    Reading:
    call ReadNumber
    mov array[si], dl
    cmp si, arrlength
    jz StopReading
    inc si
    jmp Reading

    StopReading:
    ret 
ReadMatrix endp

ProcessMatrix proc ;a[i][j] = min(a[i][j], a[i][k] + a[k][j])
    mov di, 0
    push dimension
    pop lim
    dec lim

    StartProcessing:
    mov si, 0   
    Processing:
    call ProcessElemnt
    mov al, min
    mov array[si], al
    cmp si, arrlength
    jz NextIteration
    inc si
    jmp Processing
    NextIteration:
    cmp di, lim
    jz StopProcessing
    inc di
    jmp StartProcessing

    StopProcessing:
    ret
ProcessMatrix endp

ProcessElemnt proc ;min(a[i][j], a[i][k] + a[k][j])
    mov ax, si
    div dimension
    mov i, ax
    mov j, dx

    mov ax, i
    mul dimension
    add ax, di
    mov bx, ax
    mov cl, array[bx]
    mov temp1, cl

    mov ax, di
    mul dimension
    add ax, j
    mov bx, ax
    mov cl, array[bx]
    mov temp2, cl

    mov al, temp1
    add al, temp2
    mov bl, array[si]

    cmp al, bl
    ja Second 
    mov min, al
    jmp ProcessingOut
    Second:
    mov min, bl

    ProcessingOut:
    ret
ProcessElemnt endp

WriteMatrix proc
    mov si, 0

    Writing:
    mov al, array[si]
    call WriteNumber
    call Space
    cmp si, arrlength
    jz StopWriting
    inc si
    jmp Writing

    StopWriting:
    ret
WriteMatrix endp

Space proc
    push ax
    mov dx, 0
    inc si

    mov ax, si
    div dimension
    cmp dx, 0
    jz NewLine
    mov ah, 02h
    mov dx, ' '
    jmp Stop

    NewLine:
    mov ah, 09h
    mov dx, offset endl

    Stop:
    int 21h
    pop ax
    dec si
    ret
Space endp



end main