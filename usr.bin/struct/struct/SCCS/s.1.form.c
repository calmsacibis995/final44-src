h27380
s 00000/00000/00235
d D 8.1 93/06/06 16:28:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00229
d D 4.3 91/04/16 16:48:29 bostic 3 2
c new copyright; att/bsd/shared
e
s 00009/00000/00222
d D 4.2 90/06/24 13:04:49 bostic 2 1
c will be a problem with the new stdio package; from Chris Torek
e
s 00222/00000/00000
d D 4.1 83/02/11 15:44:03 rrh 1 0
c date and time created 83/02/11 15:44:03 by rrh
e
u
U
t
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include <stdio.h>
#include "1.defs.h"
#include "def.h"
I 2

/*
 * The following are used in <stdio.h> but are defines as constants
 * in 1.defs.h -- since their values are never used here we simply
 * discard them.			XXX
 */
#undef _r
#undef _p

E 2
extern int linechar, errflag, debug;
extern int (*input)(), (*unput)();



uptolow(c)		/*translates upper to lower case */
int c;
	{
	if ('A' <= c && c <= 'Z')
		return(c+'a'-'A');
	else
		return(c);
	}

rdfree(func)
int (*func)();
	{
	int c;
	while ( (c = (*input)()) != '\n')
		{
		(*func)(c);
		}
	}

rdstand(func)
int (*func)();
	{
	int c;
	while ( (c=(*input)()) != '\n')
		{
		(*func)(c);
		}
	}

labfree(func)			/* labels in freeform input */
int (*func)();
	{
	int c;
	int temp[6];
	int j;
	for (j = 0; j < 5; ++j)
		{
		while ( (c = (*input)()) == ' ' || c == '\t' );
		if (c == '\n')
			{
			if (j != 0)
				{
				temp[j] = '\0';
				error("label without code - ignored:","","");
				}
			}
		if (c < '0' || c > '9')
			{
			(*unput)(c);
			break;
			}
		else
			{
			temp[j] = c;
			(*func)(c);
			}
		}
	for ( ; j < 5; ++j)
		(*func)(' ');
	}

labstand(func)			/* labels in standard form input */
int (*func)();
	{
	int c;
	int j;

	for (j = 0; j < 5; ++j)
		{
		c = (*input)();
		if (c == '\n')
			{
			error("line shorter than 5 characters","","");
			errflag = 1;
			(*unput)('\n');
			}
		if (c == '\t' || c == '\n')
			{
			for ( ;j<5; ++j)
				(*func)(' ');
			return;
			}
		(*func)(c);
		}
	(*input)();			/* throw away continuation char */
	}



contfree()			/* identify continuation lines in free-form input */
	{
	return(nonblchar(_diglet,0));	/* any non-alpha non-digit */
	}


nonblchar(class,yesno)
int class,yesno;
	{
#define CARDSIZE	121
	int temp[CARDSIZE];
	int j;
	for (j=0; (temp[j]=(*input)()) == ' ' || temp[j] == '\t'; ++j)
		if (j>=CARDSIZE-1)
			{
			temp[CARDSIZE-1] = '\0';
			 error ("line unexpectedly long","","");
			break;
			}
	if (temp[j]!=EOF && classmatch(temp[j],class)==yesno)
		return(1);
	else
		{
		for ( ; j >= 0; --j)
			(*unput)(temp[j]);
		return(0);
		}
	}


contstand()			/* continuation lines in standard form input */
	{
	int temp[6];
	int i;

	for (i = 0; i < 6; ++i)
		{
		temp[i] = (*input)();
		if (temp[i] == '\t' || temp[i] == '\n' || temp[i] == '\0' || temp[i] == EOF)
			{
			for ( ;i >= 0; --i)
				(*unput)(temp[i]);
			return(0);
			}
		}
	if (temp[5] != '0' && temp[5] != ' ')
		return(1);
	else
		{
		for ( i = 5 ; i >= 0; --i)
			(*unput)(temp[i]);
		return(0);
		}
	}



comstand(posafter)			/* standard form comments */
int posafter;
	{
	int c;
	c = (*input)();
	if (!posafter)
		(*unput)(c);
	if (c == 'c' || c == '*' || c== '#')
		return(1);
	else
		return(0);
	}


comfree(posafter)
int posafter;
	{
	return(comstand(posafter));
	}
int (*rline[])()		= {rdfree,rdstand};
int (*comment[])()		= {comfree,comstand};
int (*getlabel[])()		= {labfree, labstand};
int (*chkcont[])()		= {contfree,contstand};

blankline()
	{
	if ( nonblchar(_nl,1) )		/* first non-blank is nl */
		{
		(*unput) ('\n');
		return(1);
		}
	else return(0);
	}

#define maxunbp	80
char unbuf[maxunbp+1];
int unbp;

empseek(linebeg)
int linebeg;
	{
	unbp = 0;
	if (fseek(infd,(long)(linebeg+rtnbeg),0) == -1)
		faterr("in disk seek","","");
	}

inchar()
	{
	if (unbp > 0)
		return( unbuf[--unbp] );
	else
		{
		return( uptolow(getc(infd)) );
		}
	}


unchar(c)
int c;
	{
	if (unbp >= maxunbp)
		faterr("dec.rat: unbuf size exceeded","","");
	if(c!=EOF)unbuf[unbp++] = c;
	}
E 1
