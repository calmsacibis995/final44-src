h40103
s 00002/00002/00060
d D 8.1 93/06/04 13:10:36 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00051/00136/00011
d D 5.6 91/01/20 21:16:58 bostic 16 15
c new stdio; renamed from flsbuf.c
e
s 00031/00020/00116
d D 5.5 90/06/18 18:59:41 edward 15 14
c restart writes interrupted by signals but have made some progress
e
s 00008/00000/00128
d D 5.4 88/12/19 13:35:59 bostic 14 13
c add fpurge
e
s 00007/00000/00121
d D 5.3 88/09/22 16:52:58 bostic 13 12
c move _cleanup from findiop.c to flsbuf.c so lorder doesn't get confused
e
s 00002/00002/00119
d D 5.2 86/03/09 20:49:59 donn 12 11
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00111
d D 5.1 85/05/30 14:27:56 dist 11 10
c Add copyright
e
s 00002/00015/00110
d D 4.9 85/02/13 15:48:52 serge 10 9
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00002/00001/00123
d D 4.8 84/11/21 12:10:10 ralph 9 8
c fix flsbuf('\377'); make _cnt backward comp. with old putc macro.
e
s 00005/00009/00119
d D 4.7 84/06/06 14:49:45 ralph 8 6
c use malloc instead of static 8K sobuf.
e
s 00002/00009/00119
d R 4.7 84/05/15 16:54:41 ralph 7 6
c use malloc instead of static 8K sibuf and sobuf.
e
s 00001/00001/00127
d D 4.6 83/06/30 15:17:22 sam 6 5
c from sun
e
s 00001/00041/00127
d D 4.5 82/12/16 09:45:01 sam 5 4
c clean up after clem
e
s 00046/00006/00122
d D 4.4 82/12/15 21:34:52 clemc 4 3
c Fixed a bug in fclose as per Dennis Ritchie comments.
c fclose should not have any side effects.  It is supposed to sanitize
c the buffer structure when it exits.  Currently, it left most of the
c fields within the buffer structure Non-Zero.  This normally does not
c matter, BUT if fopen/setbuf/fclose/fopen.. the structure returned by the
c second fopen would already be filled in.  This is a lose!   Clem
e
s 00018/00005/00110
d D 4.3 82/10/05 22:44:00 mckusick 3 2
c utilize st_blksize field to optimize size of reads and writes
e
s 00007/00002/00108
d D 4.2 81/03/09 20:59:12 toy 2 1
c Feldman's stdio changes
e
s 00110/00000/00000
d D 4.1 80/12/21 16:50:14 wnj 1 0
c date and time created 80/12/21 16:50:14 by wnj
e
u
U
t
T
I 1
D 11
/* %W% (Berkeley) %G% */
E 11
I 11
D 16
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
/*-
D 17
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 16
 */

D 12
#ifndef lint
E 12
I 12
#if defined(LIBC_SCCS) && !defined(lint)
E 12
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif not lint
E 12
I 12
D 16
#endif LIBC_SCCS and not lint
E 16
I 16
#endif /* LIBC_SCCS and not lint */
E 16
E 12

E 11
D 16
#include	<stdio.h>
I 3
#include	<sys/types.h>
#include	<sys/stat.h>
E 16
I 16
#include <stdio.h>
#include "local.h"
E 16
E 3

D 16
char	*malloc();

_flsbuf(c, iop)
I 9
unsigned char c;
E 9
register FILE *iop;
E 16
I 16
/*
 * Write the given character into the (probably full) buffer for
 * the given file.  Flush the buffer out if it is or becomes full,
 * or if c=='\n' and the file is line buffered.
 */
__swbuf(c, fp)
	register int c;
	register FILE *fp;
