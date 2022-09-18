h36953
s 00077/00129/00471
d D 8.2 95/04/29 09:56:51 bostic 7 6
c There were several places where m4 did not conform to the specification
c in `The M4 Macro Processor', by Kernighan and Ritchie.  The following
c patch addresses them.
c * `|' and `||' are both logical or.  There is no binary or.
c * `&' and `&&' are both logical and.  There is no binary and.
c * `!' has a much higher precedence.
c * The equal and relation operators have the same precedence.
c * `**' is implemented, and `^' is for exponentation (not xor).
c * Unary `+' in implemented.
c From: "Charles M. Hannum" <mycroft@NetBSD.ORG>
e
s 00002/00002/00598
d D 8.1 93/06/06 15:04:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00599
d D 5.5 91/11/20 16:27:08 bostic 5 4
c add affiliation for Oz
e
s 00406/00380/00194
d D 5.4 91/09/03 11:38:00 bostic 4 3
c New version from Oz Yigit; BSD-ized
e
s 00003/00001/00571
d D 5.3 91/02/26 14:05:40 bostic 3 2
c ANSI fixes, use strdup(3) instead of rolling your own
e
s 00001/00011/00571
d D 5.2 90/06/01 16:09:28 bostic 2 1
c new copyright notice
e
s 00582/00000/00000
d D 5.1 89/08/28 15:14:14 bostic 1 0
c date and time created 89/08/28 15:14:14 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
D 5
 * Ozan Yigit.
E 5
I 5
 * Ozan Yigit at York University.
E 5
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 3
D 4
#include <setjmp.h>
E 4
I 4
#include <sys/cdefs.h>
E 4
#include <stdio.h>

E 3
/*
 *      expression evaluator: performs a standard recursive
 *      descent parse to evaluate any expression permissible
 *      within the following grammar:
 *
 *      expr    :       query EOS
 *      query   :       lor
 *              |       lor "?" query ":" query
 *      lor     :       land { "||" land }
D 7
 *      land    :       bor { "&&" bor }
 *      bor     :       bxor { "|" bxor }
 *      bxor    :       band { "^" band }
 *      band    :       eql { "&" eql }
 *      eql     :       relat { eqrel relat }
 *      relat   :       shift { rel shift }
E 7
I 7
 *      land    :       not { "&&" not }
 *	not	:	eqrel
 *		|	'!' not
 *      eqrel   :       shift { eqrelop shift }
E 7
 *      shift   :       primary { shop primary }
 *      primary :       term { addop term }
D 7
 *      term    :       unary { mulop unary }
E 7
I 7
 *      term    :       exp { mulop exp }
 *	exp	:	unary { expop unary }
E 7
 *      unary   :       factor
 *              |       unop unary
 *      factor  :       constant
 *              |       "(" query ")"
 *      constant:       num
 *              |       "'" CHAR "'"
 *      num     :       DIGIT
 *              |       DIGIT num
 *      shop    :       "<<"
 *              |       ">>"
D 7
 *      eqlrel  :       "="
E 7
I 7
 *      eqrel   :       "="
E 7
 *              |       "=="
 *              |       "!="
D 7
 *      rel     :       "<"
E 7
I 7
 *      	|       "<"
E 7
 *              |       ">"
 *              |       "<="
 *              |       ">="
 *
 *
 *      This expression evaluator is lifted from a public-domain
 *      C Pre-Processor included with the DECUS C Compiler distribution.
 *      It is hacked somewhat to be suitable for m4.
 *
 *      Originally by:  Mike Lutz
 *                      Bob Harper
 */
D 4
 
E 4
I 4

E 4
#define TRUE    1
#define FALSE   0
#define EOS     (char) 0
#define EQL     0
#define NEQ     1
#define LSS     2
#define LEQ     3
#define GTR     4
#define GEQ     5
#define OCTAL   8
#define DECIMAL 10
D 4
 
static char *nxtch;     /* Parser scan pointer */
 
E 4
I 4

static char *nxtch;		       /* Parser scan pointer */

static int query __P((void));
static int lor __P((void));
static int land __P((void));
D 7
static int bor __P((void));
static int bxor __P((void));
static int band __P((void));
static int eql __P((void));
static int relat __P((void));
E 7
I 7
static int not __P((void));
static int eqrel __P((void));
E 7
static int shift __P((void));
static int primary __P((void));
static int term __P((void));
I 7
static int exp __P((void));
E 7
static int unary __P((void));
static int factor __P((void));
static int constant __P((void));
static int num __P((void));
D 7
static int geteql __P((void));
static int getrel __P((void));
E 7
I 7
static int geteqrel __P((void));
E 7
static int skipws __P((void));
static void experr __P((char *));

E 4
/*
 * For longjmp
 */
D 3
#include <setjmp.h>
E 3
D 4
static jmp_buf  expjump;
 
E 4
I 4
#include <setjmp.h>
static jmp_buf expjump;

E 4
/*
 * macros:
D 4
 *
E 4
 *      ungetch - Put back the last character examined.
 *      getch   - return the next character from expr string.
 */
#define ungetch()       nxtch--
#define getch()         *nxtch++
D 4
 
E 4
I 4

int
E 4
expr(expbuf)
char *expbuf;
{
D 4
        register int rval;
 
        nxtch = expbuf;
        if (setjmp(expjump) != 0)
                return (FALSE);
        rval = query();
        if (skipws() == EOS)
                return(rval);
        experr("Ill-formed expression");
E 4
I 4
	register int rval;

	nxtch = expbuf;
	if (setjmp(expjump) != 0)
		return FALSE;

	rval = query();
	if (skipws() == EOS)
		return rval;

	printf("m4: ill-formed expression.\n");
	return FALSE;
E 4
}
D 4
 
E 4
I 4

E 4
/*
 * query : lor | lor '?' query ':' query
D 4
 *
E 4
 */
I 4
static int
E 4
query()
{
D 4
        register int bool, true_val, false_val;
 
        bool = lor();
        if (skipws() != '?') {
                ungetch();
                return(bool);
        }
 
        true_val = query();
        if (skipws() != ':')
                experr("Bad query");
 
        false_val = query();
        return(bool ? true_val : false_val);
E 4
I 4
	register int bool, true_val, false_val;

	bool = lor();
	if (skipws() != '?') {
		ungetch();
		return bool;
	}

	true_val = query();
	if (skipws() != ':')
		experr("bad query");

	false_val = query();
	return bool ? true_val : false_val;
E 4
}
D 4
 
E 4
I 4

E 4
/*
 * lor : land { '||' land }
D 4
 *
E 4
 */
I 4
static int
E 4
lor()
{
D 4
        register int c, vl, vr;
 
        vl = land();
        while ((c = skipws()) == '|' && getch() == '|') {
                vr = land();
                vl = vl || vr;
        }
 
        if (c == '|')
                ungetch();
        ungetch();
        return(vl);
E 4
I 4
	register int c, vl, vr;

	vl = land();
D 7
	while ((c = skipws()) == '|' && getch() == '|') {
E 7
I 7
	while ((c = skipws()) == '|') {
		if (getch() != '|')
			ungetch();
E 7
		vr = land();
		vl = vl || vr;
	}

D 7
	if (c == '|')
		ungetch();
E 7
	ungetch();
	return vl;
E 4
}
D 4
 
E 4
I 4

E 4
/*
D 7
 * land : bor { '&&' bor }
E 7
I 7
 * land : not { '&&' not }
E 7
D 4
 *
E 4
 */
I 4
static int
E 4
land()
{
D 4
        register int c, vl, vr;
 
        vl = bor();
        while ((c = skipws()) == '&' && getch() == '&') {
                vr = bor();
                vl = vl && vr;
        }
 
        if (c == '&')
                ungetch();
        ungetch();
        return(vl);
E 4
I 4
	register int c, vl, vr;

D 7
	vl = bor();
	while ((c = skipws()) == '&' && getch() == '&') {
		vr = bor();
E 7
I 7
	vl = not();
	while ((c = skipws()) == '&') {
		if (getch() != '&')
			ungetch();
		vr = not();
E 7
		vl = vl && vr;
	}

D 7
	if (c == '&')
		ungetch();
E 7
	ungetch();
	return vl;
E 4
}
D 4
 
E 4
I 4

E 4
/*
D 7
 * bor : bxor { '|' bxor }
E 7
I 7
 * not : eqrel | '!' not
E 7
D 4
 *
E 4
 */
I 4
static int
E 4
D 7
bor()
E 7
I 7
not()
E 7
{
D 4
        register int vl, vr, c;
 
        vl = bxor();
        while ((c = skipws()) == '|' && getch() != '|') {
                ungetch();
                vr = bxor();
                vl |= vr;
        }
 
        if (c == '|')
                ungetch();
        ungetch();
        return(vl);
E 4
I 4
D 7
	register int vl, vr, c;
E 7
I 7
	register int val, c;
E 7

D 7
	vl = bxor();
	while ((c = skipws()) == '|' && getch() != '|') {
E 7
I 7
	if ((c = skipws()) == '!' && getch() != '=') {
E 7
		ungetch();
D 7
		vr = bxor();
		vl |= vr;
E 7
I 7
		val = not();
		return !val;
E 7
	}

D 7
	if (c == '|')
E 7
I 7
	if (c == '!')
E 7
		ungetch();
	ungetch();
D 7
	return vl;
E 7
I 7
	return eqrel();
E 7
E 4
}
D 4
 
E 4
I 4

E 4
/*
D 7
 * bxor : band { '^' band }
E 7
I 7
 * eqrel : shift { eqrelop shift }
E 7
D 4
 *
E 4
 */
I 4
static int
E 4
D 7
bxor()
E 7
I 7
eqrel()
E 7
{
D 4
        register int vl, vr;
 
        vl = band();
        while (skipws() == '^') {
                vr = band();
                vl ^= vr;
        }
 
        ungetch();
        return(vl);
E 4
I 4
D 7
	register int vl, vr;
E 7
I 7
	register int vl, vr, eqrel;
E 7

D 7
	vl = band();
	while (skipws() == '^') {
		vr = band();
		vl ^= vr;
	}
E 7
I 7
	vl = shift();
	while ((eqrel = geteqrel()) != -1) {
		vr = shift();
E 7

D 7
	ungetch();
	return vl;
E 4
}
E 7
I 7
		switch (eqrel) {
E 7
D 4
 
E 4
I 4

E 4
D 7
/*
 * band : eql { '&' eql }
D 4
 *
E 4
 */
I 4
static int
E 4
band()
{
D 4
        register int vl, vr, c;
 
        vl = eql();
        while ((c = skipws()) == '&' && getch() != '&') {
                ungetch();
                vr = eql();
                vl &= vr;
        }
 
        if (c == '&')
                ungetch();
        ungetch();
        return(vl);
E 4
I 4
	register int vl, vr, c;

	vl = eql();
	while ((c = skipws()) == '&' && getch() != '&') {
		ungetch();
		vr = eql();
		vl &= vr;
	}

	if (c == '&')
		ungetch();
	ungetch();
	return vl;
E 4
}
D 4
 
E 4
I 4

E 4
/*
 * eql : relat { eqrel relat }
D 4
 *
E 4
 */
I 4
static int
E 4
eql()
{
D 4
        register int vl, vr, rel;
 
        vl = relat();
        while ((rel = geteql()) != -1) {
                vr = relat();
 
                switch (rel) {
 
                case EQL:
                        vl = (vl == vr);
                        break;
                case NEQ:
                        vl = (vl != vr);
                        break;
                }
        }
        return(vl);
}
 
E 4
I 4
	register int vl, vr, rel;

	vl = relat();
	while ((rel = geteql()) != -1) {
		vr = relat();

		switch (rel) {

E 7
		case EQL:
			vl = (vl == vr);
			break;
		case NEQ:
			vl = (vl != vr);
			break;
D 7
		}
	}
	return vl;
}
E 7

E 4
D 7
/*
 * relat : shift { rel shift }
D 4
 *
E 4
 */
I 4
static int
E 4
relat()
{
D 4
        register int vl, vr, rel;
 
        vl = shift();
        while ((rel = getrel()) != -1) {
 
                vr = shift();
                switch (rel) {
 
                case LEQ:
                        vl = (vl <= vr);
                        break;
                case LSS:
                        vl = (vl < vr);
                        break;
                case GTR:
                        vl = (vl > vr);
                        break;
                case GEQ:
                        vl = (vl >= vr);
                        break;
                }
        }
        return(vl);
}
 
E 4
I 4
	register int vl, vr, rel;

	vl = shift();
	while ((rel = getrel()) != -1) {

		vr = shift();
		switch (rel) {

E 7
		case LEQ:
			vl = (vl <= vr);
			break;
		case LSS:
			vl = (vl < vr);
			break;
		case GTR:
			vl = (vl > vr);
			break;
		case GEQ:
			vl = (vl >= vr);
			break;
		}
	}
	return vl;
}

E 4
/*
 * shift : primary { shop primary }
D 4
 *
E 4
 */
I 4
static int
E 4
shift()
{
D 4
        register int vl, vr, c;
 
        vl = primary();
        while (((c = skipws()) == '<' || c == '>') && c == getch()) {
                vr = primary();
 
                if (c == '<')
                        vl <<= vr;
                else
                        vl >>= vr;
        }
 
        if (c == '<' || c == '>')
                ungetch();
        ungetch();
        return(vl);
E 4
I 4
	register int vl, vr, c;

	vl = primary();
D 7
	while (((c = skipws()) == '<' || c == '>') && c == getch()) {
E 7
I 7
	while (((c = skipws()) == '<' || c == '>') && getch() == c) {
E 7
		vr = primary();

		if (c == '<')
			vl <<= vr;
		else
			vl >>= vr;
	}

	if (c == '<' || c == '>')
		ungetch();
	ungetch();
	return vl;
E 4
}
D 4
 
E 4
I 4

E 4
/*
 * primary : term { addop term }
D 4
 *
E 4
 */
I 4
static int
E 4
primary()
{
D 4
        register int c, vl, vr;
 
        vl = term();
        while ((c = skipws()) == '+' || c == '-') {
                vr = term();
                if (c == '+')
                        vl += vr;
                else
                        vl -= vr;
        }
 
        ungetch();
        return(vl);
E 4
I 4
	register int c, vl, vr;

	vl = term();
	while ((c = skipws()) == '+' || c == '-') {
		vr = term();
I 7

E 7
		if (c == '+')
			vl += vr;
		else
			vl -= vr;
	}

	ungetch();
	return vl;
E 4
}
D 4
 
E 4
I 4

E 4
/*
D 7
 * <term> := <unary> { <mulop> <unary> }
E 7
I 7
 * <term> := <exp> { <mulop> <exp> }
E 7
D 4
 *
E 4
 */
I 4
static int
E 4
term()
{
D 4
        register int c, vl, vr;
 
        vl = unary();
        while ((c = skipws()) == '*' || c == '/' || c == '%') {
                vr = unary();
 
                switch (c) {
                case '*':
                        vl *= vr;
                        break;
                case '/':
                        vl /= vr;
                        break;
                case '%':
                        vl %= vr;
                        break;
                }
        }
        ungetch();
        return(vl);
}
 
E 4
I 4
	register int c, vl, vr;

D 7
	vl = unary();
E 7
I 7
	vl = exp();
E 7
	while ((c = skipws()) == '*' || c == '/' || c == '%') {
D 7
		vr = unary();
E 7
I 7
		vr = exp();
E 7

		switch (c) {
		case '*':
			vl *= vr;
			break;
		case '/':
			vl /= vr;
			break;
		case '%':
			vl %= vr;
			break;
		}
	}
	ungetch();
	return vl;
}

E 4
/*
I 7
 * <term> := <unary> { <expop> <unary> }
 */
static int
exp()
{
	register c, vl, vr, n;

	vl = unary();
	switch (c = skipws()) {

	case '*':
		if (getch() != '*') {
			ungetch();
			break;
		}

	case '^':
		vr = exp();
		n = 1;
		while (vr-- > 0)
			n *= vl;
		return n;
	}

	ungetch();
	return vl;
}

/*
E 7
 * unary : factor | unop unary
D 4
 *
E 4
 */
I 4
static int
E 4
unary()
{
D 4
        register int val, c;
 
        if ((c = skipws()) == '!' || c == '~' || c == '-') {
                val = unary();
 
                switch (c) {
                case '!':
                        return(! val);
                case '~':
                        return(~ val);
                case '-':
                        return(- val);
                }
        }
 
        ungetch();
        return(factor());
}
 
E 4
I 4
	register int val, c;

D 7
	if ((c = skipws()) == '!' || c == '~' || c == '-') {
E 7
I 7
	if ((c = skipws()) == '+' || c == '-' || c == '~') {
E 7
		val = unary();

		switch (c) {
D 7
		case '!':
			return !val;
		case '~':
			return ~val;
E 7
I 7
		case '+':
			return val;
E 7
		case '-':
			return -val;
I 7
		case '~':
			return ~val;
E 7
		}
	}

	ungetch();
	return factor();
}

E 4
/*
 * factor : constant | '(' query ')'
D 4
 *
E 4
 */
I 4
static int
E 4
factor()
{
D 4
        register int val;
 
        if (skipws() == '(') {
                val = query();
                if (skipws() != ')')
                        experr("Bad factor");
                return(val);
        }
 
        ungetch();
        return(constant());
E 4
I 4
	register int val;

	if (skipws() == '(') {
		val = query();
		if (skipws() != ')')
			experr("bad factor");
		return val;
	}

	ungetch();
	return constant();
E 4
}
D 4
 
E 4
I 4

E 4
/*
 * constant: num | 'char'
D 4
 *
E 4
I 4
 * Note: constant() handles multi-byte constants
E 4
 */
I 4
static int
E 4
constant()
{
D 4
        /*
         * Note: constant() handles multi-byte constants
         */
 
        register int    i;
        register int    value;
        register char   c;
        int             v[sizeof (int)];
 
        if (skipws() != '\'') {
                ungetch();
                return(num());
        }
        for (i = 0; i < sizeof(int); i++) {
                if ((c = getch()) == '\'') {
                        ungetch();
                        break;
                }
                if (c == '\\') {
                        switch (c = getch()) {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                                ungetch();
                                c = num();
                                break;
                        case 'n':
                                c = 012;
                                break;
                        case 'r':
                                c = 015;
                                break;
                        case 't':
                                c = 011;
                                break;
                        case 'b':
                                c = 010;
                                break;
                        case 'f':
                                c = 014;
                                break;
                        }
                }
                v[i] = c;
        }
        if (i == 0 || getch() != '\'')
                experr("Illegal character constant");
        for (value = 0; --i >= 0;) {
                value <<= 8;
                value += v[i];
        }
        return(value);
}
 
E 4
I 4
	register int i;
	register int value;
	register char c;
	int v[sizeof(int)];

	if (skipws() != '\'') {
		ungetch();
		return num();
	}
	for (i = 0; i < sizeof(int); i++) {
		if ((c = getch()) == '\'') {
			ungetch();
			break;
		}
		if (c == '\\') {
			switch (c = getch()) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
				ungetch();
				c = num();
				break;
			case 'n':
				c = 012;
				break;
			case 'r':
				c = 015;
				break;
			case 't':
				c = 011;
				break;
			case 'b':
				c = 010;
				break;
			case 'f':
				c = 014;
				break;
			}
		}
		v[i] = c;
	}
	if (i == 0 || getch() != '\'')
		experr("illegal character constant");
	for (value = 0; --i >= 0;) {
		value <<= 8;
		value += v[i];
	}
	return value;
}

E 4
/*
 * num : digit | num digit
D 4
 *
E 4
 */
I 4
static int
E 4
num()
{
D 4
        register int rval, c, base;
        int ndig;
 
        base = ((c = skipws()) == '0') ? OCTAL : DECIMAL;
        rval = 0;
        ndig = 0;
        while (c >= '0' && c <= (base == OCTAL ? '7' : '9')) {
                rval *= base;
                rval += (c - '0');
                c = getch();
                ndig++;
        }
        ungetch();
        if (ndig)
                return(rval);
        experr("Bad constant");
E 4
I 4
	register int rval, c, base;
	int ndig;

	base = ((c = skipws()) == '0') ? OCTAL : DECIMAL;
	rval = 0;
	ndig = 0;
	while (c >= '0' && c <= (base == OCTAL ? '7' : '9')) {
		rval *= base;
		rval += (c - '0');
		c = getch();
		ndig++;
	}
	ungetch();
	
	if (ndig == 0)
		experr("bad constant");
	
	return rval;

E 4
}
D 4
 
E 4
I 4

E 4
/*
D 7
 * eqlrel : '=' | '==' | '!='
E 7
I 7
 * eqrel : '=' | '==' | '!=' | '<' | '>' | '<=' | '>='
E 7
D 4
 *
E 4
 */
I 4
static int
E 4
D 7
geteql()
E 7
I 7
geteqrel()
E 7
{
D 4
        register int c1, c2;
 
        c1 = skipws();
        c2 = getch();
 
        switch (c1) {
 
        case '=':
                if (c2 != '=')
                        ungetch();
                return(EQL);
 
        case '!':
                if (c2 == '=')
                        return(NEQ);
                ungetch();
                ungetch();
                return(-1);
 
        default:
                ungetch();
                ungetch();
                return(-1);
        }
E 4
I 4
	register int c1, c2;

	c1 = skipws();
	c2 = getch();

	switch (c1) {

	case '=':
		if (c2 != '=')
			ungetch();
		return EQL;

	case '!':
		if (c2 == '=')
			return NEQ;
		ungetch();
		ungetch();
		return -1;
D 7

	default:
		ungetch();
		ungetch();
		return -1;
	}
E 4
}
D 4
 
E 4
I 4

E 4
/*
 * rel : '<' | '>' | '<=' | '>='
D 4
 *
E 4
 */
I 4
static int
E 4
getrel()
{
D 4
        register int c1, c2;
 
        c1 = skipws();
        c2 = getch();
 
        switch (c1) {
 
        case '<':
                if (c2 == '=')
                        return(LEQ);
                ungetch();
                return(LSS);
 
        case '>':
                if (c2 == '=')
                        return(GEQ);
                ungetch();
                return(GTR);
 
        default:
                ungetch();
                ungetch();
                return(-1);
        }
E 4
I 4
	register int c1, c2;

	c1 = skipws();
	c2 = getch();

	switch (c1) {
E 7

	case '<':
		if (c2 == '=')
			return LEQ;
		ungetch();
		return LSS;

	case '>':
		if (c2 == '=')
			return GEQ;
		ungetch();
		return GTR;

	default:
		ungetch();
		ungetch();
		return -1;
	}
E 4
}
D 4
 
E 4
I 4

E 4
/*
 * Skip over any white space and return terminating char.
 */
I 4
static int
E 4
skipws()
{
D 4
        register char c;
 
        while ((c = getch()) <= ' ' && c > EOS)
                ;
        return(c);
E 4
I 4
	register char c;

	while ((c = getch()) <= ' ' && c > EOS)
		;
	return c;
E 4
}
D 4
 
E 4
I 4

E 4
/*
D 4
 * Error handler - resets environment to eval(), prints an error,
 * and returns FALSE.
E 4
I 4
 * resets environment to eval(), prints an error 
 * and forces eval to return FALSE.
E 4
 */
I 4
static void
E 4
experr(msg)
char *msg;
{
D 4
        printf("mp: %s\n",msg);
        longjmp(expjump, -1);          /* Force eval() to return FALSE */
E 4
I 4
	printf("m4: %s in expr.\n", msg);
	longjmp(expjump, -1);
E 4
}
E 1
