h44411
s 00016/00014/00307
d D 1.7 86/03/04 12:43:30 slatteng 8 7
c Take out dependencies on RES-olution defined in rst.h
e
s 00018/00006/00303
d D 1.6 85/02/19 13:42:36 slatteng 7 5
c added a couple more idiot-proof checks
e
s 00014/00006/00303
d R 1.6 85/02/15 16:42:42 slatteng 6 5
c added a couple more idiot-proff checks
e
s 00080/00056/00229
d D 1.5 85/01/31 19:34:11 slatteng 5 4
c cleanup... added comments, etc.
e
s 00016/00002/00269
d D 1.4 84/04/07 15:53:50 slatteng 4 3
c added -s option
e
s 00001/00001/00270
d D 1.3 84/02/27 18:22:07 slatteng 3 2
c change "header" to ""
e
s 00019/00007/00252
d D 1.2 84/02/16 15:11:24 slatteng 2 1
c adda bit of error checking if no bits are on in a glyph, or overflow
e
s 00259/00000/00000
d D 1.1 84/02/13 15:31:34 slatteng 1 0
c date and time created 84/02/13 15:31:34 by slatteng
e
u
U
t
T
I 1
D 2
/* Font translation to Imagen-style fonts (RST format) from character format.
E 2
I 2
D 5
/* %M%	%I%	%E%
E 5
I 5
/*	%M%	%I%	%E%
E 5
E 2
 *
I 2
 * Font translation to Imagen-style fonts (RST format) from character format.
 *
E 2
D 4
 *	Use:	ch2rst  [ -i ]  charfile  > rstfile
E 4
I 4
 *	Use:	ch2rst  [ -i  -s ]  charfile  > rstfile
E 4
 *
 *		Takes input from charfile (which must be in the format written
D 5
 *	by rst2ch), converts to rst format and writes to stdout.  If charfile
 *	is missing, stdin is read.  The -i flag tells ch2rst to ignore the
 *	character codes at the start of each glyph definition, and pack the
D 4
 *	glyphs in consecutive code positions starting with 0.
E 4
I 4
 *	glyphs in consecutive code positions starting with 0.  The -s flag
 *	forces ch2rst to NOT trim off any white space in the glyph map.  This
 *	is usefull to make stipples of fixed size.
E 5
I 5
 *	by one of the xxx2ch programs), converts to rst format and writes to
 *	stdout.  If charfile is missing, stdin is read.  The -i flag tells
 *	ch2rst to ignore the character codes at the start of each glyph
 *	definition, and pack the glyphs in consecutive code positions starting
 *	with 0.  The -s flag forces ch2rst to NOT trim off any white space in
 *	the glyph map.  This is usefull to make stipples of fixed size.
E 5
E 4
 */

#include <stdio.h>
D 5
#include <ctype.h>
E 5
#include "rst.h"


#define PREAMBLE	44			/* size of preamble */
#define STRINGS		2			/* length of strings at pre. */
#define STARTGLYPH	PREAMBLE + STRINGS
D 2
#define MAXLINE		200
E 2
I 2
D 7
#define MAXLINE		250
E 7
I 7
#define MAXLINE		300
E 7
#define GLYPHSPACE	(MAXLINE * MAXLINE)
E 2
#define wr1(x)		putchar(x)


D 5
char *	rdchar();
E 5
char *	malloc();

glyph_dir g[DIRSIZ];		/* directory of glyph definitions */
preamble p;			/* set of variables for preamble */
D 5
double widthtofix = 1.0 / FIXPIX;	/* fix conversion factor */
E 5
I 5
double widthtofix;		/* fix conversion factor */
I 8
double wordsptemp;		/* holds wordsp "fix" `til res. is known */
double linesptemp;		/* holds linesp "fix" `til res. is known */
E 8
E 5

D 5
int	code, codeindex;
E 5
I 5
D 7
int	code;
E 5
int	width, length, maxv, minv, maxh, minh, refv, refh;
E 7
I 7
int	code;			/* read in code for a glyph */
int	width, length;		/* width and length of read-in matrix */
int	maxv, minv, maxh, minh;	/* extent of "blackness" in glyph */
int	refv, refh;		/* reference point in matrix */
E 7
int	bitwidth;

D 7
int	ignorecode = 0;
I 4
int	stipple = 0;
E 7
I 7
int	ignorecode = 0;		/* flag: ignore the code number; successive */
int	stipple = 0;		/* flag: don't eliminate white-space */
E 7
E 4
FILE *	filep;
char	ibuff[MAXLINE];
char	ebuff[MAXLINE];
char *	glyphs[DIRSIZ];
D 2
char	charbits[20000];	/* place to store bits for a glyph */
E 2
I 2
char	charbits[GLYPHSPACE];	/* place to store bits for a glyph */
E 2