E 16
{
D 16
	register char *base;
	register n, rn;
	char c1;
I 3
	int size;
	struct stat stbuf;
E 16
I 16
	register int n;
E 16
E 3
D 8
	extern char _sobuf[];
E 8

I 2
D 16
	if (iop->_flag & _IORW) {
		iop->_flag |= _IOWRT;
D 6
		iop->_flag &= ~_IOEOF;
E 6
I 6
		iop->_flag &= ~(_IOEOF|_IOREAD);
E 6
	}
E 16
I 16
	/*
	 * In case we cannot write, or longjmp takes us out early,
	 * make sure _w is 0 (if fully- or un-buffered) or -_bf._size
	 * (if line buffered) so that we will get called again.
	 * If we did not do this, a sufficient number of putc()
	 * calls might wrap _w from negative to positive.
	 */
	fp->_w = fp->_lbfsize;
	if (cantwrite(fp))
		return (EOF);
	c = (unsigned char)c;
E 16

E 2
D 16
	if ((iop->_flag&_IOWRT)==0)
		return(EOF);
tryagain:
	if (iop->_flag&_IOLBF) {
		base = iop->_base;
		*iop->_ptr++ = c;
D 3
		if (iop->_ptr >= base+BUFSIZ || c == '\n') {
E 3
I 3
D 15
		if (iop->_ptr >= base+iop->_bufsiz || c == '\n') {
E 3
			n = write(fileno(iop), base, rn = iop->_ptr - base);
E 15
I 15
		if ((rn = iop->_ptr - base) >= iop->_bufsiz || c == '\n') {
E 15
			iop->_ptr = base;
I 9
			iop->_cnt = 0;
E 9
D 15
		} else
E 15
I 15
		} else {
			/* we got here because _cnt is wrong, so fix it */
			iop->_cnt = -rn;
E 15
			rn = n = 0;
I 15
		}
E 15
D 9
		iop->_cnt = 0;
E 9
	} else if (iop->_flag&_IONBF) {
		c1 = c;
		rn = 1;
D 15
		n = write(fileno(iop), &c1, rn);
E 15
I 15
		base = &c1;
E 15
		iop->_cnt = 0;
	} else {
		if ((base=iop->_base)==NULL) {
I 3
			if (fstat(fileno(iop), &stbuf) < 0 ||
			    stbuf.st_blksize <= NULL)
				size = BUFSIZ;
			else
				size = stbuf.st_blksize;
E 3
D 8
			if (iop==stdout) {
				if (isatty(fileno(stdout)))
					iop->_flag |= _IOLBF;
				iop->_base = _sobuf;
				iop->_ptr = _sobuf;
I 3
				iop->_bufsiz = size;
E 3
				goto tryagain;
			}
E 8
D 3
			if ((iop->_base=base=malloc(BUFSIZ)) == NULL) {
E 3
I 3
			if ((iop->_base=base=malloc(size)) == NULL) {
E 3
				iop->_flag |= _IONBF;
				goto tryagain;
			}
			iop->_flag |= _IOMYBUF;
I 3
			iop->_bufsiz = size;
I 8
			if (iop==stdout && isatty(fileno(stdout))) {
				iop->_flag |= _IOLBF;
				iop->_ptr = base;
				goto tryagain;
			}
E 8
E 3
			rn = n = 0;
D 15
		} else if ((rn = n = iop->_ptr - base) > 0) {
			iop->_ptr = base;
			n = write(fileno(iop), base, n);
		}
D 3
		iop->_cnt = BUFSIZ-1;
E 3
I 3
		iop->_cnt = iop->_bufsiz-1;
E 3
		*base++ = c;
E 15
I 15
		} else
			rn = iop->_ptr - base;
E 15
		iop->_ptr = base;
I 15
		iop->_cnt = iop->_bufsiz;
E 16
I 16
	/*
	 * If it is completely full, flush it out.  Then, in any case,
	 * stuff c into the buffer.  If this causes the buffer to fill
	 * completely, or if c is '\n' and the file is line buffered,
	 * flush it (perhaps a second time).  The second flush will always
	 * happen on unbuffered streams, where _bf._size==1; fflush()
	 * guarantees that putc() will always call wbuf() by setting _w
	 * to 0, so we need not do anything else.
	 */
	n = fp->_p - fp->_bf._base;
	if (n >= fp->_bf._size) {
		if (fflush(fp))
			return (EOF);
		n = 0;
E 16
E 15
	}
D 15
	if (rn != n) {
		iop->_flag |= _IOERR;
		return(EOF);
E 15
I 15
D 16
	while (rn > 0) {
		if ((n = write(fileno(iop), base, rn)) <= 0) {
			iop->_flag |= _IOERR;
			return(EOF);
		}
		rn -= n;
		base += n;
E 15
	}
I 15
	if ((iop->_flag&(_IOLBF|_IONBF)) == 0) {
		iop->_cnt--;
		*iop->_ptr++ = c;
	}
E 15
	return(c);
}

I 14
fpurge(iop)
register FILE *iop;
{
	iop->_ptr = iop->_base;
	iop->_cnt = iop->_flag&(_IOLBF|_IONBF|_IOREAD) ? 0 : iop->_bufsiz;
	return(0);
}

E 14
fflush(iop)
D 10
register struct _iobuf *iop;
E 10
I 10
register FILE *iop;
E 10
{
	register char *base;
D 15
	register n;
E 15
I 15
	register n, rn;
E 15

D 15
	if ((iop->_flag&(_IONBF|_IOWRT))==_IOWRT
	 && (base=iop->_base)!=NULL && (n=iop->_ptr-base)>0) {
E 15
I 15
	if ((iop->_flag&(_IONBF|_IOWRT))==_IOWRT &&
	    (base = iop->_base) != NULL && (rn = n = iop->_ptr - base) > 0) {
E 15
		iop->_ptr = base;
D 3
		iop->_cnt = (iop->_flag&(_IOLBF|_IONBF)) ? 0 : BUFSIZ;
E 3
I 3
		iop->_cnt = (iop->_flag&(_IOLBF|_IONBF)) ? 0 : iop->_bufsiz;
E 3
D 15
		if (write(fileno(iop), base, n)!=n) {
			iop->_flag |= _IOERR;
			return(EOF);
		}
E 15
I 15
		do {
			if ((n = write(fileno(iop), base, rn)) <= 0) {
				iop->_flag |= _IOERR;
				return(EOF);
			}
			rn -= n;
			base += n;
		} while (rn > 0);
E 15
	}
	return(0);
}

D 10
/*
 * Flush buffers on exit
 */

_cleanup()
{
	register struct _iobuf *iop;
	extern struct _iobuf *_lastbuf;

	for (iop = _iob; iop < _lastbuf; iop++)
		fclose(iop);
}

E 10
I 4
D 5
/*
 * fclose(*iop) - Close an open stdio stream without side effects.
 *
 * As per Dennis Ricthie's mail, fclose is defined to leave in a "virgin" state,
 * the structure pointed to by the parameter, *iop.  This means that
 * all flags are cleared, counters set to 0 and Pointers set to NULL.
 *
 * Which implies:
 *		foo = fopen...
 *		setbuf (foo, some_buffer);
 *		.....
 *		fclose(foo);
 *
 *	Will leave the buffer stucture cleared.  If the user wishes to
 * reuse the *iop (foo) when he opens another file he must AGAIN call setbuf(3)
 * if he again wishes to supply his own buffer.
 *
 *	The old method allowed the above case but had a nasty side effect
 * of leaving data around if the phase of the moon was right.  The correct
 * solution is to sanitize everything with the fclose.
 *	Clem Cole 12-15-82
 */

E 5
E 4
fclose(iop)
D 5
register struct _iobuf *iop;
E 5
I 5
D 10
	register struct _iobuf *iop;
E 10
I 10
	register FILE *iop;
E 10
E 5
{
D 4
	register r;
E 4
I 4
	register int r;
E 4

	r = EOF;
I 4
D 5
	/*
	 * Is this an open file structure as opposed to being String.
	 */
E 5
E 4
D 2
	if (iop->_flag&(_IOREAD|_IOWRT) && (iop->_flag&_IOSTRG)==0) {
E 2
I 2
	if (iop->_flag&(_IOREAD|_IOWRT|_IORW) && (iop->_flag&_IOSTRG)==0) {
I 4
D 5
		/*
		 * flush out any pending I/O
		 */
E 5
E 4
E 2
		r = fflush(iop);
I 4
D 5
		/*
		 * tell UNIX that it can free up the file descriptor
		 */
E 5
E 4
		if (close(fileno(iop)) < 0)
			r = EOF;
I 4
D 5
		/*
		 * if we had done a malloc(3) in flsbuf or filbuf we need
		 * to give the buffer back to the system
		 */
E 5
E 4
		if (iop->_flag&_IOMYBUF)
			free(iop->_base);
D 3
		if (iop->_flag&(_IOMYBUF|_IONBF|_IOLBF))
E 3
I 3
D 4
		if (iop->_flag&(_IOMYBUF|_IONBF|_IOLBF)) {
E 3
			iop->_base = NULL;
I 3
			iop->_bufsiz = 0;
		}
E 4
E 3
	}
D 2
	iop->_flag &= ~(_IOREAD|_IOWRT|_IOLBF|_IONBF|_IOMYBUF|_IOERR|_IOEOF|_IOSTRG);
E 2
I 2
D 4
	iop->_flag &= ~(_IOREAD|_IOWRT|_IOLBF|_IONBF|_IOMYBUF|_IOERR|_IOEOF|_IOSTRG|_IORW);
E 4
I 4
D 5
	/*
	 * finially sanitize the buffer structure
	 */
E 5
E 4
E 2
	iop->_cnt = 0;
I 4
	iop->_base = (char *)NULL;
	iop->_ptr = (char *)NULL;
	iop->_bufsiz = 0;
	iop->_flag = 0;
	iop->_file = 0;
D 5

E 5
E 4
	return(r);
}
I 13

_cleanup()
{
	extern int _fwalk();

	_fwalk(fclose);
E 16
I 16
	fp->_w--;
	*fp->_p++ = c;
	if (++n == fp->_bf._size || (fp->_flags & __SLBF && c == '\n'))
		if (fflush(fp))
			return (EOF);
	return (c);
E 16
}
E 13
E 1
