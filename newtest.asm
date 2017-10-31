   global main
   extern printf
    segment .bss
    x$0 resq 1
    i$1 resq 1
    x$2 resq 1
    section .text
main:
    mov rax, 5
    push rax
    pop qword[x$0]
    mov rax, 1
    push rax
    pop qword[i$1]
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
    mov rax, 8
    push rax
    pop qword[x$2]
    push qword[i$1]
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop qword[i$1]
    push qword[x$2]
    mov rdi,fmt1
    pop rsi
    mov rax,0
    push rbp
    call printf
    pop rbp
    jmp L2
L3:
    push qword[x$0]
    mov rdi,fmt2
    pop rsi
    mov rax,0
    push rbp
    call printf
    pop rbp

    section .data
   fmt1: db `%ld \n`,0
   fmt2: db `%ld \n`,0
   fmt:  db '%ld ', 0
   endl: db 10, 0
