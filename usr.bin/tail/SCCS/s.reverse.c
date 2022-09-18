h61111
s 00002/00002/00231
d D 8.1 93/06/06 16:30:30 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00228
d D 5.8 93/03/19 15:47:45 bostic 9 8
c unmap the memory when done, other might run out
e
s 00009/00002/00221
d D 5.7 92/06/24 09:41:21 bostic 8 7
c delete MAP_FILE, check file size before mmap'ing, print file name on
c error
e
s 00002/00002/00221
d D 5.6 92/06/21 13:41:24 bostic 7 6
c fixes without testing for mmap, lseek, fseek when quads went in
e
s 00003/00003/00220
d D 5.5 92/03/04 14:55:21 bostic 6 4
c make -r work again (add RBYTES and RLINES cases into switch)
e
s 00014/00017/00206
d R 5.5 92/03/04 09:14:16 bostic 5 4
c use stdin instead of another file descriptor; make -[cnb] -r work
c on pipes
e
s 00006/00004/00217
d D 5.4 92/03/03 16:13:33 bostic 4 3
c make tail work like head for multiple files
e
s 00004/00002/00217
d D 5.3 92/02/12 15:28:19 bostic 3 2
c fix so if falls off the beginning of the file doesn't discard first byte
e
s 00002/00001/00217
d D 5.2 91/10/21 11:39:58 bostic 2 1
c mmap returns -1 on error, not NULL
e
s 00218/00000/00000
d D 5.1 91/07/21 14:50:15 bostic 1 0
c date and time created 91/07/21 14:50:15 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Edward Sze-Tyan Wang.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/mman.h>
I 8

#include <limits.h>
E 8
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

static void r_buf __P((FILE *));
static void r_reg __P((FILE *, enum STYLE, long, struct stat *));

/*
 * reverse -- display input in reverse order by line.
 *
 * There are six separate cases for this -- regular and non-regular
 * files by bytes, lines or the whole file.
 *
 * BYTES	display N bytes
 *	REG	mmap the file and display the lines
 *	NOREG	cyclically read characters into a wrap-around buffer
 *
 * LINES	display N lines
 *	REG	mmap the file and display the lines
 *	NOREG	cyclically read lines into a wrap-around array of buffers
 *
 * FILE		display the entire file
 *	REG	mmap the file and display the lines
 *	NOREG	cyclically read input into a linked list of buffers
 */
void
reverse(fp, style, off, sbp)
	FILE *fp;
	enum STYLE style;
	long off;
	struct stat *sbp;
{
	if (style != REVERSE && off == 0)
		return;

	if (S_ISREG(sbp->st_mode))
		r_reg(fp, style, off, sbp);
	else
		switch(style) {
		case FBYTES:
I 6
		case RBYTES:
E 6
			bytes(fp, off);
			break;
		case FLINES:
I 6
		case RLINES:
E 6
			lines(fp, off);
			break;
		case REVERSE:
			r_buf(fp);
			break;
		}
}

/*
 * r_reg -- display a regular file in reverse order by line.
 */
static void
r_reg(fp, style, off, sbp)
	FILE *fp;
	register enum STYLE style;
	long off;
	struct stat *sbp;
{
	register off_t size;
	register int llen;
	register char *p;
I 9
	char *start;
E 9
D 6
	int fd;
E 6

