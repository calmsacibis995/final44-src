h34639
s 00007/00012/00354
d D 1.15 86/04/14 10:20:41 slatteng 16 14
c took out stipple map as default and made it an option
e
s 00007/00011/00355
d R 1.15 86/04/14 09:59:53 slatteng 15 14
c took stipple map out as default and made it an option
e
s 00007/00003/00359
d D 1.14 84/11/27 20:50:38 opcode 14 13
c stipple fonts 1 - 8 are mapped through stipple_index[] 
c stipple fonts > 8 are not mapped
e
s 00019/00004/00343
d D 1.13 84/10/08 15:42:07 ralph 13 12
c update for format of new SUN gremlin files.
e
s 00033/00004/00314
d D 1.12 84/05/25 15:22:59 slatteng 12 11
c added polygon handling
e
s 00002/00002/00316
d D 1.11 83/12/08 17:29:52 slatteng 11 10
c fix core dumping if no points exist in an element
e
s 00003/00004/00315
d D 1.10 83/11/02 12:58:09 slatteng 10 9
c removing command-line options affected type of tsize[]
e
s 00014/00007/00305
d D 1.9 83/10/13 11:55:56 slatteng 9 8
c comment fixing and setbrush routine done smarter
e
s 00001/00001/00311
d D 1.8 83/10/12 20:38:03 slatteng 8 7
c cut down the size of an output line allowed
e
s 00013/00005/00299
d D 1.7 83/10/12 18:16:07 slatteng 7 6
c fix \w'(string)' error to use ^G, and fix \\ to put \\\
c 
e
s 00015/00014/00289
d D 1.6 83/10/07 22:03:42 slatteng 6 5
c fix .sp bug for eqn and other vertical motions.
e
s 00011/00002/00292
d D 1.5 83/09/19 15:28:00 slatteng 5 4
c fixed text bug: eqn puts extra space on some lines.
e
s 00007/00009/00287
d D 1.4 83/08/23 13:25:49 slatteng 4 3
c fixed text handling procedures - changed to strings, not diversions
e
s 00014/00014/00282
d D 1.3 83/08/03 09:38:42 slatteng 3 2
c fixed text motion commands and prettied up comments.
e
s 00096/00069/00200
d D 1.2 83/07/24 12:09:38 slatteng 2 1
c added text processing function HGPutText and setfont, too.
e
s 00269/00000/00000
d D 1.1 83/07/21 15:31:50 slatteng 1 0
c date and time created 83/07/21 15:31:50 by slatteng
e
u
U
t
T
I 1
/*	%M%	%I%	(Berkeley) %E%
 *
 *     This file contains the graphics routines for converting gremlin
 * pictures to troff input.
 */

#include "gprint.h"

D 2
#define MAXVECT 50
E 2

D 2
/* line and character styles */
E 2
I 2
D 8
#define  MAXVECT	50
E 8
I 8
#define  MAXVECT	40
E 8
#define  pi		3.14159265358979324
#define  twopi		(2.0 * pi)
#define  len(a, b)	sqrt((b.x-a.x) * (b.x-a.x) + (b.y-a.y) * (b.y-a.y))
E 2

D 2
extern int style[];
E 2
I 2

extern int style[];	/* line and character styles */
E 2
extern int thick[];
extern char *tfont[];
D 10
extern char *tsize[];
E 10
I 10
extern int tsize[];
I 12
D 13
extern char *stipple;
E 13
I 13
extern int stipple_index[];	/* stipple font index for stipples 1 - 8 */
extern char *stipple;		/* stipple type (cf or ug) */
I 16
extern int oldstipmap;		/* use old-style stipple mapping */
E 16
E 13
E 12
E 10


D 2
/* variables used to print from font file */

extern cfont;
extern csize;
extern char *devdir ;

/* imports from main.c */

extern double scale;
E 2
I 2
D 10
extern double scale;		/* imports from main.c */
E 2
extern double troffscale;
E 10
I 10
extern double troffscale;	/* imports from main.c */
E 10
extern point();
extern int linethickness;
extern int linmod;
extern int lastx;
extern int lasty;
extern int lastyline;
D 2

E 2
extern int ytop;
extern int ybottom;
extern int xleft;
extern int xright;


