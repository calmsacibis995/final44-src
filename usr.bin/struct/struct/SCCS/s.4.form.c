h21900
s 00000/00000/00121
d D 8.1 93/06/06 16:30:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00115
d D 4.2 91/04/16 16:48:51 bostic 2 1
c new copyright; att/bsd/shared
e
s 00117/00000/00000
d D 4.1 83/02/11 15:44:54 rrh 1 0
c date and time created 83/02/11 15:44:54 by rrh
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <stdio.h>
#
#include "def.h"
#include "4.def.h"
extern int linechars;
extern int rdfree(), comfree(), labfree(), contfree();
extern int rdstand(), comstand(), labstand(), contstand();
extern int (*rline[])();
extern int (*comment[])();
extern int (*getlabel[])();
extern int (*chkcont[])();
null(c)
char c;
	{return;}



comprint()
	{
	int c, blank, first,count;
	blank = 1;
	first = 1;
	count = 0;
	while ((c = (*comment[inputform])(0) ) || blankline() )
		{
		++count;
		if (c)
			{
			(*comment[inputform])(1);		/* move head past comment signifier */
			blank = blankline();
			/* if (first && !blank)
				OUTSTR("#\n");*/
			prline("#");
			first = 0;
			}
		else
			(*rline[inputform])(null);
		}
	/* if (!blank) 
		OUTSTR("#\n"); */
	return(count);
	}



prcode(linecount,tab)
int linecount, tab;
	{
	int someout;
	someout = FALSE;
	while (linecount)
		{
		if ( (*comment[inputform])(0) )
			{
			linecount -= comprint();
			someout = TRUE;
			continue;
			}
		else if (blankline() )
			(*rline[inputform])(null);
		else if ((*chkcont[inputform])() )
			{
			TABOVER(tab);
			prline("&");
			someout  = TRUE;
			}
		else 
			{if (someout) TABOVER(tab);
			(*getlabel[inputform])(null);
			prline("");
			someout=TRUE;
			}
		--linecount;
		}
	}


charout(c)
char c;
	{
	putc(c,outfd);
	}



prline(str)
char *str;
	{
	fprintf(outfd,"%s",str);
	(*rline[inputform]) (charout);
	putc('\n',outfd);
	}


input2()
	{
	static int c;
	c = inchar();
	if (c == '\n')
		linechars = 0;
	else
		++linechars;
	return(c);
	}


unput2(c)
int c;
	{
	unchar(c);
	--linechars;
	return(c);
	}
E 1
