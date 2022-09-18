h26723
s 00002/00002/00229
d D 8.1 93/06/10 21:23:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00229
d D 7.4 92/10/11 08:55:09 bostic 4 3
c make kernel includes standard
e
s 00017/00018/00214
d D 7.3 90/12/16 16:36:08 bostic 3 2
c kernel reorg
e
s 00001/00001/00231
d D 7.2 90/11/04 19:30:50 mckusick 2 1
c update identifier from Utah
e
s 00232/00000/00000
d D 7.1 90/05/08 22:06:58 mckusick 1 0
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
D 2
 * from: Utah $Hdr: hil_keymaps.c 1.1 89/08/22$
E 2
I 2
 * from: Utah $Hdr: hil_keymaps.c 1.1 90/07/09$
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
D 3
 * Keymaps for various HP-HIL keyboard layouts.
 * These tables apply only to keyboards in "cooked" mode.
 * Currently only one is supported as an ITE keyboard.
E 3
I 3
 * Keymaps for various HP-HIL keyboard layouts.  These tables apply only to
 * keyboards in "cooked" mode.  Currently only one is supported as an ITE
 * keyboard.
E 3
 *
D 3
 * Maps are indexed by cooked keycode and contain the ASCII
 * character for that keycode.  The map-set used depends on the
 * keyboard "language".  The map used within that set depends on
 * the shift/control status that is returned by the hardware along
 * with the keycode.  If an entry is NULL for a key in the appropriate
 * unshifted, shifted, control, or control-shifted table, then a
 * single "string" table is consulted.  In this fashion, a multi-
 * character sequence can be returned for a key press.  Note that
 * control/shift status have no effect on multi-character lookup
 * (i.e. there is only one string table per set, not four).
E 3
I 3
 * Maps are indexed by cooked keycode and contain the ASCII character for
 * that keycode.  The map-set used depends on the keyboard "language".  The
 * map used within that set depends on the shift/control status that is
 * returned by the hardware along with the keycode.  If an entry is NULL for
 * a key in the appropriate unshifted, shifted, control, or control-shifted
 * table, then a single "string" table is consulted.  In this fashion, a
 * multi- character sequence can be returned for a key press.  Note that
 * control/shift status have no effect on multi-character lookup (i.e. there
 * is only one string table per set, not four).
E 3
 *
D 3
 * Someday we could allow user-definable keymaps, but we would have
 * to come up with a better format (at least externally).  This
 * format takes up lots of space.  Having keymaps for all 18 or so
 * HP supported layouts would be bad news.
E 3
I 3
 * Someday we could allow user-definable keymaps, but we would have to come up
 * with a better format (at least externally).  This format takes up lots of
 * space.  Having keymaps for all 18 or so HP supported layouts would be bad
 * news.
E 3
 */
D 3
#include "param.h"
E 3
I 3
D 4
#include "sys/param.h"
E 3
#include "kbdmap.h"
E 4
I 4
#include <sys/param.h>
#include <hp/dev/kbdmap.h>
E 4

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

char	us_ctrlshiftmap[] = {
	NULL,	'~',	'|',	DEL,	NULL,	DEL,	NULL,	NULL,
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	DEL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'`',	'|',	'\034',	'~',
	'!',	'\000',	'#',	'$',	'%',	'\036',	'&',	'*',
	'(',	')',	'\037',	'+',	'{',	'}',	':',	'\"',
	'<',	'>',	'?',	'\040',	'\017',	'\020',	'\013',	'\014',
	'\021',	'\027',	'\005',	'\022',	'\024',	'\031',	'\025',	'\011',
	'\001',	'\023',	'\004',	'\006',	'\007',	'\010',	'\012',	'\015',
	'\032',	'\030',	'\003',	'\026',	'\002',	'\016',	NULL,	NULL
};

char	*us_stringmap[] = {
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	"\033V","\033h",
	"\033U",NULL,	NULL,	NULL,	NULL,	NULL,	"\033K","\033J",
	NULL,	NULL,	NULL,	"\033p","\033q","\033t","\033u","\033v",
	"\033r","\033s","\033B","\033A","\033w",NULL,	"\033D","\033C",
	"\033L","\033M",NULL,	NULL,	"\033P",NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL
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

char	uk_ctrlshiftmap[] = {
	NULL,	'~',	'>',	DEL,	NULL,	DEL,	NULL,	NULL,
	'\n',	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\n',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	'\t',	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	DEL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ESC,	'\r',	NULL,	'\n',	'0',	'.',	',',	'+',
	'1',	'2',	'3',	'-',	'4',	'5',	'6',	'*',
	'7',	'8',	'9',	'/',	'`',	'|',	'\034',	'~',
	'!',	'\"',	'#',	'$',	'%',	'&',	'\036',	'(',
	')',	'=',	'?',	'/',	'{',	'}',	'\000',	'|',
	';',	':',	'\037',	'\040',	'\017',	'\020',	'\013',	'\014',
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
	KBD_US,		"US ASCII",
	us_keymap,	us_shiftmap,	us_ctrlmap,	us_ctrlshiftmap,
	us_stringmap,

#ifdef UK_KEYBOARD
	KBD_UK,		"United Kingdom",
	uk_keymap,	uk_shiftmap,	uk_ctrlmap,	uk_ctrlshiftmap,
	us_stringmap,
#endif

	0,		NULL,
	NULL,		NULL,		NULL,		NULL,
	NULL,
};
E 1
