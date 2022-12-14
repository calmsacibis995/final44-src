/*	%M%	(Berkeley)	%I%	%E%
 *
 *	This file contains the functions for producing the graphics
 *   images in the sun driver for ditroff.
 */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "fixpoint.h"


#define TRUE	1
#define FALSE	0
				/* imports from dver.c */
#define  hmot(n)	hpos += n;
#define  vmot(n)	vpos += n;
#define  vgoto(n)	vpos = n;

extern int hpos;
extern int vpos;
extern int output;
extern point();
extern int scale();

#define MAXPOINTS 200	/* number of points legal for a curve */

#define SOLID -1	/* line styles:  these are used as bit masks to */
#define DOTTED 004	/* create the right style lines. */
#define DASHED 020
#define DOTDASHED 024
#define LONGDASHED 074
				/* constants... */
#define  pi		3.14159265358979324


int	linethickness = 1;	/* number of pixels wide to make lines */
int	linmod = SOLID;		/* type of line (SOLID, DOTTED, DASHED...) */



/*----------------------------------------------------------------------------
 * Routine:	drawline (horizontal_motion, vertical_motion)
 *
 * Results:	Draws a line of "linethickness" width and "linmod" style
 *		from current (hpos, vpos) to (hpos + dh, vpos + dv).
 *
 * Side Efct:	Resulting position is at end of line (hpos + dh, vpos + dv)
 *----------------------------------------------------------------------------*/

drawline(dh, dv)
register int dh;
register int dv;
{
    if (output) HGtline (hpos, vpos, hpos + dh, vpos + dv);
    hmot (dh);					/* new position is at */
    vmot (dv);					/* the end of the line */
}


/*----------------------------------------------------------------------------
 * Routine:	drawcirc (diameter)
 *
 * Results:	Draws a circle with leftmost point at current (hpos, vpos)
 *		with the given diameter d.  Does a thick line by calling
 *		RoundEnd many times with varying radii.
 *
 * Side Efct:	Resulting position is at (hpos + diameter, vpos)
 *----------------------------------------------------------------------------*/

drawcirc(d)
int d;
{
    register int delta_rad;
    register int limit;
    register int radius;


    if (output) {
	radius = scale(d) / 2;
	delta_rad = radius - linethickness / 2;
	limit = radius + (linethickness - 1) / 2;
	while (delta_rad <= limit) {
	    RoundEnd (scale(hpos)+radius, scale(vpos), delta_rad, FALSE);
	    delta_rad++;
	}
    }

    hmot (d);
}


/*----------------------------------------------------------------------------
 * Routine:	drawellip (horizontal_diameter, vertical_diameter)
 *
 * Results:	Draws regular ellipses given the major "diameters."  It does
 *		so using a modified circle algorithm (see RoundEnd) that
 *		increments x and y proportionally to their axes.
 *
 * Side Efct:	Resulting position is at (hpos + hd, vpos).
 *----------------------------------------------------------------------------*/

