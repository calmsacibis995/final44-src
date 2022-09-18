h25901
s 00006/00002/00095
d D 4.3 91/04/18 18:17:31 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00094
d D 4.2 83/08/11 21:13:40 sam 2 1
c standardize sccs keyword lines
e
s 00095/00000/00000
d D 4.1 83/02/12 19:06:21 shannon 1 0
c date and time created 83/02/12 19:06:21 by shannon
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
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3
E 2

 /* t3.c: interpret commands affecting whole table */
# include "t..c"
struct optstr {char *optnam; int *optadd;} options [] = {
	"expand", &expflg,
	"EXPAND", &expflg,
	"center", &ctrflg,
	"CENTER", &ctrflg,
	"box", &boxflg,
	"BOX", &boxflg,
	"allbox", &allflg,
	"ALLBOX", &allflg,
	"doublebox", &dboxflg,
	"DOUBLEBOX", &dboxflg,
	"frame", &boxflg,
	"FRAME", &boxflg,
	"doubleframe", &dboxflg,
	"DOUBLEFRAME", &dboxflg,
	"tab", &tab,
	"TAB", &tab,
	"linesize", &linsize,
	"LINESIZE", &linsize,
	"delim", &delim1,
	"DELIM", &delim1,
	0,0};
getcomm()
{
char line[200], *cp, nb[25], *t;
struct optstr *lp;
int c, ci, found;
for(lp= options; lp->optnam; lp++)
	*(lp->optadd) = 0;
texname = texstr[texct=0];
tab = '\t';
printf(".nr %d \\n(.s\n", LSIZE);
gets1(line);
/* see if this is a command line */
if (index(line,';') == NULL)
	{
	backrest(line);
	return;
	}
for(cp=line; (c = *cp) != ';'; cp++)
	{
	if (!letter(c)) continue;
	found=0;
	for(lp= options; lp->optadd; lp++)
		{
		if (prefix(lp->optnam, cp))
			{
			*(lp->optadd) = 1;
			cp += strlen(lp->optnam);
			if (letter(*cp))
				error("Misspelled global option");
			while (*cp==' ')cp++;
			t=nb;
			if ( *cp == '(')
				while ((ci= *++cp) != ')')
					*t++ = ci;
			else cp--;
			*t++ = 0; *t=0;
			if (lp->optadd == &tab)
				{
				if (nb[0])
					*(lp->optadd) = nb[0];
				}
			if (lp->optadd == &linsize)
				printf(".nr %d %s\n", LSIZE, nb);
			if (lp->optadd == &delim1)
				{
				delim1 = nb[0];
				delim2 = nb[1];
				}
			found=1;
			break;
			}
		}
	if (!found)
		error("Illegal option");
	}
cp++;
backrest(cp);
return;
}
backrest(cp)
	char *cp;
{
char *s;
for(s=cp; *s; s++);
un1getc('\n');
while (s>cp)
	un1getc(*--s);
return;
}
E 1
