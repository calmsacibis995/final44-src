h51778
s 00001/00001/00254
d D 8.4 95/04/27 16:26:29 bostic 16 15
c This fixes a null pointer dereference.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00254
d D 8.3 94/04/02 15:11:23 pendry 15 14
c add 1994 copyright
e
s 00032/00031/00223
d D 8.2 94/04/02 15:06:50 pendry 14 13
c prettyness police
e
s 00002/00002/00252
d D 8.1 93/06/06 14:41:30 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00247
d D 5.4 92/06/18 16:10:46 andrew 12 11
c slightly better error messages, add extra error check
e
s 00001/00001/00251
d D 5.3 91/03/01 14:25:26 bostic 11 10
c ANSI
e
s 00001/00011/00251
d D 5.2 90/06/01 15:52:25 bostic 10 9
c new copyright notice
e
s 00000/00000/00262
d D 5.1 89/03/01 14:27:49 karels 9 8
c bring up to rev 5
e
s 00051/00036/00211
d D 1.8 89/03/01 14:25:47 karels 8 7
c (some of) my favorite fixes, review changes
e
s 00005/00005/00242
d D 1.7 89/02/28 14:09:33 karels 7 6
c checked in for rick: add restart, size, modtime, newer, syst;
c switch to binary if both sides are unix; ls uses LIST, (new) nlist uses NLST;
c add default token to .netrc as wildcard machine
e
s 00001/00001/00246
d D 1.6 88/09/20 17:09:58 bostic 6 5
c switch includes for utmp.h
e
s 00010/00005/00237
d D 1.5 88/06/29 20:34:29 bostic 5 4
c install approved copyright notice
e
s 00009/00004/00233
d D 1.4 88/03/14 17:21:48 bostic 4 3
c add Berkeley specific headers
e
s 00012/00010/00225
d D 1.3 86/03/07 12:33:00 minshall 3 2
c Clean up for lint; change some stderr to stdout; bug fix
c (in ruserpass.c, routine rnetrc()).
e
s 00004/00004/00231
d D 1.2 86/02/03 15:23:48 minshall 2 1
c Change "ftprc" to "netrc" (to keep compatibility).
e
s 00235/00000/00000
d D 1.1 86/02/03 15:22:28 minshall 1 0
c date and time created 86/02/03 15:22:28 by minshall
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1985 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 13
I 13
D 15
 * Copyright (c) 1985, 1993
E 15
I 15
 * Copyright (c) 1985, 1993, 1994
E 15
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 7
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 7
E 5
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint

E 4
I 4
#endif /* not lint */
E 4

D 8
struct macel {
	char mac_name[9];	/* macro name */
	char *mac_start;	/* start of macro in macbuf */
	char *mac_end;		/* end of macro in macbuf */
};

extern int macnum, proxy;			/* number of defined macros */
extern struct macel macros[16], *macpt;
extern char macbuf[4096];

E 8
I 6
#include <sys/types.h>
E 6
D 14
#include <stdio.h>
#include <utmp.h>
#include <ctype.h>
E 14
D 6
#include <sys/types.h>
E 6
#include <sys/stat.h>
I 14

#include <ctype.h>
#include <err.h>
E 14
#include <errno.h>
I 14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

E 14
I 8
#include "ftp_var.h"
E 8

D 14
char	*renvlook(), *malloc(), *index(), *getenv(), *getpass(), *getlogin();
I 3
char	*strcpy();
E 3
struct	utmp *getutmp();
E 14
I 14
static	int token __P((void));
E 14
static	FILE *cfile;

D 8
ruserpass(host, aname, apass, aacct)
	char *host, **aname, **apass, **aacct;
{

	/* renv(host, aname, apass, aacct);
	if (*aname == 0 || *apass == 0) */
		return(rnetrc(host, aname, apass, aacct));
}

E 8
#define	DEFAULT	1
#define	LOGIN	2
#define	PASSWD	3
#define	ACCOUNT 4
#define MACDEF  5
#define	ID	10
D 8
#define	MACHINE	11
E 8
I 8
#define	MACH	11
E 8

static char tokval[100];

static struct toktab {
	char *tokstr;
	int tval;
} toktab[]= {
D 14
	"default",	DEFAULT,
	"login",	LOGIN,
	"password",	PASSWD,
I 8
	"passwd",	PASSWD,
E 8
	"account",	ACCOUNT,
D 8
	"machine",	MACHINE,
E 8
I 8
	"machine",	MACH,
E 8
	"macdef",	MACDEF,
	0,		0
E 14
I 14
	{ "default",	DEFAULT },
	{ "login",	LOGIN },
	{ "password",	PASSWD },
	{ "passwd",	PASSWD },
	{ "account",	ACCOUNT },
	{ "machine",	MACH },
	{ "macdef",	MACDEF },
	{ NULL,		0 }
E 14
};

