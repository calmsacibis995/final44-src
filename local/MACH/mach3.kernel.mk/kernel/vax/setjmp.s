	.globl	__setjmp
__setjmp:
	.word	0
	movl	4(ap),r0		# point to jump buffer
	movq	r6,(r0)+		# save regs 6..11
	movq	r8,(r0)+
	movq	r10,(r0)+
	movq	8(fp),(r0)+		# ap/fp
	movab	4(ap),(r0)+		# sp
	movl	16(fp),(r0)		# and pc
	clrl	r0			# return 0
	ret

	.globl	__longjmp
__longjmp:
	.word	0
	movl	8(ap),r0		# get return value
	bneq	0f			# if zero,
	movl	$1,r0			#     set to 1
0:
	movl	4(ap),r1		# point to jump buffer
	movq	(r1)+,r6		# restore r6..r11
	movq	(r1)+,r8
	movq	(r1)+,r10
	movq	(r1)+,ap		# ap/fp
	movl	(r1)+,sp		# sp
	jmp	*0(r1)			# return to call of setjmp

