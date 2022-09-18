h06914
s 00005/00005/00100
d D 8.1 93/06/06 22:25:22 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00104
d D 5.12 93/05/24 21:23:00 mckusick 15 14
c update NIC host name
e
s 00005/00005/00100
d D 5.11 91/03/02 13:35:01 bostic 14 13
c ANSI, make exit codes consistent
e
s 00004/00003/00101
d D 5.10 90/12/13 18:38:16 bostic 13 12
c concatenate multiple arguments
e
s 00001/00011/00103
d D 5.9 90/06/01 18:36:12 bostic 12 11
c new copyright notice
e
s 00005/00004/00109
d D 5.8 89/09/10 18:20:24 bostic 11 10
c more lint, exit 0 on success; bug report 4.3BSD-tahoe/usr.bin/27
e
s 00013/00015/00100
d D 5.7 89/05/04 18:24:25 bostic 10 9
c sri-nic.arpa -> nic.ddn.mil; minor lint; bug report tahoe/ucb/42
e
s 00003/00002/00112
d D 5.6 88/10/11 14:17:52 bostic 9 8
c fix argument parsing; use herror
e
s 00010/00005/00104
d D 5.5 88/06/29 21:51:19 bostic 8 7
c install approved copyright notice
e
s 00039/00018/00070
d D 5.4 88/06/10 10:50:26 bostic 7 6
c add getopt; add Berkeley specific header
e
s 00001/00000/00087
d D 5.3 88/02/08 14:38:40 leres 6 5
c Must zero sockaddr_in sin before using.
e
s 00001/00001/00086
d D 5.2 85/11/01 14:36:08 bloom 5 4
c sri-nic -> sri-nic.arpa
e
s 00014/00002/00073
d D 5.1 85/05/31 09:40:53 dist 4 2
c Add copyright
e
s 00002/00002/00073
d R 4.3 85/03/25 20:15:24 sam 3 2
c need .arpa for name server
e
s 00005/00008/00070
d D 4.2 83/06/10 09:30:24 ralph 2 1
c fixed argument count test so -h host works.
e
s 00078/00000/00000
d D 4.1 82/12/31 10:49:20 sam 1 0
c date and time created 82/12/31 10:49:20 by sam
e
u
U
t
T
I 4
/*
D 16
 * Copyright (c) 1980 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 8
E 7
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% %E%";
#endif
E 4
I 4
D 16
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 16
I 16
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 16
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 4

#include <sys/types.h>
#include <sys/socket.h>
D 10

E 10
#include <netinet/in.h>
D 10

#include <stdio.h>
E 10
#include <netdb.h>
I 10
#include <stdio.h>
E 10

D 5
#define	NICHOST	"sri-nic"
E 5
I 5
D 10
#define	NICHOST	"sri-nic.arpa"
E 10
I 10
D 15
#define	NICHOST	"nic.ddn.mil"
E 15
I 15
#define	NICHOST	"whois.internic.net"
E 15
E 10
E 5

main(argc, argv)
	int argc;
D 10
	char *argv[];
E 10
I 10
	char **argv;
E 10
{
D 7
	int s;
E 7
I 7
	extern char *optarg;
	extern int optind;
E 7
	register FILE *sfi, *sfo;
D 7
	register char c;
	char *host = NICHOST;
E 7
I 7
D 10
	register int c;
E 10
I 10
	register int ch;
E 10
E 7
	struct sockaddr_in sin;
	struct hostent *hp;
	struct servent *sp;
I 7
D 10
	int ch, s;
E 10
I 10
	int s;
E 10
	char *host;
E 7

D 7
	argc--, argv++;
D 2
	if (argc > 2) {
usage:
		fprintf(stderr, "usage: whois [ -h host ] name\n");
		exit(1);
	}
	if (strcmp(*argv, "-h") == 0) {
E 2
I 2
	if (argc > 2 && strcmp(*argv, "-h") == 0) {
E 2
		argv++, argc--;
		host = *argv++;
		argc--;
	}
D 2
	if (argc != 1)
		goto usage;
E 2
I 2
	if (argc != 1) {
		fprintf(stderr, "usage: whois [ -h host ] name\n");
		exit(1);
	}
E 7
I 7
	host = NICHOST;
D 9
	while ((ch = getopt(argc, argv, "h")) != EOF)
E 9
I 9
	while ((ch = getopt(argc, argv, "h:")) != EOF)
E 9
		switch((char)ch) {
		case 'h':
			host = optarg;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 13
	if (argc != 1)
E 13
I 13
	if (!argc)
E 13
		usage();

E 7
E 2
	hp = gethostbyname(host);
	if (hp == NULL) {
D 9
		fprintf(stderr, "whois: %s: host unknown\n", host);
E 9
I 9
D 10
		fprintf(stderr, "whois: %s: ", host);
E 10
I 10
		(void)fprintf(stderr, "whois: %s: ", host);
E 10
		herror((char *)NULL);
E 9
		exit(1);
	}
	host = hp->h_name;
D 11
	s = socket(hp->h_addrtype, SOCK_STREAM, 0, 0);
E 11
I 11
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
E 11
	if (s < 0) {
		perror("whois: socket");
D 14
		exit(2);
E 14
I 14
		exit(1);
E 14
	}
I 6
	bzero((caddr_t)&sin, sizeof (sin));
E 6
	sin.sin_family = hp->h_addrtype;
D 11
	if (bind(s, &sin, sizeof (sin), 0) < 0) {
E 11
I 11
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
E 11
		perror("whois: bind");
D 14
		exit(3);
E 14
I 14
		exit(1);
E 14
	}
D 11
	bcopy(hp->h_addr, &sin.sin_addr, hp->h_length);
E 11
I 11
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
E 11
	sp = getservbyname("whois", "tcp");
	if (sp == NULL) {
D 10
		fprintf(stderr, "whois: whois/tcp: unknown service\n");
E 10
I 10
		(void)fprintf(stderr, "whois: whois/tcp: unknown service\n");
E 10
D 14
		exit(4);
E 14
I 14
		exit(1);
E 14
	}
	sin.sin_port = sp->s_port;
D 11
	if (connect(s, &sin, sizeof (sin), 0) < 0) {
E 11
I 11
D 14
	if (connect(s, &sin, sizeof(sin)) < 0) {
E 14
I 14
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
E 14
E 11
		perror("whois: connect");
D 14
		exit(5);
E 14
I 14
		exit(1);
E 14
	}
	sfi = fdopen(s, "r");
	sfo = fdopen(s, "w");
	if (sfi == NULL || sfo == NULL) {
D 10
		perror("fdopen");
		close(s);
E 10
I 10
		perror("whois: fdopen");
		(void)close(s);
E 10
		exit(1);
	}
I 13
	while (argc-- > 1)
		(void)fprintf(sfo, "%s ", *argv++);
E 13
D 10
	fprintf(sfo, "%s\r\n", *argv);
E 10
I 10
	(void)fprintf(sfo, "%s\r\n", *argv);
E 10
D 7
	fflush(sfo);
E 7
I 7
	(void)fflush(sfo);
E 7
D 10
	while ((c = getc(sfi)) != EOF)
		putchar(c);
E 10
I 10
	while ((ch = getc(sfi)) != EOF)
		putchar(ch);
I 11
	exit(0);
E 11
E 10
I 7
}

D 13
static
E 13
usage()
{
D 10
	fprintf(stderr, "usage: whois [-h host] name\n");
E 10
I 10
D 13
	(void)fprintf(stderr, "usage: whois [-h host] name\n");
E 13
I 13
	(void)fprintf(stderr, "usage: whois [-h hostname] name ...\n");
E 13
E 10
	exit(1);
E 7
}
E 1
