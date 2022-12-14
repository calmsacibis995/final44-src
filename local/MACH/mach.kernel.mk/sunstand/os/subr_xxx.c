/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	subr_xxx.c,v $
 * Revision 2.2  89/07/12  01:13:59  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*      @(#)subr_xxx.c 1.7 88/02/08 SMI      */

#include <machine/pte.h>

#include <sys/param.h>
#include "boot/systm.h"
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include "boot/vnode.h"
#include <sys/vm.h>
#include "boot/cmap.h"
#include <sys/uio.h>

#undef	u
extern	struct	user	u;

/*
 * Routine placed in illegal entries in the bdevsw and cdevsw tables.
 */
nodev()
{

	return (ENODEV);
}

/*
 * Null routine; placed in insignificant entries
 * in the bdevsw and cdevsw tables.
 */
nulldev()
{

	return (0);
}

/*
 * Null system calls. Not invalid, just not configured.
 */
errsys()
{
	u.u_error = EINVAL;
}

#ifdef	NEVER
nullsys()
{
}
#endif	/* NEVER */

imin(a, b)
{

	return (a < b ? a : b);
}

imax(a, b)
{

	return (a > b ? a : b);
}

unsigned
min(a, b)
	u_int a, b;
{

	return (a < b ? a : b);
}

unsigned
max(a, b)
	u_int a, b;
{

	return (a > b ? a : b);
}

#ifndef vax
ffs(mask)
	register long mask;
{
	register int i;

	if (mask == 0)
		return(0);
	for(i = 1; i < NSIG; i++) {
		if (mask & 1)
			return (i);
		mask >>= 1;
	}
	return (0);
}

bcmp(s1, s2, len)
	register char *s1, *s2;
	register int len;
{

	while (len--)
		if (*s1++ != *s2++)
			return (1);
	return (0);
}

skpc(c, len, cp)
	register char c;
	register u_short len;
	register char *cp;
{
	if (len == 0)
		return (0);
	while (*cp++ == c && --len)
		;
	return (len);
}
#endif

/*
 * Returns the number of
 * non-NULL bytes in string argument.
 */
strlen(s)
	register char *s;
{
	register int n;

	if (s == (char *)0)	{
		_stop("strlen: zero pointer");
	}

	n = 0;
	while (*s++)
		n++;
	return (n);
}

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

strncmp(s1, s2, n)
        register char *s1, *s2;
        register int n;
{

        while (--n >= 0 && *s1 == *s2++)
                if (*s1++ == '\0')
                        return (0);
        return (n<0 ? 0 : *s1 - *--s2);
}

/*
 * Copy string s2 to s1.  s1 must be large enough.
 * return ptr to null in s1
 */
char *
strcpy(s1, s2)
	register char *s1, *s2;
{

	while (*s1++ = *s2++)
		;
	return (s1 - 1);
}

/*
 * Copy s2 to s1, truncating to copy n bytes
 * return ptr to null in s1 or s1 + n
 */
char *
strncpy(s1, s2, n)
	register char *s1, *s2;
{
	register i;

	for (i = 0; i < n; i++) {
		if ((*s1++ = *s2++) == '\0') {
			return (s1 - 1);
		}
	}
	return (s1);
}
