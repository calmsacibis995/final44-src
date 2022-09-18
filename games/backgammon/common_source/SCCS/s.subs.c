h00373
s 00002/00002/00449
d D 8.1 93/05/31 16:10:17 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00450
d D 5.5 90/06/01 12:59:23 bostic 8 7
c new copyright notice
e
s 00010/00005/00451
d D 5.4 88/06/18 19:47:21 bostic 7 6
c install approved copyright notice
e
s 00009/00003/00447
d D 5.3 88/02/16 11:16:37 bostic 6 5
c authored by Alan Char; add Berkeley specific header
e
s 00002/00000/00448
d D 5.2 87/04/09 15:42:54 bostic 5 4
c bug report 4.2BSD/games/5
e
s 00009/00001/00439
d D 5.1 85/05/29 11:37:35 dist 4 3
c Add copyright
e
s 00026/00033/00414
d D 4.2 82/11/27 12:33:01 mckusick 3 2
c make game saving and restoring rational
e
s 00000/00000/00447
d D 4.1 82/05/11 15:02:36 rrh 2 1
c bringing to release 4.1
e
s 00447/00000/00000
d D 1.1 82/05/11 14:54:09 rrh 1 0
c date and time created 82/05/11 14:54:09 by rrh
e
u
U
t
T
I 1
D 4
static char sccsid[] = "	%M%	%I%	%E%	";
E 4
I 4
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 4

#include <stdio.h>
#include "back.h"

int	buffnum;
char	outbuff[BUFSIZ];

static char	plred[] = "Player is red, computer is white.";
static char	plwhite[] = "Player is white, computer is red.";
static char	nocomp[] = "(No computer play.)";

char  *descr[] = {
	"Usage:  backgammon [-] [n r w b pr pw pb t3a]\n",
	"\t-\tgets this list\n\tn\tdon't ask for rules or instructions",
	"\tr\tplayer is red (implies n)\n\tw\tplayer is white (implies n)",
	"\tb\ttwo players, red and white (implies n)",
	"\tpr\tprint the board before red's turn",
	"\tpw\tprint the board before white's turn",
	"\tpb\tprint the board before both player's turn",
	"\tterm\tterminal is a term",
	"\tsfile\trecover saved game from file",
	0
};

errexit (s)
register char	*s;
{
	write (2,"\n",1);
	perror (s);
	getout();
}

strset (s1,s2)
register char	*s1, *s2;
{
	while ( (*s1++ = *s2++) != '\0');
}

addbuf (c)
register char	c;

{
	buffnum++;
	if (buffnum == BUFSIZ)  {
		if (write(1,outbuff,BUFSIZ) != BUFSIZ)
			errexit ("addbuf (write):");
		buffnum = 0;
	}
	outbuff[buffnum] = c;
}

buflush ()  {
	if (buffnum < 0)
		return;
	buffnum++;
	if (write (1,outbuff,buffnum) != buffnum)
		errexit ("buflush (write):");
	buffnum = -1;
}

readc () {
	char	c;

	if (tflag)  {
		cline();
		newpos();
	}
	buflush();
	if (read(0,&c,1) != 1)
		errexit ("readc");
I 5
#ifdef WHY_IS_THIS_HARDWIRED_IN_HERE
E 5
	if (c == '\177')
		getout();
I 5
#endif
E 5
	if (c == '\033' || c == '\015')
		return ('\n');
	if (cflag)
		return (c);
	if (c == '\014')
		return ('R');
	if (c >= 'a' && c <= 'z')
		return (c & 0137);
	return (c);
}

writec (c)
char	c;
{
	if (tflag)
		fancyc (c);
	else
		addbuf (c);
}

writel (l)
register char	*l;
{
#ifdef DEBUG
	register char	*s;

	if (trace == NULL)
		trace = fopen ("bgtrace","w");
	
	fprintf (trace,"writel: \"");
	for (s = l; *s; s++) {
		if (*s < ' ' || *s == '\177')
			fprintf (trace,"^%c",(*s)^0100);
		else
			putc (*s,trace);
	}
	fprintf (trace,"\"\n");
	fflush (trace);
#endif

	while (*l)
		writec (*l++);
}

