h35225
s 00002/00002/00206
d D 8.1 93/06/06 16:30:17 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00207
d D 5.9 93/03/19 15:49:04 bostic 11 10
c was munmap'ing the wrong size
e
s 00011/00004/00197
d D 5.8 92/06/24 09:41:20 bostic 10 9
c delete MAP_FILE, check file size before mmap'ing, print file name on
c error
e
s 00003/00003/00198
d D 5.7 92/06/21 13:41:23 bostic 9 8
c fixes without testing for mmap, lseek, fseek when quads went in
e
s 00007/00002/00194
d D 5.6 92/05/14 15:41:27 bostic 8 5
c add munmap call
e
s 00001/00002/00194
d R 5.6 92/03/04 14:41:51 bostic 7 5
c don't need to clear the error if returning
e
s 00024/00026/00170
d R 5.6 92/03/04 09:14:14 bostic 6 5
c use stdin instead of another file descriptor; make -[cnb] -r work
c on pipes
e
s 00033/00013/00163
d D 5.5 92/03/03 16:13:29 bostic 5 4
c make tail work like head for multiple files
e
s 00005/00004/00171
d D 5.4 92/02/12 14:09:27 bostic 4 3
c fix so if falls off the beginning of the file doesn't discard first byte
e
s 00002/00002/00173
d D 5.3 91/10/21 11:39:57 bostic 3 2
c mmap returns -1 on error, not NULL
e
s 00001/00000/00174
d D 5.2 91/07/26 16:03:31 bostic 2 1
c flush any non-newline terminated output
e
s 00174/00000/00000
d D 5.1 91/07/21 14:50:06 bostic 1 0
c date and time created 91/07/21 14:50:06 by bostic
e
u
U
t
T
I 1
/*-
D 12
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
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
#include <sys/time.h>
#include <sys/mman.h>
I 10

#include <limits.h>
E 10
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

static void rlines __P((FILE *, long, struct stat *));

/*
 * forward -- display the file, from an offset, forward.
 *
 * There are eight separate cases for this -- regular and non-regular
 * files, by bytes or lines and from the beginning or end of the file.
 *
 * FBYTES	byte offset from the beginning of the file
 *	REG	seek
 *	NOREG	read, counting bytes
 *
 * FLINES	line offset from the beginning of the file
 *	REG	read, counting lines
 *	NOREG	read, counting lines
 *
 * RBYTES	byte offset from the end of the file
 *	REG	seek
 *	NOREG	cyclically read characters into a wrap-around buffer
 *
 * RLINES
 *	REG	mmap the file and step back until reach the correct offset.
 *	NOREG	cyclically read lines into a wrap-around array of buffers
 */
void
forward(fp, style, off, sbp)
	FILE *fp;
	enum STYLE style;
	long off;
	struct stat *sbp;
{
	register int ch;
	struct timeval second;
	fd_set zero;

	switch(style) {
	case FBYTES:
		if (off == 0)
			break;
		if (S_ISREG(sbp->st_mode)) {
			if (sbp->st_size < off)
				off = sbp->st_size;
D 5
			if (fseek(fp, off, SEEK_SET) == -1)
E 5
I 5
			if (fseek(fp, off, SEEK_SET) == -1) {
E 5
				ierr();
I 5
				return;
			}
E 5
		} else while (off--)
			if ((ch = getc(fp)) == EOF) {
D 5
				if (ferror(fp))
E 5
I 5
				if (ferror(fp)) {
E 5
					ierr();
D 5
					break;
E 5
I 5
					return;
E 5
				}
I 5
				break;
			}
E 5
		break;
	case FLINES:
		if (off == 0)
			break;
		for (;;) {
			if ((ch = getc(fp)) == EOF) {
D 5
				if (ferror(fp))
E 5
I 5
				if (ferror(fp)) {
E 5
					ierr();
I 5
					return;
				}
E 5
				break;
			}
			if (ch == '\n' && !--off)
				break;
		}
		break;
	case RBYTES:
		if (S_ISREG(sbp->st_mode)) {
			if (sbp->st_size >= off &&
D 5
			    fseek(fp, -off, SEEK_END) == -1)
E 5
I 5
			    fseek(fp, -off, SEEK_END) == -1) {
E 5
				ierr();
I 5
				return;
			}
E 5
		} else if (off == 0) {
			while (getc(fp) != EOF);
D 5
			if (ferror(fp))
E 5
I 5
			if (ferror(fp)) {
E 5
				ierr();
I 5
				return;
			}
E 5
		} else
			bytes(fp, off);
		break;
	case RLINES:
		if (S_ISREG(sbp->st_mode))
			if (!off) {
D 5
				if (fseek(fp, 0L, SEEK_END) == -1)
E 5
I 5
				if (fseek(fp, 0L, SEEK_END) == -1) {
E 5
					ierr();
I 5
					return;
				}
E 5
			} else
				rlines(fp, off, sbp);
		else if (off == 0) {
			while (getc(fp) != EOF);
D 5
			if (ferror(fp))
E 5
I 5
			if (ferror(fp)) {
E 5
				ierr();
I 5
				return;
			}
E 5
		} else
			lines(fp, off);
		break;
	}

	/*
	 * We pause for one second after displaying any data that has
	 * accumulated since we read the file.
	 */
	if (fflag) {
		FD_ZERO(&zero);
		second.tv_sec = 1;
		second.tv_usec = 0;
	}

	for (;;) {
		while ((ch = getc(fp)) != EOF)
			if (putchar(ch) == EOF)
				oerr();
D 5
		if (ferror(fp))
E 5
I 5
		if (ferror(fp)) {
E 5
			ierr();
I 5
			return;
		}
E 5
I 2
		(void)fflush(stdout);
E 2
		if (!fflag)
			break;
		/* Sleep(3) is eight system calls.  Do it fast. */
		if (select(0, &zero, &zero, &zero, &second) == -1)
D 5
			err("select: %s", strerror(errno));
E 5
I 5
			err(1, "select: %s", strerror(errno));
E 5
		clearerr(fp);
	}
}

