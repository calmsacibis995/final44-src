h23350
s 00038/00030/00760
d D 1.14 85/12/16 13:50:13 slatteng 18 16
c clean/speed up pic curve rendering (and ellipses)
e
s 00032/00026/00764
d R 1.14 85/12/13 12:51:35 slatteng 17 16
c clean/speeded up pic curve rendering
e
s 00022/00022/00768
d D 1.13 84/05/24 18:19:57 slatteng 16 14
c added polygons with stipples to varian/versatec drivers and sorter
e
s 00021/00020/00770
d R 1.13 84/05/24 16:58:17 slatteng 15 14
c added polygons with stipples to varian/versatec drivers and sorter
e
s 00041/00047/00749
d D 1.12 84/04/07 19:09:07 slatteng 14 12
c clean up RoundEnd, and make it use diameters.
e
s 00016/00017/00779
d R 1.12 84/03/27 11:45:58 slatteng 13 12
c fix run--forever problem in Roundend, and try a speedup.
e
s 00004/00002/00792
d D 1.11 84/03/14 17:55:12 slatteng 12 10
c cleaned up input (test for EOF), fixed RoundEnd bug testing for end condition
e
s 00005/00003/00791
d R 1.11 84/03/14 17:52:26 slatteng 11 10
c clean up input (added EOF checking), fixed bug in RoundEnd for ending condition
e
s 00095/00078/00699
d D 1.10 84/03/03 15:25:54 slatteng 10 9
c fixed up ellipse, circle and RoundEnd routines for speed
e
s 00022/00014/00755
d D 1.9 83/11/30 17:49:14 slatteng 9 8
c changed ellipse drawing function to not force even-widthed ellipses
e
s 00011/00008/00758
d D 1.8 83/11/22 16:57:32 slatteng 8 7
c fix to not output when "output" isn't set.
e
s 00002/00002/00764
d D 1.7 83/07/09 21:44:17 slatteng 7 6
c fixed semicolon problem
e
s 00138/00028/00628
d D 1.6 83/07/09 20:39:50 slatteng 6 5
c add new spline function, thickness, and style too
e
s 00001/00001/00655
d D 1.5 83/07/08 14:41:39 slatteng 5 4
c fixed syntax error
e
s 00272/00240/00384
d D 1.4 83/07/08 13:48:36 slatteng 4 3
c added comments and suped up a bit.
e
s 00004/00004/00620
d D 1.3 83/07/05 17:54:01 slatteng 3 2
c change resolution of ellipses to a line every two pixels instead of 1
e
s 00070/00025/00554
d D 1.2 83/07/05 17:15:58 slatteng 2 1
c fix bugs in arcs and splines, and put in ellipse routine
e
s 00579/00000/00000
d D 1.1 83/07/01 12:32:35 slatteng 1 0
c date and time created 83/07/01 12:32:35 by slatteng
e
u
U
t
T
I 1
D 14
/* %M%	%I%	%E%
E 14
I 14
/* graph.c	1.12	84/03/27
E 14
 *
 *	This file contains the functions for producing the graphics
 *   images in the varian/versatec drivers for ditroff.
 */


#include <stdio.h>
I 2
#include <ctype.h>
E 2
#include <math.h>


#define TRUE	1
#define FALSE	0
I 12
#define FATAL	1
E 12
I 4
				/* imports from dver.c */
#define  hmot(n)	hpos += n;
#define  vmot(n)	vgoto(vpos + n);

extern int hpos;
extern int vpos;
I 8
extern int output;
E 8
extern vgoto();
extern point();

E 4
#define MAXPOINTS 200	/* number of points legal for a curve */

#define SOLID -1	/* line styles:  these are used as bit masks to */
#define DOTTED 004	/* create the right style lines. */
#define DASHED 020
#define DOTDASHED 024
#define LONGDASHED 074
				/* constants... */
D 2
#define  pi	3.141592653589793238462643
E 2
I 2
#define  pi		3.14159265358979324
E 2
#define  log2_10	3.3219280948873623
D 4
				/* imports from dver.c */
#define  hmot(n)	hpos += n;
#define  vmot(n)	vgoto(vpos + n);
E 4

D 4
extern int hpos;
extern int vpos;
extern vgoto();
extern point();
E 4

D 4


E 4
int	linethickness = 3;	/* number of pixels wide to make lines */
int	linmod = SOLID;		/* type of line (SOLID, DOTTED, DASHED...) */
D 2
int	lastx;
int	lasty;
E 2



I 4
/*----------------------------------------------------------------------------
 * Routine:	drawline (horizontal_motion, vertical_motion)
 *
 * Results:	Draws a line of "linethickness" width and "linmod" style
 *		from current (hpos, vpos) to (hpos + dh, vpos + dv).
 *
 * Side Efct:	Resulting position is at end of line (hpos + dh, vpos + dv)
 *----------------------------------------------------------------------------*/

E 4
drawline(dh, dv)
register int dh;
register int dv;
{
D 8
    HGtline (hpos, vpos, hpos + dh, vpos + dv);
E 8
I 8
    if (output) HGtline (hpos, vpos, hpos + dh, vpos + dv);
E 8
    hmot (dh);					/* new position is at */
    vmot (dv);					/* the end of the line */
}


I 4
/*----------------------------------------------------------------------------
 * Routine:	drawcirc (diameter)
 *
 * Results:	Draws a circle with leftmost point at current (hpos, vpos)
 *		with the given diameter d.
 *
 * Side Efct:	Resulting position is at (hpos + diameter, vpos)
 *----------------------------------------------------------------------------*/

