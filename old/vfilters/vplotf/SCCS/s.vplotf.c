h03196
s 00001/00011/00494
d D 5.5 90/06/01 18:48:08 bostic 10 9
c new copyright notice
e
s 00010/00005/00495
d D 5.4 88/06/30 17:53:32 bostic 9 8
c install approved copyright notice
e
s 00015/00003/00485
d D 5.3 88/03/08 08:30:19 bostic 8 7
c add Berkeley specific header
e
s 00001/00001/00487
d D 5.2 85/11/11 18:19:21 mckusick 7 6
c fix macro so that circles do not come out as squares (from mcvax!jaap)
e
s 00007/00001/00481
d D 5.1 85/05/15 11:33:26 dist 6 5
c Add copyright notice
e
s 00001/00001/00481
d D 4.4 84/03/12 16:05:48 ralph 5 4
c fix page accounting computation.
e
s 00004/00001/00478
d D 4.3 83/07/16 23:49:04 sam 4 3
c add useful sccs id's
e
s 00024/00015/00455
d D 4.2 83/05/23 14:49:07 ralph 3 1
c changes for px and py printcap entries.
e
s 00022/00013/00457
d R 4.2 83/05/16 17:21:44 ralph 2 1
c changes for px and py printcap entries.
e
s 00470/00000/00000
d D 4.1 83/05/03 15:38:08 ralph 1 0
c date and time created 83/05/03 15:38:08 by ralph
e
u
U
t
T
I 6
/*
 * Copyright (c) 1983 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 8
 */

E 6
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
#ifndef lint
I 8
char copyright[] =
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif
E 6
I 6
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 6

E 4
/*
 *  Lpd filter to read standard graphics input and produce a plot on the
 *  Varian or Versatec
 */

#include <stdio.h>
#include <vfont.h>
#include <sys/vcmd.h>

#define	mapx(x)	((DevRange*((x)-botx)/del)+centx)
#define	mapy(y)	((DevRange*(del-(y)+boty)/del)-centy)
#define SOLID -1
#define DOTTED 014
#define SHORTDASHED 034
#define DOTDASHED 054
#define LONGDASHED 074

D 3
static char *Sid = "%Z%\t%G%";
E 3
I 3
static char *Sid = "@(#)\t5/16/83";
E 3

int	linmod = SOLID;
int	done1;
char	chrtab[][16];
char	*obuf;
int	bufsize;
int	lastx;
int	lasty;
int	radius, startx, starty, endx, endy;
double	topx;
double	topy;
double	botx;
double	boty;
int	centx = 0;
int	centy = 0;
double	delx;
double	dely;
double	del;

int	warned = 0;	/* Indicates whether the warning message about
			 * unimplemented routines has been printed */

int	plotmd[] = {VPLOT};
int	prtmd[]  = {VPRINT};
D 3
int	varian = 1;		/* default is the varian */
E 3
I 3
int	varian;			/* 0 for versatec, 1 for varian. */
int	BYTES_PER_LINE;		/* number of bytes per raster line. */
int	PAGE_LINES;		/* number of raster lines per page. */
E 3
int	DevRange = 1536;	/* output array size (square) in pixels */
int	DevRange8 = 1536/8;	/* output array size in bytes */
D 3
int	BytesPerLine = 264;	/* Bytes per raster line (physical) */
E 3
int	lines;			/* number of raster lines printed */
char	zeros[880];		/* one raster line */

char	*name, *host, *acctfile;

D 3
/* variables for used to print from font file */
E 3
I 3
/* variables used to print from font file */
E 3
int	fontSet = 0;		/* Has the font file been read */
struct	header header;
struct	dispatch dispatch[256];
char	*bits;
D 3
char	*fontFile = "/usr/lib/vfont/R.10";
E 3
I 3
char	*fontFile = "/usr/lib/vfont/R.8";
E 3

