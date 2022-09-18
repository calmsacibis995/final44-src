h21950
s 00021/00010/00518
d D 8.2 95/05/04 18:00:04 christos 5 4
c 
e
s 00002/00002/00526
d D 8.1 93/05/31 15:20:13 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00526
d D 5.3 92/07/15 09:12:34 marc 3 2
c always flush out2
e
s 00022/00000/00504
d D 5.2 92/06/23 18:07:44 marc 2 1
c add dprintf for debugging.
e
s 00504/00000/00000
d D 5.1 91/03/07 20:27:51 bostic 1 0
c date and time created 91/03/07 20:27:51 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Shell output routines.  We use our own output routines because:
 *	When a builtin command is interrupted we have to discard
 *		any pending output.
 *	When a builtin command appears in back quotes, we want to
 *		save the output of the command in a region obtained
 *		via malloc, rather than doing a fork and reading the
 *		output of the command via a pipe.
 *	Our output routines may be smaller than the stdio routines.
 */

I 5
#include <sys/ioctl.h>

E 5
#include <stdio.h>	/* defines BUFSIZ */
D 5
#include "shell.h"
#include "syntax.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
E 5
I 5
#include <string.h>
E 5
#ifdef __STDC__
D 5
#include "stdarg.h"
E 5
I 5
#include <stdarg.h>
E 5
#else
#include <varargs.h>
#endif
#include <errno.h>
I 5
#include <unistd.h>
#include <stdlib.h>
E 5

I 5
#include "shell.h"
#include "syntax.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
E 5

I 5

E 5
#define OUTBUFSIZ BUFSIZ
#define BLOCK_OUT -2		/* output to a fixed block of memory */
#define MEM_OUT -3		/* output to dynamically allocated memory */
#define OUTPUT_ERR 01		/* error occurred on output */


struct output output = {NULL, 0, NULL, OUTBUFSIZ, 1, 0};
struct output errout = {NULL, 0, NULL, 100, 2, 0};;
struct output memout = {NULL, 0, NULL, 0, MEM_OUT, 0};
struct output *out1 = &output;
struct output *out2 = &errout;



#ifdef mkinit

INCLUDE "output.h"
INCLUDE "memalloc.h"

RESET {
	out1 = &output;
	out2 = &errout;
	if (memout.buf != NULL) {
		ckfree(memout.buf);
		memout.buf = NULL;
	}
}

#endif


#ifdef notdef	/* no longer used */
/*
 * Set up an output file to write to memory rather than a file.
 */

void
open_mem(block, length, file)
	char *block;
	int length;
	struct output *file;
	{
	file->nextc = block;
	file->nleft = --length;
	file->fd = BLOCK_OUT;
	file->flags = 0;
}
#endif


void
out1str(p)
D 5
	char *p;
E 5
I 5
	const char *p;
E 5
	{
	outstr(p, out1);
}


void
out2str(p)
D 5
	char *p;
E 5
I 5
	const char *p;
E 5
	{
	outstr(p, out2);
}


void
outstr(p, file)
D 5
	register char *p;
E 5
I 5
	register const char *p;
E 5
	register struct output *file;
	{
	while (*p)
		outc(*p++, file);
I 3
	if (file == out2)
		flushout(file);
E 3
}


char out_junk[16];


void
emptyoutbuf(dest)
	struct output *dest;
	{
	int offset;

	if (dest->fd == BLOCK_OUT) {
		dest->nextc = out_junk;
		dest->nleft = sizeof out_junk;
		dest->flags |= OUTPUT_ERR;
	} else if (dest->buf == NULL) {
		INTOFF;
		dest->buf = ckmalloc(dest->bufsize);
		dest->nextc = dest->buf;
		dest->nleft = dest->bufsize;
		INTON;
	} else if (dest->fd == MEM_OUT) {
		offset = dest->bufsize;
		INTOFF;
		dest->bufsize <<= 1;
		dest->buf = ckrealloc(dest->buf, dest->bufsize);
		dest->nleft = dest->bufsize - offset;
		dest->nextc = dest->buf + offset;
		INTON;
	} else {
		flushout(dest);
	}
	dest->nleft--;
}


