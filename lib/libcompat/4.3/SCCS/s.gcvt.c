h04311
s 00002/00002/00071
d D 8.1 93/06/04 16:24:58 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00065
d D 5.3 91/04/20 14:12:51 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00064
d D 5.2 86/03/09 19:46:51 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00062
d D 5.1 85/06/05 12:17:18 mckusick 2 1
c Add copyright
e
s 00063/00000/00000
d D 4.1 80/12/21 16:50:29 wnj 1 0
c date and time created 80/12/21 16:50:29 by wnj
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3

E 2
/*
 * gcvt  - Floating output conversion to
 * minimal length string
 */

char	*ecvt();

char *
gcvt(number, ndigit, buf)
double number;
char *buf;
{
	int sign, decpt;
	register char *p1, *p2;
	register i;

	p1 = ecvt(number, ndigit, &decpt, &sign);
	p2 = buf;
	if (sign)
		*p2++ = '-';
	for (i=ndigit-1; i>0 && p1[i]=='0'; i--)
		ndigit--;
	if (decpt >= 0 && decpt-ndigit > 4
	 || decpt < 0 && decpt < -3) { /* use E-style */
		decpt--;
		*p2++ = *p1++;
		*p2++ = '.';
		for (i=1; i<ndigit; i++)
			*p2++ = *p1++;
		*p2++ = 'e';
		if (decpt<0) {
			decpt = -decpt;
			*p2++ = '-';
		} else
			*p2++ = '+';
		*p2++ = decpt/10 + '0';
		*p2++ = decpt%10 + '0';
	} else {
		if (decpt<=0) {
			if (*p1!='0')
				*p2++ = '.';
			while (decpt<0) {
				decpt++;
				*p2++ = '0';
			}
		}
		for (i=1; i<=ndigit; i++) {
			*p2++ = *p1++;
			if (i==decpt)
				*p2++ = '.';
		}
		if (ndigit<decpt) {
			while (ndigit++<decpt)
				*p2++ = '0';
			*p2++ = '.';
		}
	}
	if (p2[-1]=='.')
		p2--;
	*p2 = '\0';
	return(buf);
}
E 1
