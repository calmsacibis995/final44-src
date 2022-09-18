h10357
s 00002/00002/00077
d D 8.1 93/06/04 17:43:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00073
d D 5.2 91/04/22 15:49:37 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00071
d D 5.1 85/05/07 12:07:27 dist 2 1
c Add copyright notice
e
s 00072/00000/00000
d D 4.1 83/11/10 14:14:28 ralph 1 0
c date and time created 83/11/10 14:14:28 by ralph
e
u
U
t
T
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

#include "hp2648.h"

linemod( line )
char	*line;
{
	putchar('Z'); 
	handshake();
	putchar(ESC); 
	putchar(GRAPHIC);
	putchar(MODE);
	if ( *(line) == 's' ) {
		if ( *(++line) == 'o' ) {
			/*
			 * solid mode 1
			 */
			putchar( '1' );
			putchar( 'b' );
			goto done;
		}
		else if ( *(line) == 'h' ) {
			/*
			 * shortdashed mode 4
			 */
			putchar( '6' );
			putchar( 'b' );
			goto done;
		}
	}
	else if ( *(line) == 'd' ) {
		if ( *(++line) == 'o' && *(++line) == 't' ) {
			if ( *(++line) == 't' ) {
				/*
				 * dotted mode 2
				 */
				putchar( '7' );
				putchar( 'b' );
				goto done;
			}
			else if ( *(line) == 'd' ) {
				/*
				 * dotdashed mode 3
				 */
				putchar( '8' );
				putchar( 'b' );
				goto done;
			}
		}
	}
	else if ( *(line) == 'l' ) {
		/*
		 * longdashed mode 5
		 */
		putchar( '5' );
		putchar( 'b' );
		goto done;
	}
	putchar( '1' );				/* default to solid */
	putchar( 'b' );				/* default to solid */
done:
	putchar( 'Z' );
	handshake();
	putchar(ESC); 
	putchar(GRAPHIC);
	putchar(PLOT);
	putchar(BINARY);
	buffcount = 4;
	return;
}
E 1
