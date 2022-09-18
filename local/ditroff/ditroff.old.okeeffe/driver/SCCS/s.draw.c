h37579
s 00001/00001/00805
d D 1.11 86/01/12 16:19:58 slatteng 12 11
c fixed minor typo in ellipse drawing
e
s 00061/00060/00745
d D 1.10 85/12/16 12:17:52 slatteng 11 9
c Fix/Clean up ellipse and spline generation
e
s 00060/00060/00745
d R 1.10 85/12/16 11:58:31 slatteng 10 9
c Fix/Clean up ellipse and spline generation
e
s 00012/00007/00793
d D 1.9 84/11/27 13:19:03 slatteng 9 8
c added line-style to polygons
e
s 00005/00002/00795
d D 1.8 84/05/09 17:00:36 slatteng 8 7
c add unbordered polygons
e
s 00082/00064/00715
d D 1.7 84/04/13 15:05:48 slatteng 7 6
c redo ellipse drawing and put in polygon rendering.
e
s 00003/00001/00776
d D 1.6 84/03/15 13:52:20 slatteng 6 5
c put in checks for EOF on input
e
s 00059/00050/00718
d D 1.5 84/02/09 23:14:53 slatteng 5 4
c fix bug of too long draw-paths to imagen
e
s 00040/00027/00728
d D 1.4 83/11/30 14:51:45 slatteng 4 3
c use "output" variable from main program, change ellipse routines
c from forcing even horizontal axis, change style production slightly
e
s 00107/00008/00648
d D 1.3 83/11/01 11:57:42 slatteng 3 2
c add line drawing of dotted and/or dashed lines (from gprint).
e
s 00000/00000/00656
d D 1.2 83/09/14 11:13:41 slatteng 2 1
c first pass - no line style yet.  Based on graph.c
e
s 00656/00000/00000
d D 1.1 83/09/07 13:28:48 slatteng 1 0
c date and time created 83/09/07 13:28:48 by slatteng
e
u
U
t
T
I 1
/*	%M%	%I%	%E%
 *
 *	This file contains the functions for producing the graphics
D 3
 *   images in the varian/versatec drivers for ditroff.
E 3
I 3
 *   images in the canon/imagen driver for ditroff.
E 3
 */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "canon.h"

D 5

#define TRUE	1
#define FALSE	0
E 5
				/* imports from dip.c */
I 6
#define  FATAL		1
E 6
#define  hmot(n)	hpos += n;
#define  hgoto(n)	hpos = n;
#define  vmot(n)	vpos += n;
#define  vgoto(n)	vpos = n;

I 4
extern int output;
E 4
extern int hpos;
extern int vpos;
extern int MAXX;
extern int MAXY;
extern FILE *tf;
extern putint();

#define word(x)	putint(x,tf)
#define byte(x)	putc(x,tf)
#define MAXPOINTS 200	/* number of points legal for a curve */

#define SOLID -1	/* line styles:  these are used as bit masks to */
#define DOTTED 004	/* create the right style lines. */
#define DASHED 020
#define DOTDASHED 024
#define LONGDASHED 074
				/* constants... */
#define  pi		3.14159265358979324
D 5
#define  log2_10	3.3219280948873623
E 5

#define START	1
#define POINT	0
D 3
#define xbound(x)	(x < 0 ? 0 : x > MAXX ? MAXX : x)
#define ybound(y)	(y < 0 ? 0 : y > MAXY ? MAXY : y)
E 3
I 3
/* the imagen complains if a path is drawn at < 1, or > limit, so truncate. */
D 5
#define xbound(x)	(x < 1 ? 1 : x > MAXX ? MAXX : x)
#define ybound(y)	(y < 1 ? 1 : y > MAXY ? MAXY : y)
E 5
I 5
#define xbound(x)	((x) < 1 ? 1 : (x) > MAXX ? MAXX : (x))
#define ybound(y)	((y) < 1 ? 1 : (y) > MAXY ? MAXY : (y))
E 5
E 3


int	linethickness = -1;	/* number of pixels wide to make lines */
int	linmod = SOLID;		/* type of line (SOLID, DOTTED, DASHED...) */
I 8
int	polyborder = 1;		/* flag for whether or not to draw a border */
E 8



/*----------------------------------------------------------------------------
 | Routine:	drawline (horizontal_motion, vertical_motion)
 |
 | Results:	Draws a line of "linethickness" width and "linmod" style
 |		from current (hpos, vpos) to (hpos + dh, vpos + dv).
 |
 | Side Efct:	Resulting position is at end of line (hpos + dh, vpos + dv)
 *----------------------------------------------------------------------------*/

drawline(dh, dv)
register int dh;
register int dv;
{
D 4
    HGtline (hpos, vpos, hpos + dh, vpos + dv);
E 4
I 4
    if (output) HGtline (hpos, vpos, hpos + dh, vpos + dv);
E 4
    hmot (dh);					/* new position is at */
    vmot (dv);					/* the end of the line */
}


/*----------------------------------------------------------------------------
 | Routine:	drawcirc (diameter)
 |
 | Results:	Draws a circle with leftmost point at current (hpos, vpos)
 |		with the given diameter d.
 |
 | Side Efct:	Resulting position is at (hpos + diameter, vpos)
 *----------------------------------------------------------------------------*/

