h36382
s 00002/00002/00038
d D 8.1 93/06/06 22:30:37 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00037
d D 3.5 90/06/06 21:44:39 bostic 5 4
c fix contrib notice (Edward Wang)
e
s 00001/00011/00036
d D 3.4 90/06/02 15:22:23 bostic 4 3
c new copyright notice
e
s 00010/00005/00037
d D 3.3 88/06/29 21:36:57 bostic 3 2
c install approved copyright notice
e
s 00013/00007/00029
d D 3.2 88/02/21 13:37:46 bostic 2 1
c written by Edward Wang; attach Berkeley specific copyright
e
s 00036/00000/00000
d D 3.1 86/08/04 15:16:17 edward 1 0
c date and time created 86/08/04 15:16:17 by edward
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

E 2
/*
D 2
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 2
I 2
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
I 5
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 5
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
E 2
 */
I 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include "ww.h"
#include "tt.h"

/*
 * Zentec 1021
 *
 * We let the termcap entry specify how to enter and exit graphics mode,
 * since it varies with what the terminal is emulating.
 */

#define G (WWM_GRP << WWC_MSHIFT)
short zentec_frame[16] = {
	' ',	'x'|G,	'q'|G,	'm'|G,
	'x'|G,	'x'|G,	'l'|G,	't'|G,
	'q'|G,	'j'|G,	'q'|G,	'v'|G,
	'k'|G,	'u'|G,	'w'|G,	'n'|G
};

tt_zentec()
{
	if (tt_generic() < 0)
		return -1;
	if (tt.tt_availmodes | WWM_GRP)
		tt.tt_frame = zentec_frame;
	return 0;
}
E 1
