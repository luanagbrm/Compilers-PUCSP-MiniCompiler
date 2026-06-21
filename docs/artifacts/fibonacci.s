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
	str	w0, [sp, #12]
	str	x1, [sp, #16]
	str	wzr, [sp, #24]
	str	wzr, [sp, #28]
	str	wzr, [sp, #32]
	str	wzr, [sp, #36]
	str	wzr, [sp, #40]
	ldr	w9, [sp, #12]
	str	wzr, [sp, #44]
	mov	w8, #1                          ; =0x1
	subs	w8, w8, w9
	b.ge	LBB0_2
	b	LBB0_1
LBB0_1:                                 ; %paramstr.ok
	ldr	x8, [sp, #16]
	ldr	x0, [x8, #8]
	bl	_atoi
	str	w0, [sp, #44]
	b	LBB0_2
LBB0_2:                                 ; %paramstr.done
	ldr	w8, [sp, #44]
	str	w8, [sp, #24]
	ldr	w8, [sp, #24]
	subs	w8, w8, #0
	b.gt	LBB0_4
	b	LBB0_3
LBB0_3:                                 ; %then
	mov	x8, sp
	str	xzr, [x8]
	adrp	x0, l_fmt@PAGE
	add	x0, x0, l_fmt@PAGEOFF
	bl	_printf
	adrp	x0, l_nl@PAGE
	add	x0, x0, l_nl@PAGEOFF
	bl	_printf
	b	LBB0_5
LBB0_4:                                 ; %else
	ldr	w8, [sp, #24]
	subs	w8, w8, #1
	b.eq	LBB0_6
	b	LBB0_7
LBB0_5:                                 ; %ifmerge
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
LBB0_6:                                 ; %then6
	mov	x9, sp
	mov	w8, #1                          ; =0x1
                                        ; kill: def $x8 killed $w8
	str	x8, [x9]
	adrp	x0, l_fmt.1@PAGE
	add	x0, x0, l_fmt.1@PAGEOFF
	bl	_printf
	adrp	x0, l_nl.2@PAGE
	add	x0, x0, l_nl.2@PAGEOFF
	bl	_printf
	b	LBB0_8
LBB0_7:                                 ; %else7
	str	wzr, [sp, #32]
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #36]
	ldr	w8, [sp, #24]
	str	w8, [sp, #8]                    ; 4-byte Spill
	mov	w8, #2                          ; =0x2
	str	w8, [sp, #28]
	b	LBB0_9
LBB0_8:                                 ; %ifmerge8
	b	LBB0_5
LBB0_9:                                 ; %for.cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w9, [sp, #8]                    ; 4-byte Reload
	ldr	w8, [sp, #28]
	subs	w8, w8, w9
	b.gt	LBB0_11
	b	LBB0_10
LBB0_10:                                ; %for.body
                                        ;   in Loop: Header=BB0_9 Depth=1
	ldr	w8, [sp, #32]
	ldr	w9, [sp, #36]
	add	w8, w8, w9
	str	w8, [sp, #40]
	ldr	w8, [sp, #36]
	str	w8, [sp, #32]
	ldr	w8, [sp, #40]
	str	w8, [sp, #36]
	ldr	w8, [sp, #28]
	add	w8, w8, #1
	str	w8, [sp, #28]
	b	LBB0_9
LBB0_11:                                ; %for.end
	ldr	w8, [sp, #36]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_fmt.3@PAGE
	add	x0, x0, l_fmt.3@PAGEOFF
	bl	_printf
	adrp	x0, l_nl.4@PAGE
	add	x0, x0, l_nl.4@PAGEOFF
	bl	_printf
	b	LBB0_8
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_fmt:                                  ; @fmt
	.asciz	"%d"

l_nl:                                   ; @nl
	.asciz	"\n"

l_fmt.1:                                ; @fmt.1
	.asciz	"%d"

l_nl.2:                                 ; @nl.2
	.asciz	"\n"

l_fmt.3:                                ; @fmt.3
	.asciz	"%d"

l_nl.4:                                 ; @nl.4
	.asciz	"\n"

.subsections_via_symbols
