h41015
s 00002/00002/00171
d D 8.1 93/06/04 12:03:26 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00011/00159
d D 5.10 91/03/23 14:13:06 karels 12 11
c close /etc/ttys in getttynam
e
s 00004/00002/00166
d D 5.9 91/02/23 19:49:46 donn 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00167
d D 5.8 90/06/01 14:11:17 bostic 10 9
c new copyright notice
e
s 00001/00001/00177
d D 5.7 90/05/15 19:45:44 bostic 9 8
c string.h is ANSI C include file
e
s 00008/00006/00170
d D 5.6 90/02/22 13:06:03 bostic 8 7
c p not set on long /etc/ttys lines, causing premature loop termination
e
s 00115/00076/00061
d D 5.5 89/09/19 11:24:12 bostic 7 6
c handle long lines; move defines into ttyent.h; move getttynam() into
c getttyent.c; make all fields null pointers if unspecified; make setttyent()
c and endtttyent() return values; move field explanations into ttys.5;
c document it all.  Add Berkeley specific copyright notice.
e
s 00024/00029/00113
d D 5.4 86/05/19 23:04:07 karels 6 5
c comments now delimited, quoted strings may escape quotes, can quote
c anything but flags
c 
e
s 00004/00003/00138
d D 5.3 86/05/19 15:15:57 lepreau 5 4
c magic flag strings must be tokens
e
s 00002/00002/00139
d D 5.2 86/03/09 19:48:50 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00132
d D 5.1 85/05/30 10:42:51 dist 3 2
c Add copyright
e
s 00062/00013/00071
d D 4.2 85/01/30 12:07:05 ralph 2 1
c added quoted fields & support for windows.
e
s 00084/00000/00000
d D 4.1 84/04/27 10:25:32 ralph 1 0
c date and time created 84/04/27 10:25:32 by ralph
e
u
U
t
T
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
E 6
I 6
D 7
 * Copyright (c) 1985 Regents of the University of California.
E 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 7
 */

D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 4
E 3

I 7
#include <ttyent.h>
E 7
#include <stdio.h>
I 7
#include <ctype.h>
E 7
I 2
D 9
#include <strings.h>
E 9
I 9
#include <string.h>
E 9
E 2
D 7
#include <ttyent.h>
E 7

D 7
static char TTYFILE[] = "/etc/ttys";
E 7
D 6
static char EMPTY[] = "";
E 6
I 6
static char zapchar;
E 6
D 7
static FILE *tf = NULL;
D 2
static char line[BUFSIZ+1];
E 2
I 2
#define LINE 256
static char line[LINE];
E 2
static struct ttyent tty;
E 7
I 7
static FILE *tf;
E 7

D 7
setttyent()
E 7
I 7
struct ttyent *
getttynam(tty)
D 11
	char *tty;
E 11
I 11
	const char *tty;
E 11
E 7
{
D 7
	if (tf == NULL)
		tf = fopen(TTYFILE, "r");
	else
		rewind(tf);
E 7
I 7
	register struct ttyent *t;

	setttyent();
	while (t = getttyent())
		if (!strcmp(tty, t->ty_name))
			break;
D 12
	return(t);
E 12
I 12
	endttyent();
	return (t);
E 12
E 7
}

