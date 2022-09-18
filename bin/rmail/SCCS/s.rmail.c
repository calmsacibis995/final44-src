h41011
s 00010/00011/00337
d D 8.3 95/05/15 10:04:20 eric 34 33
c convert empty return path to <>; use -p instead of -oM
e
s 00018/00003/00330
d D 8.2 94/11/13 14:52:37 eric 33 32
c wrap <> around addresses containing commas to avoid screwups
e
s 00005/00005/00328
d D 8.1 93/05/31 15:10:27 bostic 32 31
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00330
d D 5.2 93/05/13 09:00:32 eric 31 30
c avoid null pointer dereferences
e
s 00285/00169/00047
d D 5.1 93/04/29 23:32:37 bostic 30 29
c mostly a complete rewrite for cleanliness, but a few speedups too
e
s 00001/00011/00215
d D 4.15 90/05/31 20:38:40 bostic 29 28
c new copyright notice
e
s 00002/00001/00224
d D 4.14 89/09/01 13:32:30 rick 28 27
c check for EOF on fgets so dont get into infinite loop on
c truncated input (i.e. a file with only a from  line in it)
e
s 00006/00007/00219
d D 4.13 89/05/11 14:13:19 bostic 27 26
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00216
d D 4.12 89/01/19 16:23:42 bostic 26 25
c redo/comment/add args to sendmail; minor cleanups
e
s 00006/00001/00215
d D 4.11 88/11/15 14:04:28 bostic 25 24
c another worm fix; don't pass args starting with '-'; from Rick Adams
e
s 00025/00002/00191
d D 4.10 88/11/15 12:16:34 bostic 24 23
c originally written by Mark Horton; add Berkeley specific copyright
e
s 00126/00062/00066
d D 4.9 88/04/07 16:16:32 bostic 23 22
c new version from Rick Adams; rick@seismo.css.gov
e
s 00001/00002/00127
d D 4.8 86/05/15 15:22:51 karels 22 21
c initialize those registers
e
s 00001/00001/00128
d D 4.7 86/03/02 13:47:29 eric 21 20
c call sendmail with -i to ignore "." on a line by itself
e
s 00005/00005/00124
d D 4.6 85/12/06 07:37:59 lepreau 20 19
c grow some buffers
e
s 00001/00001/00128
d D 4.5 84/08/18 10:47:23 eric 19 18
c change sendmail error flag from -em to -ee to avoid duplicate returns
e
s 00004/00002/00125
d D 4.4 83/08/11 19:53:10 sam 18 17
c sccs keyword fixes
e
s 00000/00000/00127
d D 4.3 83/02/18 22:02:58 leres 17 16
c Actually, there have been no changes since version 3.12. I discovered
c that there were copies of the source in two places, but that they were
c the same. Here are the comments that would have been lost by the movement:
c 
c By eric 82/12/27 10:00:08
c handle multiple users; know about sendmail; mail back errors (perhaps
c this is why mail is getting lost); don't puke on badly formatted mail;
c work with new format headers (w/o "remote from ..."); other general
c cleanup to bulletproof etc.
e
s 00000/00000/00127
d D 4.2 83/02/18 21:59:02 leres 16 15
c 
e
s 00000/00000/00127
d D 4.1 83/02/18 21:58:39 leres 15 14
c 
e
s 00008/00004/00119
d D 3.12 82/12/27 09:49:01 eric 14 13
c remove useful.h references so that it can be compiled from normal place
e
s 00010/00010/00113
d D 3.11 82/05/31 18:50:42 eric 13 12
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00001/00001/00122
d D 3.10 82/03/30 07:00:34 eric 12 11
c make it work with new format headers (no ... remote from... lines);
c this was supposed to work before (sigh)
e
s 00004/00001/00119
d D 3.9 82/03/22 21:12:06 eric 11 10
c strip off parentheses from recipient names -- to keep sendmail from
c treating them as comments.
e
s 00009/00005/00111
d D 3.8 82/03/16 08:40:03 eric 10 9
c hack to pass badly formatted mail through reasonably
e
s 00008/00002/00108
d D 3.7 82/03/07 09:33:18 eric 9 8
c check exit status more carefully
e
s 00003/00003/00107
d D 3.6 81/12/06 12:40:16 eric 8 7
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00022/00016/00088
d D 3.5 81/10/31 23:12:21 eric 7 6
c work with more sophisticated addresses as well as garbage ones
e
s 00002/00002/00102
d D 3.4 81/10/26 14:23:12 eric 6 4
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00001/00000/00104
d D 3.3.1.1 81/09/23 18:23:39 eric 5 4
c break some configuration into conf.h -- simplifies makefile changes
c on different machines.  But there are still conditional libraries, so
c this may not be a good idea.....
e
s 00001/00001/00103
d D 3.3 81/09/06 19:49:33 eric 4 3
c cleanup, commenting, linting, etc.
e
s 00001/00001/00103
d D 3.2 81/09/06 11:57:40 eric 3 2
c mail back errors (perhaps this is why mail gets lost.....)
e
s 00046/00036/00058
d D 3.1 81/09/06 11:53:07 eric 2 1
c handle multiple users; know about sendmail
e
s 00094/00000/00000
d D 1.1 81/09/06 11:31:30 eric 1 0
c date and time created 81/09/06 11:31:30 by eric
e
u
U
f b 
f i 
f t (Berkeley)
t
T
I 24
/*
D 30
 * Copyright (c) 1981, 1988 The Regents of the University of California.
E 30
I 30
D 32
 * Copyright (c) 1988, 1993 The Regents of the University of California.
E 30
 * All rights reserved.
E 32
I 32
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 32
 *
D 29
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
E 29
I 29
 * %sccs.include.redist.c%
E 29
 */