I 2
D 5

E 2
main(argc,argv)
E 5
I 5
main(argc, argv)
E 5
int argc;
char **argv;
{
    register int i;
    register int j;
D 5
    register int k;
E 5
I 5
    register int codeindex;
E 5
    register char *chp;
    register char *bitp;
    float par;

    while (argc > 1 && argv[1][0] == '-') {
	switch(argv[1][1]) {
	case 'i':
		ignorecode = 1;
		break;
I 4

	case 's':
		stipple = 1;
		break;
E 4
	default:
		error("%s, unknown option flag", argv[1]);
	}
	argc--; argv++;
    }

I 7
    if (argc > 2)
	error("too many arguments");
E 7
    if (argc == 2) {
	if ((filep = fopen (argv[1], "r")) == NULL)
	    error("can't open file \"%s\"", argv[1]);
    } else filep = stdin;

I 5
D 8
    widthtofix = (1.0 / FIXPIX);	/* default fix conversion factor */
E 8
E 5
    codeindex = 0;
    for (i = 0; i < DIRSIZ; glyphs[i++] = (char *) 0);

    fgets(ibuff, MAXLINE, filep);
D 3
    if (strcmp(ibuff, "header\n"))
E 3
I 3
    if (strcmp(ibuff, "fontheader\n"))
E 3
	error("not a character font file");

    while (fgets(ibuff, MAXLINE, filep) != NULL) {
	if (index(ibuff, '\n') == 0)
	    error("input line too long");

	if (ibuff[0] != ':') {
	    sscanf (ibuff, "%s %f", ebuff, &par);
	    if (strcmp(ebuff, "size") == 0) p.p_size = par + 0.5;
	    else if (strcmp(ebuff, "version") == 0) {
		if (p.p_version = par + 0.5)
		    error("wrong version (%d) for Font file.", p.p_version);
D 8
	    } else if (strcmp(ebuff, "mag") == 0) {
		p.p_mag = par + 0.5;
		if (p.p_mag) widthtofix = 1000.0 / (FIXPIX * p.p_mag);
	    } else if (strcmp(ebuff, "desiz") == 0) p.p_desiz = par / FIX + 0.5;
	    else if (strcmp(ebuff, "linesp") == 0)
		p.p_linesp = par * widthtofix + 0.5;
	    else if (strcmp(ebuff, "wordsp") == 0)
		p.p_wordsp = par * widthtofix + 0.5;
E 8
I 8
	    } else if (strcmp(ebuff, "mag") == 0) p.p_mag = par + 0.5;
	    else if (strcmp(ebuff, "desiz") == 0) p.p_desiz = par / FIX + 0.5;
	    else if (strcmp(ebuff, "linesp") == 0) linesptemp = par;
	    else if (strcmp(ebuff, "wordsp") == 0) wordsptemp = par;
E 8
	    else if (strcmp(ebuff, "rot") == 0) p.p_rot = par + 0.5;
	    else if (strcmp(ebuff, "cadv") == 0) p.p_cadv = par + 0.5;
	    else if (strcmp(ebuff, "ladv") == 0) p.p_ladv = par + 0.5;
	    else if (strcmp(ebuff, "id") == 0) p.p_id = par + 0.5;
D 8
	    else if (strcmp(ebuff, "res") == 0) {
		if ((p.p_res = par + 0.5) != RES)
D 5
		    error("wrong resolution in Font file.", p.p_res);
	    } else
		error("unknown input descriptor, \"%s\"", ebuff);
E 5
I 5
D 7
		    fprintf(stderr, "ch2rst: Warning, wrong resolution (%d).\n",
E 7
I 7
		    fprintf(stderr, "ch2rst: warning, wrong resolution (%d).\n",
E 7
				p.p_res);
	    } /* ignore unrecognized fields */
E 8
I 8
	    else if (strcmp(ebuff, "res") == 0) p.p_res = par + 0.5;
		/* ignore unrecognized fields */
E 8
E 5
	} else {
I 8
			/* set up for real resolution of font file */
	    if (p.p_mag)
		widthtofix = 1000.0 / (FIXIN * p.p_res * p.p_mag);
	    else
		widthtofix = (1.0 / (FIXIN * p.p_res));
	    p.p_wordsp = wordsptemp * widthtofix + 0.5;
	    p.p_linesp = linesptemp * widthtofix + 0.5;

E 8
	    if (sscanf (ibuff, ":%d, width = %f", &code, &par) != 2)
		error("bad glyph header, %s", ibuff);
D 5
	    if (ignorecode) i = codeindex++; else i = code;
	    g[i].g_pwidth = par * widthtofix + 0.5;
E 5
I 5
	    if (ignorecode) codeindex++; else codeindex = code;
	    g[codeindex].g_pwidth = par * widthtofix + 0.5;
E 5

	    chp = &charbits[0];
	    if (fgets(chp, MAXLINE, filep) == NULL)
		error("unexpected end of input");
	    width = strlen(chp) - 1;
	    minh = width;
	    maxh = 0;
D 2
	    minv = -1;
E 2
I 2
	    refv = minv = -1;
E 2

	    for (length = 0; *chp != '\n'; length++) {
I 2
		if ((length + 1) * width > GLYPHSPACE)
		    error ("out of glyph space");
E 2
D 5
		for (j = 0; j < width; j++, chp++) {
E 5
I 5
		for (i = 0; i < width; i++, chp++) {
E 5
		    switch (*chp) {
			case '.':
				break;
			case 'x':
I 7
				if (refv != -1)
				 error("two reference points in glyph %d",code);
E 7
D 5
				refh = j;
E 5
I 5
				refh = i;
E 5
				refv = length;
				*chp = '.';
				break;
			case 'X':
I 7
				if (refv != -1)
				 error("two reference points in glyph %d",code);
E 7
D 5
				refh = j;
E 5
I 5
				refh = i;
E 5
				refv = length;
			case '@':
D 2
			case 'a':
E 2
I 2
			case '*':
E 2
				maxv = length;
D 2
				if (minv == -1) minv = length;
E 2
I 2
				if (minv < 0) minv = length;
E 2
D 5
				if (j < minh) minh = j;
				if (j > maxh) maxh = j;
E 5
I 5
				if (i < minh) minh = i;
				if (i > maxh) maxh = i;
E 5
				break;
			default:
				error("illegal character '%c' in map.", *chp);
		    } /* switch */
D 5
		} /* for j */
E 5
I 5
		} /* for i */
I 7
		if (*chp != '\n')
		    error("not all lines equal length in glyph %d", code);
E 7
E 5
		if (fgets(chp, MAXLINE, filep) == NULL)
			error("unexpected end of input");
	    } /* for length */
I 4

	    if (stipple) {		/* use the whole box to make a */
		minv = 0;		/* stipple pattern. */
		minh = 0;
		maxv = length - 1;
		maxh = width - 1;
	    }
E 4
I 2

	    if (refv < 0) error("no reference point in glyph %d.", code);
	    if (minv < 0) {
		minv = maxv = refv;
		minh = maxh = refh;
	    }
E 2
D 5
	    g[i].g_height = maxv + 1 - minv;
	    g[i].g_width = maxh + 1 - minh;
	    g[i].g_up = refv - minv;
	    g[i].g_left = refh - minh;
	    g[i].g_bitp = g[i].g_height * ((g[i].g_width + 7) / 8);
E 5
I 5
	    g[codeindex].g_height = maxv + 1 - minv;
	    g[codeindex].g_width = maxh + 1 - minh;
	    g[codeindex].g_up = refv - minv;
	    g[codeindex].g_left = refh - minh;
	    g[codeindex].g_bitp =
		g[codeindex].g_height * ((g[codeindex].g_width + 7) / 8);
E 5

D 2
	    
E 2
I 2
D 5

E 2
	    bitp = (glyphs[i] = malloc(g[i].g_bitp)) - 1;
	    for (k = minv; k <= maxv; k++) {
		chp = &charbits[0] + width * k + minh;
E 5
I 5
	    bitp = (glyphs[codeindex] = malloc(g[codeindex].g_bitp)) - 1;
I 7
	    if (!glyphs[codeindex])
		error("out of memory");
E 7
	    for (i = minv; i <= maxv; i++) {
		chp = &charbits[0] + width * i + minh;
E 5
		bitwidth = 0;
		for (j = minh; j <= maxh; j++, chp++) {
		    if (--bitwidth < 0) {
			*++bitp = '\0';
			bitwidth = 7;
		    }
		    if (*chp != '.') *bitp |= 1 << bitwidth;
		}
D 5
	    } /* for */
E 5
I 5
	    } /* for i */
E 5
	} /* else */
    } /* while */

    if (ignorecode) {
D 5
	i = codeindex;
	p.p_last = i - 1;
E 5
I 5
	p.p_last = codeindex - 1;
E 5
	p.p_first = 0;
    } else {
	for (i = DIRSIZ - 1; glyphs[i] == (char *) 0; i--);
	p.p_last = i;
D 5
	for (j = 0; glyphs[j] == (char *) 0; j++);
	p.p_first = j;
E 5
I 5
	for (i = 0; glyphs[i] == (char *) 0; i++);
	p.p_first = i;
E 5
    }
    bitwidth = STARTGLYPH + 15 * (1 + p.p_last - p.p_first);

    printf("Rast UCB");
    wr2(p.p_size);	 wr1(p.p_version);	wr3(STARTGLYPH);
    wr2(p.p_first);	 wr2(p.p_last);		wr4(p.p_mag);
    wr4(p.p_desiz);	 wr4(p.p_linesp);	wr4(p.p_wordsp);
    wr2(p.p_rot);	 wr1(p.p_cadv);		wr1(p.p_ladv);
    wr4(p.p_id);	 wr2(p.p_res);
    for (i = 0; i < STRINGS; i++) putchar('\0');

    for (i = p.p_first; i <= p.p_last; i++) {
	if (glyphs[i] == (char *) 0) {
	    for (j = 0; j < 15; j++) putchar('\0');
	} else {
	    wr2(g[i].g_height);
	    wr2(g[i].g_width);
	    wr2(g[i].g_up);
	    wr2(g[i].g_left);
	    wr4(g[i].g_pwidth);
	    wr3(bitwidth);
	    bitwidth += g[i].g_bitp;
	}
D 5
    }
