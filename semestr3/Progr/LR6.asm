.model small
.stack 1000
.data
    old dd 0 
.code
.486
    cipherFlag db 1
    shiftFlag db 0
    firstFlag db 0
    cipherKey db 3
    num dw 0
    aplhSize dw 26
 
CaesarCipher proc      
    push ds si es di dx cx bx ax 
    xor dx,dx
    xor si, si
    mov di,10
    cmp firstFlag, 1
    jz Input
    

    xor ax,ax
    xor cx, cx
    xor dx, dx
    xor bx, bx
    in ax, 60h
    
    cmp al, 28
    jz Endpr
    
    cmp al, 11
    mov cl, 0
    jz vichislen
    
    cmp al, 2
    mov cl, 1
    jz vichislen  
   
    cmp al, 3
    mov cl, 2
    jz vichislen
   
    cmp al, 4
    mov cl, 3
    jz vichislen
   
    cmp al, 5
    mov cl, 4
    jz vichislen
   
    cmp al, 6
    mov cl, 5
    jz vichislen 

    cmp al, 7
    mov cl, 6
    jz vichislen
    
    cmp al, 8
    mov cl, 7
    jz vichislen
    
    cmp al, 9
    mov cl, 8
    jz vichislen
    
    cmp al, 10
    mov cl, 9
    jz vichislen
    
    jmp Exit
    
vichislen:     
    mov ax, num
    mul di
    mov dx, cx
    add ax,cx
    
    mov cx, ax
    
    add dx, '0'
    mov ah, 02h
    int 21h

    mov num, cx
    
    jmp Exit
    
Endpr: 
    mov ax, num
    xor dx, dx
    div aplhSize
    mov cipherKey, dl
    mov firstFlag, 1
    jmp EnterKey   
      
    
Input:        
    xor ax, ax 
    xor dx, dx
    xor bx, bx
    in  ax, 60h        

    cmp al, 57
    mov bl, al  
    mov al, 32 
    jz Final
        
    mov al,bl
    cmp al, 28        
    jz EnterKey
        
    cmp al, 1
    jz SwitchEncryption
        
    cmp al,42
    jz SwitchShift
        
    cmp al,170
    jz SwitchShift
        
        
    cmp al, 30 
    mov bl, al  
    mov al, 97
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 48
    mov bl, al  
    mov al, 98
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 46
    mov bl, al  
    mov al, 99
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 32
    mov bl, al  
    mov al, 100
    jz CheckShift     
        
        
    mov al, bl
    cmp al, 18
    mov bl, al  
    mov al, 101
    jz CheckShift 
        

    mov al, bl
    cmp al, 33
    mov bl, al  
    mov al, 102
    jz CheckShift 
        

    mov al, bl
    cmp al, 34
    mov bl, al  
    mov al, 103
    jz CheckShift
       
       
    mov al, bl
    cmp al, 35
    mov bl, al  
    mov al, 104
    jz CheckShift
      

    mov al, bl
    cmp al, 23
    mov bl, al  
    mov al, 105
    jz CheckShift 
      
      
    mov al, bl
    cmp al, 36
    mov bl, al  
    mov al, 106
    jz CheckShift 
      
    mov al, bl
    cmp al, 37
    mov bl, al  
    mov al, 107
    jz CheckShift 
      
      
    mov al, bl
    cmp al, 38
    mov bl, al  
    mov al, 108
    jz CheckShift  
       
       
    mov al, bl
    cmp al, 50
    mov bl, al  
    mov al, 109
    jz CheckShift  
        
        
    mov al, bl
    cmp al, 49
    mov bl, al  
    mov al, 110
    jz CheckShift  
        
        
    mov al, bl
    cmp al, 24
    mov bl, al  
    mov al, 111
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 25
    mov bl, al  
    mov al, 112
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 16
    mov bl, al  
    mov al, 113
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 19
    mov bl, al  
    mov al, 114
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 31
    mov bl, al  
    mov al, 115
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 20
    mov bl, al  
    mov al, 116
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 22
    mov bl, al  
    mov al, 117
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 47
    mov bl, al  
    mov al, 118
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 17
    mov bl, al  
    mov al, 119
    jz CheckShift 
        

    mov al, bl
    cmp al, 45
    mov bl, al  
    mov al, 120
    jz CheckShift 
        

    mov al, bl
    cmp al, 21
    mov bl, al  
    mov al, 121
    jz CheckShift 
        
        
    mov al, bl
    cmp al, 44
    mov bl, al  
    mov al, 122
    jz CheckShift 
        


    mov al, bl 
    cmp al, 11
    mov bl, al  
    mov al, 48
    jz CheckDigitsEncryption 
               
    mov al, bl
    cmp al, 2
    mov bl, al  
    mov al, 49
    jz CheckDigitsEncryption 
        
    mov al, bl
    cmp al, 3
    mov bl, al  
    mov al, 50
    jz CheckDigitsEncryption 
        
    mov al, bl
    cmp al, 4
    mov bl, al  
    mov al, 51
    jz CheckDigitsEncryption 
        
    mov al, bl
    cmp al, 5
    mov bl, al  
    mov al, 52
    jz CheckDigitsEncryption 
        
    mov al, bl
    cmp al, 6
    mov bl, al  
    mov al, 53
    jz CheckDigitsEncryption 
               
    mov al, bl
    cmp al, 7
    mov bl, al  
    mov al, 54
    jz CheckDigitsEncryption 
        
    mov al, bl
    cmp al, 8
    mov bl, al  
    mov al, 55
    jz CheckDigitsEncryption 
        
    mov al, bl
    cmp al, 8
    mov bl, al  
    mov al, 56
    jz CheckDigitsEncryption 
        
    mov al, bl
    cmp al, 10
    mov bl, al  
    mov al, 57
    jz CheckDigitsEncryption 

    jmp Exit