/*----------------------------------------------------------------------------*
D 12
 | Routine:	HGPrintElt (element_pointer)
E 12
I 12
 | Routine:	HGPrintElt (element_pointer, baseline)
E 12
 |
 | Results:	examines a picture element and calls the appropriate
 |		routine(s) to print them according to their type.
 |		After the picture is drawn, current position is (lastx, lasty).
 *----------------------------------------------------------------------------*/

D 12
HGPrintElt(element)
E 12
I 12
HGPrintElt(element, baseline)
E 12
ELT *element;
I 12
int baseline;
E 12
{
    register POINT *p1;
    register POINT *p2;
    register int length;
I 12
    static int didstipple = 1;	/* flag to prevent multipe messages about no */
				/* stipple font requested from being printed */
I 13
    float firstx, firsty;	/* for completing polygons */
E 13
E 12

D 11
    if ( !DBNullelt(element) ) {
I 2
	p1 = element->ptlist;		/* p1 always has first point */
E 11
I 11
    if ( !DBNullelt(element) && !Nullpoint((p1 = element->ptlist))) {
						/* p1 always has first point */
E 11
E 2
        if (TEXT(element->type)) {
            HGSetFont(element->brushf, element->size);
D 2
            HGPutText(element->type, *(element->ptlist), element->textpt);
E 2
I 2
            HGPutText(element->type, *p1, element->textpt);
E 2
        } else {
D 2
	    tmove(p1 = element->ptlist);	/* always move to start first */
	    HGSetBrush(element->brushf);	/* p1 always has first point */
E 2
I 2
D 12
	    HGSetBrush(element->brushf);	/* graphics need brush set */
E 12
I 12
	    if (element->brushf) {		/* if there is a brush, the */
		HGSetBrush(element->brushf);	/* graphics need it set */
	    }
E 12
E 2
            switch (element->type) {

                 case ARC:  p2 = PTNextPoint(p1);
D 2
			    printf("\\D'a");

				/* stuff... */
				printf(" 0 0 0 0'");

E 2
I 2
			    doarc(*p1, *p2, element->size);
E 2
                            break;

D 2
               case CURVE:  printf("\\D'g");
E 2
I 2
               case CURVE:  tmove(p1);
			    printf("\\D'g");
E 2
                            while (!Nullpoint((p1 = PTNextPoint(p1)))) {
                                dx((double) p1->x);
                                dy((double) p1->y);
                            }  /* end while */;
			    putchar('\'');
I 6
			    cr();
E 6
                            break;

D 12
              case VECTOR:  length = 1;		/* keep track of line length */
E 12
I 12
	      case VECTOR:  length = 1;		/* keep track of line length */
E 12
D 2
					   /* so single lines don't get long */
E 2
I 2
			    tmove(p1);	   /* so single lines don't get long */
E 2
                            while (!Nullpoint((p1 = PTNextPoint(p1)))) {
				printf("\\D'l");
                                dx((double) p1->x);
                                dy((double) p1->y);
				putchar('\'');
				if (length++ > MAXVECT) {
I 6
				    cr();
E 6
				    tmove (p1);
				    length = 1;
				}
D 2
                            }  /* end while */;
E 2
I 2
                            }  /* end while */
I 12
			    cr();
                            break;

	     case POLYGON:  tmove(p1);
			    if (stipple) {
				didstipple = 1;
D 16
				if (element->brushf) {
D 13
				    printf("\\D'p %d", element->size);
E 13
I 13
D 14
				    printf("\\D'p %d",
					    stipple_index[element->size - 1]);
E 14
I 14
				    printf("\\D'p %d", 
					    element->size <= NSTIPPLES ?
					    stipple_index[element->size - 1] :
					    element->size);
E 14
E 13
				} else {
D 13
				    printf("\\D'P %d", element->size);
E 13
I 13
				    printf("\\D'P %d",
D 14
					    stipple_index[element->size - 1]);
E 14
I 14
					    element->size <= NSTIPPLES ?
					    stipple_index[element->size - 1] :
					    element->size);
E 14
E 13
				}
E 16
I 16
				printf(element->brushf ? "\\D'p %d":"\\D'P %d",
					(element->size > NSTIPPLES ||
					oldstipmap == FALSE) ? element->size :
					stipple_index[element->size - 1]);
E 16
			    } else {
				if (didstipple) {
D 16
				    error("no stipple font requested for picture at line %d", baseline);
E 16
I 16
				    error("no stipple for picture at line %d",
						baseline);
E 16
				    didstipple = 0;
				}
				printf("\\D'p 0");
			    }
D 13
                            while (!Nullpoint((p1 = PTNextPoint(p1)))) {
E 13
I 13

			    firstx = p1->x;
			    firsty = p1->y;
                            while (!Nullpoint((PTNextPoint(p1)))) {
				p1 = PTNextPoint(p1);
E 13
                                dx((double) p1->x);
                                dy((double) p1->y);
                            }  /* end while */;
I 13

			    /* close polygon if not done so by user */
			    if ((firstx != p1->x) || (firsty != p1->y)) {
				dx((double) firstx);
				dy((double) firsty);
			    }

E 13
			    putchar('\'');
E 12
I 6
			    cr();
E 6
E 2
                            break;
D 2
            }  /* end switch */;
E 2
I 2
            }  /* end switch */
E 2
        }  /* end else Text */
    }  /* end if */
}  /* end PrintElt */


