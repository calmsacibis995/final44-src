h37589
s 00002/00002/00079
d D 8.1 93/06/04 17:20:14 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00072
d D 5.3 91/04/22 14:54:49 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00073
d D 5.2 88/07/22 16:32:40 bostic 4 2
c ANSIfication
e
s 00009/00002/00072
d R 5.2 85/04/30 16:06:12 dist 3 2
c add copyright
e
s 00001/00001/00073
d D 5.1 85/04/30 15:48:08 dist 2 1
c add copyright
e
s 00074/00000/00000
d D 4.1 83/11/11 15:12:39 ralph 1 0
c date and time created 83/11/11 15:12:39 by ralph
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 5
static char sccsid[] = "@(#)open.c	4.1 (Berkeley) 11/11/83";
E 2
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

/*
 * Displays plot files on a AED512 graphics terminal.
 */

#include "aed.h"

char dbuf[BUFSIZ];	/* Used to buffer display characters */
struct sgttyb sgttyb;	/* Used to save terminal control bits */
D 4
curx, cury;		/* Current screen position */
E 4
I 4
int curx, cury;		/* Current screen position */
E 4
int xbot, ybot;		/* Coordinates of screen lower-left corner */
int scale;		/* The number of pixels per 2**12 units
			 * of world coordinates.
			 */

/*
 * The following is the color map, containing reg, green, and blue
 * values for color locations 0 and 1.
 */

static int colors[] = {200, 200, 200, 0, 0, 125, 125, 0, 0, 125, 0, 0};

/*---------------------------------------------------------
 *	Openpl initializes the graphics display and clears its screen.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *	The display is re-initialized and the file is remembered for
 *	use in all subsequent calls to this module.  The display's
 *	color map is reset.  The display is put into raw mode, but
 *	the previous mode bits are saved.
 *
 *	Errors:		None.
 *---------------------------------------------------------
 */
openpl()
{
    int flags, *p, i;
    char dum[4];

    /* First, grab up the display modes, then reset them to put it
     * into cooked mode.  Also, lock the terminal.
     */

    (void) gtty(fileno(stdout), &sgttyb);
    flags = sgttyb.sg_flags;
    sgttyb.sg_flags = (sgttyb.sg_flags & ~(RAW | CBREAK)) | EVENP | ODDP;
    (void) stty(fileno(stdout), &sgttyb);
    sgttyb.sg_flags = flags;

    /* Save the file pointer around for later use, then output an
     * initialization string to the display.  The initialization
     * string resets the terminal, sets formats, clears the display,
     * initializes the read and write masks, and sets the color map.
     */

    setbuf(stdout, dbuf);
    fputs("\33\33G1HHHN[00LFFCFFMFFFFFFFF", stdout);
    fputs("K0004", stdout);
    p = colors;
    for (i=0; i<12; i++)
    {
	chex(*p++, dum, 2);
	fputs(dum, stdout);
    }
    fputs("^15060AL", stdout);
    scale = 1<<12;
    curx = cury = xbot = ybot = 0;
    (void) fflush(stdout);
}
E 1