E 4
drawcirc(d)
register int d;
D 4
{
E 4
I 4
{			/* 0.0 is the angle to sweep the arc: = full circle */
E 4
D 8
    HGArc (hpos + d/2, vpos, hpos, vpos, 0.0);
E 8
I 8
    if (output) HGArc (hpos + d/2, vpos, hpos, vpos, 0.0);
E 8
    hmot (d);			/* new postion is the right of the circle */
}


D 2
drawellip(h, v)
register int h;
register int v;
E 2
I 2
D 4
/*******************************************************************************
 *
E 4
I 4
/*----------------------------------------------------------------------------
E 4
 * Routine:	drawellip (horizontal_diameter, vertical_diameter)
 *
D 4
 *	This routine draws regular ellipses given the major diagonals.
D 3
 *	It does so by drawing many small lines, every one pixels.
E 3
I 3
 *	It does so by drawing many small lines, every other pixel.
E 4
I 4
 * Results:	Draws regular ellipses given the major "diameters."  It does
D 10
 *		so by drawing many small lines, every other pixel.  The ellipse
 *		formula:  ((x-x0)/hrad)**2 + ((y-y0)/vrad)**2 = 1 is used,
 *		converting to:  y = y0 +- vrad * sqrt(1 - ((x-x0)/hrad)**2).
 *		The line segments are duplicated (mirrored) on either side of
 *		the horizontal "diameter".
E 10
I 10
 *		so using a modified circle algorithm (see RoundEnd) that
 *		increments x and y proportionally to their axes.
E 10
E 4
E 3
 *
D 4
 *	The ellipse formula:  ((x-x0)/hrad)**2 + ((y-y0)/vrad)**2 = 1
 *	is used, converting to y = f(x) and duplicating the lines about
 *	the vertical axis.
E 4
I 4
 * Side Efct:	Resulting position is at (hpos + hd, vpos).
E 4
D 10
 *
D 4
 * Results:	The current position is at the rightmost point of the ellipse
 *
 ******************************************************************************/
E 4
I 4
 * Bugs:	Odd numbered horizontal axes are rounded up to even numbers.
E 10
 *----------------------------------------------------------------------------*/
E 4

I 9
D 10
#define ELLIPSEDX	3

E 10
E 9
drawellip(hd, vd)
D 10
register int hd;
E 10
I 10
int hd;
E 10
int vd;
E 2
{
I 2
D 10
    register int bx;		/* multiplicative x factor */
    register int x;		/* x position drawing to */
    register int yk;		/* the square-root term */
    register int y;		/* y position drawing to */
    double k1;			/* k? are constants depending on parameters */
    int k2, oldy1, oldy2;	/* oldy? are last y points drawn to */
E 10
I 10
    double xs, ys, xepsilon, yepsilon;
    register int thick;
    register int basex;
    register int basey;
    register int x;
    register int y;
E 10


D 4
    hd = 2 * ((hd + 1) / 2);	/* don't accept odd diagonals */
E 4
I 4
D 9
    hd = 2 * ((hd + 1) / 2);	/* don't accept odd diameters */
E 9
I 9
D 10
    if (hd < ELLIPSEDX) {
	if (output) HGtline(hpos, vpos, hpos + hd, vpos);
	hmot(hd);
	return;
    }
E 10
I 10
D 18
    basex = hpos + (hd >> 1);		/* bases == coordinates of center */
E 18
I 18
    basex = hpos;			/* bases == coordinates of center */
E 18
    hmot(hd);				/* horizontal motion (hpos should */
D 18
    basey = vpos;			/*   NOT be used after this) */
E 18
I 18
    if (!output) return;		/*   NOT be used after this) */
    basey = vpos;
E 18
					/* hd and vd are radii, not diameters */
D 18
    if ((hd = hd >> 1) < 1) hd++;	/* neither diameter can be zero. */
    if ((vd = vd >> 1) < 1) vd++;	/*   hd changed!! no hmot after this */
E 18
I 18
    if ((hd = hd >> 1) < 1) hd = 1;	/* neither diameter can be zero. */
    basex += hd;			/*   hd changed!! no hmot after this */
    if ((vd = vd >> 1) < 1) vd = 1;
E 18
    ys = (double) vd;			/* start at top of the ellipse */
    xs = 0.0;				/*   (y = 1/2 diameter, x = 0) */
E 10
E 9
E 4

D 10
    bx = 4 * (hpos + hd);
    x = hpos;
    k1 = vd / (2.0 * hd);
D 9
    k2 = hd * hd - 4 * (hpos + hd/2) * (hpos + hd/2);
E 9
I 9
    k2 = hd * hd - (2 * hpos + hd) * (2 * hpos + hd);
E 9
    oldy1 = vpos;
    oldy2 = vpos;
E 10
I 10
    if ((thick = vd) > hd) thick = hd;
    xepsilon = (double) thick / (double) (vd * vd);
    yepsilon = (double) thick / (double) (hd * hd);
E 10

D 10
    hmot (hd);		/* end position is the right-hand side of the ellipse */
E 10
I 10
		/* Calculate trajectory of the ellipse for 1/4	*/
		/* the circumference (while ys is non-negative)	*/
		/* and mirror to get the other three quadrants.	*/
E 10

D 8
    do {
E 8
I 8
D 9
    if (output) do {
E 8
D 4
	yk = k1 * sqrt((double) (k2 + (bx -= 8) * (x += 2))) + 0.5;
E 4
I 4
	yk = (int) (k1 * sqrt((double) (k2 + (bx -= 8) * (x += 2))));
E 9
I 9
D 10
    if (output) {
	while ((hd -= ELLIPSEDX) > 0) {
	    yk=(int)(k1*sqrt((double)(k2+(bx-=(4*ELLIPSEDX))*(x+=ELLIPSEDX))));
E 9
E 4

D 3
	HGtline (x-1, oldy1, x, y = vpos + yk);    /* top half of ellipse */
E 3
I 3
D 9
	HGtline (x-2, oldy1, x, y = vpos + yk);    /* top half of ellipse */
E 3
	oldy1 = y;
D 3
	HGtline (x-1, oldy2, x, y = vpos - yk);	  /* bottom half of ellipse */
E 3
I 3
	HGtline (x-2, oldy2, x, y = vpos - yk);	  /* bottom half of ellipse */
E 3
	oldy2 = y;

D 3
    } while (--hd);
E 3
I 3
    } while (hd -= 2);
E 9
I 9
	    HGtline (x-ELLIPSEDX, oldy1, x, y = vpos + yk);	/* top half */
	    oldy1 = y;
	    HGtline (x-ELLIPSEDX, oldy2, x, y = vpos - yk);	/* bottom */
	    oldy2 = y;
E 10
I 10
D 14
    thick = linethickness / 2;
    if (thick) {		/* more than one pixel thick */
	RoundEnd(basex, ((int)(ys + 0.5)) + basey, thick, 0);
	RoundEnd(basex, basey - ((int)(ys + 0.5)), thick, 0);
E 14
I 14
    if (linethickness > 1) {		/* more than one pixel thick */
	RoundEnd(basex, ((int)(ys + 0.5)) + basey, linethickness, 0);
	RoundEnd(basex, basey - ((int)(ys + 0.5)), linethickness, 0);
E 14
	while (ys >= 0) {
	    xs += xepsilon * ys;	/* generate circumference */
	    ys -= yepsilon * xs;
	    x = (int)(xs + 0.5);
	    y = (int)(ys + 0.5);
D 14
	    RoundEnd(x + basex, y + basey, thick, 0);
	    RoundEnd(x + basex, basey - y, thick, 0);
	    RoundEnd(basex - x, y + basey, thick, 0);
	    RoundEnd(basex - x, basey - y, thick, 0);
E 14
I 14
	    RoundEnd(x + basex, y + basey, linethickness, 0);
	    RoundEnd(x + basex, basey - y, linethickness, 0);
	    RoundEnd(basex - x, y + basey, linethickness, 0);
	    RoundEnd(basex - x, basey - y, linethickness, 0);
E 14
E 10
	}
D 10
	HGtline(x, oldy1, hpos, vpos);
	HGtline(x, oldy2, hpos, vpos);
E 10
I 10
    } else {		/* do the perimeter only (no fill) */
	point(basex, ((int)(ys + 0.5)) + basey);
	point(basex, basey - ((int)(ys + 0.5)));
	while (ys >= 0) {
	    xs += xepsilon * ys;	/* generate circumference */
	    ys -= yepsilon * xs;
	    x = (int)(xs + 0.5);
	    y = (int)(ys + 0.5);
	    point(x + basex, y + basey);
	    point(x + basex, basey - y);
	    point(basex - x, y + basey);
	    point(basex - x, basey - y);
        }
E 10
    }
E 9
E 3
E 2
}

I 4

/*----------------------------------------------------------------------------
 * Routine:	drawarc (xcenter, ycenter, xpoint, ypoint)
 *
 * Results:	Draws an arc starting at current (hpos, vpos).  Center is
 *		at (hpos + cdh, vpos + cdv) and the terminating point is
 *		at <center> + (pdh, pdv).  The angle between the lines
 *		formed by the starting, ending, and center points is figured
 *		first, then the points and angle are sent to HGArc for the
 *		drawing.
 *
 * Side Efct:	Resulting position is at the last point of the arc.
 *----------------------------------------------------------------------------*/

E 4
drawarc (cdh, cdv, pdh, pdv)
register int cdh;
register int cdv;
register int pdh;
register int pdv;
{
    register double angle;
				/* figure angle from the three points...*/
D 2
    angle = atan2((double) -cdh, (double) -cdv)
		- atan2 ((double) pdh, (double) pdv);
    if (angle < 0.0) angle += 2 * pi;
E 2
I 2
				/* and convert (and round) to degrees */
    angle = (atan2((double) pdh, (double) pdv)
		- atan2 ((double) -cdh, (double) -cdv)) * 180.0 / pi;
				/* "normalize" and round */
    angle += (angle < 0.0)  ?  360.5 : 0.5;
E 2

D 2
    HGArc(hpos+cdh, vpos+cdv, hpos+cdh+pdh, vpos+cdv+pdv, angle*180.0/pi);
E 2
I 2
D 8
    HGArc(hpos + cdh, vpos + cdv, hpos, vpos, (int) angle);
E 8
I 8
    if (output) HGArc(hpos + cdh, vpos + cdv, hpos, vpos, (int) angle);
E 8
E 2
    hmot(cdh + pdh);
    vmot(cdv + pdv);
}


I 4
/*----------------------------------------------------------------------------
D 6
 * Routine:	drawwig (character_buffer, file_pointer)
E 6
I 6
 * Routine:	drawwig (character_buffer, file_pointer, type_flag)
E 6
 *
 * Results:	Given the starting position, the motion list in buf, and any
 *		extra characters from fp (terminated by a \n), drawwig sets
D 6
 *		up a point list to make a spline from and calls HGCurve.
E 6
I 6
 *		up a point list to make a spline from.  If "pic" is set picurve
 *		is called to draw the curve in pic style; else it calls HGCurve
 *		for the gremlin-style curve.
E 6
 *
 * Side Efct:	Resulting position is reached from adding successive motions
 *		to the current position.
D 6
 *
 * Bugs:	This MAY not be the final spline maker (PIC expects different)
E 6
 *----------------------------------------------------------------------------*/

E 4
D 6
drawwig (buf, fp)
E 6
I 6
drawwig (buf, fp, pic)
E 6
char *buf;
FILE *fp;
I 6
int pic;
E 6
{
D 4
    register int len = strlen(buf);
D 2
    register int i = 1;
E 2
I 2
    register int i = 2;
E 2
    register char *ptr = buf;
    float x[MAXPOINTS], y[MAXPOINTS];
E 4
I 4
    register int len = strlen(buf);	/* length of the string in "buf" */
D 6
    register int i = 2;			/* point list index */
E 6
I 6
    register int npts = 2;		/* point list index */
E 6
    register char *ptr = buf;		/* "walking" pointer into buf */
D 6
    float x[MAXPOINTS], y[MAXPOINTS];	/* point list */
E 6
I 6
    int x[MAXPOINTS], y[MAXPOINTS];	/* point list */
E 6
E 4

    while (*ptr == ' ') ptr++;		/* skip any leading spaces */
I 2
D 6
    x[1] = (float) hpos;	/* the curve starts at the */
    y[1] = (float) vpos;	/* current position */
E 6
I 6
    x[1] = hpos;		/* the curve starts at the */
    y[1] = vpos;		/* current position */
E 6

E 2
D 4
    while (*ptr != '\n') {		/* curve commands end with a "cr" */
D 2
	hmot((int) (x[i] = (float) atoi(ptr)));		/* convert text */
	while (isdigit(*++ptr));			/* to curve points */
	while (*++ptr == ' ');
	vmot((int) (y[i] = (float) atoi(ptr)));
E 2
I 2
	hmot(atoi(ptr));		/* convert to curve points */
E 4
I 4
    while (*ptr != '\n') {		/* curve commands end with a '\n' */
	hmot(atoi(ptr));		/* convert motion to curve points */
E 4
D 6
	x[i] = (float) hpos;		/* and remember them */
E 6
I 6
	x[npts] = hpos;			/* and remember them */
E 6
	while (isdigit(*++ptr));		/* skip number*/
	while (*++ptr == ' ');		/* skip spaces 'tween numbers */
	vmot(atoi(ptr));
D 6
	y[i] = (float) vpos;
E 6
I 6
	y[npts] = vpos;
E 6
E 2
	while (isdigit(*++ptr));
	while (*ptr == ' ') ptr++;
				/* if the amount we read wasn't the */
		 		/*    whole thing, read some more in */
	if (len - (ptr - buf) < 15 && *(buf + len - 1) != '\n') {
	    char *cop = buf;

	    while (*cop++ = *ptr++);	/* copy what's left to the beginning */
D 12
	    fgets ((cop - 1), len - (cop - buf), fp);
E 12
I 12
	    if (fgets ((cop - 1), len - (cop - buf), fp) == NULL)
		error(FATAL, "unexpected end of input");
E 12
	    ptr = buf;
	}
D 4

E 4
D 6
	if (i < MAXPOINTS - 1) i++;	/* if too many points, forget some */
E 6
I 6
	if (npts < MAXPOINTS - 1)	/* if too many points, forget some */
	    npts++;
E 6
    }
D 4

E 4
D 2
    HGCurve(x, y, i);		/* now, actually DO the curve */
E 2
I 2
D 6
    HGCurve(x, y, --i);		/* now, actually DO the curve */
E 6
I 6
    npts--;	/* npts must point to the last coordinate in x and y */
				/* now, actually DO the curve */
D 8
    if (pic)
	picurve(x, y, npts);
    else
	HGCurve(x, y, npts);
E 8
I 8
    if (output) {
D 16
	if (pic)
E 16
I 16
	if (pic > 0)
E 16
D 18
	    picurve(x, y, npts);
E 18
I 18
	    picurve(&x[0], &y[0], npts);
E 18
I 16
	else if (pic < 0)
D 18
	    polygon(x, y, npts);
E 18
I 18
	    polygon(&x[0], &y[0], npts);
E 18
E 16
	else
D 18
	    HGCurve(x, y, npts);
E 18
I 18
	    HGCurve(&x[0], &y[0], npts);
E 18
    }
E 8
E 6
E 2
}


I 6
/*----------------------------------------------------------------------------*
 | Routine:	drawthick (thickness)
 |
 | Results:	sets the variable "linethickness" to the given size.
 |		NO motion is involved.
 *----------------------------------------------------------------------------*/

drawthick(s)
D 7
int s
E 7
I 7
int s;
E 7
{
    linethickness = s;
}


/*----------------------------------------------------------------------------*
 | Routine:	drawstyle (style_bit_map)
 |
 | Results:	sets the variable "linmod" to the given bit map.
 |		NO motion is involved.
 *----------------------------------------------------------------------------*/

drawstyle(s)
D 7
int s
E 7
I 7
int s;
E 7
{
    linmod = s;
}


E 6
I 4
/*----------------------------------------------------------------------------
I 6
 * Routine:	picurve (xpoints, ypoints, num_of_points)
 *
 * Results:	Draws a curve delimited by (not through) the line segments
 *		traced by (xpoints, ypoints) point list.  This is the "Pic"
 *		style curve.
D 9
 *
 * Bugs:	does nothing yet....
E 9
 *----------------------------------------------------------------------------*/

picurve (x, y, npts)
D 18
int x[MAXPOINTS];
int y[MAXPOINTS];
E 18
I 18
register int *x;
register int *y;
E 18
int npts;
{
D 18
    register int i;		/* line segment traverser */
E 18
    register int nseg;		/* effective resolution for each curve */
D 18
    register float w;		/* position factor */
    register int xp;		/* current point (and intermediary) */
E 18
I 18
    register int xp;		/* current point (and temporary) */
E 18
    register int yp;
    int pxp, pyp;		/* previous point (to make lines from) */
D 18
    float t1, t2, t3;		/* calculation temps */
    int j;			/* inner curve segment traverser */
E 18
I 18
    int i;			/* inner curve segment traverser */
    double w;			/* position factor */
    double t1, t2, t3;		/* calculation temps */
E 18


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

    pxp = (x[0] + x[1]) / 2;		/* make the last point pointers */
    pyp = (y[0] + y[1]) / 2;		/* point to the start of the 1st line */

D 18
    for (i = 0; i < npts; i++) {	/* traverse the line segments */
	xp = x[i] - x[i+1];
	yp = y[i] - y[i+1];
E 18
I 18
    for (; npts--; x++, y++) {		/* traverse the line segments */
	xp = x[0] - x[1];
	yp = y[0] - y[1];
E 18
	nseg = (int) sqrt((double)(xp * xp + yp * yp));
D 18
	xp = x[i+1] - x[i+2];
	yp = y[i+1] - y[i+2];		/* "nseg" is the number of line */
E 18
I 18
	xp = x[1] - x[2];
	yp = y[1] - y[2];		/* "nseg" is the number of line */
E 18
					/* segments that will be drawn for */
					/* each curve segment.  ">> 3" is */
					/* dropping the resolution ( == / 8) */
	nseg = (nseg + (int) sqrt((double)(xp * xp + yp * yp))) >> 3;

D 18
	for (j = 1; j < nseg; j++) {
	    w = (float) j / (float) nseg;
E 18
I 18
	for (i = 1; i < nseg; i++) {
	    w = (double) i / (double) nseg;
#ifdef old_curve_calc
E 18
	    t1 = 0.5 * w * w;
	    w -= 0.5;
	    t2 = 0.75 - w * w ;
	    w -= 0.5;
	    t3 = 0.5 * w * w;
D 18
	    xp = t1 * x[i+2] + t2 * x[i+1] + t3 * x[i] + 0.5;
	    yp = t1 * y[i+2] + t2 * y[i+1] + t3 * y[i] + 0.5;

E 18
I 18
	    xp = t1 * x[2] + t2 * x[1] + t3 * x[0] + 0.5;
	    yp = t1 * y[2] + t2 * y[1] + t3 * y[0] + 0.5;
#else
	    t1 = w * w;
	    t3 = t1 + 1.0 - (w + w);
	    t2 = 2.0 - (t3 + t1);
	    xp = (((int) (t1 * x[2] + t2 * x[1] + t3 * x[0])) + 1) / 2;
	    yp = (((int) (t1 * y[2] + t2 * y[1] + t3 * y[0])) + 1) / 2;
#endif
E 18
	    HGtline(pxp, pyp, xp, yp);
	    pxp = xp;
	    pyp = yp;
	}
    }
}


/*----------------------------------------------------------------------------
E 6
 * Routine:	line (xstart, ystart, xend, yend)
 *
D 9
 * Results:	Draws a one-pixel wide line from (x0, y0) to
 *		(x1, y1) using point(x,y) to place the dots.
E 9
I 9
 * Results:	Draws a one-pixel wide line from (x0, y0) to (x1, y1)
 *		using point(x,y) to place the dots.  Line style
 *		is done in this routine by masking off unwanted dots.
E 9
 *----------------------------------------------------------------------------*/
E 4

line(x0, y0, x1, y1)
D 4
int x0, y0, x1, y1;

/* This routine is called to draw a line from the point at (x0, y0) to (x1, y1).
 * The line is drawn using a variation of 
 */

E 4
I 4
register int x0;
register int y0;
int x1;
int y1;
E 4
{
D 4
    int dx, dy;
    int xinc, yinc;
    int res1;
E 4
I 4
    register int dx;
    register int dy;
D 16
    register int res1;
E 4
    int res2;
E 16
I 16
    register int res;
    register int slope;
E 16
I 4
    int xinc;
    int yinc;
E 4
D 16
    int slope;
E 16

    xinc = 1;
    yinc = 1;
D 4
    if ((dx = x1-x0) < 0) 
    {
E 4
I 4
    if ((dx = x1-x0) < 0) {
E 4
        xinc = -1;
        dx = -dx;
    }
D 4
    if ((dy = y1-y0) < 0) 
    {
E 4
I 4
    if ((dy = y1-y0) < 0) {
E 4
        yinc = -1;
        dy = -dy;
    }
    slope = xinc*yinc;
D 16
    res1 = 0;
    res2 = 0;
    if (dx >= dy) 
E 16
I 16
    if (dx >= dy) {
	res = (dy >> 1) - (dx >> 1);
E 16
D 4
        while (x0 != x1) 
        {
E 4
I 4
        while (x0 != x1) {
E 4
D 16
            if((x0+slope*y0)&linmod) point(x0, y0);
D 4
            if (res1 > res2) 
            {
E 4
I 4
            if (res1 > res2) {
E 4
                res2 += dx - res1;
                res1 = 0;
E 16
I 16
            if ((x0+slope*y0)&linmod) point(x0, y0);
            if (res >= 0) {
                res -= dx;
E 16
                y0 += yinc;
            }
D 16
            res1 += dy;
E 16
I 16
            res += dy;
E 16
            x0 += xinc;
        } 
D 16
    else 
E 16
I 16
    } else {
	res = (dx >> 1) - (dy >> 1);
E 16
D 4
        while (y0 != y1) 
        {
E 4
I 4
        while (y0 != y1) {
E 4
D 16
            if((x0+slope*y0)&linmod) point(x0, y0);
D 4
            if (res1 > res2) 
            {
E 4
I 4
            if (res1 > res2) {
E 4
                res2 += dy - res1;
                res1 = 0;
E 16
I 16
            if ((x0+slope*y0)&linmod) point(x0, y0);
            if (res >= 0) {
                res -= dy;
E 16
                x0 += xinc;
            }
D 16
            res1 += dx;
E 16
I 16
            res += dx;
E 16
            y0 += yinc;
        }
I 16
    }
E 16
    if((x1+slope*y1)&linmod) point(x1, y1);
}


I 4
/*----------------------------------------------------------------------------
 * Routine:	HGArc (xcenter, ycenter, xstart, ystart, angle)
 *
 * Results:	This routine plots an arc centered about (cx, cy) counter
 *		clockwise starting from the point (px, py) through 'angle'
 *		degrees.  If angle is 0, a full circle is drawn.
 *		It does so by calling RoundEnd (fat point maker) for points
 *		along the circle with density depending on the circle's size.
 *----------------------------------------------------------------------------*/
E 4

HGArc(cx,cy,px,py,angle)
register int cx;
register int cy;
D 10
register int px;
register int py;
register int angle;
E 10
I 10
int px;
int py;
int angle;
E 10
D 4

D 2
/* This routine plots an arc centered about 'center' counter clockwise for
 * the point 'cpoint' through 'angle' degrees.  If angle is 0, a full circle
E 2
I 2
/* This routine plots an arc centered about (cx, cy) counter clockwise for
 * the point (px, py) through 'angle' degrees.  If angle is 0, a full circle
E 2
 * is drawn.
 */

E 4
{
D 10
    double xs, ys, resolution, epsilon, degreesperpoint, fullcircle;
    double t1, t2;
    int i, extent, nx, ny;
E 10
I 10
    double xs, ys, resolution, epsilon, fullcircle;
D 14
    int thick = linethickness / 2;
E 14
    register int nx;
    register int ny;
    register int extent;
E 10

    xs = px - cx;
    ys = py - cy;
D 2
    lastx = cx;
    lasty = cy;
E 2

/* calculate drawing parameters */

D 10
    t1 = log10(sqrt( xs * xs + ys * ys)) * log2_10;
    t1 = ceil(t1);
    resolution = pow(2.0, t1);
E 10
I 10
    resolution = log10(sqrt( xs * xs + ys * ys)) * log2_10;
    resolution = ceil(resolution);
    resolution = pow(2.0, resolution);
E 10
    epsilon = 1.0 / resolution;
    fullcircle = 2 * pi * resolution;
    fullcircle = ceil(fullcircle);
D 10
    degreesperpoint = 360.0 / fullcircle;
E 10

D 10
    if (angle == 0) extent = fullcircle;
    else extent = angle/degreesperpoint;
E 10
I 10
    if (angle == 0)
	extent = fullcircle;
    else
	extent = angle * fullcircle / 360.0;
E 10

D 10
    for (i=0; i<extent; ++i) {
E 10
I 10
    while (extent-- > 0) {
E 10
        xs += epsilon * ys;
D 10
        nx = (int) (xs + cx + 0.5);
E 10
I 10
        nx = cx + (int) (xs + 0.5);
E 10
        ys -= epsilon * xs;
D 10
        ny = (int) (ys + cy + 0.5);
        RoundEnd(nx, ny, (int) (linethickness/2), FALSE);
E 10
I 10
        ny = cy + (int) (ys + 0.5);
D 14
        RoundEnd(nx, ny, thick, FALSE);
E 14
I 14
        RoundEnd(nx, ny, linethickness, FALSE);
E 14
E 10
D 2
        lastx = nx;
        lasty = ny;
E 2
    }   /* end for */
}  /* end HGArc */


I 4
/*----------------------------------------------------------------------------
D 14
 * Routine:	RoundEnd (x, y, radius, filled_flag)
E 14
I 14
 * Routine:	RoundEnd (x, y, diameter, filled_flag)
E 14
 *
D 14
 * Results:	Plots a filled (if requested) circle of the specified radius
E 14
I 14
 * Results:	Plots a filled (if requested) circle of the specified diameter
E 14
 *		centered about (x, y).
 *----------------------------------------------------------------------------*/

E 4
D 14
RoundEnd(x, y, radius, filled)
E 14
I 14
RoundEnd(x, y, diameter, filled)
E 14
D 10
int x, y, radius;
E 10
I 10
register int x;
register int y;
D 14
int radius;
E 14
I 14
int diameter;
E 14
E 10
D 4
int filled;                /* indicates whether the circle is filled */
E 4
I 4
int filled;
E 4
D 10

E 10
D 4
/* This routine plots a filled circle of the specified radius centered 
 * about (x, y).
 */

E 4
{
D 10
    double xs, ys, epsilon;
    int i, j, k, extent, nx, ny;
    int cx, cy;
E 10
I 10
    double xs, ys;	/* floating point distance form center of circle */
    double epsilon;	/* "resolution" of the step around circle */
D 14
    register int cx;	/* center of circle */
    register int cy;
E 14
I 14
    register int cy;	/* to index up from center of circle */
E 14
    register int nx;	/* integer distance from center */
    register int ny;
I 14
    register int arc;	/* counts how far around the circle to go */
E 14
E 10

D 4
    if (radius < 1)    /* too small to notice */
    {
E 4
I 4

D 14
    if (radius < 1) {	/* too small to notice */
E 14
I 14
    if (diameter < 2) {	/* too small to notice */
E 14
E 4
        point(x, y);
        return;
    }
I 4

E 4
    xs = 0;
D 14
    ys = radius;
    epsilon = 1.0 / radius;
E 14
I 14
    ys = (double) (diameter - 1) / 2.0;
    epsilon = 1.0 / ys;
    arc = (pi / 2.0) * ys;
    if (arc < 4) {		/* if too small, make it bigger */
	arc += arc;		/*   to try and fill in more.   */
	epsilon /= 2.0;
    }
E 14
D 4
    extent = pi * radius / 2;    /* 1/4 the circumference */
E 4
I 4
D 10
    extent = pi * radius / 2.0;    /* 1/4 the circumference */
E 10
E 4

        /* Calculate the trajectory of the circle for 1/4 the circumference
         * and mirror appropriately to get the other three quadrants.
         */

D 10
    point(x, y+((int) ys));    /* take care if end of arc missed by */
    point(x, y-((int) ys));    /* below formulation                 */
    for (i=0; i<extent; ++i)
    {
             /* generate circumference */
        xs += epsilon * ys;
        nx = (int) (xs + x + 0.5);
        if (nx < x) nx = x;  /* 1st quadrant, should be positive */
        ys -= epsilon * xs;
        ny = (int) (ys + y + 0.5);
        if (ny < y) ny = y;  /* 1st quadrant, should be positive */
E 10
I 10
D 14
    nx = x;			/* must start out the x and y for first */
    ny = y + radius;		/*   painting going on in while loop */
E 14
I 14
    nx = 0;			/* must start out the x and y for first */
    ny = (int) (ys + 0.5);	/*   painting in while loop */
E 14
E 10

D 4
        if (filled == TRUE)
        {       /* fill from center */
E 4
I 4
D 10
        if (filled == TRUE) {	/* fill from center */
E 10
I 10
D 12
    while (ny >= 0)
E 12
I 12
D 14
    while (ny >= y)
E 12
    {
E 14
I 14
    while (arc-- >= 0) {
E 14
        if (filled) {		/* fill from center */
E 10
E 4
D 14
            cx = x;
            cy = y;
E 14
I 14
            cy = 0;
E 14
D 4
        }
        else
        {       /* fill from perimeter only (no fill) */
E 4
I 4
        } else {		/* fill from perimeter only (no fill) */
E 4
D 14
            cx = nx;
E 14
            cy = ny;
        }
D 4
        for (j=cx; j<=nx; ++j)
        {
            for (k=cy; k<=ny; ++k)
            {
E 4
I 4
D 10
        for (j=cx; j<=nx; ++j) {
            for (k=cy; k<=ny; ++k) {
E 4
                point(j, k);
                point(j, 2*y-k);
                point(2*x-j, k);
                point(2*x-j, 2*y-k);
E 10
I 10
D 14
        while (cx <= nx) {
            while (cy <= ny) {
                point(cx, cy);
                point(cx, 2*y-cy);
                point(2*x-cx, cy);
                point(2*x-cx, 2*y-cy);
		cy++;
E 10
            }  /* end for k */
I 10
	    cx++;
E 10
        }  /* end for j */;
E 14
I 14
	while (cy <= ny) {
	    point(nx + x, cy + y);
	    point(nx + x, y - cy);
	    point(x - nx, cy + y);
	    point(x - nx, y - cy);
	    cy++;
	}  /* end while cy */
E 14
I 10
				 /* generate circumference */
D 14
        xs += epsilon * ys;
        nx = x + (int) (xs + 0.5);
        ys -= epsilon * xs;
        ny = y + (int) (ys + 0.5);
E 10
    }  /* end for i */;
E 14
I 14
        nx = (int) ((xs += epsilon * ys) + 0.5);
        ny = (int) ((ys -= epsilon * xs) + 0.5);
    }  /* end while arc */;
E 14
}  /* end RoundEnd */;


I 4
/*----------------------------------------------------------------------------
 * Routine:	Paramaterize (xpoints, ypoints, hparams, num_points)
 *
 * Results:	This routine calculates parameteric values for use in
 *		calculating curves.  The parametric values are returned
 *		in the array h.  The values are an approximation of
 *		cumulative arc lengths of the curve (uses cord length).
 *		For additional information, see paper cited below.
 *----------------------------------------------------------------------------*/
E 4

static Paramaterize(x, y, h, n)
D 4
float x[MAXPOINTS], y[MAXPOINTS], h[MAXPOINTS];
E 4
I 4
D 6
float x[MAXPOINTS];
float y[MAXPOINTS];
E 6
I 6
D 18
int x[MAXPOINTS];
int y[MAXPOINTS];
E 18
I 18
int *x;
int *y;
E 18
E 6
float h[MAXPOINTS];
E 4
int n;
D 4
/*     This routine calculates parameteric values for use in calculating
 * curves.  The parametric values are returned in the array u.  The values
 * are an approximation of cumulative arc lengths of the curve (uses cord
 * length).  For additional information, see paper cited below.
 */

E 4
{
D 6
	int i,j;
E 6
I 6
	register int dx;
	register int dy;
	register int i;
	register int j;
E 6
	float u[MAXPOINTS];

D 4
	for (i=1; i<=n; ++i)
	{
		u[i] = 0;
		for (j=1; j<i; j++)
		{
			u[i] += sqrt(pow((double) (x[j+1] - x[j]),(double) 2.0)
			         + pow((double) (y[j+1] - y[j]), (double) 2.0));
		}
E 4
I 4

	for (i=1; i<=n; ++i) {
	    u[i] = 0;
	    for (j=1; j<i; j++) {
D 6
		u[i] += sqrt (pow((double) (x[j+1] - x[j]),(double) 2.0)
			      + pow((double) (y[j+1] - y[j]), (double) 2.0));
E 6
I 6
		dx = x[j+1] - x[j];
		dy = y[j+1] - y[j];
		u[i] += sqrt ((double) (dx * dx + dy * dy));
E 6
	    }
E 4
	}
D 4
	for (i=1; i<n; ++i)
		h[i] = u[i+1] - u[i];
E 4
I 4
	for (i=1; i<n; ++i)  h[i] = u[i+1] - u[i];
E 4
}  /* end Paramaterize */

I 4

/*----------------------------------------------------------------------------
 * Routine:	PeriodicSpline (h, z, dz, d2z, d3z, npoints)
 *
 * Results:	This routine solves for the cubic polynomial to fit a
 *		spline curve to the the points  specified by the list
 *		of values.  The Curve generated is periodic.  The algorithms
 *		for this curve are from the "Spline Curve Techniques" paper
 *		cited below.
 *----------------------------------------------------------------------------*/

E 4
static PeriodicSpline(h, z, dz, d2z, d3z, npoints)
D 6
float h[MAXPOINTS], z[MAXPOINTS];	/* Point list and paramaterization  */
E 6
I 6
float h[MAXPOINTS];		/* paramaterization  */
D 18
int z[MAXPOINTS];		/* point list */
E 18
I 18
int *z;				/* point list */
E 18
E 6
float dz[MAXPOINTS];			/* to return the 1st derivative */
float d2z[MAXPOINTS], d3z[MAXPOINTS];	/* 2nd and 3rd derivatives */
int npoints;				/* number of valid points */
D 4
/*
 *     This routine solves for the cubic polynomial to fit a spline
 * curve to the the points  specified by the list of values.
 * The Curve generated is periodic.  The alogrithms for this 
 * curve are from the "Spline Curve Techniques" paper cited below.
 */

E 4
{
	float d[MAXPOINTS]; 
	float deltaz[MAXPOINTS], a[MAXPOINTS], b[MAXPOINTS];
	float c[MAXPOINTS], r[MAXPOINTS], s[MAXPOINTS];
	int i;

D 4
	            /* step 1 */
	for (i=1; i<npoints; ++i)
	{
		if (h[i] != 0)
			deltaz[i] = (z[i+1] - z[i]) / h[i];
		else
			deltaz[i] = 0;
E 4
I 4
						/* step 1 */
	for (i=1; i<npoints; ++i) {
D 6
	    deltaz[i] = h[i] ? (z[i+1] - z[i]) / h[i] : 0;
E 6
I 6
	    deltaz[i] = h[i] ? ((double) (z[i+1] - z[i])) / h[i] : 0;
E 6
E 4
	}
	h[0] = h[npoints-1];
	deltaz[0] = deltaz[npoints-1];

D 4
	            /* step 2 */
	for (i=1; i<npoints-1; ++i)
	{
		d[i] = deltaz[i+1] - deltaz[i];
E 4
I 4
						/* step 2 */
	for (i=1; i<npoints-1; ++i) {
	    d[i] = deltaz[i+1] - deltaz[i];
E 4
	}
	d[0] = deltaz[1] - deltaz[0];

D 4
	            /* step 3a */
E 4
I 4
						/* step 3a */
E 4
	a[1] = 2 * (h[0] + h[1]);
	b[1] = d[0];
	c[1] = h[0];
D 4
	for (i=2; i<npoints-1; ++i)
	{
		a[i] = 2 * (h[i-1] + h[i]) - pow((double) h[i-1], (double) 2.0)
		            / a[i-1];
		b[i] = d[i-1] - h[i-1] * b[i-1]/a[i-1];
		c[i] = -h[i-1] * c[i-1]/a[i-1];
E 4
I 4
	for (i=2; i<npoints-1; ++i) {
	    a[i] = 2*(h[i-1]+h[i]) - pow ((double) h[i-1],(double)2.0) / a[i-1];
	    b[i] = d[i-1] - h[i-1] * b[i-1]/a[i-1];
	    c[i] = -h[i-1] * c[i-1]/a[i-1];
E 4
	}

D 4
	            /* step 3b */
E 4
I 4
						/* step 3b */
E 4
	r[npoints-1] = 1;
	s[npoints-1] = 0;
D 4
	for (i=npoints-2; i>0; --i)
	{
		r[i] = -(h[i] * r[i+1] + c[i])/a[i];
		s[i] = (6 * b[i] - h[i] * s[i+1])/a[i];
E 4
I 4
	for (i=npoints-2; i>0; --i) {
	    r[i] = -(h[i] * r[i+1] + c[i])/a[i];
	    s[i] = (6 * b[i] - h[i] * s[i+1])/a[i];
E 4
	}

D 4
	            /* step 4 */
E 4
I 4
						/* step 4 */
E 4
	d2z[npoints-1] = (6 * d[npoints-2] - h[0] * s[1] 
	                   - h[npoints-1] * s[npoints-2]) 
	                 / (h[0] * r[1] + h[npoints-1] * r[npoints-2] 
	                    + 2 * (h[npoints-2] + h[0]));
D 4
	for (i=1; i<npoints-1; ++i)
	{
		d2z[i] = r[i] * d2z[npoints-1] + s[i];
E 4
I 4
	for (i=1; i<npoints-1; ++i) {
	    d2z[i] = r[i] * d2z[npoints-1] + s[i];
E 4
	}
	d2z[npoints] = d2z[1];

D 4
	            /* step 5 */
	for (i=1; i<npoints; ++i)
	{
		dz[i] = deltaz[i] - h[i] * (2 * d2z[i] + d2z[i+1])/6;
		if (h[i] != 0)
			d3z[i] = (d2z[i+1] - d2z[i])/h[i];
		else
			d3z[i] = 0;
E 4
I 4
						/* step 5 */
	for (i=1; i<npoints; ++i) {
	    dz[i] = deltaz[i] - h[i] * (2 * d2z[i] + d2z[i+1])/6;
	    d3z[i] = h[i] ? (d2z[i+1] - d2z[i])/h[i] : 0;
E 4
	}
}  /* end PeriodicSpline */


I 4
/*----------------------------------------------------------------------------
 * Routine:	NaturalEndSpline (h, z, dz, d2z, d3z, npoints)
 *
 * Results:	This routine solves for the cubic polynomial to fit a
 *		spline curve the the points  specified by the list of
 *		values.  The alogrithms for this curve are from the
 *		"Spline Curve Techniques" paper cited below.
 *----------------------------------------------------------------------------*/

E 4
static NaturalEndSpline(h, z, dz, d2z, d3z, npoints)
D 6
float h[MAXPOINTS], z[MAXPOINTS];	/* Point list and parameterization */
E 6
I 6
float h[MAXPOINTS];		/* parameterization */
D 18
int z[MAXPOINTS];		/* Point list */
E 18
I 18
int *z;				/* Point list */
E 18
E 6
float dz[MAXPOINTS];			/* to return the 1st derivative */
float d2z[MAXPOINTS], d3z[MAXPOINTS];	/* 2nd and 3rd derivatives */
int npoints;				/* number of valid points */
D 4
/*
 *     This routine solves for the cubic polynomial to fit a spline
 * curve the the points  specified by the list of values.  The alogrithms for
 * this curve are from the "Spline Curve Techniques" paper cited below.
 */

E 4
{
	float d[MAXPOINTS];
	float deltaz[MAXPOINTS], a[MAXPOINTS], b[MAXPOINTS];
	int i;

D 4
	            /* step 1 */
	for (i=1; i<npoints; ++i)
	{
		if (h[i] != 0)
			deltaz[i] = (z[i+1] - z[i]) / h[i];
		else
			deltaz[i] = 0;
E 4
I 4
						/* step 1 */
	for (i=1; i<npoints; ++i) {
D 6
	    deltaz[i] = h[i] ? (z[i+1] - z[i]) / h[i] : 0;
E 6
I 6
	    deltaz[i] = h[i] ? ((double) (z[i+1] - z[i])) / h[i] : 0;
E 6
E 4
	}
	deltaz[0] = deltaz[npoints-1];

D 4
	            /* step 2 */
	for (i=1; i<npoints-1; ++i)
	{
		d[i] = deltaz[i+1] - deltaz[i];
E 4
I 4
						/* step 2 */
	for (i=1; i<npoints-1; ++i) {
	    d[i] = deltaz[i+1] - deltaz[i];
E 4
	}
	d[0] = deltaz[1] - deltaz[0];

D 4
	            /* step 3 */
E 4
I 4
						/* step 3 */
E 4
	a[0] = 2 * (h[2] + h[1]);
	b[0] = d[1];
D 4
	for (i=1; i<npoints-2; ++i)
	{
		a[i] = 2 * (h[i+1] + h[i+2]) - pow((double) h[i+1],(double) 2.0)
		             / a[i-1];
		b[i] = d[i+1] - h[i+1] * b[i-1]/a[i-1];
E 4
I 4
	for (i=1; i<npoints-2; ++i) {
	    a[i] = 2*(h[i+1]+h[i+2]) - pow((double) h[i+1],(double) 2.0)/a[i-1];
	    b[i] = d[i+1] - h[i+1] * b[i-1]/a[i-1];
E 4
	}

D 4
	            /* step 4 */
E 4
I 4
						/* step 4 */
E 4
	d2z[npoints] = d2z[1] = 0;
D 4
	for (i=npoints-1; i>1; --i)
	{
		d2z[i] = (6 * b[i-2] - h[i] *d2z[i+1])/a[i-2];
E 4
I 4
	for (i=npoints-1; i>1; --i) {
	    d2z[i] = (6 * b[i-2] - h[i] *d2z[i+1])/a[i-2];
E 4
	}

D 4
	            /* step 5 */
	for (i=1; i<npoints; ++i)
	{
		dz[i] = deltaz[i] - h[i] * (2 * d2z[i] + d2z[i+1])/6;
		if (h[i] != 0)
			d3z[i] = (d2z[i+1] - d2z[i])/h[i];
		else
			d3z[i] = 0;
E 4
I 4
						/* step 5 */
	for (i=1; i<npoints; ++i) {
	    dz[i] = deltaz[i] - h[i] * (2 * d2z[i] + d2z[i+1])/6;
	    d3z[i] = h[i] ? (d2z[i+1] - d2z[i])/h[i] : 0;
E 4
	}
}  /* end NaturalEndSpline */


I 4
/*----------------------------------------------------------------------------
 * Routine:	HGCurve(xpoints, ypoints, num_points)
 *
 * Results:	This routine generates a smooth curve through a set of points.
 *		The method used is the parametric spline curve on unit knot
 *		mesh described in "Spline Curve Techniques" by Patrick
 *		Baudelaire, Robert Flegal, and Robert Sproull -- Xerox Parc.
 *----------------------------------------------------------------------------*/

E 4
#define PointsPerInterval 32

HGCurve(x, y, numpoints)
D 4
float x[MAXPOINTS], y[MAXPOINTS];
E 4
I 4
D 6
float x[MAXPOINTS];
float y[MAXPOINTS];
E 6
I 6
D 18
int x[MAXPOINTS];
int y[MAXPOINTS];
E 18
I 18
int *x;
int *y;
E 18
E 6
E 4
int numpoints;
D 4

/*
 *    This routine generates a smooth curve through a set of points.  The 
 * method used is the parametric spline curve on unit knot mesh described
 * in "Spline Curve Techniques" by Patrick Baudelaire, Robert Flegal, and 
 * Robert Sproull -- Xerox Parc.
 */
E 4
{
	float h[MAXPOINTS], dx[MAXPOINTS], dy[MAXPOINTS];
	float d2x[MAXPOINTS], d2y[MAXPOINTS], d3x[MAXPOINTS], d3y[MAXPOINTS];
D 4
	float t, t2, t3, xinter, yinter;
	int i, j, k, lx, ly, nx, ny;
E 4
I 4
	float t, t2, t3;
	register int j;
	register int k;
	register int nx;
	register int ny;
D 5
	int lx, ly,;
E 5
I 5
	int lx, ly;
E 5
E 4


D 2
	lx = (int) x[0];
	ly = (int) y[0];
E 2
I 2
D 6
	lx = (int) x[1];
	ly = (int) y[1];
E 6
I 6
	lx = x[1];
	ly = y[1];
E 6
E 2

	     /* Solve for derivatives of the curve at each point 
              * separately for x and y (parametric).
	      */
	Paramaterize(x, y, h, numpoints);
							/* closed curve */
D 2
	if ((x[0] == x[numpoints]) && (y[0] == y[numpoints])) {
E 2
I 2
	if ((x[1] == x[numpoints]) && (y[1] == y[numpoints])) {
E 2
D 4
		PeriodicSpline(h, x, dx, d2x, d3x, numpoints);
		PeriodicSpline(h, y, dy, d2y, d3y, numpoints);
E 4
I 4
	    PeriodicSpline(h, x, dx, d2x, d3x, numpoints);
	    PeriodicSpline(h, y, dy, d2y, d3y, numpoints);
E 4
	} else {
D 4
		NaturalEndSpline(h, x, dx, d2x, d3x, numpoints);
		NaturalEndSpline(h, y, dy, d2y, d3y, numpoints);
E 4
I 4
	    NaturalEndSpline(h, x, dx, d2x, d3x, numpoints);
	    NaturalEndSpline(h, y, dy, d2y, d3y, numpoints);
E 4
	}

	      /* generate the curve using the above information and 
	       * PointsPerInterval vectors between each specified knot.
	       */

D 4
	for (j=1; j<numpoints; ++j)
	{
		if ((x[j] == x[j+1]) && (y[j] == y[j+1])) continue;
		for (k=0; k<=PointsPerInterval; ++k)
		{
			t = (float) k * h[j] / (float) PointsPerInterval;
			t2 = t * t;
			t3 = t * t * t;
			xinter = x[j] + t * dx[j] + t2 * d2x[j]/2
			       + t3 * d3x[j]/6;
			nx = (int) xinter;
			yinter = y[j] + t * dy[j] + t2 * d2y[j]/2
			       + t3 * d3y[j]/6;
			ny = (int) yinter;
			HGtline(lx, ly, nx, ny);
			lx = nx;
			ly = ny;
		}  /* end for k */
E 4
I 4
	for (j=1; j<numpoints; ++j) {
	    if ((x[j] == x[j+1]) && (y[j] == y[j+1])) continue;
	    for (k=0; k<=PointsPerInterval; ++k) {
		t = (float) k * h[j] / (float) PointsPerInterval;
		t2 = t * t;
		t3 = t * t * t;
D 6
		nx = (int) (x[j] + t * dx[j] + t2 * d2x[j]/2 + t3 * d3x[j]/6);
		ny = (int) (y[j] + t * dy[j] + t2 * d2y[j]/2 + t3 * d3y[j]/6);
E 6
I 6
		nx = x[j] + (int) (t * dx[j] + t2 * d2x[j]/2 + t3 * d3x[j]/6);
		ny = y[j] + (int) (t * dy[j] + t2 * d2y[j]/2 + t3 * d3y[j]/6);
E 6
		HGtline(lx, ly, nx, ny);
		lx = nx;
		ly = ny;
	    }  /* end for k */
E 4
	}  /* end for j */
}  /* end HGCurve */


I 4
/*----------------------------------------------------------------------------
 * Routine:	HGtline(xstart, ystart, xend, yend)
 *
 * Results:	Draws a line of proper thickness by calling "line" numerous
 *		times until the desired thickness is reached.
 *----------------------------------------------------------------------------*/
E 4

HGtline(x0, y0, x1, y1)
register int x0;
register int y0;
D 4
register int x1;
register int y1;
/*
 *      This routine calls line repeatedly until the line is 
 * of the proper thickness.
 */

E 4
I 4
int x1;
int y1;
E 4
{
I 4
        register int xs;
	register int xe;
	register int ys;
	register int ye;
E 4
D 14
        double morelen, theta, wx, wy, xx, xy;
E 14
I 14
        double theta, wx, wy, xx, xy;
E 14
D 4
        int xs, xe, ys, ye;
E 4
        int addln, j, xdir, ydir, dx, dy;

I 4

E 4
        xdir = ydir = 1;
D 4
        dx = x1 - x0;   /* calculate direction to move to  */
        dy = y1 - y0;   /* move to draw additional lines if needed */
        if (dx < 0 )       /* for extra thickness */
        {
E 4
I 4
        dx = x1 - x0;		/* calculate direction to move to  */
        dy = y1 - y0;		/* move to draw additional lines if needed */
        if (dx < 0 ) {		/* for extra thickness */
E 4
            dx = -dx;
            xdir = -1;
        }
D 4
        if (dy < 0 )
        {
E 4
I 4
        if (dy < 0 ) {
E 4
            dy = -dy;
            ydir = -1;
        }

D 14
        morelen = linethickness / 2;
	addln = (int) morelen;
D 4
        RoundEnd(x0, y0, (int) morelen, TRUE);    /* add rounded end */
        for (j=(-addln); j<=addln; ++j)
        {
                if (dy == 0) 
                {
                        xs = x0;
                        xe = x1;
                        ys = ye = y0 + j;
                }
                if (dx == 0)
                {
                       ys = y0;
                       ye = y1;
                       xs = xe = x0 + j;
                }
                if ((dx != 0) && (dy != 0))
                {
                       theta =  pi / 2.0 - atan( ((double) dx)/((double) dy) );
                       wx = j * sin(theta);
                       wy = j * cos(theta);
                       xs = x0 + wx * xdir;
                       ys = y0 - wy * ydir;
                       xe = x1 + wx * xdir;
                       ye = y1 - wy * ydir;
                }
                line(xs, ys, xe, ye);
E 4
I 4
        RoundEnd (x0, y0, (int) morelen, TRUE);    /* add rounded end */
E 14
I 14
	addln = linethickness / 2;
        RoundEnd (x0, y0, linethickness, TRUE);    /* add rounded end */
E 14

        for (j=(-addln); j<=addln; ++j) {
	    if (dy == 0) {
		xs = x0;
		xe = x1;
		ys = ye = y0 + j;
	    }
	    if (dx == 0) {
		ys = y0;
		ye = y1;
		xs = xe = x0 + j;
	    }
	    if ((dx != 0) && (dy != 0)) {
		theta =  pi / 2.0 - atan( ((double) dx)/((double) dy) );
		wx = j * sin(theta);
		wy = j * cos(theta);
D 16
		xs = x0 + wx * xdir;
		ys = y0 - wy * ydir;
		xe = x1 + wx * xdir;
		ye = y1 - wy * ydir;
E 16
I 16
		xs = x0 + (int) (wx * xdir + 0.4);
		ys = y0 - (int) (wy * ydir + 0.4);
		xe = x1 + (int) (wx * xdir + 0.4);
		ye = y1 - (int) (wy * ydir + 0.4);
E 16
	    }
	    line(xs, ys, xe, ye);
E 4
        }  /* end for */
I 4

E 4
D 14
        RoundEnd(x1, y1, (int) morelen, TRUE);    /* add rounded end */
E 14
I 14
        RoundEnd(x1, y1, linethickness, TRUE);    /* add rounded end */
E 14
}  /* end HGtline */
E 1
