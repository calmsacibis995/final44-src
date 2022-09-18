h52763
s 00002/00002/00057
d D 8.1 93/06/10 22:30:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00059/00000/00000
d D 7.1 92/12/13 03:50:33 akito 1 0
c date and time created 92/12/13 03:50:33 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * tape.c -- operation commands for TAPE unit.
 * by A.Fujita, APR-14-1992
 */

#include <sys/param.h>
#include <luna68k/stand/status.h>

dev_t  rst0 = 0x0000;
dev_t nrst0 = 0x0004;

u_char buff[512];

int
tape(argc, argv)
	int   argc;
	char *argv[];
{
	int size, count;
	u_long *p = (u_long *) buff;

	if (!strcmp(argv[1], "read")) {
		count = 0;
		while ((size = stread(rst0, buff, 512)) == 512)
			count++;
		printf("tape: size  = %d\n", size);
		printf("tape: count = %d\n", count);
	} else if (!strcmp(argv[1], "write")) {
		for (count = 0; count < 500; count++) {
			if ((size = stwrite(rst0, buff, 512)) != 512)
				break;
		}
		printf("tape: size  = %d\n", size);
		printf("tape: count = %d\n", count);
	} else if (!strcmp(argv[1], "rewind")) {
		st_rewind(rst0);
	} else if (!strcmp(argv[1], "weof")) {
		st_write_EOF(rst0);
	} else if (!strcmp(argv[1], "skip")) {
		st_skip(rst0);
	} else {
		return(ST_ERROR);
	}

	return(ST_NORMAL);
}
E 1
