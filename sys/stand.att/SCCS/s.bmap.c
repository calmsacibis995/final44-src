h46495
s 00002/00002/00081
d D 8.1 93/06/11 16:01:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00082
d D 7.4 93/05/24 22:44:04 mckusick 4 3
c new include location
e
s 00001/00001/00082
d D 7.3 92/10/11 10:01:00 bostic 3 2
c make kernel includes standard
e
s 00004/00004/00079
d D 7.2 91/05/25 15:28:57 bostic 2 1
c delete obsolete printf formats (%D -> %ld)
e
s 00083/00000/00000
d D 7.1 91/05/05 13:19:54 bostic 1 0
c date and time created 91/05/05 13:19:54 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1982, 1988 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
D 3
#include "saio.h"
E 3
I 3
D 4
#include <stand/saio.h>
E 4
I 4
#include <stand.att/saio.h>
E 4
E 3

#define	NBUFS	4
static char	b[NBUFS][MAXBSIZE];
static daddr_t	blknos[NBUFS];

daddr_t
bmap(io, bn)
	register struct iob *io;
	daddr_t bn;
{
	register struct dinode *ip;
	int i, j, sh;
	daddr_t nb, *bap;

	ip = &io->i_ino;
	if (bn < 0) {
		printf("bn negative\n");
		return ((daddr_t)0);
	}

	/* The first NDADDR blocks are direct blocks. */
	if(bn < NDADDR) {
		nb = ip->di_db[bn];
		return (nb);
	}

	/* Determine the number of levels of indirection. */
	sh = 1;
	bn -= NDADDR;
	for (j = NIADDR; j > 0; j--) {
		sh *= NINDIR(&io->i_fs);
		if (bn < sh)
			break;
		bn -= sh;
	}
	if (j == 0) {
D 2
		printf("bn ovf %D\n", bn);
E 2
I 2
		printf("bn ovf %ld\n", bn);
E 2
		return ((daddr_t)0);
	}

	/* Get the first indirect block address. */
	nb = ip->di_ib[NIADDR - j];
	if (nb == 0) {
D 2
		printf("bn void %D\n",bn);
E 2
I 2
		printf("bn void %ld\n",bn);
E 2
		return ((daddr_t)0);
	}

	/* Get the indirect blocks. */
	for (; j <= NIADDR; j++) {
		if (blknos[j] != nb) {
			io->i_bn = fsbtodb(&io->i_fs, nb) + io->i_boff;
			io->i_ma = b[j];
			io->i_cc = io->i_fs.fs_bsize;
			if (devread(io) != io->i_fs.fs_bsize) {
				if (io->i_error)
					errno = io->i_error;
D 2
				printf("bn %D: read error\n", io->i_bn);
E 2
I 2
				printf("bn %ld: read error\n", io->i_bn);
E 2
				return ((daddr_t)0);
			}
			blknos[j] = nb;
		}
		bap = (daddr_t *)b[j];
		sh /= NINDIR(&io->i_fs);
		i = (bn / sh) % NINDIR(&io->i_fs);
		nb = bap[i];
		if(nb == 0) {
D 2
			printf("bn void %D\n",bn);
E 2
I 2
			printf("bn void %ld\n",bn);
E 2
			return ((daddr_t)0);
		}
	}
	return (nb);
}
E 1
