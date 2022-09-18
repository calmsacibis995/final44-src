h63571
s 00006/00005/00133
d D 8.2 94/01/04 14:43:25 bostic 18 17
c use FOPEN_MAX instead of NSTATIC, _POSIX_STREAM_MAX makes it public
e
s 00002/00002/00136
d D 8.1 93/06/04 13:05:14 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00135
d D 5.11 93/06/04 11:38:46 torek 16 15
c must align FILE structures correctly
e
s 00003/00002/00134
d D 5.10 91/02/24 13:30:05 bostic 15 14
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00134
d D 5.9 91/02/01 19:29:49 bostic 14 13
c initialization out of order wrt stdio.h
e
s 00102/00088/00034
d D 5.8 91/01/20 21:13:39 bostic 13 12
c new stdio; renamed from findiop.c
e
s 00000/00007/00122
d D 5.7 88/09/22 16:52:57 bostic 12 11
c move _cleanup from findiop.c to flsbuf.c so lorder doesn't get confused
e
s 00002/00002/00127
d D 5.6 86/03/09 20:49:43 donn 11 10
c added LIBC_SCCS condition for sccs ids
e
s 00006/00012/00123
d D 5.5 86/02/10 17:21:56 karels 10 8
c all right, all right, I'll use calloc (using malloc/bzero screws up
c libc order; ld bug?)
e
s 00005/00010/00125
d R 5.5 86/02/10 17:18:57 karels 9 8
c all right, all right, I'll use calloc (using malloc/bzero screws up
c libc ordering; ld bug?)
e
s 00038/00012/00097
d D 5.4 86/02/09 16:51:56 karels 8 7
c try again; can't be called from crt0 (breaks sh)
e
s 00038/00022/00071
d D 5.3 86/02/06 17:34:22 karels 7 5
c outs for programs using alternae memory allocators:
c call _stdio_init before main to give 20 files worth without callocs,
c and provide f_prealloc to fill in everything
e
s 00038/00022/00071
d R 5.3 86/02/04 18:19:00 karels 6 5
c outs for programs using alternae memory allocators:
c call _stdio_init before main to give 20 files worth without callocs,
c and provide f_prealloc to fill in everything
e
s 00006/00001/00087
d D 5.2 85/09/18 23:44:32 lepreau 5 4
c set EMFILE if out of fd's
e
s 00010/00001/00078
d D 5.1 85/05/30 14:27:38 dist 4 3
c Add copyright
e
s 00049/00062/00030
d D 1.3 85/03/04 14:54:38 serge 3 2
c allocate only as many FILE's as needed
e
s 00045/00022/00047
d D 1.2 85/02/13 15:49:29 serge 2 1
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00069/00000/00000
d D 1.1 85/01/29 00:38:11 serge 1 0
c date and time created 85/01/29 00:38:11 by serge
e
u
U
t
T
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
D 13
/*
D 7
 * Copyright (c) 1983 Regents of the University of California.
E 7
I 7
 * Copyright (c) 1983, 1985 Regents of the University of California.
E 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
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
E 13
 */

D 11
#ifndef lint
E 11
I 11
#if defined(LIBC_SCCS) && !defined(lint)
E 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 11
#endif not lint
E 11
I 11
D 13
#endif LIBC_SCCS and not lint
E 13
I 13
#endif /* LIBC_SCCS and not lint */
E 13
E 11

I 16
#include <sys/param.h>
E 16
E 4
D 2
#include "stdio.h"
E 2
I 2
D 15
#include <stdio.h>
I 13
#include <stdlib.h>
E 15
#include <unistd.h>
I 15
#include <stdio.h>
E 15
E 13
I 5
#include <errno.h>
I 15
#include <stdlib.h>
#include <string.h>
E 15
I 13
#include "local.h"
#include "glue.h"
E 13
E 5
E 2

I 5
D 13
extern int errno;
E 13
I 13
int	__sdidinit;
E 13

E 5
D 2
#define NSTATIC	5	/* stdin, stdout, stderr, plus slack */
E 2
I 2
D 3
#define NSTATIC	10	/* stdin, stdout, stderr, plus slack */
E 3
I 3
D 13
#define active(iop)	((iop)->_flag & (_IOREAD|_IOWRT|_IORW))
E 3
E 2

E 13
D 3
extern char *calloc();
E 3
I 3
D 7
#define NSTATIC	3	/* stdin + stdout + stderr */
E 7
I 7
D 18
#define NSTATIC	20	/* stdin + stdout + stderr + the usual */
I 13
#define	NDYNAMIC 10	/* add ten more whenever necessary */
E 18
I 18
#define	NDYNAMIC 10		/* add ten more whenever necessary */
E 18
E 13
E 7
E 3

