/********************************************************************
 *
 * Device driving
 *
 *******************************************************************/

#include <sys/vcmd.h>
#include "the.h"
#include <math.h>


public int	output = 0;		/* do we do output at all?	*/
public int	nolist = 0;		/* output page list is > 0	*/
public int	olist[20];		/* pairs of page numbers	*/

public int	virtRES = RES;		/* resolution of input		*/

public int	hpos;		/* next hor. pos. in virtRES units; left = 0	*/
public int	vpos;		/* current vert pos. in virtRES units; top = 0	*/
public int	lastw;		/* width of last char printed, in virtRES un.	*/
public int	maxv;		/* how far down page we've been in RES units	*/

public char	buffer[BUFFER_SIZE];	/* versatec-wide NLINES buffer		*/
public int	vorigin = 0;		/* where on page startbuf maps to	*/
public int	pagelen = 0;		/* how lone current page has printed	*/

public int	pltmode[] = { VPLOT };
public int	prtmode[] = { VPRINT };

public int 	slant;		/* current general slanting factor (of slant cmd) */
public double	slantoffset;	/* slant-offset per pixel 			*/


/* from graph.c		*/
extern int	linethickness;

/* from font.c		*/
extern short	*pstab;
extern int	nsizes, nfonts, size, font;
extern struct	fontname fontname[];
extern struct	Font *fontbase[];

/* from main.c		*/
extern int	debug, dbg;



t_init()	/* initialize device */
{
	vorigin = pagelen = maxv = hpos = vpos = 0;

	output = 0;		/* don't output anything yet */
	setsize(t_size(10));	/* start somewhere */
	setfont(1);
	vclear(buf0p, BUFFER_SIZE);
}


struct state {
	int	ssize;
	int	sfont;
	int	shpos;
	int	svpos;
	int	sthick;
};

struct	state	state[MAXSTATE];
struct	state	*statep = state;


t_push()	/* begin a new block */
{
	statep->ssize = size;
	statep->sfont = font;
	statep->sthick = linethickness;
	statep->shpos = hpos;
	statep->svpos = vpos;
	if (statep++ >= state+MAXSTATE)
		error(FATAL, "{ nested too deep");
}

t_pop()	/* pop to previous state */
{
	if (--statep < state)
		error(FATAL, "extra }");
	size = statep->ssize;
	font = statep->sfont;
	hpos = statep->shpos;
	linethickness = statep->sthick;
	vpos = statep->svpos;
}


t_page(n)	/* do whatever new page functions */
{
	int i;


	if (output) outband(PAGEEND);

	maxv = vpos = 0;

	output = 1;
	if (nolist == 0)
		return;		/* no -o specified */
	output = 0;
	for (i = 0; i < nolist; i += 2)
		if (n >= olist[i] && n <= olist[i+1]) {
			output = 1;
			break;
		}
}


outband(page)
int page;
{
    register int outsize;

    if (page == PAGEEND) {		/* set outsize to inch boundary */

	DBGPRINT(0,("outband (PAGEEND) vpos %d maxv %d\n", vpos, maxv));

	if(maxv < PHYS(vpos))		/* be sure about the end of the */
		maxv = PHYS(vpos);	/* page (JNA) */

	outsize = (maxv + (RES - 2) - pagelen) / RES;
	vorigin = pagelen = 0;		/* reset for new page */
	if (outsize < 1) return;	/* if outsize <= zero, forget it */

	outsize *= RES * BYTES_PER_LINE;

	DBGPRINT(2,("outband outsize %d\n", outsize));

	vwrite(buf0p, outsize > BUFFER_SIZE ? BUFFER_SIZE : outsize);

	/* now fill rest of page with empty space.. */
	vclear(buf0p, BUFFER_SIZE);
	while ((outsize -= BUFFER_SIZE) > 0)
	    vwrite(buf0p, outsize > BUFFER_SIZE ? BUFFER_SIZE : outsize);

    } 
    else 				/* outband OVERBAND		*/
    {
	DBGPRINT(0,("outband vpos %d\n", vpos));

	vorigin += NLINES;
	pagelen += NLINES;
	vwrite(buf0p, BUFFER_SIZE);
	vclear(buf0p, BUFFER_SIZE);
    }
}


t_newline()	/* do whatever for the end of a line */
{
	hpos = 0;	/* because we're now back at the left margin */
}