main(argc, argv)
	int argc;
	char *argv[];
{
	register char *cp, *arg;
	register n, again;

D 3
	if (argv[0][strlen(argv[0])-1] == 'W') {
		varian = 0;
		DevRange = 2048;
		DevRange8 = 2048/8;
		BytesPerLine = 880;
	}

E 3
	while (--argc) {
		if (**++argv == '-') {
			switch (argv[0][1]) {
I 3
			case 'x':
				BYTES_PER_LINE = atoi(&argv[0][2]) / 8;
				if (varian = BYTES_PER_LINE == 264) {
					DevRange = 1536;
					DevRange8 = 1536/8;
				} else {
					DevRange = 2048;
					DevRange8 = 2048/8;
				}
				break;

			case 'y':
				PAGE_LINES = atoi(&argv[0][2]);
				break;

E 3
			case 'n':
				argc--;
				name = *++argv;
				break;

			case 'h':
				argc--;
				host = *++argv;
			}
		} else
			acctfile = *argv;
	}

	/* init constants for scaling */
	topx = topy = DevRange;
	botx = boty = 0;
	delx = dely = del = DevRange;
	centx = (DevRange - mapx(topx))/2;
	centy = mapy(topy)/2;

	if ((obuf = (char *) malloc(bufsize = DevRange * DevRange8)) == NULL) {
		fprintf(stderr, "vplotf: ran out of memory\n");
		exit(2);
	}

	do {
		arg = &obuf[bufsize];
		for (cp = obuf; cp < arg; )
			*cp++ = 0;

		again = getpict();

		ioctl(1, VSETSTATE, plotmd);
D 3
		n = BytesPerLine - DevRange8;
E 3
I 3
		n = BYTES_PER_LINE - DevRange8;
E 3
		for (cp = obuf; cp < arg; cp += DevRange8) {
			if (write(1, cp, DevRange8) != DevRange8)
				exit(1);
			if (n && write(1, zeros, n) != n)
				exit(1);
			lines++;
		}
		ioctl(1, VSETSTATE, prtmd);
		if (varian)
			write(1, "\f", 2);
		else
			write(1, "\n\n\n\n\n", 6);
	} while (again);

	account(name, host, *argv);
	exit(0);
}

account(who, from, acctfile)
	char *who, *from, *acctfile;
{
	register FILE *a;

	if (who == NULL || acctfile == NULL)
		return;
	if (access(acctfile, 02) || (a = fopen(acctfile, "a")) == NULL)
		return;
	/*
	 * Varian accounting is done by 8.5 inch pages;
	 * Versatec accounting is by the (12 inch) foot.
	 */
D 3
	fprintf(a, "t%6.2f\t", (lines / 200.0) / (varian ? 8.5 : 12.0));
E 3
I 3
D 5
	fprintf(a, "t%6.2f\t", (lines / 200.0) / PAGE_LINES);
E 5
I 5
	fprintf(a, "t%6.2f\t", (double)lines / (double)PAGE_LINES);
E 5
E 3
	if (from != NULL)
		fprintf(a, "%s:", from);
	fprintf(a, "%s\n", who);
	fclose(a);
}

getpict()
{
	register x1, y1;

	for (;;) switch (x1 = getc(stdin)) {

	case '\n':
		continue;

	case 's':
		botx = getinteger(stdin);
		boty = getinteger(stdin);
		topx = getinteger(stdin);
		topy = getinteger(stdin);
		delx = topx-botx;
		dely = topy-boty;
		if (dely/delx > 1536./2048.)
			del = dely;
		else
			del = delx;
		centx = 0;
		centx = (DevRange - mapx(topx))/2;
		centy = 0;
		centy = mapy(topy) / 2;
		continue;

	case 'b':
		x1 = getc(stdin);
		continue;

	case 'l':
		done1 |= 01;
		x1 = mapx(getinteger(stdin));
		y1 = mapy(getinteger(stdin));
		lastx = mapx(getinteger(stdin));
		lasty = mapy(getinteger(stdin));
		line(x1, y1, lastx, lasty);
		continue;

	case 'c':
		x1 = mapx(getinteger(stdin));
		y1 = mapy(getinteger(stdin));
		radius = mapx(getinteger(stdin));
		circle(x1, y1, radius);
		continue;
		
	case 'a':
		x1 = mapx(getinteger(stdin));
		y1 = mapy(getinteger(stdin));
		startx = mapx(getinteger(stdin));
		starty = mapy(getinteger(stdin));
		endx = mapx(getinteger(stdin));
		endy = mapy(getinteger(stdin));
		if (!warned) {
			fprintf(stderr,"Arcs are unimplemented\n");
			warned++;
		}
		continue;

	case 'm':
		lastx = mapx(getinteger(stdin));
		lasty = mapy(getinteger(stdin));
		continue;

	case 't':
		lastx = lastx - 6;
		lasty = lasty + 6;
		done1 |= 01;
		while ((x1 = getc(stdin)) != '\n')
			plotch(x1);
		continue;

	case 'e':
		if (done1)
			return(1);
		continue;

	case 'p':
		done1 |= 01;
		lastx = mapx(getinteger(stdin));
		lasty = mapy(getinteger(stdin));
		point(lastx, lasty);
		point(lastx+1, lasty);
		point(lastx, lasty+1);
		point(lastx+1, lasty+1);
		continue;

	case 'n':
		done1 |= 01;
		x1 = mapx(getinteger(stdin));
		y1 = mapy(getinteger(stdin));
		line(lastx, lasty, x1, y1);
		lastx = x1;
		lasty = y1;
		continue;

	case 'f':
		getinteger(stdin);
		getc(stdin);
		switch (getc(stdin)) {
		case 't':
			linmod = DOTTED;
			break;
		default:
		case 'i':
			linmod = SOLID;
			break;
		case 'g':
			linmod = LONGDASHED;
			break;
		case 'r':
			linmod = SHORTDASHED;
			break;
		case 'd':
			linmod = DOTDASHED;
			break;
		}
		while ((x1 = getc(stdin)) != '\n')
			if (x1 == EOF)
				return(0);
		continue;

	case 'd':
		getinteger(stdin);
		getinteger(stdin);
		getinteger(stdin);
		x1 = getinteger(stdin);
		while (--x1 >= 0)
			getinteger(stdin);
		continue;

	case 0:		/* ignore null characters */
		continue;

	case 255:
	case EOF:
		return(0);

	default:
		fprintf(stderr, "Input format error %c(%o)\n",x1,x1);
		exit(2);
	}
}

