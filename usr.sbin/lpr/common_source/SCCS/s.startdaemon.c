h45538
s 00002/00001/00080
d D 8.2 94/04/17 09:33:01 bostic 20 19
c un is declared as an automatic variable in main(), and isn't
c bzero'd before use.
c From: "Chris G. Demetriou" <cgd@nobozo.CS.Berkeley.EDU>
e
s 00002/00002/00079
d D 8.1 93/06/06 13:59:11 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00077
d D 5.10 93/02/25 17:03:18 torek 18 16
c hide the magic strlen+2: use the SUN_LEN macro
e
s 00004/00001/00077
d R 5.10 93/02/25 16:32:38 torek 17 16
c hide the magic strlen+2: use the SUN_LEN macro
e
s 00014/00008/00064
d D 5.9 92/07/21 10:28:27 bostic 16 15
c prototype lpr to fix quad's
e
s 00004/00004/00068
d D 5.8 91/08/21 02:03:56 torek 15 14
c sun => un, so we can compile on a sun
e
s 00003/00002/00069
d D 5.7 91/03/02 14:50:52 bostic 14 13
c ANSI
e
s 00001/00011/00070
d D 5.6 90/06/01 18:44:44 bostic 13 12
c new copyright notice
e
s 00003/00006/00078
d D 5.5 90/05/28 13:03:33 bostic 12 11
c sys_errlist -> strerror(3)
e
s 00003/00002/00081
d D 5.4 89/05/11 14:09:54 bostic 11 10
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00073
d D 5.3 88/06/30 18:00:16 bostic 10 9
c install approved copyright notice
e
s 00009/00003/00069
d D 5.2 88/05/05 18:08:40 bostic 9 8
c written by Ralph Campbell; add Berkeley specific header
e
s 00007/00001/00065
d D 5.1 85/06/06 10:09:46 dist 8 7
c Add copyright
e
s 00004/00001/00062
d D 4.7 83/07/17 00:12:30 sam 7 6
c put sccs id's to some use
e
s 00038/00020/00025
d D 4.6 83/06/29 17:10:04 ralph 6 5
c changed to use unix domain ipc.
e
s 00003/00002/00042
d D 4.5 83/06/02 12:24:21 ralph 5 4
c made local variables static to improve separation between functions.
e
s 00017/00001/00027
d D 4.4 83/05/27 11:36:07 ralph 4 3
c improved error messages
e
s 00001/00001/00027
d D 4.3 83/05/18 16:46:05 ralph 3 2
c fixed lprm segmentation fault when remote is down.
e
s 00000/00000/00028
d D 4.2 83/05/13 11:54:01 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00028/00000/00000
d D 4.1 83/04/29 11:30:46 ralph 1 0
c date and time created 83/04/29 11:30:46 by ralph
e
u
U
t
T
I 8
/*
D 19
 * Copyright (c) 1983 Regents of the University of California.
D 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
 * All rights reserved.
E 19
I 19
D 20
 * Copyright (c) 1983, 1993
E 20
I 20
 * Copyright (c) 1983, 1993, 1994
E 20
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 10
E 9
 */

E 8
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif
E 8
I 8
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 8

E 7
D 16
/*
 * Tell the printer daemon that there are new files in the spool directory.
 */
E 16

D 6
#include "lp.h"
E 6
I 6
D 11
#include <stdio.h>
E 11
D 16
#include <sys/types.h>
E 16
I 16
#include <sys/param.h>
E 16
#include <sys/socket.h>
#include <sys/un.h>
I 16

#include <dirent.h>
#include <errno.h>
E 16
I 11
#include <stdio.h>
E 11
D 16
#include "lp.local.h"
E 16
I 16
#include <unistd.h>
#include <string.h>
#include "lp.h"
E 16
I 11
#include "pathnames.h"
E 11
E 6

I 16
static void perr __P((char *));

