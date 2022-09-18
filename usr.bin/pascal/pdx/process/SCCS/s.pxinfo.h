h14172
s 00002/00002/00053
d D 8.1 93/06/06 15:43:18 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00050
d D 5.4 91/04/16 15:17:43 bostic 7 6
c new copyright; att/bsd/shared
e
s 00007/00008/00047
d D 5.3 89/01/09 17:25:05 mckusick 6 4
c from John Gilmore for gcc
e
s 00008/00008/00047
d R 5.3 89/01/09 17:23:00 mckusick 5 4
c from John Gilmore for gcc
e
s 00017/00000/00038
d D 5.2 87/04/07 15:55:09 mckusick 4 3
c port to tahoe by Nir peleg of CCI
e
s 00007/00003/00031
d D 5.1 85/06/06 16:18:47 dist 3 2
c Add copyright
e
s 00001/00001/00033
d D 1.2 82/01/18 21:59:31 linton 2 1
c sccsid
e
s 00034/00000/00000
d D 1.1 82/01/18 19:20:47 linton 1 0
c date and time created 82/01/18 19:20:47 by linton
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1982 Regents of the University of California */

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
/* static char sccsid[] = "%Z%%M% %I% %G%"; */
E 3
I 3
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 3
E 2

/*
 * This is the information we get after the initial trap that px does.
 * By passing the "-d" flag, we cause px to call a procedure with the
 * the following information:
 *
 *	address of the display
 *	address of the display pointer
 *	address of the beginning of the object code
 *
D 6
 *	the address of a variable containing the address of the first local
 *		variable in the interpreter procedure
 *		(this is used to find the frame where the pc is)
 *	the address of the main interpreter loop
E 6
I 6
 *	the address of the program counter used in the interpreter procedure
 *		(px actually keeps the pc in a register if it can, but stores
 *		 it in this location each time around the interpreter loop.)
 *	the address of the main interpreter loop (past the store of pc)
E 6
 */

I 4
#ifdef tahoe
E 4
typedef struct {
I 4
	short trp_savemask;
	short trp_removed;
	int trp_oldfp;
	ADDRESS *disp;
	ADDRESS *dp;
	ADDRESS objstart;
D 6
	ADDRESS pcaddrp;
E 6
I 6
	ADDRESS pcaddr;
E 6
	ADDRESS loopaddr;
} TRAPARGS;
#else
typedef struct {
E 4
	int nargs;
	ADDRESS *disp;
	ADDRESS *dp;
	ADDRESS objstart;
D 6
	ADDRESS pcaddrp;
E 6
I 6
	ADDRESS pcaddr;
E 6
	ADDRESS loopaddr;
} TRAPARGS;
I 4
#endif
E 4

ADDRESS *DISPLAY;
ADDRESS *DP;
ADDRESS ENDOFF;
D 6
ADDRESS PCADDRP;
E 6
I 6
ADDRESS PCADDR;
E 6
ADDRESS LOOPADDR;
D 6
ADDRESS *pcframe;
E 6
I 4
#ifdef tahoe
ADDRESS RETLOC;
ADDRESS INTFP;
#endif
E 4
E 1