drawcirc(d)
register int d;
{			/* 0.0 is the angle to sweep the arc: = full circle */
D 4
    HGArc (hpos + d/2, vpos, hpos, vpos, 0.0);
E 4
I 4
    if (output) HGArc (hpos + d/2, vpos, hpos, vpos, 0.0);
E 4
    hmot (d);			/* new postion is the right of the circle */
}


/*----------------------------------------------------------------------------
 | Routine:	drawellip (horizontal_diameter, vertical_diameter)
 |
 | Results:	Draws regular ellipses given the major "diameters."  It does
D 4
 |		so by drawing many small lines, every other pixel.  The ellipse
 |		formula:  ((x-x0)/hrad)**2 + ((y-y0)/vrad)**2 = 1 is used,
E 4
I 4
D 7
 |		so by drawing many small lines, every ELLIPSEDX pixels (DX
 |		defined here).  The ellipse formula:
 |			((x-x0)/hrad)**2 + ((y-y0)/vrad)**2 = 1     is used,
E 4
 |		converting to:  y = y0 +- vrad * sqrt(1 - ((x-x0)/hrad)**2).
 |		The line segments are duplicated (mirrored) on either side of
 |		the horizontal "diameter".
E 7
I 7
 |		so by drawing many small lines along the ellipses perimeter.
 |		The algorithm is a modified (bresenham-like) circle algorithm
E 7
 |
 | Side Efct:	Resulting position is at (hpos + hd, vpos).
 |
 | Bugs:	Odd numbered horizontal axes are rounded up to even numbers.
 *----------------------------------------------------------------------------*/

I 4
D 7
#define ELLIPSEDX	3

