h00402
s 00011/00000/00265
d D 1.6 85/07/03 13:42:29 slatteng 6 5
c put in "sun" options to produce sun vfont files
e
s 00074/00058/00191
d D 1.5 85/01/31 19:34:21 slatteng 5 4
c cleanup... added comments, etc.
e
s 00017/00002/00232
d D 1.4 84/04/07 15:53:38 slatteng 4 3
c added -s option.
e
s 00001/00001/00233
d D 1.3 84/02/27 18:23:06 slatteng 3 2
c change "header" to "fontheader"
e
s 00016/00006/00218
d D 1.2 84/02/16 15:10:57 slatteng 2 1
c add a bit of error checking if no bits are on in a glyph, or overflow.
e
s 00224/00000/00000
d D 1.1 84/02/13 15:31:29 slatteng 1 0
c date and time created 84/02/13 15:31:29 by slatteng
e
u
U
t
T
I 1
D 2
/* Font translation to vfonts (RST format) from character format.
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
D 5
 * Font translation to vfonts (RST format) from character format.
E 5
I 5
 * Font translation to vfont format from character format.
E 5
 *
E 2
D 4
 *	Use:	ch2vft  [ -i ]  charfile  > vfontfile
E 4
I 4
 *	Use:	ch2vft  [ -i  -s ]  charfile  > vfontfile
E 4
 *
 *		Takes input from charfile (which must be in the format written
D 5
 *	by xxx2ch), converts to rst format and writes to stdout.  If charfile
 *	is missing, stdin is read.  The -i flag tells ch2rst to ignore the
 *	character codes at the start of each glyph definition, and pack the
D 4
 *	glyphs in consecutive code positions starting with 0.
E 4
I 4
 *	glyphs in consecutive code positions starting with 0.  The -s flag
 *	forces ch2vft to include the whole bit-map that defines the glyph.
 *	Normally, it is trimmed of white space.  This is usefull for making
 *	stipple patterns of fixed size.
E 5
I 5
 *	by one of the xxx2ch programs), converts to vfont format and writes it
 *	to stdout.  If charfile is missing, stdin is read.  The -i flag tells
 *	ch2vft to ignore the character codes at the start of each glyph
 *	definition, and pack the glyphs in consecutive code positions starting
 *	with 0.  The -s flag forces ch2vft to include the whole bit-map that
 *	defines the glyph.  Normally, it is trimmed of white space.  This is
 *	usefull for making stipple patterns of fixed size.
E 5
E 4
 */

#include <stdio.h>
D 5
#include <ctype.h>
E 5
#include <vfont.h>


I 6
#ifdef sun
#define RES		120	/* for SUN vfont, resolution is 120 */
#else
E 6
#define RES		200	/* for vfont, resolution is 200 */
I 6
#endif
E 6
#define MAXLINE		200
I 2
#define GLYPHSPACE	(MAXLINE * MAXLINE)
E 2
#define MAGICNO		0436
#define DIRSIZ		256	/* vfonts MUST have 256 entries */
#define DIMLIMIT	128


D 5
char *	rdchar();
E 5
char *	malloc();

struct dispatch g[DIRSIZ];	/* directory of glyph definitions */
struct header	head;		/* font file header */

D 5
int	code, codeindex;
E 5
I 5
int	code;
E 5
int	width, length, maxv, minv, maxh, minh, refv, refh;
int	fileaddr;

int	ignorecode = 0;
I 4
int	stipple = 0;
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


main(argc,argv)
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

I 5

E 5
    head.magic = MAGICNO;
    head.maxx = head.maxy = head.xtend = 0;
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

    if (argc == 2) {
	if ((filep = fopen (argv[1], "r")) == NULL)
	    error("can't open file \"%s\"", argv[1]);
    } else filep = stdin;

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
D 5
	    if (strcmp(ebuff, "size") == 0);
	    else if (strcmp(ebuff, "version") == 0) {
		if ((int) (par + 0.5))
		    error("wrong version (%d) for Font file.", (int)(par+0.5));
	    } else if (strcmp(ebuff, "mag") == 0);
	    else if (strcmp(ebuff, "desiz") == 0);  /*des_size = par/FIX + 0.5*/
	    else if (strcmp(ebuff, "linesp") == 0);
	    else if (strcmp(ebuff, "wordsp") == 0);
	    else if (strcmp(ebuff, "rot") == 0);
	    else if (strcmp(ebuff, "cadv") == 0);
	    else if (strcmp(ebuff, "ladv") == 0);
	    else if (strcmp(ebuff, "id") == 0);
	    else if (strcmp(ebuff, "res") == 0) {
E 5
I 5
	    if (strcmp(ebuff, "res") == 0) {
E 5
		if (((int) (par + 0.5)) != RES)
		    fprintf(stderr, "ch2vft warning: wrong resolution (%d).\n",
			(int) (par + 0.5) );
D 5
	    } else
		error("unknown input descriptor, \"%s\"", ebuff);
E 5
I 5
	    }
