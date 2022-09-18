h30106
s 00455/00075/00551
d D 1.11 84/05/29 13:16:30 slatteng 12 10
c added polygons, redid graphics area routines to NOT use an extra buffer
e
s 00388/00019/00607
d R 1.11 84/05/24 16:58:37 slatteng 11 10
c added polygons with stipples to varian/versatec drivers and sorter
e
s 00001/00005/00625
d D 1.10 84/04/11 16:39:17 slatteng 10 9
c fix problem of ordering "p" commands so dver doesn't get confused with mixed "P" commands
e
s 00035/00026/00595
d D 1.9 84/03/14 17:44:12 slatteng 9 8
c clean up input (check for EOF), fix algorithm for calculating when
c  to start a span, remove qsort (unnecessary), fix line style (with \n separater)
e
s 00113/00066/00508
d D 1.8 84/02/05 14:10:49 slatteng 8 7
c Revamped to be smarter about keeping things on separate bands
c AND have less sections produced.
e
s 00003/00003/00571
d D 1.7 83/11/30 10:02:08 slatteng 7 6
c change band size from 2 to 1 inches, and fix bug in arc bound calculation
e
s 00068/00034/00506
d D 1.6 83/10/22 15:10:05 slatteng 6 5
c Band size 3" -> 2";  buffer overflow is now a fatal error;
c line thickness affects graphic's bounds;  new arc boundary calculation
e
s 00010/00002/00530
d D 1.5 83/09/23 14:23:40 slatteng 5 4
c add band size change capability
e
s 00201/00101/00331
d D 1.4 83/08/19 14:49:48 slatteng 4 3
c It works!!  puts pages side-by-side and makes 3" bands
e
s 00024/00049/00408
d D 1.3 83/07/30 12:09:09 slatteng 3 2
c added arcs and debugging compile-flag
e
s 00031/00014/00426
d D 1.2 83/07/29 17:02:08 slatteng 2 1
c get it working... added thickness/style to graphics
e
s 00440/00000/00000
d D 1.1 83/07/12 11:48:30 slatteng 1 0
c date and time created 83/07/12 11:48:30 by slatteng
e
u
U
t
T
I 1
/* %M%	%I%	%E%
 *
D 4
 *	sort troff output into troff output that only goes one
 *	direction down the page.
E 4
I 4
 *	Sorts and shuffles ditroff output for versatec wide printer.  It
 *	puts pages side-by-side on the output, and fits as many as it can
 *	on one horizontal span.  The versatec driver sees only pages of
 *	full width, not the individual pages.  Output is sorted vertically
 *	and bands are created NLINES pixels high.  Any object that has
 *	ANY part of it in a band is put on that band.
E 4
 */

D 3
/*******************************************************************************
E 3

D 3
output language from troff:
all numbers are character strings

sn	size in points
fn	font as number from 1-n
cx	ascii character x
Cxyz	funny char xyz. terminated by white space
Hn	go to absolute horizontal position n
Vn	go to absolute vertical position n (down is positive)
hn	go n units horizontally (relative)
vn	ditto vertically
nnc	move right nn, then print c (exactly 2 digits!)
		(this wart is an optimization that shrinks output file size
		 about 35% and run-time about 15% while preserving ascii-ness)
Dt ...\n	draw operation 't':
I 2
	Dt x		line thickness setting
	Ds x		line style (bit mask) setting
E 2
	Dl x y		line from here by x,y
	Dc d		circle of diameter d with left side here
	De x y		ellipse of axes x,y with left side here
	Da x y r	arc counter-clockwise by x,y of radius r
D 2
	D~ x y x y ...	wiggly line by x,y then x,y ...
E 2
I 2
	D~ (or Dg) x y x y ...	wiggly line by x,y then x,y ...
E 2
nb a	end of line (information only -- no action needed)
	b = space before line, a = after
p	new page begins -- set v to 0
#...\n	comment
x ...\n	device control functions:
	x i	init
	x T s	name of device is s
	x r n h v	resolution is n/inch
		h = min horizontal motion, v = min vert
	x p	pause (can restart)
	x s	stop -- done for ever
	x t	generate trailer
	x f n s	font position n contains font s
	x H n	set character height to n
	x S n	set slant to N

	Subcommands like "i" are often spelled out like "init".

*******************************************************************************/

E 3
#include	<stdio.h>
#include	<ctype.h>
I 4
#include	<math.h>
E 4


I 3
D 6
#define DEBUGABLE	/* compile-time flag for debugging */
E 6
I 6
/* #define DEBUGABLE	/* compile-time flag for debugging */
E 6
E 3
#define	FATAL	1
D 3
#define	NVLIST	1500
#define	OBUFSIZ	40000
#define	SLOP	1000
E 3
I 3
D 4
#define	NVLIST	1500	/* size of list of vertical spans */
#define	OBUFSIZ	40000	/* size of character buffer before sorting */
E 4
I 4
#define	NVLIST	3000	/* size of list of vertical spans */
#define	OBUFSIZ	250000	/* size of character buffer before sorting */
E 4
#define	SLOP	1000	/* extra bit of buffer to allow for passing OBUFSIZ */
I 12
#define MAXVECT	200	/* maximum number of points (vectors) in a polygon */
E 12
E 3

I 8
#ifndef FONTDIR
E 8
D 4
#define hgoto(n)	hpos = n
#define hmot(n)		hgoto(hpos + (n))
#define vmot(n)		vgoto(vpos + (n))
E 4
I 4
#define FONTDIR "/usr/lib/font"
I 8
#endif
E 8
#define INCH	200	/* assumed resolution of the printer (dots/inch) */
#define POINT	72	/* number of points per inch */
#define WIDTH	7040	/* number of pixels across the page */
#define HALF	(INCH/2)
D 5
#define BAND	3
E 5
I 5
#ifndef DEBUGABLE
D 6
#define BAND	3	/* or defined below.... */
E 6
I 6
D 7
#define BAND	2	/* or defined below.... */
E 7
I 7
#define BAND	1	/* length of each band (or defined below) */
E 7
E 6
#endif
E 5
#define NLINES	(int)(BAND * INCH)	/* number of pixels in each band */
E 4

I 4
#define hgoto(n)	if((hpos = leftmarg + n) > maxh) maxh = hpos
#define hmot(n)		if((hpos += n) > maxh) maxh = hpos
D 12
#define vmot(n)		vgoto(vpos + n)
E 12
I 12
#define vmot(n)		vpos += (n)
#define vgoto(n)	vpos = (n)
E 12
E 4

I 4

E 4
I 3
#ifdef DEBUGABLE
E 3
D 5
int	dbg	= 0;	/* debug flag != 0 means do debug output */
E 5
I 5
int	dbg = 0;	/* debug flag != 0 means do debug output */
D 6
float	BAND = 3.0;
E 6
I 6
D 9
float	BAND = 2.0;
E 9
I 9
float	BAND = 1.0;
E 9
E 6
E 5
I 3
#endif
E 3
D 4
int	size	= 10;	/* current size */
E 4
I 4

