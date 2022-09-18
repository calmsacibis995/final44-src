/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	common.c,v $
 * Revision 2.2  89/07/12  01:11:01  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)common.c 1.5 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Common code for various bootstrap routines.
 */

#include "../mon/sunromvec.h"

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
	unsigned count;
{
	while (--count != -1)
		*dest++ = *src++;
}


/*
 * Hex string scanner for open().   Converts strings of the
 * form {[0-9]|[a-f]|[A_F]}*.    If none of these characters
 * are found before a delimiter ',' or illegal character, the
 * value accumulated so far is returned.   If a ',' is found,
 * the value returned points after the ','.   If the string
 * ends in '\0', the value returned points to the '\0'.  Other-
 * wise, the value returned points to the first non-hex char-
 * acter encountered.
 */


char *
openhex(p, ip)
	register char *p;
	int *ip;
{
	register int ac = 0;

	while (*p) {
		if (*p >= '0' && *p <= '9')
			ac = (ac<<4) + (*p - '0');
		else if (*p >= 'a' && *p <= 'f')
			ac = (ac<<4) + (*p - 'a' + 10);
		else if (*p >= 'A' && *p <= 'F')
			ac = (ac<<4) + (*p - 'A' + 10);
		else
			break;
		p++;
	}
	if (*p == ',')
		p++;
	*ip = ac;
	return (p);

}

