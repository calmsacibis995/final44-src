h02510
s 00000/00000/00381
d D 8.1 93/06/06 16:08:29 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00376
d D 1.4 91/04/16 14:45:28 bostic 4 3
c new copyright; att/bsd/shared
e
s 00004/00001/00373
d D 1.3 83/08/11 21:00:21 sam 3 2
c standardize sccs keyword lines
e
s 00003/00001/00371
d D 1.2 82/12/15 22:00:19 clemc 2 1
c Added a bug fix from Tom Quarles, to fix a problem where
c The preprocessor will determine that there is no way to reach the end
c of the for loop because of a return statement imbedded as the last line of
c a for loop.  The problem code is:
c 	for ( ... ) { 
c 		if (..) {
c 			...; next
c 		}
c 		....
c 		return
c 	}
c 
e
s 00372/00000/00000
d D 1.1 82/12/15 21:46:27 clemc 1 0
c date and time created 82/12/15 21:46:27 by clemc
e
u
U
t
Original BTL Ratfor System for 4.2
T
I 4
/*-
 * %sccs.include.proprietary.c%
 */

E 4
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

E 3
#include "r.h"

#define	wasbreak	brkused[brkptr]==1 || brkused[brkptr]==3
#define	wasnext	brkused[brkptr]==2 || brkused[brkptr]==3

int	transfer	= 0;	/* 1 if just finished retrun, break, next */

char	fcname[10];
char	scrat[500];

int	brkptr	= -1;
int	brkstk[10];	/* break label */
int	typestk[10];	/* type of loop construct */
int	brkused[10];	/* loop contains BREAK or NEXT */

int	forptr	= 0;
char	*forstk[10];

repcode() {
	transfer = 0;
	outcont(0);
	putcom("repeat");
	yyval = genlab(3);
	indent++;
	outcont(yyval);
	brkstk[++brkptr] = yyval+1;
	typestk[brkptr] = REPEAT;
	brkused[brkptr] = 0;
}

untils(p1,un) int p1,un; {
	outnum(p1+1);
	outtab();
	if (un > 0) {
		outcode("if(.not.");
		balpar();
		outcode(")");
	}
	transfer = 0;
	outgoto(p1);
	indent--;
	if (wasbreak)
		outcont(p1+2);
	brkptr--;
}

ifcode() {
	transfer = 0;
	outtab();
	outcode("if(.not.");
	balpar();
	outcode(")");
	outgoto(yyval=genlab(2));
	indent++;
}

elsecode(p1) {
	outgoto(p1+1);
	indent--;
	putcom("else");
	indent++;
	outcont(p1);
}

whilecode() {
	transfer = 0;
	outcont(0);
	putcom("while");
	brkstk[++brkptr] = yyval = genlab(2);
	typestk[brkptr] = WHILE;
	brkused[brkptr] = 0;
	outnum(yyval);
	outtab();
	outcode("if(.not.");
	balpar();
	outcode(")");
	outgoto(yyval+1);
	indent++;
}

whilestat(p1) int p1; {
	outgoto(p1);
	indent--;
	putcom("endwhile");
	outcont(p1+1);
	brkptr--;
}

balpar() {
	register c, lpar;
	while ((c=gtok(scrat)) == ' ' || c == '\t')
		;
	if (c != '(') {
		error("missing left paren");
		return;
	}
	outcode(scrat);
	lpar = 1;
	do {
		c = gtok(scrat);
		if (c==';' || c=='{' || c=='}' || c==EOF) {
			pbstr(scrat);
			break;
		}
		if (c=='(')
			lpar++;
		else if (c==')')
			lpar--;
		else if (c == '\n') {
			while ((c = gtok(scrat)) == ' ' || c=='\t' || c=='\n')
				;
			pbstr(scrat);
			continue;
		}
		else if (c == '=' && scrat[1] == '\0')
			error("assigment inside conditional");
		outcode(scrat);
	} while (lpar > 0);
	if (lpar != 0)
		error("missing parenthesis");
}

int	labval	= 23000;

genlab(n){
	labval += n;
	return(labval-n);
}

gokcode(p1) {
	transfer = 0;
	outtab();
	outcode(p1);
	eatup();
	outdon();
}

eatup() {
	int t, lpar;
	char temp[100];
	lpar = 0;
	do {
		if ((t = gtok(scrat)) == ';' || t == '\n')
			break;
		if (t == '{' || t == '}' || t == EOF) {
			pbstr(scrat);
			break;
		}
		if (t == ',' || t == '+' || t == '-' || t == '*' || t == '('
		  || t == '&' || t == '|' || t == '=') {
			while (gtok(temp) == '\n')
				;
			pbstr(temp);
		}
		if (t == '(')
			lpar++;
		else if (t==')') {
			lpar--;
			if (lpar < 0) {
				error("missing left paren");
				return(1);
			}
		}
		outcode(scrat);
	} while (lpar >= 0);
	if (lpar > 0) {
		error("missing right paren");
		return(1);
	}
	return(0);
}