D 7
endttyent()
E 7
I 7
struct ttyent *
getttyent()
E 7
{
D 7
	if (tf != NULL) {
		(void) fclose(tf);
		tf = NULL;
E 7
I 7
	static struct ttyent tty;
	register int c;
	register char *p;
#define	MAXLINELENGTH	100
	static char line[MAXLINELENGTH];
D 11
	char *skip(), *value();
E 11
I 11
	static char *skip(), *value();
E 11

	if (!tf && !setttyent())
D 12
		return(NULL);
E 12
I 12
		return (NULL);
E 12
D 8
	do {
		if (!fgets(line, sizeof(line), tf))
E 8
I 8
	for (;;) {
		if (!fgets(p = line, sizeof(line), tf))
E 8
D 12
			return(NULL);
E 12
I 12
			return (NULL);
E 12
		/* skip lines that are too big */
D 8
		if (!index(line, '\n')) {
E 8
I 8
		if (!index(p, '\n')) {
E 8
			while ((c = getc(tf)) != '\n' && c != EOF)
				;
			continue;
		}
D 8
		for (p = line; isspace(*p); ++p)
			;
	} while (!*p || *p == '#');
E 8
I 8
		while (isspace(*p))
			++p;
		if (*p && *p != '#')
			break;
	}
E 8

	zapchar = 0;
	tty.ty_name = p;
	p = skip(p);
	if (!*(tty.ty_getty = p))
		tty.ty_getty = tty.ty_type = NULL;
	else {
		p = skip(p);
		if (!*(tty.ty_type = p))
			tty.ty_type = NULL;
		else
			p = skip(p);
	}
	tty.ty_status = 0;
	tty.ty_window = NULL;

#define	scmp(e)	!strncmp(p, e, sizeof(e) - 1) && isspace(p[sizeof(e) - 1])
#define	vcmp(e)	!strncmp(p, e, sizeof(e) - 1) && p[sizeof(e) - 1] == '='
	for (; *p; p = skip(p)) {
		if (scmp(_TTYS_OFF))
			tty.ty_status &= ~TTY_ON;
		else if (scmp(_TTYS_ON))
			tty.ty_status |= TTY_ON;
		else if (scmp(_TTYS_SECURE))
			tty.ty_status |= TTY_SECURE;
		else if (vcmp(_TTYS_WINDOW))
			tty.ty_window = value(p);
		else
			break;
E 7
	}
I 7

	if (zapchar == '#' || *p == '#')
		while ((c = *++p) == ' ' || c == '\t')
			;
	tty.ty_comment = p;
	if (*p == 0)
		tty.ty_comment = 0;
	if (p = index(p, '\n'))
		*p = '\0';
D 12
	return(&tty);
E 12
I 12
	return (&tty);
E 12
E 7
}

I 2
D 6
#define QUOTED 1
E 6
I 6
D 7
#define QUOTED	1
E 7
I 7
#define	QUOTED	1
E 7
E 6

/*
D 6
 * Skip over the current field and 
 * return a pointer to the next field.
E 6
I 6
D 7
 * Skip over the current field, removing quotes,
 * and return a pointer to the next field.
E 7
I 7
 * Skip over the current field, removing quotes, and return a pointer to
 * the next field.
E 7
E 6
 */
E 2
static char *
skip(p)
D 2
register char *p;
E 2
I 2
	register char *p;
E 2
{
I 6
D 7
	register char *t = p;
E 6
	register int c;
I 2
	register int q = 0;
E 7
I 7
	register char *t;
	register int c, q;
E 7
E 2

D 2
	while ((c = *p) != '\0') {
E 2
I 2
D 7
	for (; (c = *p) != '\0'; p++) {
E 7
I 7
	for (q = 0, t = p; (c = *p) != '\0'; p++) {
E 7
		if (c == '"') {
			q ^= QUOTED;	/* obscure, but nice */
			continue;
		}
I 6
		if (q == QUOTED && *p == '\\' && *(p+1) == '"')
			p++;
		*t++ = *p;
E 6
		if (q == QUOTED)
			continue;
E 2
		if (c == '#') {
D 6
			*p = '\0';
E 6
I 6
			zapchar = c;
			*p = 0;
E 6
			break;
		}
		if (c == '\t' || c == ' ' || c == '\n') {
D 6
			*p++ = '\0';
E 6
I 6
			zapchar = c;
			*p++ = 0;
E 6
			while ((c = *p) == '\t' || c == ' ' || c == '\n')
				p++;
			break;
		}
D 2
		p++;
E 2
	}
I 6
	*--t = '\0';
E 6
D 7
	return (p);
E 7
I 7
D 12
	return(p);
E 12
I 12
	return (p);
E 12
E 7
}

I 2
static char *
value(p)
	register char *p;
{
D 7
	if ((p = index(p,'=')) == 0)
		return(NULL);
	p++;			/* get past the = sign */
	return(p);
E 7
I 7
D 12
	return((p = index(p, '=')) ? ++p : NULL);
E 12
I 12

	return ((p = index(p, '=')) ? ++p : NULL);
E 12
E 7
}

I 11
int
E 11
D 6
/* get rid of quotes. */

static
qremove(p)
	register char *p;
{
	register char *t;

	for (t = p; *p; p++)
		if (*p != '"')
			*t++ = *p;
	*t = '\0';
}

E 6
E 2
D 7
struct ttyent *
getttyent()
E 7
I 7
setttyent()
E 7
{
I 12

E 12
D 2
	register char *p, *cp;
E 2
I 2
D 7
	register char *p;
E 2
	register int c;
E 7
I 7
	if (tf) {
		(void)rewind(tf);
D 12
		return(1);
E 12
I 12
		return (1);
E 12
	} else if (tf = fopen(_PATH_TTYS, "r"))
D 12
		return(1);
	return(0);
E 12
I 12
		return (1);
	return (0);
E 12
}
E 7

I 11
int
E 11
D 7
	if (tf == NULL) {
		if ((tf = fopen(TTYFILE, "r")) == NULL)
			return (NULL);
E 7
I 7
endttyent()
{
	int rval;

	if (tf) {
		rval = !(fclose(tf) == EOF);
		tf = NULL;
D 12
		return(rval);
E 12
I 12
		return (rval);
E 12
E 7
	}
D 7
	do {
D 2
		p = fgets(line, BUFSIZ, tf);
E 2
I 2
		p = fgets(line, LINE, tf);
E 2
		if (p == NULL)
			return (NULL);
		while ((c = *p) == '\t' || c == ' ' || c == '\n')
			p++;
	} while (c == '\0' || c == '#');
I 6
	zapchar = 0;
E 6
	tty.ty_name = p;
	p = skip(p);
	tty.ty_getty = p;
	p = skip(p);
	tty.ty_type = p;
I 2
	p = skip(p);
E 2
	tty.ty_status = 0;
D 2
	for (p = skip(p); *p; p = cp) {
		cp = skip(p);
		if (strcmp(p, "on") == 0)
E 2
I 2
D 6
	tty.ty_window = EMPTY;
E 6
I 6
	tty.ty_window = NULL;
E 6
	for (; *p; p = skip(p)) {
D 5
		if (strncmp(p, "on", 2) == 0)
E 5
I 5
#define space(x) ((c = p[x]) == ' ' || c == '\t' || c == '\n')
		if (strncmp(p, "on", 2) == 0 && space(2))
E 5
E 2
			tty.ty_status |= TTY_ON;
D 2
		else if (strcmp(p, "off") == 0)
E 2
I 2
D 5
		else if (strncmp(p, "off", 3) == 0)
E 5
I 5
		else if (strncmp(p, "off", 3) == 0 && space(3))
E 5
E 2
			tty.ty_status &= ~TTY_ON;
D 2
		else if (strcmp(p, "secure") == 0)
E 2
I 2
D 5
		else if (strncmp(p, "secure", 6) == 0)
E 5
I 5
		else if (strncmp(p, "secure", 6) == 0 && space(6))
E 5
E 2
			tty.ty_status |= TTY_SECURE;
I 2
D 6
		else if (strncmp(p, "window", 6) == 0) {
			if ((tty.ty_window = value(p)) == NULL)
				tty.ty_window = EMPTY;
		} else
E 6
I 6
		else if (strncmp(p, "window=", 7) == 0)
			tty.ty_window = value(p);
		else
E 6
			break;
E 2
	}
I 6
	if (zapchar == '#' || *p == '#')
		while ((c = *++p) == ' ' || c == '\t')
			;
E 6
D 2
	tty.ty_comment = EMPTY;
	return (&tty);
E 2
I 2
	tty.ty_comment = p;
I 6
	if (*p == 0)
		tty.ty_comment = 0;
E 6
	if (p = index(p, '\n'))
		*p = '\0';
D 6
	qremove(tty.ty_getty);
	qremove(tty.ty_window);
	qremove(tty.ty_comment);
E 6
	return(&tty);
E 7
I 7
D 12
	return(1);
E 12
I 12
	return (1);
E 12
E 7
E 2
}
E 1
