h46663
s 00005/00005/00161
d D 8.1 93/06/06 15:01:15 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00024/00137
d D 6.16 92/06/24 12:14:49 bostic 18 17
c minor cleanups, ANSI prototypes
e
s 00012/00014/00149
d D 6.15 91/03/01 14:55:30 bostic 17 14
c minor cleanups
e
s 00002/00001/00174
d R 6.16 91/02/02 18:22:36 torek 16 15
c get errno from <errno.h>
e
s 00038/00026/00137
d R 6.15 90/09/29 11:56:24 bostic 15 14
c check for openlog/syslog errors
e
s 00001/00011/00162
d D 6.14 90/06/01 16:56:09 bostic 14 13
c new copyright notice
e
s 00004/00004/00169
d D 6.13 90/04/05 11:42:35 bostic 13 12
c typo; bug report 4.3BSD/ucb/289
e
s 00006/00048/00167
d D 6.12 89/11/13 18:41:45 bostic 12 11
c move shared internal facilities into syslog.h; probably should be read
c out of a configuration file, though.
e
s 00004/00001/00211
d D 6.11 89/02/15 12:21:59 bostic 11 10
c add LOG_PERROR flag
e
s 00009/00016/00203
d D 6.10 88/12/19 12:07:15 bostic 10 9
c increase buffer size; rewrite argument collection loop
e
s 00004/00004/00215
d D 6.9 88/08/03 09:45:44 bostic 9 8
c logger(1) hiccups on % signs; bug report 4.3BSD/ucb/231
e
s 00010/00005/00209
d D 6.8 88/06/29 21:50:55 bostic 8 7
c install approved copyright notice
e
s 00001/00000/00213
d D 6.7 88/06/06 09:34:28 bostic 7 6
c add LOG_UUCP
e
s 00010/00005/00203
d D 6.6 88/05/27 11:38:05 karels 6 5
c don't ignore long arguments
e
s 00080/00095/00128
d D 6.5 88/05/24 09:46:46 bostic 5 4
c add getopt, don't overflow with command line arguments, use strcasecmp
c instead of converting string, don't need most of these buffers
c add Berkeley header, written by Eric Allman
e
s 00000/00001/00223
d D 6.4 86/10/27 21:42:15 eric 4 3
c tut tut....  LOG_MARK doesn't belong here
e
s 00004/00000/00220
d D 6.3 86/10/27 19:24:00 eric 3 2
c add mark, syslog, lpr, news facilities
e
s 00001/00000/00219
d D 6.2 85/09/19 02:15:14 eric 2 1
c add "daemon" to list of known facility names
e
s 00219/00000/00000
d D 6.1 85/09/17 20:26:21 eric 1 0
c enter messages in system log -- new with 4.3 Beta release
e
u
U
f b 
f i 
t
T
I 1
/*
D 19
 * Copyright (c) 1983 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 14
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 8
E 5
 */

#ifndef lint
D 19
char copyright[] =
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
E 19
I 19
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 19
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

I 18
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
E 18
#include <stdio.h>
D 18
#include <syslog.h>
E 18
#include <ctype.h>
I 18
#include <string.h>
E 18

D 18
/*
**  LOGGER -- read and log utility
**
**	This routine reads from an input and arranges to write the
**	result on the system log, along with a useful tag.
*/
E 18
I 18
#define	SYSLOG_NAMES
#include <syslog.h>
E 18

I 18
int	decode __P((char *, CODE *));
int	pencode __P((char *));
void	usage __P((void));

/*
 * logger -- read and log utility
 *
 *	Reads from an input and arranges to write the result on the system
 *	log.
 */
int
E 18
main(argc, argv)
	int argc;
D 18
	char **argv;
E 18
I 18
	char *argv[];
