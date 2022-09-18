h17179
s 00002/00002/00048
d D 8.1 93/06/06 22:30:28 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00049
d D 3.4 90/06/06 21:44:33 bostic 4 3
c fix contrib notice (Edward Wang)
e
s 00001/00011/00049
d D 3.3 90/06/02 15:22:09 bostic 3 2
c new copyright notice
e
s 00026/00012/00034
d D 3.2 88/12/28 09:57:43 bostic 2 1
c  add Berkeley copyright for consistency
e
s 00046/00000/00000
d D 3.1 87/10/06 00:36:05 edward 1 0
c date and time created 87/10/06 00:36:05 by edward
e
u
U
t
T
I 1
D 2
#ifndef lint
static char sccsid[] = "%W% %G%";
#endif

#include "ww.h"
#include "tt.h"

E 2
/*
D 2
 * Wyse-60
E 2
I 2
 * Copyright 1987 by David C. Elliott, MIPS Computer Systems.
E 2
 *
D 2
 * Contributed by David Elliott of MIPS (mips!dce).
E 2
I 2
 * Unlimited redistribution allowed as long as this notice
 * is kept intact.
E 2
 */

/*
D 2
 * Copyright 1987 by David C. Elliott, MIPS Computer Systems.
E 2
I 2
D 5
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
E 2
 *
D 2
 * Unlimited redistribution allowed as long as this notice
 * is kept intact.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
D 4
 * David C. Elliott.
E 4
I 4
 * David C. Elliott, of MIPS Computer Systems.
E 4
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */
I 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "ww.h"
#include "tt.h"
E 2

#define G (WWM_GRP << WWC_MSHIFT)
short wyse60_frame[16] = {
	' ',	'6'|G,	':'|G,	'1'|G,
	'6'|G,	'6'|G,	'2'|G,	'4'|G,
	':'|G,	'5'|G,	':'|G,	'='|G,
	'3'|G,	'9'|G,	'0'|G,	'0'|G
};

extern struct tt_str *gen_AS;
extern struct tt_str *gen_AE;

tt_wyse60()
{
	static struct tt_str ae = { "\033H\003", 3 };
	static struct tt_str as = { "\033H\002", 3 };

	if (tt_generic() < 0)
		return -1;
	tt.tt_availmodes |= WWM_GRP;
	tt.tt_frame = wyse60_frame;
	if (gen_AS == 0)
		gen_AS = &as;
	if (gen_AE == 0)
		gen_AE = &ae;
	return 0;
}
E 1
