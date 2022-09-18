h36872
s 00002/00002/00124
d D 8.1 93/06/17 19:46:15 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00122
d D 5.13 93/06/17 19:46:07 bostic 20 17
c lint
e
s 00002/00002/00122
d R 8.1 93/06/07 11:28:08 bostic 19 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00122
d R 8.1 93/06/04 12:50:21 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00123
d D 5.12 93/04/12 18:13:16 andrew 17 16
c inet_aton returns a boolean value, don't need to return long.
e
s 00002/00002/00122
d D 5.11 91/12/09 16:26:48 bostic 16 15
c welcome to the wonderful world of ANSI!
e
s 00001/00000/00123
d D 5.10 91/02/24 13:14:35 bostic 15 14
c need ctype.h, shouldn't have deleted it
e
s 00003/00003/00120
d D 5.9 91/02/24 12:40:09 bostic 14 13
c Add include files to get prototype declarations, and fix bugs found.
e
s 00073/00055/00050
d D 5.8 90/06/23 15:36:11 karels 13 12
c replace inet_addr with inet_aton, which has separate error and value
c returns
e
s 00001/00011/00104
d D 5.7 90/06/01 14:14:55 bostic 12 11
c new copyright notice
e
s 00010/00005/00105
d D 5.6 88/06/27 18:28:07 bostic 11 10
c install approved copyright notice
e
s 00009/00003/00101
d D 5.5 88/03/07 21:07:35 bostic 10 9
c add Berkeley specific headers
e
s 00003/00003/00101
d D 5.4 87/10/01 14:31:59 bostic 9 8
c INADDR_NONE, not -1; bug report 4.3BSD/lib/22
e
s 00006/00004/00098
d D 5.3 87/06/03 10:45:30 bostic 8 7
c bug report 4.3BSD/lib/65
e
s 00002/00002/00100
d D 5.2 86/03/09 20:10:47 donn 7 6
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00093
d D 5.1 85/05/30 11:14:40 dist 6 5
c Add copyright
e
s 00001/00001/00093
d D 4.5 82/11/14 13:57:09 sam 5 4
c merge of 4.1b and 4.1c
e
s 00001/00001/00093
d D 4.4 82/10/07 16:59:40 sam 4 3
c too much trouble to type it properly
e
s 00040/00019/00054
d D 4.3 82/10/07 16:13:20 sam 3 2
c rewrite a bit to be more lucid
e
s 00004/00000/00069
d D 4.2 82/10/05 22:19:48 sam 2 1
c rename library routines so as not conflict with gethostname
e
s 00069/00000/00000
d D 4.1 82/10/05 17:14:04 sam 1 0
c date and time created 82/10/05 17:14:04 by sam
e
u
U
t
T
I 1
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
/*
D 13
 * Copyright (c) 1983 Regents of the University of California.
E 13
I 13
D 21
 * Copyright (c) 1983, 1990 Regents of the University of California.
E 13
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1983, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
E 10
 */

D 7
#ifndef lint
E 7
I 7
#if defined(LIBC_SCCS) && !defined(lint)
E 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
D 10
#endif LIBC_SCCS and not lint
E 10
I 10
#endif /* LIBC_SCCS and not lint */
E 10
E 7
E 6
I 2

D 14
#include <sys/types.h>
#include <ctype.h>
E 14
I 14
#include <sys/param.h>
E 14
I 3
D 5
#include <net/in.h>
E 5
I 5
#include <netinet/in.h>
I 14
#include <arpa/inet.h>
I 15
#include <ctype.h>
E 15
E 14
E 5
E 3

E 2
/*
D 13
 * Internet address interpretation routine.
 * All the network library routines call this
 * routine to interpret entries in the data bases
 * which are expected to be an address.
E 13
I 13
 * Ascii internet address interpretation routine.
E 13
I 3
 * The value returned is in network order.
E 3
 */
D 3
u_long
E 3
I 3
D 4
struct in_addr
E 4
I 4
u_long
E 4
E 3
inet_addr(cp)
D 14
	register char *cp;
E 14
I 14
	register const char *cp;
E 14
{
I 13
	struct in_addr val;

	if (inet_aton(cp, &val))
		return (val.s_addr);
	return (INADDR_NONE);
}

/* 
 * Check whether "cp" is a valid ascii representation
 * of an Internet address and convert to a binary address.
 * Returns 1 if the address is valid, 0 if not.
 * This replaces inet_addr, the return value from which
 * cannot distinguish between failure and a local broadcast address.
 */
D 16

E 16
I 16
D 17
unsigned long
E 17
I 17
int
E 17
E 16
inet_aton(cp, addr)
D 16
	register char *cp;
E 16
I 16
	register const char *cp;
