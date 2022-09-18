/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ascii.s,v $
 * Revision 2.3  89/02/25  19:39:54  gm0w
 * 	Changes for cleanup.
 * 
 */
        .data
        .asciz  "@(#)ascii.s 1.1 86/02/03 Copyr 1985 Sun Micro"
        .even
        .text

|       Copyright (c) 1985 by Sun Microsystems, Inc.

| typedef unsigned char ext_fp[12] ;

| void ltofpr(l, fpr)

|	long l ;
|	ext_fp *fpr ;

|/*
| * 	Converts long l to floating point register at fpr.
| */

	.globl	_ltofpr
_ltofpr:
	link	a6,#0
	fmovem	fp0/fp0,sp@-	| Save fp0.
	fmovel	a6@(8),fp0	| fp0 gets l.
	movl	a6@(12),a0	| a0 gets address of fpr.
	fmovem	fp0/fp0,a0@	| fpr gets extended l.
	fmovem	sp@+,fp0/fp0	| Restore fp0.
	unlk	a6
	rts

	.globl	_dtofpr
_dtofpr:
	link	a6,#0
	fmovem	fp0/fp0,sp@-	| Save fp0.
	movel	a6@(8),a0
	fmoved	a0@,fp0		| fp0 gets d.
	movl	a6@(12),a0	| a0 gets address of fpr.
	fmovem	fp0/fp0,a0@	| fpr gets extended d.
	fmovem	sp@+,fp0/fp0	| Restore fp0.
	unlk	a6
	rts

| int fprtop( fpr, p )

| 	ext_fp *fpr ;
| 	char *p [12] ;

|/*
| *	Converts floating point register at fpr to bcd record at *p.
| *	Function result is fps register after conversion; indicates inexact
| *	or exponent spill.
| */

	.globl	_fprtop
_fprtop:
	link	a6,#0
	moveml	d7/d7,sp@-
	fmovem	fp0/fp0,sp@-	| Save fp0.
	movl	a6@(8),a1	| a1 gets address of fpr.
	fmovem	a1@,fp0/fp0	| fp0 gets fpr.
	movl	a6@(12),a0	| a0 gets address of p.
	movw	#17,d7		| d7 gets k-factor.
	fmovep	fp0,a0@		| Store p.
	fmovel	fps,d0		| d0 gets function result.
	fmovem	sp@+,fp0/fp0	| Restore fp0.
	moveml	sp@+,d7/d7
	unlk	a6
	rts

	.globl	_FNOP
_FNOP:
	fnop
	rts
