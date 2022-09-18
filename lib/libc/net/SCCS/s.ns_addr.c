h40606
s 00002/00002/00199
d D 8.1 93/06/07 11:30:02 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00197
d D 6.9 93/06/07 11:29:49 bostic 10 8
c index -> strcghr
e
s 00002/00002/00199
d R 8.1 93/06/04 12:50:57 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00199
d D 6.8 91/07/01 19:24:35 sklower 8 7
c misplaced parens fucks up parameter to strncpy
e
s 00019/00013/00182
d D 6.7 91/02/24 12:40:17 bostic 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00003/00003/00192
d D 6.6 90/06/06 20:44:43 bostic 6 5
c redo contrib notice
e
s 00001/00011/00194
d D 6.5 90/06/01 14:16:06 bostic 5 4
c new copyright notice
e
s 00016/00005/00189
d D 6.4 88/08/12 17:18:03 bostic 4 3
c add Berkeley specific copyright notices
e
s 00011/00012/00183
d D 6.3 87/09/30 11:53:25 bostic 3 2
c long/int problems, linted; bug report 4.3BSD/lib/34
e
s 00002/00002/00193
d D 6.2 86/03/09 20:40:11 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00195/00000/00000
d D 6.1 86/01/29 14:45:05 sklower 1 0
c This routine converts ascii to NS addresses
e
u
U
t
T
I 1
/*
D 11
 * Copyright (c) 1986 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
E 4
 *
D 4
 * Includes material written at Cornell University, by J. Q. Johnson.
 * Used by permission.
E 4
I 4
D 5
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
D 6
 * %sccs.include.redist.c%
E 5
 *
E 6
 * This code is derived from software contributed to Berkeley by
D 6
 * J.Q. Johnson at Cornell University.
E 6
I 6
 * J.Q. Johnson.
 *
 * %sccs.include.redist.c%
E 6
E 4
 */

D 2
#ifndef lint
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 2

D 7
#include <sys/types.h>
E 7
I 7
#include <sys/param.h>
E 7
#include <netns/ns.h>
I 7
#include <stdio.h>
#include <string.h>
E 7

static struct ns_addr addr, zero_addr;

I 7
static void Field(), cvtbase();

E 7
struct ns_addr 
ns_addr(name)
D 7
	char *name;
E 7
I 7
	const char *name;
E 7
{
D 3
	u_long net;
	u_short socket;
E 3
D 7
	char separator = '.';
E 7
I 7
	char separator;
E 7
	char *hostname, *socketname, *cp;
	char buf[50];
D 7
	extern char *index();
E 7

D 7
	addr = zero_addr;
D 3
	strncpy(buf, name, 49);
E 3
I 3
	(void)strncpy(buf, name, 49);
E 7
I 7
D 8
	(void)strncpy(buf, name, sizeof(buf - 1));
	buf[sizeof(buf - 1)] = '\0';
E 8
I 8
	(void)strncpy(buf, name, sizeof(buf) - 1);
	buf[sizeof(buf) - 1] = '\0';
E 8
E 7
E 3

	/*
	 * First, figure out what he intends as a field separtor.
	 * Despite the way this routine is written, the prefered
	 * form  2-272.AA001234H.01777, i.e. XDE standard.
	 * Great efforts are made to insure backward compatability.
	 */
D 10
	if (hostname = index(buf, '#'))
E 10
I 10
	if (hostname = strchr(buf, '#'))
E 10
		separator = '#';
	else {
D 10
		hostname = index(buf, '.');
		if ((cp = index(buf, ':')) &&
E 10
I 10
		hostname = strchr(buf, '.');
		if ((cp = strchr(buf, ':')) &&
E 10
D 7
		    ( (hostname && cp < hostname) || (hostname == 0))) {
E 7
I 7
		    ((hostname && cp < hostname) || (hostname == 0))) {
E 7
			hostname = cp;
			separator = ':';
D 7
		}
E 7
I 7
		} else
			separator = '.';
E 7
	}
	if (hostname)
		*hostname++ = 0;
I 7

	addr = zero_addr;
E 7
	Field(buf, addr.x_net.c_net, 4);
	if (hostname == 0)
		return (addr);  /* No separator means net only */

D 10
	socketname = index(hostname, separator);
E 10
I 10
	socketname = strchr(hostname, separator);
E 10
	if (socketname) {
		*socketname++ = 0;
D 3
		Field(socketname, &addr.x_port, 2);
E 3
I 3
		Field(socketname, (u_char *)&addr.x_port, 2);
E 3
	}

	Field(hostname, addr.x_host.c_host, 6);

	return (addr);
}