E 7
E 4
drawellip(hd, vd)
D 7
register int hd;
E 7
I 7
D 11
int hd;
E 7
int vd;
E 11
I 11
register int hd;
register int vd;
E 11
{
D 7
    register int bx;		/* multiplicative x factor */
    register int x;		/* x position drawing to */
    register int k2;		/* the square-root term */
    register int y;		/* y position drawing to */
    double k1;			/* k? are constants depending on parameters */
    int bxsave, xsave, hdsave;	/* places to save things to be used over */
E 7
I 7
    double xs, ys, xepsilon, yepsilon;	/* ellipse-calculation vairables */
    register int basex;			/* center of the ellipse */
    register int basey;
D 11
    register int mask;			/* used to skip points on the ellipse */
E 11
    register int extent;		/* number of points to produce */
E 7


D 4
    hd = 2 * ((hd + 1) / 2);	/* don't accept odd diameters */
    if (hd < 2) hd = 2;		/* or dinky ones */
E 4
I 4
D 7
    if (hd < ELLIPSEDX) {	/* don't draw tiny ellipses */
	if (output) HGtline (hpos, vpos, hpos + hd, vpos);
	hmot (hd);
	return;
E 7
I 7
D 11
    basex = hpos + (hd >> 1);	/* set the center of the ellipse */
E 11
I 11
    basex = hpos;		/* set the center of the ellipse */
E 11
    basey = vpos;
    hmot (hd);			/* troff motion done here, once. */
I 11
    if (!output) return;
E 11
    if ((hd = hd >> 1) < 1) hd = 1;	/* hd and vd are like radii */
I 11
    basex += ++hd;
E 11
    if ((vd = vd >> 1) < 1) vd = 1;
D 11
    ys = (double) vd;		/* initial distances from center to perimeter */
E 11
I 11
    ys = (double) ++vd;		/* initial distances from center to perimeter */
E 11
    xs = 0.0;
				/* calculate drawing parameters */
    if (vd > hd) {
D 11
	xepsilon = (double) hd / (double) (vd * vd);
	yepsilon = 1.0 / (double) hd;
	extent = 6 * vd + (vd >> 1);
	mask = (1 << (int) log10(5.0 / xepsilon + 1.0)) - 1;
E 11
I 11
	xepsilon = 4.0 * (double) hd / (double) (vd * vd);
	yepsilon = 4.0 / (double) hd;
	extent = (int) (1.575 * (double) vd);
E 11
    } else {
D 11
	xepsilon = 1.0 / (double) vd;
	yepsilon = (double) vd / (double) (hd * hd);
	extent = 6 * hd + (hd >> 1);
	mask = (1 << (int) log10(5.0 / yepsilon + 1.0)) - 1;
E 11
I 11
	xepsilon = 4.0 / (double) vd;
	yepsilon = 4.0 * (double) vd / (double) (hd * hd);
	extent = (int) (1.575 * (double) hd);
E 11
E 7
    }
E 4

D 7
    bx = 4 * (hpos + hd);
    x = hpos;
    k1 = vd / (2.0 * hd);
D 4
    k2 = hd * hd - 4 * (hpos + hd/2) * (hpos + hd/2);
E 4
I 4
    k2 = hd * hd - (2 * hpos + hd) * (2 * hpos + hd);
E 4

I 4
  if (output) {
E 4
    bxsave = bx;	/* remember the parameters that will change through */
D 4
    xsave = x;		/*    the top half of the elipse, so the bottom half */
E 4
I 4
    xsave = x;		/*    the top half of the ellipse so the bottom half */
E 4
    hdsave = hd;	/*    can be drawn later. */

    byte(ASPATH);		/* define drawing path */
D 4
    word(hd / 2 + 1);
E 4
I 4
    word((hd - 1) / ELLIPSEDX + 2);
E 4
    word(xbound(hpos));	/* start out at current position */
    word(ybound(vpos));
D 4
    do {
	x += 2;
E 4
I 4
    while ((hd -= ELLIPSEDX) > 0) {
	x += ELLIPSEDX;
E 4
	word(xbound(x));
D 4
	y = vpos + (int) (k1 * sqrt((double) (k2 + (bx -= 8) * x)));
E 4
I 4
	y = vpos + (int) (k1 * sqrt((double) (k2 + (bx -= (4*ELLIPSEDX)) * x)));
E 4
	word(ybound(y));
E 7
I 7
    byte(ASPATH);			/* start path definition */
D 11
    word(2 + (extent-1) / (mask+1));	/* number of points */
E 11
I 11
    word(1 + extent);			/* number of points */
E 11
    word(xbound(basex));
D 11
    word(ybound(basey + vd));
    while (--extent >= 0) {
E 11
I 11
    vd += basey;
    word(ybound(vd));
    while (extent--) {
E 11
	xs += xepsilon * ys;
	ys -= yepsilon * xs;
D 11
	if (!(extent&mask)) {		/* put out a point on ellipse */
	    word(xbound(basex + (int)(0.5 + xs)));
	    word(ybound(basey + (int)(0.5 + ys)));
	}
E 11
I 11
	hd = basex + (int) xs;
	vd = basey + (int) ys;
	word(xbound(hd));	/* put out a point on ellipse */
D 12
	word(ybound(hd));
E 12
I 12
	word(ybound(vd));
E 12
E 11
E 7
D 4
    } while (hd -= 2);
E 4
I 4
    }
D 7
    word(xbound(hpos + hdsave));	/* end at right side */
    word(ybound(vpos));
E 4
    byte(ADRAW);		/* now draw the top half */
E 7
I 7
    byte(ADRAW);		/* now draw the arc */
E 7
    byte(15);
D 7

    bx = bxsave;	/* get back the parameters for bottom half */
    x = xsave;
    hd = hdsave;

    byte(ASPATH);		/* define drawing path */
D 4
    word(hd / 2 + 1);
E 4
I 4
    word((hd - 1) / ELLIPSEDX + 2);
E 4
    word(xbound(hpos));	/* start out at current position */
    word(ybound(vpos));
D 4
    do {
	x += 2;
E 4
I 4
    while ((hd -= ELLIPSEDX) > 0) {
	x += ELLIPSEDX;
E 4
	word(xbound(x));
D 4
	y = vpos - (int) (k1 * sqrt((double) (k2 + (bx -= 8) * x)));
E 4
I 4
	y = vpos - (int) (k1 * sqrt((double) (k2 + (bx -= (4*ELLIPSEDX)) * x)));
E 4
	word(ybound(y));
D 4
    } while (hd -= 2);
E 4
I 4
    }
    word(xbound(hpos + hdsave));	/* end at right side */
    word(ybound(vpos));
E 4
    byte(ADRAW);		/* now draw the bottom half */
    byte(15);
I 4
  }
E 4

    hmot (hdsave);	/* end position is the right-hand side of the ellipse */
E 7
}


/*----------------------------------------------------------------------------
 | Routine:	drawarc (xcenter, ycenter, xpoint, ypoint)
 |
 | Results:	Draws an arc starting at current (hpos, vpos).  Center is
 |		at (hpos + cdh, vpos + cdv) and the terminating point is
 |		at <center> + (pdh, pdv).  The angle between the lines
 |		formed by the starting, ending, and center points is figured
 |		first, then the points and angle are sent to HGArc for the
 |		drawing.
 |
 | Side Efct:	Resulting position is at the last point of the arc.
 *----------------------------------------------------------------------------*/

drawarc (cdh, cdv, pdh, pdv)
register int cdh;
register int cdv;
register int pdh;
register int pdv;
{
    register double angle;
				/* figure angle from the three points...*/
				/* and convert (and round) to degrees */
    angle = (atan2((double) pdh, (double) pdv)
		- atan2 ((double) -cdh, (double) -cdv)) * 180.0 / pi;
				/* "normalize" and round */
    angle += (angle < 0.0)  ?  360.5 : 0.5;

D 4
    HGArc(hpos + cdh, vpos + cdv, hpos, vpos, (int) angle);
E 4
I 4
    if (output) HGArc(hpos + cdh, vpos + cdv, hpos, vpos, (int) angle);
E 4
    hmot(cdh + pdh);
    vmot(cdv + pdv);
}


/*----------------------------------------------------------------------------
 | Routine:	drawwig (character_buffer, file_pointer, type_flag)
 |
 | Results:	Given the starting position, the motion list in buf, and any
 |		extra characters from fp (terminated by a \n), drawwig sets
D 9
 |		up a point list to make a spline from.  If "pic" is set picurve
 |		is called to draw the curve in pic style; else it calls HGCurve
 |		for the gremlin-style curve.
E 9
I 9
 |		up a point list to make a spline or polygon from.  If "pic" is
 |		zero, a gremlin curve is drawn with HGCurve; if less than zero
 |		a polygon is drawn, else (pic > 0) a pic style spline is drawn
 |		using picurve.
E 9
 |
 | Side Efct:	Resulting position is reached from adding successive motions
 |		to the current position.
 *----------------------------------------------------------------------------*/

drawwig (buf, fp, pic)
char *buf;
FILE *fp;
int pic;
{
    register int len = strlen(buf);	/* length of the string in "buf" */
    register int npts = 2;		/* point list index */
    register char *ptr = buf;		/* "walking" pointer into buf */
    int x[MAXPOINTS], y[MAXPOINTS];	/* point list */

    while (*ptr == ' ') ptr++;		/* skip any leading spaces */
    x[1] = hpos;		/* the curve starts at the */
    y[1] = vpos;		/* current position */

    while (*ptr != '\n') {		/* curve commands end with a '\n' */
	hmot(atoi(ptr));		/* convert motion to curve points */
	x[npts] = hpos;			/* and remember them */
	while (isdigit(*++ptr));		/* skip number*/
	while (*++ptr == ' ');		/* skip spaces 'tween numbers */
	vmot(atoi(ptr));
	y[npts] = vpos;
	while (isdigit(*++ptr));
	while (*ptr == ' ') ptr++;
				/* if the amount we read wasn't the */
		 		/*    whole thing, read some more in */
	if (len - (ptr - buf) < 15 && *(buf + len - 1) != '\n') {
	    char *cop = buf;

	    while (*cop++ = *ptr++);	/* copy what's left to the beginning */
D 6
	    fgets ((cop - 1), len - (cop - buf), fp);
E 6
I 6
	    if (fgets ((cop - 1), len - (cop - buf), fp) == NULL)
		error (FATAL, "unexpected end of input");
E 6
	    ptr = buf;
	}
	if (npts < MAXPOINTS - 1)	/* if too many points, forget some */
	    npts++;
    }
    npts--;	/* npts must point to the last coordinate in x and y */
				/* now, actually DO the curve */
D 4
    if (pic)
	picurve(x, y, npts);
    else
	HGCurve(x, y, npts);
E 4
I 4
    if (output) {
D 7
	if (pic)
E 7
I 7
	if (pic > 0)
E 7
D 11
	    picurve(x, y, npts);
E 11
I 11
	    picurve(&x[0], &y[0], npts);
E 11
I 7
	else if (pic < 0)
D 11
	    polygon(x, y, npts);
E 11
I 11
	    polygon(&x[0], &y[0], npts);
E 11
E 7
	else
D 11
	    HGCurve(x, y, npts);
E 11
I 11
	    HGCurve(&x[0], &y[0], npts);
E 11
    }
E 4
}


/*----------------------------------------------------------------------------*
 | Routine:	drawthick (thickness)
 |
 | Results:	sets the variable "linethickness" to the given size.  If this
 |		is different than previous thiknesses, informs Imagen of the
 |		change.  NO motion is involved.
 *----------------------------------------------------------------------------*/

drawthick(s)
int s;
{
    if (linethickness != s) {
	byte(ASPEN);
	byte((linethickness = s) < 1 ? 1 : linethickness > MAXPENW ?
					MAXPENW : linethickness);
    }
}


/*----------------------------------------------------------------------------*
 | Routine:	drawstyle (style_bit_map)
 |
 | Results:	sets the variable "linmod" to the given bit map.
 |		NO motion is involved.
 *----------------------------------------------------------------------------*/

drawstyle(s)
int s;
{
    linmod = s;
I 7
}


/*----------------------------------------------------------------------------*
 | Routine:	polygon (xpoints, ypoints, num_of_points)
 |
 | Results:	draws a polygon through the points (xpoints, ypoints).
 |		The polygon has a raster fill associated with it.  The
 |		fill is already set up from conv(), but if the stipple
 |		pattern "laststipmem" is zero, polygon draws a "clear"
 |		polygon.
 |
 | Bugs:	If the path is not closed, polygon will NOT close it.
 |		(or is that a feature?)
D 9
 |		polygons are affected by line thickness, but NOT line style.
E 9
I 9
 |		self-interseting polygons can choke the Imagen - tough luck
E 9
 |		if the path is "counterclockwise", it'll slow down the
D 9
 |		Imagen's rendering.  This is not checked for here.
E 9
I 9
 |		rendering.  This is not checked for here.
E 9
 *----------------------------------------------------------------------------*/

extern int laststipmem;		/* this is set, before this routine, to the */
				/* stipple member number to be printed.  If */
				/* it's zero, the path should not be filled */
polygon(x, y, npts)
D 11
int x[MAXPOINTS];
int y[MAXPOINTS];
int npts;
E 11
I 11
register int *x;
register int *y;
register int npts;
E 11
{
	register int i;

I 9
	if (polyborder && linmod != SOLID) {	/* if the border isn't solid */
		for (i = 2; i <= npts; i++)	/*    have HGtline draw it */
			HGtline(x[i-1], y[i-1], x[i], y[i]);
	}
E 9
	byte(ASPATH);		/* set up to send the path */
	word(npts);
D 11
	for (i = 1; i <= npts; i++) {	/* send the path */
		word(xbound(x[i]));
		word(ybound(y[i]));
E 11
I 11
	while (npts--) {	/* send the path */
		x++;
		y++;
		word(xbound(*x));
		word(ybound(*y));
E 11
	}
D 8
	byte(ADRAW);
	byte(15);
E 8
I 8
D 9
	if (polyborder) {
E 9
I 9
	if (polyborder && linmod == SOLID) {
E 9
		byte(ADRAW);	/* draw the border, if requested */
		byte(15);
	}
E 8
	if (laststipmem) {	/* draw a filled path, if requested */
		byte(AFPATH);
		byte(7);
	}
E 7
}


/*----------------------------------------------------------------------------
 | Routine:	picurve (xpoints, ypoints, num_of_points)
 |
 | Results:	Draws a curve delimited by (not through) the line segments
 |		traced by (xpoints, ypoints) point list.  This is the "Pic"
 |		style curve.
 *----------------------------------------------------------------------------*/

picurve (x, y, npts)
D 11
int x[MAXPOINTS];
int y[MAXPOINTS];
E 11
I 11
register int *x;
register int *y;
E 11
int npts;
{
D 11
    register int i;		/* line segment traverser */
    register float w;		/* position factor */
    register int xp;		/* current point (and intermediary) */
    register int yp;
    register int j;		/* inner curve segment traverser */
E 11
    register int nseg;		/* effective resolution for each curve */
I 5
D 11
    register int pxp, pyp;	/* "previous" line segments' end */
E 5
    float t1, t2, t3;		/* calculation temps */
E 11
I 11
    register int xp;		/* current point (and temporary) */
    register int yp;
    int pxp, pyp;		/* previous point (to make lines from) */
    int i;			/* inner curve segment traverser */
    double w;			/* position factor */
    double t1, t2, t3;		/* calculation temps */
E 11


    if (x[1] == x[npts] && y[1] == y[npts]) {
	x[0] = x[npts - 1];		/* if the lines' ends meet, make */
	y[0] = y[npts - 1];		/* sure the curve meets */
	x[npts + 1] = x[2];
	y[npts + 1] = y[2];
    } else {				/* otherwise, make the ends of the */
	x[0] = x[1];			/* curve touch the ending points of */
	y[0] = y[1];			/* the line segments */
	x[npts + 1] = x[npts];
	y[npts + 1] = y[npts];
    }

D 11
    for (i = 0; i < npts; i++) {	/* traverse the line segments */
	xp = x[i] - x[i+1];
	yp = y[i] - y[i+1];
E 11
I 11
    pxp = (x[0] + x[1]) / 2;		/* make the last point pointers */
    pyp = (y[0] + y[1]) / 2;		/* point to the start of the 1st line */

    for (; npts--; x++, y++) {		/* traverse the line segments */
	xp = x[0] - x[1];
	yp = y[0] - y[1];
E 11
	nseg = (int) sqrt((double)(xp * xp + yp * yp));
D 11
	xp = x[i+1] - x[i+2];
	yp = y[i+1] - y[i+2];		/* "nseg" is the number of line */
E 11
I 11
	xp = x[1] - x[2];
	yp = y[1] - y[2];		/* "nseg" is the number of line */
E 11
					/* segments that will be drawn for */
D 11
					/* each curve segment.  ">> 3" is */
					/* dropping the resolution ( == / 8) */
	nseg = (nseg + (int) sqrt((double)(xp * xp + yp * yp))) >> 3;
E 11
I 11
					/* each curve segment.  ">> 4" is */
					/* dropping the resolution ( == / 16) */
	nseg = (nseg + (int) sqrt((double)(xp * xp + yp * yp))) >> 4;
E 11

D 5
	byte(ASPATH);
	if (nseg)
	    word(nseg + 1);
	else
	    word(2);
	for (j = 0; j <= nseg; j++) {
E 5
I 5
D 11
	pxp = (x[i]+x[i+1]+1) >> 1;	/* the start of the first line seg */
	pyp = (y[i]+y[i+1]+1) >> 1;
	for (j = 1; j <= nseg; j++) {
E 5
	    w = (float) j / (float) nseg;
	    t1 = 0.5 * w * w;
	    w -= 0.5;
	    t2 = 0.75 - w * w ;
	    w -= 0.5;
	    t3 = 0.5 * w * w;
	    xp = t1 * x[i+2] + t2 * x[i+1] + t3 * x[i] + 0.5;
	    yp = t1 * y[i+2] + t2 * y[i+1] + t3 * y[i] + 0.5;
D 5
	    word(xbound(xp));
	    word(ybound(yp));
E 5
I 5
	    HGtline (pxp, pyp, xp, yp);
E 11
I 11
	for (i = 1; i < nseg; i++) {
	    w = (double) i / (double) nseg;
	    t1 = w * w;
	    t3 = t1 + 1.0 - (w + w);
	    t2 = 2.0 - (t3 + t1);
	    xp = (((int) (t1 * x[2] + t2 * x[1] + t3 * x[0])) + 1) / 2;
	    yp = (((int) (t1 * y[2] + t2 * y[1] + t3 * y[0])) + 1) / 2;

	    HGtline(pxp, pyp, xp, yp);
E 11
	    pxp = xp;
	    pyp = yp;
E 5
	}
D 5
	if (nseg == 0) {
	    word(xbound(xp));
	    word(ybound(yp));
	}
	byte(ADRAW);
	byte(15);
E 5
    }
}


/*----------------------------------------------------------------------------
 | Routine:	HGArc (xcenter, ycenter, xstart, ystart, angle)
 |
 | Results:	This routine plots an arc centered about (cx, cy) counter
 |		clockwise starting from the point (px, py) through 'angle'
 |		degrees.  If angle is 0, a full circle is drawn. It does so
 |		by creating a draw-path around the arc whose density of
 |		points depends on the size of the arc.
 *----------------------------------------------------------------------------*/

HGArc(cx,cy,px,py,angle)
D 5
int cx, cy, px, py, angle;
E 5
I 5
register int cx;
register int cy;
int px, py, angle;
E 5
{
    double xs, ys, resolution, fullcircle;
D 5
    register int i;
E 5
I 5
    register int mask;
E 5
    register int extent;
    register int nx;
    register int ny;
    register double epsilon;

    xs = px - cx;
    ys = py - cy;

D 5
/* calculate drawing parameters */
E 5
I 5
		/* calculate how fine to make the lines that build
		   the circle.  Resolution cannot be dropped, but
		   mask is used to skip some points for larger
		   arcs due to Imagen's path length limitations */
E 5

D 5
    resolution = pow(2.0, floor(log10(sqrt(xs * xs + ys * ys)) * log2_10));
E 5
I 5
    resolution = sqrt(xs * xs + ys * ys);
    mask = (1 << (int) log10(resolution + 1.0)) - 1;

E 5
    epsilon = 1.0 / resolution;
D 5
    fullcircle = ceil(2 * pi * resolution);
E 5
I 5
    fullcircle = (2.0 * pi) * resolution;
E 5
    if (angle == 0)
	extent = fullcircle;
    else 
	extent = angle * fullcircle / 360.0;

    byte(ASPATH);			/* start path definition */
    if (extent > 1) {
D 5
	word(extent);			/* number of points */
	for (i=0; i<extent; ++i) {
E 5
I 5
	word(2 + (extent-1) / (mask+1));	/* number of points */
	word(xbound(px));
	word(ybound(py));
	while (--extent >= 0) {
E 5
	    xs += epsilon * ys;
D 5
	    nx = (int) (xs + cx + 0.5);
E 5
I 5
	    nx = cx + (int) (xs + 0.5);
E 5
	    ys -= epsilon * xs;
D 5
	    ny = (int) (ys + cy + 0.5);
	    word(xbound(nx));	/* put out a point on circle */
	    word(ybound(ny));
E 5
I 5
	    ny = cy + (int) (ys + 0.5);
	    if (!(extent&mask)) {
		word(xbound(nx));	/* put out a point on circle */
		word(ybound(ny));
	    }
E 5
	}   /* end for */
    } else {			/* arc is too small: put out point */
	word(2);
D 5
	word(xbound(cx));
	word(ybound(cy));
	word(xbound(cx));
	word(ybound(cy));
E 5
I 5
	word(xbound(px));
	word(ybound(py));
	word(xbound(px));
	word(ybound(py));
E 5
    }
    byte(ADRAW);		/* now draw the arc */
    byte(15);
}  /* end HGArc */


/*----------------------------------------------------------------------------
 | Routine:	Paramaterize (xpoints, ypoints, hparams, num_points)
 |
 | Results:	This routine calculates parameteric values for use in
 |		calculating curves.  The parametric values are returned
 |		in the array h.  The values are an approximation of
 |		cumulative arc lengths of the curve (uses cord length).
 |		For additional information, see paper cited below.
 *----------------------------------------------------------------------------*/

static Paramaterize(x, y, h, n)
int x[MAXPOINTS];
int y[MAXPOINTS];
float h[MAXPOINTS];
int n;
{
	register int dx;
	register int dy;
	register int i;
	register int j;
	float u[MAXPOINTS];


	for (i=1; i<=n; ++i) {
	    u[i] = 0;
	    for (j=1; j<i; j++) {
		dx = x[j+1] - x[j];
		dy = y[j+1] - y[j];
		u[i] += sqrt ((double) (dx * dx + dy * dy));
	    }
	}
	for (i=1; i<n; ++i)  h[i] = u[i+1] - u[i];
}  /* end Paramaterize */


/*----------------------------------------------------------------------------
 | Routine:	PeriodicSpline (h, z, dz, d2z, d3z, npoints)
 |
 | Results:	This routine solves for the cubic polynomial to fit a
 |		spline curve to the the points  specified by the list
 |		of values.  The Curve generated is periodic.  The algorithms
 |		for this curve are from the "Spline Curve Techniques" paper
 |		cited below.
 *----------------------------------------------------------------------------*/

static PeriodicSpline(h, z, dz, d2z, d3z, npoints)
float h[MAXPOINTS];		/* paramaterization  */
int z[MAXPOINTS];		/* point list */
float dz[MAXPOINTS];			/* to return the 1st derivative */
float d2z[MAXPOINTS], d3z[MAXPOINTS];	/* 2nd and 3rd derivatives */
int npoints;				/* number of valid points */
{
	float d[MAXPOINTS]; 
	float deltaz[MAXPOINTS], a[MAXPOINTS], b[MAXPOINTS];
	float c[MAXPOINTS], r[MAXPOINTS], s[MAXPOINTS];
	int i;

						/* step 1 */
	for (i=1; i<npoints; ++i) {
	    deltaz[i] = h[i] ? ((double) (z[i+1] - z[i])) / h[i] : 0;
	}
	h[0] = h[npoints-1];
	deltaz[0] = deltaz[npoints-1];

						/* step 2 */
	for (i=1; i<npoints-1; ++i) {
	    d[i] = deltaz[i+1] - deltaz[i];
	}
	d[0] = deltaz[1] - deltaz[0];

						/* step 3a */
	a[1] = 2 * (h[0] + h[1]);
	b[1] = d[0];
	c[1] = h[0];
	for (i=2; i<npoints-1; ++i) {
	    a[i] = 2*(h[i-1]+h[i]) - pow ((double) h[i-1],(double)2.0) / a[i-1];
	    b[i] = d[i-1] - h[i-1] * b[i-1]/a[i-1];
	    c[i] = -h[i-1] * c[i-1]/a[i-1];
	}

						/* step 3b */
	r[npoints-1] = 1;
	s[npoints-1] = 0;
	for (i=npoints-2; i>0; --i) {
	    r[i] = -(h[i] * r[i+1] + c[i])/a[i];
	    s[i] = (6 * b[i] - h[i] * s[i+1])/a[i];
	}

						/* step 4 */
	d2z[npoints-1] = (6 * d[npoints-2] - h[0] * s[1] 
	                   - h[npoints-1] * s[npoints-2]) 
	                 / (h[0] * r[1] + h[npoints-1] * r[npoints-2] 
	                    + 2 * (h[npoints-2] + h[0]));
	for (i=1; i<npoints-1; ++i) {
	    d2z[i] = r[i] * d2z[npoints-1] + s[i];
	}
	d2z[npoints] = d2z[1];

						/* step 5 */
	for (i=1; i<npoints; ++i) {
	    dz[i] = deltaz[i] - h[i] * (2 * d2z[i] + d2z[i+1])/6;
	    d3z[i] = h[i] ? (d2z[i+1] - d2z[i])/h[i] : 0;
	}
}  /* end PeriodicSpline */


/*----------------------------------------------------------------------------
 | Routine:	NaturalEndSpline (h, z, dz, d2z, d3z, npoints)
 |
 | Results:	This routine solves for the cubic polynomial to fit a
 |		spline curve the the points  specified by the list of
 |		values.  The alogrithms for this curve are from the
 |		"Spline Curve Techniques" paper cited below.
 *----------------------------------------------------------------------------*/

static NaturalEndSpline(h, z, dz, d2z, d3z, npoints)
float h[MAXPOINTS];		/* parameterization */
int z[MAXPOINTS];		/* Point list */
float dz[MAXPOINTS];			/* to return the 1st derivative */
float d2z[MAXPOINTS], d3z[MAXPOINTS];	/* 2nd and 3rd derivatives */
int npoints;				/* number of valid points */
{
	float d[MAXPOINTS];
	float deltaz[MAXPOINTS], a[MAXPOINTS], b[MAXPOINTS];
	int i;

						/* step 1 */
	for (i=1; i<npoints; ++i) {
	    deltaz[i] = h[i] ? ((double) (z[i+1] - z[i])) / h[i] : 0;
	}
	deltaz[0] = deltaz[npoints-1];

						/* step 2 */
	for (i=1; i<npoints-1; ++i) {
	    d[i] = deltaz[i+1] - deltaz[i];
	}
	d[0] = deltaz[1] - deltaz[0];

						/* step 3 */
	a[0] = 2 * (h[2] + h[1]);
	b[0] = d[1];
	for (i=1; i<npoints-2; ++i) {
	    a[i] = 2*(h[i+1]+h[i+2]) - pow((double) h[i+1],(double) 2.0)/a[i-1];
	    b[i] = d[i+1] - h[i+1] * b[i-1]/a[i-1];
	}

						/* step 4 */
	d2z[npoints] = d2z[1] = 0;
	for (i=npoints-1; i>1; --i) {
	    d2z[i] = (6 * b[i-2] - h[i] *d2z[i+1])/a[i-2];
	}

						/* step 5 */
	for (i=1; i<npoints; ++i) {
	    dz[i] = deltaz[i] - h[i] * (2 * d2z[i] + d2z[i+1])/6;
	    d3z[i] = h[i] ? (d2z[i+1] - d2z[i])/h[i] : 0;
	}
}  /* end NaturalEndSpline */


/*----------------------------------------------------------------------------
 | Routine:	HGCurve(xpoints, ypoints, num_points)
 |
 | Results:	This routine generates a smooth curve through a set of points.
 |		The method used is the parametric spline curve on unit knot
 |		mesh described in "Spline Curve Techniques" by Patrick
 |		Baudelaire, Robert Flegal, and Robert Sproull -- Xerox Parc.
 *----------------------------------------------------------------------------*/

#define PointsPerInterval 32

HGCurve(x, y, numpoints)
D 11
int x[MAXPOINTS];
int y[MAXPOINTS];
E 11
I 11
int *x;
int *y;
E 11
int numpoints;
{
	float h[MAXPOINTS], dx[MAXPOINTS], dy[MAXPOINTS];
	float d2x[MAXPOINTS], d2y[MAXPOINTS], d3x[MAXPOINTS], d3y[MAXPOINTS];
	float t, t2, t3;
	register int j;
	register int k;
	register int nx;
	register int ny;
	int lx, ly;


	lx = x[1];
	ly = y[1];

	     /* Solve for derivatives of the curve at each point 
              * separately for x and y (parametric).
	      */
	Paramaterize(x, y, h, numpoints);
							/* closed curve */
	if ((x[1] == x[numpoints]) && (y[1] == y[numpoints])) {
	    PeriodicSpline(h, x, dx, d2x, d3x, numpoints);
	    PeriodicSpline(h, y, dy, d2y, d3y, numpoints);
	} else {
	    NaturalEndSpline(h, x, dx, d2x, d3x, numpoints);
	    NaturalEndSpline(h, y, dy, d2y, d3y, numpoints);
	}

	      /* generate the curve using the above information and 
	       * PointsPerInterval vectors between each specified knot.
	       */

	for (j=1; j<numpoints; ++j) {
	    if ((x[j] == x[j+1]) && (y[j] == y[j+1])) continue;
	    for (k=0; k<=PointsPerInterval; ++k) {
		t = (float) k * h[j] / (float) PointsPerInterval;
		t2 = t * t;
		t3 = t * t * t;
		nx = x[j] + (int) (t * dx[j] + t2 * d2x[j]/2 + t3 * d3x[j]/6);
		ny = y[j] + (int) (t * dy[j] + t2 * d2y[j]/2 + t3 * d3y[j]/6);
		HGtline(lx, ly, nx, ny);
		lx = nx;
		ly = ny;
	    }  /* end for k */
	}  /* end for j */
}  /* end HGCurve */


/*----------------------------------------------------------------------------
D 3
 | Routine:	HGtline(xstart, ystart, xend, yend)
E 3
I 3
 | Routine:	line(xstart, ystart, xend, yend)
E 3
 |
 | Results:	Creates a drawing path and draws the line.  If the line falls
 |		off the end of the page, a crude clipping is done:  truncating
 |		the offending ordinate.
D 3
 |
 | Bugs:	Does NOTHING about line style yet...
E 3
 *----------------------------------------------------------------------------*/

D 3
HGtline(x0, y0, x1, y1)
E 3
I 3
line(x0, y0, x1, y1)
E 3
int x0, y0, x1, y1;
{
    byte(ASPATH);		/* send the coordinates first */
    word(2);		/* only two */
    word(xbound(x0));
    word(ybound(y0));
    word(xbound(x1));
    word(ybound(y1));
    byte(ADRAW);		/* now draw it */
    byte(15);		/* black */
D 3
}  /* end HGtline */
E 3
I 3
}  /* end line */


/*----------------------------------------------------------------------------*
 | Routine:	change (x_position, y_position, visible_flag)
 |
 | Results:	As HGtline passes from the invisible to visible (or vice
 |		versa) portion of a line, change is called to either draw
 |		the line, or initialize the beginning of the next one.
 |		Change calls line to draw segments if visible_flag is set
 |		(which means we're leaving a visible area).
 *----------------------------------------------------------------------------*/

change (x, y, vis)
register int x;
register int y;
register int vis;
{
    static int xorg;
    static int yorg;

    if (vis)		/* leaving a visible area, draw it. */
	line (xorg, yorg, x, y);
    else {		/* otherwise, we're entering one, remember beginning */
	xorg = x;
	yorg = y;
    }
}


/*----------------------------------------------------------------------------
 | Routine:	HGtline (xstart, ystart, xend, yend)
 |
 | Results:	Draws a line from (x0,y0) to (x1,y1) using line(x0,y0,x1,y1)
 |		to place individual segments of dotted or dashed lines.
 *----------------------------------------------------------------------------*/

HGtline(x0, y0, x1, y1)
D 5
register int x0;
register int y0;
int x1;
int y1;
E 5
I 5
int x0, y0, x1, y1;
E 5
{
    register int dx;
    register int dy;
I 5
    register int oldcoord;
E 5
    register int res1;
    register int visible;
D 5
    int res2;
    int xinc;
    int yinc;
E 5
I 5
    register int res2;
    register int xinc;
    register int yinc;
E 5
D 4
    int slope;
E 4


D 9
    if (linmod == -1) {
E 9
I 9
    if (linmod == SOLID) {
E 9
	line(x0, y0, x1, y1);
	return;
    }
    xinc = 1;
    yinc = 1;
    if ((dx = x1-x0) < 0) {
        xinc = -1;
        dx = -dx;
    }
    if ((dy = y1-y0) < 0) {
        yinc = -1;
        dy = -dy;
    }
D 4
    slope = xinc*yinc;
E 4
    res1 = 0;
    res2 = 0;
    visible = 0;
D 5
    if (dx >= dy) 
E 5
I 5
    if (dx >= dy) {
	oldcoord = y0;
E 5
        while (x0 != x1) {
D 4
            if((((x0+slope*y0)&linmod)&&1)^visible) {
E 4
I 4
D 5
            if(((x0&linmod)&&1)^visible) {
E 4
	    	change(x0, y0, visible);
		visible = !visible;
E 5
I 5
            if((x0&linmod) && !visible) {
		change(x0, y0, 0);
		visible = 1;
	    } else if(visible && !(x0&linmod)) {
		change(x0 - xinc, oldcoord, 1);
		visible = 0;
E 5
	    }
            if (res1 > res2) {
I 5
		oldcoord = y0;
E 5
                res2 += dx - res1;
                res1 = 0;
                y0 += yinc;
            }
            res1 += dy;
            x0 += xinc;
        } 
D 5
    else 
E 5
I 5
    } else {
	oldcoord = x0;
E 5
        while (y0 != y1) {
D 4
            if((((x0+slope*y0)&linmod)&&1)^visible) {
E 4
I 4
D 5
            if(((y0&linmod)&&1)^visible) {
E 4
		change(x0, y0, visible);
		visible = !visible;
E 5
I 5
            if((y0&linmod) && !visible) {
		change(x0, y0, 0);
		visible = 1;
	    } else if(visible && !(y0&linmod)) {
		change(oldcoord, y0 - yinc, 1);
		visible = 0;
E 5
	    }
            if (res1 > res2) {
I 5
		oldcoord = x0;
E 5
                res2 += dy - res1;
                res1 = 0;
                x0 += xinc;
            }
            res1 += dx;
            y0 += yinc;
        }
I 5
    }
E 5
    if(visible) change(x1, y1, 1);
}
E 3
E 1