/*----------------------------------------------------------------------------*
 | Routine:	HGPutText (justification, position_point, string)
 |
D 2
 | Results:	
 |
 | Side Efct:	
 |
 | Bugs:	
E 2
I 2
 | Results:	given the justification, a point to position with, and a
 |		string to put, HGPutText first sends the string into a
 |		diversion, moves to the positioning point, then outputs local
 |		vertical and horizontal motions as needed to justify the text.
 |		After all motions are done, the diversion is printed out.
E 2
 *----------------------------------------------------------------------------*/

HGPutText(justify,pnt,string)
int justify;
POINT pnt;
D 7
char string[];
E 7
I 7
register char *string;
E 7
D 2

/* This routine is used to calculate the proper starting position for a
 * text string (based on justification, size and font), and prints it 
 * character by character.
 */

E 2
{
I 5
    int savelasty = lasty;		/* vertical motion for text is to be */
					/*   ignored.  save current y here */

D 6
    printf(".nr g8 \\n(.d\n", string);	/* save current vertical position. */
E 5
I 2
D 4
    printf(".di gt\n\\&%s\n.di", string);	/* divert the text. */
    tmove(&pnt);				/* move to positioning point */
E 4
I 4
    printf(".ds g9 \"%s", string);	/* define string containing the text. */
E 6
I 6
    printf(".nr g8 \\n(.d\n");		/* save current vertical position. */
D 7
    printf(".ds g9 \"%s\n", string);	/* define string containing the text. */
E 7
I 7
    printf(".ds g9 \"");		/* define string containing the text. */
    while (*string) {					/* put out the string */
	if (*string == '\\' && *(string+1) == '\\') {	/* one character at a */
	    printf("\\\\\\");				/* time replacing //  */
	    string++;					/* by //// to prevent */
	}						/* interpretation at  */
	printf("%c", *(string++));			/* printout time */
    }
    printf("\n");
E 7
E 6
    tmove(&pnt);			/* move to positioning point */
E 4
E 2
    switch (justify) {
I 2
					/* local vertical motions */
I 5
					/* (the numbers here are used to be */
					/* somewhat compatible with gprint) */
E 5
        case CENTLEFT:
        case CENTCENT:
D 3
       case CENTRIGHT:	printf("\\v'\\n(dnu/2u'");	/* down half */
E 3
I 3
D 4
       case CENTRIGHT:	printf("\\v'(\\n(dnu+1m)/2u'");	/* down half */
E 4
I 4
       case CENTRIGHT:	printf("\\v'0.85n'");		/* down half */
E 4
E 3
			break;
E 2

D 2
	case BOTLEFT:
E 2
I 2
	 case TOPLEFT:
	 case TOPCENT:
D 3
        case TOPRIGHT:	printf("\\v'\\n(dnu'");		/* down whole */
E 3
I 3
D 4
        case TOPRIGHT:	printf("\\v'\\n(dnu+1m'");		/* down whole */
E 4
I 4
        case TOPRIGHT:	printf("\\v'1.7n'");		/* down whole */
E 4
E 3
    }

    switch (justify) {
					/* local horizontal motions */
	 case BOTCENT:
        case CENTCENT:
D 4
	 case TOPCENT:	printf("\\h'-\\n(dlu/2u'");	/* back half */
E 4
I 4
D 7
	 case TOPCENT:	printf("\\h'-\\w'\\*(g9'u/2u'");	/* back half */
E 7
I 7
	 case TOPCENT:	printf("\\h-\\w\\*(g9u/2u");	/* back half */
E 7
E 4
E 2
			break;
D 2
	case BOTCENT:
			break;
       case BOTRIGHT:
			break;
       case CENTLEFT:
			break;
       case CENTCENT:
			break;
      case CENTRIGHT:
			break;
	case TOPLEFT:
			break;
	case TOPCENT:
			break;
       case TOPRIGHT:
			break;
E 2
I 2

        case BOTRIGHT:
       case CENTRIGHT:
D 4
        case TOPRIGHT:	printf("\\h'-\\n(dlu'");	/* back whole */
E 4
I 4
D 7
        case TOPRIGHT:	printf("\\h'-\\w'\\*(g9'u'");		/* back whole */
E 7
I 7
        case TOPRIGHT:	printf("\\h-\\w\\*(g9u");	/* back whole */
E 7
E 4
E 2
    }
I 6

E 6
D 2
    HGplotch(string);
} /* end HGPutText */;
E 2
I 2
D 4
				/* now print the text.  The (cr) at the end */
    printf("\\c\n.gt\n");	/* results in a blank line in the output.  It */
				/* is necessary to break the "\c" directive. */