E 5
	} else {
	    if (sscanf (ibuff, ":%d, width = %f", &code, &par) != 2)
		error("bad glyph header, %s", ibuff);
D 5
	    if (ignorecode) i = codeindex++; else i = code;
	    if (i < 0 || i >= DIRSIZ) error("code (%d) out of range", i);
	    g[i].width = par + 0.5;
E 5
I 5
	    if (ignorecode) codeindex++; else codeindex = code;
	    if (codeindex < 0 || codeindex >= DIRSIZ)
		error("code (%d) out of range", codeindex);
	    g[codeindex].width = par + 0.5;
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
			case '*':
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
E 5
		if (fgets(chp, MAXLINE, filep) == NULL)
			error("unexpected end of input");
	    } /* for length */
I 4

	    if (stipple) {		/* force whole box if making stipples */
		minv = 0;
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
	    g[i].up = bound(refv - minv);
	    g[i].down = bound(maxv + 1 - refv);
	    g[i].right = bound(maxh + 1 - refh);
	    g[i].left = bound(refh - minh);
	    g[i].nbytes = (maxv + 1 - minv) * ((maxh + 8 - minh) >> 3);
E 5
I 5
	    g[codeindex].up = bound(refv - minv);
	    g[codeindex].down = bound(maxv + 1 - refv);
	    g[codeindex].right = bound(maxh + 1 - refh);
	    g[codeindex].left = bound(refh - minh);
I 6
#ifdef sun
	    g[codeindex].nbytes = (maxv+1-minv) * ((maxh+16-minh) / 16) * 2;
#else
E 6
	    g[codeindex].nbytes = (maxv + 1 - minv) * ((maxh + 8 - minh) >> 3);
I 6
#endif
E 6
E 5

				/* convert from characters to bits */
D 5
	    bitp = (glyphs[i] = malloc(g[i].nbytes)) - 1;
	    for (k = minv; k <= maxv; k++) {
E 5
I 5
	    bitp = (glyphs[codeindex] = malloc(g[codeindex].nbytes)) - 1;
	    for (i = minv; i <= maxv; i++) {
E 5
		register int bitwidth;

D 5
		chp = &charbits[0] + width * k + minh;
E 5
I 5
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
I 6
#ifdef sun
		if (!((bitp - glyphs[codeindex]) & 1)) *++bitp = '\0';
#endif
E 6
D 5
	    } /* for */
E 5
I 5
	    } /* for i */
E 5
	} /* else */
    } /* while */

    fileaddr = 0;
    for (i = 0; i < DIRSIZ; i++) {
	if (glyphs[i] == (char *) 0) {
	    g[i].nbytes = 0;
	} else {
	    g[i].addr = fileaddr;
	    fileaddr += g[i].nbytes;
	    if (g[i].up > head.maxy) head.maxy = g[i].up;
	    if (g[i].down > head.xtend) head.xtend = g[i].down;
	    if (((int) g[i].left + g[i].right) > head.maxx)
		head.maxx = g[i].left + (int) g[i].right;
	}
    }
    head.size = fileaddr;

    vwrite((char *) &head, sizeof(head));
    vwrite((char *) &(g[0]), sizeof(g));
    for (i = 0; i < DIRSIZ; i++)
	if (glyphs[i] != (char *) 0)
	    vwrite(glyphs[i], g[i].nbytes);
I 5
    exit(0);
E 5
}


D 5
vwrite(buf,usize)
E 5
I 5
/*----------------------------------------------------------------------------*
 | Routine:	bound (value)
 |
 | Results:	checks to make sure that the dimensions of a glyph fit into
 |		the vfont format's limitations.  The up, down, right, and left
 |		fields must fit into a byte!), but can be signed.
 *----------------------------------------------------------------------------*/

bound(i)
{
	if(i < DIMLIMIT && i >= -DIMLIMIT) return i;
	error ("dimension out of range");
}


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
D 2
			perror("ch2rst: write failed");
E 2
I 2
			perror("ch2vft: write failed");
E 2
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
	fprintf(stderr, "ch2vft: ");
	fprintf(stderr, string, a1, a2, a3, a4);
	fprintf(stderr, "\n");
D 5
	exit(8);
};

bound(i)
{
	if(i < DIMLIMIT && i >= -DIMLIMIT) return i;
	error ("dimension out of range");
E 5
I 5
	exit(1);
E 5
}
E 1
