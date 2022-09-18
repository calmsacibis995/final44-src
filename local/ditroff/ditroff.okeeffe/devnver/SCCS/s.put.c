h39263
s 00023/00012/00151
d D 1.2 87/07/10 12:30:06 denise 3 1
c 
e
s 00022/00009/00154
d R 1.2 87/07/06 15:51:19 denise 2 1
c fixed loop in put1(); does not access font 0 anymore
e
s 00163/00000/00000
d D 1.1 87/07/06 14:14:59 denise 1 0
c date and time created 87/07/06 14:14:59 by denise
e
u
U
t
T
I 1
D 3
#ifndef lint
static char sccsid[] = "%W%	%E%";
#endif

E 3
/********************************************************************
 *
I 3
 * %W% (CWI) %E%
 *
E 3
 * code to put a character
 *
 *******************************************************************/

#include "the.h"

extern struct	dev dev;
extern struct	Font *fontbase[];
extern int	output;
extern short	*pstab;
extern int	nfonts, smnt, nchtab;
extern char	*chname, *fitab[];
extern char	*widthtab[], *codetab[];
extern short	*chtab, *fonttab[];
extern struct	fontname fontname[];
extern int	size, font, hpos, vpos, lastw, maxv;
extern int	virtRES;
extern char	buffer[];
extern int	vorigin, pagelen;
extern int	debug, dbg;




/* 
 * s is the name of a special character
 */

put1s(s)	
char *s;
{
	int i;

	if (!output)
		return;

	DBGPRINT(2, ("%s ", s));

	for (i = 0; i < nchtab; i++)
		if (strcmp(&chname[chtab[i]], s) == 0)
			break;

	if (i < nchtab)
		put1(i + 128);
}


/* 
 *  output char c
 */

put1(c)	
int c;
{
	char *pw;
	register char *p;
	register int i, k;
D 3
	int j, ofont, code;
E 3
I 3
	int ofont, code;
E 3
	short f;

	if (!output)
		return;

	c -= 32;
	if (c <= 0) {
		DBGPRINT(0, ("non-exist 0%o\n", c+32));
		lastw = (widthtab[font][0] * pstab[size] + dev.unitwidth/2)/dev.unitwidth;
		return;
	}
	k = ofont = font;
I 3

	/* try to find it on this font
	 */
E 3
	i = fitab[font][c] & BMASK;
D 3
	if (i != 0) {	/* it's on this font */
E 3
I 3
	if (i != 0) {	
E 3
		p = codetab[font];
		pw = widthtab[font];
D 3
	} else if (smnt > 0) {		/* on special (we hope) */
		for (k=smnt, j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1))
		/*
		 * Look for the character, start at the special font
		 * and search further in a wrap around manner 
		 */ 
E 3
I 3
	}
	/* well, check special font
	 */
	else if ((smnt > 0) && ((i = fitab[smnt][c] & BMASK) != 0)) {
		k = smnt;
		p = codetab[k];
		pw = widthtab[k];
		setfont(k);
	}
	/* now just see if we can find something on another font.
	 */
	else {
		for (k=1; k <= nfonts; k++) {
			if ( k == smnt ) continue;
E 3
			if ((i = fitab[k][c] & BMASK) != 0) {
				p = codetab[k];
				pw = widthtab[k];
				setfont(k);
				break;
			}
I 3
		}
E 3
	}
	if (i == 0 || (code = p[i] & BMASK) == 0 || k > nfonts) {
#ifdef DEBUGABLE
		if (dbg) {
			if (isprint(c+32) && isascii(c+32)) 
				fprintf(stderr,"not found %c\n", c+32);
			else
				fprintf(stderr,"not found \\(%s\n", &chname[chtab[c -128+32]]);
		}
#endif DEBUGABLE
I 3
		lastw = (widthtab[font][0] * pstab[size] + dev.unitwidth/2)/dev.unitwidth;
E 3
		return;
	}
	if (fontbase[k]->fonttab == 1){
		f = fonttab[k][i];
	}
	else {
		f = fontname[k].number;
	}
#ifdef DEBUGABLE
	if (dbg) {
		if (isprint(c+32) && isascii(c+32)) { /* My God! */
			fprintf(stderr,"%c %d %d\n", c+32, code, f);
		}
		else
			fprintf(stderr,"\\(%s %d %d\n", &chname[chtab[c -128+32]], code, f);
	}
#endif DEBUGABLE
	/*
	if(code == 0 || code > 0200) {
		error(FATAL,"Illegal code 0%o found for char %03o\n", code, c+32);
	}
	*/
	putcode(code, f);	/* character is < 254 */
	if (font != ofont)	/* char on special font, reset	*/
		setfont(ofont);
	lastw = pw[i] & NMASK;

	lastw = (lastw * pstab[size] + dev.unitwidth/2) / dev.unitwidth;
}





/*
 * Plot a dot at (x, y).  
 *
 * x and y are *VIRTUAL* coordinates (a change from prev. versions).
 *
 * The physical mapping of the point should be in the range 0 <= x < RASTER_LENGTH,
 * vorigin <= y < vorigin + NLINES.  If the point will not fit on the buffer,
 * it is left out.  Things outside the x boundary are wrapped around the end.
 */

point(x, y)
register int x;
register int y;
{
    register char *ptr;

    x = PHYS(x);
    y = PHYS(y);

    ptr = buf0p + (y - vorigin) * BYTES_PER_LINE + (x >> 3);

    if (ptr > BUFBOTTOM || ptr < BUFTOP)	/* ignore if it's off buffer */
	return;

    *ptr |= 1 << (7 - (x & 07));
    if (y > maxv) maxv = y;
}
E 1
