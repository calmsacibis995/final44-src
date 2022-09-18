h33648
s 00002/00002/00034
d D 8.1 93/06/04 12:50:27 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00034
d D 5.6 91/02/24 12:40:11 bostic 10 9
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00034
d D 5.5 90/06/01 14:15:14 bostic 9 8
c new copyright notice
e
s 00004/00002/00041
d D 5.4 88/11/17 15:20:55 sklower 8 7
c make it possible to input subnetted class D nets and pre-shifted
c class B subnets.
e
s 00010/00005/00033
d D 5.3 88/06/27 18:28:10 bostic 7 6
c install approved copyright notice
e
s 00009/00003/00029
d D 5.2 88/03/07 21:07:38 bostic 6 5
c add Berkeley specific headers
e
s 00009/00001/00023
d D 5.1 86/03/11 12:43:38 karels 5 4
c copyright and rev 5
e
s 00003/00003/00021
d D 4.4 85/06/02 19:04:40 karels 4 3
c good enough for now; mask off bits from host that overlap network
e
s 00004/00004/00020
d D 4.3 82/11/14 13:57:22 sam 3 2
c merge of 4.1b and 4.1c
e
s 00001/00001/00023
d D 4.2 82/10/07 18:28:10 sam 2 1
c names all wrong
e
s 00024/00000/00000
d D 4.1 82/10/07 16:40:02 sam 1 0
c date and time created 82/10/07 16:40:02 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 11
 * Copyright (c) 1983 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
E 6
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5

D 10
#include <sys/types.h>
E 10
I 10
#include <sys/param.h>
E 10
D 3
#include <net/in.h>
E 3
I 3
#include <netinet/in.h>
I 10
#include <arpa/inet.h>
E 10
E 3

/*
 * Formulate an Internet address from network + host.  Used in
 * building addresses stored in the ifnet structure.
 */
struct in_addr
D 2
if_makeaddr(net, host)
E 2
I 2
inet_makeaddr(net, host)
E 2
D 8
	int net, host;
E 8
I 8
	u_long net, host;
E 8
{
	u_long addr;

	if (net < 128)
D 3
		addr = (net << 24) | host;
E 3
I 3
D 4
		addr = (net << IN_CLASSA_NSHIFT) | host;
E 4
I 4
		addr = (net << IN_CLASSA_NSHIFT) | (host & IN_CLASSA_HOST);
E 4
E 3
	else if (net < 65536)
D 3
		addr = (net << 16) | host;
E 3
I 3
D 4
		addr = (net << IN_CLASSB_NSHIFT) | host;
E 4
I 4
		addr = (net << IN_CLASSB_NSHIFT) | (host & IN_CLASSB_HOST);
E 4
E 3
D 8
	else
E 8
I 8
	else if (net < 16777216L)
E 8
D 3
		addr = (net << 8) | host;
E 3
I 3
D 4
		addr = (net << IN_CLASSC_NSHIFT) | host;
E 4
I 4
		addr = (net << IN_CLASSC_NSHIFT) | (host & IN_CLASSC_HOST);
I 8
	else
		addr = net | host;
E 8
E 4
E 3
	addr = htonl(addr);
	return (*(struct in_addr *)&addr);
}
E 1