E 4
I 4
D 5
    printf("\\*(g9");			/* now print the text. */
E 5
I 5
D 7
    printf("\\*(g9\n");			/* now print the text. */
E 7
I 7
    printf("\\&\\*(g9\n");	/* now print the text. */
E 7
D 6
    printf(".sp |\\n(g8u");		/* restore vertical position */
    lasty = savelasty;		/* vertical position is restored to */
				/*   what it was before text was printed */
E 6
I 6
    printf(".sp |\\n(g8u\n");	/* restore vertical position */
    lasty = savelasty;		/* vertical position restored to where it was */
    lastx = xleft;		/*   before text, also horizontal is at left */
E 6
E 5
E 4
} /* end HGPutText */
E 2


I 2
/*----------------------------------------------------------------------------*
 | Routine:	doarc (center_point, start_point, angle)
 |
 | Results:	produces either drawarc command or a drawcircle command
 |		depending on the angle needed to draw through.
 *----------------------------------------------------------------------------*/
E 2

I 2
doarc (cp, sp, angle)
POINT cp;
POINT sp;
int angle;
{
	double radius = len(cp, sp);
	double radians;


	if (angle) {		/* arc with angle */
	    tmove (&sp);		/* starting point first */
	    printf("\\D'a");
	    dx((double) cp.x);		/* move to center */
	    dy((double) cp.y);

	    radians = acos((sp.x - cp.x) / radius);	  /* angle of ending */
	    if (cp.y - sp.y < 0.0)			 /* point calculated */
		radians = twopi - radians;		 /* from start point */
	    radians += ((double) angle) * (pi / 180.0);	  /* and arc's angle */
	    if (radians > twopi) radians -= twopi;

	    dx(cp.x + cos(radians) * radius);	/* move to ending point */
	    dy(cp.y - sin(radians) * radius);

	} else {		/* a full circle (angle == 0) */
	    cp.x -= radius;
	    tmove(&cp);			/* move to the left point first */
					/* draw circle with given diameter */
	    printf("\\D'c %du", (int) ((radius + radius) * troffscale));
	}
	putchar('\'');		/* finish the command */
I 6
	cr();
E 6
}


/*----------------------------------------------------------------------------*
 | Routine:	HGSetFont (font_number, Point_size)
 |
 | Results:	ALWAYS outputs a .ft and .ps directive to troff.  This is
 |		done because someone may change stuff inside a text string.
 *----------------------------------------------------------------------------*/

E 2
HGSetFont(font, size)
int font, size;
{
D 2
    int i;
    char c, string[100];

    if (font != cfont) cfont = font;
    if (size != csize) csize = size;
    /* and whatever... */
E 2
I 2
D 6
    cr();
E 6
D 10
    printf(".ft %s\n.ps %s\n", tfont[font-1], tsize[size-1]);
E 10
I 10
    printf(".ft %s\n.ps %d\n", tfont[font-1], tsize[size-1]);
E 10
E 2
}


/*----------------------------------------------------------------------------*
 | Routine:	HGSetBrush (line_mode)
 |
 | Results:	generates the troff commands to set up the line width and
 |		style of subsequent lines.  Does nothing if no change is needed.
 |
 | Side Efct:	sets "linmode" and "linethicknes"
 *----------------------------------------------------------------------------*/

