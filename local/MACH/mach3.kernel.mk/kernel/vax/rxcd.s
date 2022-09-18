/*
 ****************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 ****************************************************************
 */
/*
 *	File:	vax/rxcd.s
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	Support for RXCD: Receive Console Data Register.
 *
 ************************************************************************
 * HISTORY
 * $Log:	rxcd.s,v $
 * Revision 2.1  89/08/03  16:38:33  rwd
 * Created.
 * 
 * Revision 2.2  88/08/10  10:35:17  rvb
 * The RXCD register must be read the same way testing the v bit.
 * 
 *
 * 13-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 ************************************************************************
 */

#include <vax/ka820.h>

/*
 *	rxcd_send(cpu, c) sends the specified character to the specified
 *	cpu's logical console by busy waiting for the console to be free.
 */
	.globl	_rxcd_send
_rxcd_send:
	.word	0x0
	movl	4(ap),r0		# node to send to
	movl	8(ap),r1		# character to send.
	ashl	$8,r0,r0		# put in send field
	bisl2	r1,r0			# value to put in register.
1:	mtpr	r0,$RXCD		# try sending
	bvs	1b			# try again if V-bit set
	ret				# sent

	.globl	_rxcd_receive
_rxcd_receive:
	.word	0x0
1:	mfpr	$RXCD,r0		# try receiving
	bvs	1b			# try again if V-bit set
	ret				# got it

