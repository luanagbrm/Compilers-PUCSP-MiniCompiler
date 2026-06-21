	.build_version macos, 15, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 48
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	w0, [sp, #4]
	str	x1, [sp, #8]
	mov	w9, #0                          ; =0x0
	str	wzr, [sp, #16]
	str	wzr, [sp, #20]
	mov	w8, #1                          ; =0x1
	and	w9, w9, #0x1
	and	w9, w9, w8
	strb	w9, [sp, #27]
	ldr	w9, [sp, #4]
	str	wzr, [sp, #28]
	subs	w8, w8, w9
	b.ge	LBB0_2
	b	LBB0_1
LBB0_1:                                 ; %paramstr.ok
	ldr	x8, [sp, #8]
	ldr	x0, [x8, #8]
	bl	_atoi
	str	w0, [sp, #28]
	b	LBB0_2
LBB0_2:                                 ; %paramstr.done
	ldr	w8, [sp, #28]
	str	w8, [sp, #16]
	ldr	w8, [sp, #16]
	subs	w8, w8, #2
	b.ge	LBB0_4
	b	LBB0_3
LBB0_3:                                 ; %then
	mov	w8, #0                          ; =0x0
	and	w8, w8, #0x1
	and	w8, w8, #0x1
	strb	w8, [sp, #27]
	b	LBB0_5
LBB0_4:                                 ; %else
	mov	w8, #1                          ; =0x1
	and	w8, w8, #0x1
	and	w8, w8, #0x1
	strb	w8, [sp, #27]
	mov	w8, #2                          ; =0x2
	str	w8, [sp, #20]
	b	LBB0_6
LBB0_5:                                 ; %ifmerge
	ldrb	w8, [sp, #27]
	tbnz	w8, #0, LBB0_12
	b	LBB0_13
LBB0_6:                                 ; %while.cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #20]
	ldr	w9, [sp, #20]
	mul	w8, w8, w9
	ldr	w9, [sp, #16]
	subs	w8, w8, w9
	b.gt	LBB0_8
	b	LBB0_7
LBB0_7:                                 ; %while.body
                                        ;   in Loop: Header=BB0_6 Depth=1
	ldr	w8, [sp, #16]
	ldr	w10, [sp, #20]
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	cbz	w8, LBB0_9
	b	LBB0_10
LBB0_8:                                 ; %while.end
	b	LBB0_5
LBB0_9:                                 ; %then10
                                        ;   in Loop: Header=BB0_6 Depth=1
	mov	w8, #0                          ; =0x0
	and	w8, w8, #0x1
	and	w8, w8, #0x1
	strb	w8, [sp, #27]
	ldr	w8, [sp, #16]
	str	w8, [sp, #20]
	b	LBB0_11
LBB0_10:                                ; %else11
                                        ;   in Loop: Header=BB0_6 Depth=1
	b	LBB0_11
LBB0_11:                                ; %ifmerge12
                                        ;   in Loop: Header=BB0_6 Depth=1
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	b	LBB0_6
LBB0_12:                                ; %then16
	adrp	x0, l_str@PAGE
	add	x0, x0, l_str@PAGEOFF
	bl	_printf
	adrp	x0, l_nl@PAGE
	add	x0, x0, l_nl@PAGEOFF
	bl	_printf
	b	LBB0_14
LBB0_13:                                ; %else17
	adrp	x0, l_str.1@PAGE
	add	x0, x0, l_str.1@PAGEOFF
	bl	_printf
	adrp	x0, l_nl.2@PAGE
	add	x0, x0, l_nl.2@PAGEOFF
	bl	_printf
	b	LBB0_14
LBB0_14:                                ; %ifmerge18
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_str:                                  ; @str
	.asciz	"true"

l_nl:                                   ; @nl
	.asciz	"\n"

l_str.1:                                ; @str.1
	.asciz	"false"

l_nl.2:                                 ; @nl.2
	.asciz	"\n"

.subsections_via_symbols
