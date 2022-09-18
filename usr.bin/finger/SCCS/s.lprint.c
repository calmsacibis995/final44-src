h58988
s 00001/00001/00309
d D 8.3 95/04/28 17:36:38 bostic 20 19
c use memmove, not memcpy
e
s 00005/00002/00305
d D 8.2 95/04/28 17:35:55 bostic 19 18
c You may have already done the same (does the Alpha have alignment
c constraints? I think it does...).  I also changed it to use the libc
c err, instead of its own, and fixed most of the `gcc -Wall' complaints.
c The important changes are to memcpy the pointers from db->get and db->seq.
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00305
d D 8.1 93/06/06 14:39:14 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00306
d D 5.17 91/10/27 16:12:17 bostic 17 16
c lint
e
s 00013/00004/00294
d D 5.16 91/07/27 17:59:17 bostic 16 15
c finger really didn't need its own hashing scheme
e
s 00017/00003/00281
d D 5.15 91/07/27 15:58:24 bostic 15 14
c Welcome to the Wonderful World of ANSI!
e
s 00045/00012/00239
d D 5.14 91/07/27 15:12:43 bostic 14 13
c display .forward files; if short file, put on same line as header
e
s 00004/00003/00247
d D 5.13 90/10/31 14:04:52 bostic 13 12
c make the date outputs consistent, don't print newline from ctime
e
s 00001/00001/00249
d D 5.12 90/06/24 23:27:33 bostic 12 11
c don't need pathnames.h, just paths.h
e
s 00014/00008/00236
d D 5.11 90/06/05 19:00:43 bostic 11 10
c add timezone to the long output
e
s 00001/00011/00243
d D 5.10 90/06/01 16:49:36 bostic 10 9
c new copyright notice
e
s 00000/00000/00254
d D 5.9 90/02/07 08:25:16 bostic 9 8
x 3
c exclude sccs changes to remove contrib line from copyright
e
s 00007/00005/00244
d D 5.8 89/10/01 15:11:47 edward 8 7
c correct printing of \n at the end of .plan; and use fopen() not freopen()
e
s 00001/00001/00248
d D 5.7 89/09/02 10:14:05 bostic 7 6
c don't let \v, \f etc. through, \f clears screen for SUNs
e
s 00027/00007/00222
d D 5.6 89/09/01 08:57:38 bostic 6 5
c don't display meta/control chars; bug report 4.3BSD/usr.bin/213
e
s 00005/00004/00224
d D 5.5 89/05/18 11:29:30 bostic 5 4
c print out certain types of phone numbers in US formats
e
s 00001/00040/00227
d D 5.4 89/05/10 15:37:42 bostic 4 3
c don't bother reporting on mail -- it's never going to be right
e
s 00000/00003/00267
d D 5.3 89/05/08 11:36:04 bostic 3 2
c clean up copyright notice
e
s 00035/00051/00235
d D 5.2 89/05/07 01:02:54 edward 2 1
c show last login time if more recent than current logins,
c cleaned up, speeded up, put people in hash table, separate login info
c from personal info
e
s 00286/00000/00000
d D 5.1 89/05/06 13:53:32 bostic 1 0
c Tony Nardo (trn@warper.jhuapl.edu) reworked the original, I
c redid his stuff; should handle multiple logons right.
e
u
U
t
T
I 1
/*
D 18
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 3
 * This code is derived from software contributed to Berkeley by
 * Tony Nardo of the Johns Hopkins University/Applied Physics Lab.
 *
E 3
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 15
#include <sys/file.h>
E 15
#include <sys/stat.h>
#include <sys/time.h>
I 15
#include <fcntl.h>
#include <time.h>
E 15
#include <tzfile.h>
I 16
#include <db.h>
I 19
#include <err.h>
E 19
E 16
I 15
#include <pwd.h>
#include <utmp.h>
I 16
#include <errno.h>
E 16
#include <unistd.h>
E 15
#include <stdio.h>
I 6
#include <ctype.h>
I 15
#include <string.h>
E 15
I 12
#include <paths.h>
E 12
E 6
#include "finger.h"
D 12
#include "pathnames.h"
E 12

#define	LINE_LEN	80
#define	TAB_LEN		8		/* 8 spaces between tabs */
I 14
#define	_PATH_FORWARD	".forward"
E 14
#define	_PATH_PLAN	".plan"
#define	_PATH_PROJECT	".project"

I 15
static int	demi_print __P((char *, int));
static void	lprint __P((PERSON *));
static int	show_text __P((char *, char *, char *));
static void	vputc __P((int));

void
E 15
lflag_print()
{
D 2
	extern PERSON *head;
E 2
	extern int pplan;
	register PERSON *pn;
I 16
	register int sflag, r;
I 19
	PERSON *tmp;
E 19
	DBT data, key;
E 16

D 2
	for (pn = head;;) {
		if (pn->info == PRINTED) {
			if (!(pn = pn->next))
				break;
			continue;
		}
E 2
I 2
D 16
	for (pn = phead;;) {
E 16
I 16
	for (sflag = R_FIRST;; sflag = R_NEXT) {
		r = (*db->seq)(db, &key, &data, sflag);
		if (r == -1)
D 19
			err("db seq: %s", strerror(errno));
E 19
I 19
			err(1, "db seq");
E 19
		if (r == 1)
			break;
D 19
		pn = *(PERSON **)data.data;
E 19
I 19
D 20
		memcpy(&tmp, data.data, sizeof tmp);
E 20
I 20
		memmove(&tmp, data.data, sizeof tmp);
E 20
		pn = tmp;
E 19
		if (sflag != R_FIRST)
			putchar('\n');
E 16
E 2
		lprint(pn);
		if (!pplan) {
D 2
			(void)show_text(pn->dir, _PATH_PROJECT,
			    "Project:");
E 2
I 2
D 14
			(void)show_text(pn->dir, _PATH_PROJECT, "Project:");
E 2
			if (!show_text(pn->dir, _PATH_PLAN, "Plan:"))
E 14
I 14
			(void)show_text(pn->dir,
			    _PATH_FORWARD, "Mail forwarded to");
			(void)show_text(pn->dir, _PATH_PROJECT, "Project");
			if (!show_text(pn->dir, _PATH_PLAN, "Plan"))
E 14
				(void)printf("No Plan.\n");
		}
D 16
		if (!(pn = pn->next))
			break;
		putchar('\n');
E 16
	}
}

I 15
static void
E 15
lprint(pn)
	register PERSON *pn;
{
	extern time_t now;
	register struct tm *delta;
D 2
	register PERSON *p;
E 2
I 2
	register WHERE *w;
E 2
	register int cpr, len, maxlen;
I 11
	struct tm *tp;
E 11
	int oddfield;
D 15
	time_t time();
D 5
	char *t, *ctime();
E 5
I 5
D 11
	char *t, *ctime(), *prphone();
E 11
I 11
	char *t, *tzn, *prphone();
E 15
I 15
	char *t, *tzn;
E 15
E 11
E 5

	/*
	 * long format --
	 *	login name
	 *	real name
	 *	home directory
	 *	shell
	 *	office, office phone, home phone if available
	 */
	(void)printf("Login: %-15s\t\t\tName: %s\nDirectory: %-25s",
	    pn->name, pn->realname, pn->dir);
	(void)printf("\tShell: %-s\n", *pn->shell ? pn->shell : _PATH_BSHELL);

	/*
	 * try and print office, office phone, and home phone on one line;
	 * if that fails, do line filling so it looks nice.
	 */
#define	OFFICE_TAG		"Office"
#define	OFFICE_PHONE_TAG	"Office Phone"
	oddfield = 0;
	if (pn->office && pn->officephone &&
	    strlen(pn->office) + strlen(pn->officephone) +
	    sizeof(OFFICE_TAG) + 2 <= 5 * TAB_LEN) {
D 14
		(void)sprintf(tbuf, "%s: %s, %s", OFFICE_TAG, pn->office,
D 5
		    pn->officephone);
E 5
I 5
		    prphone(pn->officephone));
E 14
I 14
		(void)snprintf(tbuf, sizeof(tbuf), "%s: %s, %s",
		    OFFICE_TAG, pn->office, prphone(pn->officephone));
E 14
E 5
		oddfield = demi_print(tbuf, oddfield);
	} else {
		if (pn->office) {
D 14
			(void)sprintf(tbuf, "%s: %s", OFFICE_TAG, pn->office);
E 14
I 14
			(void)snprintf(tbuf, sizeof(tbuf), "%s: %s",
			    OFFICE_TAG, pn->office);
E 14
			oddfield = demi_print(tbuf, oddfield);
		}
		if (pn->officephone) {
D 14
			(void)sprintf(tbuf, "%s: %s", OFFICE_PHONE_TAG,
D 5
			    pn->officephone);
E 5
I 5
			    prphone(pn->officephone));
E 14
I 14
			(void)snprintf(tbuf, sizeof(tbuf), "%s: %s",
			    OFFICE_PHONE_TAG, prphone(pn->officephone));
E 14
E 5
			oddfield = demi_print(tbuf, oddfield);
		}
	}
	if (pn->homephone) {
D 5
		(void)sprintf(tbuf, "%s: %s", "Home Phone", pn->homephone);
E 5
I 5
D 14
		(void)sprintf(tbuf, "%s: %s", "Home Phone",
E 14
I 14
		(void)snprintf(tbuf, sizeof(tbuf), "%s: %s", "Home Phone",
E 14
		    prphone(pn->homephone));
E 5
		oddfield = demi_print(tbuf, oddfield);
	}
	if (oddfield)
		putchar('\n');

	/*
D 2
	 * long format con't: if logged in
E 2
I 2
	 * long format con't: * if logged in
E 2
	 *	terminal
	 *	idle time
	 *	if messages allowed
	 *	where logged in from
I 2
	 * if not logged in
	 *	when last logged in
E 2
	 */
D 2
	if (pn->info == LOGGEDIN) {
		/* find out longest device name for this user for formatting */
		for (maxlen = -1, p = pn; p; p = p->next)
			if (!strcmp(p->name, pn->name) &&
			    (len = strlen(p->tty)) > maxlen)
				maxlen = len;
		/* find rest of entries for user */
		for (p = pn; p; p = p->next) {
			if (strcmp(p->name, pn->name))
				continue;
			p->info = PRINTED;
E 2
I 2
	/* find out longest device name for this user for formatting */
D 4
	for (w = pn->whead; w != NULL; w = w->next)
E 4
I 4
	for (w = pn->whead, maxlen = -1; w != NULL; w = w->next)
E 4
		if ((len = strlen(w->tty)) > maxlen)
			maxlen = len;
	/* find rest of entries for user */
	for (w = pn->whead; w != NULL; w = w->next) {
		switch (w->info) {
		case LOGGEDIN:
E 2
D 11
			cpr = printf("On since %16.16s on %s",
D 2
			    ctime(&p->loginat), p->tty);
E 2
I 2
			    ctime(&w->loginat), w->tty);
E 11
I 11
			tp = localtime(&w->loginat);
			t = asctime(tp);
			tzn = tp->tm_zone;
D 13
			cpr = printf("On since %16.16s (%s) on %s",
E 13
I 13
			cpr = printf("On since %.16s (%s) on %s",
E 13
			    t, tzn, w->tty);
E 11
E 2
			/*
			 * idle time is tough; if have one, print a comma,
			 * then spaces to pad out the device name, then the
			 * idle time.  Follow with a comma if a remote login.
			 */
D 2
			delta = gmtime(&p->idletime);
E 2
I 2
			delta = gmtime(&w->idletime);
E 2
			if (delta->tm_yday || delta->tm_hour || delta->tm_min) {
				cpr += printf("%-*s idle ",
D 2
				    maxlen - strlen(p->tty) + 1, ",");
E 2
I 2
				    maxlen - strlen(w->tty) + 1, ",");
E 2
				if (delta->tm_yday > 0) {
					cpr += printf("%d day%s ",
					   delta->tm_yday,
					   delta->tm_yday == 1 ? "" : "s");
				}
				cpr += printf("%d:%02d",
				    delta->tm_hour, delta->tm_min);
D 2
				if (*p->host) {
E 2
I 2
				if (*w->host) {
E 2
					putchar(',');
					++cpr;
				}
			}
D 2
			if (!p->writable)
E 2
I 2
			if (!w->writable)
E 2
				cpr += printf(" (messages off)");
D 2
			if (*p->host) {
				if (LINE_LEN < (cpr + 6 +
				    strlen(p->host))) {
					(void)printf("\n   ");
				}
				(void)printf(" from %s", p->host);
E 2
I 2
			break;
		case LASTLOG:
			if (w->loginat == 0) {
				(void)printf("Never logged in.");
				break;
E 2
			}
D 2
			(void)putchar('\n');
E 2
I 2
D 11
			t = ctime(&w->loginat);
E 11
I 11
			tp = localtime(&w->loginat);
			t = asctime(tp);
			tzn = tp->tm_zone;
E 11
			if (now - w->loginat > SECSPERDAY * DAYSPERNYEAR / 2)
D 11
				cpr = printf("Last login %10.10s, %4.4s on %s",
				    t, t + 20, w->tty);
E 11
I 11
D 13
				cpr = printf("Last login %10.10s (%s), %4.4s on %s",
E 13
I 13
				cpr =
				    printf("Last login %.16s %.4s (%s) on %s",
E 13
				    t, t + 20, tzn, w->tty);
E 11
			else
D 11
				cpr = printf("Last login %16.16s on %s",
					t, w->tty);
E 11
I 11
D 13
				cpr = printf("Last login %16.16s (%s) on %s",
E 13
I 13
				cpr = printf("Last login %.16s (%s) on %s",
E 13
				    t, tzn, w->tty);
E 11
			break;
E 2
		}
D 2
	}
	/*
	 * long format con't: if not logged in
	 *	when last logged in
	 */
	else if (!pn->loginat)
		(void)printf("Never logged in.\n");
	else {
		t = ctime(&pn->loginat);
		if (now - pn->loginat > SECSPERDAY * DAYSPERNYEAR / 2)
			cpr = printf("Last login %10.10s, %4.4s on %s",
			    t, t + 20, pn->tty);
		else
			cpr = printf("Last login %16.16s on %s", t, pn->tty);
		if (*pn->host) {
			if (LINE_LEN < (cpr + 6 + strlen(pn->host)))
E 2
I 2
		if (*w->host) {
			if (LINE_LEN < (cpr + 6 + strlen(w->host)))
E 2
				(void)printf("\n   ");
D 2
			(void)printf(" from %s", pn->host);
E 2
I 2
			(void)printf(" from %s", w->host);
E 2
		}
		putchar('\n');
	}
D 4
	/*
	 * long format con't:
	 *	mail status
	 */
	chkmail(pn);
E 4
}

I 15
static int
E 15
demi_print(str, oddfield)
	char *str;
	int oddfield;
{
	static int lenlast;
	int lenthis, maxlen;

	lenthis = strlen(str);
	if (oddfield) {
		/*
		 * We left off on an odd number of fields.  If we haven't
		 * crossed the midpoint of the screen, and we have room for
		 * the next field, print it on the same line; otherwise,
		 * print it on a new line.
		 *
		 * Note: we insist on having the right hand fields start
		 * no less than 5 tabs out.
		 */
		maxlen = 5 * TAB_LEN;
		if (maxlen < lenlast)
			maxlen = lenlast;
		if (((((maxlen / TAB_LEN) + 1) * TAB_LEN) +
		    lenthis) <= LINE_LEN) {
			while(lenlast < (4 * TAB_LEN)) {
				putchar('\t');
				lenlast += TAB_LEN;
			}
			(void)printf("\t%s\n", str);	/* force one tab */
		} else {
			(void)printf("\n%s", str);	/* go to next line */
			oddfield = !oddfield;	/* this'll be undone below */
		}
	} else
		(void)printf("%s", str);
	oddfield = !oddfield;			/* toggle odd/even marker */
	lenlast = lenthis;
	return(oddfield);
}

I 15
D 17
static
E 17
I 17
static int
E 17
E 15
show_text(directory, file_name, header)
	char *directory, *file_name, *header;
{
D 6
	register int fd, n;
E 6
I 6
D 8
	register int ch;
E 8
I 8
D 14
	register int ch, lastc;
E 14
I 14
	struct stat sb;
E 14
	register FILE *fp;
I 14
	register int ch, cnt, lastc;
	register char *p;
	int fd, nr;
E 14
E 8
E 6

D 14
	(void)sprintf(tbuf, "%s/%s", directory, file_name);
D 6
	if ((fd = open(tbuf, O_RDONLY, 0)) < 0)
E 6
I 6
D 8
	if (!freopen(tbuf, "r", stdin))
E 8
I 8
	if ((fp = fopen(tbuf, "r")) == NULL)
E 14
I 14
	(void)snprintf(tbuf, sizeof(tbuf), "%s/%s", directory, file_name);
	if ((fd = open(tbuf, O_RDONLY)) < 0 || fstat(fd, &sb) ||
	    sb.st_size == 0)
E 14
E 8
E 6
		return(0);
D 14
	(void)printf("%s\n", header);
E 14
I 14

	/* If short enough, and no newlines, show it on a single line.*/
	if (sb.st_size <= LINE_LEN - strlen(header) - 5) {
		nr = read(fd, tbuf, sizeof(tbuf));
		if (nr <= 0) {
			(void)close(fd);
			return(0);
		}
		for (p = tbuf, cnt = nr; cnt--; ++p)
			if (*p == '\n')
				break;
		if (cnt <= 1) {
			(void)printf("%s: ", header);
			for (p = tbuf, cnt = nr; cnt--; ++p)
				vputc(lastc = *p);
			if (lastc != '\n')
				(void)putchar('\n');
			(void)close(fd);
			return(1);
		}
		else
			(void)lseek(fd, 0L, SEEK_SET);
	}
	if ((fp = fdopen(fd, "r")) == NULL)
		return(0);
	(void)printf("%s:\n", header);
E 14
D 6
	(void)fflush(stdout);
	while ((n = read(fd, tbuf, sizeof(tbuf))) > 0)
		if (write(1, tbuf, n) != n)
			break;
	(void)close(fd);
E 6
I 6
D 8
	while ((ch = getchar(fp)) != EOF)
		vputc(ch);
	if (ch != '\n')
E 8
I 8
	while ((ch = getc(fp)) != EOF)
		vputc(lastc = ch);
	if (lastc != '\n')
E 8
		(void)putchar('\n');
I 8
	(void)fclose(fp);
E 8
E 6
	return(1);
I 6
}

I 15
static void
E 15
vputc(ch)
	register int ch;
{
	int meta;

	if (!isascii(ch)) {
		(void)putchar('M');
		(void)putchar('-');
		ch = toascii(ch);
		meta = 1;
	} else
		meta = 0;
D 7
	if (isprint(ch) || !meta && isspace(ch))
E 7
I 7
	if (isprint(ch) || !meta && (ch == ' ' || ch == '\t' || ch == '\n'))
E 7
		(void)putchar(ch);
	else {
		(void)putchar('^');
		(void)putchar(ch == '\177' ? '?' : ch | 0100);
	}
E 6
D 4
}

chkmail(pn)
	PERSON *pn;
{
	register char *date;
	struct stat sb;

	/*
	 * build path of user's mail box and get stats; if missing
	 * or empty, no mail.
	 */
	(void)sprintf(tbuf, "%s/%s", _PATH_MAILDIR, pn->name);
	if (stat(tbuf, &sb) < 0 || !sb.st_size) {
		(void)printf("No unread mail.\n");
		return;
	}

	/*
	 * if access time matches the modification time then we know
	 * that new mail was received but we haven't a clue as to when
	 * it was last read.
	 */
	date = ctime(&sb.st_ctime);
	if (sb.st_atime == sb.st_ctime)
		(void)printf("New mail received %16.16s.\n", date);
	else if (sb.st_atime > sb.st_ctime) {
		date = ctime(&sb.st_atime);
		(void)printf("No new mail, last read %16.16s.\n", date);
	} else {
		(void)printf("Mail received %16.16s; ", date);
		date = ctime(&sb.st_atime);
		(void)printf("last read %16.16s.\n", date);
	}
E 4
}
E 1
