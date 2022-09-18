h14572
s 00002/00002/00112
d D 8.1 93/06/09 21:43:31 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00005/00104
d D 7.5 91/04/17 17:38:18 bostic 5 4
c new copyright; att/bsd/shared
e
s 00004/00000/00105
d D 7.4 87/03/09 12:47:26 conrad 4 3
c make ex/vi work on vms
e
s 00001/00001/00104
d D 7.3 86/01/31 16:51:02 bloom 3 2
c fix problem reading last entry in tags file if EOF read first
e
s 00001/00001/00104
d D 7.2 85/06/07 18:20:49 bloom 2 1
c fix sccsid and copyright for xstr
e
s 00105/00000/00000
d D 7.1 85/05/31 12:51:02 bloom 1 0
c date and time created 85/05/31 12:51:02 by bloom
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1985 Regents of the University of California */
E 5
I 5
/*-
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */
E 5

I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
/*
 * These routines are for faster tag lookup.  They support the binary
 * search used in tagfind() instead of the linear search.  The speedup
 * is quite noticable looking for a tag at the end of a long tags
 * file.  Define FASTTAG in the Makefile to use these routines.
 */
D 5

E 5
#ifdef FASTTAG
D 5
#ifndef lint
D 2
static char *sccsid = "%W%	%G%";
E 2
I 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
#endif
E 5

I 4
#ifndef vms
E 4
#include <sys/file.h>
I 4
#else
#include <file.h>
#endif
E 4
#include "ex.h"

static long offset = -1;
static long block = -1;
static int bcnt = 0;
static int b_size = MAXBSIZE;
static char *ibuf;

topen(file, buf)
char *file, *buf;
{
	int fd;
	struct stat statb;

	offset = -1;
	block = -1;
	if ((fd = open(file, O_RDONLY, 0)) < 0)
		return(-1);
	if (fstat(fd, &statb) < 0) {
		(void)close(fd);
		return(-1);
	}
	ibuf = buf;
	b_size = statb.st_blksize;
	return(fd);
}

tseek(fd, off)
int fd;
long off;
{
	int nblock;

	nblock = off / b_size * b_size;
	offset = off % b_size;
	if (nblock == block)
		return(0);
	block = nblock;
	if (lseek(fd, nblock, L_SET) < 0)
		return(-1);
	if ((bcnt = read(fd, ibuf, b_size)) < 0)
		return(-1);
	return(0);
}

tgets(buf, cnt, fd)
register char *buf;
int cnt;
int fd;
{
	register char *cp;
	register cc;

	cc = offset;
	if (cc == -1) {
		if ((bcnt = read(fd, ibuf, b_size)) <= 0)
			return (NULL);
		cc = 0;
		block = 0;
	}
	if (bcnt == 0)		/* EOF */
		return(NULL);
	cp = ibuf + cc;
	while (--cnt > 0) {
		if (++cc > bcnt) {
I 3
			block += b_size;
E 3
			if ((bcnt = read(fd, ibuf, b_size)) <= 0) {
				offset = cc;
				return (NULL);
			}
D 3
			block += b_size;
E 3
			cp = ibuf;
			cc = 1;
		}
		if ((*buf++ = *cp++) == '\n')
			break;
	}
	*--buf = NULL;
	offset = cc;
	return(1);
}

tclose(fd)
int fd;
{
	(void)close(fd);
	offset = -1;
	block = -1;
	bcnt = 0;
}
#endif
E 1