plotch(ch)
char ch;
{
	register int i,j,k;
	register char *ptr,c;
	int nbytes;

	if (!fontSet)
		InitFont();	/* Read font if not already read */

	ptr = bits + dispatch[ch].addr;

	for (i = dispatch[ch].up; i > -dispatch[ch].down; --i) {
		nbytes = (dispatch[ch].right + dispatch[ch].left + 7)/8;
		for (j = 0; j < nbytes; j++) {
			c = *ptr++;
			for (k = 7; k >= 0; k--)
				if ((c >> k) & 1)
					point(lastx+7-k+j*8-dispatch[ch].left, lasty-i);
		}
	}
	if (ch != ' ')
		lastx += dispatch[ch].width;
	else
		lastx += dispatch['a'].width;
}

InitFont()
{
	char *s;
	int fonts;
	int i;

	fontSet = 1;
	/* Get the font file */
	s = fontFile;
	if ((fonts = open(s, 0)) == -1) {
		perror(s);
		fprintf(stderr, "Can't get font file");
		exit(2);
	}
	/* Get the header and check magic number */
	if (read(fonts, &header, sizeof(header)) != sizeof(header)) {
		perror(s);
		fprintf(stderr, "Bad read in font file");
		exit(2);
	}
	if (header.magic != 0436) {
		fprintf(stderr,"Bad magic numer in font file");
		exit(2);
	}
	/* Get dispatches */
	if (read(fonts, dispatch, sizeof(dispatch)) != sizeof(dispatch)) {
		perror(s);
		fprintf(stderr, "Bad read in font file");
		exit(2);
	}
	/* Allocate space for bit map and read in bits */
	bits = (char *) malloc(header.size);
	if (read(fonts, bits, header.size) != header.size) {
		perror(s);
		fprintf(stderr,"Can't read bit map in font file");
		exit(2);
	}
	/* Close font file */
	if (close(fonts) != 0) {
		perror(s);
		fprintf(stderr,"Can't close font file");
		exit(2);
	}
}

line(x0, y0, x1, y1)
register x0, y0;
{
	int dx, dy;
	int xinc, yinc;
	register res1;
	int res2;
	int slope;

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
	slope = xinc*yinc;
	res1 = 0;
	res2 = 0;
	if (dx >= dy) while (x0 != x1) {
		if ((x0+slope*y0) & linmod)
			point(x0, y0);
		if (res1 > res2) {
			res2 += dx - res1;
			res1 = 0;
			y0 += yinc;
		}
		res1 += dy;
		x0 += xinc;
	} else while (y0 != y1) {
		if ((x0+slope*y0) & linmod)
		point(x0, y0);
		if (res1 > res2) {
			res2 += dy - res1;
			res1 = 0;
			x0 += xinc;
		}
		res1 += dx;
		y0 += yinc;
	}
	if ((x1+slope*y1) & linmod)
		point(x1, y1);
}

D 7
#define labs(a) (a >= 0 ? a : -a)
E 7
I 7
#define labs(a) ((a) >= 0 ? (a) : -(a))
E 7

circle(x,y,c)
{
	register dx, dy;
	long ep;
	int de;

	dx = 0;
	ep = 0;
	for (dy=c; dy>=dx; dy--) {
		for (;;) {
			point(x+dx, y+dy);
			point(x-dx, y+dy);
			point(x+dx, y-dy);
			point(x-dx, y-dy);
			point(x+dy, y+dx);
			point(x-dy, y+dx);
			point(x+dy, y-dx);
			point(x-dy, y-dx);
			ep += 2*dx + 1;
			de = -2*dy + 1;
			dx++;
			if (labs(ep) >= labs(ep+de)) {
				ep += de;
				break;
			}
		}
	}
}

/*
 * Points should be in the range 0 <= x (or y) <= DevRange.
 * The origin is the top left-hand corner with increasing x towards the
 * right and increasing y going down.
 */
point(x, y)
register unsigned x, y;
{
	register unsigned byte;

	if (x < DevRange && y < DevRange) {
		byte = y * DevRange8 + (x >> 3);
		obuf[byte] |= 1 << (7 - (x & 07));
	}
}

getinteger(f)
FILE *f;
{
	register int low, high, result;

	low = getc(f);
	high = getc(f);
	result = ((high << 8) | low);
	if (high > 127)
		result |= ~0xffff;
	return(result);
}
E 1
