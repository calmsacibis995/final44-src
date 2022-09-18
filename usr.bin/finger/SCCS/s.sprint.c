h10122
s 00001/00001/00124
d D 8.3 95/04/28 17:36:39 bostic 14 13
c use memmove, not memcpy
e
s 00005/00002/00120
d D 8.2 95/04/28 17:35:57 bostic 13 12
c You may have already done the same (does the Alpha have alignment
c constraints? I think it does...).  I also changed it to use the libc
c err, instead of its own, and fixed most of the `gcc -Wall' complaints.
c The important changes are to memcpy the pointers from db->get and db->seq.
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00120
d D 8.1 93/06/06 14:39:24 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00036/00111
d D 5.11 91/10/27 16:15:24 bostic 11 10
c use btree instead of hashing, don't have to resort later
e
s 00015/00007/00132
d D 5.10 91/07/27 17:59:19 bostic 10 9
c finger really didn't need its own hashing scheme
e
s 00016/00010/00123
d D 5.9 91/07/27 15:58:26 bostic 9 8
c Welcome to the Wonderful World of ANSI!
e
s 00001/00001/00132
d D 5.8 90/12/04 15:18:54 bostic 8 7
c use "Login Time", not "Login"
e
s 00001/00011/00132
d D 5.7 90/06/01 16:49:54 bostic 7 6
c new copyright notice
e
s 00000/00000/00143
d D 5.6 90/02/07 08:25:18 bostic 6 5
x 3
c exclude sccs changes to remove contrib line from copyright
e
s 00006/00005/00134
d D 5.5 89/05/18 11:29:33 bostic 5 4
c print out certain types of phone numbers in US formats
e
s 00001/00001/00138
d D 5.4 89/05/11 15:54:07 bostic 4 3
c don't overflow office phone number
e
s 00000/00003/00139
d D 5.3 89/05/08 11:36:07 bostic 3 2
c clean up copyright notice
e
s 00042/00041/00100
d D 5.2 89/05/07 01:02:56 edward 2 1
c show last login time if more recent than current logins,
c cleaned up, speeded up, put people in hash table, separate login info
c from personal info
e
s 00141/00000/00000
d D 5.1 89/05/06 13:53:35 bostic 1 0
c Tony Nardo (trn@warper.jhuapl.edu) reworked the original, I
c redid his stuff; should handle multiple logons right.
e
u
U
t
T
I 1
/*
D 12
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 3
 * This code is derived from software contributed to Berkeley by
 * Tony Nardo of the Johns Hopkins University/Applied Physics Lab.
 *
E 3
D 7
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
I 9
#include <time.h>
E 9
#include <tzfile.h>
I 10
#include <db.h>
I 13
#include <err.h>
E 13
E 10
I 9
#include <pwd.h>
I 10
#include <errno.h>
E 10
#include <utmp.h>
E 9
#include <stdio.h>
I 9
#include <stdlib.h>
#include <string.h>
E 9
#include "finger.h"

D 9
extern int entries;
E 9
I 9
D 11
static int	  psort __P((const void *, const void *));
static PERSON	**sort __P((void));
E 11
static void	  stimeprint __P((WHERE *));
E 9

I 9
void
E 9
sflag_print()
{
	extern time_t now;
	register PERSON *pn;
I 2
	register WHERE *w;
E 2
D 11
	register int cnt;
E 11
I 11
	register int sflag, r;
E 11
	register char *p;
I 13
	PERSON *tmp;
E 13
D 9
	PERSON **list, **sort();
	time_t time();
D 5
	char *ctime();
E 5
I 5
	char *ctime(), *prphone();
E 9
I 9
D 11
	PERSON **list;
E 11
I 11
	DBT data, key;
E 11
E 9
E 5

D 11
	list = sort();
E 11
	/*
	 * short format --
	 *	login name
	 *	real name
	 *	terminal name (the XX of ttyXX)
	 *	if terminal writeable (add an '*' to the terminal name
	 *		if not)
	 *	if logged in show idle time and day logged in, else
	 *		show last login date and time.  If > 6 moths,
	 *		show year instead of time.
	 *	office location
	 *	office phone
	 */
#define	MAXREALNAME	20
	(void)printf("%-*s %-*s %s\n", UT_NAMESIZE, "Login", MAXREALNAME,
D 2
	    "Name", "Tty  Idle Login        Office      Office Phone");
E 2
I 2
D 5
	    "Name", "Tty  Idle  Login        Office      Office Phone");
E 5
I 5
D 8
	    "Name", "Tty  Idle  Login        Office     Office Phone");
E 8
I 8
	    "Name", "Tty  Idle  Login Time   Office     Office Phone");
E 8
E 5
E 2
D 11
	for (cnt = 0; cnt < entries; ++cnt) {
		pn = list[cnt];
E 11
I 11

	for (sflag = R_FIRST;; sflag = R_NEXT) {
		r = (*db->seq)(db, &key, &data, sflag);
		if (r == -1)
D 13
			err("db seq: %s", strerror(errno));
E 13
I 13
			err(1, "db seq");
E 13
		if (r == 1)
			break;
D 13
		pn = *(PERSON **)data.data;
E 13
I 13
D 14
		memcpy(&tmp, data.data, sizeof tmp);
E 14
I 14
		memmove(&tmp, data.data, sizeof tmp);
E 14
		pn = tmp;
E 13

E 11
D 2
		 (void)printf("%-*.*s %-*.*s ", UT_NAMESIZE, UT_NAMESIZE,
		    pn->name, MAXREALNAME, MAXREALNAME,
		    pn->realname ? pn->realname : "");
		if (!pn->loginat) {
			(void)printf("          Never logged in\n");
			continue;
E 2
I 2
		for (w = pn->whead; w != NULL; w = w->next) {
			(void)printf("%-*.*s %-*.*s ", UT_NAMESIZE, UT_NAMESIZE,
			    pn->name, MAXREALNAME, MAXREALNAME,
			    pn->realname ? pn->realname : "");
			if (!w->loginat) {
				(void)printf("  *     *  No logins   ");
				goto office;
			}
			(void)putchar(w->info == LOGGEDIN && !w->writable ?
			    '*' : ' ');
			if (*w->tty)
				(void)printf("%-2.2s ",
				    w->tty[0] != 't' || w->tty[1] != 't' ||
				    w->tty[2] != 'y' ? w->tty : w->tty + 3);
			else
				(void)printf("   ");
			if (w->info == LOGGEDIN) {
				stimeprint(w);
				(void)printf("  ");
			} else
				(void)printf("    *  ");
			p = ctime(&w->loginat);
			(void)printf("%.6s", p + 4);
			if (now - w->loginat >= SECSPERDAY * DAYSPERNYEAR / 2)
				(void)printf("  %.4s", p + 20);
			else
				(void)printf(" %.5s", p + 11);
office:			if (pn->office)
D 5
				(void)printf(" %-11.11s", pn->office);
E 5
I 5
				(void)printf(" %-10.10s", pn->office);
E 5
			else if (pn->officephone)
D 5
				(void)printf(" %-11.11s", " ");
E 5
I 5
				(void)printf(" %-10.10s", " ");
E 5
			if (pn->officephone)
D 4
				(void)printf(" %s", pn->officephone);
E 4
I 4
D 5
				(void)printf(" %-.14s", pn->officephone);
E 5
I 5
				(void)printf(" %-.15s",
				    prphone(pn->officephone));
E 5
E 4
			putchar('\n');
E 2
		}
D 2
		(void)printf(pn->info == LOGGEDIN &&
		    !pn->writable ? "*" : " ");
		if (*pn->tty)
			(void)printf("%-2.2s ",
			    pn->tty[0] != 't' || pn->tty[1] != 't' ||
			    pn->tty[2] != 'y' ? pn->tty : pn->tty + 3);
		else
			(void)printf("   ");
		stimeprint(pn);
		p = ctime(&pn->loginat);
		(void)printf(" %.6s", p + 4);
		if (now - pn->loginat >= SECSPERDAY * DAYSPERNYEAR / 2)
			(void)printf(" %.4s ", p + 20);
		else
			(void)printf(" %.5s", p + 11);
		if (pn->office)
			(void)printf(" %-11.11s", pn->office);
		else if (pn->officephone)
			(void)printf(" %-11.11s", " ");
		if (pn->officephone)
			(void)printf(" %s", pn->officephone);
		putchar('\n');
E 2
	}
D 11
}

D 9
PERSON **
E 9
I 9
static PERSON **
E 9
sort()
{
D 2
	extern PERSON *head;
	register PERSON *pn;
	register int cnt;
E 2
I 2
D 10
	register PERSON *pn, **lp;
E 10
I 10
	register PERSON **lp;
	register int sflag, r;
E 10
E 2
	PERSON **list;
I 10
	DBT data, key;
E 10
D 9
	int psort();
	char *malloc();
E 9

D 10
	if (!(list = (PERSON **)malloc((u_int)(entries * sizeof(PERSON *))))) {
		(void)fprintf(stderr, "finger: out of space.\n");
		exit(1);
E 10
I 10
	if ((list = malloc((u_int)(entries * sizeof(PERSON *)))) == NULL)
		err("%s", strerror(errno));
	for (sflag = R_FIRST, lp = list;; sflag = R_NEXT) {
		r = (*db->seq)(db, &key, &data, sflag);
		if (r == -1)
			err("db seq: %s", strerror(errno));
		if (r == 1)
			break;
		*lp++ = *(PERSON **)data.data;
E 10
	}
D 2
	for (pn = head, cnt = 0; cnt < entries; pn = pn->next)
		list[cnt++] = pn;
E 2
I 2
D 10
	for (lp = list, pn = phead; pn != NULL; pn = pn->next)
		*lp++ = pn;
E 10
E 2
	(void)qsort(list, entries, sizeof(PERSON *), psort);
	return(list);
}

D 9
psort(p, t)
	PERSON **p, **t;
E 9
I 9

psort(a, b)
	const void *a, *b;
E 9
{
D 9
	return(strcmp((*p)->name, (*t)->name));
E 9
I 9
D 10
	return(strcmp(((PERSON *)a)->name, ((PERSON *)b)->name));
E 10
I 10
	return(strcmp((*(PERSON **)a)->name, (*(PERSON **)b)->name));
E 11
E 10
E 9
}

I 9
static void
E 9
D 2
stimeprint(pn)
	PERSON *pn;
E 2
I 2
stimeprint(w)
	WHERE *w;
E 2
{
	register struct tm *delta;

D 2
	if (pn->info != LOGGEDIN) {
		(void)printf("     ");
		return;
	}
	delta = gmtime(&pn->idletime);
E 2
I 2
	delta = gmtime(&w->idletime);
E 2
	if (!delta->tm_yday)
		if (!delta->tm_hour)
			if (!delta->tm_min)
				(void)printf("     ");
			else
				(void)printf("%5d", delta->tm_min);
		else
			(void)printf("%2d:%02d",
			    delta->tm_hour, delta->tm_min);
	else
		(void)printf("%4dd", delta->tm_yday);
}
E 1
