h36217
s 00002/00002/00044
d D 8.1 93/06/11 15:13:58 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00044
d D 7.4 93/04/20 19:20:15 torek 4 3
c spelling
e
s 00007/00007/00039
d D 7.3 92/10/11 12:45:40 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00041
d D 7.2 92/07/21 16:50:39 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00041/00000/00000
d D 7.1 92/07/13 00:43:47 torek 1 0
c date and time created 92/07/13 00:43:47 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: rcons_font.c,v 1.8 92/06/17 06:23:37 torek Exp $
E 4
I 4
 * from: $Header: rcons_font.c,v 1.10 93/04/20 11:15:38 torek Exp $
E 4
 */

#ifdef KERNEL
D 3
#include "sys/param.h"
#include "sys/kernel.h"
#include "sys/fbio.h"
#include "sys/device.h"
#include "machine/fbvar.h"
E 3
I 3
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/fbio.h>
#include <sys/device.h>
#include <machine/fbvar.h>
E 3
#else
#include <sys/types.h>
#include "myfbdevice.h"
#endif

D 3
#include "raster.h"
E 3
I 3
#include <sparc/rcons/raster.h>
E 3

D 3
#include "gallant19.h"
E 3
I 3
#include <sparc/rcons/gallant19.h>
E 3

void
rcons_font(fb)
	register struct fbdevice *fb;
{

	/* XXX really rather get this from the prom */
	fb->fb_font = &gallant19;

	/* Get distance to top and bottom of font from font origin */
	fb->fb_font_ascent = -(fb->fb_font->chars)['a'].homey;
}
E 1