proll ()   {
	if (d0)
		swap;
	if (cturn == 1)
		writel ("Red's roll:  ");
	else
		writel ("White's roll:  ");
	writec (D0+'0');
	writec ('\040');
	writec (D1+'0');
	if (tflag)
		cline();
}

wrint (n)
int	n;
{
	register int	i, j, t;

	for (i = 4; i > 0; i--)  {
		t = 1;
		for (j = 0; j<i; j++)
			t *= 10;
		if (n > t-1)
			writec ((n/t)%10+'0');
	}
	writec (n%10+'0');
}

gwrite()  {
	register int	r, c;

	if (tflag)  {
		r = curr;
		c = curc;
		curmove (16,0);
	}

	if (gvalue > 1)  {
		writel ("Game value:  ");
		wrint (gvalue);
		writel (".  ");
		if (dlast == -1)
			writel (color[0]);
		else
			writel (color[1]);
		writel (" doubled last.");
	} else  {
		switch (pnum)  {
		case -1:			    /* player is red */
			writel (plred);
			break;
		case 0:				    /* player is both colors */
			writel (nocomp);
			break;
		case 1:				    /* player is white */
			writel (plwhite);
		}
	}

	if (rscore || wscore)  {
		writel ("  ");
		wrscore();
	}

	if (tflag)  {
		cline();
		curmove (r,c);
	}
}

quit ()  {
	register int	i;

	if (tflag)  {
		curmove (20,0);
		clend();
	} else
		writec ('\n');
	writel ("Are you sure you want to quit?");
	if (yorn (0))  {
		if (rfl)  {
			writel ("Would you like to save this game?");
			if (yorn(0))
				save(0);
		}
		cturn = 0;
		return (1);
	}
	return (0);
}

yorn (special)
register char	special;			/* special response */
{
	register char	c;
	register int	i;

	i = 1;
	while ( (c = readc()) != 'Y' && c != 'N')  {
		if (special && c == special)
			return (2);
		if (i)  {
			if (special)  {
				writel ("  (Y, N, or ");
				writec (special);
				writec (')');
			} else
				writel ("  (Y or N)");
			i = 0;
		} else
			writec ('\007');
	}
	if (c == 'Y')
		writel ("  Yes.\n");
	else
		writel ("  No.\n");
	if (tflag)
		buflush();
	return (c == 'Y');
}

wrhit (i)
register int	i;
{
	writel ("Blot hit on ");
	wrint (i);
	writec ('.');
	writec ('\n');
}

nexturn ()  {
	register int	c;

	cturn = -cturn;
	c = cturn/abs(cturn);
	home = bar;
	bar = 25-bar;
	offptr += c;
	offopp -= c;
	inptr += c;
	inopp -= c;
	Colorptr += c;
	colorptr += c;
}

getarg (arg)
register char	***arg;

