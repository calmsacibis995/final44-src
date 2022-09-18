h26335
s 00000/00000/00220
d D 8.1 93/06/06 16:08:34 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00001/00214
d D 1.3 91/04/16 14:45:32 bostic 3 2
c new copyright; att/bsd/shared
e
s 00004/00001/00211
d D 1.2 83/08/11 21:00:37 sam 2 1
c standardize sccs keyword lines
e
s 00212/00000/00000
d D 1.1 82/12/15 21:46:33 clemc 1 0
c date and time created 82/12/15 21:46:33 by clemc
e
u
U
t
Original BTL Ratfor System for 4.2
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */

E 3

E 2
#include "r.h"
char	ibuf[BUFSIZ];
char	*ip = ibuf;

char	type[] = {
	0,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,
	CRAP,	'\t',	'\n',	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,
	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,
	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,	CRAP,
	' ',	'!',	'"',	'#',	'$',	'%',	'&',	'\'',
	'(',	')',	'*',	'+',	',',	'-',	'.',	'/',
	DIG,	DIG,	DIG,	DIG,	DIG,	DIG,	DIG,	DIG,
	DIG,	DIG,	':',	';',	'<',	'=',	'>',	'?',
	'@',	LET,	LET,	LET,	LET,	LET,	LET,	LET,
	LET,	LET,	LET,	LET,	LET,	LET,	LET,	LET,
	LET,	LET,	LET,	LET,	LET,	LET,	LET,	LET,
	LET,	LET,	LET,	'[',	'\\',	']',	'^',	'_',
	'`',	LET,	LET,	LET,	LET,	LET,	LET,	LET,
	LET,	LET,	LET,	LET,	LET,	LET,	LET,	LET,
	LET,	LET,	LET,	LET,	LET,	LET,	LET,	LET,
	LET,	LET,	LET,	'{',	'|',	'}',	'~',	0,
};

gtok(s) char *s; {	/* get token into s */
	register c, t;
	register char *p;
	struct nlist *q;

	for(;;) {
		p = s;
		*p++ = c = getchr();
		switch(t = type[c]) {
		case 0:
			if (infptr > 0) {
				fclose(infile[infptr]);
				infptr--;
				continue;
			}
			if (svargc > 1) {
				svargc--;
				svargv++;
				if (infile[infptr] != stdin)
					fclose(infile[infptr]);
				if( (infile[infptr] = fopen(*svargv,"r")) == NULL )
					cant(*svargv);
				linect[infptr] = 0;
				curfile[infptr] = *svargv;
				continue;
			}
			return(EOF);	/* real eof */
		case ' ':
		case '\t':
			while ((c = getchr()) == ' ' || c == '\t')
				;	/* skip others */
			if (c == COMMENT || c == '_') {
				putbak(c);
				continue;
			}
			if (c != '\n') {
				putbak(c);
				*p = '\0';
				return(' ');
			} else {
				*s = '\n';
				*(s+1) = '\0';
				return(*s);
			}
		case '_':
			while ((c = getchr()) == ' ' || c == '\t')
				;
			if (c == COMMENT) {
				putbak(c);
				gtok(s);	/* recursive */
			}
			else if (c != '\n')
				putbak(c);
			continue;
		case LET:
		case DIG:
			while ((t=type[*p = getchr()]) == LET || t == DIG)
				p++;
			putbak(*p);
			*p = '\0';
			if ((q = lookup(s))->name != NULL && q->ydef == 0) {	/* found but not keyword */
				if (q->def != fcnloc) {	/* not "function" */
					pbstr(q->def);
					continue;
				}
				getfname();	/* recursive gtok */
			}
			for (p=s; *p; p++)
				if (*p>='A' && *p<='Z')
					*p += 'a' - 'A';
			for (p=s; *p; p++)
				if (*p < '0' || *p > '9')
					return(LET);
			return(DIG);
		case '[':
			*p = '\0';
			return('{');
		case ']':
			*p = '\0';
			return('}');
		case '$':
		case '\\':
			if ((*p = getchr()) == '(' || *p == ')') {
				putbak(*p=='(' ? '{' : '}');
				continue;
			}
			if (*p == '"' || *p == '\'')
				p++;
			else
				putbak(*p);
			*p = '\0';
			return('$');
		case COMMENT:
			comment[comptr++] = 'c';
			while ((comment[comptr++] = getchr()) != '\n')
				;
			flushcom();
			*s = '\n';
			*(s+1) = '\0';
			return(*s);
		case '"':
		case '\'':
			for (; (*p = getchr()) != c; p++) {
				if (*p == '\\')
					*++p = getchr();
				if (*p == '\n') {
					error("missing quote");
					putbak('\n');
					break;
				}
			}
			*p++ = c;
			*p = '\0';
			return(QUOTE);
		case '%':
			while ((*p = getchr()) != '\n')
				p++;
			putbak(*p);
			*p = '\0';
			return('%');
		case '>': case '<': case '=': case '!': case '^':
			return(peek(p, '='));
		case '&':
			return(peek(p, '&'));
		case '|':
			return(peek(p, '|'));
		case CRAP:
			continue;
		default:
			*p = '\0';
			return(*s);
		}
	}
}

gnbtok(s) char *s; {
	register c;
	while ((c = gtok(s)) == ' ' || c == '\t')
		;
	return(c);
}

getfname() {
	while (gtok(fcname) == ' ')
		;
	pbstr(fcname);
	putbak(' ');
}

peek(p, c1) char *p, c1; {
	register c;
	c = *(p-1);
	if ((*p = getchr()) == c1)
		p++;
	else
		putbak(*p);
	*p = '\0';
	return(c);
}

pbstr(str)
register char *str;
{
	register char *p;

	p = str;
	while (*p++);
	--p;
	if (ip >= &ibuf[BUFSIZ]) {
		error("pushback overflow");
		exit(1);
	}
	while (p > str)
		putbak(*--p);
}

getchr() {
	register c;

	if (ip > ibuf)
		return(*--ip);
	c = getc(infile[infptr]);
	if (c == '\n')
		linect[infptr]++;
	if (c == EOF)
		return(0);
	return(c);
}
E 1
