h39611
s 00002/00002/00030
d D 8.1 93/06/04 12:03:44 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00006/00029
d D 5.9 93/04/28 12:26:15 bostic 15 14
c use err/warn, instead of rolling our own
e
s 00006/00032/00029
d D 5.8 91/11/12 18:47:04 mckusick 14 13
c use new library function getgrouplist
e
s 00005/00002/00056
d D 5.7 91/02/23 19:49:50 donn 13 12
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00057
d D 5.6 90/06/01 14:11:51 bostic 12 11
c new copyright notice
e
s 00008/00001/00060
d D 5.5 89/08/26 16:57:42 karels 11 10
c duplicate "effective" group id in groups, so not lost when execing setgid
e
s 00014/00003/00047
d D 5.4 88/07/18 15:28:07 bostic 10 9
c add Berkeley specific copyright
e
s 00001/00001/00049
d D 5.3 86/04/27 01:41:04 donn 9 8
c Change error return to -1 to match manual page.  Shouldn't affect anything --
c no utility that I can find ever checks the return value!
e
s 00002/00002/00048
d D 5.2 86/03/09 19:49:52 donn 8 7
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00041
d D 5.1 85/05/30 10:43:56 dist 7 6
c Add copyright
e
s 00001/00000/00041
d D 4.4 83/06/17 20:12:32 sam 6 5
c don't forget to close the file
e
s 00006/00003/00035
d D 4.3 83/05/01 19:04:12 sam 5 4
c avoid duplicate group id's; update diagnostics
e
s 00001/00001/00037
d D 4.2 83/02/15 21:59:43 mckusick 4 1
c complain about too many groups too early
e
s 00001/00001/00037
d R 4.2 83/02/15 21:57:23 mckusick 3 1
c complained too early about too many groups
e
s 00001/00001/00037
d R 4.2 83/02/10 16:55:39 sam 2 1
c group id's are short's, not int's
e
s 00038/00000/00000
d D 4.1 82/11/07 19:11:20 sam 1 0
c date and time created 82/11/07 19:11:20 by sam
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
D 16
 * Copyright (c) 1983 Regents of the University of California.
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
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

D 15
/*
 * initgroups
 */
E 15
D 13
#include <stdio.h>
E 13
#include <sys/param.h>
I 15

E 15
I 13
#include <stdio.h>
D 14
#include <string.h>
#include <unistd.h>
E 13
#include <grp.h>
E 14

D 14
struct group *getgrent();

E 14
I 13
int
E 13
initgroups(uname, agroup)
D 13
	char *uname;
E 13
I 13
	const char *uname;
E 13
	int agroup;
{
D 14
	int groups[NGROUPS], ngroups = 0;
	register struct group *grp;
	register int i;
E 14
I 14
	int groups[NGROUPS], ngroups;
E 14

D 11
	if (agroup >= 0)
E 11
I 11
D 14
	/*
	 * If installing primary group, duplicate it;
	 * the first element of groups is the effective gid
	 * and will be overwritten when a setgid file is executed.
	 */
	if (agroup >= 0) {
E 11
		groups[ngroups++] = agroup;
I 11
		groups[ngroups++] = agroup;
	}
E 11
	setgrent();
D 5
	while (grp = getgrent())
E 5
I 5
	while (grp = getgrent()) {
		if (grp->gr_gid == agroup)
			continue;
E 5
		for (i = 0; grp->gr_mem[i]; i++)
			if (!strcmp(grp->gr_mem[i], uname)) {
D 4
				groups[ngroups++] = grp->gr_gid;
E 4
				if (ngroups == NGROUPS) {
D 5
fprintf(stderr, "inigrp: %s is in too many groups\n", uname);
E 5
I 5
fprintf(stderr, "initgroups: %s is in too many groups\n", uname);
E 5
					goto toomany;
				}
I 4
				groups[ngroups++] = grp->gr_gid;
E 4
			}
I 5
	}
E 5
toomany:
I 6
	endgrent();
E 14
I 14
	ngroups = NGROUPS;
	if (getgrouplist(uname, agroup, groups, &ngroups) < 0)
D 15
		fprintf(stderr,
		    "initgroups: %s is in too many groups, using first %d\n",
E 15
I 15
		warnx("%s is in too many groups, using first %d",
E 15
		    uname, ngroups);
E 14
E 6
	if (setgroups(ngroups, groups) < 0) {
D 5
		perror("setgrp");
E 5
I 5
D 15
		perror("setgroups");
E 15
I 15
		warn("setgroups");
E 15
E 5
D 9
		return (1);
E 9
I 9
		return (-1);
E 9
	}
	return (0);
}
E 1
