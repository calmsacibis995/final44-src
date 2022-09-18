h39254
s 00002/00002/00118
d D 8.1 93/06/11 15:00:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00017/00119
d D 7.3 93/03/09 23:52:42 utashiro 3 2
c cleanup header and machine dependency.
e
s 00001/00001/00135
d D 7.2 92/12/17 03:18:10 utashiro 2 1
c make kernel includes standard
e
s 00136/00000/00000
d D 7.1 92/06/04 15:54:59 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: kbreg.h,v 4.300 91/06/09 06:42:47 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

#ifndef __KEYBOARD__
#define __KEYBOARD__ 1

D 2
#include "machine/fix_machine_type.h"
E 2
I 2
D 3
#include <machine/fix_machine_type.h>
E 2

E 3
#define	key_any(x)	((x) != -1)
#define	key_down(x)	(((x) & 0x80) == 0)
#define	key_up(x)	((x) & 0x80)

D 3
/*
 *
 */
E 3
typedef	struct key_string {
	int	key_length;
	char	*key_string;
} Key_string;

typedef struct pfk_table {
	int		pfk_addr;
	Key_string	pfk_normal;
	Key_string	pfk_shift;
} Pfk_table;

typedef	struct pfk_string {
	int		pfk_num;
	int		pfk_shift;
	Key_string	pfk_string;
} Pfk_string;

#define	KBDPRI		28

D 3
#ifdef news800
#define	KB_TEST		0
#endif news800

E 3
#define	KIOCSETS	0		/* set pfk string	*/
#define	KIOCBELL	1		/* ring bell		*/
#define	KIOCBACK	2		/* push back string	*/
#define	KIOCREPT	3		/* auto repeat on	*/
#define	KIOCNRPT	4		/* auto repeat off	*/
#define	KIOCGETS	5		/* get pfk string	*/
#define	KIOCRAW		6		/* get raw key data	*/
#define	KIOCSETE	7
#define	KIOCFLUSH	8
#define	KIOCNREAD	FIONREAD	/* return input char's	*/
#define	KIOCSETLOCK	10		/* set lock type	*/
#define	KIOCSETTBL	11		/* set key_table	*/
#define	KIOCGETCNUM	12		/* get country number	*/
#define	KIOCSETCNUM	13		/* set country number	*/
#define	KIOCDEFTBL	14		/* default key_table 	*/
#define	KIOCCHTBL	15		/* change key_table 	*/
#define	KIOCOYATBL	16		/* oya_key_table	*/
#define	KIOCGETSTAT	17		/* get keyboard status	*/
#define	KIOCSETSTAT	18		/* set keyboard status	*/

D 3
/*
 *
 */
E 3
#define	OFF		0x80
D 3
#ifndef SS2
#define	SS2		0x8e
#endif
E 3

extern int N_Pfk;
#define	N_PFK		N_Pfk

#define	N_KEY		93

/*
D 3
 *	Programmable function key
E 3
I 3
 * Programmable function key
E 3
 */
#define	F1		1
#define	F2		2
#define	F3		3
#define	F4		4
#define	F5		5
#define	F6		6
#define	F7		7
#define	F8		8
#define	F9		9
#define	F10		10

#define	PF1		11
#define	PF2		12
#define	PF3		13
#define	PF4		14
#define	PF5		15
#define	PF6		16
#define	PF7		17
#define	PF8		18
#define	PF9		19
#define	PF10		20
#define	PF11		21
#define	PF12		22

#define	NCNV		23
#define	CONV		24
#define	ENTER		25

#define	N0		26
#define	N1		27
#define	N2		28
#define	N3		29
#define	N4		30
#define	N5		31
#define	N6		32
#define	N7		33
#define	N8		34
#define	N9		35

#define	PERIOD		36
#define	MINUS		37
#define	PLUS		38
#define	COMMA		39
#define	NENTER		40
#define	UP		41
#define	DOWN		42
#define	RIGHT		43
#define	LEFT		44
D 3

E 3

#endif /* !__KEYBOARD__ */
E 1