{
D 3
	register char	*s;
E 3
I 3
	register char	**s;
E 3

	/* process arguments here.  dashes are ignored, nbrw are ignored
	   if the game is being recovered */

D 3
	s = **arg;
	if (*s == '-' && s[1] == '\0')  {
		tflag = 0;
		text (descr);
		getout ();
	}
	for (; *s != '\0'; s++)  {
		switch (*s)  {
E 3
I 3
	s = *arg;
	while (s[0][0] == '-') {
		switch (s[0][1])  {
E 3

D 3
		/* ignore dashes */
		case '-':
			break;

E 3
		/* don't ask if rules or instructions needed */
		case 'n':
			if (rflag)
				break;
			aflag = 0;
D 3
			args[acnt++] = *s;
E 3
I 3
			args[acnt++] = 'n';
E 3
			break;

		/* player is both read and white */
		case 'b':
			if (rflag)
				break;
			pnum = 0;
			aflag = 0;
D 3
			args[acnt++] = *s;
E 3
I 3
			args[acnt++] = 'b';
E 3
			break;

		/* player is red */
		case 'r':
			if (rflag)
				break;
			pnum = -1;
			aflag = 0;
D 3
			args[acnt++] = *s;
E 3
I 3
			args[acnt++] = 'r';
E 3
			break;

		/* player is white */
		case 'w':
			if (rflag)
				break;
			pnum = 1;
			aflag = 0;
D 3
			args[acnt++] = *s;
E 3
I 3
			args[acnt++] = 'w';
E 3
			break;

		/* print board after move according to following character */
		case 'p':
D 3
			s++;
			if (*s != 'r' && *s != 'w' && *s != 'b')
E 3
I 3
			if (s[0][2] != 'r' && s[0][2] != 'w' && s[0][2] != 'b')
E 3
				break;
			args[acnt++] = 'p';
D 3
			args[acnt++] = *s;
			if (*s == 'r')
E 3
I 3
			args[acnt++] = s[0][2];
			if (s[0][2] == 'r')
E 3
				bflag = 1;
D 3
			if (*s == 'w')
E 3
I 3
			if (s[0][2] == 'w')
E 3
				bflag = -1;
D 3
			if (*s == 'b')
E 3
I 3
			if (s[0][2] == 'b')
E 3
				bflag = 0;
			break;

		case 't':
D 3
			if (*++s == '\0')	/* get terminal caps */
				tflag = getcaps (*(++*arg));
			else
				tflag = getcaps (s);
			return;
E 3
I 3
			if (s[0][2] == '\0') {	/* get terminal caps */
				s++;
				tflag = getcaps (*s);
			} else
				tflag = getcaps (&s[0][2]);
			break;
E 3

		case 's':
D 3
			if (*++s == '\0')	/* recover file */
				recover (*(++*arg));
			else
				recover (s);
			return;
E 3
I 3
			s++;
			/* recover file */
			recover (s[0]);
			break;
E 3
		}
I 3
		s++;
E 3
	}
I 3
	if (s[0] != 0)
		recover(s[0]);
E 3
}

init ()  {
	register int	i;
	for (i = 0; i < 26;)
		board[i++] = 0;
	board[1] = 2;
	board[6] = board[13] = -5;
	board[8] = -3;
	board[12] = board[19] = 5;
	board[17] = 3;
	board[24] = -2;
	off[0] = off[1] = -15;
	in[0] = in[1] = 5;
	gvalue = 1;
	dlast = 0;
}

wrscore ()  {
	writel ("Score:  ");
	writel (color[1]);
	writec (' ');
	wrint (rscore);
	writel (", ");
	writel (color[0]);
	writec (' ');
	wrint (wscore);
}

fixtty (mode)
int	mode;
{
	if (tflag)
		newpos();
	buflush();
	tty.sg_flags = mode;
	if (stty (0,&tty) < 0)
		errexit("fixtty");
}

getout ()  {
	/* go to bottom of screen */
	if (tflag)  {
		curmove (23,0);
		cline();
	} else
		writec ('\n');

	/* fix terminal status */
	fixtty (old);
	exit();
}
roll ()  {
	register char	c;
	register int	row;
	register int	col;

	if (iroll)  {
		if (tflag)  {
			row = curr;
			col = curc;
			curmove (17,0);
		} else
			writec ('\n');
		writel ("ROLL: ");
		c = readc();
		if (c != '\n')  {
			while (c < '1' || c > '6')
				c = readc();
			D0 = c-'0';
			writec (' ');
			writec (c);
			c = readc();
			while (c < '1' || c > '6')
				c = readc();
			D1 = c-'0';
			writec (' ');
			writec (c);
			if (tflag)  {
				curmove (17,0);
				cline();
				curmove (row,col);
			} else
				writec ('\n');
			return;
		}
		if (tflag)  {
			curmove (17,0);
			cline();
			curmove (row,col);
		} else
			writec ('\n');
	}
	D0 = rnum(6)+1;
	D1 = rnum(6)+1;
	d0 = 0;
}
E 1
