h11438
s 00050/00000/00000
d D 1.1 84/10/08 15:29:20 ralph 1 0
c date and time created 84/10/08 15:29:20 by ralph
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/
/*
 * This file contains routines for manipulating the point data
 * structures for the gremlin picture editor.
 */

#include "gprint.h"

/* imports from C */

extern char *malloc();


/*
 * Return pointer to empty point list.
 */
POINT *
PTInit()
{
    return((POINT *) NULL);
}


/*
 * This routine creates a new point with coordinates x and y and 
 * links it into the pointlist.
 */
POINT *
PTMakePoint(x, y, pplist)
float x, y;
POINT **pplist;
{
    register POINT *point;

    if (Nullpoint(point = *pplist)) {	/* empty list */
	*pplist = (POINT *) malloc(sizeof(POINT));
	point = *pplist;
    }
    else {
	while (!Nullpoint(point->nextpt))
	    point = point->nextpt;
	point->nextpt = (POINT *) malloc(sizeof(POINT));
	point = point->nextpt;
    }

    point->x = x;
    point->y = y;
    point->nextpt = PTInit();
    return(point);
}  /* end PTMakePoint */
E 1