I 5

E 5
int	size	= 10;	/* current size (points) */
int	up	= 0;	/* number of pixels that the current size pushes up */
int	down	= 0;	/* # of pixels that the current size will hang down */
E 4
int	font	= 1;	/* current font */
I 12
int	stip	= 1;	/* current stipple */
E 12
I 4
char *	fontdir = FONTDIR;	/* place to find DESC.out file */
E 4
I 2
int	thick	= 3;	/* line thickness */
D 4
int	style	= 255;	/* line style bit-mask */
E 4
I 4
int	style	= -1;	/* line style bit-mask */
E 4
E 2
int	hpos	= 0;	/* horizontal position to be at next (left = 0) */
int	vpos	= 0;	/* current vertical position (down positive) */

I 4
int	maxh	= 0;	/* farthest right we've gone on the current span */
int	leftmarg= 0;	/* current page offset */
D 6
int	pageno	= 0;	/* number of pages on this horizontal span */
E 6
int	spanno	= 0;	/* current span number for driver in 'p#' commands */
I 6
int	pageno	= 0;	/* number of pages spread across a physical page */
E 6


E 4
struct vlist {
D 2
	int	v;
	int	h;
	int	s;
	int	f;
	char	*p;
E 2
I 2
D 4
	int	v;	/* vertical position of this spread */
	int	h;	/* horizontal position */
	int	s;	/* point size */
	int	t;	/* line thickness */
E 4
I 4
D 8
	short	v;	/* vertical position of this spread */
	short	h;	/* horizontal position */
	short	t;	/* line thickness */
E 8
I 8
	unsigned short	v;	/* vertical position of this spread */
	unsigned short	h;	/* horizontal position */
	unsigned short	t;	/* line thickness */
E 8
D 12
	short	st;	/* style mask */
E 12
I 12
	short	st;		/* style mask */
E 12
D 8
	short	u;	/* upper extent of height */
	short	d;	/* depth of height */
	char	s;	/* point size */
E 4
	char	f;	/* font number */
E 8
I 8
	unsigned short	u;	/* upper extent of height */
	unsigned short	d;	/* depth of height */
D 12
	unsigned char	s;	/* point size */
E 12
I 12
	unsigned short	s;	/* point size */
E 12
	unsigned char	f;	/* font number */
E 8
D 4
	char	st;	/* style mask */
E 4
D 12
	char	*p;	/* text pointer to this spread */
E 12
I 12
	unsigned char	l;	/* stipple number */
	char	*p;		/* text pointer to this spread */
E 12
E 2
};

struct	vlist	vlist[NVLIST + 1];
D 4
struct	vlist	*vlp	= vlist;
int	nvlist	= 0;
E 4
I 4
struct	vlist	*vlp;			/* current spread being added to */
D 8
int	nvlist	= 0;			/* number of spreads in list */
E 8
I 8
int	nvlist	= 1;			/* number of spreads in list */
E 8
E 4
int	obufsiz	= OBUFSIZ;
char	obuf[OBUFSIZ + SLOP];
D 4
char	*op = obuf;
E 4
I 4
char	*op = obuf;			/* pointer to current spot in buffer */
E 4


main(argc, argv)
int argc;
char *argv[];
{
	FILE *fp;
I 5
	double atof();
E 5


I 4
D 8
	vlp = &vlist[0] - 1;		/* initialize pointer to one less */
	startspan(0);			/* than beginning so "startspan" can */
					/* increment it before using it */
E 8
I 8
	vlp = &vlist[0];		/* initialize spread pointer */
	vlp->p = op;
	vlp->v = vlp->d = vlp->u = vlp->h = 0;
	vlp->s = size;
	vlp->f = font;
I 12
	vlp->l = stip;
E 12
	vlp->st = style;
	vlp->t = thick;

E 8
E 4
	while (argc > 1 && **++argv == '-') {
	    switch ((*argv)[1]) {
I 4
		case 'f':
			fontdir = &(*argv)[2];
			break;
E 4
I 3
#ifdef DEBUGABLE
I 5
		case 'B':
			BAND = atof(&(*argv)[2]);
			break;
E 5
E 3
		case 'd':
			dbg = atoi(&(*argv)[2]);
D 4
			if (dbg == 0) {
			    dbg = 1;
			    obufsiz = 50;
			} else
			    obufsiz = dbg;
E 4
I 4
			if (!dbg) dbg = 1;
E 4
			break;
I 4

		case 's':
			if((obufsiz = atoi(&(*argv)[2])) > OBUFSIZ)
			    obufsiz = OBUFSIZ;
			break;
E 4
I 3
#endif
E 3
	    }
	    argc--;
	}
I 4

E 4
	if (argc <= 1)
	    conv(stdin);
	else
	    while (--argc > 0) {
		if ((fp = fopen(*argv, "r")) == NULL)
		    error(FATAL, "can't open %s", *argv);
		conv(fp);
		fclose(fp);
	    }
D 4
    done();
E 4
I 4
	done();
E 4
}

			/* read number from input:  copy to output */
int getnumber (fp)
register FILE *fp;
{
D 4
    register int k;
    register char c;
E 4
I 4
	register int k;
	register char c;
E 4

D 4
    while ((c = getc(fp)) == ' ')
	;
    k = 0;
    do {
	k = 10 * k + (*op++ = c) - '0';
    } while (isdigit(c = getc(fp)));
    ungetc(c, fp);
    return (k);
E 4
I 4
D 12
	while ((c = getc(fp)) == ' ')
E 12
I 12
	while (isspace(c = getc(fp)))
E 12
	    ;
	k = 0;
D 12
	do {
	    k = 10 * k + (*op++ = c) - '0';
	} while (isdigit(c = getc(fp)));
E 12
I 12
	if (c == '-') {
	    c = getc(fp);
	    do {
		k = 10 * k - ((*op++ = c) - '0');
	    } while (isdigit(c = getc(fp)));
	} else {
	    do {
		k = 10 * k + (*op++ = c) - '0';
	    } while (isdigit(c = getc(fp)));
	}
E 12
	ungetc(c, fp);
	return (k);
E 4
}

			/* read number from input:  do _N_O_T copy to output */
int ngetnumber (fp)
register FILE *fp;
{
D 4
    register int k;
    register char c;
E 4
I 4
	register int k;
	register char c;
E 4

D 4
    while ((c = getc(fp)) == ' ')
	;
    k = 0;
    do {
	k = 10 * k + c - '0';
    } while (isdigit(c = getc(fp)));
    ungetc(c, fp);
    return (k);
E 4
I 4
D 12
	while ((c = getc(fp)) == ' ')
E 12
I 12
	while (isspace(c = getc(fp)))
E 12
	    ;
	k = 0;
D 12
	do {
	    k = 10 * k + c - '0';
	} while (isdigit(c = getc(fp)));
E 12
I 12
	if (c == '-') {
	    c = getc(fp);
	    do {
		k = 10 * k - (c - '0');
	    } while (isdigit(c = getc(fp)));
	} else {
	    do {
		k = 10 * k + c - '0';
	    } while (isdigit(c = getc(fp)));
	}
E 12
	ungetc(c, fp);
	return (k);
E 4
}


