	.build_version macos, 15, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 64
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	w0, [sp, #20]
	str	x1, [sp, #24]
	str	wzr, [sp, #36]
	str	wzr, [sp, #40]
	ldr	w9, [sp, #20]
	str	wzr, [sp, #44]
	mov	w8, #1                          ; =0x1
	subs	w8, w8, w9
	b.ge	LBB0_2
	b	LBB0_1
LBB0_1:                                 ; %paramstr.ok
	ldr	x8, [sp, #24]
	ldr	x0, [x8, #8]
	bl	_atoi
	str	w0, [sp, #44]
	b	LBB0_2
LBB0_2:                                 ; %paramstr.done
	ldr	w8, [sp, #44]
	str	w8, [sp, #36]
	mov	w8, #2                          ; =0x2
	str	w8, [sp, #40]
	b	LBB0_3
LBB0_3:                                 ; %while.cond
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_6 Depth 2
	ldr	w8, [sp, #40]
	ldr	w9, [sp, #40]
	mul	w8, w8, w9
	ldr	w9, [sp, #36]
	subs	w8, w8, w9
	b.gt	LBB0_5
	b	LBB0_4
LBB0_4:                                 ; %while.body
                                        ;   in Loop: Header=BB0_3 Depth=1
	b	LBB0_6
LBB0_5:                                 ; %while.end
	ldr	w8, [sp, #36]
	subs	w8, w8, #1
	b.gt	LBB0_9
	b	LBB0_10
LBB0_6:                                 ; %while.cond7
                                        ;   Parent Loop BB0_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	w8, [sp, #36]
	ldr	w10, [sp, #40]
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	cbnz	w8, LBB0_8
	b	LBB0_7
LBB0_7:                                 ; %while.body8
                                        ;   in Loop: Header=BB0_6 Depth=2
	ldr	w8, [sp, #40]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_fmt@PAGE
	add	x0, x0, l_fmt@PAGEOFF
	bl	_printf
	adrp	x0, l_str@PAGE
	add	x0, x0, l_str@PAGEOFF
	bl	_printf
	ldr	w8, [sp, #36]
	ldr	w9, [sp, #40]
	sdiv	w8, w8, w9
	str	w8, [sp, #36]
	b	LBB0_6
LBB0_8:                                 ; %while.end9
                                        ;   in Loop: Header=BB0_3 Depth=1
	ldr	w8, [sp, #40]
	add	w8, w8, #1
	str	w8, [sp, #40]
	b	LBB0_3
LBB0_9:                                 ; %then
	ldr	w8, [sp, #36]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_fmt.1@PAGE
	add	x0, x0, l_fmt.1@PAGEOFF
	bl	_printf
	adrp	x0, l_str.2@PAGE
	add	x0, x0, l_str.2@PAGEOFF
	bl	_printf
	b	LBB0_11
LBB0_10:                                ; %else
	b	LBB0_11
LBB0_11:                                ; %ifmerge
	adrp	x0, l_nl@PAGE
	add	x0, x0, l_nl@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_fmt:                                  ; @fmt
	.asciz	"%d"

l_str:                                  ; @str
	.asciz	" "

l_fmt.1:                                ; @fmt.1
	.asciz	"%d"

l_str.2:                                ; @str.2
	.asciz	" "

l_nl:                                   ; @nl
	.asciz	"\n"

.subsections_via_symbols
