h49927
s 00002/00002/00032
d D 8.1 93/06/04 16:52:04 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00034
d D 5.3 92/07/03 00:23:55 christos 3 2
c Up-to-date with cornell's last RCS version
e
s 00001/00001/00033
d D 5.2 92/06/22 18:24:03 marc 2 1
c merge editline.h and history.h
e
s 00034/00000/00000
d D 5.1 92/06/22 18:08:33 bostic 1 0
c date and time created 92/06/22 18:08:33 by bostic
e
u
U
t
T
I 1
/*-
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
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * el.refresh.h: Screen refresh functions
 */
#ifndef _h_el_refresh
#define _h_el_refresh

D 2
#include "editline.h"
E 2
I 2
#include "histedit.h"
E 2

typedef struct {
    coord_t 	 r_cursor;	/* Refresh cursor position	*/
    int r_oldcv, r_newcv;	/* Vertical locations		*/
} el_refresh_t;

protected void	re_putc 		__P((EditLine *, int));
protected void	re_clear_lines		__P((EditLine *));
protected void	re_clear_display	__P((EditLine *));
protected void	re_refresh		__P((EditLine *));
protected void	re_refresh_cursor	__P((EditLine *));
protected void	re_fastaddc		__P((EditLine *));
protected void	re_goto_bottom		__P((EditLine *));

#endif /* _h_el_refresh */
E 1
