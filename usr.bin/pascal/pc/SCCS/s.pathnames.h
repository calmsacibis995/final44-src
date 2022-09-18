h59510
s 00002/00002/00038
d D 8.1 93/06/06 15:27:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00038
d D 5.2 92/03/07 11:09:48 bostic 2 1
c move pcc assembler/loader to /usr/old/bin
e
s 00040/00000/00000
d D 5.1 90/06/29 07:35:48 mckusick 1 0
c date and time created 90/06/29 07:35:48 by mckusick
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	_PATH_PC0	"/usr/libexec/pascal/pc0"
#define	_PATH_PC1	"/usr/libexec/f1"
#define	_PATH_PC2	"/usr/libexec/pascal/pc2"
#define	_PATH_C2	"/usr/libexec/c2"
#define	_PATH_PC3	"/usr/libexec/pascal/pc3"
#define	_PATH_PCEXTERN	"/usr/lib/pcexterns.o"

D 2
#define	_PATH_AS	"/usr/bin/as"
#define	_PATH_LD	"/usr/bin/ld"
E 2
I 2
#define	_PATH_AS	"/usr/old/bin/as"
#define	_PATH_LD	"/usr/old/bin/ld"
E 2
#define	_PATH_CRT0	"/usr/lib/crt0.o"
#define	_PATH_MCRT0	"/usr/lib/mcrt0.o"
#define	_PATH_GCRT0	"/usr/lib/gcrt0.o"

#define	_PATH_TMP	"/tmp"
#define	_PATH_CAT	"/bin/cat"
#define	_PATH_HOWPC	"/usr/libdata/pascal/how_pc"

/* DEBUG */
#define	_PATH_DPC0	"/usr/src/pgrm/pascal/pc0/obj/pc0"
#ifdef vax
#define	_PATH_DPC1	"/usr/src/libexec/pcc/f1.vax/obj/f1"
#else
#ifdef tahoe
#define	_PATH_DPC1	"/usr/src/libexec/pcc/f1.tahoe/obj/f1"
#else
NO F1 PROGRAM AVAILABLE
#endif
#endif
#define	_PATH_DPC2	"/usr/src/pgrm/pascal/pc2/obj/pc2"
#define	_PATH_DPC3	"/usr/src/pgrm/pascal/pc3/obj/pc3"
#define	_PATH_DLPC	"/usr/src/lib/libpc/obj/libpc.a"
E 1
