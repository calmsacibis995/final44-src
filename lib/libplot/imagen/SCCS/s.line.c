h17304
s 00002/00002/00039
d D 8.1 93/06/04 17:44:56 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00035
d D 5.3 91/04/22 15:55:17 bostic 3 2
c new copyright; att/bsd/shared
e
s 00006/00007/00034
d D 5.2 85/09/21 16:21:39 sam 2 1
c bring in most up to date code; removes hardcoded printer resolution; 
c adds 2 pixels to effective plotting resolution; parameterizes font and point size; 
c make linemod a hack to set font from plot file
e
s 00041/00000/00000
d D 5.1 85/09/21 15:05:53 sam 1 0
c date and time created 85/09/21 15:05:53 by sam
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

#include "imp.h"
#include "imPcodes.h"
D 2

E 2
float obotx = 0.;
float oboty = 0.;
D 2
float botx = 0.;
float boty = 0.;
E 2
I 2
float botx = 2.;
float boty = 2.;
E 2
float scalex = 1.;
float scaley = 1.;
line(x0,y0,x1,y1)
{
	putch(imP_CREATE_PATH);
	putwd(2);		/* two coordinates follow */
D 2
	putwd((int)((x0-obotx)*scalex+botx+1));	
	putwd((int)((y0-oboty)*scaley+boty+1));	
	putwd((int)((x1-obotx)*scalex+botx+1));	
	putwd((int)((y1-oboty)*scaley+boty+1));	
E 2
I 2
	putwd((int)((x0-obotx)*scalex+botx));	
	putwd((int)((y0-oboty)*scaley+boty));	
	putwd((int)((x1-obotx)*scalex+botx));	
	putwd((int)((y1-oboty)*scaley+boty));	
E 2
	putch(imP_DRAW_PATH);
	putch(15);		/* "black" lines */
	imPx = x1;
	imPy = y1;
}
putch(c)
{
	putc(c, stdout);
}
putwd(w)
{
	putch(w>>8);
	putch(w);
}
E 1