I 14
int
E 14
D 8
static
rnetrc(host, aname, apass, aacct)
E 8
I 8
ruserpass(host, aname, apass, aacct)
E 8
	char *host, **aname, **apass, **aacct;
{
D 3
	char *hdir, buf[BUFSIZ], *tmp, c;
	int t, i;
E 3
I 3
	char *hdir, buf[BUFSIZ], *tmp;
I 8
	char myname[MAXHOSTNAMELEN], *mydomain;
E 8
D 7
	int t, i, c;
E 7
I 7
	int t, i, c, usedefault = 0;
E 7
E 3
	struct stat stb;
D 11
	extern int errno;
E 11
I 11
D 14
	static int token();
E 14
E 11

	hdir = getenv("HOME");
	if (hdir == NULL)
		hdir = ".";
D 2
	sprintf(buf, "%s/.ftprc", hdir);
E 2
I 2
D 3
	sprintf(buf, "%s/.netrc", hdir);
E 3
I 3
	(void) sprintf(buf, "%s/.netrc", hdir);
E 3
E 2
	cfile = fopen(buf, "r");
	if (cfile == NULL) {
		if (errno != ENOENT)
D 14
			perror(buf);
		return(0);
E 14
I 14
			warn("%s", buf);
		return (0);
E 14
	}
I 8
	if (gethostname(myname, sizeof(myname)) < 0)
		myname[0] = '\0';
D 14
	if ((mydomain = index(myname, '.')) == NULL)
E 14
I 14
	if ((mydomain = strchr(myname, '.')) == NULL)
E 14
		mydomain = "";
E 8
next:
	while ((t = token())) switch(t) {

	case DEFAULT:
D 7
		(void) token();
		continue;
E 7
I 7
		usedefault = 1;
		/* FALL THROUGH */
E 7

D 8
	case MACHINE:
D 7
		if (token() != ID || strcmp(host, tokval))
E 7
I 7
		if (!usedefault && (token() != ID || strcmp(host, tokval)))
E 8
I 8
	case MACH:
		if (!usedefault) {
			if (token() != ID)
				continue;
			/*
			 * Allow match either for user's input host name
			 * or official hostname.  Also allow match of 
			 * incompletely-specified host in local domain.
			 */
			if (strcasecmp(host, tokval) == 0)
				goto match;
			if (strcasecmp(hostname, tokval) == 0)
				goto match;
D 14
			if ((tmp = index(hostname, '.')) != NULL &&
E 14
I 14
			if ((tmp = strchr(hostname, '.')) != NULL &&
E 14
			    strcasecmp(tmp, mydomain) == 0 &&
			    strncasecmp(hostname, tokval, tmp-hostname) == 0 &&
			    tokval[tmp - hostname] == '\0')
				goto match;
D 14
			if ((tmp = index(host, '.')) != NULL &&
E 14
I 14
			if ((tmp = strchr(host, '.')) != NULL &&
E 14
			    strcasecmp(tmp, mydomain) == 0 &&
			    strncasecmp(host, tokval, tmp - host) == 0 &&
			    tokval[tmp - host] == '\0')
				goto match;
E 8
E 7
			continue;
D 8
		while ((t = token()) && t != MACHINE) switch(t) {
E 8
I 8
		}
	match:
		while ((t = token()) && t != MACH && t != DEFAULT) switch(t) {
E 8

		case LOGIN:
			if (token())
				if (*aname == 0) { 
D 3
					*aname = malloc(strlen(tokval) + 1);
					strcpy(*aname, tokval);
E 3
I 3
					*aname = malloc((unsigned) strlen(tokval) + 1);
					(void) strcpy(*aname, tokval);
E 3
				} else {
					if (strcmp(*aname, tokval))
						goto next;
				}
			break;
		case PASSWD:
D 8
			if (fstat(fileno(cfile), &stb) >= 0
			    && (stb.st_mode & 077) != 0) {
E 8
I 8
D 16
			if (strcmp(*aname, "anonymous") &&
E 16
I 16
			if ((*aname == NULL || strcmp(*aname, "anonymous")) &&
E 16
			    fstat(fileno(cfile), &stb) >= 0 &&
			    (stb.st_mode & 077) != 0) {
E 8
D 2
	fprintf(stderr, "Error - .ftprc file not correct mode.\n");
E 2
I 2
D 12
	fprintf(stderr, "Error - .netrc file not correct mode.\n");
E 2
	fprintf(stderr, "Remove password or correct mode.\n");
E 12
I 12
D 14
	fprintf(stderr, "Error: .netrc file is readable by others.\n");
	fprintf(stderr, 
		"Remove password or make file unreadable by others.\n\n");
E 14
I 14
	warnx("Error: .netrc file is readable by others.");
	warnx("Remove password or make file unreadable by others.");
E 14
E 12
D 8
				return(-1);
E 8
I 8
				goto bad;
E 8
			}
			if (token() && *apass == 0) {
D 3
				*apass = malloc(strlen(tokval) + 1);
				strcpy(*apass, tokval);
E 3
I 3
				*apass = malloc((unsigned) strlen(tokval) + 1);
				(void) strcpy(*apass, tokval);
E 3
			}
			break;
		case ACCOUNT:
			if (fstat(fileno(cfile), &stb) >= 0
			    && (stb.st_mode & 077) != 0) {
D 2
	fprintf(stderr, "Error - .ftprc file not correct mode.\n");
E 2
I 2
D 12
	fprintf(stderr, "Error - .netrc file not correct mode.\n");
E 2
	fprintf(stderr, "Remove account or correct mode.\n");
E 12
I 12
D 14
	fprintf(stderr, "Error: .netrc file is readable by others.\n");
	fprintf(stderr, 
		"Remove account or make file unreadable by others.\n\n");
E 14
I 14
	warnx("Error: .netrc file is readable by others.");
	warnx("Remove account or make file unreadable by others.");
E 14
E 12
D 8
				return(-1);
E 8
I 8
				goto bad;
E 8
			}
			if (token() && *aacct == 0) {
D 3
				*aacct = malloc(strlen(tokval) + 1);
				strcpy(*aacct, tokval);
E 3
I 3
				*aacct = malloc((unsigned) strlen(tokval) + 1);
				(void) strcpy(*aacct, tokval);
E 3
			}
			break;
		case MACDEF:
			if (proxy) {
I 8
				(void) fclose(cfile);
E 8
D 14
				return(0);
E 14
I 14
				return (0);
E 14
			}
			while ((c=getc(cfile)) != EOF && c == ' ' || c == '\t');
			if (c == EOF || c == '\n') {
				printf("Missing macdef name argument.\n");
D 8
				return(-1);
E 8
I 8
				goto bad;
E 8
			}
			if (macnum == 16) {
				printf("Limit of 16 macros have already been defined\n");
D 8
				return(-1);
E 8
I 8
				goto bad;
E 8
			}
			tmp = macros[macnum].mac_name;
			*tmp++ = c;
			for (i=0; i < 8 && (c=getc(cfile)) != EOF &&
			    !isspace(c); ++i) {
				*tmp++ = c;
			}
			if (c == EOF) {
				printf("Macro definition missing null line terminator.\n");
D 8
				return(-1);
E 8
I 8
				goto bad;
E 8
			}
			*tmp = '\0';
			if (c != '\n') {
				while ((c=getc(cfile)) != EOF && c != '\n');
			}
			if (c == EOF) {
				printf("Macro definition missing null line terminator.\n");
D 8
				return(-1);
E 8
I 8
				goto bad;
E 8
			}
			if (macnum == 0) {
				macros[macnum].mac_start = macbuf;
			}
			else {
				macros[macnum].mac_start = macros[macnum-1].mac_end + 1;
			}
			tmp = macros[macnum].mac_start;
			while (tmp != macbuf + 4096) {
				if ((c=getc(cfile)) == EOF) {
				printf("Macro definition missing null line terminator.\n");
D 8
					return(-1);
E 8
I 8
					goto bad;
E 8
				}
				*tmp = c;
				if (*tmp == '\n') {
					if (*(tmp-1) == '\0') {
					   macros[macnum++].mac_end = tmp - 1;
					   break;
					}
					*tmp = '\0';
				}
				tmp++;
			}
			if (tmp == macbuf + 4096) {
				printf("4K macro buffer exceeded\n");
D 8
				return(-1);
E 8
I 8
				goto bad;
E 8
			}
			break;
		default:
D 2
	fprintf(stderr, "Unknown .ftprc keyword %s\n", tokval);
E 2
I 2
D 14
	fprintf(stderr, "Unknown .netrc keyword %s\n", tokval);
E 14
I 14
			warnx("Unknown .netrc keyword %s", tokval);
E 14
E 2
			break;
		}
		goto done;
	}
done:
D 3
	fclose(cfile);
E 3
I 3
	(void) fclose(cfile);
D 14
	return(0);
E 14
I 14
	return (0);
E 14
I 8
bad:
	(void) fclose(cfile);
D 14
	return(-1);
E 14
I 14
	return (-1);
E 14
E 8
E 3
}

D 14
static
E 14
I 14
static int
E 14
token()
{
	char *cp;
	int c;
	struct toktab *t;

D 12
	if (feof(cfile))
E 12
I 12
	if (feof(cfile) || ferror(cfile))
E 12
		return (0);
	while ((c = getc(cfile)) != EOF &&
	    (c == '\n' || c == '\t' || c == ' ' || c == ','))
		continue;
	if (c == EOF)
		return (0);
	cp = tokval;
	if (c == '"') {
		while ((c = getc(cfile)) != EOF && c != '"') {
			if (c == '\\')
				c = getc(cfile);
			*cp++ = c;
		}
	} else {
		*cp++ = c;
		while ((c = getc(cfile)) != EOF
		    && c != '\n' && c != '\t' && c != ' ' && c != ',') {
			if (c == '\\')
				c = getc(cfile);
			*cp++ = c;
		}
	}
	*cp = 0;
	if (tokval[0] == 0)
		return (0);
	for (t = toktab; t->tokstr; t++)
		if (!strcmp(t->tokstr, tokval))
			return (t->tval);
	return (ID);
}
E 1
