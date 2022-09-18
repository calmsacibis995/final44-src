h43877
s 00051/00043/00261
d D 1.6 85/02/04 15:25:36 slatteng 10 6
c total revamp ...
e
s 00030/00021/00283
d R 1.6 85/02/04 11:56:01 slatteng 9 6
c Total revamp and cleanup.
e
s 00028/00018/00286
d R 1.6 85/02/01 17:22:13 slatteng 8 6
c fix for characters that have one line hanging below the reference point
e
s 00026/00018/00286
d R 1.6 85/02/01 12:41:48 slatteng 7 6
c reworked, commented some... fixed jaggies on right-side of vertical stuff
e
s 00038/00017/00266
d D 1.5 85/01/30 14:46:12 slatteng 6 5
c cleaned up code a bit.
e
s 00002/00002/00281
d D 1.4 84/04/12 18:38:09 slatteng 5 3
c change "header" to "fontheader"
e
s 00001/00001/00282
d R 1.4 84/02/27 18:21:07 slatteng 4 3
c change "header" to "fontheader"
e
s 00174/00076/00109
d D 1.3 84/01/04 14:21:17 slatteng 3 2
c installed new scaling algorithm
e
s 00075/00024/00110
d D 1.2 83/12/06 13:52:32 slatteng 2 1
c change scaling algorithm to be a bit smarter (only a bit)
e
s 00134/00000/00000
d D 1.1 83/12/01 11:17:32 slatteng 1 0
c date and time created 83/12/01 11:17:32 by slatteng
e
u
U
t
T
I 1
D 2
/* Font scaling for character format fonts.
E 2
I 2
D 10
/*	%M%	(Berkeley)	%I%	%E%
E 10
I 10
/*	%M%	%I%	%E%
E 10
E 2
 *
I 2
 * Font scaling for character format fonts.
 *
E 2
D 6
 *	Use:	scalech  [ -s# ]  charfile1  > charfile2
E 6
I 6
 *	Use:	scalech  [ -s# ]  [ charfile1 ]  > charfile2
E 6
 *
 *		Takes input from charfile1 (which must be in the format
D 6
 *	written by rst2ch), scales by # (default = 50%) and writes to stdout.
 *	If charfile1 is missing, stdin is read.  The -s flag sets the scaling
 *	factor to # (which is a percentage REDUCTION - can't make fonts bigger)
E 6
I 6
 *	written by any of the xxx2ch programs), scales by # (default = 50%)
 *	and writes to stdout.  If charfile1 is missing, stdin is read.  The
 *	-s flag sets the scaling factor to # (which is a percentage REDUCTION:
 *	scalech can't make fonts bigger)
E 6
 */

#include <stdio.h>
D 6
#include <ctype.h>
E 6


D 6
#define MAXLINE		200
I 3
#define MAXHEIGHT	200
E 6
I 6
#define MAXLINE		300
#define MAXHEIGHT	300
E 6
E 3
#define SCALE		50

D 6

E 6
I 6
					/* don't ask, really */
E 6
D 2
int	width, length, refv, refh, code;
E 2
I 2
int	width, length, vdest, hdest, code;
D 3
int	refh, spot, start, Bduring, Wduring;
E 3
I 3
int	refv, refh, spot, start, Bduring, Wduring;
D 10
int	notfirsttime, build, voffset, hoffset;
E 10
I 10
int	notfirsttime, build, refvdest, refhdest, destwidth;
E 10
E 3
E 2

D 10
int	scale = SCALE;
E 10
I 10
int	scale = SCALE;		/* percentage to scale by (in 100's) */
int	hscale;			/* half scale value:  used in computations */
E 10
FILE *	filep;
D 2
char	ibuff[MAXLINE];
char	ebuff[MAXLINE];
E 2
I 2
D 3
char	ibuff[MAXLINE], ebuff[MAXLINE];
E 3
I 3
char	ibuff[MAXHEIGHT][MAXLINE], ebuff[MAXLINE];
E 3
E 2