conv(fp)
register FILE *fp;
{
	register int c;
	int m, n, m1, n1;
D 12
	char buf[SLOP];
E 12

	while ((c = getc(fp)) != EOF) {
I 3
#ifdef DEBUGABLE
E 3
D 4
	    if (dbg) fprintf(stderr, "%c i=%d V=%d\n", c, op-obuf, vpos);
E 4
I 4
	    if (dbg > 2) fprintf(stderr, "%c i=%d V=%d\n", c, op-obuf, vpos);
E 4
I 3
#endif
E 3
D 6
	    if (op > obuf + obufsiz)
E 6
I 6
	    if (op > obuf + obufsiz) {
		error(!FATAL, "buffer overflow %d.", op - (obuf + obufsiz));
E 6
		oflush();
I 6
	    }
E 6
	    switch (c) {
I 9
		case '\0':	/* filter out noise */
			break;
E 9
		case '\n':	/* let text input through */
		case '\t':
		case ' ':
			*op++ = c;
			break;
		case '{':	/* push down current environment */
			*op++ = c;
			t_push();
			break;
		case '}':	/* pop up last environment */
			*op++ = c;
			t_pop();
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
				/* two motion digits plus a character */
I 8
			setlimit(vpos - up, vpos + down);
E 8
			*op++ = c;
			hmot((c-'0') * 10 + (*op++ = getc(fp)) - '0');
			*op++ = getc(fp);
I 4
D 8
			setlimit();
E 8
E 4
			break;
		case 'c':	/* single ascii character */
I 8
			setlimit(vpos - up, vpos + down);
E 8
			*op++ = c;
			*op++ = getc(fp);
I 4
D 8
			setlimit();
E 8
E 4
			break;
		case 'C':	/* white-space terminated funny character */
I 8
			setlimit(vpos - up, vpos + down);
E 8
			*op++ = c;
D 9
			while ((*op++ = c = getc(fp)) != ' ' && c != '\n')
				;
E 9
I 9
			do
			    *op++ = c = getc(fp);
D 12
			while (c != ' ' && c != '\n' && c != EOF);
E 12
I 12
			while (c != EOF && !isspace(c));
E 12
E 9
I 4
D 8
			setlimit();
E 8
E 4
			break;
		case 't':	/* straight text */
I 8
			setlimit(vpos - up, vpos + down);
E 8
			*op++ = c;
			fgets(op, SLOP, fp);
			op += strlen(op);
I 4
D 8
			setlimit();
E 8
E 4
			break;
		case 'D':	/* draw function */
D 9
			fgets(buf, SLOP, fp);
E 9
I 9
D 12
			if (fgets(buf, SLOP, fp) == NULL)
			    error(FATAL, "unexpected end of input");
E 9
			switch (buf[0]) {
E 12
I 12
			switch (c = getc(fp)) {
E 12
I 2
			case 's':	/* "style" */
D 12
				sscanf(buf+1, "%d", &style);
				sprintf(op, "D%s", buf);
I 9
				op += strlen(op);
E 12
I 12
				sprintf(op, "Ds ");
				op += 3;
				style = getnumber(fp);
E 12
E 9
				break;
I 12

E 12
			case 't':	/* thickness */
D 12
				sscanf(buf+1, "%d", &thick);
				sprintf(op, "D%s", buf);
I 9
				op += strlen(op);
E 12
I 12
				sprintf(op, "Dt ");
				op += 3;
				thick = getnumber(fp);
E 12
E 9
				break;
I 12

E 12
E 2
			case 'l':	/* draw a line */
D 12
				sscanf(buf+1, "%d %d", &n, &m);
E 12
I 12
				n = ngetnumber(fp);
				m = ngetnumber(fp);
E 12
D 4
						/* if line starts higher, put */
						/* it on its own span */
E 4
I 4
D 8
						/* put line on its own spread */
E 8
E 4
				if (m < 0) {
D 8
				    startspan(vpos + m);
D 4
				    sprintf(op, "V%d ", vpos);
				    op += strlen(op);
E 4
I 4
D 6
				    vlp->d = vpos - m;
E 6
I 6
				    vlp->d = vpos + thick/2;
E 8
I 8
				    setlimit(vpos+m-thick/2, vpos+thick/2);
E 8
E 6
				} else {
D 8
				    startspan(vpos);
D 6
				    vlp->d = vpos + m;
E 6
I 6
				    vlp->d = vpos + m + thick/2;
E 8
I 8
D 9
				    setlimit(vpos-thick/2, vpos+m+thick/2);
E 9
I 9
				    setlimit(vpos-(1+thick/2),vpos+1+m+thick/2);
E 9
E 8
E 6
E 4
				}
D 4
				sprintf(op, "D%s", buf);
E 4
I 4
D 8
				sprintf(op, "V%dD%s", vpos, buf);
E 8
I 8
D 12
				sprintf(op, "D%s", buf);
E 12
I 12
				sprintf(op, "Dl %d %d", n, m);
E 12
E 8
E 4
				op += strlen(op);
				hmot(n);
				vmot(m);
				break;
D 12
			case 'c':	/* circle */
E 12
I 12

E 12
D 4
				sscanf(buf+1, "%d", &n);	/* always put */
				startspan(vpos + n/2);		/* circles on */
				sprintf(op, "V%d D%s", vpos, buf);/*their own */
				op += strlen(op);		/* vertl list */
E 4
I 4
D 8
				sscanf(buf+1, "%d", &n);	/* put circle */
D 6
				startspan(vpos - n/2);		/* on its own */
				vlp->d = vpos + n/2;		/* spread */
E 6
I 6
				startspan(vpos - (n + thick)/2);/* on its own */
				vlp->d = vpos + (n + thick)/2;	/* spread */
E 6
				sprintf(op, "V%dD%s", vpos, buf);
E 8
I 8
			case 'e':	/* ellipse */
D 12
				sscanf(buf+1, "%d", &n);
E 12
I 12
				n = ngetnumber(fp);
				m = ngetnumber(fp);
				setlimit(vpos-(m+thick)/2, vpos+(m+thick)/2);
				sprintf(op, "De %d %d", n, m);
				op += strlen(op);
				hmot(n);
				break;

			case 'c':	/* circle */
				n = ngetnumber(fp);
E 12
				setlimit(vpos-(n+thick)/2, vpos+(n+thick)/2);
D 12
				sprintf(op, "D%s", buf);
E 12
I 12
				sprintf(op, "Dc %d", n);
E 12
E 8
				op += strlen(op);
E 4
				hmot(n);
D 8
				startspan(vpos);
E 8
				break;
I 12

E 12
D 8
			case 'e':	/* ellipse */
				sscanf(buf+1, "%d %d", &m, &n);	/* same here */
D 4
				startspan(vpos + n/2);
				sprintf(op, "V%d D%s", vpos, buf);
E 4
I 4
D 6
				startspan(vpos - n/2);
				vlp->d = vpos + n/2;
E 6
I 6
				startspan(vpos - (n + thick)/2);
				vlp->d = vpos + (n + thick)/2;
E 6
				sprintf(op, "V%dD%s", vpos, buf);
E 4
				op += strlen(op);
				hmot(m);
				startspan(vpos);
				break;
E 8
			case 'a':	/* arc */
D 12
				sscanf(buf+1, "%d %d %d %d", &n, &m, &n1, &m1);
E 12
I 12
				n = getnumber(fp);
				m = getnumber(fp);
				n1 = getnumber(fp);
				m1 = getnumber(fp);
E 12
D 3
				sprintf(op, "D%s", buf);
E 3
I 3
D 4

				if ((m += m1) < 0)	/* set m1 to highest */
				    m1 = vpos + m;	 /* of the endpoints */
				else		
				    m1 = vpos;		/* can't be any more */
				m1 -= (((n += n1) < 0) ?	 /* than 1/2 */
					-n : n) >> 1;	/* horiz diff higher */

				startspan(m1 < 0 ? 0 : m1);
				sprintf(op, "V%d D%s", vpos, buf);
E 4
I 4
D 8
				startspan(vpos);
E 8
				arcbounds(n, m, n1, m1);
D 8
				sprintf(op, "V%dD%s", vpos, buf);
E 8
I 8
D 12
				sprintf(op, "D%s", buf);
E 12
I 12
				sprintf(op, "Da %d %d %d %d", n, m, n1, m1);
E 12
E 8
E 4
E 3
				op += strlen(op);
D 3
				hmot(n + n1);
				vmot(m + m1);
E 3
I 3
D 4
				hmot(n);
				vmot(m);
E 4
I 4
				hmot(n + n1);
				vmot(m + m1);
E 4
E 3
				break;
D 12
			case '~':	/* wiggly line */
I 2
			case 'g':	/* gremlin curve */
E 12
I 12

			case 'P':
			case 'p':
E 12
E 2
			    {
D 12
				register char *pop;
E 12
I 12
				register int nvect;
				int member;
				int border;
				int x[MAXVECT];
				int y[MAXVECT];
E 12
D 4
							/* a curve goes on */
				startspan(vpos);	/* its own span */
				sprintf(op, "V%dD", vpos);  /* vertical move */
E 4
I 4
D 8
							   /* a curve goes on */
				startspan(vpos);	      /* its own span */
				sprintf(op, "V%dD", vpos);   /* vertical move */
E 4
				pop = op += strlen(op);     /* to curve start */
				do {			   /* read in rest of */
D 4
				    sprintf(op, "%s", buf);/* point input */
E 4
I 4
				    sprintf(op, "%s", buf);    /* point input */
E 8
I 8

D 12
				startspan(vpos);	/* always put curve */
				*op++ = 'D';		 /* on its own span */
				pop = op;	   /* pop -> start of points */
				do {			  /* read in rest of */
				    sprintf(op, "%s", buf);   /* point input */
E 8
E 4
				    op += strlen(op);
				    if (*(op - 1) != '\n')
D 9
					fgets(buf, SLOP, fp);
E 9
I 9
					if (fgets(buf, SLOP, fp) == NULL)
					    error(FATAL, "unexpected end of input");
E 9
				} while (*(op - 1) != '\n');
E 12
I 12

				border = (c == 'p');	/* type of polygon */
				member = ngetnumber(fp);/* and member number */

				nvect = 1;		/* starting point for */
				x[1] = hpos;		/* points on polygon */
				y[1] = vpos;
E 12
D 4
				n = vpos;		/* = minimum vertical */
E 4
I 4
				m = n = vpos;		/* = max/min vertical */
E 4
							/* position for curve */
D 12
				while (*++pop == ' ');	/* skip '~' & blanks */
				do {			/* calculate minimum */
				    hpos += atoi(pop);		/* vertical */
				    while (isdigit(*++pop));	/* position */
				    while (*++pop == ' ');
				    vpos += atoi(pop);
				    while (isdigit(*++pop));
				    while (*pop == ' ') pop++;
				    if (vpos < n) n = vpos;
I 4
				    else if (vpos > m) m = vpos;
E 4
				} while (*pop != '\n');
E 12
I 12
				{
				    register int h;
				    register int v;
E 12

D 4
				(vlp - 1)->v = n;
E 4
I 4
D 8
				vlp->u = vlp->v = n < 0 ? 0 : n;
E 8
I 8
D 12
				vlp->u = n < 0 ? 0 : n;
E 8
				vlp->d = m;
E 4
				startspan(vpos);
E 12
I 12

				    h = hpos;	/* calculate max and minimum */
				    v = vpos;		/* vertical position */
							/*    and get points */
				    do {
					h += ngetnumber(fp);
					v += ngetnumber(fp);

					if (v < n) n = v;
					else if (v > m) m = v;

					if (nvect < (MAXVECT-1))/* keep the */
					    nvect++;		/* points in */
					x[nvect] = h;		/* bounds */
					y[nvect] = v;		/* of arrays */
					c = getc(fp);
				    } while (c != '\n' && c != EOF);
				}
				if (border) {		/* output border as a */
				    register int *x1;	/*  bunch of lines */
				    register int *x2;	/*  instead of having */
				    register int *y1;	/*  the filter do it */
				    register int *y2;
				    register int extra = thick/2;

				    x1 = &(x[0]);	/* x1, y1, x2, y2 are */
				    x2 = &(x[1]);	/* for indexing along */
				    y1 = &(y[0]);	/* coordinate arrays */
				    y2 = &(y[1]);
				    for (border = 0; ++border < nvect; ) {
					if (*++y1 > *++y2) {
					   setlimit(*y2-extra, vpos+extra);
					} else {
					   setlimit(vpos-(1+extra),*y2+1+extra);
						/* the extra 1's are to force */
						/* setlimit to know this is a */
						/* real entry (making sure it */
						/* doesn't get vpos as limit */
					}
					sprintf(op, "Dl %d %d\n",
						c = *++x2 - *++x1, *y2 - *y1);
					op += strlen(op);
					hmot(c);	/* update vpos for */
					vgoto(*y2);	/* the setlimit call */
				    }
				} else {
				    register int *x1;	/* x1, x2, are for */
				    register int *x2;	/* indexing points */
				    register int i;	/* random int */

				    x1 = &(x[0]);
				    x2 = &(x[1]);
				    for (i = 0; ++i < nvect; ) {
					hmot(*++x2 - *++x1);
				    }
				    vgoto(y[nvect]);
				    sprintf(op, "H%dV%d", hpos, vpos);
				    op += strlen(op);
				}
				if (member) {
				    polygon(member, nvect, x, y, m, n);
				}
E 12
			    }
			    break;

I 12
			case '~':	/* wiggly line */
			case 'g':	/* gremlin curve */
			    startspan(vpos);		/* always put curve */
			    sprintf(op, "D%c ", c);	/* on its own span */
			    op += 3;

			    m = n = vpos;		/* = max/min vertical */
			    do {			/* position for curve */
				hpos += getnumber(fp);
				*op++ = ' ';
				vpos += getnumber(fp);
				*op++ = ' ';

				if (vpos < n) n = vpos;
				else if (vpos > m) m = vpos;

				c = getc(fp);
			    } while (c != '\n' && c != EOF);

			    vlp->u = n < 0 ? 0 : n;
			    vlp->d = m;
			    *op++ = '\n';
			    startspan(vpos);
			    break;

E 12
			default:
D 12
				error(FATAL,"unknown drawing command %s\n",buf);
E 12
I 12
				error(FATAL,"unknown drawing command %c", c);
E 12
				break;
			}
			break;
		case 's':
			*op++ = c;
D 4
			size = getnumber (fp);
E 4
I 4
			size = getnumber(fp);
D 6
			up = (size * INCH) / POINT;
			down = up / 3;
E 6
I 6
D 8
			up = (size * INCH) / POINT;	/* rough estimate */
E 8
I 8
D 9
			up = (size * INCH) / POINT;	/* ROUGH estimate */
E 9
I 9
			up = ((size + 1)*INCH) / POINT;	/* ROUGH estimate */
E 9
E 8
			down = up / 3;			/* of max up/down */
E 6
E 4
			break;
		case 'f':
			*op++ = c;
D 4
			font = getnumber (fp);
E 4
I 4
			font = getnumber(fp);
E 4
			break;
D 12
		case 'H':	/* absolute horizontal motion */
E 12
I 12
		case 'i':
E 12
			*op++ = c;
I 12
			stip = getnumber(fp);
			break;
		case 'H':	/* absolute horizontal motion */
E 12
D 4
			hgoto(getnumber (fp));
E 4
I 4
			hgoto(ngetnumber(fp));
D 12
			sprintf(op, "%d", hpos);
E 12
I 12
			sprintf(op, "H%d", hpos);
E 12
			op += strlen(op);	/* reposition by page offset */
E 4
			break;
		case 'h':	/* relative horizontal motion */
			*op++ = c;
D 4
			hmot(getnumber (fp));
E 4
I 4
			hmot(getnumber(fp));
E 4
			break;
		case 'w':	/* useless */
			break;
		case 'V':	/* absolute vertical motion */
D 4
			vgoto(ngetnumber (fp));
E 4
I 4
D 12
			vgoto(ngetnumber(fp));
E 12
I 12
			*op++ = c;
			vgoto(getnumber(fp));
E 12
E 4
			break;
		case 'v':
D 4
			vmot(ngetnumber (fp));
E 4
I 4
D 12
			vmot(ngetnumber(fp));
E 12
I 12
			*op++ = c;
			vmot(getnumber(fp));
E 12
E 4
			break;
		case 'p':	/* new page */
I 4
			t_page(ngetnumber(fp));
E 4
			vpos = 0;
D 4
			oflush();
			*op++ = c;
			fscanf(fp, "%s", op);
			op += strlen(op);
E 4
			break;
		case 'n':	/* end of line */
D 4
			hpos = 0;
E 4
I 4
			hpos = leftmarg;
I 9
			*op++ = c;
			do
			    *op++ = c = getc(fp);
			while (c != '\n' && c != EOF);
			break;
E 9
E 4
		case '#':	/* comment */
I 9
			do
			    c = getc(fp);
			while (c != '\n' && c != EOF);
			break;
E 9
I 4
		case 'x':	/* device control */
I 8
			startspan(vpos);
E 8
E 4
			*op++ = c;
D 9
			while ((*op++ = getc(fp)) != '\n')
				;
E 9
I 9
			do
			    *op++ = c = getc(fp);
			while (c != '\n' && c != EOF);
E 9
			break;
D 4
		case 'x':	/* device control */
			oflush();
			putchar(c);
			fgets(buf, sizeof buf, fp);
			fputs(buf, stdout);
			fflush(stdout);
			break;
E 4
		default:
D 9
			error(!FATAL, "unknown input character %o %c\n", c, c);
E 9
I 9
			error(!FATAL, "unknown input character %o %c", c, c);
E 9
			done();
	    }
	}
}

I 4
D 6
		/* set the "u" and "d" parts of the vlist given the current */
setlimit()	/* up and down limits set by the point size */
E 6
I 6

/*----------------------------------------------------------------------------*
 | Routine:	setlimit
 |
D 8
 | Results:	using "up" and "down" set by point size changes, set the
 |		maximum rise and/or fall of a vertical extent
E 8
I 8
 | Results:	using "newup" and "newdown" decide when to start a new span.
 |		maximum rise and/or fall of a vertical extent are saved.
E 8
 |
D 8
 | Side Efct:	may set vlp's u and/or d
 |
 | Bugs:	assumes all text of a particular point size is of the same
 |		maximum rise fall above and below the text base line
E 8
I 8
 | Side Efct:	may start new span.
E 8
 *----------------------------------------------------------------------------*/

D 8
setlimit()
E 8
I 8
D 9
#define diffspan(x,y)	((x)/((int)(BAND * INCH)) - (y)/((int)(BAND * INCH)))
E 9
I 9
D 12
#define diffspan(x,y)	((x)/((int)(BAND * INCH)) != (y)/((int)(BAND * INCH)))
E 12
I 12
#define diffspan(x,y)	((x)/NLINES != (y)/NLINES)
E 12
E 9

setlimit(newup, newdown)
register int newup;
register int newdown;
E 8
E 6
{
D 8
	register int upv = vpos - up;
	register int downv = vpos + down;
E 8
I 8
	register int currup = vlp->u;
	register int currdown = vlp->d;
E 8
E 4

I 4
D 8
	if (upv < vlp->u) vlp->u = upv;
	if (downv > vlp->d) vlp->d = downv;
E 8
I 8
	if (newup < 0) newup = 0;	/* don't go back beyond start of page */
	if (newdown < 0) newdown = 0;

	if (diffspan(currup, currdown)) {	/* now spans > one band */
D 9
	    if ((newup < currup && diffspan(newup, currup))
		    || (newdown > currdown && diffspan(newdown, currdown))
		    || diffspan(newup, newdown) == 0) {
E 9
I 9
	    if (diffspan(newup, currup) || diffspan(newdown, currdown)) {
E 9
		startspan (vpos);
		vlp->u = newup;
		vlp->d = newdown;
I 9
	    } else {
		if (newup < currup) vlp->u = newup;
		if (newdown > currdown) vlp->d = newdown;
E 9
	    }
	} else {
	    if (newup < currup) {	/* goes farther up than before */
		if (currup == vlp->v) {		/* is new span, just set "up" */
		    vlp->u = newup;
		} else {
		    if (diffspan(newup, currup)) {	/* goes up farther */
			startspan(vpos);		/* than previously */
			vlp->u = newup;			/* AND to a higher */
			vlp->d = newdown;		/* band.  */
			return;
		    } else {
			vlp->u = newup;
		    }
		}
	    }
	    if (newdown > currdown) {
		if (currdown == vlp->v) {
		    vlp->d = newdown;
		    return;
		} else {
		    if (diffspan(newdown, currdown)) {
			startspan(vpos);
			vlp->u = newup;
			vlp->d = newdown;
			return;
		    } else {
			vlp->d = newdown;
		    }
		}
	    }
	}
E 8
}


D 6
arcbounds(h, v, h1, v1)		/* make a circle out of the arc to estimate */
int h, v, h1, v1;		/* how far up/down the arc will span */
E 6
I 6
/*----------------------------------------------------------------------------*
 | Routine:	arcbounds (h, v, h1, v1)
 |
 | Results:	using the horizontal positions of the starting and ending
 |		points relative to the center and vertically relative to
 |		each other, arcbounds calculates the upper and lower extent
 |		of the arc which is one of:  starting point, ending point
 |		or center + rad for bottom, and center - rad for top.
 |
D 8
 | Side Efct:	sets vlp's v, u and d
E 8
I 8
 | Side Efct:	calls setlimit(up, down) to save the extent information.
E 8
 *----------------------------------------------------------------------------*/

arcbounds(h, v, h1, v1)
int h, v, h1, v1;
E 6
{
D 6
	register int center = vpos + v;
	register int rad = ((int) sqrt ((double) (h*h + v*v))) >> 1;
						/* set the vertical extents */
	vlp->v = vlp->u = (center - rad) < 0 ? 0 : center - rad;
	vlp->d = center + rad;
E 6
I 6
D 7
	register int rad = ((int) (sqrt ((double) (h*h + v*v)) + 0.5)) >> 1;
E 7
I 7
	register unsigned rad = (int)(sqrt((double)(h*h + v*v)) + 0.5);
E 7
	register int i = ((h >= 0) << 2) | ((h1 < 0) << 1) | ((v + v1) < 0);

			/* i is a set of flags for the points being on the */
			/* left of the center point, and which is higher */

	v1 += vpos + v;		/* v1 is vertical position of ending point */
D 8
	vlp->v = vpos;		/* set vertical starting position of arc */

E 8
				/* test relative positions for maximums */
D 8
	vlp->u = (((i&3)==1) ? v1 : (((i&5)==4) ? vpos : vpos+v-rad)) - thick/2;
D 7
	vlp->d = (((i&3)==2) ? v1 : (((i&5)==1) ? vpos : vpos+v-rad)) - thick/2;
E 7
I 7
	vlp->d = (((i&3)==2) ? v1 : (((i&5)==1) ? vpos : vpos+v+rad)) + thick/2;
E 8
I 8
	setlimit(		/* and set the up/down of the arc */
	    ((((i&3)==1) ? v1 : (((i&5)==4) ? vpos : vpos+v-rad)) - thick/2),
	    ((((i&3)==2) ? v1 : (((i&5)==1) ? vpos : vpos+v+rad)) + thick/2));
E 8
E 7
E 6
}


E 4
oflush()	/* sort, then dump out contents of obuf */
{
	register struct vlist *vp;
D 2
	int i;
E 2
I 2
D 4
	register int lastv = -1;
E 4
I 4
	register int notdone;
	register int topv;
	register int botv;
E 4
	register int i;
I 4
	register char *p;
E 4
E 2
D 9
	int compar();
E 9

I 3
#ifdef DEBUGABLE
E 3
	if (dbg) fprintf(stderr, "into oflush, V=%d\n", vpos);
I 3
#endif
E 3
	if (op == obuf)
		return;
D 9
 	qsort((char *) vlist, nvlist, sizeof (struct vlist), compar);
	*op++ = 0;
E 9
I 9
	*op = 0;
E 9
D 4
	vp = vlist;
	for (i = 0; i < nvlist; i++, vp++) {
D 2
		register int lastv = -1;
		register char *p;
E 2
I 2
	    register char *p;
E 4
E 2

D 2
		if (lastv != vp->v)
		    printf("V%d", lastv = vp->v);
		printf("H%ds%df%d ", vp->h, vp->s, vp->f);
		for (p = vp->p; *p != 0; p++)
			putchar(*p);
E 2
I 2
D 4
	    if (lastv != vp->v) printf("V%d", lastv = vp->v);
	    printf("H%ds%df%d Ds %d\nDt %d\n",vp->h,vp->s,vp->f,vp->st,vp->t);
	    for (p = vp->p; *p != 0; p++) putchar(*p);
E 2
	}
E 4
I 4
	topv = 0;
	botv = NLINES - 1;
	do {
	    notdone = 0;
	    vp = vlist;
#ifdef DEBUGABLE
	    if (dbg) fprintf(stderr, "topv=%d, botv=%d\n", topv, botv);
#endif
	    for (i = 0; i < nvlist; i++, vp++) {
#ifdef DEBUGABLE
		if(dbg>1)fprintf(stderr,"u=%d, d=%d,%.60s\n",vp->u,vp->d,vp->p);
#endif
		if (vp->u <= botv && vp->d >= topv) {
D 8
		    printf("V%dH%ds%df%dDs%d\nDt%d\n",
				vp->v, vp->h, vp->s, vp->f, vp->st, vp->t);
E 8
I 8
D 9
		    printf("H%dV%ds%df%dDs%d\nDt%d\n",
				vp->h, vp->v, vp->s, vp->f, vp->st, vp->t);
E 8
		    for (p = vp->p; *p != 0; p++) putchar(*p);
E 9
I 9
D 12
		    printf("H%dV%ds%df%d\nDs%d\nDt%d\n%s",
			    vp->h, vp->v, vp->s, vp->f, vp->st, vp->t, vp->p);
E 12
I 12
		    printf("H%dV%ds%df%d\ni%d\nDs%d\nDt%d\n%s",
			 vp->h,vp->v,vp->s,vp->f,vp->l,vp->st,vp->t,vp->p);
E 12
E 9
		}
		notdone |= vp->d > botv;	/* not done if there's still */
	    }					/* something to put lower */
D 10
#ifdef DEBUGABLE
	    if (dbg) fprintf(stderr, "topv=%d, botv=%d\n", topv, botv);
#endif
E 10
	    if (notdone) putchar('P');		/* mark the end of the spread */
	    topv += NLINES;			/* unless it's the last one */
	    botv += NLINES;
	} while (notdone);

E 4
	fflush(stdout);
	vlp = vlist;
	vlp->p = op = obuf;
	vlp->h = hpos;
	vlp->v = vpos;
I 4
	vlp->u = vpos;
	vlp->d = vpos;
E 4
	vlp->s = size;
	vlp->f = font;
I 12
	vlp->l = stip;
E 12
I 2
	vlp->st = style;
	vlp->t = thick;
E 2
	*op = 0;
D 4
	vlp++;
E 4
	nvlist = 1;
}

D 9

compar(p1, p2)
struct vlist *p1, *p2;
{
	return(p1->v - p2->v);
}
E 9

done()
{
	oflush();
	exit(0);
}

error(f, s, a1, a2, a3, a4, a5, a6, a7) {
	fprintf(stderr, "vsort: ");
	fprintf(stderr, s, a1, a2, a3, a4, a5, a6, a7);
	fprintf(stderr, "\n");
	if (f)
		done();
}

#define	MAXSTATE	5

struct state {
	int	ssize;
	int	sfont;
	int	shpos;
	int	svpos;
};
struct	state	state[MAXSTATE];
struct	state	*statep = state;

t_push()	/* begin a new block */
{
	statep->ssize = size;
	statep->sfont = font;
	statep->shpos = hpos;
	statep->svpos = vpos;
	hpos = vpos = 0;
	if (statep++ >= state+MAXSTATE)
		error(FATAL, "{ nested too deep");
	hpos = vpos = 0;
}

t_pop()	/* pop to previous state */
{
	if (--statep < state)
		error(FATAL, "extra }");
	size = statep->ssize;
	font = statep->sfont;
	hpos = statep->shpos;
	vpos = statep->svpos;
}


D 12
	/* vertical motion:  start new vertical span if necessary */
vgoto(n)
register int n;
{
D 8
    if (n != vpos)
	startspan(n);
    vpos = n;
E 8
I 8
	sprintf (op, "V%d", n);
	op += strlen(op);
	vpos = n;
E 8
}


E 12
I 8
/*----------------------------------------------------------------------------*
 | Routine:	t_page
 |
 | Results:	new Margins are calculated for putting pages side-by-side.
 |		If no more pages can fit across the paper (WIDTH wide)
 |		a real page end is done and the currrent page is output.
 |
 | Side Efct:	oflush is called on a REAL page boundary.
 *----------------------------------------------------------------------------*/

E 8
I 4
t_page(n)
int n;
{
D 6
    register int x;
E 6
I 6
    static int first = 1;		/* flag to catch the 1st time through */
E 6

D 6
    pageno++;
    if (maxh > (WIDTH - INCH)	/* if we're close to the edge */
	    || n == 1		/* or if i think we'll go over with this page */
	    || leftmarg + leftmarg / pageno > (WIDTH - INCH)) {
	oflush();				/* make it a REAL page-break */
	sprintf(op, "p%d\n", ++spanno);
E 6
I 6
    				/* if we're near the edge, we'll go over on */
    if (leftmarg + 2*(pageno ? leftmarg/pageno : 0) > WIDTH	/* this page, */
	  || maxh > WIDTH - INCH || first) {	/* or this is the first page */
D 10
	sprintf(op, "p%d\n", spanno++);		/* make it a REAL page-break */
E 6
	op += strlen(op);
E 10
D 6
	pageno = leftmarg = maxh = 0;
    } else {					    /* x = last page's width */
	x = (maxh - leftmarg + (HALF - 1)) / HALF;	/*  (in half-inches) */
	if (x > 12 && x <= 17)
E 6
I 6
	oflush();
I 10
	printf("p%d\n", spanno++);		/* make it a REAL page-break */
E 10
	first = pageno = leftmarg = maxh = 0;
    } else {			    /* x = last page's width (in half-inches) */
	register int x = (maxh - leftmarg + (HALF - 1)) / HALF;

	if (x > 11 && x <= 17)
E 6
	    leftmarg += (8 * INCH) + HALF; 		/* if close to 8.5"  */
	else						/* then make it so   */
	    leftmarg = ((maxh + HALF) / HALF) * HALF;	/* else set it to the */
D 6
    }							/* nearest half-inch */
E 6
I 6
	pageno++;					/* nearest half-inch */
    }
E 6
}


E 4
startspan(n)
register int n;
{
	*op++ = 0;
	if (nvlist >= NVLIST) {
I 8
#ifdef DEBUGABLE
	    error(!FATAL, "ran out of vlist");
#endif
E 8
	    oflush();
	}
I 4
	vlp++;
E 4
	vlp->p = op;
	vlp->v = n;
I 4
	vlp->d = n;
	vlp->u = n;
E 4
	vlp->h = hpos;
	vlp->s = size;
	vlp->f = font;
I 12
	vlp->l = stip;
E 12
I 2
	vlp->st = style;
	vlp->t = thick;
E 2
D 4
	vlp++;
E 4
	nvlist++;
}
I 12


#define MAXX	0x7fff
#define MINX	0x8000

typedef struct poly {
	struct poly *next;	/* doublely-linked lists of vectors */
	struct poly *prev;
	int param;	/* bressenham line algorithm parameter */
	short dx;	/* delta-x for calculating line */
	short dy;	/* delta-y for calculating line */
	short currx;	/* current x in this vector */
	short endy;	/* where vector ends */
} polyvector;


/*----------------------------------------------------------------------------*
 | Routine:	polygon ( member, num_vectors, x_coor, y_coor, maxy, miny )
 |
 | Results:	outputs commands to draw a polygon starting at (x[1], y[1])
 |		going through each of (x_coordinates, y_coordinates), and
 |		filled with "member" stipple pattern.
 |
 |		A scan-line algorithm is simulated and pieces of the
 |		polygon are put out that fit on bands of the versatec
 |		output filter.
 |
 |		The format of the polygons put out are:
 |			'Dp member num miny maxy [p dx dy curx endy]'
 |		where "num" is the number of [..] entries in that
 |		section of the polygon.
 *----------------------------------------------------------------------------*/

polygon(member, nvect, x, y, maxy, miny)
int member;
int nvect;
int x[];
int y[];
int maxy;
int miny;
{
    int nexty;			/* at what x value the next vector starts */
    register int active;	/* number of vectors in active list */
    int firsttime;		/* force out a polgon the first time through */
    polyvector *activehead;		/* doing fill, is active edge list */
    polyvector *waitinghead;		/* edges waiting to be active */
    register polyvector *vectptr;	/* random vector */
    register int i;			/* random register */


				/* allocate space for raster-fill algorithm*/
    vectptr = (polyvector *) malloc(sizeof(polyvector) * (nvect + 4));
    if (vectptr == (polyvector *) NULL) {
	error(!FATAL, "unable to allocate space for polygon");
	return;
    }

    waitinghead = vectptr;
    vectptr->param = miny - 1;
    (vectptr++)->prev = NULL;		/* put dummy entry at start */
    waitinghead->next = vectptr;
    vectptr->prev = waitinghead;
    i = 1;					/* starting point of coords */
    if (y[1] != y[nvect] || x[1] != x[nvect]) {
	y[0] = y[nvect];			/* close polygon if it's not */
	x[0] = x[nvect];
	i = 0;
    }
    active = 0;
    while (i < nvect) {		/* set up the vectors */
	register int j;			/* indexes to work off of */
	register int k;

	j = i;			/* j "points" to the higher (lesser) point */
	k = ++i;
	if (y[j] == y[k])		/* ignore horizontal lines */
	    continue;

	if (y[j] > y[k]) {
	    j++;
	    k--;
	}
	active++;
	vectptr->next = vectptr + 1;
	vectptr->param = y[j];		/* starting point of vector */
	vectptr->dx = x[k] - x[j];	/* line-calculating parameters */
	vectptr->dy = y[k] - y[j];
	vectptr->currx = x[j];		/* starting point */
	(vectptr++)->endy = y[k];	/* ending point */
	vectptr->prev = vectptr - 1;
    }
					/* if no useable vectors, quit */
    if (active < 2)
	goto leavepoly;

    vectptr->param = maxy + 1;		/* dummy entry at end, too */
    vectptr->next = NULL;

    activehead = ++vectptr;		/* two dummy entries for active list */
    vectptr->currx = MINX;		/* head */
    vectptr->endy = maxy + 1;
    vectptr->param = vectptr->dx = vectptr->dy = 0;
    activehead->next = ++vectptr;
    activehead->prev = vectptr;
    vectptr->prev = activehead;		/* tail */
    vectptr->next = activehead;
    vectptr->currx = MAXX;
    vectptr->endy = maxy + 1;
    vectptr->param = vectptr->dx = vectptr->dy = 0;

					/* if there's no need to break the */
					/* polygon into pieces, don't bother */
    if (diffspan(miny, maxy)) {
	active = 0;			/* will keep track of # of vectors */
	firsttime = 1;
    } else {				/*   in the active list */
	startspan(miny);
	sprintf(op, "Dq %d %d %d %d", member, active, miny, maxy);
	op += strlen(op);
	for (vectptr = waitinghead->next; active--; vectptr++) {
	    sprintf(op, " %d %d %d %d %d",
		vectptr->param, vectptr->dx, vectptr->dy,
		vectptr->currx, vectptr->endy);
	    op += strlen(op);
	}
	*(op++) = '\n';
	goto leavepoly;
    }
			/* main loop -- gets vectors off the waiting list, */
			/* then displays spans while updating the vectors in */
    			/* the active list */
    while (miny <= maxy) {
	i = maxy + 1;		/* this is the NEXT time to get a new vector */
	for (vectptr = waitinghead->next; vectptr != NULL; ) {
	    if (miny == vectptr->param) {
				/* the entry in waiting list (vectptr) is */
				/*   ready to go into active list.  Need to */
				/*   convert some vector stuff and sort the */
				/*   entry into the list. */
		register polyvector *p;	/* random vector pointers */
		register polyvector *v;

							/* convert this */
		if (vectptr->dx < 0)			/* entry to active */
		    vectptr->param = -((vectptr->dx >> 1) + (vectptr->dy >> 1));
		else
		    vectptr->param = (vectptr->dx >> 1) - (vectptr->dy >> 1);

		p = vectptr;			/* remove from the */
		vectptr = vectptr->next;	/* waiting list */
		vectptr->prev = p->prev;
		p->prev->next = vectptr;
						/* find where it goes */
						/* in the active list */
						/* (sorted smallest first) */
		for (v = activehead->next; v->currx < p->currx; v = v->next)
		    ;
		p->next = v;		/* insert into active list */
		p->prev = v->prev;	/* before the one it stopped on */
		v->prev = p;
		p->prev->next = p;
		active++;
	    } else {
		if (i > vectptr->param) {
		    i = vectptr->param;
		}
		vectptr = vectptr->next;
	    }
	}
	nexty = i;

					/* print the polygon while there */
					/* are no more vectors to add */
	while (miny < nexty) {
					/* remove any finished vectors */
	    vectptr = activehead->next;
	    do {
		if (vectptr->endy <= miny) {
		    vectptr->prev->next = vectptr->next;
		    vectptr->next->prev = vectptr->prev;
		    active--;
		}
	    } while ((vectptr = vectptr->next) != activehead);

					/* output a polygon for this band */
	    if (firsttime || !(miny % NLINES)) {
		register int numwait;	/* number in the waiting list */
		register int newmaxy;	/* max for this band (bottom or maxy)*/


		startspan(miny);
		if ((newmaxy = (miny / NLINES) * NLINES + (NLINES - 1)) > maxy)
		    newmaxy = maxy;

					/* count up those vectors that WILL */
					/* become active in this band */
		for (numwait = 0, vectptr = waitinghead->next;
				vectptr != NULL; vectptr = vectptr->next) {
		    if (vectptr->param <= newmaxy)
			numwait++;
		}

		sprintf(op,"Dq %d %d %d %d",member,active+numwait,miny,newmaxy);
		op += strlen(op);
		for (i = active, vectptr = activehead->next; i--;
						vectptr = vectptr->next) {
		    sprintf(op, " %d %d %d %d %d",
			    vectptr->param, vectptr->dx, -vectptr->dy,
			    vectptr->currx, vectptr->endy);
		    op += strlen(op);
		}
		for (vectptr = waitinghead->next; vectptr != NULL;
						vectptr = vectptr->next) {
		    if (vectptr->param <= newmaxy) {
			sprintf(op, " %d %d %d %d %d",
				vectptr->param, vectptr->dx, vectptr->dy,
				vectptr->currx, vectptr->endy);
			op += strlen(op);
		    }
		}
		*(op++) = '\n';
		firsttime = 0;
	    }

					/* update the vectors */
	    vectptr = activehead->next;
	    do {
		if (vectptr->dx > 0) {
		    while (vectptr->param >= 0) {
			vectptr->param -= vectptr->dy;
			vectptr->currx++;
		    }
		    vectptr->param += vectptr->dx;
		} else if (vectptr->dx < 0) {
		    while (vectptr->param >= 0) {
			vectptr->param -= vectptr->dy;
			vectptr->currx--;
		    }
		    vectptr->param -= vectptr->dx;
		}
					/* must sort the vectors if updates */
					/* caused them to cross */
					/* also move to next vector here */
		if (vectptr->currx < vectptr->prev->currx) {
		    register polyvector *v;		/* vector to move */
		    register polyvector *p;	/* vector to put it after */

		    v = vectptr;
		    p = v->prev;
		    while (v->currx < p->currx)	/* find the */
			p = p->prev;		/* right vector */

		    vectptr = vectptr->next;	/* remove from spot */
		    vectptr->prev = v->prev;
		    v->prev->next = vectptr;

		    v->prev = p;		/* put in new spot */
		    v->next = p->next;
		    p->next = v;
		    v->next->prev = v;
		} else {
		    vectptr = vectptr->next;
		}
	    } while (vectptr != activehead);

	    ++miny;
	} /* while (miny < nexty) */
    } /* while (miny <= maxy) */

leavepoly:
    startspan(vpos);	/* make sure stuff after polygon is at correct vpos */
    free(waitinghead);
}  /* polygon function */
E 12
E 1
