h37017
s 00002/00002/00232
d D 8.1 93/06/10 21:46:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00229
d D 7.4 92/10/11 10:01:38 bostic 4 3
c make kernel includes standard
e
s 00003/00003/00231
d D 7.3 92/06/18 21:33:22 hibler 3 2
c merge with latest Utah version
e
s 00004/00004/00230
d D 7.2 90/12/16 16:39:18 bostic 2 1
c kernel reorg
e
s 00234/00000/00000
d D 7.1 90/05/08 22:46:03 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: hil.c 1.1 89/08/22$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Keyboard routines for the standalone ITE.
 */
D 4
#include "samachdep.h"
E 4
I 4
#include <hp300/stand/samachdep.h>
E 4

#ifdef ITECONSOLE

D 2
#include "param.h"
#include "../hpdev/hilreg.h"
#include "../hpdev/kbdmap.h"
#include "../hpdev/itevar.h"
E 2
I 2
D 4
#include "sys/param.h"
D 3
#include "../dev/hilreg.h"
#include "../dev/kbdmap.h"
#include "../dev/itevar.h"
E 3
I 3
#include "hp/dev/hilreg.h"
#include "hp/dev/kbdmap.h"
#include "hp/dev/itevar.h"
E 4
I 4
#include <sys/param.h>
#include <hp/dev/hilreg.h>
#include <hp/dev/kbdmap.h>
#include <hp/dev/itevar.h>
E 4
E 3
E 2

#ifndef SMALL

/*
 * HIL cooked keyboard keymaps.
 * Supports only unshifted, shifted and control keys.
 */
char	us_keymap[] = {
	NULL,	'`',	'\\',	ESC,	NULL,	DEL,	NULL,	NULL,  
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,  
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,  
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	'\b',	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'E',	'(',	')',	'^',
	'1',	'2',	'3',	'4',	'5',	'6',	'7',	'8',
	'9',	'0',	'-',	'=',	'[',	']',	';',	'\'',
	',',	'.',	'/',	'\040',	'o',	'p',	'k',	'l',
	'q',	'w',	'e',	'r',	't',	'y',	'u',	'i',
	'a',	's',	'd',	'f',	'g',	'h',	'j',	'm',
	'z',	'x',	'c',	'v',	'b',	'n',	NULL,	NULL
};

char	us_shiftmap[] = {
	NULL,	'~',	'|',	DEL,	NULL,	DEL,	NULL,	NULL,
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	DEL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'`',	'|',	'\\',	'~',
	'!',	'@',	'#',	'$',	'%',	'^',	'&',	'*',
	'(',	')',	'_',	'+',	'{',	'}',	':',	'\"',
	'<',	'>',	'?',	'\040',	'O',	'P',	'K',	'L',
	'Q',	'W',	'E',	'R',	'T',	'Y',	'U',	'I',
	'A',	'S',	'D',	'F',	'G',	'H',	'J',	'M',
	'Z',	'X',	'C',	'V',	'B',	'N',	NULL,	NULL
};

char	us_ctrlmap[] = {
	NULL,	'`',	'\034',	ESC,	NULL,	DEL,	NULL,	NULL,
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	'\b',	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'E',	'(',	')',	'\036',
	'1',	'2',	'3',	'4',	'5',	'6',	'7',	'8',
	'9',	'0',	'-',	'=',	'\033',	'\035',	';',	'\'',
	',',	'.',	'/',	'\040',	'\017',	'\020',	'\013',	'\014',
	'\021',	'\027',	'\005',	'\022',	'\024',	'\031',	'\025',	'\011',
	'\001',	'\023',	'\004',	'\006',	'\007',	'\010',	'\012',	'\015',
	'\032',	'\030',	'\003',	'\026',	'\002',	'\016',	NULL,	NULL
};

#ifdef UK_KEYBOARD
char	uk_keymap[] = {
	NULL,	'`',	'<',	ESC,	NULL,	DEL,	NULL,	NULL,  
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,  
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,  
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	'\b',	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'E',	'(',	')',	'^',
	'1',	'2',	'3',	'4',	'5',	'6',	'7',	'8',
	'9',	'0',	'+',	'\'',	'[',	']',	'*',	'\\',
	',',	'.',	'-',	'\040',	'o',	'p',	'k',	'l',
	'q',	'w',	'e',	'r',	't',	'y',	'u',	'i',
	'a',	's',	'd',	'f',	'g',	'h',	'j',	'm',
	'z',	'x',	'c',	'v',	'b',	'n',	NULL,	NULL
};