/*
 * Tell the printer daemon that there are new files in the spool directory.
 */

int
E 16
D 5
startdaemon()
E 5
I 5
D 6
startdaemon(ahost)
	char *ahost;
E 6
I 6
startdaemon(printer)
	char *printer;
E 6
E 5
{
D 6
	register int rem, i, err = 0;
E 6
I 6
D 15
	struct sockaddr_un sun;
E 15
I 15
	struct sockaddr_un un;
E 15
	register int s, n;
E 6
	char buf[BUFSIZ];
I 14
D 16
	static void perr();
E 16
E 14

D 3
	rem = getport();
E 3
I 3
D 5
	rem = getport(host);
E 5
I 5
D 6
	rem = getport(ahost);
E 5
E 3
D 4
	if (rem < 0)
E 4
I 4
	if (rem < 0) {
		perr();
E 6
I 6
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if (s < 0) {
		perr("socket");
E 6
E 4
		return(0);
I 4
	}
I 20
	memset(&un, 0, sizeof(un));
E 20
I 6
D 15
	sun.sun_family = AF_UNIX;
D 11
	strcpy(sun.sun_path, SOCKETNAME);
E 11
I 11
	strcpy(sun.sun_path, _PATH_SOCKETNAME);
E 11
D 14
	if (connect(s, &sun, strlen(sun.sun_path) + 2) < 0) {
E 14
I 14
	if (connect(s, (struct sockaddr *)&sun, strlen(sun.sun_path) + 2) < 0) {
E 15
I 15
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, _PATH_SOCKETNAME);
D 18
	if (connect(s, (struct sockaddr *)&un, strlen(un.sun_path) + 2) < 0) {
E 18
I 18
#ifndef SUN_LEN
#define SUN_LEN(unp) (strlen((unp)->sun_path) + 2)
#endif
	if (connect(s, (struct sockaddr *)&un, SUN_LEN(&un)) < 0) {
E 18
E 15
E 14
		perr("connect");
		(void) close(s);
		return(0);
	}
E 6
E 4
	(void) sprintf(buf, "\1%s\n", printer);
D 6
	i = strlen(buf);
	if (write(rem, buf, i) != i) {
I 4
		perr();
E 4
		(void) close(rem);
E 6
I 6
	n = strlen(buf);
	if (write(s, buf, n) != n) {
		perr("write");
		(void) close(s);
E 6
		return(0);
	}
D 6
	while ((i = read(rem, buf, sizeof(buf))) > 0) {
		(void) fwrite(buf, 1, i, stdout);
		err++;
E 6
I 6
	if (read(s, buf, 1) == 1) {
		if (buf[0] == '\0') {		/* everything is OK */
			(void) close(s);
			return(1);
		}
		putchar(buf[0]);
E 6
	}
I 4
D 6
	if (i < 0)
		perr();
E 4
	(void) close(rem);
	return(i == 0 && err == 0);
E 6
I 6
	while ((n = read(s, buf, sizeof(buf))) > 0)
		fwrite(buf, 1, n, stdout);
	(void) close(s);
	return(0);
E 6
I 4
}

D 14
static
E 14
I 14
static void
E 14
D 6
perr()
E 6
I 6
perr(msg)
	char *msg;
E 6
{
I 6
D 12
	extern char *name;
E 6
	extern int sys_nerr;
	extern char *sys_errlist[];
E 12
I 6
D 16
	extern int errno;
E 16
I 12
	extern char *name;
D 16
	char *strerror();
E 16
E 12
E 6

D 6
	printf("%s: ", name);
E 6
I 6
D 12
	printf("%s: %s: ", name, msg);
E 6
	fputs(errno < sys_nerr ? sys_errlist[errno] : "Unknown error" , stdout);
	putchar('\n');
E 12
I 12
	(void)printf("%s: %s: %s\n", name, msg, strerror(errno));
E 12
E 4
}
E 1