E 24
I 18
#ifndef lint
D 24
static char sccsid[] =	"%W% (Berkeley) %G%";
#endif
E 24
I 24
D 32
char copyright[] =
D 30
"%Z% Copyright (c) 1981, 1988 The Regents of the University of California.\n\
E 30
I 30
"%Z% Copyright (c) 1988, 1993 The Regents of the University of California.\n\
E 30
 All rights reserved.\n";
E 32
I 32
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 32
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 24

E 18
I 1
/*
D 7
 * rmail: front end for mail to stack up those stupid >From ... remote from ...
 * lines and make a correct return address.  This works with the -f option
D 2
 * to /etc/delivermail so it won't work on systems without delivermail.
E 2
I 2
 * to /usr/lib/sendmail so it won't work on systems without sendmail.
E 2
 * However, it ought to be easy to modify a standard /bin/mail to do the
 * same thing.
 *
 * NOTE: Rmail is SPECIFICALLY INTENDED for ERNIE COVAX because of its
 * physical position as a gateway between the uucp net and the arpanet.
 * By default, other sites will probably want /bin/rmail to be a link
 * to /bin/mail, as it was intended by BTL.  However, other than the
 * (somewhat annoying) loss of information about when the mail was
 * originally sent, rmail should work OK on other systems running uucp.
 * If you don't run uucp you don't even need any rmail.
 */
E 7
I 7
D 10
** rmail: front end for mail to stack up those stupid >From ... remote from ...
** lines and make a correct return address.  This works with the -f option
** to /usr/lib/sendmail so it won't work on systems without sendmail.
** However, it ought to be easy to modify a standard /bin/mail to do the
** same thing.
E 10
I 10
D 23
**  RMAIL -- UUCP mail server.
**
**	This program reads the >From ... remote from ... lines that
**	UUCP is so fond of and turns them into something reasonable.
**	It calls sendmail giving it a -f option built from these
**	lines.
E 10
*/
E 23
I 23
 * RMAIL -- UUCP mail server.
 *
D 30
 *	This program reads the >From ... remote from ... lines that
 *	UUCP is so fond of and turns them into something reasonable.
 *	It calls sendmail giving it a -f option built from these lines. 
E 30
I 30
 * This program reads the >From ... remote from ... lines that UUCP is so
 * fond of and turns them into something reasonable.  It then execs sendmail
 * with various options built from these lines. 
 *
 * The expected syntax is:
 *
 *	 <user> := [-a-z0-9]+
 *	 <date> := ctime format
 *	 <site> := [-a-z0-9!]+
 * <blank line> := "^\n$"
 *	 <from> := "From" <space> <user> <space> <date>
 *		  [<space> "remote from" <space> <site>]
 *    <forward> := ">" <from>
 *	    msg := <from> <forward>* <blank-line> <body>
 *
 * The output of rmail(8) compresses the <forward> lines into a single
 * from path.
 *
 * The err(3) routine is included here deliberately to make this code
 * a bit more portable.