I 2
D 3
unsigned char Black[MAXLINE];	/* arrays to figure new scaled line based */
unsigned char BtoW[MAXLINE];	/* on various conditions of the changes in */
unsigned char WtoB[MAXLINE];	/* pixels within lines */
unsigned char WBW[MAXLINE];
unsigned char BWB[MAXLINE];
unsigned char White[MAXLINE];
E 3
I 3
unsigned char lastline[MAXLINE];	/* last printed line */
unsigned char Black[2][MAXLINE];	/* arrays to figure new */
unsigned char WtoB[2][MAXLINE];		/* scaled line based on */
unsigned char BtoW[2][MAXLINE];		/* pixels within lines */
unsigned char White[2][MAXLINE];
E 3
E 2

I 2

E 2
main(argc,argv)
int argc;
char **argv;
{
    register int i;
    register int j;
    register char *chp;
    float par;

    while (argc > 1 && argv[1][0] == '-') {
	switch(argv[1][1]) {
	case 's':
		scale = atoi (&(argv[1][2]));
		break;
	default:
		error("%s, unknown option flag", argv[1]);
	}
	argc--; argv++;
    }

    if (argc == 2) {
	if ((filep = fopen (argv[1], "r")) == NULL)
	    error("can't open file \"%s\"", argv[1]);
    } else filep = stdin;

I 10
    hscale = scale / 2;
E 10
    fgets(ibuff, MAXLINE, filep);
D 5
    if (strcmp(ibuff, "header\n"))
E 5
I 5
    if (strcmp(ibuff, "fontheader\n"))
E 5
	error("not a character font file");
D 5
    printf("header\n");
E 5
I 5
    printf("fontheader\n");
E 5

    while (fgets(ibuff, MAXLINE, filep) != NULL) {
	if (index(ibuff, '\n') == 0)
	    error("input line too long");

D 3
	if (ibuff[0] != ':') {
E 3
I 3
	if (ibuff[0][0] != ':') {
E 3
	    sscanf (ibuff, "%s %f", ebuff, &par);
	    if (strcmp(ebuff, "mag") == 0)
D 6
		printf("mag %d\n", (int) (par * scale / 100 + 0.1));
E 6
I 6
		printf("mag %d\n", (int) (par * scale / 100.0 + 0.1));
E 6
	    else if (strcmp(ebuff, "linesp") == 0)
D 6
		printf("linesp %.2f\n", par * scale / 100 + 0.001);
E 6
I 6
		printf("linesp %.2f\n", par * scale / 100.0 + 0.001);
E 6
	    else if (strcmp(ebuff, "wordsp") == 0)
D 6
		printf("wordsp %.2f\n", par * scale / 100 + 0.001);
E 6
I 6
		printf("wordsp %.2f\n", par * scale / 100.0 + 0.001);
E 6
	    else
		printf("%s", ibuff);
	} else {
	    if (sscanf (ibuff, ":%d, width = %f", &code, &par) != 2)
		error("bad glyph header, %s", ibuff);
	    printf(":%d, width = %.2f\n", code, (par * scale) / 100.0 + 0.001);

	    if (fgets(ibuff, MAXLINE, filep) == NULL)
		error("unexpected end of input");
D 3
	    width = strlen(ibuff) - 1;

D 2
	    for (j = 0; j < MAXLINE; ebuff[j++] = '.');
	    refv = 1;
E 2
I 2
	    vdest = 1;
	    refh = -1;
E 2
	    for (length = 1; *(chp = ibuff) != '\n'; length++) {
I 2
		hdest = 0;
		start = 0;
		Bduring = 0;
		Wduring = 0;
E 3
I 3
	    width = strlen(&(ibuff[0][0])) - 1;
						/* first read in whole glyph */
	    refh = -1;				/* and put in ibuff */
	    for (length = 0; *(chp = &(ibuff[length][0])) != '\n'; length++) {
E 3
E 2
D 10
		for (j = 0; j < width; j++, chp++) {
E 10
I 10
		for (j = 0; j <= width; j++, chp++) {
E 10
D 2
		    refh = (j * scale) / 100 + 0.1;
E 2
I 2
D 3
		    if (hdest != (int) ((j * scale) / 100 + 0.1)) {
			if (start && !Wduring) Black[hdest]++;
			if (start && !spot) BtoW[hdest]++;
			if ((!start) && spot) WtoB[hdest]++;
			if ((!start) && Bduring && !spot) WBW[hdest]++;
			if (start && Wduring && spot) BWB[hdest]++;
			if ((!start) && !Bduring) White[hdest]++;

			hdest = (j * scale) / 100 + 0.1;
			start = spot;
			Bduring = 0;
			Wduring = 0;
		    }
		    spot = 0;
E 3
E 2
		    switch (*chp) {
I 3
			case '@':
			case '*':
				*chp = 1;
				break;
E 3
			case '.':
I 10
			case '\n':
			case '\r':
E 10
I 3
				*chp = 0;
E 3
				break;
I 2
D 3
			case 'X':
				spot = 1;
E 3
E 2
			case 'x':
D 2
				if (ebuff[refh] == '.')
				    ebuff[refh] = 'x';
				else
				    ebuff[refh] = 'X';
E 2
I 2
D 3
				if (refh >= 0)
E 3
I 3
				*chp = 0;
				goto mark;
			case 'X':
				*chp = 1;
		mark:		if (refh >= 0)
E 3
				    error ("glyph %d - two reference points",
									code);
D 3
				refh = hdest;
E 3
I 3
D 10
				refh = j + 1;
E 10
I 10
				refh = j;
E 10
				refv = length;
E 3
E 2
				break;
D 2
			case 'X':
				ebuff[refh] = 'X';
				break;
E 2
D 3
			case '@':
D 2
			case 'a':
				if (ebuff[refh] == 'x')
				    ebuff[refh] = 'X';
				else if (ebuff[refh] != 'X')
				    ebuff[refh] = '@';
E 2
I 2
			case '*':
				spot = 1;
E 2
				break;
E 3
			default:
				error("illegal character '%c' in map.", *chp);
D 3
		    } /* switch */
E 3
I 3
		    }
		}
		if (fgets(&(ibuff[length + 1][0]), MAXLINE, filep) == NULL)
			error("unexpected end of input");
	    }
	    if (refh < 0) error("No position point in glyph %d", code);


D 10
	    voffset = (refv * scale) / 100;
	    hoffset = (refh * scale) / 100;
E 10
I 10
	    refvdest = (refv * scale + hscale) / 100;
	    refhdest = (refh * scale - hscale) / 100 + (refh ? 2 : 1);
	    destwidth = refhdest + ((width - refh) * scale - hscale) / 100;
E 10
	    vdest = 0;
	    notfirsttime = 0;
I 10
	    build = 0;
E 10
	    for (j = 0; j <= width; j++)
D 10
		Black[build][j] = BtoW[build][j] =
			WtoB[build][j] = White[build][j] = 0;
E 10
I 10
		Black[build][j] = BtoW[build][j] = WtoB[build][j] =
		    White[build][j] = lastline[j] = 0;
E 10

	    for (i = 0; i < length; i++) {
		chp = &(ibuff[i][0]);
		hdest = 1;
		start = 0;
		Bduring = 0;
		Wduring = 0;
		White[build][0]++;
D 10
		for (j = 0; j < width; j++, chp++) {
		    code = ((j-refh) * scale) / 100 + (j<refh ? 1:2) + hoffset;
E 10
I 10
		for (j = 0; j <= width; j++, chp++) {
		    code = ((j-refh)*scale+hscale)/100+refhdest-((j<refh)?1:0);
E 10
		    if (hdest != code) {
			if ((start && !Wduring) ||
			    ((!start)&& Bduring &&!spot)) Black[build][hdest]++;
			if (start && !spot) BtoW[build][hdest]++;
			if ((!start) && spot) WtoB[build][hdest]++;
			if (((!start) && !Bduring) ||
			    (start && Wduring && spot)) White[build][hdest]++;

			hdest = code;
			start = spot;
			Bduring = 0;
			Wduring = 0;
		    }

		    spot = *chp;
E 3
I 2
		    Bduring |= spot;
		    Wduring |= !spot;
E 2
		} /* for j */
I 2

D 3
		if (start && !Wduring) Black[hdest]++;
		if (start) BtoW[hdest]++;
		if ((!start) && Bduring) WBW[hdest]++;
		if ((!start) && !Bduring) White[hdest]++;
E 3
I 3
		if ((start && !Wduring)
		    || ((!start) && Bduring)) Black[build][hdest]++;
		if (start) BtoW[build][hdest]++;
		if ((!start) && !Bduring) White[build][hdest]++;
E 3
D 10

E 2
D 3
		if (fgets(ibuff, MAXLINE, filep) == NULL)
			error("unexpected end of input");
E 3
I 3
		code = voffset - (((refv - (i+1))*scale)/100 - (i>=refv ? 1:0));
E 10
I 10
				/* look at what line we're gonna build for NEXT
				   and if that's different than what we WERE
				   building for, output the line BEFORE that */
		code = refvdest+((i>=refv)?1:0)-((refv-(i+1))*scale+hscale)/100;
E 10
		if (code != vdest || i == (length - 1)) {
		    if (notfirsttime)
D 10
			outline(vdest == (voffset + 1));
E 10
I 10
			outline(vdest == (refvdest + 1));
E 10
		    else
			notfirsttime = 1;
		    vdest = code;
E 3

D 2
		if (((int) ((length * scale) / 100 + 0.1)) == refv
E 2
I 2
D 3
		if (((int) ((length * scale) / 100 + 0.1)) == vdest
E 2
							|| ibuff[0] == '\n') {
D 2
		    refh = (width * scale) / 100 + 0.1;
		    for (j = 0; refh-- > 0; putchar(ebuff[j++]));
E 2
I 2
		    i = (width * scale) / 100 + 0.1;
		    for (j = 0; i-- > 0; j++) {
			if (Black[j] || WBW[j]) spot = 1;
			else if (BWB[j]) spot = 0;
			else if (WtoB[j]) spot = 1;
			else spot = 0;
			if (spot)  {
			    if (j != refh) putchar('@');
			    else {
				putchar('X');
				refh = 2 * width;
			    }
			} else {
			    if (j != refh) putchar('.');
			    else {
				putchar('x');
				refh = 2 * width;
			    }
			}
		    }
E 2
		    putchar('\n');
E 3
I 3
		    build = !build;
E 3
D 2
		    for (j = 0; j <= width; ebuff[j++] = '.');
		    refv = (length * scale) / 100 + 1.1;
E 2
I 2
		    for (j = 0; j <= width; j++)
D 3
			Black[j] = BtoW[j] = WtoB[j] =
				WBW[j] = BWB[j] = White[j] = 0;
		    vdest = (length * scale) / 100 + 1.1;
E 3
I 3
			Black[build][j] = BtoW[build][j] =
				WtoB[build][j] = White[build][j] = 0;
E 3
E 2
		}
D 3
	    } /* for length */
I 2
	    if (refh < 0) error("No position point in glyph %d", code);
E 3
I 3
	    } /* for i */

	    for (j = 0; j <= width; j++) White[build][j] = 1;
D 10
	    outline(vdest == (voffset + 1));		/* output last line */
E 3
E 2
	    putchar('\n');
	} /* else */
E 10
I 10
	    outline(refv == length - 1);	/* output last line - ref */
	    putchar('\n');			/* point only if it's on the */
	} /* else */				/* last line of the block */
E 10
    } /* while */
I 10
    exit(0);
E 10
}

I 3
D 6
outline(i)
register int i;
E 6
I 6

I 10
#define	upleft	(lastline[j-1])
#define	up	(lastline[j])
#define	upright	(lastline[j+1])

E 10
/*----------------------------------------------------------------------------*
 | Routine:	outline (baseline)
 |
 | Results:	outputs a row of dots, based on gobs of information gathered
 |		in the main program.  If "baseline" is set, then this line
 |		should have the reference point on it.
 |
 | Bugs:	this method smells
 *----------------------------------------------------------------------------*/

outline(baseline)
int baseline;
E 6
{
	register int set;
	register int output = !build;
	register int j;
D 10
	int oldset = 0;
E 10
I 10
	register int left = 0;
	int right, down, downright, downleft;
E 10
E 3

I 3
D 10
	for (j = 1; j <= hdest; j++) {
E 10
I 10
	for (j = 1; j <= destwidth; j++) {
E 10
					/* decide whether to put out a '.' */
					/* or '@' spot for pixel j */
D 10
		set = ((!BtoW[output][j]) << 3) | ((!WtoB[output][j]) << 2) |
E 10
I 10
	    right = Black[output][j+1] || WtoB[output][j+1];
	    downleft = Black[build][j-1] || WtoB[build][j-1];
	    down = Black[build][j] || WtoB[build][j];
	    downright = Black[build][j+1] || WtoB[build][j+1];

	    set = ((!BtoW[output][j]) << 3) | ((!WtoB[output][j]) << 2) |
E 10
			((!White[output][j]) << 1) | !Black[output][j];
D 10
		switch (set) {
E 10
I 10
	    switch (set) {
E 10
		case 14:	/* all black */
		case 11:	/* all white->black */
		case 10:	/* black and white->black */
		case  2:	/* everything but all white */
		    set = 1;
		    break;

		case 13:	/* all white */
		case  7:	/* all black->white */
		case  5:	/* white and black->white */
I 10
		case  1:	/* everything but all black */
E 10
		    set = 0;
		    break;

D 10
		case  1:	/* everything but all black */
		    if (oldset && (Black[output][j+1] || WtoB[output][j+1]))
			set = 0;
		    else
			set = 1;
		    break;

		case 12:	/* black and white only */
E 10
I 10
		case 12:	/* black and white */
E 10
		case  8:	/* black and white and white->black */
		case  4:	/* black and white and black->white */
D 10
		    if (Black[build][j])
E 10
I 10
		    if (down)
E 10
			set = !lastline[j];
		    else
			set = 1;
		    break;

		case  6:	/* black and black->white */
D 10
		    if (lastline[j] && !White[build][j])
E 10
I 10
		    if (right && upright && downright && (down || up))
E 10
			set = 0;
		    else
			set = 1;
		    break;

		case  9:	/* white and white->black */
D 10
		    if ((!lastline[j] && !Black[build][j] && !WtoB[build][j])
				|| White[output][j+1] || BtoW[output][j+1])
E 10
I 10
		    if ((up && upright) || (down && downright) || left || right)
E 10
			set = 1;
		    else
			set = 0;
		    break;

		case 15:	/* none of them */
		case  3:	/* black->white and white->black */
		case  0:	/* everything */
D 10
		    if (lastline[j-1] + lastline[j] + lastline[j+1] + oldset +
			(Black[output][j+1] || WtoB[output][j+1]) + 
			(Black[build][j-1] || WtoB[build][j-1]) + 
			(Black[build][j] || WtoB[build][j]) + 
			(Black[build][j+1] || WtoB[build][j+1]) > 5)
E 10
I 10
		    if((up+down+right+left+upright+downleft+upleft+downright)>4)
E 10
			set = 0;
		    else
			set = 1;
		    break;
		}

		if (set)  {
D 6
		    if (!i || j != (hoffset + 1))
E 6
I 6
D 10
		    if (!baseline || j != (hoffset + 1))
E 10
I 10
		    if (!baseline || j != refhdest)
E 10
E 6
			putchar('@');
		    else
			putchar('X');
		} else {
D 6
		    if (!i || j != (hoffset + 1))
E 6
I 6
D 10
		    if (!baseline || j != (hoffset + 1))
E 10
I 10
		    if (!baseline || j != refhdest)
E 10
E 6
			putchar('.');
		    else
			putchar('x');
		}
D 10
		lastline[j-1] = oldset;
		oldset = set;
E 10
I 10
		lastline[j-1] = left;
		left = set;
E 10
	}
D 10
	lastline[j-1] = oldset;
E 10
I 10
	lastline[j-1] = left;
E 10
	putchar('\n');
}

I 6

/*----------------------------------------------------------------------------*
 | Routine:	error (format_string, argument1, argument2.... )
 |
 | Results:	fprints a message to standard error, then exits with error
 |		code 1.
 |
 | Side Efct:	This routine does NOT return
 *----------------------------------------------------------------------------*/

E 6
E 3
/*VARARGS1*/
error(string, a1, a2, a3, a4)
char *string;
{ 
D 3
	fprintf(stderr, "ch2rst: ");
E 3
I 3
	fprintf(stderr, "scalech: ");
E 3
	fprintf(stderr, string, a1, a2, a3, a4);
	fprintf(stderr, "\n");
D 6
	exit(8);
};
E 6
I 6
	exit (1);
}
E 6
E 1
