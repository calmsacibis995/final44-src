h31633
s 00002/00002/00087
d D 8.1 93/06/06 14:46:34 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00001/00083
d D 5.6 92/02/19 14:17:30 mckusick 9 8
c nllookup failures are acceptable
e
s 00001/00001/00083
d D 5.5 91/02/06 22:52:50 torek 8 7
c fprintf takes a FILE pointer too
e
s 00001/00011/00083
d D 5.4 90/06/01 16:04:13 bostic 7 6
c new copyright notice
e
s 00010/00005/00084
d D 5.3 88/06/29 19:23:17 bostic 6 5
c install approved copyright notice
e
s 00009/00003/00080
d D 5.2 88/05/05 17:50:17 bostic 5 4
c add Berkeley specific header; written by K. McKusick and P. Kessler
e
s 00008/00002/00075
d D 5.1 85/06/04 13:29:15 dist 4 3
c Add copyright
e
s 00003/00003/00074
d D 1.3 81/11/02 14:32:28 peter 3 2
c gather and use static call graph from a.out file.
e
s 00001/00001/00076
d D 1.2 81/10/20 15:49:19 peter 2 1
c name change to confuse to innocent/
e
s 00077/00000/00000
d D 1.1 81/10/15 13:47:05 peter 1 0
c date and time created 81/10/15 13:47:05 by peter
e
u
U
t
T
I 4
/*
D 10
 * Copyright (c) 1983 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */

E 4
I 1
#ifndef lint
D 4
    static	char *sccsid = "%W% (Berkeley) %G%";
#endif lint
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 4

D 2
#include "dprof.h"
E 2
I 2
#include "gprof.h"
E 2

    /*
     *	look up an address in a sorted-by-address namelist
     *	    this deals with misses by mapping them to the next lower 
     *	    entry point.
     */
nltype *
nllookup( address )
    unsigned long	address;
{
    register long	low;
    register long	middle;
    register long	high;
#   ifdef DEBUG
	register int	probes;

	probes = 0;
#   endif DEBUG
    for ( low = 0 , high = nname - 1 ; low != high ; ) {
#	ifdef DEBUG
	    probes += 1;
#	endif DEBUG
	middle = ( high + low ) >> 1;
	if ( nl[ middle ].value <= address && nl[ middle+1 ].value > address ) {
#	    ifdef DEBUG
D 3
		if ( debug & TALLYDEBUG ) {
E 3
I 3
		if ( debug & LOOKUPDEBUG ) {
E 3
		    printf( "[nllookup] %d (%d) probes\n" , probes , nname-1 );
		}
#	    endif DEBUG
	    return &nl[ middle ];
	}
	if ( nl[ middle ].value > address ) {
	    high = middle;
	} else {
	    low = middle + 1;
	}
    }
D 9
    fprintf( stderr , "[nllookup] binary search fails???\n" );
E 9
I 9
#   ifdef DEBUG
	if ( debug & LOOKUPDEBUG ) {
	    fprintf( stderr , "[nllookup] (%d) binary search fails\n" ,
		nname-1 );
	}
#   endif DEBUG
E 9
    return 0;
}

arctype *
arclookup( parentp , childp )
    nltype	*parentp;
    nltype	*childp;
{
    arctype	*arcp;

    if ( parentp == 0 || childp == 0 ) {
D 8
	fprintf( "[arclookup] parentp == 0 || childp == 0\n" );
E 8
I 8
	fprintf( stderr, "[arclookup] parentp == 0 || childp == 0\n" );
E 8
	return 0;
    }
#   ifdef DEBUG
D 3
	if ( debug & TALLYDEBUG ) {
E 3
I 3
	if ( debug & LOOKUPDEBUG ) {
E 3
	    printf( "[arclookup] parent %s child %s\n" ,
		    parentp -> name , childp -> name );
	}
#   endif DEBUG
    for ( arcp = parentp -> children ; arcp ; arcp = arcp -> arc_childlist ) {
#	ifdef DEBUG
D 3
	    if ( debug & TALLYDEBUG ) {
E 3
I 3
	    if ( debug & LOOKUPDEBUG ) {
E 3
		printf( "[arclookup]\t arc_parent %s arc_child %s\n" ,
			arcp -> arc_parentp -> name ,
			arcp -> arc_childp -> name );
	    }
#	endif DEBUG
	if ( arcp -> arc_childp == childp ) {
	    return arcp;
	}
    }
    return 0;
}
E 1