drawellip(hd, vd)
int hd;
int vd;
{
    fixed xs, ys, xepsilon, yepsilon;
    int thick;
    register int basex;
    register int basey;
    register int x;
    register int y;


    basex = scale(hpos + (hd >> 1));	/* bases == coordinates of center */
    hmot(hd);				/* horizontal motion (hpos should */
    basey = scale(vpos);		/*   NOT be used after this) */
					/* hd and vd are radii, not diameters */
    if ((hd=scale(hd >> 1)) < 1) hd++;	/* neither diameter can be zero. */
    if ((vd=scale(vd >> 1)) < 1) vd++;	/*   hd changed!! no hmot after this */
    ys = ffix(vd);			/* start at top of the ellipse */
    xs = ffix(0);			/*   (y = 1/2 diameter, x = 0) */

    if ((thick = vd) > hd) thick = hd;
    xepsilon = ffixd((double) thick / (double) (vd * vd));
    yepsilon = ffixd((double) thick / (double) (hd * hd));

		/* Calculate trajectory of the ellipse for 1/4	*/
		/* the circumference (while ys is non-negative)	*/
		/* and mirror to get the other three quadrants.	*/

    thick = linethickness / 2;
    if (thick) {		/* more than one pixel thick */
	RoundEnd(basex, fintr(ys) + basey, thick, 0);
	RoundEnd(basex, basey - fintr(ys), thick, 0);
	while (ys >= 0) {
	    xs += fmult(xepsilon, ys);	/* generate circumference */
	    ys -= fmult(yepsilon, xs);
	    x = fintr(xs);
	    y = fintr(ys);
	    RoundEnd(x + basex, y + basey, thick, 0);
	    RoundEnd(x + basex, basey - y, thick, 0);
	    RoundEnd(basex - x, y + basey, thick, 0);
	    RoundEnd(basex - x, basey - y, thick, 0);
	}
    } else {		/* do the perimeter only (no fill) */
	point(basex, fintr(ys) + basey);
	point(basex, basey - fintr(ys));
	while (ys >= 0) {
	    xs += fmult(xepsilon, ys);	/* generate circumference */
	    ys -= fmult(yepsilon, xs);
	    x = fintr(xs);
	    y = fintr(ys);
	    point(x + basex, y + basey);
	    point(x + basex, basey - y);
	    point(basex - x, y + basey);
	    point(basex - x, basey - y);
        }
    }
}


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

    if (output) HGArc(hpos + cdh, vpos + cdv, hpos, vpos, (int) angle);
    hmot(cdh + pdh);
    vmot(cdv + pdv);
}


/*----------------------------------------------------------------------------
 * Routine:	drawwig (character_buffer, file_pointer, type_flag)
 *
 * Results:	Given the starting position, the motion list in buf, and any
 *		extra characters from fp (terminated by a \n), drawwig sets
 *		up a point list to make a spline from.  If "pic" is set picurve
 *		is called to draw the curve in pic style; else it calls HGCurve
 *		for the gremlin-style curve.
 *
 * Side Efct:	Resulting position is reached from adding successive motions
 *		to the current position.
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
	    fgets ((cop - 1), len - (cop - buf), fp);
	    ptr = buf;
	}
	if (npts < MAXPOINTS - 1)	/* if too many points, forget some */
	    npts++;
    }
    npts--;	/* npts must point to the last coordinate in x and y */
				/* now, actually DO the curve */
    if (output) {
	if (pic)
	    picurve(x, y, npts);
	else
	    HGCurve(x, y, npts);
    }
}


/*----------------------------------------------------------------------------*
 | Routine:	drawthick (thickness)
 |
 | Results:	sets the variable "linethickness" to the given size.
 |		NO motion is involved.
 *----------------------------------------------------------------------------*/

drawthick(s)
int s;
{
    if ((linethickness = scale(s)) < 1) linethickness = 1;
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
}


/*----------------------------------------------------------------------------
 * Routine:	picurve (xpoints, ypoints, num_of_points)
 *
 * Results:	Draws a curve delimited by (not through) the line segments
 *		traced by (xpoints, ypoints) point list.  This is the "Pic"
 *		style curve.
 *----------------------------------------------------------------------------*/

picurve (x, y, npts)
int x[MAXPOINTS];
int y[MAXPOINTS];
int npts;
{
    register int i;		/* line segment traverser */
    register fixed nseg;	/* effective resolution for each curve */
    register fixed w;		/* position factor */
    register int xp;		/* current point (and intermediary) */
    register int yp;
    int pxp, pyp;		/* previous point (to make lines from) */
    fixed t1, t2, t3;		/* calculation temps */
    fixed j;			/* inner curve segment traverser */


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

    for (i = 0; i < npts; i++) {	/* traverse the line segments */
	xp = x[i] - x[i+1];
	yp = y[i] - y[i+1];
	nseg = ffixd(sqrt((double)(xp * xp + yp * yp)) / (20.0));
	xp = x[i+1] - x[i+2];
	yp = y[i+1] - y[i+2];		/* "nseg" is the number of line */
					/* segments that will be drawn for */
					/* each curve segment.  The division */
					/* is there to get better performace */
					/* by sacrificing resolution */
	nseg += ffixd(sqrt((double)(xp * xp + yp * yp)) / (20.0));

	for (j = ffix(1); j < nseg; j += ffix(1)) {
	    w = fdiv(j, nseg);
	    t1 = fmult(ffixd(0.5), fmult(w, w));
	    w -= ffixd(0.5);
	    t2 = ffixd(0.75) - fmult(w, w);
	    w -= ffixd(0.5);
	    t3 = fmult(ffixd(0.5), fmult(w, w));
	    xp = fintr(fmult(t1, ffix(x[i+2]))
			+ fmult(t2, ffix(x[i+1])) + fmult(t3, ffix(x[i])));
	    yp = fintr(fmult(t1, ffix(y[i+2]))
			+ fmult(t2, ffix(y[i+1])) + fmult(t3, ffix(y[i])));
	    HGtline(pxp, pyp, xp, yp);
	    pxp = xp;
	    pyp = yp;
	}
    }
}


