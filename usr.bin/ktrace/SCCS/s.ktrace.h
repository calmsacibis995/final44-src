h32627
s 00002/00002/00013
d D 8.1 93/06/06 14:53:24 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00012
d D 5.2 92/04/15 17:27:59 marc 4 3
c split out trace points into default and complete list
e
s 00000/00007/00013
d D 5.1 91/01/17 15:58:01 bostic 3 2
c distribute includes around
e
s 00014/00003/00006
d D 1.2 90/06/29 00:38:07 marc 2 1
c copyright; textual changes
e
s 00009/00000/00000
d D 1.1 89/01/04 21:11:45 marc 1 0
c date and time created 89/01/04 21:11:45 by marc
e
u
U
t
T
I 2
/*-
D 5
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
D 3
#include <sys/param.h>
#include <sys/file.h>
D 2
#include <sys/dir.h>
E 2
#include <sys/user.h>
I 2
#include <sys/proc.h>
E 2
#include <sys/ktrace.h>
#include <stdio.h>

E 3
D 2
#define DEF_FACS (KTRFAC_SYSCALL | KTRFAC_SYSRET | KTRFAC_NAMEI)
#define DEF_TRACEFILE	"ktrace.data"
E 2
I 2
D 4
#define ALL_POINTS (KTRFAC_SYSCALL | KTRFAC_SYSRET | KTRFAC_NAMEI | \
E 4
I 4
#define DEF_POINTS (KTRFAC_SYSCALL | KTRFAC_SYSRET | KTRFAC_NAMEI | \
E 4
		  KTRFAC_GENIO | KTRFAC_PSIG)
I 4

#define ALL_POINTS (DEF_POINTS | KTRFAC_CSW)
E 4

#define DEF_TRACEFILE	"ktrace.out"
E 2
E 1
