h51688
s 00001/00002/00070
d D 1.2 83/04/18 15:43:19 slatteng 2 1
c DLS takeover
e
s 00072/00000/00000
d D 1.1 83/04/18 13:45:58 slatteng 1 0
c date and time created 83/04/18 13:45:58 by slatteng
e
u
U
t
T
I 1
D 2

/* point.c -
E 2
I 2
/* %W%	%G%
E 2
 *
 * Copyright -C- 1982 Barry S. Roitblat
 *
 *
 *      This file contains routines for manipulating the point data
 * structures for the gremlin picture editor.
 */

#include "gremlin.h"
#include "grem2.h"

/* imports from c */

extern char *malloc();

POINT *PTInit()
/*
 *      This routine creates a null point and returns  a pointer
 * to it.
 */

{
	POINT *pt;

	pt = (POINT *) malloc(sizeof(POINT));
	pt->x = nullpt;
	pt->y = nullpt;
	return(pt);
}  /* end PTInit */

POINT *PTMakePoint(x, y, pointlist)
float x, y;
POINT *(*pointlist);
/*
 *      This routine creates a new point with coordinates x and y and 
 * links it into the pointlist.
 */

{
	POINT *pt1;

	pt1 = *pointlist;
	while ( !Nullpoint(pt1) )
	{
		pt1 = pt1->nextpt;
	}  /* end while */;
	pt1->x = x;
	pt1->y = y;
	pt1->nextpt = PTInit();
        return(pt1);
}  /* end MakePoint */

PTDeletePoint(pt)
POINT *pt;
/*
 *      This routine removes the specified point from the pointlist and
 * returns it to free storage.  Deletion is done in place by copying the
 * next point over the one to be deleted and then removing the (previously)
 * next point.
 */

{
	POINT *tempt;

	tempt = PTNextPoint(pt);
	pt->x = tempt->x;
	pt->y = tempt->y;
	pt->nextpt = tempt->nextpt;
	free((char *) tempt);
}  /* end DeletePoint */
E 1