char	uk_shiftmap[] = {
	NULL,	'~',	'>',	DEL,	NULL,	DEL,	NULL,	NULL,
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	DEL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'`',	'|',	'\\',	'~',
	'!',	'\"',	'#',	'$',	'%',	'&',	'^',	'(',
	')',	'=',	'?',	'/',	'{',	'}',	'@',	'|',
	';',	':',	'_',	'\040',	'O',	'P',	'K',	'L',
	'Q',	'W',	'E',	'R',	'T',	'Y',	'U',	'I',
	'A',	'S',	'D',	'F',	'G',	'H',	'J',	'M',
	'Z',	'X',	'C',	'V',	'B',	'N',	NULL,	NULL
};

char	uk_ctrlmap[] = {
	NULL,	'`',	'<',	ESC,	NULL,	DEL,	NULL,	NULL,
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	'\b',	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'E',	'(',	')',	'\036',
	'1',	'2',	'3',	'4',	'5',	'6',	'7',	'8',
	'9',	'0',	'+',	'\'',	'\033',	'\035',	'*',	'\034',
	',',	'.',	'/',	'\040',	'\017',	'\020',	'\013',	'\014',
	'\021',	'\027',	'\005',	'\022',	'\024',	'\031',	'\025',	'\011',
	'\001',	'\023',	'\004',	'\006',	'\007',	'\010',	'\012',	'\015',
	'\032',	'\030',	'\003',	'\026',	'\002',	'\016',	NULL,	NULL
};
#endif

/*
 * The keyboard map table.
 * Lookup is by hardware returned language code.
 */
struct kbdmap kbd_map[] = {
	KBD_US,		NULL,
	us_keymap,	us_shiftmap,	us_ctrlmap,	NULL,	NULL,

#ifdef UK_KEYBOARD
	KBD_UK,		NULL,
	uk_keymap,	uk_shiftmap,	uk_ctrlmap,	NULL,	NULL,
#endif

	0,		NULL,
	NULL,		NULL,		NULL,		NULL,	NULL,
};

char	*kbd_keymap = us_keymap;
char	*kbd_shiftmap = us_shiftmap;
char	*kbd_ctrlmap = us_ctrlmap;

kbdgetc()
{
	register int status, c;
	register struct hil_dev *hiladdr = HILADDR;

	status = hiladdr->hil_stat;
	if ((status & HIL_DATA_RDY) == 0)
		return(0);
	c = hiladdr->hil_data;
	switch ((status>>KBD_SSHIFT) & KBD_SMASK) {
	case KBD_SHIFT:
		c = kbd_shiftmap[c & KBD_CHARMASK];
		break;
	case KBD_CTRL:
		c = kbd_ctrlmap[c & KBD_CHARMASK];
		break;
	case KBD_KEY:
		c = kbd_keymap[c & KBD_CHARMASK];
		break;
	default:
		c = 0;
		break;
	}
	return(c);
}
#endif

kbdnmi()
{
	register struct hil_dev *hiladdr = HILADDR;

	HILWAIT(hiladdr);
	hiladdr->hil_cmd = HIL_CNMT;
	HILWAIT(hiladdr);
	hiladdr->hil_cmd = HIL_CNMT;
	HILWAIT(hiladdr);
	printf("\nboot interrupted\n");
}

kbdinit()
{
	register struct hil_dev *hiladdr = HILADDR;
	register struct kbdmap *km;
	u_char lang;

	HILWAIT(hiladdr);
	hiladdr->hil_cmd = HIL_SETARR;
	HILWAIT(hiladdr);
	hiladdr->hil_data = ar_format(KBD_ARR);
	HILWAIT(hiladdr);
	hiladdr->hil_cmd = HIL_READKBDLANG;
	HILDATAWAIT(hiladdr);
	lang = hiladdr->hil_data;
	for (km = kbd_map; km->kbd_code; km++)
		if (km->kbd_code == lang) {
			kbd_keymap = km->kbd_keymap;
			kbd_shiftmap = km->kbd_shiftmap;
			kbd_ctrlmap = km->kbd_ctrlmap;
		}
	HILWAIT(hiladdr);
	hiladdr->hil_cmd = HIL_INTON;
}
#endif
E 1
