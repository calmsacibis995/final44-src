h22419
s 00046/00046/00084
d D 7.5 90/05/03 17:47:32 sklower 5 4
c first crack at torek changes, may need bug fixes
e
s 00004/00004/00126
d D 7.4 89/09/06 14:29:11 marc 4 3
c ANSI C, CTRL macro
e
s 00009/00004/00121
d D 7.3 86/12/15 20:26:48 sam 3 2
c lint
e
s 00001/00001/00124
d D 7.2 86/11/20 14:44:11 sam 2 1
c no more TRUE|FALSE
e
s 00125/00000/00000
d D 7.1 86/11/20 12:22:04 sam 1 0
c date and time created 86/11/20 12:22:04 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 3

#include "../kdb/defs.h"

char	line[LINSIZ];
D 5
char	*lp;
char	peekc,lastc = EOR;
E 5
I 5
char	*kdblp;
char	kdbpeekc,kdblastc = EOR;
E 5
D 3
int	eof;
E 3

/* input routines */

D 5
eol(c)
E 5
I 5
kdbeol(c)
E 5
	char c;
{
	return (c==EOR || c==';');
}

D 5
rdc()
E 5
I 5
kdbrdc()
E 5
{
	do
D 3
		readchar();
E 3
I 3
D 5
		(void) readchar();
E 3
	while (lastc==SP || lastc==TB);
	return (lastc);
E 5
I 5
		(void) kdbreadchar();
	while (kdblastc==SP || kdblastc==TB);
	return (kdblastc);
E 5
}

D 5
readchar()
E 5
I 5
kdbreadchar()
E 5
{
	static char *erase = "\b \b";

D 5
	if (lp==0) {
		lp=line;
E 5
I 5
	if (kdblp==0) {
		kdblp=line;
E 5
		do {
D 5
			(void) kdbreadc(lp);
			if (mkfault)
D 3
				error(0);
E 3
I 3
				error((char *)0);
E 3
			switch (*lp) {
E 5
I 5
			(void) kdbreadc(kdblp);
			if (kdbmkfault)
				kdberror((char *)0);
			switch (*kdblp) {
E 5
D 4
			case CTRL(h): case 0177:
E 4
I 4
			case CTRL('h'): case 0177:
E 4
D 5
				if (lp > line)
					kdbwrite(erase, 3), lp--;
E 5
I 5
				if (kdblp > line)
					kdbwrite(erase, 3), kdblp--;
E 5
				break;
D 4
			case CTRL(u):
E 4
I 4
			case CTRL('u'):
E 4
D 5
				while (lp > line) 
					kdbwrite(erase, 3), lp--;
E 5
I 5
				while (kdblp > line) 
					kdbwrite(erase, 3), kdblp--;
E 5
				break;
D 4
			case CTRL(r):
E 4
I 4
			case CTRL('r'):
E 4
				kdbwrite("^R\n", 3);
D 5
				if (lp > line)
					kdbwrite(line, lp-line);
E 5
I 5
				if (kdblp > line)
					kdbwrite(line, kdblp-line);
E 5
				break;
D 4
			case CTRL(w):
E 4
I 4
			case CTRL('w'):
E 4
D 5
				if (lp <= line)
E 5
I 5
				if (kdblp <= line)
E 5
					break;
				do {
D 5
					if (!isspace(*lp))
E 5
I 5
					if (!isspace(*kdblp))
E 5
						goto erasenb;
					kdbwrite(erase, 3);
D 5
				} while (--lp > line);
E 5
I 5
				} while (--kdblp > line);
E 5
				break;
			erasenb:
				do
					kdbwrite(erase, 3);
D 5
				while (--lp > line && !isspace(*lp));
E 5
I 5
				while (--kdblp > line && !isspace(*kdblp));
E 5
				break;
			default:
D 5
				echo(*lp++);
E 5
I 5
				kdbecho(*kdblp++);
E 5
				break;
			}
D 5
		} while (lp == line || lp[-1] != EOR);
		*lp=0; lp=line;
E 5
I 5
		} while (kdblp == line || kdblp[-1] != EOR);
		*kdblp=0; kdblp=line;
E 5
	}
D 5
	if (lastc = peekc)
		peekc=0;
	else  if (lastc = *lp)
		lp++;
	return (lastc);
E 5
I 5
	if (kdblastc = kdbpeekc)
		kdbpeekc=0;
	else  if (kdblastc = *kdblp)
		kdblp++;
	return (kdblastc);
E 5
}

static
D 5
echo(c)
E 5
I 5
kdbecho(c)
E 5
	char c;
{
	char buf[2];

	if (c==0177 || (c<SP && c != TB && c != EOR)) {
		buf[0] = '^';
		buf[1] = c ^ 0100;
		kdbwrite(buf, 2);
	} else
		kdbwrite(&c, 1);
}

D 5
nextchar()
E 5
I 5
kdbnextchar()
E 5
{

D 5
	if (eol(rdc())) {
		lp--;
E 5
I 5
	if (kdbeol(kdbrdc())) {
		kdblp--;
E 5
		return (0);
	}
D 5
	return (lastc);
E 5
I 5
	return (kdblastc);
E 5
}

D 5
quotchar()
E 5
I 5
kdbquotchar()
E 5
{

D 5
	if (readchar()=='\\')
		return (readchar());
	if (lastc=='\'')
E 5
I 5
	if (kdbreadchar()=='\\')
		return (kdbreadchar());
	if (kdblastc=='\'')
E 5
		return (0);
D 5
	return (lastc);
E 5
I 5
	return (kdblastc);
E 5
}

D 5
getformat(deformat)
E 5
I 5
kdbgetformat(deformat)
E 5
	char *deformat;
{
	register char *fptr;
	register int quote;

D 2
	fptr=deformat; quote=FALSE;
E 2
I 2
	fptr=deformat; quote=0;
E 2
D 5
	while ((quote ? readchar()!=EOR : !eol(readchar())))
		if ((*fptr++ = lastc)=='"')
E 5
I 5
	while ((quote ? kdbreadchar()!=EOR : !kdbeol(kdbreadchar())))
		if ((*fptr++ = kdblastc)=='"')
E 5
			quote = ~quote;
D 5
	lp--;
E 5
I 5
	kdblp--;
E 5
	if (fptr!=deformat)
		*fptr++ = '\0';
}
E 1
