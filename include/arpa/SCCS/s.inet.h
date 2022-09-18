h00288
s 00002/00002/00025
d D 8.1 93/06/02 20:01:31 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00026
d D 5.9 93/04/12 18:14:57 andrew 11 10
c inet_aton returns a boolean value, don't need to return long.
e
s 00007/00006/00020
d D 5.8 91/11/27 11:18:53 bostic 10 9
c add inet_aton prototype
e
s 00005/00000/00021
d D 5.7 91/04/03 16:06:58 bostic 9 8
c protect all user-level include files against reinclusion
e
s 00001/00001/00020
d D 5.6 91/04/01 09:00:58 bostic 8 7
c ANSI
e
s 00010/00015/00011
d D 5.5 91/02/21 13:53:15 bostic 7 6
c first pass at function prototypes with cdefs.h
e
s 00001/00011/00025
d D 5.4 90/06/01 14:02:13 bostic 6 5
c new copyright notice
e
s 00017/00008/00019
d D 5.3 90/03/06 15:34:24 bostic 5 4
c add ANSI C prototypes
e
s 00013/00002/00014
d D 5.2 88/06/27 16:37:42 bostic 4 3
c install approved copyright notice
e
s 00007/00001/00009
d D 5.1 85/05/30 09:46:57 dist 3 2
c Add copyright
e
s 00001/00001/00009
d D 4.2 85/01/10 12:49:08 serge 2 1
c changed declaration of inet_addr() to unsigned long
e
s 00010/00000/00000
d D 4.1 83/05/28 15:18:25 sam 1 0
c date and time created 83/05/28 15:18:25 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
D 12
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
 *
 *	%W% (Berkeley) %G%
 */
E 3

I 9
#ifndef _INET_H_
#define	_INET_H_

E 9
D 5
/*
 * External definitions for
 * functions in inet(3N)
 */
D 2
struct	in_addr inet_addr();
E 2
I 2
unsigned long inet_addr();
E 2
char	*inet_ntoa();
struct	in_addr inet_makeaddr();
unsigned long inet_network();
E 5
I 5
/* External definitions for functions in inet(3) */

D 7
#ifdef __STDC__
extern unsigned long inet_addr(const char *);
extern char *inet_ntoa(struct in_addr);
extern struct in_addr inet_makeaddr(int , int);
extern unsigned long inet_network(const char *);
extern unsigned long inet_lnaof(struct in_addr);
extern unsigned long inet_netof(struct in_addr);
#else
extern unsigned long inet_addr();
extern char *inet_ntoa();
extern struct in_addr inet_makeaddr();
extern unsigned long inet_network();
extern unsigned long inet_lnaof();
extern unsigned long inet_netof();
#endif
E 7
I 7
#include <sys/cdefs.h>

__BEGIN_DECLS
D 10
extern unsigned long	 inet_addr __P((const char *));
extern unsigned long	 inet_lnaof __P((struct in_addr));
D 8
extern struct in_addr	 inet_makeaddr __P((int , int));
E 8
I 8
extern struct in_addr	 inet_makeaddr __P((u_long , u_long));
E 8
extern unsigned long	 inet_netof __P((struct in_addr));
extern unsigned long	 inet_network __P((const char *));
extern char		*inet_ntoa __P((struct in_addr));
E 10
I 10
unsigned long	 inet_addr __P((const char *));
D 11
unsigned long	 inet_aton __P((const char *, struct in_addr *));
E 11
I 11
int		 inet_aton __P((const char *, struct in_addr *));
E 11
unsigned long	 inet_lnaof __P((struct in_addr));
struct in_addr	 inet_makeaddr __P((u_long , u_long));
unsigned long	 inet_netof __P((struct in_addr));
unsigned long	 inet_network __P((const char *));
char		*inet_ntoa __P((struct in_addr));
E 10
__END_DECLS
I 9

#endif /* !_INET_H_ */
E 9
E 7
E 5
E 1