E 30
 */
E 23
E 7
D 30

D 8
static char	SccsId[] =	"%W%	%G%";

E 8
D 2
#include <stdio.h>
FILE *popen();
char *index();
E 2
I 2
D 23
# include <stdio.h>
# include <sysexits.h>
E 23
I 23
D 27
#include <stdio.h>
E 27
#include <sysexits.h>
#include <sys/types.h>
#include <sys/file.h>
E 30
I 30
#include <sys/param.h>
E 30
#include <sys/stat.h>
I 27
D 30
#include <stdio.h>
E 30
I 30
#include <sys/wait.h>

#include <ctype.h>
#include <fcntl.h>
E 30
#include <paths.h>
I 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>
E 30
E 27
E 23
D 14
# include "useful.h"
E 14
I 5
# include "conf.h"
E 5
E 2
D 18

I 8
D 14
SCCSID(%W%	%Y%	%G%);
E 14
I 14
static char	SccsId[] =	"%W%	%Y%	%G%";
E 18
E 14

I 33
#ifndef MAX
# define MAX(a, b)	((a) < (b) ? (b) : (a))
#endif

E 33
E 8
D 2
#define MAILER	"/etc/delivermail"
E 2
I 2
D 14
extern FILE *popen();
extern char *index();
E 14
I 14
D 23
typedef char	bool;
E 23
I 23
D 30
typedef char bool;
E 23
#define TRUE	1
#define FALSE	0
E 30
I 30
void err __P((int, const char *, ...));
void usage __P((void));
E 30

D 23
extern FILE	*popen();
extern char	*index();
extern char	*rindex();
E 23
I 23
D 30
extern char *index();
extern char *rindex();
E 23
E 14
E 2

I 2
D 23
bool	Debug;
E 23
I 23
char *Domain = "UUCP";		/* Default "Domain" */
E 23

E 30
I 30
int
E 30
D 23
# define MAILER	"/usr/lib/sendmail"
E 23
I 23
D 27
#define MAILER	"/usr/lib/sendmail"
E 23

E 27
E 2
main(argc, argv)
I 23
	int argc;
E 23
D 2
char **argv;
E 2
I 2
D 30
	char **argv;
E 30
I 30
	char *argv[];
