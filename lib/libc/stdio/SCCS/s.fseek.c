h12513
s 00001/00001/00218
d D 8.3 94/01/02 14:41:32 bostic 18 17
c fgetline(3) renamed to be fgetln(3)
e
s 00003/00005/00216
d D 8.2 93/11/04 00:02:56 torek 17 16
c fseek drops ungetc data; compute correct final offset (from Donn@BSDI)
e
s 00002/00002/00219
d D 8.1 93/06/04 13:06:36 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00219
d D 5.8 92/06/21 15:52:07 bostic 15 14
c the seek function takes a fpos_t (off_t), not a long
e
s 00002/00001/00219
d D 5.7 91/02/24 13:30:09 bostic 14 13
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00001/00218
d D 5.6 91/02/05 00:26:36 torek 13 12
c repair arguments (add const)
e
s 00001/00001/00218
d D 5.5 91/02/01 19:30:43 bostic 12 11
c fflush -> __sflush
e
s 00205/00050/00014
d D 5.4 91/01/20 21:22:48 bostic 11 10
c new stdio
e
s 00002/00002/00062
d D 5.3 86/03/09 20:51:40 donn 10 9
c added LIBC_SCCS condition for sccs ids
e
s 00010/00011/00054
d D 5.2 86/03/01 04:52:20 lepreau 9 8
c back out portion of last rev that make it return the offset;
c (for Sys V compat);  more error checking
e
s 00004/00001/00061
d D 5.1 85/06/05 13:36:05 mckusick 8 7
c Add copyright
e
s 00016/00010/00046
d D 4.4 85/02/13 17:12:05 serge 7 3
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00016/00010/00046
d R 4.4 85/02/13 17:11:01 serge 6 3
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00016/00010/00046
d R 4.4 85/02/13 17:09:40 serge 5 3
c autoconfigure FILE array using getdtablesize() \ 
e
s 00014/00008/00048
d R 4.4 85/02/13 15:48:46 serge 4 3
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00001/00000/00055
d D 4.3 83/09/25 11:48:07 karels 3 2
c fix seek on IORW streams
e
s 00012/00002/00043
d D 4.2 81/03/09 20:59:21 toy 2 1
c Feldman's stdio changes
e
s 00045/00000/00000
d D 4.1 80/12/21 16:50:25 wnj 1 0
c date and time created 80/12/21 16:50:25 by wnj
e
u
U
t
T
I 11
/*-
D 16
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 11
I 1
D 8
/* %W% (Berkeley) %G% */
E 8
I 8
D 10
#ifndef lint
E 10
I 10
#if defined(LIBC_SCCS) && !defined(lint)
E 10
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif not lint
E 10
I 10
D 11
#endif LIBC_SCCS and not lint
E 11
I 11
#endif /* LIBC_SCCS and not lint */
E 11
E 10

I 11
#include <sys/types.h>
D 14
#include <sys/file.h>
E 14
#include <sys/stat.h>
I 14
#include <fcntl.h>
E 14
#include <stdio.h>
I 14
#include <stdlib.h>
E 14
#include <errno.h>
#include "local.h"

#define	POS_ERR	(-(fpos_t)1)

E 11
E 8
/*
D 11
 * Seek for standard library.  Coordinates with buffering.
E 11
I 11
 * Seek the given file to the given offset.
 * `Whence' must be one of the three SEEK_* macros.
E 11
 */
