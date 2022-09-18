h53110
s 00003/00003/00152
d D 5.6 91/03/02 14:42:40 bostic 11 10
c ANSI
e
s 00001/00011/00154
d D 5.5 90/06/01 18:40:38 bostic 10 9
c new copyright notice
e
s 00002/00001/00163
d D 5.4 88/10/11 12:22:29 bostic 9 8
c use herror
e
s 00021/00004/00143
d D 5.3 88/09/20 16:10:52 bostic 8 7
c Berkeley copyright notice
e
s 00004/00005/00143
d D 5.2 86/04/30 04:53:57 lepreau 7 6
c ipc calls have only 3 args and other lint
e
s 00007/00001/00141
d D 5.1 85/05/28 13:56:04 dist 6 5
c add copyright
e
s 00032/00006/00110
d D 4.5 84/12/23 16:55:09 sam 5 4
c check format more stringently and show proper exit status on errors; 
c from folks@brl
e
s 00017/00004/00099
d D 4.4 84/02/22 16:47:29 ralph 4 3
c added -v option to get just the version number.
e
s 00004/00003/00099
d D 4.3 83/10/05 09:59:19 karels 3 2
c service is hostnames, not nicname
e
s 00001/00001/00101
d D 4.2 83/08/11 22:51:27 sam 2 1
c standardize sccs keyword lines
e
s 00102/00000/00000
d D 4.1 82/12/31 10:42:55 sam 1 0
c date and time created 82/12/31 10:42:55 by sam
e
u
U
t
T
I 6
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
 */

E 6
I 3
D 4

E 4
E 3
I 1
#ifndef lint
I 8
char copyright[] =
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 8
D 2
static char sccsid[] = "%W% (Bekeley) %G%";
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
D 6
#endif
E 6
I 6
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 6

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <stdio.h>
#include <netdb.h>

#define	OUTFILE		"hosts.txt"	/* default output file */
I 4
#define	VERFILE		"hosts.ver"	/* default version file */
E 4
#define	QUERY		"ALL\r\n"	/* query to hostname server */
I 4
#define	VERSION		"VERSION\r\n"	/* get version number */
E 4

#define	equaln(s1, s2, n)	(!strncmp(s1, s2, n))

struct	sockaddr_in sin;
char	buf[BUFSIZ];
char	*outfile = OUTFILE;

