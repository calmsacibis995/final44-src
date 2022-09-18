/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	misc.c,v $
 * Revision 2.1.1.1  90/02/09  17:26:49  rvb
 * 	Add Intel copyright
 * 	[90/02/09            rvb]
 * 
 */
/*
 * 			INTEL CORPORATION PROPRIETARY INFORMATION
 *
 *	This software is supplied under the terms of a license  agreement or 
 *	nondisclosure agreement with Intel Corporation and may not be copied 
 *	nor disclosed except in accordance with the terms of that agreement.
 *
 *	Copyright 1988 Intel Corporation
 * Copyright 1988, 1989 by Intel Corporation
 */

/*
 * keyboard controller (8042) I/O port addresses
 */
#define PORT_A		0x60		/* port A */
#define PORT_B		0x64		/* port B */

/*
 * keyboard controller command
 */
#define CMD_WOUT	0xd1		/* write controller's output port */

/*
 * keyboard controller status flags
 */
#define KB_INFULL	0x2		/* input buffer full */
#define KB_OUTFULL	0x1		/* output buffer full */

#define KB_A20		0x9f		/* enable A20,
					   enable output buffer full interrupt
					   enable data line
					   disable clock line */

/*
 * setA20():
 *	Turn on gate A20 to be able to access memory above 1MB
 */
setA20()
{
	unsigned char	outport;

	/* make sure that the input buffer is empty */
	while (inb(PORT_B) & KB_INFULL);

	/* make sure that the output buffer is empty */
	if (inb(PORT_B) & KB_OUTFULL)
		(void)inb(PORT_A);

	/* make sure that the input buffer is empty */
	while (inb(PORT_B) & KB_INFULL);

	/* write output port */
	outb(PORT_B, CMD_WOUT);

	/* wait until command is accepted */
	while (inb(PORT_B) & KB_INFULL);

	outb(PORT_A, KB_A20);

	while (inb(PORT_B) & KB_INFULL);	/* wait until done */
}

/*
 * copy n bytes from src to dst. Both src and dst are virtual addresses.
 */
bcopy(src, dst, n)
register char *src, *dst;
register int n;
{
	while (n-- > 0)
		*dst++ = *src++;
}

sleep(n)
{
	int	i;
	while(n--)
		for(i=0; i<2000000; i++);
}