E 18
{
D 5
	char buf[200];
	char *tag;
	register char *p;
E 5
I 5
D 18
	extern char *optarg;
D 13
	extern int optind;
E 13
I 13
	extern int errno, optind;
E 13
E 5
	int pri = LOG_NOTICE;
D 5
	int logflags = 0;
	extern char *getlogin();
E 5
I 5
	int ch, logflags = 0;
D 10
	char *tag, buf[200], *getlogin();
E 10
I 10
D 13
	char *tag, buf[1024], *getlogin();
E 13
I 13
	char *tag, buf[1024], *getlogin(), *strerror();
E 18
I 18
	int ch, logflags, pri;
	char *tag, buf[1024];
E 18
E 13
E 10
E 5

D 5
	/* initialize */
	tag = getlogin();

	/* crack arguments */
	while (--argc > 0)
	{
		p = *++argv;
		if (*p != '-')
			break;

		switch (*++p)
		{
		  case '\0':		/* dummy */
			/* this can be used to give null parameters */
			break;

		  case 't':		/* tag */
			if (argc > 1 && argv[1][0] != '-')
			{
				argc--;
				tag = *++argv;
E 5
I 5
	tag = NULL;
I 18
	pri = LOG_NOTICE;
	logflags = 0;
E 18
D 11
	while ((ch = getopt(argc, argv, "f:ip:t:")) != EOF)
E 11
I 11
	while ((ch = getopt(argc, argv, "f:ip:st:")) != EOF)
E 11
		switch((char)ch) {
		case 'f':		/* file to log */
			if (freopen(optarg, "r", stdin) == NULL) {
D 13
				fprintf("logger: ");
				perror(optarg);
E 13
I 13
				(void)fprintf(stderr, "logger: %s: %s.\n",
				    optarg, strerror(errno));
E 13
				exit(1);
E 5
			}
D 5
			else
				tag = NULL;
E 5
			break;
D 5

		  case 'p':		/* priority */
			if (argc > 1 && argv[1][0] != '-')
			{
				argc--;
				pri = pencode(*++argv);
			}
			break;

		  case 'i':		/* log process id also */
E 5
I 5
		case 'i':		/* log process id also */
E 5
			logflags |= LOG_PID;
			break;
D 5

		  case 'f':		/* file to log */
			if (argc > 1 && argv[1][0] != '-')
			{
				argc--;
				if (freopen(*++argv, "r", stdin) == NULL)
				{
					fprintf("logger: ");
					perror(*argv);
					exit(1);
				}
			}
E 5
I 5
		case 'p':		/* priority */
			pri = pencode(optarg);
I 11
			break;
		case 's':		/* log to standard error */
			logflags |= LOG_PERROR;
E 11
E 5
			break;
D 5

		  default:
			fprintf(stderr, "logger: unknown flag -%s\n", p);
E 5
I 5
		case 't':		/* tag */
			tag = optarg;
E 5
			break;
I 5
		case '?':
		default:
			usage();
E 5
		}
D 5
	}
E 5
I 5
	argc -= optind;
	argv += optind;
E 5

	/* setup for logging */
D 5
	openlog(tag, logflags, 0);
E 5
I 5
	openlog(tag ? tag : getlogin(), logflags, 0);
E 5
	(void) fclose(stdout);

	/* log input line if appropriate */
D 5
	if (argc > 0)
	{
		char buf[120];
E 5
I 5
	if (argc > 0) {
		register char *p, *endp;
		int len;
E 5

D 5
		buf[0] = '\0';
		while (argc-- > 0)
		{
			strcat(buf, " ");
			strcat(buf, *argv++);
E 5
I 5
D 10
		for (p = buf, endp = buf + sizeof(buf) - 1;;) {
E 10
I 10
		for (p = buf, endp = buf + sizeof(buf) - 2; *argv;) {
E 10
			len = strlen(*argv);
D 6
			if (p + len < endp) {
E 6
I 6
D 10
			if (p + len < endp && p > buf) {
				*--p = '\0';
E 10
I 10
			if (p + len > endp && p > buf) {
E 10
D 9
				syslog(pri, buf);
E 9
I 9
				syslog(pri, "%s", buf);
E 9
				p = buf;
			}
D 10
			if (len > sizeof(buf) - 1) {
E 10
I 10
			if (len > sizeof(buf) - 1)
E 10
D 9
				syslog(pri, *argv++);
E 9
I 9
				syslog(pri, "%s", *argv++);
E 9
D 10
				if (!--argc)
					break;
			} else {
E 10
I 10
			else {
				if (p != buf)
					*p++ = ' ';
E 10
E 6
				bcopy(*argv++, p, len);
D 10
				p += len;
				if (!--argc)
					break;
				*p++ = ' ';
D 6
			}
			else {
E 6
				*--p = '\0';
E 10
I 10
				*(p += len) = '\0';
E 10
D 6
				syslog(pri, buf);
				p = buf;
E 6
			}
E 5
		}
D 5
		syslog(pri, buf + 1);
E 5
I 5
D 10
		if (p != buf) {
			*p = '\0';
E 10
I 10
		if (p != buf)
E 10
D 9
			syslog(pri, buf);
E 9
I 9
			syslog(pri, "%s", buf);
E 9
D 10
		}
E 10
E 5
D 18
		exit(0);
	}

	/* main loop */
D 5
	while (fgets(buf, sizeof buf, stdin) != NULL)
E 5
I 5
	while (fgets(buf, sizeof(buf), stdin) != NULL)
E 5
D 9
		syslog(pri, buf);
E 9
I 9
		syslog(pri, "%s", buf);
E 9

E 18
I 18
	} else
		while (fgets(buf, sizeof(buf), stdin) != NULL)
			syslog(pri, "%s", buf);
E 18
	exit(0);
}

I 12
D 18
#define	SYSLOG_NAMES
#include <syslog.h>
E 12

E 18
D 12
struct code {
	char	*c_name;
	int	c_val;
};

struct code	PriNames[] = {
	"panic",	LOG_EMERG,
	"emerg",	LOG_EMERG,
	"alert",	LOG_ALERT,
	"crit",		LOG_CRIT,
	"err",		LOG_ERR,
	"error",	LOG_ERR,
	"warn",		LOG_WARNING,
	"warning",	LOG_WARNING,
	"notice",	LOG_NOTICE,
	"info",		LOG_INFO,
	"debug",	LOG_DEBUG,
	NULL,		-1
};

struct code	FacNames[] = {
	"kern",		LOG_KERN,
	"user",		LOG_USER,
	"mail",		LOG_MAIL,
I 2
	"daemon",	LOG_DAEMON,
E 2
	"auth",		LOG_AUTH,
	"security",	LOG_AUTH,
I 3
D 4
	"mark",		LOG_MARK,
E 4
	"syslog",	LOG_SYSLOG,
	"lpr",		LOG_LPR,
	"news",		LOG_NEWS,
I 7
	"uucp",		LOG_UUCP,
E 7
E 3
	"local0",	LOG_LOCAL0,
	"local1",	LOG_LOCAL1,
	"local2",	LOG_LOCAL2,
	"local3",	LOG_LOCAL3,
	"local4",	LOG_LOCAL4,
	"local5",	LOG_LOCAL5,
	"local6",	LOG_LOCAL6,
	"local7",	LOG_LOCAL7,
	NULL,		-1
};


E 12
/*
 *  Decode a symbolic name to a numeric value
 */
I 18
int
E 18
D 12

E 12
pencode(s)
	register char *s;
{
D 5
	register char *p;
	int lev;
	int fac;
	char buf[100];
E 5
I 5
	char *save;
	int fac, lev;
E 5

D 5
	for (p = buf; *s && *s != '.'; )
		*p++ = *s++;
	*p = '\0';
	if (*s++) {
		fac = decode(buf, FacNames);
E 5
I 5
	for (save = s; *s && *s != '.'; ++s);
	if (*s) {
		*s = '\0';
D 12
		fac = decode(save, FacNames);
E 12
I 12
		fac = decode(save, facilitynames);
E 12
E 5
D 17
		if (fac < 0)
D 5
			bailout("unknown facility name: ", buf);
		for (p = buf; *p++ = *s++; )
			continue;
	} else
E 5
I 5
			bailout("unknown facility name: ", save);
E 17
I 17
		if (fac < 0) {
			(void)fprintf(stderr,
			    "logger: unknown facility name: %s.\n", save);
			exit(1);
		}
E 17
		*s++ = '.';
	}
	else {
E 5
		fac = 0;
D 5
	lev = decode(buf, PriNames);
E 5
I 5
		s = save;
	}
D 12
	lev = decode(s, PriNames);
E 12
I 12
	lev = decode(s, prioritynames);
E 12
E 5
D 17
	if (lev < 0)
D 5
		bailout("unknown priority name: ", buf);

E 5
I 5
		bailout("unknown priority name: ", save);
E 17
I 17
	if (lev < 0) {
		(void)fprintf(stderr,
		    "logger: unknown priority name: %s.\n", save);
		exit(1);
	}
E 17
E 5
	return ((lev & LOG_PRIMASK) | (fac & LOG_FACMASK));
}

I 18
int
E 18
D 17

E 17
decode(name, codetab)
	char *name;
D 12
	struct code *codetab;
E 12
I 12
	CODE *codetab;
E 12
{
D 12
	register struct code *c;
E 12
I 12
	register CODE *c;
E 12
D 5
	register char *p;
	char buf[40];
E 5

	if (isdigit(*name))
		return (atoi(name));

D 5
	(void) strcpy(buf, name);
	for (p = buf; *p; p++)
		if (isupper(*p))
			*p = tolower(*p);
E 5
	for (c = codetab; c->c_name; c++)
D 5
		if (!strcmp(buf, c->c_name))
E 5
I 5
		if (!strcasecmp(name, c->c_name))
E 5
			return (c->c_val);

	return (-1);
}

I 18
void
E 18
D 5
bailout(a, b)
	char *a, *b;
E 5
I 5
D 17
bailout(msg, arg)
	char *msg, *arg;
E 5
{
D 5
	fprintf(stderr, "logger: %s%s\n", a, b);
E 5
I 5
	fprintf(stderr, "logger: %s%s\n", msg, arg);
	exit(1);
}

E 17
usage()
{
D 17
	fputs("logger: [-i] [-f file] [-p pri] [-t tag] [ message ... ]\n",
	    stderr);
E 17
I 17
	(void)fprintf(stderr,
D 18
	    "logger: [-i] [-f file] [-p pri] [-t tag] [ message ... ]\n");
E 18
I 18
	    "logger: [-is] [-f file] [-p pri] [-t tag] [ message ... ]\n");
E 18
E 17
E 5
	exit(1);
}
E 1
