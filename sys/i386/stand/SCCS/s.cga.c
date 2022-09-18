h59508
s 00002/00002/00114
d D 8.1 93/06/11 15:57:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00115
d D 7.4 92/10/11 10:22:55 bostic 4 3
c make kernel includes standard
e
s 00078/00024/00038
d D 7.3 91/04/28 16:58:00 william 3 2
c and avoid clear of screen and change of attribute bytes...
e
s 00001/00001/00061
d D 7.2 91/04/28 16:55:57 william 2 1
c minimized so we can fit obese disklabel
e
s 00062/00000/00000
d D 7.1 90/04/24 19:56:29 william 1 0
c date and time created 90/04/24 19:56:29 by william
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 2
 * %sccs.include.noredist.c%
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 3
typedef unsigned short u_short;
typedef unsigned char u_char;
E 3
I 3
D 4
#include "param.h"
E 4
I 4
#include <sys/param.h>
E 4
E 3

D 3
#define	CRT_TXTADDR	((u_short *)0xb8000)
E 3
#define	COL		80
#define	ROW		25
#define	CHR		2
I 3
#define MONO_BASE	0x3B4
#define MONO_BUF	0xB0000
#define CGA_BASE	0x3D4
#define CGA_BUF		0xB8000
E 3

D 3
u_short	*crtat;
u_char	color = 0xe ;
int row;
E 3
I 3
static u_char	att = 0x7 ;
u_char *Crtat = (u_char *)CGA_BUF;
E 3

D 3
sput(c) u_char c; {
E 3
I 3
static unsigned int addr_6845 = CGA_BASE;
cursor(pos)
int pos;
{
	outb(addr_6845,14);
	outb(addr_6845+1,pos >> 8);
	outb(addr_6845,15);
	outb(addr_6845+1,pos&0xff);
}
E 3

I 3
sput(c)
u_char c;
{

	static u_char *crtat = 0;
	unsigned cursorat; u_short was;
	u_char *cp;

E 3
	if (crtat == 0) {
D 3
		crtat = CRT_TXTADDR; bzero (crtat,COL*ROW*CHR);
E 3
I 3

		/* XXX probe to find if a color or monochrome display */
		was = *(u_short *)Crtat;
		*(u_short *)Crtat = 0xA55A;
		if (*(u_short *)Crtat != 0xA55A) {
			Crtat = (u_char *) MONO_BUF;
			addr_6845 = MONO_BASE;
		}
		*(u_short *)Crtat = was;

		/* Extract cursor location */
		outb(addr_6845,14);
		cursorat = inb(addr_6845+1)<<8 ;
		outb(addr_6845,15);
		cursorat |= inb(addr_6845+1);

		if(cursorat <= COL*ROW) {
			crtat = Crtat + cursorat*CHR;
			att = crtat[1];	/* use current attribute present */
		} else	crtat = Crtat;

		/* clean display */
		for (cp = crtat; cp < Crtat+ROW*COL*CHR; cp += 2) {
			cp[0] = ' ';
			cp[1] = att;
		}
E 3
	}
D 3
	if (crtat >= (CRT_TXTADDR+COL*ROW*CHR)) {
		crtat = CRT_TXTADDR+COL*(ROW-1); row = 0;
	}
	switch(c) {
E 3

I 3
	switch (c) {

E 3
	case '\t':
D 3
		do {
			*crtat++ = (color<<8)| ' '; row++ ;
		} while (row %8);
E 3
I 3
		do
			sput(' ');
		while ((int)crtat % (8*CHR));
E 3
		break;

	case '\010':
D 3
		crtat--; row--;
E 3
I 3
		crtat -= CHR;
E 3
		break;

	case '\r':
D 3
		bzero (crtat,(COL-row)*CHR) ; crtat -= row ; row = 0;
E 3
I 3
		crtat -= (crtat - Crtat) % (COL*CHR);
E 3
		break;

	case '\n':
D 3
		if (crtat >= CRT_TXTADDR+COL*(ROW-1)) { /* scroll */
			bcopy(CRT_TXTADDR+COL, CRT_TXTADDR,COL*(ROW-1)*CHR);
			bzero (CRT_TXTADDR+COL*(ROW-1),COL*CHR) ;
			crtat -= COL ;
		}
		crtat += COL ;
E 3
I 3
		crtat += COL*CHR ;
E 3
		break;

	default:
D 3
		*crtat++ = (color<<8)| c; row++ ;
E 3
I 3
		crtat[0] = c;
		crtat[1] = att;
		crtat += CHR;
E 3
		break ;
	}
I 3

#ifndef SMALL
	/* implement a scroll */
	if (crtat >= Crtat+COL*ROW*CHR) {
		/* move text up */
		bcopy(Crtat+COL*CHR, Crtat, COL*(ROW-1)*CHR);

		/* clear line */
		for (cp = Crtat+ COL*(ROW-1)*CHR;
			cp < Crtat + COL*ROW*CHR ; cp += 2)
			cp[0] = ' ';

		crtat -= COL*CHR ;
	}
#endif

	cursor((crtat-Crtat)/CHR);
E 3
}
E 1
