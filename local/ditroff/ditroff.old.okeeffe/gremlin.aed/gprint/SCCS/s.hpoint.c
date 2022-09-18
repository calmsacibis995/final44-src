h48906
s 00006/00006/00045
d D 1.4 83/07/09 15:59:35 slatteng 4 3
c just some tuning... register declarations, and stuff
e
s 00001/00003/00050
d D 1.3 83/03/30 13:37:59 ralph 3 2
c modified mapping and scale factors to fit in square arrays.
e
s 00000/00000/00053
d D 1.2 83/03/02 13:49:48 ralph 2 1
c this version uses remote line printer software.
e
s 00053/00000/00000
d D 1.1 83/03/02 13:29:26 ralph 1 0
c date and time created 83/03/02 13:29:26 by ralph
e
u
U
t
T
I 1
D 3

/* hpoint.c -
E 3
I 3
/*	%M%	%I%	%E%
E 3
 *
 * Copyright -C- 1982 Barry S. Roitblat
 *
 *      This file contains routines for manipulating the point data
 * structures for the hard copy programs of the gremlin picture editor.
 */

#include "gprint.h"
D 3
#include "grem2.h"
E 3

/* imports from c */

extern char *malloc();

POINT *PTInit()
/*
 *      This routine creates a null point and returns  a pointer
 * to it.
 */

{
D 4
	POINT *pt;
E 4
I 4
	register POINT *pt;
E 4

	pt = (POINT *) malloc(sizeof(POINT));
	pt->x = nullpt;
	pt->y = nullpt;
	return(pt);
}  /* end PTInit */

POINT *PTMakePoint(x, y, pointlist)
D 4
float x, y;
E 4
I 4
float x;
float y;
E 4
POINT *(*pointlist);
/*
 *      This routine creates a new point with coordinates x and y and 
 * links it into the pointlist.
 */

{
D 4
	POINT *pt1;
E 4
I 4
	register POINT *pt1;
E 4

	pt1 = *pointlist;
D 4
	while ( !Nullpoint(pt1) )
	{
E 4
I 4
	while ( !Nullpoint(pt1) ) {
E 4
		pt1 = pt1->nextpt;
D 4
	}  /* end while */;
E 4
I 4
	}
E 4
	pt1->x = x;
	pt1->y = y;
	pt1->nextpt = PTInit();
        return(pt1);
}  /* end MakePoint */

E 1
