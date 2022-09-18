h58318
s 00002/00002/00025
d D 8.1 93/06/06 22:22:48 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 5.1 93/05/21 15:10:07 torek 1 0
c date and time created 93/05/21 15:10:07 by torek
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
 *
 *	%W% (Berkeley) %G%
 */

#ifdef hp300
char *defdrives[] = { "sd0", "sd1", "sd2", "rd0", "rd1", "rd2", 0 };
#define	DONE
#endif

#ifdef tahoe
char *defdrives[] = { "dk0", "dk1", "dk2", 0 };
#define	DONE
#endif

#ifdef vax
char *defdrives[] = { "hp0", "hp1", "hp2", 0 };
#define	DONE
#endif

#ifndef DONE
char *defdrives[] = { 0 };
#endif
E 1