E 30
E 2
{
D 2
	FILE *out;	/* output to delivermail */
E 2
I 2
D 23
	FILE *out;	/* output to sendmail */
E 23
E 2
D 20
	char lbuf[512];	/* one line of the message */
	char from[512];	/* accumulated path of sender */
	char ufrom[64];	/* user on remote system */
	char sys[64];	/* a system in path */
	char junk[512];	/* scratchpad */
E 20
I 20
D 30
	char lbuf[1024];	/* one line of the message */
	char from[512];		/* accumulated path of sender */
	char ufrom[512];	/* user on remote system */
	char sys[512];		/* a system in path */
I 23
	char fsys[512];		/* first system in path */
E 23
	char junk[1024];	/* scratchpad */
E 20
D 2
	char cmd[512];
	char *to, *cp;
E 2
I 2
D 23
	char cmd[2000];
E 23
I 23
	char *args[100];	/* arguments to mailer command */
E 23
	register char *cp;
I 7
D 22
	register char *uf;	/* ptr into ufrom */
E 22
I 22
D 23
	register char *uf = ufrom;	/* ptr into ufrom */
E 23
I 23
	register char *uf = NULL;	/* ptr into ufrom */
E 23
E 22
I 9
	int i;
I 23
	long position;
	struct stat sbuf;
#ifdef DEBUG
	bool Debug;
E 30
I 30
	extern char *optarg;
	extern int errno, optind;
	FILE *fp;
	struct stat sb;
	size_t fplen, fptlen, len;
	off_t offset;
	int ch, debug, i, pdes[2], pid, status;
	char *addrp, *domain, *p, *t;
	char *from_path, *from_sys, *from_user;
	char *args[100], buf[2048], lbuf[2048];
E 30
E 23
E 9
E 7
E 2

D 2
	to = argv[1];
	if (argc != 2) {
		fprintf(stderr, "Usage: rmail user\n");
		exit(1);
E 2
I 2
D 23
# ifdef DEBUG
	if (argc > 1 && strcmp(argv[1], "-T") == 0)
	{
E 23
I 23
D 30
	if (argc > 1 && strcmp(argv[1], "-T") == 0) {
E 23
		Debug = TRUE;
		argc--;
		argv++;
E 2
	}
I 2
D 23
# endif DEBUG
E 23
I 23
#endif
E 30
I 30
	debug = 0;
	domain = "UUCP";		/* Default "domain". */
	while ((ch = getopt(argc, argv, "D:T")) != EOF)
		switch (ch) {
		case 'T':
			debug = 1;
			break;
		case 'D':
			domain = optarg;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
E 30
E 23
E 2

D 2
	for (;;) {
E 2
I 2
D 23
	if (argc < 2)
	{
E 23
I 23
D 30
	if (argc < 2) {
E 23
		fprintf(stderr, "Usage: rmail user ...\n");
		exit(EX_USAGE);
	}
I 10
D 23

D 13
	strcpy(from, "");
	strcpy(ufrom, "/dev/null");
E 13
I 13
	(void) strcpy(from, "");
E 23
I 23
	if (argc > 2 && strncmp(argv[1], "-D", 2) == 0) {
		Domain = &argv[1][2];
		argc -= 2;
		argv += 2;
	}
	from[0] = '\0';
	fsys[0] = '\0';
E 23
D 27
	(void) strcpy(ufrom, "/dev/null");
E 27
I 27
	(void) strcpy(ufrom, _PATH_DEVNULL);
E 30
I 30
	if (argc < 1)
		usage();
E 30
E 27
E 13
E 10

D 23
	for (;;)
	{
E 23
I 23
D 30
	for (position = 0;; position = ftell(stdin)) {
E 23
E 2
D 4
		fgets(lbuf, sizeof lbuf, stdin);
E 4
I 4
D 28
		(void) fgets(lbuf, sizeof lbuf, stdin);
E 28
I 28
		if (fgets(lbuf, sizeof lbuf, stdin) == NULL)
			exit(EX_DATAERR);
E 28
E 4
D 2
		if (strncmp(lbuf, "From ", 5) && strncmp(lbuf, ">From ", 6))
E 2
I 2
D 23
		if (strncmp(lbuf, "From ", 5) != 0 && strncmp(lbuf, ">From ", 6) != 0)
E 23
I 23
		if (strncmp(lbuf, "From ", 5) != 0 &&
		    strncmp(lbuf, ">From ", 6) != 0)
E 30
I 30
	from_path = from_sys = from_user = NULL;
	for (offset = 0;;) {

		/* Get and nul-terminate the line. */
		if (fgets(lbuf, sizeof(lbuf), stdin) == NULL)
			exit (EX_DATAERR);
		if ((p = strchr(lbuf, '\n')) == NULL)
			err(EX_DATAERR, "line too long");
		*p = '\0';

		/* Parse lines until reach a non-"From" line. */
		if (!strncmp(lbuf, "From ", 5))
			addrp = lbuf + 5;
		else if (!strncmp(lbuf, ">From ", 6))
			addrp = lbuf + 6;
		else if (offset == 0)
			err(EX_DATAERR,
			    "missing or empty From line: %s", lbuf);
		else {
			*p = '\n';
E 30
E 23
E 2
			break;
D 2
		/* sscanf(lbuf, "%s %s %s %s %s %s %s remote from %s", junk, ufrom, junk, junk, junk, junk, junk, sys); */
E 2
D 6
		sscanf(lbuf, "%s %s", junk, ufrom);
E 6
I 6
D 30
		(void) sscanf(lbuf, "%s %s", junk, ufrom);
E 6
		cp = lbuf;
I 7
D 22
		uf = ufrom;
E 22
E 7
D 2
		for (;;) {
E 2
I 2
D 23
		for (;;)
		{
E 2
			cp = index(cp+1, 'r');
			if (cp == NULL)
I 7
			{
E 23
I 23
		uf = ufrom;
		for (;;) {
			cp = index(cp + 1, 'r');
			if (cp == NULL) {
E 23
				register char *p = rindex(uf, '!');
E 30
I 30
		}
E 30

D 23
				if (p != NULL)
				{
E 23
I 23
D 30
				if (p != NULL) {
E 23
					*p = '\0';
D 13
					strcpy(sys, uf);
E 13
I 13
					(void) strcpy(sys, uf);
E 13
					uf = p + 1;
					break;
				}
E 7
D 23
				cp = "remote from somewhere";
E 23
I 23
				(void) strcpy(sys, "");
				break;	/* no "remote from" found */
E 23
I 7
			}
E 7
#ifdef DEBUG
D 2
			printf("cp='%s'\n", cp);
E 2
I 2
			if (Debug)
				printf("cp='%s'\n", cp);
E 2
#endif
D 23
			if (strncmp(cp, "remote from ", 12)==0)
E 23
I 23
			if (strncmp(cp, "remote from ", 12) == 0)
E 30
I 30
		if (*addrp == '\0')
			err(EX_DATAERR, "corrupted From line: %s", lbuf);

		/* Use the "remote from" if it exists. */
		for (p = addrp; (p = strchr(p + 1, 'r')) != NULL;)
			if (!strncmp(p, "remote from ", 12)) {
				for (t = p += 12; *t && !isspace(*t); ++t);
				*t = '\0';
				if (debug)
					(void)fprintf(stderr,
					    "remote from: %s\n", p);
E 30
E 23
				break;
I 30
			}

		/* Else use the string up to the last bang. */
		if (p == NULL)
			if (*addrp == '!')
				err(EX_DATAERR,
				    "bang starts address: %s", addrp);
			else if ((t = strrchr(addrp, '!')) != NULL) {
				*t = '\0';
				p = addrp;
				addrp = t + 1;
				if (*addrp == '\0')
					err(EX_DATAERR,
					    "corrupted From line: %s", lbuf);
				if (debug)
					(void)fprintf(stderr, "bang: %s\n", p);
			}

		/* 'p' now points to any system string from this line. */
		if (p != NULL) {
			/* Nul terminate it as necessary. */
			for (t = p; *t && !isspace(*t); ++t);
			*t = '\0';

			/* If the first system, copy to the from_sys string. */
			if (from_sys == NULL) {
				if ((from_sys = strdup(p)) == NULL)
					err(EX_TEMPFAIL, NULL);
				if (debug)
					(void)fprintf(stderr,
					    "from_sys: %s\n", from_sys);
			}

			/* Concatenate to the path string. */
			len = t - p;
			if (from_path == NULL) {
				fplen = 0;
				if ((from_path = malloc(fptlen = 256)) == NULL)
					err(EX_TEMPFAIL, NULL);
			}
			if (fplen + len + 2 > fptlen) {
				fptlen += MAX(fplen + len + 2, 256);
				if ((from_path =
				    realloc(from_path, fptlen)) == NULL)
					err(EX_TEMPFAIL, NULL);
			}
			memmove(from_path + fplen, p, len);
			fplen += len;
			from_path[fplen++] = '!';
			from_path[fplen] = '\0';
E 30
		}
D 6
		sscanf(cp, "remote from %s", sys);
E 6
I 6
D 7
		(void) sscanf(cp, "remote from %s", sys);
E 7
I 7
D 30
		if (cp != NULL)
			(void) sscanf(cp, "remote from %s", sys);
E 7
E 6
D 13
		strcat(from, sys);
		strcat(from, "!");
E 13
I 13
D 23
		(void) strcat(from, sys);
		(void) strcat(from, "!");
E 23
I 23
		if (fsys[0] == '\0')
			(void) strcpy(fsys, sys);
		if (sys[0]) {
			(void) strcat(from, sys);
			(void) strcat(from, "!");
E 30
I 30

		/* Save off from user's address; the last one wins. */
		for (p = addrp; *p && !isspace(*p); ++p);
		*p = '\0';
I 34
		if (*addrp == '\0')
			addrp = "<>";
E 34
		if (from_user != NULL)
			free(from_user);
		if ((from_user = strdup(addrp)) == NULL)
			err(EX_TEMPFAIL, NULL);

		if (debug) {
			if (from_path != NULL)
				(void)fprintf(stderr,
				    "from_path: %s\n", from_path);
			(void)fprintf(stderr, "from_user: %s\n", from_user);
E 30
		}
E 23
E 13
D 30
#ifdef DEBUG
D 2
		printf("ufrom='%s', sys='%s', from now '%s'\n", ufrom, sys, from);
E 2
I 2
		if (Debug)
D 7
			printf("ufrom='%s', sys='%s', from now '%s'\n", ufrom, sys, from);
E 7
I 7
			printf("ufrom='%s', sys='%s', from now '%s'\n", uf, sys, from);
E 7
E 2
#endif
E 30
I 30

		if (offset != -1)
			offset = (off_t)ftell(stdin);
E 30
	}
I 23
D 30
	if (uf == NULL) {	/* No From line was provided */
		fprintf(stderr, "No From line in rmail\n");
		exit(EX_DATAERR);
E 30
I 30

	i = 0;
	args[i++] = _PATH_SENDMAIL;	/* Build sendmail's argument list. */
	args[i++] = "-oee";		/* No errors, just status. */
	args[i++] = "-odq";		/* Queue it, don't try to deliver. */
	args[i++] = "-oi";		/* Ignore '.' on a line by itself. */

D 34
	if (from_sys != NULL) {		/* Set sender's host name. */
		if (strchr(from_sys, '.') == NULL)
			(void)snprintf(buf, sizeof(buf),
			    "-oMs%s.%s", from_sys, domain);
		else
			(void)snprintf(buf, sizeof(buf), "-oMs%s", from_sys);
		if ((args[i++] = strdup(buf)) == NULL)
			 err(EX_TEMPFAIL, NULL);
E 30
	}
E 23
D 12
	strcat(from, ufrom);
E 12
I 12
D 13
	strcat(from, uf);
E 13
I 13
D 30
	(void) strcat(from, uf);
I 23
	(void) fstat(0, &sbuf);
	(void) lseek(0, position, L_SET);
E 30
I 30
					/* Set protocol used. */
	(void)snprintf(buf, sizeof(buf), "-oMr%s", domain);
E 34
I 34
	/* set from system and protocol used */
	if (from_sys == NULL)
		(void)snprintf(buf, sizeof(buf), "-p%s", domain);
	else if (strchr(from_sys, '.') == NULL)
		(void)snprintf(buf, sizeof(buf), "-p%s:%s.%s",
			domain, from_sys, domain);
	else
		(void)snprintf(buf, sizeof(buf), "-p%s:%s", domain, from_sys);
E 34
	if ((args[i++] = strdup(buf)) == NULL)
		err(EX_TEMPFAIL, NULL);
E 30
E 23
E 13
E 12

I 30
					/* Set name of ``from'' person. */
D 31
	(void)snprintf(buf, sizeof(buf), "-f%s%s", from_path, from_user);
E 31
I 31
	(void)snprintf(buf, sizeof(buf), "-f%s%s",
	    from_path ? from_path : "", from_user);
E 31
	if ((args[i++] = strdup(buf)) == NULL)
		err(EX_TEMPFAIL, NULL);

E 30
D 2
	sprintf(cmd, "%s -r%s %s", MAILER, from, to);
E 2
I 2
D 3
	sprintf(cmd, "%s -f%s", MAILER, from);
E 3
I 3
D 8
	sprintf(cmd, "%s -em -f%s", MAILER, from);
E 8
I 8
D 19
	(void) sprintf(cmd, "%s -em -f%s", MAILER, from);
E 19
I 19
D 21
	(void) sprintf(cmd, "%s -ee -f%s", MAILER, from);
E 21
I 21
D 23
	(void) sprintf(cmd, "%s -ee -f%s -i", MAILER, from);
E 21
E 19
E 8
E 3
	while (*++argv != NULL)
	{
D 13
		strcat(cmd, " '");
E 13
I 13
		(void) strcat(cmd, " '");
E 13
D 11
		strcat(cmd, *argv);
E 11
I 11
		if (**argv == '(')
D 13
			strncat(cmd, *argv + 1, strlen(*argv) - 2);
E 13
I 13
			(void) strncat(cmd, *argv + 1, strlen(*argv) - 2);
E 13
		else
D 13
			strcat(cmd, *argv);
E 11
		strcat(cmd, "'");
E 13
I 13
			(void) strcat(cmd, *argv);
		(void) strcat(cmd, "'");
E 23
I 23
	/*
D 30
	 * Now we rebuild the argument list and chain to sendmail. Note that
	 * the above lseek might fail on irregular files, but we check for
	 * that case below. 
E 30
I 30
	 * Don't copy arguments beginning with - as they will be
	 * passed to sendmail and could be interpreted as flags.
I 33
	 * To prevent confusion of sendmail wrap < and > around
	 * the address (helps to pass addrs like @gw1,@gw2:aa@bb)
E 33
E 30
	 */
D 30
	i = 0;
D 27
	args[i++] = MAILER;
E 27
I 27
	args[i++] = _PATH_SENDMAIL;
E 27
D 26
	args[i++] = "-ee";
	if (fsys[0] != '\0') {
E 26
I 26
	args[i++] = "-oee";		/* no errors, just status */
	args[i++] = "-odq";		/* queue it, don't try to deliver */
	args[i++] = "-oi";		/* ignore '.' on a line by itself */
	if (fsys[0] != '\0') {		/* set sender's host name */
E 26
		static char junk2[512];
E 30
I 30
D 33
	do {
D 31
		if (**argv == '-')
E 31
I 31
		if (*argv && **argv == '-')
E 33
I 33
	while (*argv) {
		if (**argv == '-')
E 33
E 31
			err(EX_USAGE, "dash precedes argument: %s", *argv);
D 33
	} while ((args[i++] = *argv++) != NULL);
E 33
I 33
		if (strchr(*argv, ',') == NULL || strchr(*argv, '<') != NULL)
			args[i++] = *argv;
		else {
			if ((args[i] = malloc(strlen(*argv) + 3)) == NULL)
				err(EX_TEMPFAIL, "Cannot malloc");
			sprintf (args [i++], "<%s>", *argv);
		}
		argv++;
	} 
	args[i] = 0;
E 33
E 30

D 30
		if (index(fsys, '.') == NULL) {
			(void) strcat(fsys, ".");
			(void) strcat(fsys, Domain);
		}
		(void) sprintf(junk2, "-oMs%s", fsys);
		args[i++] = junk2;
E 30
I 30
	if (debug) {
		(void)fprintf(stderr, "Sendmail arguments:\n");
		for (i = 0; args[i]; i++)
			(void)fprintf(stderr, "\t%s\n", args[i]);
E 30
E 23
E 13
	}
I 26
D 30
					/* set protocol used */
E 26
I 23
	(void) sprintf(junk, "-oMr%s", Domain);
	args[i++] = junk;
D 26
	if (from[0] != '\0') {
E 26
I 26
	if (from[0] != '\0') {		/* set name of ``from'' person */
E 26
		static char junk2[512];
E 30

D 30
		(void) sprintf(junk2, "-f%s", from);
		args[i++] = junk2;
E 30
I 30
	/*
	 * If called with a regular file as standard input, seek to the right
	 * position in the file and just exec sendmail.  Could probably skip
	 * skip the stat, but it's not unreasonable to believe that a failed
	 * seek will cause future reads to fail.
	 */
	if (!fstat(STDIN_FILENO, &sb) && S_ISREG(sb.st_mode)) {
		if (lseek(STDIN_FILENO, offset, SEEK_SET) != offset)
			err(EX_TEMPFAIL, "stdin seek");
		execv(_PATH_SENDMAIL, args);
		err(EX_OSERR, "%s", _PATH_SENDMAIL);
E 30
	}
D 30
	for (; *++argv != NULL; i++) {
D 25
		args[i] = *argv;
E 25
I 25
		/*
		 * don't copy arguments beginning with - as they will
		 * be passed to sendmail and could be interpreted as flags
I 26
		 * should be fixed in sendmail by using getopt(3), and
		 * just passing "--" before regular args.
E 26
		 */
		if (**argv != '-')
			args[i] = *argv;
E 25
	}
	args[i] = NULL;
E 23
E 2
#ifdef DEBUG
D 2
	printf("cmd='%s'\n", cmd);
E 2
I 2
D 23
	if (Debug)
		printf("cmd='%s'\n", cmd);
E 2
#endif
	out = popen(cmd, "w");
	fputs(lbuf, out);
	while (fgets(lbuf, sizeof lbuf, stdin))
		fputs(lbuf, out);
D 9
	pclose(out);
E 9
I 9
	i = pclose(out);
	if ((i & 0377) != 0)
	{
		fprintf(stderr, "pclose: status 0%o\n", i);
		exit(EX_OSERR);
E 23
I 23
	if (Debug) {
		printf("Command:");
		for (i = 0; args[i]; i++)
			printf(" %s", args[i]);
		printf("\n");
E 23
	}
I 23
#endif
	if ((sbuf.st_mode & S_IFMT) != S_IFREG) {
		/*
		 * If we were not called with standard input on a regular
		 * file, then we have to fork another process to send the
		 * first line down the pipe. 
		 */
		int pipefd[2];
D 26
# ifdef DEBUG
E 26
I 26
#ifdef DEBUG
E 26
		if (Debug)
			printf("Not a regular file!\n");
D 26
# endif DEBUG
E 26
I 26
#endif
E 26
		if (pipe(pipefd) < 0)
			exit(EX_OSERR);
		if (fork() == 0) {
			/*
			 * Child: send the message down the pipe. 
			 */
			FILE *out;
E 30
E 23
E 9
D 2
}
E 2

D 2
/*
 * Return the ptr in sp at which the character c appears;
 * NULL if not found
 */

char *
index(sp, c)
register char *sp, c;
{
	do {
		if (*sp == c)
			return(sp);
	} while (*sp++);
	return(NULL);
E 2
I 2
D 9
	exit(EX_OK);
E 9
I 9
D 23
	exit((i >> 8) & 0377);
E 23
I 23
D 30
			out = fdopen(pipefd[1], "w");
			close(pipefd[0]);
			fputs(lbuf, out);
			while (fgets(lbuf, sizeof lbuf, stdin))
				fputs(lbuf, out);
			(void) fclose(out);
			exit(EX_OK);
E 30
I 30
	if (pipe(pdes) < 0)
		err(EX_OSERR, NULL);

	switch (pid = vfork()) {
	case -1:				/* Err. */
		err(EX_OSERR, NULL);
	case 0:					/* Child. */
		if (pdes[0] != STDIN_FILENO) {
			(void)dup2(pdes[0], STDIN_FILENO);
			(void)close(pdes[0]);
E 30
		}
D 30
		/*
		 * Parent: call sendmail with pipe as standard input 
		 */
		close(pipefd[1]);
		dup2(pipefd[0], 0);
E 30
I 30
		(void)close(pdes[1]);
		execv(_PATH_SENDMAIL, args);
		_exit(127);
		/* NOTREACHED */
E 30
	}
D 27
	execv(MAILER, args);
	fprintf(stderr, "Exec of %s failed!\n", MAILER);
E 27
I 27
D 30
	execv(_PATH_SENDMAIL, args);
	fprintf(stderr, "Exec of %s failed!\n", _PATH_SENDMAIL);
E 27
	exit(EX_OSERR);
E 30
I 30

	if ((fp = fdopen(pdes[1], "w")) == NULL)
		err(EX_OSERR, NULL);
	(void)close(pdes[0]);

	/* Copy the file down the pipe. */
	do {
		(void)fprintf(fp, "%s", lbuf);
	} while (fgets(lbuf, sizeof(lbuf), stdin) != NULL);

	if (ferror(stdin))
		err(EX_TEMPFAIL, "stdin: %s", strerror(errno));

	if (fclose(fp))
		err(EX_OSERR, NULL);

	if ((waitpid(pid, &status, 0)) == -1)
		err(EX_OSERR, "%s", _PATH_SENDMAIL);

	if (!WIFEXITED(status))
		err(EX_OSERR,
		    "%s: did not terminate normally", _PATH_SENDMAIL);

	if (WEXITSTATUS(status))
		err(status, "%s: terminated with %d (non-zero) status",
		    _PATH_SENDMAIL, WEXITSTATUS(status));
	exit(EX_OK);
}

void
usage()
{
	(void)fprintf(stderr, "usage: rmail [-T] [-D domain] user ...\n");
	exit(EX_USAGE);
}

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#ifdef __STDC__
err(int eval, const char *fmt, ...)
#else
err(eval, fmt, va_alist)
	int eval;
	const char *fmt;
	va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "rmail: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(eval);
E 30
E 23
E 9
E 2
}
E 1