/*----------------------------------------------------------------------------
 * Routine:	HGtline(xstart, ystart, xend, yend)
 *
 * Results:	Draws a line of proper thickness (specified in linethickness).
 *		Scales its points before doing the line - NO scaling should
 *		be done before calling this routine.
 *----------------------------------------------------------------------------*/


HGtline(xs, ys, xe, ye)
{
    register int x0;	/* starting point and line-walking registers */
    register int y0;
    int dx;		/* parameters in the line calculations */
    int dy;
    register int res;
    int xinc;
    int yinc;
    int x1;		/* end-point of the line */
    int y1;
    int radius;
    int top;		/* how much to bleed line in "up" (left) direction */
    int bottom;		/* how much to bleed line in "down" (right) direction */
    int stop1;		/* place to stop making circles at start of line */
    int stop2;		/* place to start making circles at end of line */
    int halfstop;	/* distance tween stop1 and stop3 */
    int stop3;		/* midpoint `tween making circles and lines */
    register int i;	/* line-bleeding carrier */


    x0 = scale(xs);	/* convert endpoints to SUN coordinates */
    y0 = scale(ys);
    x1 = scale(xe);
    y1 = scale(ye);

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

    radius = (linethickness - 1) / 2;
    RoundEnd(x0, y0, radius, TRUE);	/* add ends of line */
    RoundEnd(x1, y1, radius, TRUE);	/* (nice and curvy) */

    top = linethickness;	/* increase line thickness if at an angle */
    stop1 = halfstop = 0;
    if ((i = (int) (sqrt ((double) (dx * dx + dy * dy)) + 0.01)) < 2)
	return;			/* small lines are done with endpoints */
    if (dx >= dy) {
	top = (linethickness * i) / dx;
	stop1 = (linethickness * dy) / (i + 1);
	halfstop = (radius * dy) / i;
    } else {
	top = (linethickness * i) / dy;
	stop1 = (linethickness * dx) / (i + 1);
	halfstop = (radius * dx) / i;
    }
    bottom = (top - 1) / 2;
    top = top / 2;

    if (dx >= dy) {
	res = (dy >> 1) - (dx >> 1);
	if (linethickness >= i) {
	    stop1 = stop2 = x0;
	    halfstop = i + 1;
	} else if (xinc == 1) {
	    stop2 = x1 - stop1;
	    stop1 = x0 + stop1;
	    stop3 = x0 + halfstop;
	} else {
	    stop2 = x1 + stop1;
	    stop1 = x0 - stop1;
	    stop3 = x0 - halfstop;
	}

	while (x0 != stop1) {
	    RoundEnd(x0, y0, radius, FALSE);
            if ((x0&linmod) && (xinc == 1 ? x0 > stop3 : x0 < stop3))
		for (i = y0 - top; i <= y0 + bottom; i++)
		    point(x0, i);
            if (res >= 0) {
                res -= dx;
                y0 += yinc;
            }
            res += dy;
            x0 += xinc;
	}
        while (x0 != stop2) {
            if (x0&linmod)
		for (i = y0 - top; i <= y0 + bottom; i++)
		    point(x0, i);
            if (res >= 0) {
                res -= dx;
                y0 += yinc;
            }
            res += dy;
            x0 += xinc;
        } 
	stop3 = x1 + (xinc == 1 ? -halfstop : halfstop);
        while (x0 != x1) {
	    RoundEnd(x0, y0, radius, FALSE);
            if ((x0&linmod) && (xinc == 1 ? x0 < stop3 : x0 > stop3))
		for (i = y0 - top; i <= y0 + bottom; i++)
		    point(x0, i);
            if (res >= 0) {
                res -= dx;
                y0 += yinc;
            }
            res += dy;
            x0 += xinc;
        } 
    } else {
	res = (dx >> 1) - (dy >> 1);
	if (linethickness >= i) {
	    stop1 = stop2 = y0;
	    halfstop = i + 1;
	} else if (yinc == 1) {
	    stop2 = y1 - stop1;
	    stop1 = y0 + stop1;
	    stop3 = y0 + halfstop;
	} else {
	    stop2 = y1 + stop1;
	    stop1 = y0 - stop1;
	    stop3 = y0 - halfstop;
	}

        while (y0 != stop1) {
	    RoundEnd(x0, y0, radius, FALSE);
            if ((y0&linmod) && (yinc == 1 ? y0 > stop3 : y0 < stop3))
		for (i = x0 - top; i <= x0 + bottom; i++)
		    point(i, y0);
            if (res >= 0) {
                res -= dy;
                x0 += xinc;
            }
	    res += dx;
            y0 += yinc;
        }
        while (y0 != stop2) {
            if (y0&linmod)
		for (i = x0 - top; i <= x0 + bottom; i++)
		    point(i, y0);
            if (res >= 0) {
                res -= dy;
                x0 += xinc;
            }
	    res += dx;
            y0 += yinc;
        }
	stop3 = y1 + (yinc == 1 ? -halfstop : halfstop);
        while (y0 != y1) {
	    RoundEnd(x0, y0, radius, FALSE);
            if ((y0&linmod) && (yinc == 1 ? y0 < stop3 : y0 > stop3))
		for (i = x0 - top; i <= x0 + bottom; i++)
		    point(i, y0);
            if (res >= 0) {
                res -= dy;
                x0 += xinc;
            }
	    res += dx;
            y0 += yinc;
        }
    }
}