/*
 * rlines -- display the last offset lines of the file.
 */
static void
rlines(fp, off, sbp)
	FILE *fp;
	long off;
	struct stat *sbp;
{
	register off_t size;
	register char *p;
I 8
	char *start;
E 8

	if (!(size = sbp->st_size))
		return;

I 10
	if (size > SIZE_T_MAX) {
		err(0, "%s: %s", fname, strerror(EFBIG));
		return;
	}

E 10
D 3
	if ((p = mmap(NULL, size,
	    PROT_READ, MAP_FILE, fileno(fp), (off_t)0)) == NULL)
E 3
I 3
D 8
	if ((p = mmap(NULL,
E 8
I 8
D 9
	if ((start = mmap(NULL,
E 8
D 5
	    size, PROT_READ, MAP_FILE, fileno(fp), (off_t)0)) == (caddr_t)-1)
E 3
		err("%s", strerror(errno));
E 5
I 5
	    size, PROT_READ, MAP_FILE, fileno(fp), (off_t)0)) == (caddr_t)-1) {
E 9
I 9
	if ((start = mmap(NULL, (size_t)size,
D 10
	    PROT_READ, MAP_FILE, fileno(fp), (off_t)0)) == (caddr_t)-1) {
E 9
		err(0, "%s", strerror(errno));
E 10
I 10
	    PROT_READ, 0, fileno(fp), (off_t)0)) == (caddr_t)-1) {
		err(0, "%s: %s", fname, strerror(EFBIG));
E 10
		return;
	}
E 5
D 4
	p += size - 1;
E 4

	/* Last char is special, ignore whether newline or not. */
D 4
	while (--size)
		if (*--p == '\n' && !--off)
E 4
I 4
D 8
	for (p += size - 1; --size;)
E 8
I 8
	for (p = start + size - 1; --size;)
E 8
		if (*--p == '\n' && !--off) {
			++p;
E 4
			break;
I 4
		}
E 4

	/* Set the file pointer to reflect the length displayed. */
	size = sbp->st_size - size;
D 4
	WR(p + 1, size);
E 4
I 4
	WR(p, size);
E 4
D 5
	if (fseek(fp, sbp->st_size, SEEK_SET) == -1)
E 5
I 5
D 9
	if (fseek(fp, sbp->st_size, SEEK_SET) == -1) {
E 9
I 9
	if (fseek(fp, (long)sbp->st_size, SEEK_SET) == -1) {
E 9
E 5
		ierr();
I 8
		return;
	}
D 10
	if (munmap(start, size)) {
		err(0, "%s", strerror(errno));
E 10
I 10
D 11
	if (munmap(start, (size_t)size)) {
E 11
I 11
	if (munmap(start, (size_t)sbp->st_size)) {
E 11
		err(0, "%s: %s", fname, strerror(errno));
E 10
E 8
I 5
		return;
	}
E 5
}
E 1
