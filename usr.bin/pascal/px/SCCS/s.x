h54593
s 00025/00000/00000
d D 5.1 87/12/12 18:08:30 bostic 1 0
c date and time created 87/12/12 18:08:30 by bostic
e
u
U
t
T
I 1
s,"%W% (Berkeley) %G%",&,
s/callf.\$4,_setup/.data\
	.align 2\
	.comm Ll1,8\
	.text/
s/callf.\$8,_push2/shal	$16,(sp),(sp)/
/callf.\$8,_push4/d
/callf.\$12,_push8/d
/callf.\$12,_pushsze8/d
s/callf.\$8,_pushsp/movab	4(sp),r0\
	subl2	(sp)+,r0\
	movl	r0,sp/
s/callf.\$4,_pop2/shar	$16,(sp)+,r0/
s/callf.\$4,_pop4/movl	(sp)+,r0/
s/callf.\$4,_pop8/movl	(sp)+,r0\
	movl	(sp)+,r1/
s/callf.\$4,_popsze8/movl	(sp)+,Ll1\
	movl	(sp)+,Ll1+4\
	moval	Ll1,r0/
s/callf.\$8,_popsp/movab	4(sp),r0\
	addl3	(sp)+,r0,sp/
s/callf.\$4,_enableovrflo/bicpsw	$0x20/
s/callf.\$4,_disableovrflo/bicpsw	$0x20/
s/*-56(fp)/(r12)/
s/-56(fp)/r12/
E 1
