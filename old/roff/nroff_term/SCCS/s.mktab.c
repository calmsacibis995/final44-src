h16548
s 00004/00014/00098
d D 5.2 91/04/18 17:44:27 bostic 2 1
c new copyright; att/bsd/shared
e
s 00112/00000/00000
d D 5.1 89/02/28 04:08:04 donn 1 0
c date and time created 89/02/28 04:08:04 by donn
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1989 Regents of the University of California.
E 2
I 2
/*-
 * Copyright (c) 1989 The Regents of the University of California.
E 2
 * All rights reserved.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
char copyright[] =
D 2
"@(#) Copyright (c) 1989 Regents of the University of California.\n\
E 2
I 2
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 2
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * mktab.c
 *
 * Function:	Build nroff terminal tables in a compiler-independent way.
 * Usage:	cc -Itroff mktab.c tabnnn.c -o mktab; mktab > tabnnn
 * Date:	Sat Feb 25 00:10:06 MST 1989
 * Author:	Donn Seeley
 * Remarks:
 *	Traditional nroff terminal table construction works by compiling
 *	a C file into a binary that is read directly into nroff as it runs.
 *	If your C compiler or your relocation format differ from what nroff
 *	expects, you lose.  This program, when linked with a terminal table
 *	object file, fakes up an 'object' file that looks enough like the
 *	traditional one to fool nroff.
 */

#include <stdio.h>
#include "tw.h"

main()
{
	static struct fake_exec {
		int bogus[8];	/* bogus[2] == a_data */
	} fe;
	register int *bip;
	register char **tip;
	register int offset = sizeof t;
	int buf[sizeof t / sizeof (int)];
	char *malloc();
	int twbase = (int *) &t.twinit - &t.bset;

	/*
	 * Copy the integers at the start of the table.
	 */
	bcopy((char *) &t, (char *) buf, twbase * sizeof (int));

	/*
	 * Replace the character pointers in the copy with integer offsets.
	 * This duplicates the effect of relocation offsets.
	 * Take care to count the possibly null control bytes in the codetab
	 *	section.
	 */
	for (bip = &buf[twbase], tip = &t.twinit;
	     tip < &t.codetab[0];
	     ++bip, ++tip)
		if (*tip) {
			*bip = offset;
			offset += strlen(*tip) + 1;
		} else
			*bip = 0;
	for (; tip < &t.zzz; ++bip, ++tip)
		if (*tip) {
			*bip = offset;
			offset += strlen(*tip + 1) + 2;
		} else
			*bip = 0;

	/*
	 * Patch in a fake data segment size field.
	 */
	fe.bogus[2] = offset;

	/*
	 * Dump the header and the table.
	 */
	(void) fwrite((char *) &fe, sizeof fe, 1, stdout);
	(void) fwrite((char *) buf, sizeof t, 1, stdout);

	/*
	 * Dump the strings.
	 */
	for (tip = &t.twinit; tip < &t.codetab[0]; ++tip)
		if (*tip) {
			fputs(*tip, stdout);
			putchar('\0');
		}
	for (tip = &t.codetab[0]; tip < &t.zzz; ++tip)
		if (*tip) {
			putchar(**tip);
			fputs(*tip + 1, stdout);
			putchar('\0');
		}

	return 0;
}
E 1
