h23904
s 00079/00056/00044
d D 5.2 91/04/12 13:57:02 donn 2 1
c Make this i386-compatible; massive clean-up.
e
s 00100/00000/00000
d D 5.1 90/05/12 16:16:07 bostic 1 0
c date and time created 90/05/12 16:16:07 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
/*
 * simple atof() for IEEE 754 architectures
 */

#include <machine/endian.h>
#include <stdlib.h>
#include <math.h>
E 2
#include <ctype.h>

D 2
double _twoemax =
#ifdef IEEE
	9007199254740992.;	/*2^53*/
#else
	72057594037927936.;	/*2^56*/
#endif
E 2
I 2
static double twoemax = 9007199254740992.;	/*2^53*/
E 2

D 2
#ifdef hp300
E 2
/* attempt to be as exact as possible */
D 2
struct {
	long d_high;
	long d_low;
} _exp5[] = {
E 2
I 2
static struct {
	long low_word;
	long high_word;
} exp5[] = {
#if	BYTE_ORDER == BIG_ENDIAN
E 2
	{ 0x40140000, 0x00000000 },	/* 5 */
	{ 0x40390000, 0x00000000 },	/* 25 */
	{ 0x40838800, 0x00000000 },	/* 625 */
	{ 0x4117d784, 0x00000000 },	/* 390625 */
	{ 0x4241c379, 0x37e08000 },	/* 152587890625 */
	{ 0x4493b8b5, 0xb5056e17 },	/* 2.3283064365387e+022 */
	{ 0x49384f03, 0xe93ff9f6 },	/* 5.42101086242753e+044 */
	{ 0x52827748, 0xf9301d33 },	/* 2.93873587705572e+089 */
	{ 0x65154fdd, 0x7f73bf3f }	/* 8.63616855509445e+178 */
D 2
};
#else
double	_exp5[]	= {
	5.,
	25.,
	625.,
	390625.,
	152587890625.,
	23283064365386962890625.,
#ifdef IEEE
	5.4210108624275231e+044,
	2.9387358770557196e+089,
	8.6361685550944492e+178,
E 2
I 2
#else	/* BYTE_ORDER == LITTLE_ENDIAN */
	{ 0x00000000, 0x40140000 },	/* 5 */
	{ 0x00000000, 0x40390000 },	/* 25 */
	{ 0x00000000, 0x40838800 },	/* 625 */
	{ 0x00000000, 0x4117d784 },	/* 390625 */
	{ 0x37e08000, 0x4241c379 },	/* 152587890625 */
	{ 0xb5056e17, 0x4493b8b5 },	/* 2.3283064365387e+022 */
	{ 0xe93ff9f6, 0x49384f03 },	/* 5.42101086242753e+044 */
	{ 0xf9301d33, 0x52827748 },	/* 2.93873587705572e+089 */
	{ 0x7f73bf3f, 0x65154fdd }	/* 8.63616855509445e+178 */
E 2
#endif
};
D 2
#endif
E 2

double
atof(p)
D 2
register char *p;
E 2
I 2
	register const char *p;
E 2
{
D 2
	extern double ldexp();
	register c, exp = 0, eexp = 0;
	double fl = 0, flexp = 1.0;
	int bexp, neg = 1, negexp = 1;
E 2
I 2
	register int c;
	register int exp = 0;
	register int eexp = 0;
	double fl = 0;
	double flexp = 1.0;
	int bexp;
	int neg = 1;
	int negexp = 1;
E 2

D 2
	while((c = *p++) == ' ');
	if (c == '-') neg = -1;	else if (c == '+'); else --p;
E 2
I 2
	while (isspace(*p))
		++p;
E 2

D 2
	while ((c = *p++), isdigit(c))
		if (fl < _twoemax) fl = 10*fl + (c-'0'); else exp++;
E 2
I 2
	if ((c = *p++) == '-')
		neg = -1;
	else if (c == '+')
		/* skip it */;
	else
		--p;

	while ((c = *p++) && isdigit(c))
		if (fl < twoemax)
			fl = 10 * fl + (c-'0');
		else
			++exp;

E 2
	if (c == '.')
D 2
	while ((c = *p++), isdigit(c))
		if (fl < _twoemax)
		{
			fl = 10*fl + (c-'0');
			exp--;
		}
	if ((c == 'E') || (c == 'e'))
	{
		if ((c= *p++) == '+'); else if (c=='-') negexp = -1; else --p;
		while ((c = *p++), isdigit(c)) eexp = 10*eexp + (c-'0');
		if (negexp < 0) eexp = -eexp; exp += eexp;
E 2
I 2
		while ((c = *p++) && isdigit(c))
			if (fl < twoemax) {
				fl = 10 * fl + (c-'0');
				--exp;
			}

	if (c == 'E' || c == 'e') {
		if ((c = *p++) == '-')
			negexp = -1;
		else if (c == '+')
			/* skip it */;
		else
			--p;
		while ((c = *p++) && isdigit(c))
			eexp = 10 * eexp + (c-'0');
		if (negexp < 0)
			eexp = -eexp;
		exp += eexp;
E 2
	}
I 2

E 2
	bexp = exp;
D 2
	if (exp < 0) exp = -exp;
E 2
I 2
	if (exp < 0)
		exp = -exp;
E 2

D 2
	for (c = 0; c < sizeof(_exp5)/sizeof(_exp5[0]); c++)
	{
#ifdef hp300
		if (exp & 01) flexp *= *(double *)&_exp5[c];
#else
		if (exp & 01) flexp *= _exp5[c];
#endif
		exp >>= 1; if (exp == 0) break;
E 2
I 2
	for (c = 0; exp && c < sizeof exp5 / sizeof exp5[0]; ++c) {
		if (exp & 1)
			flexp *= *(double *)&exp5[c];
		exp >>= 1;
E 2
	}

D 2
	if (bexp < 0) fl /= flexp; else fl *= flexp;
E 2
I 2
	if (bexp < 0)
		fl /= flexp;
	else
		fl *= flexp;

E 2
	fl = ldexp(fl, bexp);
D 2
	if (neg < 0) return(-fl); else return(fl);
E 2
I 2

	return neg < 0 ? -fl : fl;
E 2
}
E 1
