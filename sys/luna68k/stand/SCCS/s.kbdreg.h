h00544
s 00002/00002/00030
d D 8.1 93/06/10 22:29:33 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00000/00000
d D 7.1 92/12/13 03:50:16 akito 1 0
c date and time created 92/12/13 03:50:16 by akito
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
 * kbdreg.h --
 *
 */

struct kbd_keymap {
	int	km_type;
	int	km_code[2];
};

#define KC_CHAR		0x000000FF
#define KC_TYPE		0x0000FF00
#define	KC_CODE		0x00000000
#define	KC_SHIFT	0x00000100
#define	KC_IGNORE	0x0000FF00

#define KS_SHIFT	0
#define KS_CTRL		1
#define KS_META		2
E 1