t_size(n)	/* convert integer to internal size number*/
int n;
{
	int i;

	if (n <= pstab[0])
		return(0);
	else if (n >= pstab[nsizes - 1])
		return(nsizes - 1);
	for (i = 0; n > pstab[i]; i++)
		;
	return(i);
}

/*ARGSUSED*/
t_charht(n)	/* set character height to n */
int n;
{
#ifdef DEBUGABLE
	if (dbg) error(!FATAL, "can't set height on versatec");
#endif
}


t_font(s)	/* convert string to internal font number */
char *s;
{
	int n;

	n = atoi(s);
	if (n < 0 || n > nfonts)
		n = 1;
	return(n);
}

t_text(s)	/* print string s as text */
char *s;
{
	int c;
	char str[100];

	if (!output)
		return;
	while (c = *s++) {
		if (c == '\\') {
			switch (c = *s++) {
			case '\\':
			case 'e':
				put1('\\');
				break;
			case '(':
				str[0] = *s++;
				str[1] = *s++;
				str[2] = '\0';
				put1s(str);
				break;
			}
		} else {
			put1(c);
		}
		hmot(lastw);
		DBGPRINT(0,("width = %d\n", lastw));
	}
}


t_reset(c)
{	
	switch(c){
	case 's':
		t_page(0);
#ifdef DRIVER
		ioctl(OUTFILE, VSETSTATE, prtmode);
#endif
		break;
	}
}




vgoto(n)
{
	vpos = n;
}



setsize(n)	/* set point size to n (internal) */
int n;
{
	size = n;
}


/*ARGSUSED*/
t_fp(n, s, si)	/* font position n now contains font s, intname si */
int n;		/* internal name is ignored */
char *s, *si;
{
	fontname[n].name = s;
	fontname[n].number = atoi(si);
}


setfont(n)	/* set font to n (internal) */
int n;
{
	if (!output)
		return;
	if (n < 0 || n > NFONTS)
		error(FATAL, "illegal font %d\n", n);
	font = n;
	DBGPRINT(0,("Font set to %d\n", n));
	slantfont( fontbase[n]->slant & BMASK );
}



/*
 * slant is the real current slant, and sloffset is used by putcode
 *  to accomplish it.
 * fslant is the default slant of the current font.
 * uslant is the requested slant.
 * uslant overrides fslant, and fslant can be restored by asking
 * for slant 0.
 *
 * fslant will be manupulated by setfont (slanting can be an attribute
 * to a (Harris-)font.
 *
 * There are to many slants in this comment
 */

#define PI	3.14159265

private int	fslant;		/* slanting factor of current font 		*/
private int	uslant;		/* slant set by t_slant				*/
private int	sltab[]	= { 0, 9, 12, 15, -1 };	   /* possible slanting factors */


t_slant(n)	/* do slant cmd */
int n;
{	
	uslant = n;
	setslant(n);
}


setslant(n)	/* set slant to n */
int n;
{	int j;
	static int aslant;	/* the actual slanting factor */

	if( n == aslant )
		return;
	if( n == 0 && fslant ) {	/* back to slant of font */
		setslant( fslant );
		return;
	}
	for (j = 0; n > (aslant = sltab[j]); j++)
		if ( aslant == -1 ) {
			aslant = sltab[--j];
			break;
		}
	DBGPRINT(0,("slant to %d\n", aslant));

	slant = aslant;
	slantoffset = sin((aslant * PI)/180.0);	
}


slantfont(n)	/* set fontslant */
int n;
{
	fslant = n;
	if(!uslant) 	/* uslant overrides fslant */
		setslant( fslant );	
}




#define MAXWRIT 4096			/*Maximum to write at once		*/


vwrite(buf,usize)
char *buf;
int usize;
{
	register int tsize = 0;

	while (usize) {
		buf += tsize;
		tsize = (usize > MAXWRIT ? MAXWRIT : usize);

		if ((tsize = write(OUTFILE, buf, tsize)) < 0) {
			perror("dver: write failed");
			exit(RESTART);
		}
		usize -= tsize;
	}
}



vclear (ptr, nbytes)
char	*ptr;
int nbytes;
{
    register tsize = 0;

    while (nbytes){
	if ((unsigned)(16*1024) < nbytes) {
	    tsize = 16 * 1024;
	} else
	    tsize = nbytes;
	nbytes -= tsize;

	clear(ptr,tsize);
	ptr += tsize;
    }
}



/*ARGSUSED*/
clear(lp, nbytes)
char *lp;
int nbytes;
{
	asm("movc5 $0,(sp),$0,8(ap),*4(ap)");
}



