h48642
s 00002/00002/00071
d D 8.1 93/06/10 22:30:05 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00073/00000/00000
d D 7.1 92/12/13 03:50:25 akito 1 0
c date and time created 92/12/13 03:50:25 by akito
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
 * screen.c -- screen handler
 * by A.Fujita, Jun-17-1992
 */

#include <sys/param.h>
#include <luna68k/stand/status.h>

int
screen(argc, argv)
	int   argc;
	char *argv[];
{
	int i, j, flag;
	register char *p;
	short hcnt, vcnt;

	if (!strcmp(argv[1], "clear")) {
		bmdclear();
	} else if (!strcmp(argv[1], "adjust")) {
		hcnt = vcnt = 0;

		flag = 0;
		for (p = argv[2] ; *p != '\0'; p++) {
			if (*p == '-')
				flag++;
			else
				hcnt = (hcnt * 10) + (*p - 0x30);
		}
		if (flag)
			hcnt = -1 * hcnt;

		flag = 0;
		for (p = argv[3] ; *p != '\0'; p++) {
			if (*p == '-')
				flag++;
			else
				vcnt = (vcnt * 10) + (*p - 0x30);
		}
		if (flag)
			vcnt = -1 * vcnt;

		bmdadjust(hcnt, vcnt);
	} else if (!strcmp(argv[1], "number")) {
		for (j = 0; j < 50; j++)
			for (i = 0; i < 10; i++)
				bmdputc( 0x30 + i );

	} else if (!strcmp(argv[1], "alpha")) {
		for (j = 0; j < 26; j++) {
			for (i = 0; i < 90; i++) {
				bmdputc(0x41 + j);
			}
			bmdputc(0x0D);
			bmdputc(0x0A);
		}
	}

	return(ST_NORMAL);
}
E 1
