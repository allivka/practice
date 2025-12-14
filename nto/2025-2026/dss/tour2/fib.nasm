mov eax, 6
mov ecx, 0
mov ebx, 1
mov edx, 2
jmp loop

loop:
cmp eax, edx
je finish

mov edi, ebx
add ebx, ecx
mov ecx, edi

inc edx
jmp loop

finish: