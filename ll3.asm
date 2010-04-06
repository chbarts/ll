	.file	"ll3.c"
	.intel_syntax noprefix
	.text
	.p2align 4,,15
.globl get_next
	.type	get_next, @function
get_next:
.LFB14:
	xor	eax, eax
	test	rdi, rdi
	jne	.L6
	rep
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	mov	rax, QWORD PTR [rdi+16]
	ret
.LFE14:
	.size	get_next, .-get_next
	.p2align 4,,15
.globl set_next
	.type	set_next, @function
set_next:
.LFB15:
	test	rdi, rdi
	je	.L8
	mov	QWORD PTR [rdi+16], rsi
.L8:
	mov	rax, rdi
	ret
.LFE15:
	.size	set_next, .-set_next
	.p2align 4,,15
.globl get_tag
	.type	get_tag, @function
get_tag:
.LFB16:
	test	rdi, rdi
	mov	eax, -1
	je	.L12
	mov	eax, DWORD PTR [rdi]
.L12:
	rep
	ret
.LFE16:
	.size	get_tag, .-get_tag
	.p2align 4,,15
.globl set_tag
	.type	set_tag, @function
set_tag:
.LFB17:
	test	rdi, rdi
	je	.L15
	mov	DWORD PTR [rdi], esi
.L15:
	mov	rax, rdi
	ret
.LFE17:
	.size	set_tag, .-set_tag
	.p2align 4,,15
.globl get_data
	.type	get_data, @function
get_data:
.LFB18:
	xor	eax, eax
	test	rdi, rdi
	je	.L19
	mov	rax, QWORD PTR [rdi+8]
.L19:
	rep
	ret
.LFE18:
	.size	get_data, .-get_data
	.p2align 4,,15
.globl set_data
	.type	set_data, @function
set_data:
.LFB19:
	test	rdi, rdi
	je	.L22
	mov	QWORD PTR [rdi+8], rsi
.L22:
	mov	rax, rdi
	ret
.LFE19:
	.size	set_data, .-set_data
	.p2align 4,,15
.globl get_end
	.type	get_end, @function
get_end:
.LFB20:
	test	rdi, rdi
	mov	rax, rdi
	jne	.L29
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L30:
	mov	rax, rdi
.L29:
	mov	rdi, QWORD PTR [rax+16]
	test	rdi, rdi
	jne	.L30
.L25:
	rep
	ret
.LFE20:
	.size	get_end, .-get_end
	.p2align 4,,15
.globl append_node
	.type	append_node, @function
append_node:
.LFB21:
	test	rdi, rdi
	je	.L39
	test	rsi, rsi
	je	.L39
	mov	rax, QWORD PTR [rdi+16]
	test	rax, rax
	je	.L36
.L35:
	mov	rdi, rax
	mov	rax, QWORD PTR [rax+16]
	test	rax, rax
	jne	.L35
.L36:
	mov	QWORD PTR [rdi+16], rsi
	mov	rax, rdi
	ret
	.p2align 4,,10
	.p2align 3
.L39:
	xor	edi, edi
	mov	rax, rdi
	ret
.LFE21:
	.size	append_node, .-append_node
	.p2align 4,,15
.globl prepend_node
	.type	prepend_node, @function
prepend_node:
.LFB22:
	test	rdi, rdi
	je	.L45
	test	rsi, rsi
	je	.L45
	mov	QWORD PTR [rsi+16], rdi
	mov	rax, rsi
	ret
	.p2align 4,,10
	.p2align 3
.L45:
	xor	esi, esi
	mov	rax, rsi
	.p2align 4,,2
	.p2align 3
	ret
.LFE22:
	.size	prepend_node, .-prepend_node
	.p2align 4,,15
.globl map
	.type	map, @function
map:
.LFB24:
	push	r12
.LCFI0:
	xor	eax, eax
	test	rdi, rdi
	mov	r12, rdi
	push	rbp
.LCFI1:
	mov	rbp, rsi
	push	rbx
.LCFI2:
	mov	rbx, rdi
	je	.L48
	.p2align 4,,10
	.p2align 3
.L51:
	mov	rdi, QWORD PTR [rbx+8]
	call	rbp
	mov	QWORD PTR [rbx+8], rax
	mov	rbx, QWORD PTR [rbx+16]
	test	rbx, rbx
	jne	.L51
	mov	rax, r12
.L48:
	pop	rbx
	pop	rbp
	pop	r12
	ret
.LFE24:
	.size	map, .-map
	.p2align 4,,15
.globl reverse
	.type	reverse, @function
reverse:
.LFB25:
	test	rdi, rdi
	mov	rdx, rdi
	je	.L54
	mov	rdi, QWORD PTR [rdi+16]
	test	rdi, rdi
	je	.L54
	mov	QWORD PTR [rdx+16], 0
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L58:
	mov	rdi, rax
.L56:
	mov	rax, QWORD PTR [rdi+16]
	mov	QWORD PTR [rdi+16], rdx
	mov	rdx, rdi
	test	rax, rax
	jne	.L58
.L54:
	mov	rax, rdx
	ret
.LFE25:
	.size	reverse, .-reverse
	.p2align 4,,15
.globl free_all_nodes
	.type	free_all_nodes, @function
free_all_nodes:
.LFB27:
	test	rdi, rdi
	push	rbx
.LCFI3:
	je	.L62
	.p2align 4,,10
	.p2align 3
.L63:
	mov	rbx, QWORD PTR [rdi+16]
	mov	QWORD PTR [rdi+16], 0
	call	free
	test	rbx, rbx
	mov	rdi, rbx
	jne	.L63
.L62:
	pop	rbx
	ret
.LFE27:
	.size	free_all_nodes, .-free_all_nodes
	.p2align 4,,15
.globl free_all_data
	.type	free_all_data, @function
free_all_data:
.LFB26:
	push	rbp
.LCFI4:
	xor	eax, eax
	mov	rbp, rdi
	push	rbx
.LCFI5:
	mov	rbx, rdi
	sub	rsp, 8
.LCFI6:
	test	rdi, rdi
	je	.L67
	.p2align 4,,10
	.p2align 3
.L70:
	mov	rdi, QWORD PTR [rbx+8]
	call	free
	mov	QWORD PTR [rbx+8], 0
	mov	rbx, QWORD PTR [rbx+16]
	test	rbx, rbx
	jne	.L70
	mov	rax, rbp
.L67:
	add	rsp, 8
	pop	rbx
	pop	rbp
	ret
.LFE26:
	.size	free_all_data, .-free_all_data
	.p2align 4,,15
.globl new_node
	.type	new_node, @function
new_node:
.LFB23:
	mov	QWORD PTR [rsp-24], rbx
.LCFI7:
	mov	QWORD PTR [rsp-16], rbp
.LCFI8:
	mov	ebx, edi
	mov	QWORD PTR [rsp-8], r12
.LCFI9:
	mov	edi, 24
	sub	rsp, 24
.LCFI10:
	mov	rbp, rsi
	mov	r12, rdx
	call	malloc
	test	rax, rax
	je	.L73
	mov	DWORD PTR [rax], ebx
	mov	QWORD PTR [rax+8], rbp
	mov	QWORD PTR [rax+16], r12
.L73:
	mov	rbx, QWORD PTR [rsp]
	mov	rbp, QWORD PTR [rsp+8]
	mov	r12, QWORD PTR [rsp+16]
	add	rsp, 24
	ret
.LFE23:
	.size	new_node, .-new_node
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB14
	.long	.LFE14-.LFB14
	.uleb128 0x0
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB15
	.long	.LFE15-.LFB15
	.uleb128 0x0
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB16
	.long	.LFE16-.LFB16
	.uleb128 0x0
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB17
	.long	.LFE17-.LFB17
	.uleb128 0x0
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB18
	.long	.LFE18-.LFB18
	.uleb128 0x0
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB19
	.long	.LFE19-.LFB19
	.uleb128 0x0
	.align 8
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB20
	.long	.LFE20-.LFB20
	.uleb128 0x0
	.align 8
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB21
	.long	.LFE21-.LFB21
	.uleb128 0x0
	.align 8
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB22
	.long	.LFE22-.LFB22
	.uleb128 0x0
	.align 8
.LEFDE17:
.LSFDE19:
	.long	.LEFDE19-.LASFDE19
.LASFDE19:
	.long	.LASFDE19-.Lframe1
	.long	.LFB24
	.long	.LFE24-.LFB24
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB24
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0x18
	.byte	0x86
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.align 8
.LEFDE19:
.LSFDE21:
	.long	.LEFDE21-.LASFDE21
.LASFDE21:
	.long	.LASFDE21-.Lframe1
	.long	.LFB25
	.long	.LFE25-.LFB25
	.uleb128 0x0
	.align 8
.LEFDE21:
.LSFDE23:
	.long	.LEFDE23-.LASFDE23
.LASFDE23:
	.long	.LASFDE23-.Lframe1
	.long	.LFB27
	.long	.LFE27-.LFB27
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI3-.LFB27
	.byte	0xe
	.uleb128 0x10
	.byte	0x83
	.uleb128 0x2
	.align 8
.LEFDE23:
.LSFDE25:
	.long	.LEFDE25-.LASFDE25
.LASFDE25:
	.long	.LASFDE25-.Lframe1
	.long	.LFB26
	.long	.LFE26-.LFB26
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI4-.LFB26
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xe
	.uleb128 0x18
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xe
	.uleb128 0x20
	.align 8
.LEFDE25:
.LSFDE27:
	.long	.LEFDE27-.LASFDE27
.LASFDE27:
	.long	.LASFDE27-.Lframe1
	.long	.LFB23
	.long	.LFE23-.LFB23
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI8-.LFB23
	.byte	0x86
	.uleb128 0x3
	.byte	0x83
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI10-.LCFI8
	.byte	0xe
	.uleb128 0x20
	.byte	0x8c
	.uleb128 0x2
	.align 8
.LEFDE27:
	.ident	"GCC: (Ubuntu 4.3.2-1ubuntu12) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
