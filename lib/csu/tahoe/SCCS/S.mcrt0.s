h32760
s 00011/00000/00059
d D 5.1 91/04/12 11:50:59 bostic 2 1
c new copyright; att/bsd/shared
e
s 00059/00000/00000
d D 1.1 86/08/01 08:56:08 sam 1 0
c date and time created 86/08/01 08:56:08 by sam
e
u
U
t
T
I 2
/*-
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

E 2
I 1
# @(#)mcrt0.s	4.1 (Berkeley) 12/21/80
# C runtime startoff including monitoring
#		TAHOE 3/83

	.set	exit,1
	.set	cbufs,300

.globl	start
.globl	_monitor
.globl	_monstartup
.globl	_main
.globl	_exit
.globl	_etext
.globl	_environ
.globl	__cleanup
.comm	countbase,4


start:
	.word	0x0000
	movab	-8(sp),sp
	movl	8(sp),(sp)  #  argc
	movab	12(sp),r0
	movl	r0,4(sp)  #  argv
	jmp	L3
L1:
	addl2	$4,r0
L3:
	tstl	(r0)  #  null args term ?
	jneq	L1
	addl2	$4,r0
	cmpl	r0,*4(sp)  #  end of 'env' or 'argv' ?
	jlss	L2
	subl2	$4,r0	 # envp's are in list
L2:
	movl	r0,8(sp)  #  env
	movl	r0,_environ  #  indir is 0 if no env ; not 0 if env

	pushab	_etext
	pushab	eprol
	callf	$4*2+4,_monstartup
	callf	$4*3+4,_main
	pushl	r0
	callf	$4*1+4,_exit

	.data
_environ:	.space	4

	.text
_exit:
	.word	0x0000
	callf	$4,__cleanup
	pushl	$0
	callf	$4*1+4,_monitor
	movl	4(fp),r0
	kcall	$exit
eprol:


E 1
