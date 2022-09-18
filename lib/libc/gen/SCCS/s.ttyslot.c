h51161
s 00002/00002/00040
d D 8.1 93/06/04 12:06:45 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00038
d D 5.6 91/02/23 19:50:12 donn 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00038
d D 5.5 90/06/01 14:17:20 bostic 10 9
c new copyright notice
e
s 00001/00000/00048
d D 5.4 90/03/29 15:25:24 mckusick 9 8
c call setttyent() before calling getttyent(); bug report 4.3BSD-tahoe/lib/30
e
s 00034/00034/00014
d D 5.3 88/08/31 22:51:58 bostic 8 7
c from scratch; add Berkeley specific header
e
s 00002/00002/00046
d D 5.2 86/03/09 20:00:42 donn 7 6
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00039
d D 5.1 85/06/05 12:41:46 mckusick 6 5
c Add copyright
e
s 00001/00001/00039
d D 4.4 85/01/30 08:52:37 ralph 5 3
c remove unused register variable.
e
s 00000/00000/00040
d R 4.4 85/01/30 08:51:33 ralph 4 3
c remove unused register variable.
e
s 00007/00040/00033
d D 4.3 84/04/27 10:32:11 ralph 3 2
c new versions which use getttyent(3).
e
s 00031/00017/00042
d D 4.2 84/04/03 23:34:57 sam 2 1
c eliminate 1 character reads 
e
s 00059/00000/00000
d D 4.1 80/12/21 16:40:27 wnj 1 0
c date and time created 80/12/21 16:40:27 by wnj
e
u
U
t
T
I 1
D 6
/* %W% (Berkeley) %G% */
E 6
I 6
/*
D 8
 * Copyright (c) 1984 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 12
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
 */

D 7
#ifndef lint
E 7
I 7
#if defined(LIBC_SCCS) && !defined(lint)
E 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
D 8
#endif LIBC_SCCS and not lint
E 8
I 8
#endif /* LIBC_SCCS and not lint */
E 8
E 7
E 6
I 2

E 2
D 8
/*
 * Return the number of the slot in the utmp file
 * corresponding to the current user: try for file 0, 1, 2.
 * Definition is the line number in the /etc/ttys file.
 */
E 8
I 2
D 3
#include <sys/file.h>
E 3
I 3
#include <ttyent.h>
I 8
#include <stdio.h>
I 11
#include <string.h>
#include <unistd.h>
E 11
E 8
E 3
E 2

I 11
int
E 11
D 2

E 2
D 8
char	*ttyname();
D 3
char	*getttys();
E 3
char	*rindex();
D 3
static	char	ttys[]	= "/etc/ttys";
E 3

#define	NULL	0

E 8
ttyslot()
{
I 3
D 8
	register struct ttyent *ty;
E 3
	register char *tp, *p;
D 5
	register s, tf;
E 5
I 5
	register s;
E 8
I 8
	register struct ttyent *ttyp;
	register int slot;
	register char *p;
	int cnt;
D 11
	char *name, *rindex(), *ttyname();
E 11
I 11
	char *name;
E 11
E 8
E 5

I 9
	setttyent();
E 9
D 2
	if ((tp=ttyname(0))==NULL && (tp=ttyname(1))==NULL && (tp=ttyname(2))==NULL)
E 2
I 2
D 8
	if ((tp = ttyname(0)) == NULL &&
	    (tp = ttyname(1)) == NULL &&
	    (tp = ttyname(2)) == NULL)
E 2
		return(0);
	if ((p = rindex(tp, '/')) == NULL)
		p = tp;
	else
		p++;
D 2
	if ((tf=open(ttys, 0)) < 0)
		return(0);
E 2
I 2
D 3
	if ((tf = open(ttys, O_RDONLY)) < 0)
		return (0);
E 3
I 3
	setttyent();
E 3
E 2
	s = 0;
D 3
	while (tp = getttys(tf)) {
E 3
I 3
	while ((ty = getttyent()) != NULL) {
E 3
		s++;
D 2
		if (strcmp(p, tp)==0) {
E 2
I 2
D 3
		if (strcmp(p, tp) == 0) {
E 2
			close(tf);
E 3
I 3
		if (strcmp(ty->ty_name, p) == 0) {
			endttyent();
E 3
D 2
			return(s);
E 2
I 2
			return (s);
E 8
I 8
	for (cnt = 0; cnt < 3; ++cnt) 
		if (name = ttyname(cnt)) {
			if (p = rindex(name, '/')) 
				++p;
			else
				p = name;
			for (slot = 1; ttyp = getttyent(); ++slot)
				if (!strcmp(ttyp->ty_name, p)) {
					endttyent();
					return(slot);
				}
			break;
E 8
E 2
		}
D 8
	}
E 8
D 3
	close(tf);
E 3
I 3
	endttyent();
E 3
D 2
	return(0);
E 2
I 2
D 8
	return (0);
E 8
I 8
	return(0);
E 8
E 2
D 3
}

I 2
#define	BUFSIZ	1024

E 2
static char *
getttys(f)
{
D 2
	static char line[32];
E 2
I 2
	static char buf[BUFSIZ + 1], *next = &buf[BUFSIZ + 1];
E 2
	register char *lp;
I 2
	char *start;
E 2

D 2
	lp = line;
E 2
	for (;;) {
D 2
		if (read(f, lp, 1) != 1)
			return(NULL);
		if (*lp =='\n') {
			*lp = '\0';
			return(line+2);
E 2
I 2
		if (next >= &buf[BUFSIZ]) {
			int n = read(f, buf, BUFSIZ);

			if (n <= 0)
				return (NULL);
			buf[n] = '\0';
			next = &buf[0];
E 2
		}
D 2
		if (lp >= &line[32])
			return(line+2);
		lp++;
E 2
I 2
		for (lp = next; *lp && *lp != '\n'; lp++)
			;
		if (*lp == '\n') {
			*lp++ = '\0';
			start = next;
			next = lp;
			return (start + 2);
		}
		lseek(f, next - lp, L_INCR);
		next = lp;
E 2
	}
E 3
}
E 1
