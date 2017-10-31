   global main
   extern printf
    segment .bss
    a$0 resq 1
    b$1 resq 1
    c$2 resq 1
    section .text
main:
    mov rax, 23
    push rax
    pop qword[a$0]
    mov rax, 24
    push rax
    pop qword[b$1]
    push qword[a$0]
    push qword[b$1]
    pop rbx
    pop rax
    imul rbx
    push rax
    mov rax, 25
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop qword[c$2]
L2:
    push qword[a$0]
    mov rax, 30
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
    push qword[a$0]
    mov rax, 1
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop qword[a$0]
    jmp L2
L3:
    push qword[a$0]
    push qword[c$2]
    mov rax, 2
    push rax
    pop rbx
    pop rax
    imul rbx
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
    mov rax, 16
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jl J3
    mov rax,0
    jmp J4
J3:
    mov rax, 1
J4:
    push rax
    push qword[a$0]
    mov rax, 8
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jge J5
    mov rax,0
    jmp J6
J5:
    mov rax, 1
J6:
    push rax
    pop rbx
    pop rax
    and rax, rbx
    push rax
    pop rax
    cmp rax,0
    je L4
    mov rax, 5
    push rax
    pop qword[c$2]
    jmp L5
L4:
    mov rax, 123456
    push rax
    pop qword[c$2]
    push qword[a$0]
    push qword[b$1]
    mov rdi,fmt1
    pop rdx
    pop rsi
    mov rax,0
    push rbp
    call printf
    pop rbp
L5:
    mov rax, 1
    push rax
    mov rax, 1
    push rax
    pop rbx
    pop rax
    cmp rax,rbx
    jne J7
    mov rax,0
    jmp J8
J7:
    mov rax, 1
J8:
    push rax
    pop rax
    cmp rax,0
    je L6
    mov rax, 1
    push rax
    pop qword[c$2]
L6:

    section .data
   fmt1: db `%ld %ld\n`,0
   fmt:  db '%ld ', 0
   endl: db 10, 0
