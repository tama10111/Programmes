.code16

.text
.globl _start;
.globl f;

_start:

movl $10, %ebx
movl $0, %ecx

f:

movb %ah, %al
movb $0xe, %ah
int $0x10

subl $1, %ebx
cmpl %ebx, %ecx
jne f

movb $'f', %al
movb $0xe, %ah
int $0x10
movb $'i', %al
movb $0xe, %ah
int $0x10
movb $'n', %al
movb $0xe, %ah
int $0x10
movb $'i', %al
movb $0xe, %ah
int $0x10

. = _start+510
.byte 0x55
.byte 0xaa
