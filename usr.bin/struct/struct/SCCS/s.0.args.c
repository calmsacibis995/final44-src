h61292
s 00000/00000/00106
d D 8.1 93/06/06 16:28:30 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00100
d D 4.2 91/04/16 16:48:19 bostic 2 1
c new copyright; att/bsd/shared
e
s 00102/00000/00000
d D 4.1 83/02/11 15:43:47 rrh 1 0
c date and time created 83/02/11 15:43:47 by rrh
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
int errflag;
FILE *infd;


int intcase=1, arbcase=0;
int exitsize=0;			/* max number of nodes to be left in loop without iterating */
int maxnode=400;	/* max number of nodes */
int maxhash=347;	/* prime number = size of hash table */
int progress=0;		/* if not 0, print line number every n lines, n = progress */
int labinit=10;			/* labels generated starting with labinit */
int labinc=10;			/* labels increase by labinc */
int inputform=0;		/* = 0 if freeform input, 1 if standard form input */
int debug=0;
int levbrk=1;	/* true implies multilevel breaks; false implies single-level breaks only */
int levnxt=1;	/* true implies multilevel nexts; false implies single-level nexts only */


int maxprogsw=12;		/* number of program switches which can be set */
char *progsw[]		= {"i", "a",
			"e", "m",
			"h", "p",
			"t", "c",
			"s", "d",
			"b", "n"
			};


int *swval[]		= {&intcase, &arbcase,
			&exitsize, &maxnode,
			&maxhash, &progress,
			&labinit, &labinc,
			&inputform, &debug,
			&levbrk, &levnxt
			};


char *getargs(argc, argv)
int argc; char *argv[];
	{
	int n, infile;
	infile = 0;

	for (n = 1; n < argc; ++n)
		{
		if (argv[n][0] == '-')
			setsw(&argv[n][1]);
		else
			{
			if (infile != 0)
				error("multiple input files - using first one: ", argv[infile],"");
			else
				infile = n;
			}
		}
	if (errflag)
		exit(1);
	if (!infile) faterr("no input file","","");
	infd = fopen(argv[infile],"r");
	if (infd == NULL)
		faterr("can't open input file:",argv[infile],"");
	return;
	}

setsw(str)
char *str;
	{
	int i, val, swnum;
#define maxtemp 15
	char temp[maxtemp];
	for (i = 0; 'a' <= str[i] && str[i] <= 'z'; ++i)
		{
		if (i >= maxtemp)
			{
			error("invalid switch:",str,"");
			errflag = 1;
			}
		temp[i] = str[i];
		}
	temp[i] = '\0';

	swnum = find(temp,progsw,maxprogsw);
	if (swnum == -1)
		{
		error("invalid switch:", str,"");
		errflag = 1;
		return;
		}
	if (str[i] == '\0')
		*(swval[swnum]) = !*(swval[swnum]);
	else
		{
		sscanf(&str[i],"%d",&val);
		*(swval[swnum]) = val;
		}
	}
E 1
