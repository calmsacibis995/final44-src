h33419
s 00003/00003/00073
d D 2.2 87/04/01 15:17:37 jaap 3 2
c Updates from bwk, see README for details
e
s 00057/00043/00019
d D 2.1 85/07/18 18:07:25 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00062/00000/00000
d D 1.1 85/03/01 15:26:42 jaap 1 0
c date and time created 85/03/01 15:26:42 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 2
static char *sccsid = "%M%	(CWI)	%I%	%E%";
#endif
E 2
I 2
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
E 2
# include "e.h"

D 2
setfont(ch1) char ch1; {
	/* use number '1', '2', '3' for roman, italic, bold */
E 2
I 2
setfont(ch1)
	char *ch1;
{
E 2
	yyval = ft;
D 2
	if (ch1 == 'r' || ch1 == 'R')
		ft = ROM;
	else if (ch1 == 'i' || ch1 == 'I')
E 2
I 2
	if (strcmp(ch1, "I") == 0) {	/* I and italic mean merely position 2 */
		*ch1 = '2';
E 2
		ft = ITAL;
D 2
	else if (ch1 == 'b' || ch1 == 'B')
E 2
I 2
	} else if (strcmp(ch1, "B") == 0) {	/* and similarly for B & bold */
		*ch1 = '3';
E 2
		ft = BLD;
D 2
	else
		ft = ch1;
	printf(".ft %c\n", ft);
	if(dbg)printf(".\tsetfont %c %c\n", ch1, ft);
E 2
I 2
	} else if (strcmp(ch1, "R") == 0) {	/* and R and roman */
		*ch1 = '1';
		ft = ROM;
	} else {
		ft = ROM;	/* assume it's a roman style */
	}
	ftp++;
	if (ftp >= &ftstack[10])
		error(FATAL, "font stack overflow");
	ftp->ft = ft;
	if (ch1[1] == 0) {	/* 1-char name */
		ftp->name[0] = *ch1;
		ftp->name[1] = '\0';
	} else
		sprintf(ftp->name, "(%s", ch1);
	dprintf(".\tsetfont %s %c\n", ch1, ft);
E 2
}

D 2
font(p1, p2) int p1, p2; {
E 2
I 2
font(p1, p2)
	int p1, p2;
{
E 2
		/* old font in p1, new in ft */
	yyval = p2;
	lfont[yyval] = rfont[yyval] = ft==ITAL ? ITAL : ROM;
D 2
	if(dbg)printf(".\tb:fb: S%d <- \\f%c S%d \\f%c b=%d,h=%d,lf=%c,rf=%c\n", 
		yyval, ft, p2, p1, ebase[yyval], eht[yyval], lfont[yyval], rfont[yyval]);
	printf(".ds %d \\f%c\\*(%d\\f%c\n", 
		yyval, ft, p2, p1);
E 2
I 2
	ftp--;
E 2
	ft = p1;
D 2
	printf(".ft %c\n", ft);
E 2
}

D 2
fatbox(p) int p; {
	int sh;

	yyval = p;
	sh = ps / 4;
	nrwid(p, ps, p);
	printf(".ds %d \\*(%d\\h'-\\n(%du+0.05m'\\*(%d\n", p, p, p, p);
	if(dbg)printf(".\tfat %d, sh=0.05m\n", p, sh);
}

globfont() {
E 2
I 2
globfont()
{
E 2
	char temp[20];

D 2
	getstr(temp, 20);
E 2
I 2
	getstr(temp, sizeof(temp));
E 2
	yyval = eqnreg = 0;
D 2
	gfont = temp[0];
	switch (gfont) {
	case 'r': case 'R':
		gfont = '1';
		break;
	case 'i': case 'I':
		gfont = '2';
		break;
	case 'b': case 'B':
		gfont = '3';
		break;
E 2
I 2
	if (strcmp(temp, "I") == 0 || strncmp(temp, "it", 2) == 0) {
		ft = ITAL;
		strcpy(temp, "2");
	} else if (strcmp(temp, "B") == 0 || strncmp(temp, "bo", 2) == 0) {
		ft = BLD;
		strcpy(temp, "3");
	} else if (strcmp(temp, "R") == 0 || strncmp(temp, "ro", 2) == 0) {
		ft = ROM;
		strcpy(temp, "1");
	} else { 
		ft = ROM;	/* assume it's a roman style */
E 2
	}
D 2
	printf(".ft %c\n", gfont);
	ft = gfont;
E 2
I 2
	ftstack[0].ft = ft;
	if (temp[1] == 0)	/* 1-char name */
		strcpy(ftstack[0].name, temp);
	else
		sprintf(ftstack[0].name, "(%.2s", temp);
}

fatbox(p)
	int p;
{
I 3
	extern float Fatshift;

E 3
	yyval = p;
D 3
	/* nrwid(p, ps, p); */
	/* printf(".ds %d \\*(%d\\h'-\\n(%du+0.05m'\\*(%d\n", p, p, p, p); */
	printf(".ds %d \\*(%d\\h'-\\w'\\*(%d'u+0.05m'\\*(%d\n", p, p, p, p);
E 3
I 3
	printf(".ds %d \\*(%d\\h'-\\w'\\*(%d'u+%gm'\\*(%d\n", p, p, p, Fatshift, p);
E 3
E 2
}
E 1
