h24694
s 00002/00002/00170
d D 8.1 93/06/06 16:30:27 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00170
d D 5.4 92/06/16 18:49:44 bostic 5 4
c off_t's changed size
e
s 00001/00002/00171
d D 5.3 92/03/04 14:54:51 bostic 4 2
c unsigned comparisons <= 0
e
s 00007/00010/00163
d R 5.3 92/03/04 09:14:15 bostic 3 2
c use stdin instead of another file descriptor; make -[cnb] -r work
c on pipes
e
s 00010/00006/00163
d D 5.2 92/03/03 16:13:32 bostic 2 1
c make tail work like head for multiple files
e
s 00169/00000/00000
d D 5.1 91/07/21 14:50:12 bostic 1 0
c date and time created 91/07/21 14:50:12 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Edward Sze-Tyan Wang.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

/*
 * bytes -- read bytes to an offset from the end and display.
 *
 * This is the function that reads to a byte offset from the end of the input,
 * storing the data in a wrap-around buffer which is then displayed.  If the
 * rflag is set, the data is displayed in lines in reverse order, and this
 * routine has the usual nastiness of trying to find the newlines.  Otherwise,
 * it is displayed from the character closest to the beginning of the input to
 * the end.
 */
void
bytes(fp, off)
	register FILE *fp;
D 5
	long off;
E 5
I 5
	off_t off;
E 5
{
	register int ch, len, tlen;
	register char *ep, *p, *t;
	int wrap;
	char *sp;

	if ((sp = p = malloc(off)) == NULL)
D 2
		err("%s", strerror(errno));
E 2
I 2
		err(1, "%s", strerror(errno));
E 2

	for (wrap = 0, ep = p + off; (ch = getc(fp)) != EOF;) {
		*p = ch;
		if (++p == ep) {
			wrap = 1;
			p = sp;
		}
	}
D 2
	if (ferror(fp))
E 2
I 2
	if (ferror(fp)) {
E 2
		ierr();
I 2
		return;
	}
E 2

	if (rflag) {
		for (t = p - 1, len = 0; t >= sp; --t, ++len)
			if (*t == '\n' && len) {
				WR(t + 1, len);
				len = 0;
		}
		if (wrap) {
			tlen = len;
			for (t = ep - 1, len = 0; t >= p; --t, ++len)
				if (*t == '\n') {
					if (len) {
						WR(t + 1, len);
						len = 0;
					}
					if (tlen) {
						WR(sp, tlen);
						tlen = 0;
					}
				}
			if (len)
				WR(t + 1, len);
			if (tlen)
				WR(sp, tlen);
		}
	} else {
		if (wrap && (len = ep - p))
			WR(p, len);
		if (len = p - sp)
			WR(sp, len);
	}
}

/*
 * lines -- read lines to an offset from the end and display.
 *
 * This is the function that reads to a line offset from the end of the input,
 * storing the data in an array of buffers which is then displayed.  If the
 * rflag is set, the data is displayed in lines in reverse order, and this
 * routine has the usual nastiness of trying to find the newlines.  Otherwise,
 * it is displayed from the line closest to the beginning of the input to
 * the end.
 */
void
lines(fp, off)
	register FILE *fp;
D 5
	long off;
E 5
I 5
	off_t off;
E 5
{
	struct {
		u_int blen;
		u_int len;
		char *l;
	} *lines;
	register int ch;
	register char *p;
D 4
	u_int blen, cnt, recno;
	int wrap;
E 4
I 4
	int blen, cnt, recno, wrap;
E 4
	char *sp;

	if ((lines = malloc(off * sizeof(*lines))) == NULL)
D 2
		err("%s", strerror(errno));
E 2
I 2
		err(1, "%s", strerror(errno));
E 2

	sp = NULL;
	blen = cnt = recno = wrap = 0;

	while ((ch = getc(fp)) != EOF) {
		if (++cnt > blen) {
			if ((sp = realloc(sp, blen += 1024)) == NULL)
D 2
				err("%s", strerror(errno));
E 2
I 2
				err(1, "%s", strerror(errno));
E 2
			p = sp + cnt - 1;
		}
		*p++ = ch;
		if (ch == '\n') {
			if (lines[recno].blen < cnt) {
				lines[recno].blen = cnt + 256;
				if ((lines[recno].l = realloc(lines[recno].l,
				    lines[recno].blen)) == NULL)
D 2
					err("%s", strerror(errno));
E 2
I 2
					err(1, "%s", strerror(errno));
E 2
			}
			bcopy(sp, lines[recno].l, lines[recno].len = cnt);
			cnt = 0;
			p = sp;
			if (++recno == off) {
				wrap = 1;
				recno = 0;
			}
		}
	}
D 2
	if (ferror(fp))
E 2
I 2
	if (ferror(fp)) {
E 2
		ierr();
I 2
		return;
	}
E 2
	if (cnt) {
		lines[recno].l = sp;
		lines[recno].len = cnt;
		if (++recno == off) {
			wrap = 1;
			recno = 0;
		}
	}

	if (rflag) {
		for (cnt = recno - 1; cnt >= 0; --cnt)
			WR(lines[cnt].l, lines[cnt].len);
		if (wrap)
			for (cnt = off - 1; cnt >= recno; --cnt)
				WR(lines[cnt].l, lines[cnt].len);
	} else {
		if (wrap)
			for (cnt = recno; cnt < off; ++cnt)
				WR(lines[cnt].l, lines[cnt].len);
		for (cnt = 0; cnt < recno; ++cnt)
			WR(lines[cnt].l, lines[cnt].len);
	}
}
E 1
