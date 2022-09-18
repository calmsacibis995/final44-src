h37004
s 00002/00002/00154
d D 8.1 93/06/04 16:24:55 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00155
d D 5.4 92/07/03 10:14:11 torek 5 4
c cvt() is static; say so up front
e
s 00008/00001/00148
d D 5.3 91/04/20 14:12:50 bostic 4 3
c new copyright; att/bsd/shared
e
s 00041/00000/00108
d D 5.2 90/06/24 12:29:35 bostic 3 2
c HP300 support from Mike Hibler
e
s 00004/00001/00104
d D 5.1 86/03/15 16:40:35 mckusick 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00105/00000/00000
d D 4.1 80/12/21 16:39:36 wnj 1 0
c date and time created 80/12/21 16:39:36 by wnj
e
u
U
t
T
I 4
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4

I 3
#if defined(hp300) && !defined(IEEE)
#define	IEEE	1
#endif

E 3
E 2
/*
 *	ecvt converts to decimal
 *	the number of digits is specified by ndigit
 *	decpt is set to the position of the decimal point
 *	sign is set to 0 for positive, 1 for negative
 */

D 5
char	*cvt();
E 5
I 5
static char *cvt();
E 5

I 3
#ifdef IEEE
#include <signal.h>
#define	NDIG	512
#else
E 3
#define	NDIG	80
I 3
#endif

E 3
char*
ecvt(arg, ndigits, decpt, sign)
double arg;
int ndigits, *decpt, *sign;
{
	return(cvt(arg, ndigits, decpt, sign, 1));
}

char*
fcvt(arg, ndigits, decpt, sign)
double arg;
int ndigits, *decpt, *sign;
{
	return(cvt(arg, ndigits, decpt, sign, 0));
}

static char*
cvt(arg, ndigits, decpt, sign, eflag)
double arg;
int ndigits, *decpt, *sign;
{
	register int r2;
	double fi, fj;
	register char *p, *p1;
	static char buf[NDIG];
	double modf();

I 3
#ifdef IEEE
	/* XXX */
	if (isspecial(arg, buf))
		return(buf);
#endif
E 3
	if (ndigits<0)
		ndigits = 0;
	if (ndigits>=NDIG-1)
		ndigits = NDIG-2;
	r2 = 0;
	*sign = 0;
	p = &buf[0];
	if (arg<0) {
		*sign = 1;
		arg = -arg;
	}
	arg = modf(arg, &fi);
	p1 = &buf[NDIG];
	/*
	 * Do integer part
	 */
	if (fi != 0) {
		p1 = &buf[NDIG];
		while (fi != 0) {
			fj = modf(fi/10, &fi);
			*--p1 = (int)((fj+.03)*10) + '0';
			r2++;
		}
		while (p1 < &buf[NDIG])
			*p++ = *p1++;
	} else if (arg > 0) {
		while ((fj = arg*10) < 1) {
			arg = fj;
			r2--;
		}
	}
	p1 = &buf[ndigits];
	if (eflag==0)
		p1 += r2;
	*decpt = r2;
	if (p1 < &buf[0]) {
		buf[0] = '\0';
		return(buf);
	}
	while (p<=p1 && p<&buf[NDIG]) {
		arg *= 10;
		arg = modf(arg, &fj);
		*p++ = (int)fj + '0';
	}
	if (p1 >= &buf[NDIG]) {
		buf[NDIG-1] = '\0';
		return(buf);
	}
	p = p1;
	*p1 += 5;
	while (*p1 > '9') {
		*p1 = '0';
		if (p1>buf)
			++*--p1;
		else {
			*p1 = '1';
			(*decpt)++;
			if (eflag==0) {
				if (p>buf)
					*p = '0';
				p++;
			}
		}
	}
	*p = '\0';
	return(buf);
}
I 3

#ifdef IEEE
struct IEEEdp {
	unsigned sign:1,
		 exp:11,
		 manh:20,
		 manl:32;
};

isspecial(f, bp)
	double f;
	char *bp;
{
	register struct IEEEdp *ip = (struct IEEEdp *) &f;

	if (ip->exp != 0x7ff)
		return(0);
	if (ip->manh || ip->manl)
		strcpy(bp, "NaN");
	else if (ip->sign)
		strcpy(bp, "-Infinity");
	else
		strcpy(bp, "Infinity");
	return(1);
}
#endif
E 3
E 1
