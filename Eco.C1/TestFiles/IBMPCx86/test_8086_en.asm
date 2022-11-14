.8086
.CODE
        ORG 07c00h
main:   jmp short start
        nop
start:  mov driveNumber, dl
        cli
        mov ax, cs
        mov ds, ax
        mov es, ax
        mov ss, ax
        sti
        cld
        mov si, offset text
        mov ah, 0Eh
lww:     lodsb
        test al, al
        jz exxx
        int 10h
        jmp short lww
exxx:    mov ax, 0E20h
        int 10h
        call printText
        call printText
reset:  mov ah, 0h
        mov dl, driveNumber
        int 13h
        js reset
read:   mov ax, 7e00h
        mov es,ax
        mov bx, 0
        mov ah,02h
        mov al,10h
        mov ch,00h
        mov cl,02h
        mov dh,00h
        mov dl, driveNumber
        int 13h
        jc read
        mov ax, 0E65h
        int 10h
        mov ax, 0E32h
        int 10h
        cli
        hlt
printText PROC NEAR
        mov si, offset text
        mov ah, 0Eh
lwww:     lodsb
        test al, al
        jz exxxx
        int 10h
        jmp short lwww
exxxx:    mov ax, 0E20h
        int 10h
        ret
printText ENDP
.DATA
    driveNumber db ?
    text db "Welcome to EcoOS!"
    db  443 DUP (0)
    db  55h
    db  0AAh

