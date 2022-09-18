h15270
s 00002/00002/00037
d D 8.1 93/06/10 21:24:32 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00000/00000
d D 7.1 90/05/08 22:06:45 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	ESC	'\033'
#define	DEL	'\177'

struct kbdmap {
	int	kbd_code;
	char	*kbd_desc;
	char	*kbd_keymap;
	char	*kbd_shiftmap;
	char	*kbd_ctrlmap;
	char	*kbd_ctrlshiftmap;
	char	**kbd_stringmap;
};

/* kbd_code */
#define KBD_SPECIAL	0x00		/* user defined */
#define KBD_US		0x1F		/* US ASCII */
#define KBD_UK		0x17		/* United Kingdom */

#define KBD_DEFAULT	KBD_US		/* default type */

#ifdef KERNEL
/* XXX: ITE interface */
char	*kbd_keymap;
char	*kbd_shiftmap;
char	*kbd_ctrlmap;
char	*kbd_ctrlshiftmap;
char	**kbd_stringmap;

extern struct kbdmap kbd_map[];
#endif
E 1