E 5
I 5
    } /* for i */
E 5
    fflush(stdout);

    for (i = p.p_first; i <= p.p_last; i++)
	if (glyphs[i] != (char *) 0)
	    vwrite(glyphs[i], g[i].g_bitp);
I 5
    exit(0);
E 5
}


D 5
vwrite(buf,usize)
E 5
I 5
/*----------------------------------------------------------------------------*
 | Routine:	vwrite (buffer, buffer_size)
 |
 | Results:	writes out character array "buffer" of size "buffer_size"
 |		to standard output in small enough chunks that a pipe could
 |		handle them.
 |
 | Bugs:	this routine shouldn't be needed
 *----------------------------------------------------------------------------*/

vwrite(buf, bufsize)
E 5
char *buf;
D 5
int usize;
E 5
I 5
int bufsize;
E 5
{
	int tsize = 0;

D 5
	while (usize) {
E 5
I 5
	while (bufsize) {
E 5
		buf += tsize;
D 5
		tsize = usize > BUFSIZ ? BUFSIZ : usize;
E 5
I 5
		tsize = bufsize > BUFSIZ ? BUFSIZ : bufsize;
E 5
		if ((tsize = write(1, buf, tsize)) < 0) {
			perror("ch2rst: write failed");
			exit(-1);
		}
D 5
		usize -= tsize;
E 5
I 5
		bufsize -= tsize;
E 5
	}
}


I 5
/*----------------------------------------------------------------------------*
 | Routine:	error (format_string, argument1, argument2.... )
 |
 | Results:	fprints a message to standard error, then exits with error
 |		code 1
 |
 | Side Efct:	This routine does NOT return
 *----------------------------------------------------------------------------*/

E 5
/*VARARGS1*/
error(string, a1, a2, a3, a4)
char *string;
{ 
	fprintf(stderr, "ch2rst: ");
	fprintf(stderr, string, a1, a2, a3, a4);
	fprintf(stderr, "\n");
D 5
	exit(8);
};
E 5
I 5
	exit(1);
}
E 5


I 5
/*----------------------------------------------------------------------------*
 | Routine:	wr2, wr3, wr4 (and wr1)
 |
 | Results:	writes out 2, 3, or 4 byte integers in RST byte order, using
 |		the wr1() routine, which writes one byte to standard output.
 *----------------------------------------------------------------------------*/

E 5
wr2(i)
unsigned int i;
{
D 5
    wr1((i>>8)&255);
    wr1(i&255);
E 5
I 5
    wr1((i >> 8) & 255);
    wr1(i & 255);
E 5
}

wr3(i)
unsigned int i;
{
D 5
    wr1((i>>16)&255);
    wr1((i>>8)&255);
    wr1(i&255);
E 5
I 5
    wr1((i >> 16) & 255);
    wr1(( i >> 8) & 255);
    wr1(i & 255);
E 5
}

wr4(i)
unsigned int i;
{
D 5
    wr1((i>>24)&255);
    wr1((i>>16)&255);
    wr1((i>>8)&255);
    wr1(i&255);
E 5
I 5
    wr1((i >> 24) & 255);
    wr1((i >> 16) & 255);
    wr1((i >> 8) & 255);
    wr1(i & 255);
E 5
}
E 1