D 2
static FILE **iov, **iovend;
E 2
D 3
static FILE *dummy[NSTATIC];
I 2
static FILE **iov = NULL;
static FILE **iovend;
E 2

E 3
D 13
FILE _iob[NSTATIC] = {
D 2
	{ 0, NULL, NULL, NULL, _IOREAD, 0 },		/* stdin  */
	{ 0, NULL, NULL, NULL, _IOWRT, 1 },		/* stdout */
	{ 0, NULL, NULL, NULL, _IOWRT+_IONBF, 2 },	/* stderr */
E 2
I 2
D 3
	{ 0, NULL, NULL, NULL, _IOREAD,		0 },	/* stdin  */
	{ 0, NULL, NULL, NULL, _IOWRT,		1 },	/* stdout */
	{ 0, NULL, NULL, NULL, _IOWRT|_IONBF,	2 },	/* stderr */
E 3
I 3
	{ 0, NULL, NULL, 0, _IOREAD,		0 },	/* stdin  */
	{ 0, NULL, NULL, 0, _IOWRT,		1 },	/* stdout */
	{ 0, NULL, NULL, 0, _IOWRT|_IONBF,	2 },	/* stderr */
E 13
I 13
#define	std(flags, file) \
D 14
	{0,0,0,flags,file,{0},0,__sF+file,__sread,__swrite,__sseek,__sclose}
/*	 p r w flags file _bf z  cookie    read    write    seek    close */
E 14
I 14
	{0,0,0,flags,file,{0},0,__sF+file,__sclose,__sread,__sseek,__swrite}
/*	 p r w flags file _bf z  cookie      close    read    seek    write */
E 14

D 18
static FILE usual[NSTATIC - 3];	/* the usual */
static struct glue uglue = { 0, NSTATIC - 3, usual };
E 18
I 18
				/* the usual - (stdin + stdout + stderr) */
static FILE usual[FOPEN_MAX - 3];
static struct glue uglue = { 0, FOPEN_MAX - 3, usual };
E 18

FILE __sF[3] = {
	std(__SRD, STDIN_FILENO),		/* stdin */
	std(__SWR, STDOUT_FILENO),		/* stdout */
	std(__SWR|__SNBF, STDERR_FILENO)	/* stderr */
E 13
E 3
E 2
};
I 13
struct glue __sglue = { &uglue, 3, __sF };
E 13

I 2
D 3
static char smallbuf[NSTATIC];
static char *unbufp = NULL;
E 3
I 3
D 7
static	FILE	*_lastbuf = _iob + NSTATIC;
E 3

E 7
I 3
D 8
extern	char	*calloc();
E 8
I 8
D 10
extern	char	*malloc();
E 10
I 10
D 13
extern	char	*calloc();
E 13
I 13
static struct glue *
moreglue(n)
	register int n;
{
	register struct glue *g;
	register FILE *p;
	static FILE empty;
E 13
E 10
E 8

I 8
D 13
static	char sbuf[NSTATIC];
char	*_smallbuf = sbuf;
E 8
static	FILE	**iobglue;
static	FILE	**endglue;
E 13
I 13
D 16
	g = (struct glue *)malloc(sizeof(*g) + n * sizeof(FILE));
E 16
I 16
	g = (struct glue *)malloc(sizeof(*g) + ALIGNBYTES + n * sizeof(FILE));
E 16
	if (g == NULL)
		return (NULL);
D 16
	p = (FILE *)(g + 1);
E 16
I 16
	p = (FILE *)ALIGN(g + 1);
E 16
	g->next = NULL;
	g->niobs = n;
	g->iobs = p;
	while (--n >= 0)
		*p++ = empty;
	return (g);
}
E 13
D 8
static	int	nfiles;
E 8

I 8
/*
 * Find a free FILE for fopen et al.
D 13
 * We have a fixed static array of entries, and in addition
 * may allocate additional entries dynamically, up to the kernel
 * limit on the number of open files.
 * At first just check for a free slot in the fixed static array.
 * If none are available, then we allocate a structure to glue together
 * the old and new FILE entries, which are then no longer contiguous.
E 13
 */
E 8
E 3
E 2
FILE *
D 13
_findiop()
E 13
I 13
__sfp()
E 13
{
D 3
	register FILE **iovp;
E 3
I 3
D 8
	register FILE **iov;
E 8
I 8
D 13
	register FILE **iov, *iop;
E 13
E 8
E 3
	register FILE *fp;
I 13
	register int n;
	register struct glue *g;
E 13
D 3
	register int nfiles;
E 3
D 2
	register int i;
	char *p;
E 2

D 3
	if (iov == NULL) {
I 2
		unbufp	= NULL;
		iov	= NULL;
		fp	= NULL;

E 3
I 3
D 7
	if (nfiles <= 0)
E 3
E 2
		nfiles = getdtablesize();
D 2
		if (nfiles > NSTATIC)
			p = calloc(1, nfiles * sizeof *iov +
				    (nfiles - NSTATIC) * sizeof **iov);
		else
			p = NULL;
E 2
I 2
D 3
		if (nfiles > NSTATIC) {
			fp = (FILE *)calloc(nfiles - NSTATIC, sizeof *fp);
			if (fp != NULL) {
				iov = (FILE **)calloc(nfiles, sizeof *iov);
				if (iov != NULL)
					unbufp = calloc(nfiles, sizeof *unbufp);
			}
		}
E 3
E 2

D 2
		if (p == NULL) {
			iov = dummy;
			iovend = iov + NSTATIC;
		} else {
			iov = (FILE **)p;
E 2
I 2
D 3
		if (unbufp != NULL) {
E 2
			iovend = iov + nfiles;
D 2

			fp = (FILE *)iovend;
E 2
			for (iovp = iov + NSTATIC; iovp < iovend; /* void */)
				*iovp++ = fp++;
I 2
		} else {
			if (fp != NULL) {
				free((char *)fp);
				if (iov != NULL)
					free((char *)iov);
			}
E 3
I 3
	if (iobglue == NULL) {
		iobglue = (FILE **)calloc(nfiles, sizeof *iobglue);
		if (iobglue == NULL)
			return (NULL);
E 3

D 3
			iovend	= dummy + NSTATIC;
			iov	= dummy;
E 2
		}
E 3
I 3
		endglue = iobglue + nfiles;
E 3

D 2
		for (i = 0; i < NSTATIC; i++)
			iov[i] = &_iob[i];
E 2
I 2
D 3
		iovp = iov;
		for (fp = _iob; fp < _iob + NSTATIC; /* void */)
			*iovp++ = fp++;
E 3
I 3
		iov = iobglue;
		for (fp = _iob; fp < _lastbuf; /* void */)
			*iov++ = fp++;
E 7
I 7
D 8
	if (iobglue == 0 && _stdio_init() == 0) {
		errno = ENOMEM;
		return (NULL);
E 8
I 8
D 13
	if (iobglue == 0) {
		for (iop = _iob; iop < _iob + NSTATIC; iop++)
			if (!active(iop))
				return (iop);

		if (_f_morefiles() == 0) {
			errno = ENOMEM;
			return (NULL);
		}
E 13
I 13
	if (!__sdidinit)
		__sinit();
	for (g = &__sglue;; g = g->next) {
		for (fp = g->iobs, n = g->niobs; --n >= 0; fp++)
			if (fp->_flags == 0)
				goto found;
		if (g->next == NULL && (g->next = moreglue(NDYNAMIC)) == NULL)
			break;
E 13
E 8
E 7
E 3
E 2
	}
D 13

D 3
	for (iovp = iov; (*iovp)->_flag & (_IOREAD|_IOWRT|_IORW); /* void */)
		if (++iovp >= iovend)
E 3
I 3
	iov = iobglue;
	while (*iov != NULL && active(*iov))
D 5
		if (++iov >= endglue)
E 5
I 5
		if (++iov >= endglue) {
			errno = EMFILE;
E 5
E 3
			return (NULL);
I 5
		}
E 5

D 3
	return (*iovp);
E 3
I 3
	if (*iov == NULL)
D 8
		*iov = (FILE *)calloc(1, sizeof **iov);
E 8
I 8
D 10
		*iov = (FILE *)malloc(sizeof **iov);
	if (*iov)
		bzero((char *)*iov, sizeof(**iov));
E 10
I 10
		*iov = (FILE *)calloc(1, sizeof **iov);
E 10
E 8

	return (*iov);
E 13
I 13
	return (NULL);
found:
	fp->_flags = 1;		/* reserve this slot; caller sets real flags */
	fp->_p = NULL;		/* no current pointer */
	fp->_w = 0;		/* nothing to read or write */
	fp->_r = 0;
	fp->_bf._base = NULL;	/* no buffer */
	fp->_bf._size = 0;
	fp->_lbfsize = 0;	/* not line buffered */
	fp->_file = -1;		/* no file */
/*	fp->_cookie = <any>; */	/* caller sets cookie, _read/_write etc */
	fp->_ub._base = NULL;	/* no ungetc buffer */
	fp->_ub._size = 0;
	fp->_lb._base = NULL;	/* no line buffer */
	fp->_lb._size = 0;
	return (fp);
E 13
E 3
}

D 3
_cleanup()
E 3
I 3
D 7
_fwalk(function)
	register int (*function)();
E 7
I 7
D 8
_stdio_init()
E 8
I 8
D 13
_f_morefiles()
E 13
I 13
/*
 * XXX.  Force immediate allocation of internal memory.  Not used by stdio,
 * but documented historically for certain applications.  Bad applications.
 */
f_prealloc()
E 13
E 8
E 7
E 3
{
D 3
	register FILE *_lastbuf = _iob + NSTATIC;
	register FILE **iovp;
	register FILE *iop;
E 3
I 3
D 13
	register FILE **iov;
	register FILE *fp;
I 8
	register char *cp;
	int nfiles;
E 13
I 13
D 18
	int n = getdtablesize() - NSTATIC + 20;		/* 20 for slop */
E 18
	register struct glue *g;
I 18
	int n;
E 18
E 13
E 8
E 3

I 18
	n = getdtablesize() - FOPEN_MAX + 20;		/* 20 for slop. */
E 18
D 3
	if (iov == NULL)
		for (iop = _iob; iop < _lastbuf; iop++)
			fclose(iop);
	else
		for (iovp = iov; iovp < iovend; iovp++)
			fclose(*iovp);
E 3
I 3
D 7
	if (function == NULL)
E 7
I 7
D 13
	nfiles = getdtablesize();

D 8
	iobglue = (FILE **)calloc(nfiles, sizeof *iobglue);
E 8
I 8
D 10
	iobglue = (FILE **)malloc(nfiles * sizeof *iobglue);
E 10
I 10
	iobglue = (FILE **)calloc(nfiles, sizeof *iobglue);
E 10
E 8
	if (iobglue == NULL)
		return (0);

I 8
D 10
	bzero((char *)iobglue, nfiles * sizeof(*iobglue));
E 10
E 8
	endglue = iobglue + nfiles;

	for (fp = _iob, iov = iobglue; fp < &_iob[NSTATIC]; /* void */)
		*iov++ = fp++;
I 8

D 10
	_smallbuf = malloc(nfiles * sizeof(*_smallbuf));
E 10
I 10
	_smallbuf = calloc(nfiles, sizeof(*_smallbuf));
E 10
E 8
	return (1);
E 13
I 13
	for (g = &__sglue; (n -= g->niobs) > 0 && g->next; g = g->next)
		/* void */;
	if (n > 0)
		g->next = moreglue(n);
E 13
}

D 13
f_prealloc()
E 13
I 13
/*
 * exit() calls _cleanup() through *__cleanup, set whenever we
 * open or buffer a file.  This chicanery is done so that programs
 * that do not use stdio need not link it all in.
 *
 * The name `_cleanup' is, alas, fairly well known outside stdio.
 */
void
_cleanup()
E 13
{
D 13
	register FILE **iov;
	register FILE *fp;

D 8
	if (iobglue == NULL && _stdio_init() == 0)
E 8
I 8
	if (iobglue == NULL && _f_morefiles() == 0)
E 8
E 7
		return;

I 7
	for (iov = iobglue; iov < endglue; iov++)
D 8
		if (*iov == NULL)
			*iov = (FILE *)calloc(1, sizeof **iov);
E 8
I 8
D 10
		if (*iov == NULL) {
			*iov = (FILE *)malloc(1, sizeof **iov);
			if (*iov)
				bzero((char *)*iov, sizeof(**iov));
		}
E 10
I 10
		if (*iov == NULL)
			*iov = (FILE *)calloc(1, sizeof **iov);
E 13
I 13
	/* (void) _fwalk(fclose); */
	(void) _fwalk(__sflush);		/* `cheating' */
E 13
E 10
E 8
}

D 13
_fwalk(function)
	register int (*function)();
E 13
I 13
/*
 * __sinit() is called whenever stdio's internal variables must be set up.
 */
void
__sinit()
E 13
{
D 13
	register FILE **iov;
	register FILE *fp;

E 7
	if (iobglue == NULL) {
D 7
		for (fp = _iob; fp < _lastbuf; fp++)
E 7
I 7
		for (fp = _iob; fp < &_iob[NSTATIC]; fp++)
E 7
			if (active(fp))
				(*function)(fp);
	} else {
		for (iov = iobglue; iov < endglue; iov++)
D 7
			if (*iov != NULL && active(*iov))
E 7
I 7
			if (*iov && active(*iov))
E 7
				(*function)(*iov);
	}
E 13
I 13
	/* make sure we clean up on exit */
	__cleanup = _cleanup;		/* conservative */
	__sdidinit = 1;
E 13
E 3
I 2
}
D 12

D 3
char *
_smallbuf(iop)
	register FILE *iop;
E 3
I 3
_cleanup()
E 3
{
D 3
	if (unbufp == NULL)
		return (&smallbuf[iop - _iob]);
	else
		return (&unbufp[fileno(iop)]);
E 3
I 3
	extern int fclose();

	_fwalk(fclose);
E 3
E 2
}
E 12
E 1