void
flushall() {
	flushout(&output);
	flushout(&errout);
}


void
flushout(dest)
	struct output *dest;
	{

	if (dest->buf == NULL || dest->nextc == dest->buf || dest->fd < 0)
		return;
	if (xwrite(dest->fd, dest->buf, dest->nextc - dest->buf) < 0)
		dest->flags |= OUTPUT_ERR;
	dest->nextc = dest->buf;
	dest->nleft = dest->bufsize;
}


void
freestdout() {
	INTOFF;
	if (output.buf) {
		ckfree(output.buf);
		output.buf = NULL;
		output.nleft = 0;
	}
	INTON;
}


#ifdef __STDC__
void
outfmt(struct output *file, char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	doformat(file, fmt, ap);
	va_end(ap);
}


void
out1fmt(char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	doformat(out1, fmt, ap);
	va_end(ap);
}

I 2
void
dprintf(char *fmt, ...) {
	va_list ap;
E 2

I 2
	va_start(ap, fmt);
	doformat(out2, fmt, ap);
	va_end(ap);
	flushout(out2);
}

E 2
void
fmtstr(char *outbuf, int length, char *fmt, ...) {
	va_list ap;
	struct output strout;

	va_start(ap, fmt);
	strout.nextc = outbuf;
	strout.nleft = length;
	strout.fd = BLOCK_OUT;
	strout.flags = 0;
	doformat(&strout, fmt, ap);
	outc('\0', &strout);
	if (strout.flags & OUTPUT_ERR)
		outbuf[length - 1] = '\0';
}

#else /* not __STDC__ */

void
outfmt(va_alist)
	va_dcl
	{
	va_list ap;
	struct output *file;
	char *fmt;

	va_start(ap);
	file = va_arg(ap, struct output *);
	fmt = va_arg(ap, char *);
	doformat(file, fmt, ap);
	va_end(ap);
}


void
out1fmt(va_alist)
	va_dcl
	{
	va_list ap;
	char *fmt;

	va_start(ap);
	fmt = va_arg(ap, char *);
	doformat(out1, fmt, ap);
	va_end(ap);
}

I 2
void
dprintf(va_alist)
	va_dcl
	{
	va_list ap;
	char *fmt;

	va_start(ap);
	fmt = va_arg(ap, char *);
	doformat(out2, fmt, ap);
	va_end(ap);
	flushout(out2);
}
E 2

void
fmtstr(va_alist)
	va_dcl
	{
	va_list ap;
	struct output strout;
	char *outbuf;
	int length;
	char *fmt;

	va_start(ap);
	outbuf = va_arg(ap, char *);
	length = va_arg(ap, int);
	fmt = va_arg(ap, char *);
	strout.nextc = outbuf;
	strout.nleft = length;
	strout.fd = BLOCK_OUT;
	strout.flags = 0;
	doformat(&strout, fmt, ap);
	outc('\0', &strout);
	if (strout.flags & OUTPUT_ERR)
		outbuf[length - 1] = '\0';
}
#endif /* __STDC__ */


/*
 * Formatted output.  This routine handles a subset of the printf formats:
 * - Formats supported: d, u, o, X, s, and c.
 * - The x format is also accepted but is treated like X.
 * - The l modifier is accepted.
 * - The - and # flags are accepted; # only works with the o format.
 * - Width and precision may be specified with any format except c.
 * - An * may be given for the width or precision.
 * - The obsolete practice of preceding the width with a zero to get
 *   zero padding is not supported; use the precision field.
 * - A % may be printed by writing %% in the format string.
 */

#define TEMPSIZE 24

#ifdef __STDC__
static const char digit[16] = "0123456789ABCDEF";
#else
static const char digit[17] = "0123456789ABCDEF";
#endif


