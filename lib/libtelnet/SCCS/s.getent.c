h20821
s 00009/00001/00033
d D 8.2 93/12/15 11:30:38 dab 6 5
c Add a #ifdef for HAS_CGETENT.
c Changes for Solaris support.
e
s 00002/00002/00032
d D 8.1 93/06/04 17:35:46 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00004/00023
d D 5.4 93/05/27 12:50:15 dab 4 3
c Change libtelnet so that instead of picking up
c the gettytab.c module from getty, it now uses its own
c version of getent() and getstr(), that use the newer
c library routines cgetent() and cgetstr().
e
s 00000/00019/00027
d D 5.3 93/01/20 13:24:10 bostic 3 2
c delete extra copyright notice
e
s 00002/00000/00044
d D 5.2 92/12/18 14:11:12 dab 2 1
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00044/00000/00000
d D 5.1 91/02/28 22:01:30 dab 1 0
c date and time created 91/02/28 22:01:30 by dab
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 4
static char *area;

E 4
D 3
/*
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

E 3
/*ARGSUSED*/
getent(cp, name)
char *cp, *name;
{
I 6
#ifdef	HAS_CGETENT
E 6
D 4
	return(0);
E 4
I 4
	char *dba[2];

	dba[0] = "/etc/gettytab";
	dba[1] = 0;
	return((cgetent(&area, dba, name) == 0) ? 1 : 0);
I 6
#else
	return(0);
#endif
E 6
E 4
}

I 2
D 6
#ifndef	__svr4__
E 6
I 6
#ifndef	SOLARIS
E 6
E 2
/*ARGSUSED*/
char *
D 4
getstr(cp, cpp)
char *cp, **cpp;
E 4
I 4
getstr(id, cpp)
char *id, **cpp;
E 4
{
I 6
# ifdef	HAS_CGETENT
E 6
D 4
	return(0);
E 4
I 4
	char *answer;
	return((cgetstr(area, id, &answer) > 0) ? answer : 0);
I 6
# else
	return(0);
# endif
E 6
E 4
}
I 2
#endif
E 2
E 1
