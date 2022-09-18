/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	copy.c,v $
 * Revision 2.2  89/07/12  00:18:58  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/* 
 * @(#)copy.c 1.2 88/02/08 Copyr 1985 Sun Micro
 * Byte zero and copy routines
 */

bzero(p, n)
	register char *p;
	register int n;
{
	register char zeero = 0;

	while (n > 0)
		*p++ = zeero, n--;	/* Avoid clr for 68000, still... */
}

bcopy(src, dest, count)
	register char *src, *dest;
	register int count;
{
	while (--count != -1)
		*dest++ = *src++;
}
