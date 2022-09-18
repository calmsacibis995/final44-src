h33417
s 00002/00002/00091
d D 8.1 93/06/04 12:49:57 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00023/00084
d D 5.8 91/02/24 12:40:03 bostic 14 13
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00106
d D 5.7 90/06/01 14:13:55 bostic 13 12
c new copyright notice
e
s 00002/00003/00115
d D 5.6 90/05/21 16:58:19 bostic 12 11
c put pathnames into netdb.h
e
s 00010/00005/00108
d D 5.5 88/06/27 17:12:58 bostic 11 10
c install approved copyright notice
e
s 00009/00003/00104
d D 5.4 88/03/07 21:17:06 bostic 10 9
c added Berkeley specific header
e
s 00004/00003/00103
d D 5.3 86/05/19 04:57:00 lepreau 9 8
c make "stayopen" flags work right
e
s 00002/00002/00104
d D 5.2 86/03/09 20:25:50 donn 8 7
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00097
d D 5.1 85/05/30 12:03:16 dist 7 6
c Add copyright
e
s 00001/00000/00097
d D 4.6 83/05/23 01:22:26 sam 6 5
c now need types.h
e
s 00002/00002/00095
d D 4.5 83/01/02 16:38:41 sam 5 4
c null pointer stuff from sun
e
s 00001/00001/00096
d D 4.4 82/12/17 17:05:57 sam 4 3
c pass port numbers around in network order 
e
s 00013/00012/00084
d D 4.3 82/11/14 13:49:35 sam 3 2
c null pointer problems
e
s 00000/00001/00096
d D 4.2 82/10/05 22:19:31 sam 2 1
c rename library routines so as not conflict with gethostname
e
s 00097/00000/00000
d D 4.1 82/08/25 21:54:10 sam 1 0
c date and time created 82/08/25 21:54:10 by sam
e
u
U
t
T
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
/*
D 15
 * Copyright (c) 1983 Regents of the University of California.
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 11
E 10
 */

D 8
#ifndef lint
E 8
I 8
#if defined(LIBC_SCCS) && !defined(lint)
E 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
D 10
#endif LIBC_SCCS and not lint
E 10
I 10
#endif /* LIBC_SCCS and not lint */
E 10
E 8
E 7

D 14
#include <stdio.h>
E 14
I 6
#include <sys/types.h>
E 6
#include <sys/socket.h>
#include <netdb.h>
D 14
#include <ctype.h>
E 14
I 14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 14

#define	MAXALIASES	35

D 4
static char *PROTODB = "/usr/lib/protocols";
E 4
I 4
D 12
static char PROTODB[] = "/etc/protocols";
E 12
E 4
static FILE *protof = NULL;
static char line[BUFSIZ+1];
static struct protoent proto;
static char *proto_aliases[MAXALIASES];
D 9
static int stayopen = 0;
E 9
D 2
static unsigned long value();
E 2
D 14
static char *any();
E 14
I 9
int _proto_stayopen;
E 9

I 14
void
E 14
setprotoent(f)
	int f;
{
	if (protof == NULL)
D 12
		protof = fopen(PROTODB, "r" );
E 12
I 12
		protof = fopen(_PATH_PROTOCOLS, "r" );
E 12
	else
		rewind(protof);
D 9
	stayopen |= f;
E 9
I 9
	_proto_stayopen |= f;
E 9
}

I 14
void
E 14
endprotoent()
{
D 9
	if (protof && !stayopen) {
E 9
I 9
	if (protof) {
E 9
		fclose(protof);
		protof = NULL;
	}
I 9
	_proto_stayopen = 0;
E 9
}

struct protoent *
getprotoent()
{
	char *p;
	register char *cp, **q;

D 12
	if (protof == NULL && (protof = fopen(PROTODB, "r" )) == NULL)
E 12
I 12
	if (protof == NULL && (protof = fopen(_PATH_PROTOCOLS, "r" )) == NULL)
E 12
		return (NULL);
again:
	if ((p = fgets(line, BUFSIZ, protof)) == NULL)
		return (NULL);
	if (*p == '#')
		goto again;
D 14
	cp = any(p, "#\n");
E 14
I 14
	cp = strpbrk(p, "#\n");
E 14
	if (cp == NULL)
		goto again;
	*cp = '\0';
	proto.p_name = p;
D 14
	cp = any(p, " \t");
E 14
I 14
	cp = strpbrk(p, " \t");
E 14
	if (cp == NULL)
		goto again;
	*cp++ = '\0';
	while (*cp == ' ' || *cp == '\t')
		cp++;
D 14
	p = any(cp, " \t");
E 14
I 14
	p = strpbrk(cp, " \t");
E 14
	if (p != NULL)
		*p++ = '\0';
	proto.p_proto = atoi(cp);
D 3
	proto.p_aliases = proto_aliases;
	cp = p;
	q = proto_aliases;
	while (*cp) {
		if (*cp == ' ' || *cp == '\t') {
			cp++;
			continue;
E 3
I 3
	q = proto.p_aliases = proto_aliases;
	if (p != NULL) {
		cp = p;
D 5
		while (*cp) {
E 5
I 5
		while (cp && *cp) {
E 5
			if (*cp == ' ' || *cp == '\t') {
				cp++;
				continue;
			}
			if (q < &proto_aliases[MAXALIASES - 1])
				*q++ = cp;
D 14
			cp = any(cp, " \t");
E 14
I 14
			cp = strpbrk(cp, " \t");
E 14
D 5
			if (*cp != NULL)
E 5
I 5
			if (cp != NULL)
E 5
				*cp++ = '\0';
E 3
		}
D 3
		if (q < &proto_aliases[MAXALIASES - 1])
			*q++ = cp;
		cp = any(cp, " \t");
		if (*cp != NULL)
			*cp++ = '\0';
E 3
	}
	*q = NULL;
	return (&proto);
D 14
}

static char *
any(cp, match)
	register char *cp;
	char *match;
{
	register char *mp, c;

	while (c = *cp) {
		for (mp = match; *mp; mp++)
			if (*mp == c)
				return (cp);
		cp++;
	}
	return ((char *)0);
E 14
}
E 1
