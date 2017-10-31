   global main
   extern printf
    segment .bss
    x$0 resq 1
    i$1 resq 1
    sum$2 resq 1
    section .text
hi:
    pop r15
    pop qword[x$0]
    push qword[x$0]
    mov rdi,fmt1
    pop rsi
    mov rax,0
    push rbp
    call printf
    pop rbp
    mov rax, 0
    push rax
    pop rax
    push r15
    ret
main:
    mov rax, 1
    push rax
    pop qword[i$1]
    mov rax, 0
    push rax
    pop qword[sum$2]
L2:
    push qword[i$1]
    mov rax, 3
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jl J1
    mov rax,0
    jmp J2
J1:
    mov rax, 1
J2:
    push rax
    pop rax
    cmp rax,0
    je L3
    push qword[sum$2]
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop qword[sum$2]
    push qword[i$1]
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop qword[i$1]
    jmp L2
L3:
    mov rax, 1
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    and rax, rbx
    push rax
    pop rax
    cmp rax,0
    je L4
    push qword[i$1]
    mov rdi,fmt2
    pop rsi
    mov rax,0
    push rbp
    call printf
    pop rbp
L4:
    push qword[sum$2]
    call hi
    push rax
    pop qword[i$1]
    push qword[sum$2]
    pop rax
    ret

    section .data
   fmt1: db `%ld \n`,0
   fmt2: db `%ld \n`,0
   fmt:  db '%ld ', 0
   endl: db 10, 0