HGSetBrush(mode)
int mode;
{
D 6
    if (linmod != style[--mode]) {
I 3
	cr();
E 6
I 6
D 9
    if (linmod != style[--mode] || linethickness != thick[mode]) {
E 6
E 3
	printf ("\\D's %du'",linmod = style[mode]);
E 9
I 9
    register int printed = 0;

    if (linmod != style[--mode]) {
	printf ("\\D's %du'", linmod = style[mode]);
	printed = 1;
    }
    if (linethickness != thick[mode]) {
E 9
D 6
    }
    if (linethickness != thick[mode]) {
I 3
	cr();
E 6
E 3
	printf ("\\D't %du'", linethickness = thick[mode]);
I 6
D 9
	cr();
E 9
I 9
	printed = 1;
E 9
E 6
    }
I 9
    if (printed)
	cr();
E 9
}


D 2
HGplotch(string)
char *string;
{
}


E 2
/*----------------------------------------------------------------------------*
 | Routine:	dx (x_destination)
 |
 | Results:	scales and outputs a number for delta x (with a leading space)
 |		given "lastx" and x_destination.
 |
 | Side Efct:	resets "lastx" to x_destination.
 *----------------------------------------------------------------------------*/

dx(x)
double x;
{
    register int ix = (int) (x * troffscale);

    printf(" %du", ix - lastx);
    lastx = ix;
}


/*----------------------------------------------------------------------------*
 | Routine:	dy (y_destination)
 |
 | Results:	scales and outputs a number for delta y (with a leading space)
 |		given "lastyline" and y_destination.
 |
 | Side Efct:	resets "lastyline" to y_destination.  Since "line" vertical
 |		motions don't affect "page" ones, "lasty" isn't updated.
 *----------------------------------------------------------------------------*/

dy(y)
double y;
{
    register int iy = (int) (y * troffscale);

    printf(" %du", iy - lastyline);
    lastyline = iy;
}


/*----------------------------------------------------------------------------*
 | Routine:	tmove (point_pointer)
 |
D 3
 | Results:	produces horizontal and vertical moves for troff given
 |		the point pointer.
 |
 | Bugs:	Notice that this is identical to "dx" and "dy" in value
 |		output.  This is because troff does NOT understand spaces
 |		in \h or \v commands (!)
E 3
I 3
 | Results:	produces horizontal and vertical moves for troff given the
D 6
 |		pointer of a point to move to.
E 6
I 6
D 9
 |		pointer of a point to move to.  Adds -1v to the movement to
 |		counteract the vertical space generated by input "lines"
E 9
I 9
 |		pointer of a point to move to and knowing the current position.
 |		Also puts out a horizontal move to start the line.
E 9
E 6
E 3
 *----------------------------------------------------------------------------*/

tmove(ptr)
POINT *ptr;
{
    register int ix = (int) (ptr->x * troffscale);
    register int iy = (int) (ptr->y * troffscale);
I 3
    register int dx;
    register int dy;
E 3

D 6
    cr();
E 6
D 3
    if (iy - lasty) {
	printf(".sp %du\n", iy - lasty);
E 3
I 3
    if (dy = iy - lasty) {
	printf(".sp %du\n", dy);
E 3
    }
D 5
    lastyline = lasty = iy;
E 5
I 5
    lastyline = lasty = iy;		/* lasty is always set to current */
E 5
D 3
    if (ix - lastx) {
	printf("\\h'%du'", ix - lastx);
E 3
I 3
    if (dx = ix - lastx) {
	printf("\\h'%du'", dx);
E 3
	lastx = ix;
    }
}


/*----------------------------------------------------------------------------*
D 3
 | Routine:	cr
E 3
I 3
 | Routine:	cr ( )
E 3
 |
D 9
 | Results:	breaks the output line up to not overrun troff with lines that
D 2
 |		are too long.  Outputs a ".sp -1" also to keep the vertical
 |		spacing correct.
E 2
I 2
 |		are too long.
E 9
I 9
 | Results:	Ends off an input line.  ".sp -1" is also added to counteract
 |		the vertical move done at the end of text lines.
E 9
E 2
 |
D 3
 | Side Efct:	sets "lastx" to "leftpoint" for troff's return to left margin
E 3
I 3
 | Side Efct:	sets "lastx" to "xleft" for troff's return to left margin
E 3
 *----------------------------------------------------------------------------*/

cr()
{
D 6
    putchar('\n');
E 6
I 6
    printf("\n.sp -1\n");
E 6
    lastx = xleft;
}
E 1
