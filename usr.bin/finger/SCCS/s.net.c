h59539
s 00002/00001/00121
d D 8.4 95/04/28 17:35:56 bostic 11 10
c You may have already done the same (does the Alpha have alignment
c constraints? I think it does...).  I also changed it to use the libc
c err, instead of its own, and fixed most of the `gcc -Wall' complaints.
c The important changes are to memcpy the pointers from db->get and db->seq.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00007/00117
d D 8.3 94/01/02 13:01:38 bostic 10 9
c This prevents you from specifying a raw ip address if the nameserver
c is hosed.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00002/00000/00122
d D 8.2 93/11/16 11:56:08 bostic 9 8
c The following quick patch to usr.bin/finger/net.c fixes finger so that
c it only prints a single newline when a <CR> (carriage return) is followed
c by another <CR>, which may happen if you finger a site beyond another site,
c i.e. finger user@site@some.other.site
c From: composer@Beyond.Dreams.ORG (Jeff Kellem)
e
s 00002/00002/00120
d D 8.1 93/06/06 14:39:19 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00120
d D 5.7 91/07/27 17:59:18 bostic 7 6
c finger really didn't need its own hashing scheme
e
s 00008/00002/00112
d D 5.6 91/07/27 15:58:25 bostic 6 5
c Welcome to the Wonderful World of ANSI!
e
s 00001/00011/00113
d D 5.5 90/06/01 16:49:42 bostic 5 4
c new copyright notice
e
s 00018/00014/00106
d D 5.4 90/02/21 08:34:41 bostic 4 3
c change to fold CR-NL into a single NL
e
s 00000/00000/00120
d D 5.3 90/02/07 08:25:17 bostic 3 2
x 2
c exclude sccs changes to remove contrib line from copyright
e
s 00000/00003/00117
d D 5.2 89/05/08 11:36:06 bostic 2 1
c clean up copyright notice
e
s 00120/00000/00000
d D 5.1 89/05/06 13:53:33 bostic 1 0
c Tony Nardo (trn@warper.jhuapl.edu) reworked the original, I
c redid his stuff; should handle multiple logons right.
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * Tony Nardo of the Johns Hopkins University/Applied Physics Lab.
 *
E 2
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
I 6
#include <arpa/inet.h>
E 6
#include <netdb.h>
I 7
#include <db.h>
E 7
I 6
#include <unistd.h>
#include <pwd.h>
#include <utmp.h>
E 6
#include <stdio.h>
#include <ctype.h>
I 6
#include <string.h>
#include "finger.h"
E 6

I 6
void
E 6
netfinger(name)
	char *name;
{
	extern int lflag;
	register FILE *fp;
	register int c, lastc;
	struct in_addr defaddr;
	struct hostent *hp, def;
	struct servent *sp;
	struct sockaddr_in sin;
	int s;
D 6
	char *alist[1], *host, *rindex();
	u_long inet_addr();
E 6
I 6
	char *alist[1], *host;
E 6

	if (!(host = rindex(name, '@')))
		return;
	*host++ = NULL;
D 10
	if (!(hp = gethostbyname(host))) {
		defaddr.s_addr = inet_addr(host);
		if (defaddr.s_addr == -1) {
			(void)fprintf(stderr,
			    "finger: unknown host: %s\n", host);
			return;
		}
E 10
I 10
	if (isdigit(*host) && (defaddr.s_addr = inet_addr(host)) != -1) {
E 10
		def.h_name = host;
		def.h_addr_list = alist;
		def.h_addr = (char *)&defaddr;
		def.h_length = sizeof(struct in_addr);
		def.h_addrtype = AF_INET;
		def.h_aliases = 0;
		hp = &def;
I 10
	} else if (!(hp = gethostbyname(host))) {
		(void)fprintf(stderr,
		    "finger: unknown host: %s\n", host);
		return;
E 10
	}
	if (!(sp = getservbyname("finger", "tcp"))) {
		(void)fprintf(stderr, "finger: tcp/finger: unknown service\n");
		return;
	}
	sin.sin_family = hp->h_addrtype;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port = sp->s_port;
	if ((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0) {
		perror("finger: socket");
		return;
	}

	/* have network connection; identify the host connected with */
	(void)printf("[%s]\n", hp->h_name);
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("finger: connect");
		(void)close(s);
		return;
	}

	/* -l flag for remote fingerd  */
	if (lflag)
		write(s, "/W ", 3);
	/* send the name followed by <CR><LF> */
	(void)write(s, name, strlen(name));
	(void)write(s, "\r\n", 2);

	/*
D 4
	 * read back what we get from the remote system.
E 4
I 4
	 * Read from the remote system; once we're connected, we assume some
	 * data.  If none arrives, we hang until the user interrupts.
E 4
	 *
D 4
	 * Note: once we connected to the remote site, we assume some data.
	 * If it can't/won't send any data, we hang here until Mr. User
	 * gets sufficiently bored to hit ^C.
E 4
I 4
	 * If we see a <CR> or a <CR> with the high bit set, treat it as
	 * a newline; if followed by a newline character, only output one
	 * newline.
E 4
	 *
D 4
	 * Some systems use the return key as a line terminator.  These
	 * systems tend to also set the parity bit on every byte.  If we
	 * see a <CR> with the 8th bit set, treat it as a newline character.
	 * 0x8d == <CR> with high bit set.
	 *
E 4
	 * Otherwise, all high bits are stripped; if it isn't printable and
	 * it isn't a space, we can simply set the 7th bit.  Every ASCII
	 * character with bit 7 set is printable.
	 */ 
D 11
	if (fp = fdopen(s, "r"))
E 11
I 11
	lastc = 0;
	if ((fp = fdopen(s, "r")) != NULL)
E 11
		while ((c = getc(fp)) != EOF) {
D 4
			if (c == 0x8d)
				c = '\n';
E 4
			c &= 0x7f;
D 4
			if (!isprint(c) && !isspace(c))
				c |= 0x40;
			lastc = c;
E 4
I 4
			if (c == 0x0d) {
I 9
				if (lastc == '\r')	/* ^M^M - skip dupes */
					continue;
E 9
				c = '\n';
				lastc = '\r';
			} else {
				if (!isprint(c) && !isspace(c))
					c |= 0x40;
				if (lastc != '\r' || c != '\n')
					lastc = c;
				else {
					lastc = '\n';
					continue;
				}
			}
E 4
			putchar(c);
		}
	if (lastc != '\n')
		putchar('\n');
I 7
	putchar('\n');
E 7
	(void)fclose(fp);
}
E 1
