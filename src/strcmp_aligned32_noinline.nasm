global strcmp_aligned32_noinline

section .text

strcmp_aligned32_noinline:
    vmovdqa ymm0, YWORD [rdi]
    xor rax, rax
    vptest ymm0, YWORD [rsi]
    seta al  ; 0 if equal
    ret
