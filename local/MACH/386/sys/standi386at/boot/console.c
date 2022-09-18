/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	console.c,v $
 * Revision 2.1.1.1  90/02/09  17:26:18  rvb
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
 * write one character to console
 */
putchar(c)
register c;
{
	if (c == '\n')
		putc('\r');
	return(putc(c));
}

/*
 * write one string to console -- no NL added
 */
puts(s)
register char	*s;
{
	register c;

	while ( c = *s++)
		putchar(c);
	return;
}


/*
 * Read a character from console with the echo mode on
 */
getchar()
{
	register c;

	c = getc();
	if (c == '\r')
		c = '\n';
	
	/* echo character */
	if (c == '\b') {
		putchar('\b');
		putchar(' ');
		putchar('\b');
	} else
		putchar(c);

	return(c);
}