CheckDigitsEncryption:
    cmp cipherFlag,0
    jz Final
    jmp DigitsEncryption
    
    
CheckLowLettersEncryption:
    cmp cipherFlag,0
    jz Final
    jmp LowLetters

    
CheckhighLettersEncryption:
    cmp cipherFlag,0
    jz Final
    jmp highLetters    
    

CheckShift:        
    cmp shiftFlag,0
    jz CheckLowLettersEncryption
    sub al, 20h 
    jmp CheckhighLettersEncryption   
        
SwitchEncryption:
    cmp cipherFlag,1
    jz OffEncryption
    mov cipherFlag,1    
    jmp Exit


OffEncryption:
    mov cipherFlag,0    
    jmp Exit



SwitchShift:
    cmp shiftFlag,1
    jz OffShift
    mov shiftFlag,1    
    jmp Exit


OffShift:
    mov shiftFlag,0    
    jmp Exit    
    

EnterKey:
    mov dl, 0ah
    mov ah, 02h
    int 21h
    jmp Exit

    
Final:
    mov dl, al
    mov ah, 02h
    int 21h
    jmp Exit 


DigitsEncryption:
   add al, cipherKey
DigitsCheck:   
   cmp al, 57
   ja DigitsCycle 
   jmp  Final
DigitsCycle: 
   sub al, 58
   add al, 48
   jmp DigitsCheck   
   
   
   
LowLetters:
   add al, cipherKey
   cmp al, 122
   ja  LowLettersCycle
   jmp Final
LowLettersCycle:  
   sub al, 123
   add al, 97
   jmp Final
   
   
   
highLetters:
   add al, cipherKey
   cmp al, 90 
   ja highLettersCycle
   jmp  Final 
highLettersCycle:   
   sub al, 91
   add al, 65
   jmp Final


Exit:
    xor ax, ax
    mov al, 20h
    out 20h, al 
    pop ax bx cx dx di es si ds 
    iret
CaesarCipher endp
 

NewEnd:
 
Main:
    mov ax, @data
    mov ds, ax
         
    push 0        
    pop ds
    mov eax, ds:[09h*4] 
    mov cs:[old], eax 
        
    mov ax, cs
    shl eax, 16
    mov ax, offset CaesarCipher
    mov ds:[09h*4], eax 
        
    xor ax, ax
    mov ah, 31h
    mov dx, (NewEnd - @code + 10fh) / 16 
    int 27h

end Main