void
doformat(dest, f, ap)
	register struct output *dest;
	register char *f;		/* format string */
	va_list ap;
	{
	register char c;
	char temp[TEMPSIZE];
	int flushleft;
	int sharp;
	int width;
	int prec;
	int islong;
	char *p;
	int sign;
	long l;
	unsigned long num;
	unsigned base;
	int len;
	int size;
	int pad;

	while ((c = *f++) != '\0') {
		if (c != '%') {
			outc(c, dest);
			continue;
		}
		flushleft = 0;
		sharp = 0;
		width = 0;
		prec = -1;
		islong = 0;
		for (;;) {
			if (*f == '-')
				flushleft++;
			else if (*f == '#')
				sharp++;
			else
				break;
			f++;
		}
		if (*f == '*') {
			width = va_arg(ap, int);
			f++;
		} else {
			while (is_digit(*f)) {
				width = 10 * width + digit_val(*f++);
			}
		}
		if (*f == '.') {
			if (*++f == '*') {
				prec = va_arg(ap, int);
				f++;
			} else {
				prec = 0;
				while (is_digit(*f)) {
					prec = 10 * prec + digit_val(*f++);
				}
			}
		}
		if (*f == 'l') {
			islong++;
			f++;
		}
		switch (*f) {
		case 'd':
			if (islong)
				l = va_arg(ap, long);
			else
				l = va_arg(ap, int);
			sign = 0;
			num = l;
			if (l < 0) {
				num = -l;
				sign = 1;
			}
			base = 10;
			goto number;
		case 'u':
			base = 10;
			goto uns_number;
		case 'o':
			base = 8;
			goto uns_number;
		case 'x':
			/* we don't implement 'x'; treat like 'X' */
		case 'X':
			base = 16;
uns_number:	  /* an unsigned number */
			sign = 0;
			if (islong)
				num = va_arg(ap, unsigned long);
			else
				num = va_arg(ap, unsigned int);
number:		  /* process a number */
			p = temp + TEMPSIZE - 1;
			*p = '\0';
			while (num) {
				*--p = digit[num % base];
				num /= base;
			}
			len = (temp + TEMPSIZE - 1) - p;
			if (prec < 0)
				prec = 1;
			if (sharp && *f == 'o' && prec <= len)
				prec = len + 1;
			pad = 0;
			if (width) {
				size = len;
				if (size < prec)
					size = prec;
				size += sign;
				pad = width - size;
				if (flushleft == 0) {
					while (--pad >= 0)
						outc(' ', dest);
				}
			}
			if (sign)
				outc('-', dest);
			prec -= len;
			while (--prec >= 0)
				outc('0', dest);
			while (*p)
				outc(*p++, dest);
			while (--pad >= 0)
				outc(' ', dest);
			break;
		case 's':
			p = va_arg(ap, char *);
			pad = 0;
			if (width) {
				len = strlen(p);
				if (prec >= 0 && len > prec)
					len = prec;
				pad = width - len;
				if (flushleft == 0) {
					while (--pad >= 0)
						outc(' ', dest);
				}
			}
			prec++;
			while (--prec != 0 && *p)
				outc(*p++, dest);
			while (--pad >= 0)
				outc(' ', dest);
			break;
		case 'c':
			c = va_arg(ap, int);
			outc(c, dest);
			break;
		default:
			outc(*f, dest);
			break;
		}
		f++;
	}
}



/*
 * Version of write which resumes after a signal is caught.
 */

int
xwrite(fd, buf, nbytes)
	int fd;
	char *buf;
	int nbytes;
	{
	int ntry;
	int i;
	int n;

	n = nbytes;
	ntry = 0;
	for (;;) {
		i = write(fd, buf, n);
		if (i > 0) {
			if ((n -= i) <= 0)
				return nbytes;
			buf += i;
			ntry = 0;
		} else if (i == 0) {
			if (++ntry > 10)
				return nbytes - n;
		} else if (errno != EINTR) {
			return -1;
		}
	}
}


/*
 * Version of ioctl that retries after a signal is caught.
I 5
 * XXX unused function
E 5
 */

int
D 5
xioctl(fd, request, arg) {
E 5
I 5
xioctl(fd, request, arg) 
	int fd;
	unsigned long request;
	char * arg;
{
E 5
	int i;

	while ((i = ioctl(fd, request, arg)) == -1 && errno == EINTR);
	return i;
}
E 1