/*----------------------------------------------------------------------------
 * Routine:	HGArc (xcenter, ycenter, xstart, ystart, angle)
 *
 * Results:	This routine plots an arc centered about (cx, cy) counter
 *		clockwise starting from the point (px, py) through 'angle'
 *		degrees.  If angle is 0, a full circle is drawn.
 *		It does so by calling RoundEnd (fat point maker) for points
 *		along the circle with density depending on the circle's size.
 *		The points that define the circle are scaled before doing
 *		the actual drawing.  No scaling should be done before calling
 *		this routine.
 *----------------------------------------------------------------------------*/

HGArc(cx,cy,px,py,angle)
register int cx;
register int cy;
int px;
int py;
int angle;
{
    double resolution, fullcircle;
    int extent;
    int halfline;
    fixed epsilon;
    register fixed xs;
    register fixed ys;


    halfline = linethickness / 2;

    cx = scale(cx);		/* set points to sun's res. before drawing */
    cy = scale(cy);
    px = scale(px);
    py = scale(py);

    px -= cx;		/* px, py are equal to change in x and y from */
    py -= cy;		/* center to starting point */

/* calculate drawing parameters */

    resolution = sqrt((double)(px * px + py * py));
    fullcircle = ceil(2.0 * pi * resolution);
    epsilon = ffixd(1.0 / resolution);
    xs = ffix(px);
    ys = ffix(py);

    if (angle == 0)		/* calculate how long to do the arc */
	extent = (int) fullcircle;
    else
	extent = (int) (fullcircle * (double) angle / 360.0);
    if (extent < 1) extent = 1;

    if (halfline < 1) {
	do {
	    xs += fmult(epsilon, ys);
	    ys -= fmult(epsilon, xs);
	    point(fintr(xs) + cx, fintr(ys) + cy);
	} while (--extent);
    } else {
	do {
	    xs += fmult(epsilon, ys);
	    ys -= fmult(epsilon, xs);
	    RoundEnd(cx + fintr(xs), cy + fintr(ys), halfline, FALSE);
	} while (--extent);
    }
}  /* end HGArc */


