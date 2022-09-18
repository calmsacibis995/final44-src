h09963
s 00004/00026/00184
d D 1.2 85/01/03 19:34:24 opcode 2 1
c 
e
s 00210/00000/00000
d D 1.1 84/10/21 15:03:02 opcode 1 0
c date and time created 84/10/21 15:03:02 by opcode
e
u
U
t
T
I 1
/*
 * %W%	%G%
 *
 * This file contains routines to implement the higher level display
 * driver routines for the SUN Gremlin picture editor.
 *
 * Mark Opperman (opcode@monet.BERKELEY)
 *
 */

#include <suntool/tool_hs.h>
#include "gremlin.h"

/* imports from graphics.c */

extern GRArc();
extern GRClear();
extern GRCurve();
extern GRCurrentSetOn();		/* force display of current set */
extern GRDisplayJustify();
extern GRNewElement(); 
extern GRPutText(); 
extern GRSetCurve(); 
extern GRSetLineStyle();
extern GRSetStippleStyle();
extern GRSetTextPos(); 
extern GRStippleFill(); 
extern GRVector();

extern curve_set;			/* true if spline pre-computed */

/* imports from main.c */

extern struct pixwin *pix_pw;
extern struct rect pix_size;
extern struct pixrect *cset_pr;
extern struct pixrect *scratch_pr;
extern ELT *cset;
extern SHOWPOINTS;
extern SUN_XORIGIN;
extern SUN_YORIGIN;

/* imports from long*.c */

extern LGShowPoints();

/* locals */

int minsunx, maxsunx, minsuny, maxsuny;


/*
 * This routine displays an arbitrary element type 
 * using the parameters stored with the element.  
 * Elements are drawn by Exclusive Oring the screen.
D 2
 * mro 7/13/84
E 2
 */
DISScreenAdd(element, mask)
register ELT *element;
int mask;
{
    register POINT *p0, *p1, *p2;
    POINT point;
    register x, y, width, height;

    if (DBNullelt(element))
	return;

    /* clear scratch_pr */
    pr_rop(scratch_pr, 0, 0, pix_size.r_width, pix_size.r_height,
						PIX_SRC, NULL, 0, 0);

D 2
    minsunx = minsuny = dbx_to_win(element->ptlist->x);
    maxsunx = maxsuny = dby_to_win(element->ptlist->y);
E 2
I 2
    /* determine bounds for this element */
    minsunx = maxsunx = dbx_to_win(element->ptlist->x);
    minsuny = maxsuny = dby_to_win(element->ptlist->y);
E 2

    if (TEXT(element->type)) {
	GRSetTextPos(element->textpt, element->type, element->brushf,
			element->size, element->ptlist, &point);
	GRPutText(element->textpt, element->brushf, element->size, 
			&point);
	if (mask & csetmask)	/* display justification marker */
	    GRDisplayJustify(element);
    }
    else {
	switch (element->type) {
	     case ARC:  
		p1 = element->ptlist;
		p2 = PTNextPoint(p1);
		/* angle is stored in size */
		GRArc(p1, p2, (float) element->size, element->brushf);
		break;
	    case CURVE:  
		if (!curve_set)
		    GRSetCurve(element->ptlist);
		GRCurve(element->brushf);
		curve_set = 0;
		break;
	    case POLYGON:
		if (element->brushf != 0) {	/* bordered polygon */
		    p0 = p1 = element->ptlist;
		    p2 = PTNextPoint(p1);
		    GRSetLineStyle(element->brushf);

		    while (!Nullpoint(p2)) {
			GRVector(p1->x, p1->y, p2->x, p2->y);
			p1 = p2;
			p2 = PTNextPoint(p2);
		    }

		    /* if last point not specified, join end points */
		    if ((p0->x != p1->x) || (p0->y != p1->y))
			    GRVector(p1->x, p1->y, p0->x, p0->y);
		}
		else {		/* unbordered: find min/max */
		    p0 = element->ptlist;

		    while (!Nullpoint(p0)) {
			MINMAX(minsunx, maxsunx, dbx_to_win(p0->x));
			MINMAX(minsuny, maxsuny, dby_to_win(p0->y));
			p0 = PTNextPoint(p0);
		    }
		}

		GRSetStippleStyle(element->size);
		GRStippleFill(element->ptlist);
		break;
	    case VECTOR:  
		p1 = element->ptlist;
		p2 = PTNextPoint(p1);
		GRSetLineStyle(element->brushf);

		while (!Nullpoint(p2)) {
		    GRVector(p1->x, p1->y, p2->x, p2->y);
		    p1 = p2;
		    p2 = PTNextPoint(p2);
		}
		break;
	}
    }

D 2
/*
printf("minsunx=%d maxsunx=%d minsuny=%d maxsuny=%d\n",
minsunx, maxsunx, minsuny, maxsuny);
*/

E 2
    x = minsunx - 8;
D 2
    width = maxsunx + 8 - x;
E 2
    y = minsuny - 8;
I 2
    width = maxsunx + 8 - x;
E 2
    height = maxsuny + 8 - y;
D 2
/*
printf("x=%d y=%d width=%d height=%d\n", x, y, width, height);
*/
E 2

    if (mask & pixmask)
	pw_write(pix_pw, x, y, width, height, PIX_SRC ^ PIX_DST, 
						    scratch_pr, x, y);
 
    if (mask & csetmask)
	pr_rop(cset_pr, x, y, width, height, PIX_SRC ^ PIX_DST, 
						    scratch_pr, x, y);
D 2

#ifdef oldway
    if (mask & pixmask)
	pw_write(pix_pw, 0, 0, pix_size.r_width, pix_size.r_height,
	    PIX_SRC ^ PIX_DST, scratch_pr, 0, 0);
 
    if (mask & csetmask)
	pr_rop(cset_pr, 0, 0, pix_size.r_width, pix_size.r_height,
	    PIX_SRC ^ PIX_DST, scratch_pr, 0, 0);
#endif
for (x=0;x<10000;x++);
E 2
}  /* end DISScreenAdd */


/*
 * This routine erases an arbitrary element type by redrawing the 
 * element with XOR.  This is the same as drawing the element.
D 2
 * mro 7/13/84
E 2
 */
DISScreenErase(element, mask)
register ELT *element;
register mask;
{
    DISScreenAdd(element, mask);
}  /* end ScreenErase */ 


/*
 * This routine clears the current set pixrect.
D 2
 * mro 7/31/84
E 2
 */
DISClearSetDisplay()
{
    register ELT *elist;

    GRCurrentSetOn();

    if (SHOWPOINTS)
	LGShowPoints();

    elist = cset;
    while (!DBNullelt(elist)) {
	if (TEXT(elist->type))		/* turn off text handle */
	    GRDisplayJustify(elist);
	elist = DBNextofSet(elist);
    }

    GRClear(csetmask);
}  /* end DISClearSetDisplay */
D 2

E 2
E 1
