h06162
s 00002/00002/00094
d D 8.1 93/06/10 23:50:23 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00096
d D 7.3 93/03/09 23:37:56 utashiro 3 2
c cleanup header and machine dependency.
e
s 00006/00007/00092
d D 7.2 92/12/17 02:43:59 utashiro 2 1
c make kernel includes standard
e
s 00099/00000/00000
d D 7.1 92/06/04 15:57:45 mckusick 1 0
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
 * from: $Hdr: askrom.c,v 4.300 91/06/09 06:32:39 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "../include/fix_machine_type.h"
E 2
I 2
D 3
#include <machine/fix_machine_type.h>
E 2

E 3
#include "nwb514.h"
#include "nwb251.h"
#include "nwb256.h"

#if NNWB514 > 0 || NNWB251 > 0 || NNWB256 > 0

#ifdef IPC_MRX
#include "../../h/param.h"
#include "../../iop/framebuf.h"
#include "../../iop/fbreg.h"
#else
#include <sys/types.h>
D 2
#include "../h/types.h"
#include "../h/param.h"
#include "../iop/framebuf.h"
#include "../iop/fbreg.h"
E 2
I 2
#include <sys/param.h>
#include <news3400/iop/framebuf.h>
#include <news3400/iop/fbreg.h>
E 2
#endif

D 2
#include "../fb/fbdefs.h"
E 2
I 2
#include <news3400/fb/fbdefs.h>
E 2

D 2
#include "../fb/qpdm.h"
E 2
I 2
#include <news3400/fb/qpdm.h>
E 2

extern short zero[];

extern char *ext_fnt_addr[];
extern char *ext_fnt24_addr[];

int krom_enable = 0;

caddr_t
autos_Krom_addr(fb, c, sr)
	struct fbdev *fb;
	register int c;
	lRectangle *sr;
{
	unsigned int cvcode24();

	if ((c >= 0x20) && (c <= 0x7e)) {
		/*
		 * ASCII char
		 */
		c -= ' ';
		c = ((c & 0x1f) | ((c & 0xe0) << 2)) << 7;
		return ((caddr_t)(c + QP_KJROM + (sr->extent.y > 16 ? 0 : 96)));
	} else if ((c >= 0xa1) && (c <= 0xdf)) {
		/*
		 * KANA char
		 */
		if (sr->extent.y > 16)
			return ((caddr_t)ext_fnt24_addr[c + 64]);
		else
			return ((caddr_t)ext_fnt_addr[c + 64]);
	} else if ((c >= 0x2000) && (c <= 0x7fff)) {
		/*
		 * KANJI char
		 */
		switch (c & 0x7000) {
		case 0x2000:
			c = ((c & 0x1f)|((c & 0x60)<<5)|((c & 0x700)>>1))<<7;
			break;
		case 0x3000:
		case 0x4000:
			c = ((c & 0x7f)|((c & 0xf00)>>1)|((c & 0x4000)>>3))<<7;
			break;
		case 0x5000:
		case 0x6000:
			c = ((c & 0x7f)|((c & 0xf00)>>1)
					|((c & 0x2000)>>2)|0x1000) << 7;
			break;
		case 0x7000:
			c = ((c & 0x1f)|((c & 0x60)<<5)
					| ((c & 0x700)>>1)|0x1000) << 7;
			break;
		}
		return ((caddr_t)(c + QP_KJROM + (sr->extent.y > 16 ? 0 : 96)));
	} else {
		/*
		 * UNKNOWN char
		 */
		return ((caddr_t)zero);
	}
}
#endif /* NNWB514 > 0 || NNWB251 > 0 || NNWB256 > 0 */
E 1