/*----------------------------------------------------------------------------
 * Routine:	RoundEnd (x, y, radius, filled_flag)
 *
 * Results:	Plots a filled (if requested) circle of the specified radius
 *		centered about (x, y).
 *----------------------------------------------------------------------------*/

RoundEnd(x, y, radius, filled)
register int x;
register int y;
int radius, filled;
{
    fixed xs, ys, epsilon;
    register int j;
    register int k;


    point(x, y + radius);	/* do the starting point of the circle */
    if (radius < 1) return;	/* if circle is tiny, quit now */
    point(x, y - radius);

		/* Calculate trajectory of the circle for 1/4	*/
		/* the circumference (while ys is positive) and	*/
		/* mirror to get the other three quadrants.	*/

    xs = ffix(0);
    ys = ffix(radius);
    epsilon = fdiv(ffix(1), ys);

    while (ys >= 0) {
	j = fintr(xs);
	k = fintr(ys);
        if (filled) {		/* fill from center */
	    do {
		point(j+x, k+y);
		point(j+x, y-k);
		point(x-j, k+y);
		point(x-j, y-k);
	    } while (--k >= 0);
        } else {		/* do the perimeter only (no fill) */
	    point(j+x, k+y);
	    point(j+x, y-k);
	    point(x-j, k+y);
	    point(x-j, y-k);
        }
        xs += fmult(epsilon, ys);	/* generate circumference */
        ys -= fmult(epsilon, xs);
    }
}  /* end RoundEnd */;


/*----------------------------------------------------------------------------
 * Routine:	Paramaterize (xpoints, ypoints, hparams, num_points)
 *
 * Results:	This routine calculates parameteric values for use in
 *		calculating curves.  The parametric values are returned
 *		in the array h.  The values are an approximation of
 *		cumulative arc lengths of the curve (uses cord length).
 *		For additional information, see paper cited below.
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
 * Routine:	PeriodicSpline (h, z, dz, d2z, d3z, npoints)
 *
 * Results:	This routine solves for the cubic polynomial to fit a
 *		spline curve to the the points  specified by the list
 *		of values.  The Curve generated is periodic.  The algorithms
 *		for this curve are from the "Spline Curve Techniques" paper
 *		cited below.
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
 * Routine:	NaturalEndSpline (h, z, dz, d2z, d3z, npoints)
 *
 * Results:	This routine solves for the cubic polynomial to fit a
 *		spline curve the the points  specified by the list of
 *		values.  The alogrithms for this curve are from the
 *		"Spline Curve Techniques" paper cited below.
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
 * Routine:	HGCurve(xpoints, ypoints, num_points)
 *
 * Results:	This routine generates a smooth curve through a set of points.
 *		The method used is the parametric spline curve on unit knot
 *		mesh described in "Spline Curve Techniques" by Patrick
 *		Baudelaire, Robert Flegal, and Robert Sproull -- Xerox Parc.
 *----------------------------------------------------------------------------*/

#define POINTSPERINTERVAL 16

HGCurve(x, y, numpoints)
int x[MAXPOINTS];
int y[MAXPOINTS];
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
	int PointsPerInterval;


	lx = x[1];
	ly = y[1];
	PointsPerInterval = POINTSPERINTERVAL / (9999 / scale(10000) + 1);

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
		t3 = t * t2;
		nx = x[j] + (int)(t * dx[j] + t2 * d2x[j]/2 + t3 * d3x[j]/6);
		ny = y[j] + (int)(t * dy[j] + t2 * d2y[j]/2 + t3 * d3y[j]/6);
		HGtline(lx, ly, nx, ny);
		lx = nx;
		ly = ny;
	    }  /* end for k */
	}  /* end for j */
}  /* end HGCurve */
