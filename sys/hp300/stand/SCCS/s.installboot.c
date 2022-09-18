h37508
s 00006/00008/00082
d D 7.4 92/10/11 10:01:40 bostic 4 3
c make kernel includes standard
e
s 00003/00003/00087
d D 7.3 92/06/18 21:33:33 hibler 3 2
c merge with latest Utah version
e
s 00002/00002/00088
d D 7.2 90/12/16 16:39:22 bostic 2 1
c kernel reorg
e
s 00090/00000/00000
d D 7.1 90/05/08 22:46:04 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1980, 1986, 1990 The Regents of the University of California.
E 4
I 4
/*-
 * Copyright (c) 1986, 1990 The Regents of the University of California.
E 4
 * All rights reserved.
 *
 * %sccs.include.redist.c%
D 4
 *
 *	%W% (Berkeley) %G%
E 4
 */

#ifndef lint
char copyright[] =
D 3
"%Z% Copyright (c) 1980, 1986, 1990 The Regents of the University of California.\n\
E 3
I 3
D 4
"@(#) Copyright (c) 1980, 1986, 1990 The Regents of the University of California.\n\
E 4
I 4
"%Z% Copyright (c) 1986, 1990 The Regents of the University of California.\n\
E 4
E 3
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 4
static char sccsid[] = "@(#)installboot.c	7.2 (Berkeley) 12/16/90";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
E 3
#endif /* not lint */

D 2
#include "../sys/param.h"
#include "../ufs/fs.h"
E 2
I 2
D 4
#include "sys/param.h"
D 3
#include "ufs/fs.h"
E 3
I 3
#include "ufs/ffs/fs.h"
E 4
I 4
#include <sys/param.h>
#include <ufs/ffs/fs.h>
E 4
E 3
E 2

char block[1024];
int maxbootsize = 16 * 7 * 512;		/* XXX */

/*
 * HPs are a kludge.
 * The boot program won't fit in the boot area of a file system so we
 * have to place it outside the file systems.  By convention, this means
 * that if the 'a' partition is being used for '/', it is offset one
 * cylinder into the disk and the boot program goes into that one cylinder.
 * Also by convention, the 'c' partition is defined to be the entire disk
 * including this boot cylinder.  If these conventions are not adhered to,
 * the potential for disaster is enormous.
 */
main(argc, argv)
	int argc;
	char *argv[];
{
	int ifd, ofd, len;
	char *dev, *standalonecode;
	int bsize = 1024;

	if (argc != 3)
		usage();
	dev = argv[2];
	len = strlen(dev);
	if (dev[len-1] != 'c')
		usage();
	standalonecode = argv[1];
	ifd = open(standalonecode, 0);
	if (ifd < 0) {
		perror(standalonecode);
		exit(1);
	}
	ofd = open(dev, 1);
	if (ofd < 0) {
		perror(dev);
		exit(1);
	}
	while ((len = read(ifd, block, bsize)) > 0) {
		if ((maxbootsize -= bsize) < 0) {
			printf("%s: too big\n", standalonecode);
			exit(2);
		}
		if (len < bsize)
			bzero(&block[len], bsize-len);
		if (write(ofd, block, bsize) != bsize) {
			perror(dev);
			exit(2);
		}
	}
	if (len < 0) {
		perror(standalonecode);
		exit(2);
	}
	exit(0);
}

usage()
{
	printf("Usage: installboot bootprog device\n");
	printf("where:\n");
	printf("\t\"bootprog\" is a LIF format file < %d bytes long\n",
	       maxbootsize);
	printf("\t\"device\" must be the 'c' partition of a bootable disk\n");
	printf("WARNING!!  If the 'c' partition contains a file system, %s\n",
	       "DON'T RUN THIS!!");
	exit(1);
}
E 1