forcode(){
	int lpar, t;
	char *ps, *qs;

	transfer = 0;
	outcont(0);
	putcom("for");
	yyval = genlab(3);
	brkstk[++brkptr] = yyval+1;
	typestk[brkptr] = FOR;
	brkused[brkptr] = 0;
	forstk[forptr++] = malloc(1);
	if ((t = gnbtok(scrat)) != '(') {
		error("missing left paren in FOR");
		pbstr(scrat);
		return;
	}
	if (gnbtok(scrat) != ';') {	/* real init clause */
		pbstr(scrat);
		outtab();
		if (eatup() > 0) {
			error("illegal FOR clause");
			return;
		}
		outdon();
	}
	if (gnbtok(scrat) == ';')	/* empty condition */
		outcont(yyval);
	else {	/* non-empty condition */
		pbstr(scrat);
		outnum(yyval);
		outtab();
		outcode("if(.not.(");
		for (lpar=0; lpar >= 0;) {
			if ((t = gnbtok(scrat)) == ';')
				break;
			if (t == '(')
				lpar++;
			else if (t == ')') {
				lpar--;
				if (lpar < 0) {
					error("missing left paren in FOR clause");
					return;
				}
			}
			if (t != '\n')
				outcode(scrat);
		}
		outcode("))");
		outgoto(yyval+2);
		if (lpar < 0)
			error("invalid FOR clause");
	}
	ps = scrat;
	for (lpar=0; lpar >= 0;) {
		if ((t = gtok(ps)) == '(')
			lpar++;
		else if (t == ')')
			lpar--;
		if (lpar >= 0 && t != '\n')
			while(*ps)
				ps++;
	}
	*ps = '\0';
	qs = forstk[forptr-1] = malloc((unsigned)(ps-scrat+1));
	ps = scrat;
	while (*qs++ = *ps++)
		;
	indent++;
}

forstat(p1) int p1; {
	char *bp, *q;
	bp = forstk[--forptr];
D 2
	if (wasnext)
E 2
I 2
	if (wasnext) {
E 2
		outnum(p1+1);
I 2
		transfer = 0;
	}
E 2
	if (nonblank(bp)){
		outtab();
		outcode(bp);
		outdon();
	}
	outgoto(p1);
	indent--;
	putcom("endfor");
	outcont(p1+2);
	for (q=bp; *q++;);
	free(bp);
	brkptr--;
}

retcode() {
	register c;
	if ((c = gnbtok(scrat)) != '\n' && c != ';' && c != '}') {
		pbstr(scrat);
		outtab();
		outcode(fcname);
		outcode(" = ");
		eatup();
		outdon();
	}
	else if (c == '}')
		pbstr(scrat);
	outtab();
	outcode("return");
	outdon();
	transfer = 1;
}

docode() {
	transfer = 0;
	outtab();
	outcode("do ");
	yyval = genlab(2);
	brkstk[++brkptr] = yyval;
	typestk[brkptr] = DO;
	brkused[brkptr] = 0;
	outnum(yyval);
	eatup();
	outdon();
	indent++;
}

dostat(p1) int p1; {
	outcont(p1);
	indent--;
	if (wasbreak)
		outcont(p1+1);
	brkptr--;
}

#ifdef	gcos
#define	atoi(s)	(*s-'0')	/* crude!!! */
#endif

breakcode() {
	int level, t;

	level = 0;
	if ((t=gnbtok(scrat)) == DIG)
		level = atoi(scrat) - 1;
	else if (t != ';')
		pbstr(scrat);
	if (brkptr-level < 0)
		error("illegal BREAK");
	else {
		outgoto(brkstk[brkptr-level]+1);
		brkused[brkptr-level] |= 1;
	}
	transfer = 1;
}

nextcode() {
	int level, t;

	level = 0;
	if ((t=gnbtok(scrat)) == DIG)
		level = atoi(scrat) - 1;
	else if (t != ';')
		pbstr(scrat);
	if (brkptr-level < 0)
		error("illegal NEXT");
	else {
		outgoto(brkstk[brkptr-level]);
		brkused[brkptr-level] |= 2;
	}
	transfer = 1;
}

nonblank(s) char *s; {
	int c;
	while (c = *s++)
		if (c!=' ' && c!='\t' && c!='\n')
			return(1);
	return(0);
}

int	errorflag	= 0;

error(s1) char *s1; {
	if (errorflag == 0)
		fprintf(stderr, "ratfor:");
	fprintf(stderr, "error at line %d, file %s: ",linect[infptr],curfile[infptr]);
	fprintf(stderr, s1);
	fprintf(stderr, "\n");
	errorflag = 1;
}

errcode() {
	int c;
	if (errorflag == 0)
		fprintf(stderr, "******\n");
	fprintf(stderr, "*****F ratfor:");
	fprintf(stderr, "syntax error, line %d, file %s\n", linect[infptr], curfile[infptr]);
	while ((c=getchr())!=';' && c!='}' && c!='\n' && c!=EOF && c!='\0')
		;
	if (c == EOF || c == '\0')
		putbak(c);
	errorflag = 1;
}
E 1
