.model small
.stack 100h
.data	
.code
send_data proc
	mov dx,3F8h     ; mov address of f-st port (COM-1, or tty1 for example)
	mov al,'x'      ; mov our character
	out dx,al       ; send to our port
	ret 
send_data endp

read_data proc
	mov dx,2F8h
	xor ax,ax       
	in al,dx        ; mov data from port, which address describe in dx, to al
	ret 
read_data endp   
   
output_data proc
	mov dl,al
	mov ah,02h
	int 21h
	ret 
output_data endp  
	
start:
	xor ax,ax       ; clearing ax, for normal execute

	call send_data

	xor ax,ax

	call read_data
	call output_data

	mov ah,4Ch
	int 21h
end start
;TO DO 
; we should clear port, before reading/writing, because if we use our 2-nd lab, and after it execute this
; output will be like in 2-nd lab, first time