	if (!(size = sbp->st_size))
		return;

I 8
	if (size > SIZE_T_MAX) {
		err(0, "%s: %s", fname, strerror(EFBIG));
		return;
	}

E 8
D 6
	fd = fileno(fp);
E 6
D 2
	if ((p = mmap(NULL, size, PROT_READ, MAP_FILE, fd, (off_t)0)) == NULL)
E 2
I 2
D 4
	if ((p =
	    mmap(NULL, size, PROT_READ, MAP_FILE, fd, (off_t)0)) == (caddr_t)-1)
E 2
		err("%s", strerror(errno));
E 4
I 4
D 7
	if ((p = mmap(NULL,
D 6
	    size, PROT_READ, MAP_FILE, fd, (off_t)0)) == (caddr_t)-1) {
E 6
I 6
	    size, PROT_READ, MAP_FILE, fileno(fp), (off_t)0)) == (caddr_t)-1) {
E 7
I 7
D 9
	if ((p = mmap(NULL, (size_t)size,
E 9
I 9
	if ((start = mmap(NULL, (size_t)size,
E 9
D 8
	    PROT_READ, MAP_FILE, fileno(fp), (off_t)0)) == (caddr_t)-1) {
E 7
E 6
		err(0, "%s", strerror(errno));
E 8
I 8
	    PROT_READ, 0, fileno(fp), (off_t)0)) == (caddr_t)-1) {
		err(0, "%s: %s", fname, strerror(EFBIG));
E 8
		return;
	}
E 4
D 9
	p += size - 1;
E 9
I 9
	p = start + size - 1;
E 9

	if (style == RBYTES && off < size)
		size = off;

	/* Last char is special, ignore whether newline or not. */
	for (llen = 1; --size; ++llen)
		if (*--p == '\n') {
			WR(p + 1, llen);
			llen = 0;
D 3
			if (style == RLINES && !--off)
E 3
I 3
			if (style == RLINES && !--off) {
				++p;
E 3
				break;
I 3
			}
E 3
		}
	if (llen)
D 3
		WR(p + 1, llen);
E 3
I 3
		WR(p, llen);
I 9
	if (munmap(start, (size_t)sbp->st_size))
		err(0, "%s: %s", fname, strerror(errno));
E 9
E 3
}

typedef struct bf {
	struct bf *next;
	struct bf *prev;
	int len;
	char *l;
} BF;

/*
 * r_buf -- display a non-regular file in reverse order by line.
 *
 * This is the function that saves the entire input, storing the data in a
 * doubly linked list of buffers and then displays them in reverse order.
 * It has the usual nastiness of trying to find the newlines, as there's no
 * guarantee that a newline occurs anywhere in the file, let alone in any
 * particular buffer.  If we run out of memory, input is discarded (and the
 * user warned).
 */
static void
r_buf(fp)
	FILE *fp;
{
	register BF *mark, *tl, *tr;
	register int ch, len, llen;
	register char *p;
	off_t enomem;

#define	BSZ	(128 * 1024)
	for (mark = NULL, enomem = 0;;) {
		/*
		 * Allocate a new block and link it into place in a doubly
		 * linked list.  If out of memory, toss the LRU block and
		 * keep going.
		 */
		if (enomem || (tl = malloc(sizeof(BF))) == NULL ||
		    (tl->l = malloc(BSZ)) == NULL) {
			if (!mark)
D 4
				err("%s", strerror(errno));
E 4
I 4
				err(1, "%s", strerror(errno));
E 4
			tl = enomem ? tl->next : mark;
			enomem += tl->len;
		} else if (mark) {
			tl->next = mark;
			tl->prev = mark->prev;
			mark->prev->next = tl;
			mark->prev = tl;
		} else
			mark->next = mark->prev = (mark = tl);

		/* Fill the block with input data. */
		for (p = tl->l, len = 0;
		    len < BSZ && (ch = getc(fp)) != EOF; ++len)
			*p++ = ch;

		/*
		 * If no input data for this block and we tossed some data,
		 * recover it.
		 */
		if (!len) {
			if (enomem)
				enomem -= tl->len;
			tl = tl->prev;
			break;
		}

		tl->len = len;
		if (ch == EOF)
			break;
	}

	if (enomem) {
		(void)fprintf(stderr,
		    "tail: warning: %ld bytes discarded\n", enomem);
		rval = 1;
	}

	/*
	 * Step through the blocks in the reverse order read.  The last char
	 * is special, ignore whether newline or not.
	 */
	for (mark = tl;;) {
		for (p = tl->l + (len = tl->len) - 1, llen = 0; len--;
		    --p, ++llen)
			if (*p == '\n') {
				if (llen) {
					WR(p + 1, llen);
					llen = 0;
				}
				if (tl == mark)
					continue;
				for (tr = tl->next; tr->len; tr = tr->next) {
					WR(tr->l, tr->len);
					tr->len = 0;
					if (tr == mark)
						break;
				}
			}
		tl->len = llen;
		if ((tl = tl->prev) == mark)
			break;
	}
	tl = tl->next;
	if (tl->len) {
		WR(tl->l, tl->len);
		tl->len = 0;
	}
	while ((tl = tl->next)->len) {
		WR(tl->l, tl->len);
		tl->len = 0;
	}
}
E 1
