	.build_version macos, 15, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_arccot                         ; -- Begin function arccot
	.p2align	2
_arccot:                                ; @arccot
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	mov	w8, #0                          ; =0x0
	str	wzr, [sp]
	str	w0, [sp, #4]
	str	w1, [sp, #8]
	str	wzr, [sp, #12]
	str	wzr, [sp, #16]
	str	wzr, [sp, #20]
	str	wzr, [sp, #24]
	mov	w9, #1                          ; =0x1
	and	w8, w8, #0x1
	and	w8, w8, #0x1
	strb	w8, [sp, #31]
	ldr	w8, [sp, #8]
	ldr	w10, [sp, #4]
	sdiv	w8, w8, w10
	str	w8, [sp, #16]
	ldr	w8, [sp, #16]
	str	w8, [sp, #12]
	mov	w8, #3                          ; =0x3
	str	w8, [sp, #20]
	and	w8, w9, #0x1
	and	w8, w8, w9
	strb	w8, [sp, #31]
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #4]
	ldr	w10, [sp, #4]
	mul	w9, w9, w10
	sdiv	w8, w8, w9
	str	w8, [sp, #16]
	b	LBB0_2
LBB0_1:                                 ; %exit
	ldr	w0, [sp]
	add	sp, sp, #32
	ret
LBB0_2:                                 ; %while.cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #20]
	sdiv	w8, w8, w9
	subs	w8, w8, #0
	b.le	LBB0_4
	b	LBB0_3
LBB0_3:                                 ; %while.body
                                        ;   in Loop: Header=BB0_2 Depth=1
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #20]
	sdiv	w8, w8, w9
	str	w8, [sp, #24]
	ldrb	w8, [sp, #31]
	tbnz	w8, #0, LBB0_5
	b	LBB0_6
LBB0_4:                                 ; %while.end
	ldr	w8, [sp, #12]
	str	w8, [sp]
	b	LBB0_1
LBB0_5:                                 ; %then
                                        ;   in Loop: Header=BB0_2 Depth=1
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #24]
	subs	w8, w8, w9
	str	w8, [sp, #12]
	b	LBB0_7
LBB0_6:                                 ; %else
                                        ;   in Loop: Header=BB0_2 Depth=1
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #24]
	add	w8, w8, w9
	str	w8, [sp, #12]
	b	LBB0_7
LBB0_7:                                 ; %ifmerge
                                        ;   in Loop: Header=BB0_2 Depth=1
	ldrb	w8, [sp, #31]
	mov	w9, #1                          ; =0x1
	eor	w8, w8, #0x1
	and	w8, w8, #0x1
	and	w8, w8, w9
	strb	w8, [sp, #31]
	ldr	w8, [sp, #20]
	add	w8, w8, #2
	str	w8, [sp, #20]
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #4]
	ldr	w10, [sp, #4]
	mul	w9, w9, w10
	sdiv	w8, w8, w9
	str	w8, [sp, #16]
	b	LBB0_2
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #96
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 96
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	w0, [sp, #36]
	str	x1, [sp, #40]
	str	wzr, [sp, #48]
	str	wzr, [sp, #52]
	str	wzr, [sp, #56]
	str	wzr, [sp, #60]
	str	wzr, [sp, #64]
	str	wzr, [sp, #68]
	str	wzr, [sp, #72]
	ldr	w9, [sp, #36]
	str	wzr, [sp, #76]
	mov	w8, #1                          ; =0x1
	subs	w8, w8, w9
	b.ge	LBB1_2
	b	LBB1_1
LBB1_1:                                 ; %paramstr.ok
	ldr	x8, [sp, #40]
	ldr	x0, [x8, #8]
	bl	_atoi
	str	w0, [sp, #76]
	b	LBB1_2
LBB1_2:                                 ; %paramstr.done
	ldr	w8, [sp, #76]
	str	w8, [sp, #48]
	ldr	w8, [sp, #48]
	subs	w8, w8, #6
	b.le	LBB1_4
	b	LBB1_3
LBB1_3:                                 ; %then
	mov	w8, #6                          ; =0x6
	str	w8, [sp, #48]
	b	LBB1_5
LBB1_4:                                 ; %else
	b	LBB1_5
LBB1_5:                                 ; %ifmerge
	ldr	w8, [sp, #48]
	subs	w8, w8, #1
	b.ge	LBB1_7
	b	LBB1_6
LBB1_6:                                 ; %then6
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #48]
	b	LBB1_8
LBB1_7:                                 ; %else7
	b	LBB1_8
LBB1_8:                                 ; %ifmerge8
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #56]
	ldr	w9, [sp, #48]
	add	w9, w9, #2
	str	w9, [sp, #32]                   ; 4-byte Spill
	str	w8, [sp, #52]
	b	LBB1_9
LBB1_9:                                 ; %for.cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w9, [sp, #32]                   ; 4-byte Reload
	ldr	w8, [sp, #52]
	subs	w8, w8, w9
	b.gt	LBB1_11
	b	LBB1_10
LBB1_10:                                ; %for.body
                                        ;   in Loop: Header=BB1_9 Depth=1
	ldr	w8, [sp, #56]
	mov	w9, #10                         ; =0xa
	mul	w8, w8, w9
	str	w8, [sp, #56]
	ldr	w8, [sp, #52]
	add	w8, w8, #1
	str	w8, [sp, #52]
	b	LBB1_9
LBB1_11:                                ; %for.end
	ldr	w1, [sp, #56]
	mov	w0, #5                          ; =0x5
	bl	_arccot
	mov	w8, #4                          ; =0x4
	mul	w8, w8, w0
	str	w8, [sp, #24]                   ; 4-byte Spill
	ldr	w1, [sp, #56]
	mov	w0, #239                        ; =0xef
	bl	_arccot
	ldr	w8, [sp, #24]                   ; 4-byte Reload
	subs	w8, w8, w0
	str	w8, [sp, #60]
	ldr	w8, [sp, #60]
	lsl	w8, w8, #2
	str	w8, [sp, #64]
	ldr	w8, [sp, #64]
	mov	w9, #1000                       ; =0x3e8
	sdiv	w8, w8, w9
	str	w8, [sp, #64]
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #68]
	ldr	w9, [sp, #48]
	subs	w9, w9, #1
	str	w9, [sp, #28]                   ; 4-byte Spill
	str	w8, [sp, #52]
	b	LBB1_12
LBB1_12:                                ; %for.cond21
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w9, [sp, #28]                   ; 4-byte Reload
	ldr	w8, [sp, #52]
	subs	w8, w8, w9
	b.gt	LBB1_14
	b	LBB1_13
LBB1_13:                                ; %for.body22
                                        ;   in Loop: Header=BB1_12 Depth=1
	ldr	w8, [sp, #68]
	mov	w9, #10                         ; =0xa
	mul	w8, w8, w9
	str	w8, [sp, #68]
	ldr	w8, [sp, #52]
	add	w8, w8, #1
	str	w8, [sp, #52]
	b	LBB1_12
LBB1_14:                                ; %for.end23
	ldr	w8, [sp, #48]
	str	w8, [sp, #20]                   ; 4-byte Spill
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #52]
	b	LBB1_15
LBB1_15:                                ; %for.cond31
                                        ; =>This Inner Loop Header: Depth=1
	ldr	w9, [sp, #20]                   ; 4-byte Reload
	ldr	w8, [sp, #52]
	subs	w8, w8, w9
	b.gt	LBB1_17
	b	LBB1_16
LBB1_16:                                ; %for.body32
                                        ;   in Loop: Header=BB1_15 Depth=1
	ldr	w8, [sp, #64]
	ldr	w9, [sp, #68]
	sdiv	w8, w8, w9
	str	w8, [sp, #72]
	ldr	w8, [sp, #64]
	ldr	w10, [sp, #68]
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	str	w8, [sp, #64]
	ldr	w8, [sp, #72]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_fmt@PAGE
	add	x0, x0, l_fmt@PAGEOFF
	bl	_printf
	ldr	w8, [sp, #68]
	mov	w9, #10                         ; =0xa
	sdiv	w8, w8, w9
	str	w8, [sp, #68]
	ldr	w8, [sp, #52]
	add	w8, w8, #1
	str	w8, [sp, #52]
	b	LBB1_15
LBB1_17:                                ; %for.end33
	adrp	x0, l_nl@PAGE
	add	x0, x0, l_nl@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #80]             ; 16-byte Folded Reload
	add	sp, sp, #96
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_fmt:                                  ; @fmt
	.asciz	"%d"

l_nl:                                   ; @nl
	.asciz	"\n"

.subsections_via_symbols
