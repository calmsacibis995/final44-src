/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	strops.c,v $
 * Revision 2.2  89/07/12  00:21:00  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)strops.c 1.2 88/02/08 Copyr 1985 Sun Micro
 * Assorted string operations
 */

/*
 * Compare strings:  s1>s2: >0  s1==s2: 0  s1<s2: <0
 */
strcmp(s1, s2)
	register char *s1, *s2;
{

	while (*s1 == *s2++)
		if (*s1++=='\0')
			return (0);
	return (*s1 - *--s2);
}

/*
 * Returns the number of
 * non-NULL bytes in string argument.
 */
strlen(s)
	register char *s;
{
	register int n;

	n = 0;
	while (*s++)
		n++;
	return (n);
}