E 16
	struct in_addr *addr;
{
E 13
D 3
	register unsigned long val, base, n;
E 3
I 3
D 20
	register u_long val, base, n;
E 20
I 20
	register u_long val;
	register int base, n;
E 20
E 3
	register char c;
D 3
	unsigned long parts[4], *pp = parts;
E 3
I 3
D 20
	u_long parts[4], *pp = parts;
E 20
I 20
	u_int parts[4];
	register u_int *pp = parts;
E 20
E 3

D 13
again:
I 3
	/*
	 * Collect number up to ``.''.
	 * Values are specified as for C:
	 * 0x=hex, 0=octal, other=decimal.
	 */
E 3
	val = 0; base = 10;
D 8
	if (*cp == '0')
		base = 8, cp++;
	if (*cp == 'x' || *cp == 'X')
		base = 16, cp++;
E 8
I 8
	if (*cp == '0') {
		if (*++cp == 'x' || *cp == 'X')
			base = 16, cp++;
		else
			base = 8;
	}
E 8
	while (c = *cp) {
		if (isdigit(c)) {
			val = (val * base) + (c - '0');
			cp++;
			continue;
E 13
I 13
	for (;;) {
		/*
		 * Collect number up to ``.''.
		 * Values are specified as for C:
		 * 0x=hex, 0=octal, other=decimal.
		 */
		val = 0; base = 10;
		if (*cp == '0') {
			if (*++cp == 'x' || *cp == 'X')
				base = 16, cp++;
			else
				base = 8;
E 13
		}
D 13
		if (base == 16 && isxdigit(c)) {
			val = (val << 4) + (c + 10 - (islower(c) ? 'a' : 'A'));
			cp++;
			continue;
E 13
I 13
		while ((c = *cp) != '\0') {
			if (isascii(c) && isdigit(c)) {
				val = (val * base) + (c - '0');
				cp++;
				continue;
			}
			if (base == 16 && isascii(c) && isxdigit(c)) {
				val = (val << 4) + 
					(c + 10 - (islower(c) ? 'a' : 'A'));
				cp++;
				continue;
			}
			break;
E 13
		}
D 13
		break;
E 13
I 13
		if (*cp == '.') {
			/*
			 * Internet format:
			 *	a.b.c.d
			 *	a.b.c	(with c treated as 16-bits)
			 *	a.b	(with b treated as 24 bits)
			 */
			if (pp >= parts + 3 || val > 0xff)
				return (0);
			*pp++ = val, cp++;
		} else
			break;
E 13
	}
D 13
	if (*cp == '.') {
		/*
		 * Internet format:
		 *	a.b.c.d
		 *	a.b.c	(with c treated as 16-bits)
		 *	a.b	(with b treated as 24 bits)
		 */
		if (pp >= parts + 4)
D 9
			return (-1);
E 9
I 9
			return (INADDR_NONE);
E 9
		*pp++ = val, cp++;
		goto again;
	}
E 13
I 3
	/*
	 * Check for trailing characters.
	 */
E 3
D 13
	if (*cp && !isspace(*cp))
D 9
		return (-1);
E 9
I 9
		return (INADDR_NONE);
E 9
I 3
	*pp++ = val;
E 13
I 13
	if (*cp && (!isascii(*cp) || !isspace(*cp)))
		return (0);
E 13
	/*
	 * Concoct the address according to
	 * the number of parts specified.
	 */
E 3
D 13
	n = pp - parts;
E 13
I 13
	n = pp - parts + 1;
E 13
D 3
	if (n > 0) {
		if (n > 4)
			return (-1);
		*pp++ = val; n++;
E 3
I 3
	switch (n) {

	case 1:				/* a -- 32 bits */
E 3
D 13
		val = parts[0];
E 13
D 3
		if (n > 1)
			val <<= 24;
		if (n > 2)
			val |= (parts[1] & 0xff) << 16;
		if (n > 3)
			val |= (parts[2] & 0xff) << 8;
		if (n > 1)
			val |= parts[n - 1];
#if vax || pdp11
		val = htonl(val);
#endif
E 3
I 3
		break;

	case 2:				/* a.b -- 8.24 bits */
D 13
		val = (parts[0] << 24) | (parts[1] & 0xffffff);
E 13
I 13
		if (val > 0xffffff)
			return (0);
		val |= parts[0] << 24;
E 13
		break;

	case 3:				/* a.b.c -- 8.8.16 bits */
D 13
		val = (parts[0] << 24) | ((parts[1] & 0xff) << 16) |
			(parts[2] & 0xffff);
E 13
I 13
		if (val > 0xffff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16);
E 13
		break;

	case 4:				/* a.b.c.d -- 8.8.8.8 bits */
D 13
		val = (parts[0] << 24) | ((parts[1] & 0xff) << 16) |
		      ((parts[2] & 0xff) << 8) | (parts[3] & 0xff);
E 13
I 13
		if (val > 0xff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
E 13
		break;
D 13

	default:
D 9
		return (-1);
E 9
I 9
		return (INADDR_NONE);
E 13
E 9
E 3
	}
I 3
D 13
	val = htonl(val);
E 3
	return (val);
E 13
I 13
	if (addr)
		addr->s_addr = htonl(val);
	return (1);
E 13
}
D 3

E 3
E 1
