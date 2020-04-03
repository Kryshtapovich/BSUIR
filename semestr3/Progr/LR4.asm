model small
.stack 100h
.data
    string db 50 dup('$')
    substring db 50 dup('$')
    stringlength dw 0
    sublength dw 0
    arrpi db 50 dup('$')
    endl db 0dh, 0ah, '$'
    yes db 'yes$'
    no db 'no$'
.code
main:

    mov ax, @data
    mov ds, ax

    call Input

    call PI

    call Compare

    mov al, 0
    mov ah, 4ch
    int 21h

Input proc
    lea si, substring
    
    ReadSubstring:
    mov ah, 01h
    int 21h
    cmp al, ' '
    jz StopReadSubstring
    mov [si], al
    inc si
    inc sublength
    jmp ReadSubstring
    StopReadSubstring:

    lea si, string

    ReadString:
    mov ah, 01h
    int 21h
    cmp al, 0dh
    jz StopReadString
    cmp al, 0ah
    jz StopReadString
    mov [si], al
    inc si
    inc stringlength
    jmp ReadString
    StopReadString:

    mov stringlength, si

    Final:
    ret
Input endp

PI proc
    xor ax, ax
    mov cx, sublength

    mov si, 1
    mov bx, 0

    mov arrpi[0], 0
    FillingPiArray:
    cmp cx, 1
    jz Finish
    mov al, substring[si]
    cmp al, substring[bx]
    jnz NotEqual
    inc bx
    mov arrpi[si], bl
    inc si
    dec cx
    jmp FillingPiArray

    NotEqual:
    cmp bx, 0
    jz EqualZero
    mov bl, arrpi[bx - 1]
    jmp FillingPiArray

    EqualZero:
    mov arrpi[si], 0
    inc si
    dec cx
    jmp FillingPiArray

    Finish:
    ret
PI endp

Compare proc

    mov si, 0
    mov bx, 0

    Matching:
    cmp si, stringlength 
    jz NotFinded
    mov al, string[si]
    cmp al, substring[bx]
    jnz NotMatch
    inc si
    inc bx
    cmp bx, sublength 
    jz Finded
    jmp Matching
    NotMatch:
    cmp bx, 0
    jnz NotNull
    inc si
    jmp Matching
    NotNull:
    mov bl, arrpi[bx - 1]
    jmp Matching
    
    Finded:
    mov ah, 09h
    mov dx, offset endl
    int 21h
    mov dx, offset yes
    int 21h
    jmp Stop
   
    NotFinded:
    mov ah, 09h
    mov dx, offset endl
    int 21h
    mov dx, offset no
    int 21h

    Stop:
    ret
Compare endp
end main