I 17
int
E 17
I 11
fseek(fp, offset, whence)
	register FILE *fp;
	long offset;
	int whence;
{
D 17
#if __STDC__
D 13
	register fpos_t (*seekfn)(char *, fpos_t, int);
E 13
I 13
	register fpos_t (*seekfn)(void *, fpos_t, int);
E 13
#else
	register fpos_t (*seekfn)();
#endif
E 17
I 17
	register fpos_t (*seekfn) __P((void *, fpos_t, int));
E 17
	fpos_t target, curoff;
	size_t n;
	struct stat st;
	int havepos;
E 11

D 11
#include	<stdio.h>
E 11
I 11
	/* make sure stdio is set up */
	if (!__sdidinit)
		__sinit();
E 11

D 11
long lseek();
E 11
I 11
	/*
	 * Have to be able to seek.
	 */
	if ((seekfn = fp->_seek) == NULL) {
		errno = ESPIPE;			/* historic practice */
		return (EOF);
	}
E 11

I 7
D 9
long
E 9
E 7
D 11
fseek(iop, offset, ptrname)
D 7
FILE *iop;
long offset;
E 7
I 7
	register FILE *iop;
	long offset;
E 7
{
	register resync, c;
D 7
	long p;
E 7
I 7
D 9
	long p, curpos = -1;
E 9
I 9
	long p = -1;			/* can't happen? */
E 11
I 11
	/*
	 * Change any SEEK_CUR to SEEK_SET, and check `whence' argument.
	 * After this, whence is either SEEK_SET or SEEK_END.
	 */
	switch (whence) {
E 11
E 9
E 7

D 11
	iop->_flag &= ~_IOEOF;
	if (iop->_flag&_IOREAD) {
		if (ptrname<2 && iop->_base &&
			!(iop->_flag&_IONBF)) {
			c = iop->_cnt;
			p = offset;
D 7
			if (ptrname==0)
				p += c - lseek(fileno(iop),0L,1);
			else
E 7
I 7
			if (ptrname==0) {
D 9
				curpos = lseek(fileno(iop), 0L, 1);
E 9
I 9
				long curpos = lseek(fileno(iop), 0L, 1);
E 9
				if (curpos == -1)
					return (-1);
				p += c - curpos;
			} else
E 7
				offset -= c;
D 2
			if(c>0&&p<=c&&p>=iop->_base-iop->_ptr){
E 2
I 2
			if(!(iop->_flag&_IORW) && c>0&&p<=c
			    && p>=iop->_base-iop->_ptr){
E 2
				iop->_ptr += (int)p;
				iop->_cnt -= (int)p;
D 7
				return(0);
E 7
I 7
D 9
				if (curpos == -1)
					curpos = lseek(fileno(iop), 0L, 1);
				return (curpos == -1? -1: curpos - iop->_cnt);
E 9
I 9
				return(0);
E 9
E 7
			}
			resync = offset&01;
		} else 
			resync = 0;
I 2
		if (iop->_flag & _IORW) {
			iop->_ptr = iop->_base;
			iop->_flag &= ~_IOREAD;
I 3
			resync = 0;
E 11
I 11
	case SEEK_CUR:
		/*
		 * In order to seek relative to the current stream offset,
		 * we have to first find the current stream offset a la
		 * ftell (see ftell for details).
		 */
		if (fp->_flags & __SOFF)
			curoff = fp->_offset;
		else {
			curoff = (*seekfn)(fp->_cookie, (fpos_t)0, SEEK_CUR);
			if (curoff == -1L)
				return (EOF);
E 11
E 3
		}
E 2
D 11
		p = lseek(fileno(iop), offset-resync, ptrname);
		iop->_cnt = 0;
D 7
		if (resync)
			getc(iop);
E 7
I 7
D 9
		if (resync && getc(iop) != EOF && p != -1)
			p++;
E 9
I 9
		if (resync && p != -1)
			if (getc(iop) == EOF)
				p = -1;
E 11
I 11
		if (fp->_flags & __SRD) {
			curoff -= fp->_r;
			if (HASUB(fp))
				curoff -= fp->_ur;
		} else if (fp->_flags & __SWR && fp->_p != NULL)
			curoff += fp->_p - fp->_bf._base;

		offset += curoff;
		whence = SEEK_SET;
		havepos = 1;
		break;

	case SEEK_SET:
	case SEEK_END:
I 13
		curoff = 0;		/* XXX just to keep gcc quiet */
E 13
		havepos = 0;
		break;

	default:
		errno = EINVAL;
		return (EOF);
E 11
E 9
E 7
	}
D 2
	else if (iop->_flag&_IOWRT) {
E 2
I 2
D 11
	else if (iop->_flag & (_IOWRT|_IORW)) {
E 2
D 9
		fflush(iop);
E 9
I 9
		p = fflush(iop);
E 9
I 2
		if (iop->_flag & _IORW) {
			iop->_cnt = 0;
			iop->_flag &= ~_IOWRT;
			iop->_ptr = iop->_base;
E 11
I 11

	/*
	 * Can only optimise if:
	 *	reading (and not reading-and-writing);
	 *	not unbuffered; and
	 *	this is a `regular' Unix file (and hence seekfn==__sseek).
	 * We must check __NBF first, because it is possible to have __NBF
	 * and __SOPT both set.
	 */
	if (fp->_bf._base == NULL)
		__smakebuf(fp);
	if (fp->_flags & (__SWR | __SRW | __SNBF | __SNPT))
		goto dumb;
	if ((fp->_flags & __SOPT) == 0) {
		if (seekfn != __sseek ||
		    fp->_file < 0 || fstat(fp->_file, &st) ||
		    (st.st_mode & S_IFMT) != S_IFREG) {
			fp->_flags |= __SNPT;
			goto dumb;
E 11
		}
E 2
D 9
		p = lseek(fileno(iop), offset, ptrname);
E 9
I 9
D 11
		return(lseek(fileno(iop), offset, ptrname) == -1 || p == EOF ?
		    -1 : 0);
E 11
I 11
		fp->_blksize = st.st_blksize;
		fp->_flags |= __SOPT;
E 11
E 9
	}
D 7
	return(p==-1?-1:0);
E 7
I 7
D 9
	return(p);
E 9
I 9
D 11
	return(p==-1?-1:0);
E 11
I 11

	/*
	 * We are reading; we can try to optimise.
	 * Figure out where we are going and where we are now.
	 */
	if (whence == SEEK_SET)
		target = offset;
	else {
		if (fstat(fp->_file, &st))
			goto dumb;
		target = st.st_size + offset;
	}

	if (!havepos) {
		if (fp->_flags & __SOFF)
			curoff = fp->_offset;
		else {
D 15
			curoff = (*seekfn)(fp->_cookie, 0L, SEEK_CUR);
E 15
I 15
			curoff = (*seekfn)(fp->_cookie, (fpos_t)0, SEEK_CUR);
E 15
			if (curoff == POS_ERR)
				goto dumb;
		}
		curoff -= fp->_r;
		if (HASUB(fp))
			curoff -= fp->_ur;
	}

	/*
	 * Compute the number of bytes in the input buffer (pretending
	 * that any ungetc() input has been discarded).  Adjust current
	 * offset backwards by this count so that it represents the
	 * file offset for the first byte in the current input buffer.
	 */
	if (HASUB(fp)) {
I 17
		curoff += fp->_r;	/* kill off ungetc */
E 17
		n = fp->_up - fp->_bf._base;
		curoff -= n;
		n += fp->_ur;
	} else {
		n = fp->_p - fp->_bf._base;
		curoff -= n;
		n += fp->_r;
	}

	/*
	 * If the target offset is within the current buffer,
	 * simply adjust the pointers, clear EOF, undo ungetc(),
	 * and return.  (If the buffer was modified, we have to
D 18
	 * skip this; see fgetline.c.)
E 18
I 18
	 * skip this; see fgetln.c.)
E 18
	 */
	if ((fp->_flags & __SMOD) == 0 &&
	    target >= curoff && target < curoff + n) {
		register int o = target - curoff;

		fp->_p = fp->_bf._base + o;
		fp->_r = n - o;
		if (HASUB(fp))
			FREEUB(fp);
		fp->_flags &= ~__SEOF;
		return (0);
	}

	/*
	 * The place we want to get to is not within the current buffer,
	 * but we can still be kind to the kernel copyout mechanism.
	 * By aligning the file offset to a block boundary, we can let
	 * the kernel use the VM hardware to map pages instead of
	 * copying bytes laboriously.  Using a block boundary also
	 * ensures that we only read one block, rather than two.
	 */
	curoff = target & ~(fp->_blksize - 1);
	if ((*seekfn)(fp->_cookie, curoff, SEEK_SET) == POS_ERR)
		goto dumb;
	fp->_r = 0;
	if (HASUB(fp))
		FREEUB(fp);
	fp->_flags &= ~__SEOF;
	n = target - curoff;
	if (n) {
		if (__srefill(fp) || fp->_r < n)
			goto dumb;
		fp->_p += n;
		fp->_r -= n;
	}
	return (0);

	/*
	 * We get here if we cannot optimise the seek ... just
	 * do it.  Allow the seek function to change fp->_bf._base.
	 */
dumb:
D 12
	if (fflush(fp) ||
E 12
I 12
	if (__sflush(fp) ||
E 12
D 15
	    (*seekfn)(fp->_cookie, offset, whence) == POS_ERR) {
E 15
I 15
	    (*seekfn)(fp->_cookie, (fpos_t)offset, whence) == POS_ERR) {
E 15
		return (EOF);
	}
	/* success: clear EOF indicator and discard ungetc() data */
	if (HASUB(fp))
		FREEUB(fp);
	fp->_p = fp->_bf._base;
	fp->_r = 0;
	/* fp->_w = 0; */	/* unnecessary (I think...) */
	fp->_flags &= ~__SEOF;
	return (0);
E 11
E 9
E 7
}
E 1
