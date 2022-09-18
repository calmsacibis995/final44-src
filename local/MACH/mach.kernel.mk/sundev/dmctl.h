/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dmctl.h,v $
 * Revision 2.3  89/03/09  21:41:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:50:50  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	dmctl.h	1.1	86/02/03	*/
/*
 * Bits for use with TIOCM{GET,SET,BIS,BIC} ioctls
 * really bits in dm lsr, copied from dh.c
 */
#define DML_DSR		0000400		/* data set ready, not a real DM bit */
#define DML_RNG		0000200		/* ring */
#define DML_CAR		0000100		/* carrier detect */
#define DML_CTS		0000040		/* clear to send */
#define DML_SR		0000020		/* secondary receive */
#define DML_ST		0000010		/* secondary transmit */
#define DML_RTS		0000004		/* request to send */
#define DML_DTR		0000002		/* data terminal ready */
#define DML_LE		0000001		/* line enable */
