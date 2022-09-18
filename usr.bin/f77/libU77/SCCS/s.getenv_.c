h47993
s 00008/00005/00041
d D 5.2 91/04/12 15:33:01 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00039
d D 5.1 85/06/07 23:18:35 kre 2 1
c Add copyright
e
s 00040/00000/00000
d D 1.1 81/02/18 22:10:01 dlw 1 0
c date and time created 81/02/18 22:10:01 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_getenv[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 3
E 2
 *
I 2
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
E 2
 * return environment variables
 *
 * calling sequence:
 *	character*20 evar
 *	call getenv (ENV_NAME, evar)
 * where:
 *	ENV_NAME is the name of an environment variable
 *	evar is a character variable which will receive
 *		the current value of ENV_NAME,
 *		or all blanks if ENV_NAME is not defined
 */

extern char **environ;

getenv_(fname, value, flen, vlen)
char *value, *fname;
long int vlen, flen;
{
	register char *ep, *fp;
	register char **env = environ;
	int i;

	while (ep = *env++) {
		for (fp=fname, i=0; i <= flen; i++) {
			if (i == flen || *fp == ' ') {
				if (*ep++ == '=') {
					b_char(ep, value, vlen);
					return(0);
				}
				else break;
			}
			else if (*ep++ != *fp++) break;
		}
	}
	b_char(" ", value, vlen);
	return(0);
}
E 1
