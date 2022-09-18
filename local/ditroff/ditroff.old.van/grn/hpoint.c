/*	hpoint.c	1.1	84/10/08	*/
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
