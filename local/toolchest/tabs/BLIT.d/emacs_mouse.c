/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 *
 * This is a mouse movement function for BTL EMACS written by
 * Warren Montgomery for use with Blit's running the etty terminal
 * program.  This function should be bound to ^Xg
 *
 */

/* Mousing Specials */

/* Goto screen position at line x, collumn y.  arg is decoded as:
 *	x = arg mod 128.
 *	y = arg /128.
			(128 is more lines than I can imagine on a screen.)
			
 * Will switch windows, but fails if x is an illegal position. */

go_xy(arg)
int arg;
{
	register int x,y,c;
	int linpos;

	x = arg&127;
	y = ((unsigned) arg) >>7;
	if ((x <wbase) || (x>= SCRLINES)) {
		if (twowind) {
			if ((x >= 0) && (x < wscrlines)) {
				owind();
			} else return(0); /* Can't mouse out of the display */
		} else return(0);
	}
	linpos = scrmap[x]&SCRMSK;
	if (linpos== 0) linpos = maxln;	/* If nothing there, punt to end of file */
	if (findline(linpos) == 0) return(0); /* PUNT */
	mline = nln;
	column = 0;
	mcol = LNOMOD*LNOWID;
	if (y<mcol) y = mcol;
	clptr=mkline(linpos);
	while ((mline < x) || (mcol <= y)) {
		c = clptr[column++];
		if (c == EOL) break;
		if (c & META) {
			mcol+=2;
			c-=META;
		}
		switch(ctype[c]) {

		case PLAIN:
		case UL:
			mcol++;
			break;
		case BACKSP:
			if (BACKP) {
				if (mcol) mcol--;
				break;
			}
		case CONTRL:
			mcol += 2;
			break;
		case TAB:
			if (NOTABS) mcol+= 2;
			else mcol = mcol+TABSTOP-((mcol-(LNOMOD*LNOWID))%TABSTOP);
			break;
		}
		if (mcol>SCRWID) {
			mline++;
			mcol = mcol-SCRWID;
			if (LNOMOD) mcol+= LNOWID;
		}
	}
	move(linpos,column-1);
	return(1);
}
