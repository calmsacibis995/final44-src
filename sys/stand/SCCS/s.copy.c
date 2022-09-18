h11643
s 00005/00005/00060
d D 8.1 93/06/11 16:00:47 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00065/00000/00000
d D 7.1 93/06/11 14:35:12 mckusick 1 0
c date and time created 93/06/11 14:35:12 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#define	BSIZE	10240

/*
 * Copy from from to to.  Intended for use in system installation.
 */
main()
{
	extern int errno;
	register int from, to, record, rcc, wcc, bsize = BSIZE;
	char buf[BSIZE];

	from = getfile("From", 0);
	to = getfile("To", 1);
	for (record = 0;; ++record) {
		if (!(rcc = read(from, buf, bsize)))
			break;
		if (rcc < 0) {
			printf("Record %d: read error, errno=%d\n",
			    record, errno);
			break;
		}
		if (rcc != bsize) {
			if (record == 0) {
				bsize = rcc;
				printf("Block size set from input; %d bytes\n",
				    bsize);
			} else
				printf("Record %d: read short; expected %d, got %d\n",
				    record, bsize, rcc);
		}
#ifdef vax
		/* For bug in ht driver. */
		if (rcc > bsize)
			rcc = bsize;
#endif
		if ((wcc = write(to, buf, rcc)) < 0) {
			printf("Record %d: write error: errno=%d\n",
			    record, errno);
			break;
		}
		if (wcc < rcc) {
			printf("Record %d: write short; expected %d, got %d\n",
			    record, rcc, wcc);
			break;
		}
	}
	printf("copy completed: %d records copied\n", record);
}
E 1
