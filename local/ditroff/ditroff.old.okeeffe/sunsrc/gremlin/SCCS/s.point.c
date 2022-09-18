h22166
s 00000/00060/00162
d D 1.2 85/01/03 19:38:55 opcode 2 1
c misc updates
e
s 00222/00000/00000
d D 1.1 84/10/21 15:03:59 opcode 1 0
c date and time created 84/10/21 15:03:59 by opcode
e
u
U
t
T
I 1
/*
 * %W%	%G%
 *
 * Routines for manipulating the point data structures of the
 * SUN Gremlin picture editor.
 *
 * Mark Opperman (opcode@monet.BERKELEY)
 *
 */

#include "gremlin.h"

/* imports from graphics.c */

extern GRFontStrlen();

/* imports from C */

extern char *malloc();


D 2
#ifdef oldway
E 2
/*
D 2
 * This routine creates a null point and returns a pointer to it.
 */
POINT *
PTInit()
{
    register POINT *pt;

    pt = (POINT *) malloc(sizeof(POINT));
    pt->x = nullpt;
    pt->y = nullpt;
    pt->nextpt = (POINT *) NULL;
    return(pt);
}  /* end PTInit */


/*
E 2
 * This routine creates a new point with coordinates x and y and 
 * links it into the pointlist.
 */
POINT *
D 2
PTMakePoint(x, y, plist)
float x, y;
register POINT *plist;
{
    while (!Nullpoint(plist))
	plist = plist->nextpt;

    plist->x = x;
    plist->y = y;
    plist->nextpt = PTInit();

    return(plist);
}  /* end PTMakePoint */
#endif


/*
 * This routine creates a new point with coordinates x and y and 
 * links it into the pointlist.
 */
POINT *
E 2
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


D 2
#ifdef oldway
E 2
/*
 * This routine removes the specified point from the pointlist and
 * returns it to free storage.  Deletion is done in place by copying the
 * next point over the one to be deleted and then removing the (previously)
 * next point.
D 2
 */
PTDeletePoint(pt)
register POINT *pt;
{
    register POINT *tempt;

    tempt = PTNextPoint(pt);
    pt->x = tempt->x;
    pt->y = tempt->y;
    pt->nextpt = tempt->nextpt;
    free((char *) tempt);
}  /* end PTDeletePoint */
#endif


/*
 * This routine removes the specified point from the pointlist and
 * returns it to free storage.  Deletion is done in place by copying the
 * next point over the one to be deleted and then removing the (previously)
 * next point.
E 2
 *
 * It is up to the caller to ensure that, if a list contains only one POINT,
 * any pointers to that list are set to NULL after this call.
 */
PTDeletePoint(pt, plist)
register POINT *pt;		/* the point to deleted */
register POINT **plist;		/* the address of the list from
				   which it is to be deleted */
{
    register POINT *tempt;

    if (Nullpoint(pt->nextpt)) {	/* last POINT in list */
	if (*plist == pt)		/* only POINT in list */
	    *plist = (POINT *) NULL;
	else {				/* search for previous point */
	    tempt = *plist;
	    while (tempt->nextpt != pt)
		tempt = tempt->nextpt;
	    tempt->nextpt = (POINT *) NULL;
	}
	free((char *) pt);
    }
    else {				/* copy over */
	tempt = PTNextPoint(pt);
	pt->x = tempt->x;
	pt->y = tempt->y;
	pt->nextpt = tempt->nextpt;
	free((char *) tempt);
    }
}  /* end PTDeletePoint */


/*
 * This routine makes the four positioning points required for text
 * elements: (1) the point layed down by the user, (2) the bottom left
 * corner of the text display, (3) the midpoint of the bottom edge of 
 * the text display, and (4) the bottom right corner of the text display.
 * A pointer to this list is returned.
D 2
 * mro 8/20/84
E 2
 */
POINT *
PTMakeTextPoints(text, font, size, point, pos)
char *text;
int font, size;
register POINT *point;	/* point layed down by user */
register POINT *pos;	/* bottom left corner of text display */
{
    register length;
    POINT *pt;

    length = GRFontStrlen(text, font, size);

    pt = PTInit();
    (void) PTMakePoint(point->x, point->y, &pt);	    /* user's point */
    (void) PTMakePoint(pos->x, pos->y, &pt);		    /* bottom left */
    (void) PTMakePoint(pos->x + (length / 2), pos->y, &pt); /* bottom midpt */
    (void) PTMakePoint(pos->x + length, pos->y, &pt);	    /* bottom right */

    return(pt);
}


/*
 *  Change the text points to reflect the current justification,
 *  font and size of a text element.
 */
PTModifyTextPoints(elt)
register ELT *elt;
{
    register length;
    register POINT *pos, *point;

    length = GRFontStrlen(elt->textpt, elt->brushf, elt->size);
    pos = PTNextPoint(elt->ptlist);		/* bottom left */

    GRSetTextPos(elt->textpt, elt->type, elt->brushf, elt->size, 
							elt->ptlist, pos);

    point = PTNextPoint(pos);			/* bottom midpoint */
    point->x = pos->x + (length / 2);
    point->y = pos->y;
    point = PTNextPoint(point);			/* bottom right */
    point->x = pos->x + length;
    point->y = pos->y;
}


/*
 *  Return number of POINTs in an element.
 */
PTListLength(elt)
register ELT *elt;
{
    register POINT *point;
    register length = 1;

    if (Nullpoint(point = elt->ptlist)) {
	printf("PTListLength: empty point list\n");
	return(0);
    }

    while (!Nullpoint(point->nextpt)) {
	length++;
	point = point->nextpt;
    }

    return(length);
}
E 1