main(argc, argv)
	int argc;
	char *argv[];
{
	int s;
	register len;
	register FILE *sfi, *sfo, *hf;
D 7
	register char *p;
E 7
	char *host;
	register struct hostent *hp;
	struct servent *sp;
I 4
	int version = 0;
I 5
	int beginseen = 0;
	int endseen = 0;
E 5
E 4

	argv++, argc--;
I 4
	if (**argv == '-') {
		if (argv[0][1] != 'v')
			fprintf(stderr, "unknown option %s ignored\n", *argv);
		else
			version++, outfile = VERFILE;
		argv++, argc--;
	}
E 4
	if (argc < 1 || argc > 2) {
D 4
		fprintf(stderr, "usage: gettable host [ file ]\n");
E 4
I 4
		fprintf(stderr, "usage: gettable [-v] host [ file ]\n");
E 4
		exit(1);
	}
D 3
	sp = getservbyname("nicname", "tcp");
E 3
I 3
	sp = getservbyname("hostnames", "tcp");
E 3
	if (sp == NULL) {
D 3
		fprintf(stderr, "gettable: nicname/tcp: unknown service\n");
E 3
I 3
		fprintf(stderr, "gettable: hostnames/tcp: unknown service\n");
E 3
		exit(3);
	}
	host = *argv;
	argv++, argc--;
	hp = gethostbyname(host);
	if (hp == NULL) {
D 9
		fprintf(stderr, "gettable: %s: host unknown\n", host);
E 9
I 9
		fprintf(stderr, "gettable: %s: ", host);
		herror((char *)NULL);
E 9
		exit(2);
	}
	host = hp->h_name;
	if (argc > 0)
		outfile = *argv;
	sin.sin_family = hp->h_addrtype;
D 7
	s = socket(hp->h_addrtype, SOCK_STREAM, 0, 0);
E 7
I 7
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
E 7
	if (s < 0) {
		perror("gettable: socket");
		exit(4);
	}
D 7
	if (bind(s, &sin, sizeof (sin), 0) < 0) {
E 7
I 7
D 11
	if (bind(s, &sin, sizeof (sin)) < 0) {
E 11
I 11
	if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) < 0) {
E 11
E 7
		perror("gettable: bind");
		exit(5);
	}
D 7
	bcopy(hp->h_addr, &sin.sin_addr, hp->h_length);
E 7
I 7
D 11
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
E 11
I 11
	bcopy(hp->h_addr, &sin.sin_addr, hp->h_length);
E 11
E 7
	sin.sin_port = sp->s_port;
D 7
	if (connect(s, &sin, sizeof (sin), 0) < 0) {
E 7
I 7
D 11
	if (connect(s, &sin, sizeof (sin)) < 0) {
E 11
I 11
	if (connect(s, (struct sockaddr *)&sin, sizeof (sin)) < 0) {
E 11
E 7
		perror("gettable: connect");
		exit(6);
	}
	fprintf(stderr, "Connection to %s opened.\n", host);
	sfi = fdopen(s, "r");
	sfo = fdopen(s, "w");
	if (sfi == NULL || sfo == NULL) {
		perror("gettable: fdopen");
		close(s);
		exit(1);
	}
	hf = fopen(outfile, "w");
	if (hf == NULL) {
		fprintf(stderr, "gettable: "); perror(outfile);
		close(s);
		exit(1);
	}
D 4
	fprintf(sfo, QUERY);
E 4
I 4
	fprintf(sfo, version ? VERSION : QUERY);
E 4
	fflush(sfo);
	while (fgets(buf, sizeof(buf), sfi) != NULL) {
		len = strlen(buf);
		buf[len-2] = '\0';
D 5
		if (equaln(buf, "BEGIN", 5) || equaln(buf, "END", 3)) {
E 5
I 5
		if (!version && equaln(buf, "BEGIN", 5)) {
			if (beginseen || endseen) {
				fprintf(stderr,
				    "gettable: BEGIN sequence error\n");
				exit(90);
			}
			beginseen++;
E 5
			continue;
		}
D 5
		if (equaln(buf, "ERR", 3)) {
D 3
			fprintf(stderr, "gettable: nicname error: %s", buf);
E 3
I 3
			fprintf(stderr, "gettable: hostnames error: %s", buf);
E 5
I 5
		if (!version && equaln(buf, "END", 3)) {
			if (!beginseen || endseen) {
				fprintf(stderr,
				    "gettable: END sequence error\n");
				exit(91);
			}
			endseen++;
E 5
E 3
			continue;
		}
I 5
		if (equaln(buf, "ERR", 3)) {
			fprintf(stderr,
			    "gettable: hostname service error: %s", buf);
			exit(92);
		}
E 5
		fprintf(hf, "%s\n", buf);
	}
	fclose(hf);
D 4
	fprintf(stderr, "Host table received.\n");
E 4
I 4
D 5
	if (version)
		fprintf(stderr, "Version number received.\n");
	else
E 5
I 5
	if (!version) {
		if (!beginseen) {
			fprintf(stderr, "gettable: no BEGIN seen\n");
			exit(93);
		}
		if (!endseen) {
			fprintf(stderr, "gettable: no END seen\n");
			exit(94);
		}
E 5
		fprintf(stderr, "Host table received.\n");
I 5
	} else
		fprintf(stderr, "Version number received.\n");
E 5
E 4
	close(s);
	fprintf(stderr, "Connection to %s closed\n", host);
I 4
	exit(0);
E 4
}
E 1
