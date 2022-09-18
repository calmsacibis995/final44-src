# C runtime startoff

	.set	exit,1
.globl	_exit
.globl	start
.globl	_main
.globl	_environ

#
#	C language startup routine

start:
	.word	0x0000
	subl2	$8,sp
	movl	8(sp),(sp)  #  argc
	movab	12(sp),r0
	movl	r0,4(sp)  #  argv
L1:
	tstl	(r0)+  #  null args term ?
	bneq	L1
	cmpl	r0,*4(sp)  #  end of 'env' or 'argv' ?
	blss	L2
	tstl	-(r0)  # envp's are in list
L2:
	movl	r0,8(sp)  #  env
	movl	r0,_environ  #  indir is 0 if no env ; not 0 if env
#
#	mods added by jkf and rrh, UCB to handle
#	dynamic tracing
#
	clrl	_doingtrace	# no tracing unless parity set
	movl	12(sp),r0	# get argv[0]
	beql	L3		# jump if null

	bitb	$0x80, (r0)
	beql	L3

	movl	$1,_doingtrace
	pushab	__Thandler	# signal(SIGTRACE, _Thandler)
	pushl	$5
	calls	$2,_signal

	movl	$3,r5
	movpsl	-(sp)		# set up a stack frame to enable PSL_T
	bisl2	$0x10,(sp)	# when do the rei
	movab	foo,-(sp)
	rei
foo:

L3:
	calls	$3,_main
	pushl	r0
	calls	$1,_exit
	chmk	$exit
#

	.globl	__asdyn_opcode_count_
__asdyn_opcode_count_:
	movpsl	-(sp)			# save condition codes

	movl	r0, -(sp)		# get temporary register
	movzwl	*8(sp),	r0		# return address points to word index
	incl	__opcode_count[r0]	# do it
	movl	(sp)+, r0		# restore temporary

	addl2	$2, 4(sp)		# skip over return over word index
	movw	(sp)+, (sp)		# move psw over high word of psl
	bicpsw	$0x0F			# mask out smashed condition codes
	bispsw	(sp)+			# restore what had on entry
	rsb

	.globl	__asdyn_reg_count_
__asdyn_reg_count_:
	movpsl	-(sp)			# save condition codes

	movl	r0, -(sp)		# get temporary register
	movzwl	*8(sp),	r0		# return address points to word index
	incl	__reg_count[r0]		# do it
	movl	(sp)+, r0		# restore temporary

	addl2	$2, 4(sp)		# skip over return over word index
	movw	(sp)+, (sp)		# move psw over high word of psl
	bicpsw	$0x0F			# mask out smashed condition codes
	bispsw	(sp)+			# restore what had on entry
	rsb

	.globl __asdyn_count_
__asdyn_count_:
	.word	0x00			# for callg entry
	incl	(ap)			# ap points to what to be incremented
	ret
/*
 *	We have our own versions of creat, write and close
 *	here so that when the counters are written to an
 *	intermediate file, the process of writing does not
 *	affect our counts
 */

	.set	creat,8
	.set	write,4
	.set	close,6
.globl	___creat
.globl	___write
.globl	___close

.globl  cerror

___creat:
	.word	0x0000
	chmk	$creat
	bcc 	create_noerror
	jmp 	cerror
create_noerror:
	ret

___write:
	.word	0x0000
	chmk	$write
	bcc 	write_noerror
	jmp 	cerror
write_noerror:
	ret

___close:
	.word	0x0000
	chmk	$close
	bcc 	close_noerror
	jmp 	cerror
close_noerror:
	clrl	r0
	ret

	.data
_environ:	.space	4
