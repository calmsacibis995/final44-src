/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	expr.c,v $
 * Revision 2.4  89/03/09  21:34:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:40:07  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)expr.c 1.1 86/02/03 SMI";
#endif
/*
 * adb - expression evaluation routines
 */

#include <sun3/kdb/adb.h>

char	isymbol[BUFSIZ];

#define NEEDEXPR	1
#define EXPECTRPAREN	2
/*
 * expr:
 *	term
 *	term dyadic expr
 *	lambda
 */
expr(flags)
	int flags;
{
	int rc, lhs;

	(void) rdc(); lp--; rc = term(flags);
	while (rc) {
		lhs = expv;
		switch (readchar()) {

		case '+':
			(void) term(flags|NEEDEXPR); expv += lhs; break;
		case '-':
			(void) term(flags|NEEDEXPR); expv = lhs - expv; break;
		case '#':
			(void) term(flags|NEEDEXPR); expv = round(lhs, expv);
			break;
		case '*':
			(void) term(flags|NEEDEXPR); expv *= lhs; break;
		case '%':
			(void) term(flags|NEEDEXPR); expv = lhs/expv; break;
		case '&':
			(void) term(flags|NEEDEXPR); expv &= lhs; break;
		case '|':
			(void) term(flags|NEEDEXPR); expv |= lhs; break;

		case ')':
			if ((flags&EXPECTRPAREN)==0)
				error("unexpected ')'");
			/* fall into ... */
		default:
			lp--;
			return (rc);
		}
	}
	return (rc);
}

/*
 * term:
 *	item
 *	monadic item
 *	(expr)
 *	lambda
 */
term(flags)
	int flags;
{

	switch (readchar()) {

	case '*':
		(void) term(flags|NEEDEXPR); expv = chkget(expv, DSP);
		return (1);
	case '%':
		(void) term(flags|NEEDEXPR); expv = chkget(expv, ISP);
		return (1);
	case '-':
		(void) term(flags|NEEDEXPR); expv = -expv; return (1);
	case '~':
		(void) term(flags|NEEDEXPR); expv = ~expv; return (1);
	case '#':
		(void) term(flags|NEEDEXPR); expv = !expv; return (1);
	case '(':
		(void) expr(EXPECTRPAREN);
		if (*lp!=')')
			synerror();
		else {
			lp++;
			return (1);
		}

	default:
		lp--;
		return (item(flags));
	}
}

/*
 * item:
 *	name
 *	name.local
 *	number
 *	.
 *	^
 *	<var
 *	<register
 *	'x
 *	\procedure
 *	"file"
 *	lambda
 */
item(flags)
	int flags;
{
	short base, d;
	char savc;
	int reg;
	struct nlist *s;

	(void) readchar();
	if (symchar(0)) {
		readsym(0);
		if (lastc == '.')
			return (qualified(isymbol));
		else {
			register struct nlist *s;
			expv = 0;
			lp--;
			if ((s=lookup(isymbol)) == 0) {
				if (symhex(isymbol)) {
					return (1);
				} else
					error("symbol not found");
			}
			expv = s->n_value;
			return (1);
		}
	}
	if (getnum())
		return (1);
	switch (lastc) {

	case '.':
		(void) readchar();
		if (symchar(0))
			return (qualified((char *)0));
		expv = dot;
		lp--;
		break;

	case '&':
		expv = ditto; break;
	case '+':
		expv = inkdot(dotinc); break;
	case '^':
		expv = inkdot(-dotinc); break;

	case '<':
		savc = rdc();
		reg = getreg(savc);
		if (reg >= 0) {
			expv = readreg(reg);
			break;
		}
		base = varchk(savc);
		if (base == -1)
			error("bad variable");
		expv = var[base];
		break;

	case '\'':
		d = sizeof (int); expv = 0;
		while (quotchar()) {
			if (--d < 0)
				synerror();
			if (d == 1)
				expv <<= 2*NBBY;
			expv |= ((d&1)?lastc:lastc<<NBBY);
		}
		break;

	default:
		if (flags)
			error("address expected");
		lp--;
		return (0);
	}
	return (1);
}

struct stackpos exppos;

qualified(name)
	char *name;
{
	error("don't know how to do locals");
}

/*
 * Take what we thought was a symbol, and try it as a hex number.
 * Return 1 for success (symbol WAS hex), zero for failure.
 * If successful, we set "expv" to the value scanned out.
 */
symhex(p)
	register char *p;
{
	register unsigned val = 0;

	if (radix != 16) return (0);	/* Only works for hex due to isxdigit */

	if (!isxdigit(*p)) return (0);	/* There must be one digit */

	do {
		val = (val<<4) + convdig(*p++);
	} while (isxdigit(*p));

	if (*p == '\0') {
		expv = val;
		return (1);
	} else
		return (0);
}


/* Scan out a number and convert it. */
getnum()
{
	int base, d, frpt;
	int hex = 0;
	float r;

	if (!isdigit(lastc)) {
		if (lastc != '#')
			return (0);
		hex = 1; 
		if (!isxdigit(readchar()))
			return (0);
	}
	expv = 0;
	base = (hex ? 16 : radix);
	while (base>10 ? isxdigit(lastc) : isdigit(lastc)) {
		expv = (base==16 ? expv<<4 : expv*base);
		if ((d = convdig(lastc)) >= base)
			synerror();
		expv += d;
		(void) readchar();
		if (expv == 0) {
			if (lastc=='x' || lastc=='X') {
				hex = 1; base = 16; (void) readchar();
				continue;
			}
			if (lastc=='t' || lastc=='T') {
				hex = 0; base = 10; (void) readchar();
				continue;
			}
			if (lastc=='o' || lastc=='O') {
				hex = 0; base = 8; (void) readchar();
			}
		}
	}
	if (lastc=='.' && (base==10 || expv==0) && !hex) {
		r = expv; frpt=0; base=10;
		while (isdigit(readchar())) {
			r *= base;
			frpt++;
			r += lastc - '0';
		}
		while (frpt--)
			r /= base;
		expv = *(int *)&r;
	}
	peekc = lastc;
	return (1);
}

readsym(filename)
	int filename;
{
	register char *p;

	p = isymbol;
	do {
		if (p < &isymbol[sizeof(isymbol)-1])
			*p++ = lastc;
	 	(void) readchar();
		if (filename && (lastc==0 || lastc=='\n'))
			error("missing '\"'");
	} while (filename ? (lastc != '"') : symchar(1));
	*p++ = 0;
}

convdig(c)
	char c;
{

	if (isdigit(c))
		return (c - '0');
	if (isxdigit(c)){
		if (islower(c))
			return (c - 'a' + 10);
		else
			return (c - 'A' + 10);
	}
	return (17);
}

symchar(dig)
	int dig;
{

	if (lastc=='\\') {
		(void) readchar();
		return (1);
	}
	return (isalpha(lastc) || lastc=='_' || dig && isdigit(lastc));
}

varchk(name)
	char name;
{

	if (isdigit(name))
		return (name - '0');
	if (isalpha(name))
		return ((name & 037) - 1 + 10);
	return (-1);
}

eqsym(s1, s2, c)
	register char *s1, *s2;
	char c;
{

	if (!strcmp(s1, s2))
		return (1);
	if (*s1 == c && !strcmp(s1+1, s2))
		return (1);
	return (0);
}

synerror()
{

	error("syntax error");
}
