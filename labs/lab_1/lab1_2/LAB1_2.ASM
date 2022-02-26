.model small
.stack 100h

.data

Error_Write db "Write error!",0Dh,0Ah,'$'
Error_Read db "Read error!",0Dh,0Ah,'$'
Information db "Byte sent: $"
           
.code

jmp start

Init_COM1 proc
   xor ax,ax        ; ax is zero now
   mov al,10000011b ; set speed to 1200 bod, 11 - means that we send 8 bit data
   mov dx,0         ; port-transmitter number
   int 14h          ; use 0-function of 14 interruption
   ret            
Init_COM1 endp

Write_COM1 proc
   mov al,'X'       ; mov our character
   mov ah,1         ; set 1 at ah
   mov dx,0         ; port-transmitter number
   int 14h          ; invoke 1-st fun of 14-th interruption
   test al,80h      ; bitwise &, result setting in zf flag, if res is zero (zf = 1) (if 7-th bit of ah is 1 is error (TIMEOUT))
   jnz NoWrite      ; jump if not zero (zf flag = 0), 
   ret 
Write_COM1 endp

NoWrite proc
   mov ah,9                     ; set number of a print function
   mov dx,offset Error_Write    ; mov effective address of message to dx
   int 21h
   ret 
NoWrite endp

Read_COM2 proc
    mov ah,2        ; set 2-nd nummber of func
    mov dx,1        ; numb of port (COM-1)
    int 14h         
    test al,80h     ; if there is error jump
    jnz NoRead
    ret
Read_COM2 endp

NoRead proc
   mov ah,9
   mov dx,offset Error_Read
   add dx,2
   int 21h
   ret 
NoRead endp

Output proc
   mov ah,02h
   mov dl,al
   int 21h
   ret
Output endp

Exit proc
    mov ax,4C00h
    int 21h
    ret
Exit endp

start:
	mov ax, @data
	mov ds, ax
   call Init_COM1
   call Write_COM1
   xor ax,ax        ; clearing ax register
   call Read_COM2      
   call Output
   call Exit

end start
; TO DO
; 27 line : we should compare ah not al :3, and it's why this error handling sucks
; if there are no port we should see message in initializing
; 43 line: we should check if al is null (compare with 0), then jump, because int 14h(2) return our character to al