D 7
static
E 7
I 7
static void
E 7
Field(buf, out, len)
D 7
char *buf;
u_char *out;
int len;
E 7
I 7
	char *buf;
	u_char *out;
	int len;
E 7
{
	register char *bp = buf;
	int i, ibase, base16 = 0, base10 = 0, clen = 0;
	int hb[6], *hp;
	char *fmt;

	/*
	 * first try 2-273#2-852-151-014#socket
	 */
	if ((*buf != '-') &&
	    (1 < (i = sscanf(buf, "%d-%d-%d-%d-%d",
			&hb[0], &hb[1], &hb[2], &hb[3], &hb[4])))) {
D 3
		cvtbase(1000, 256, hb, i, out, len);
E 3
I 3
		cvtbase(1000L, 256, hb, i, out, len);
E 3
		return;
	}
	/*
	 * try form 8E1#0.0.AA.0.5E.E6#socket
	 */
	if (1 < (i = sscanf(buf,"%x.%x.%x.%x.%x.%x",
			&hb[0], &hb[1], &hb[2], &hb[3], &hb[4], &hb[5]))) {
D 3
		cvtbase(256, 256, hb, i, out, len);
E 3
I 3
		cvtbase(256L, 256, hb, i, out, len);
E 3
		return;
	}
	/*
	 * try form 8E1#0:0:AA:0:5E:E6#socket
	 */
	if (1 < (i = sscanf(buf,"%x:%x:%x:%x:%x:%x",
			&hb[0], &hb[1], &hb[2], &hb[3], &hb[4], &hb[5]))) {
D 3
		cvtbase(256, 256, hb, i, out, len);
E 3
I 3
		cvtbase(256L, 256, hb, i, out, len);
E 3
		return;
	}
	/*
	 * This is REALLY stretching it but there was a
	 * comma notation separting shorts -- definitely non standard
	 */
	if (1 < (i = sscanf(buf,"%x,%x,%x",
			&hb[0], &hb[1], &hb[2]))) {
		hb[0] = htons(hb[0]); hb[1] = htons(hb[1]);
		hb[2] = htons(hb[2]);
D 3
		cvtbase(65536, 256, hb, i, out, len);
E 3
I 3
		cvtbase(65536L, 256, hb, i, out, len);
E 3
		return;
	}

	/* Need to decide if base 10, 16 or 8 */
	while (*bp) switch (*bp++) {

	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '-':
		break;

	case '8': case '9':
		base10 = 1;
		break;

	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		base16 = 1;
		break;
	
	case 'x': case 'X':
		*--bp = '0';
		base16 = 1;
		break;

	case 'h': case 'H':
		base16 = 1;
		/* fall into */

	default:
		*--bp = 0; /* Ends Loop */
	}
	if (base16) {
		fmt = "%3x";
		ibase = 4096;
	} else if (base10 == 0 && *buf == '0') {
		fmt = "%3o";
		ibase = 512;
	} else {
		fmt = "%3d";
		ibase = 1000;
	}

	for (bp = buf; *bp++; ) clen++;
	if (clen == 0) clen++;
	if (clen > 18) clen = 18;
	i = ((clen - 1) / 3) + 1;
	bp = clen + buf - 3;
	hp = hb + i - 1;

	while (hp > hb) {
D 3
		sscanf(bp, fmt, hp);
E 3
I 3
		(void)sscanf(bp, fmt, hp);
E 3
		bp[0] = 0;
		hp--;
		bp -= 3;
	}
D 3
	sscanf(buf, fmt, hp);
	cvtbase(ibase, 256, hb, i, out, len);
E 3
I 3
	(void)sscanf(buf, fmt, hp);
	cvtbase((long)ibase, 256, hb, i, out, len);
E 3
}

D 7
static
E 7
I 7
static void
E 7
cvtbase(oldbase,newbase,input,inlen,result,reslen)
D 3
	int oldbase, newbase;
E 3
I 3
	long oldbase;
	int newbase;
E 3
	int input[];
	int inlen;
	unsigned char result[];
	int reslen;
{
	int d, e;
	long sum;

	e = 1;
	while (e > 0 && reslen > 0) {
		d = 0; e = 0; sum = 0;
		/* long division: input=input/newbase */
		while (d < inlen) {
			sum = sum*oldbase + (long) input[d];
			e += (sum > 0);
			input[d++] = sum / newbase;
			sum %= newbase;
		}
		result[--reslen] = sum;	/* accumulate remainder */
	}
	for (d=0; d < reslen; d++)
		result[d] = 0;
}
E 1
