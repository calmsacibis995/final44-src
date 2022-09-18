h30421
s 00011/00000/02180
d D 8.6 94/10/09 20:49:12 mckusick 49 48
c update to support passive mode (from cgd)
e
s 00006/00004/02174
d D 8.5 94/04/06 11:01:39 pendry 48 47
c fix globbing - need NOCHECK flag
e
s 00026/00030/02152
d D 8.4 94/04/03 10:06:39 pendry 47 45
c eliminate local glob code
e
s 00011/00012/02170
d R 8.4 94/04/03 09:25:02 pendry 46 45
c use glob in libc instead of local version
e
s 00001/00001/02181
d D 8.3 94/04/02 15:10:45 pendry 45 44
c add 1994 copyright
e
s 00198/00108/01984
d D 8.2 94/04/02 15:06:53 pendry 44 43
c prettyness police
e
s 00002/00002/02090
d D 8.1 93/06/06 14:40:35 bostic 43 42
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/02091
d D 5.29 92/07/06 21:23:22 andrew 42 41
c fix order in "newer" message
e
s 00014/00031/02078
d D 5.28 92/06/18 16:09:18 andrew 41 40
c fix MDTM comparisons, fix mcase conversion in mget
e
s 00002/00002/02107
d D 5.27 91/10/31 12:04:38 rick 40 39
c fixed null dereferencing problem with "get *"
e
s 00003/00003/02106
d D 5.26 91/03/05 17:23:39 bostic 39 38
c rename glob to ftpglob
e
s 00001/00001/02108
d D 5.25 91/03/01 14:25:18 bostic 38 37
c ANSI
e
s 00138/00266/01971
d D 5.24 90/09/28 15:27:01 bostic 37 36
c Chris Torek's fixes to make ftp stop using gets()
e
s 00001/00011/02236
d D 5.23 90/06/01 15:51:31 bostic 36 35
c new copyright notice
e
s 00032/00022/02215
d D 5.22 89/10/03 15:10:19 bostic 35 34
c POSIX signals
e
s 00005/00012/02232
d D 5.21 89/05/30 10:12:42 rick 34 33
c remove unused setebcdic() to make lint happier
c prefix local error messages with "local:" to lessen user confusion.
e
s 00036/00021/02208
d D 5.20 89/05/26 12:57:51 rick 33 32
c minor portability changes (casts, signal returns, etc)
c add missing \n on an error case for newer()
e
s 00064/00010/02165
d D 5.19 89/05/17 16:25:53 karels 32 31
c remember current server type setting, don't change until doing
c transfer; back to list/nlst in ascii; check type on proxy and primary server
c before doing text in binary
e
s 00006/00003/02169
d D 5.18 89/04/20 10:27:23 karels 31 30
c use binary for list, etc. if unix; avoid null usernames; bostic's pathname
c stuff
e
s 00033/00033/02139
d D 5.17 89/03/23 17:48:50 karels 30 29
c determine system type with or without autologin
e
s 00018/00010/02154
d D 5.16 89/03/21 17:47:07 karels 29 28
c print local, remote filenames only if remapped or non-prompting,
c verbose multi-file transfer (and print before rather than after transfer)
e
s 00112/00007/02052
d D 5.15 89/03/21 16:24:14 karels 28 25
c changes from Dave Borman: add site, umask, chmod, idle commands;
c try Xxxx directory commands if standard versions don't work; non-verbose
c PWD is not useful
e
s 00000/00120/01965
d D 5.14.1.2 89/03/01 18:11:34 karels 27 26
c delete restart code on branch for net release
e
s 00028/00002/02057
d D 5.14.1.1 89/03/01 17:53:45 karels 26 25
c add ifdef for restart stuff
e
s 00037/00028/02022
d D 5.14 89/03/01 14:25:26 karels 25 24
c (some of) my favorite fixes, review changes
e
s 00216/00011/01834
d D 5.13 89/02/28 14:09:07 karels 24 23
c checked in for rick: add restart, size, modtime, newer, syst;
c switch to binary if both sides are unix; ls uses LIST, (new) nlist uses NLST;
c add default token to .netrc as wildcard machine
e
s 00007/00003/01838
d D 5.12 89/02/06 14:46:36 csvsj 23 22
c fix nmap bug reported by Rick Adams
e
s 00012/00004/01829
d D 5.11 88/12/14 15:38:01 bostic 22 21
c globbing allocation/freeing wrong; bug report 4.3BSD/etc/149
e
s 00001/00002/01832
d D 5.10 88/11/28 10:49:01 bostic 21 20
c off-by-one in account; bug report tahoe/ucb/30
e
s 00004/00004/01830
d D 5.9 88/09/21 22:40:45 bostic 20 19
c remove private versions of getpass(3)
e
s 00010/00005/01824
d D 5.8 88/06/29 20:34:10 bostic 19 18
c install approved copyright notice
e
s 00009/00003/01820
d D 5.7 88/03/14 17:21:25 bostic 18 17
c add Berkeley specific headers
e
s 00005/00000/01818
d D 5.6 87/10/06 09:58:38 csvsj 17 16
c Ask user to confirm 'ls' and 'dir' local file to prevent accidental
c overwrite; bug report (4.3BSD/ucb/124)
e
s 00086/00079/01732
d D 5.5 86/03/07 12:32:15 minshall 16 15
c Clean up for lint; change some stderr to stdout; bug fix
c (in ruserpass.c, routine rnetrc()).
e
s 00883/00074/00928
d D 5.4 86/02/03 14:41:14 minshall 15 14
c Changes from Steve Jacobson (from <csvsj@ucbopal>).
e
s 00027/00032/00975
d D 5.3 86/01/13 19:32:55 mckusick 14 13
c numerous bug fixes from sun!gorodish!guy
e
s 00001/00001/01006
d D 5.2 86/01/13 17:59:19 karels 13 12
c try multiple addresses in turn if necessary;
c don't build hostent structures, just the parts we want
e
s 00007/00001/01000
d D 5.1 85/05/31 16:58:20 dist 12 11
c Add copyright
e
s 00005/00002/00996
d D 4.11 85/03/11 13:31:03 ralph 11 10
c minor fixes from ut-sally
e
s 00001/00001/00997
d D 4.10 84/04/10 17:24:14 ralph 10 9
c fix test for mls/mdir.
e
s 00002/00022/00996
d D 4.9 83/07/26 21:33:54 sam 9 8
c linger purge
e
s 00001/00001/01017
d D 4.8 83/07/02 00:29:25 sam 8 7
c include fixes
e
s 00070/00028/00948
d D 4.7 83/06/19 23:07:50 sam 7 6
c fix m* cmds and add linger control
e
s 00002/00001/00974
d D 4.6 83/05/11 22:02:20 sam 6 5
c split ftpd out to etc source; fix bug with sendport stuff
e
s 00108/00042/00867
d D 4.5 83/03/29 11:24:42 sam 5 4
c from jsq@utexas-11 (mls, mdir and random cleanups after me)
e
s 00138/00132/00771
d D 4.4 83/03/23 10:25:36 sam 4 3
c merge of changes from jsq@utexas-11
e
s 00244/00030/00659
d D 4.3 83/03/01 03:15:20 sam 3 2
c globbing of local file names & mget and mput (ugly, needs more work)
e
s 00015/00008/00674
d D 4.2 83/02/21 19:37:49 sam 2 1
c fixes from texas
e
s 00682/00000/00000
d D 4.1 83/01/15 16:52:34 sam 1 0
c date and time created 83/01/15 16:52:34 by sam
e
u
U
f b 
t
T
I 12
/*
D 15
 * Copyright (c) 1983 Regents of the University of California.
E 15
I 15
D 26
D 28
 * Copyright (c) 1985 Regents of the University of California.
E 28
I 28
D 43
 * Copyright (c) 1985, 1989 Regents of the University of California.
E 28
E 26
I 26
 * Copyright (c) 1985, 1989 Regents of the University of California.
E 26
E 15
D 18
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
 * All rights reserved.
E 43
I 43
D 45
 * Copyright (c) 1985, 1989, 1993
E 45
I 45
 * Copyright (c) 1985, 1989, 1993, 1994
E 45
 *	The Regents of the University of California.  All rights reserved.
E 43
 *
D 36
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 24
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 24
I 24
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 36
I 36
 * %sccs.include.redist.c%
E 36
E 24
E 19
E 18
 */

E 12
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif
E 12
I 12
D 18
#endif not lint
E 18
I 18
#endif /* not lint */
E 18
E 12

/*
 * FTP User Program -- Command Routines.
 */
D 3
#include <sys/types.h>
E 3
I 3
D 15
#include <sys/param.h>
E 15
I 15
D 25
#include "ftp_var.h"
E 25
I 25
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/stat.h>
E 25
E 15
I 8
D 11
#include <sys/stat.h>
E 11
E 8
E 3
#include <sys/socket.h>
D 44

E 44
I 44
#include <netinet/in.h>
E 44
I 6
#include <arpa/ftp.h>

I 44
#include <ctype.h>
#include <err.h>
I 47
#include <glob.h>
E 47
#include <netdb.h>
E 44
E 6
#include <signal.h>
#include <stdio.h>
D 44
#include <errno.h>
#include <netdb.h>
I 15
#include <ctype.h>
E 44
I 44
#include <stdlib.h>
#include <string.h>
E 44
I 24
#include <time.h>
I 33
D 44
#include <netinet/in.h>
E 44
I 44
#include <unistd.h>
E 44
E 33
E 24
I 16
D 25
#include <sys/wait.h>
I 24
#include <sys/stat.h>
#include <sys/param.h>
E 25
E 24
E 16
E 15
I 3
D 8
#include <stat.h>
E 8
E 3

I 25
#include "ftp_var.h"
I 31
#include "pathnames.h"
E 31
E 25
D 6
#include "ftp.h"
E 6
D 15
#include "ftp_var.h"
E 15

I 25
D 31

E 31
E 25
D 3
int	autologin = 1;
E 3
I 3
D 44
extern	char *globerr;
D 39
extern	char **glob();
E 39
I 39
extern	char **ftpglob();
E 39
I 5
extern	char *home;
E 5
D 24
extern	short gflag;
E 24
I 5
extern	char *remglob();
extern	char *getenv();
extern	char *index();
extern	char *rindex();
I 34
extern	char *strerror();
extern	int  errno;
E 34
I 31
D 32
extern	int allbinary;
E 32
E 31
I 26
D 27
#ifdef RESTART
E 26
I 24
extern off_t restart_point;
I 26
#endif
E 27
E 26
extern char reply_string[];
E 44
I 44
jmp_buf	jabort;
char   *mname;
I 47
char   *home = "/";
E 47
E 44

E 24
I 15
D 44
char *mname;
jmp_buf jabort;
char *dotrans(), *domap();
E 15
E 5
E 3

E 44
/*
I 37
 * `Another' gets another argument, and stores the new argc and argv.
 * It reverts to the top level (via main.c's intr()) on EOF/error.
 *
 * Returns false if no new arguments have been added.
 */
I 44
int
E 44
another(pargc, pargv, prompt)
	int *pargc;
	char ***pargv;
	char *prompt;
{
	int len = strlen(line), ret;
D 44
	extern sig_t intr();
E 44

	if (len >= sizeof(line) - 3) {
		printf("sorry, arguments too long\n");
		intr();
	}
	printf("(%s) ", prompt);
	line[len++] = ' ';
	if (fgets(&line[len], sizeof(line) - len, stdin) == NULL)
		intr();
	len += strlen(&line[len]);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	makeargv();
	ret = margc > *pargc;
	*pargc = margc;
	*pargv = margv;
	return (ret);
}

/*
E 37
 * Connect to peer server and
 * auto-login, if possible.
 */
I 44
void
E 44
setpeer(argc, argv)
	int argc;
	char *argv[];
{
D 13
	struct hostent *host, *hookup();
E 13
I 13
D 44
	char *host, *hookup();
E 44
I 44
	char *host;
E 44
E 13
D 33
	int port;
E 33
I 33
	short port;
E 33

	if (connected) {
D 15
		printf("Already connected to %s, use disconnect first.\n",
E 15
I 15
		printf("Already connected to %s, use close first.\n",
E 15
			hostname);
I 15
		code = -1;
E 15
		return;
	}
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(to) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc > 3) {
E 37
I 37
	if (argc < 2)
		(void) another(&argc, &argv, "to");
	if (argc < 2 || argc > 3) {
E 37
		printf("usage: %s host-name [port]\n", argv[0]);
I 15
		code = -1;
E 15
		return;
	}
	port = sp->s_port;
	if (argc > 2) {
D 2
		port = atoi(argv[1]);
E 2
I 2
		port = atoi(argv[2]);
E 2
		if (port <= 0) {
D 2
			printf("%s: bad port number.\n", argv[1]);
E 2
I 2
			printf("%s: bad port number-- %s\n", argv[1], argv[2]);
			printf ("usage: %s host-name [port]\n", argv[0]);
I 15
			code = -1;
E 15
E 2
			return;
		}
		port = htons(port);
	}
	host = hookup(argv[1], port);
	if (host) {
D 30
		connected = 1;
D 24
		if (autologin)
E 24
I 24
		if (autologin) {
			int overbose;
E 30
I 30
		int overbose;
E 30
I 25

I 30
		connected = 1;
I 32
		/*
		 * Set up defaults for FTP.
		 */
		(void) strcpy(typename, "ascii"), type = TYPE_A;
		curtype = TYPE_A;
		(void) strcpy(formname, "non-print"), form = FORM_N;
		(void) strcpy(modename, "stream"), mode = MODE_S;
		(void) strcpy(structname, "file"), stru = STRU_F;
		(void) strcpy(bytename, "8"), bytesize = 8;
E 32
		if (autologin)
E 30
E 25
E 24
D 15
			login(host);
E 15
I 15
D 16
			login(argv[1]);
E 16
I 16
			(void) login(argv[1]);
I 30

E 30
I 24
#if defined(unix) && NBBY == 8
/*
 * this ifdef is to keep someone form "porting" this to an incompatible
 * system and not checking this out. This way they have to think about it.
 */
D 25
			overbose = verbose, verbose = -1;
E 25
I 25
D 30
			overbose = verbose;
			if (debug == 0)
				verbose = -1;
E 25
			if (command("SYST") == COMPLETE && overbose) {
				register char *cp, c;
				cp = index(reply_string+4, ' ');
				if (cp == NULL)
					cp = index(reply_string+4, '\r');
				if (cp) {
					if (cp[-1] == '.')
						cp--;
					c = *cp;
					*cp = '\0';
				}

				printf("Remote system type is %s.\n",
					reply_string+4);
				if (cp)
					*cp = c;
E 30
I 30
		overbose = verbose;
		if (debug == 0)
			verbose = -1;
I 31
D 32
		allbinary = 0;
E 32
E 31
		if (command("SYST") == COMPLETE && overbose) {
D 44
			register char *cp, c;
			cp = index(reply_string+4, ' ');
E 44
I 44
			char *cp, c;
			cp = strchr(reply_string+4, ' ');
E 44
			if (cp == NULL)
D 44
				cp = index(reply_string+4, '\r');
E 44
I 44
				cp = strchr(reply_string+4, '\r');
E 44
			if (cp) {
				if (cp[-1] == '.')
					cp--;
				c = *cp;
				*cp = '\0';
E 30
			}
D 30
			if (!strncmp(reply_string, "215 UNIX Type: L8", 17)) {
				setbinary();
				if (overbose)
D 25
					printf("Using %s mode to transfer files.\n",
						typename);
E 25
I 25
				    printf("Using %s mode to transfer files.\n",
					typename);
E 25
			} else if (overbose && 
			    !strncmp(reply_string, "215 TOPS20", 10)) {
D 25
				printf("Remember to set tenex mode when transfering binary files from this machine.\n");
E 25
I 25
				printf(
E 30
I 30

			printf("Remote system type is %s.\n",
				reply_string+4);
			if (cp)
				*cp = c;
		}
		if (!strncmp(reply_string, "215 UNIX Type: L8", 17)) {
D 32
			setbinary();
I 31
			allbinary = 1;
E 32
I 32
			if (proxy)
				unix_proxy = 1;
			else
				unix_server = 1;
			/*
			 * Set type to 0 (not specified by user),
			 * meaning binary by default, but don't bother
			 * telling server.  We can use binary
			 * for text files unless changed by the user.
			 */
			type = 0;
			(void) strcpy(typename, "binary");
E 32
E 31
			if (overbose)
			    printf("Using %s mode to transfer files.\n",
				typename);
D 32
		} else if (overbose && 
		    !strncmp(reply_string, "215 TOPS20", 10)) {
			printf(
E 32
I 32
		} else {
			if (proxy)
				unix_proxy = 0;
			else
				unix_server = 0;
			if (overbose && 
			    !strncmp(reply_string, "215 TOPS20", 10))
				printf(
E 32
E 30
"Remember to set tenex mode when transfering binary files from this machine.\n");
E 25
D 30
			}
			verbose = overbose;
#endif /* unix */
E 30
		}
I 30
		verbose = overbose;
#endif /* unix */
E 30
E 24
E 16
E 15
	}
}

struct	types {
	char	*t_name;
	char	*t_mode;
	int	t_type;
I 2
	char	*t_arg;
E 2
} types[] = {
D 2
	{ "ascii",	"A",	TYPE_A },
	{ "binary",	"I",	TYPE_I },
	{ "image",	"I",	TYPE_I },
	{ "ebcdic",	"E",	TYPE_E },
	{ "tenex",	"L",	TYPE_L },
E 2
I 2
	{ "ascii",	"A",	TYPE_A,	0 },
	{ "binary",	"I",	TYPE_I,	0 },
	{ "image",	"I",	TYPE_I,	0 },
	{ "ebcdic",	"E",	TYPE_E,	0 },
	{ "tenex",	"L",	TYPE_L,	bytename },
E 2
D 44
	0
E 44
I 44
	{ NULL }
E 44
};

/*
 * Set transfer type.
 */
I 44
void
E 44
settype(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
D 44
	register struct types *p;
E 44
I 44
	struct types *p;
E 44
I 2
	int comret;
E 2

	if (argc > 2) {
		char *sep;

		printf("usage: %s [", argv[0]);
		sep = " ";
		for (p = types; p->t_name; p++) {
			printf("%s%s", sep, p->t_name);
D 32
			if (*sep == ' ')
				sep = " | ";
E 32
I 32
			sep = " | ";
E 32
		}
		printf(" ]\n");
I 15
		code = -1;
E 15
		return;
	}
	if (argc < 2) {
		printf("Using %s mode to transfer files.\n", typename);
I 15
		code = 0;
E 15
		return;
	}
	for (p = types; p->t_name; p++)
		if (strcmp(argv[1], p->t_name) == 0)
			break;
	if (p->t_name == 0) {
		printf("%s: unknown mode\n", argv[1]);
I 15
		code = -1;
E 15
		return;
	}
D 2
	if (command("TYPE %s", p->t_mode) == COMPLETE) {
E 2
I 2
	if ((p->t_arg != NULL) && (*(p->t_arg) != '\0'))
		comret = command ("TYPE %s %s", p->t_mode, p->t_arg);
	else
		comret = command("TYPE %s", p->t_mode);
	if (comret == COMPLETE) {
E 2
D 16
		strcpy(typename, p->t_name);
E 16
I 16
		(void) strcpy(typename, p->t_name);
E 16
D 32
		type = p->t_type;
E 32
I 32
		curtype = type = p->t_type;
E 32
	}
I 32
}

/*
 * Internal form of settype; changes current type in use with server
 * without changing our notion of the type for data transfers.
 * Used to change to and from ascii for listings.
 */
I 44
void
E 44
changetype(newtype, show)
	int newtype, show;
{
D 44
	register struct types *p;
E 44
I 44
	struct types *p;
E 44
	int comret, oldverbose = verbose;

	if (newtype == 0)
		newtype = TYPE_I;
	if (newtype == curtype)
		return;
	if (debug == 0 && show == 0)
		verbose = 0;
	for (p = types; p->t_name; p++)
		if (newtype == p->t_type)
			break;
	if (p->t_name == 0) {
		printf("ftp: internal error: unknown type %d\n", newtype);
		return;
	}
	if (newtype == TYPE_L && bytename[0] != '\0')
		comret = command("TYPE %s %s", p->t_mode, bytename);
	else
		comret = command("TYPE %s", p->t_mode);
	if (comret == COMPLETE)
		curtype = newtype;
	verbose = oldverbose;
E 32
}

I 33
char *stype[] = {
	"type",
	"",
	0
};

E 33
/*
 * Set binary transfer type.
 */
/*VARARGS*/
D 44
setbinary()
E 44
I 44
void
setbinary(argc, argv)
	int argc;
	char **argv;
E 44
{
I 44

E 44
D 33

	call(settype, "type", "binary", 0);
E 33
I 33
	stype[1] = "binary";
	settype(2, stype);
E 33
}

/*
 * Set ascii transfer type.
 */
/*VARARGS*/
D 44
setascii()
E 44
I 44
void
setascii(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
D 33

	call(settype, "type", "ascii", 0);
E 33
I 33
	stype[1] = "ascii";
	settype(2, stype);
E 33
}

/*
 * Set tenex transfer type.
 */
/*VARARGS*/
D 44
settenex()
E 44
I 44
void
settenex(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
D 33

	call(settype, "type", "tenex", 0);
E 33
I 33
	stype[1] = "tenex";
	settype(2, stype);
E 33
}

/*
D 34
 * Set ebcdic transfer type.
 */
/*VARARGS*/
setebcdic()
{
D 33

	call(settype, "type", "ebcdic", 0);
E 33
I 33
	stype[1] = "ebcdic";
	settype(2, stype);
E 33
}

/*
E 34
 * Set file transfer mode.
 */
I 16
/*ARGSUSED*/
E 16
D 44
setmode(argc, argv)
E 44
I 44
void
setftmode(argc, argv)
E 44
I 37
	int argc;
E 37
	char *argv[];
{

	printf("We only support %s mode, sorry.\n", modename);
I 15
	code = -1;
E 15
}

/*
 * Set file transfer format.
 */
I 16
/*ARGSUSED*/
I 44
void
E 44
E 16
setform(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

	printf("We only support %s format, sorry.\n", formname);
I 15
	code = -1;
E 15
}

/*
 * Set file transfer structure.
 */
I 16
/*ARGSUSED*/
I 44
void
E 44
E 16
setstruct(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

	printf("We only support %s structure, sorry.\n", structname);
I 15
	code = -1;
E 15
}

I 11
/*
 * Send a single file.
 */
I 44
void
E 44
E 11
D 5
/*
 * Send a single file.
 */
I 4
append(argc, argv)
	char *argv[];
{

	return (put1("APPE", argc, argv));
}

E 5
E 4
put(argc, argv)
D 5
	char *argv[];
{
D 3
	int fd;
	register int n, addr;
	register char *cp, *targ;
E 3

D 4
	if (!connected) {
		printf("Not connected.\n");
		return;
	}
E 4
I 4
	return (put1("STOR", argc, argv));
}

put1(cmd, argc, argv)
	char *cmd;
E 5
	int argc;
	char *argv[];
{
I 5
	char *cmd;
I 15
	int loc = 0;
E 15
I 14
D 29
	char *oldargv1;
E 29
I 29
	char *oldargv1, *oldargv2;
E 29
E 14
E 5

E 4
D 15
	if (argc == 2)
		argc++, argv[2] = argv[1];
E 15
I 15
	if (argc == 2) {
		argc++;
		argv[2] = argv[1];
		loc++;
	}
E 15
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(local-file) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "local-file"))
		goto usage;
	if (argc < 3 && !another(&argc, &argv, "remote-file")) {
E 37
usage:
D 15
		printf("%s local-file remote-file\n", argv[0]);
E 15
I 15
D 37
		printf("usage:%s local-file remote-file\n", argv[0]);
E 37
I 37
		printf("usage: %s local-file remote-file\n", argv[0]);
E 37
		code = -1;
E 15
		return;
	}
D 37
	if (argc < 3) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(remote-file) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 3) 
		goto usage;
E 37
I 14
	oldargv1 = argv[1];
I 29
	oldargv2 = argv[2];
E 29
E 14
I 3
D 15
	if (!globulize(&argv[1]))
E 15
I 15
	if (!globulize(&argv[1])) {
		code = -1;
E 15
		return;
I 15
	}
E 15
I 14
	/*
	 * If "globulize" modifies argv[1], and argv[2] is a copy of
	 * the old argv[1], make it a copy of the new argv[1].
	 */
D 15
	if (argv[1] != oldargv1 && argv[2] == oldargv1)
E 15
I 15
	if (argv[1] != oldargv1 && argv[2] == oldargv1) {
E 15
		argv[2] = argv[1];
E 14
I 5
D 15
	cmd = (argv[0][0] == 'a') ? "APPE" : "STOR";
E 15
I 15
	}
	cmd = (argv[0][0] == 'a') ? "APPE" : ((sunique) ? "STOU" : "STOR");
	if (loc && ntflag) {
		argv[2] = dotrans(argv[2]);
	}
	if (loc && mapflag) {
		argv[2] = domap(argv[2]);
	}
E 15
E 5
E 3
D 4
	sendrequest("STOR", argv[1], argv[2]);
E 4
I 4
D 29
	sendrequest(cmd, argv[1], argv[2]);
E 29
I 29
	sendrequest(cmd, argv[1], argv[2],
	    argv[1] != oldargv1 || argv[2] != oldargv2);
E 29
E 4
}

/*
D 3
 * Receive a single file.
E 3
I 3
D 5
 * Send one or more files.
E 5
I 5
 * Send multiple files.
E 5
E 3
 */
I 44
void
E 44
I 3
mput(argc, argv)
D 35
	char *argv[];
E 35
I 35
	int argc;
	char **argv;
E 35
{
I 35
D 44
	extern jmp_buf jabort;
E 35
D 4
	char **cpp, *dst;
E 4
I 4
D 7
	char **cpp, **gargs = NULL;
E 7
I 7
	register int i;
E 44
I 44
	int i;
E 44
I 35
	sig_t oldintr;
E 35
I 15
D 33
	int ointer, (*oldintr)(), mabort();
E 33
I 33
	int ointer;
D 35
	sig_t (*oldintr)(), mabort();
E 33
	extern jmp_buf jabort;
E 35
	char *tp;
I 35
D 44
	void mabort();
E 44
E 35
E 15
E 7
E 4
D 5
	int i;
E 5

D 4
	if (!connected) {
		printf("Not connected.\n");
		return;
E 4
I 4
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(local-files) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
E 4
	}
	if (argc < 2) {
D 4
		printf("%s local-file remote-file, or\n", argv[0]);
E 4
D 15
		printf("%s local-files\n", argv[0]);
E 15
I 15
		printf("usage:%s local-files\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "local-files")) {
		printf("usage: %s local-files\n", argv[0]);
E 37
		code = -1;
E 15
		return;
	}
I 15
	mname = argv[0];
	mflag = 1;
	oldintr = signal(SIGINT, mabort);
	(void) setjmp(jabort);
	if (proxy) {
		char *cp, *tp2, tmpbuf[MAXPATHLEN];

D 16
		while ((cp = remglob(argc, argv, 0)) != NULL) {
E 16
I 16
		while ((cp = remglob(argv,0)) != NULL) {
E 16
			if (*cp == 0) {
				mflag = 0;
				continue;
			}
			if (mflag && confirm(argv[0], cp)) {
				tp = cp;
				if (mcase) {
					while (*tp && !islower(*tp)) {
						tp++;
					}
					if (!*tp) {
						tp = cp;
						tp2 = tmpbuf;
						while ((*tp2 = *tp) != NULL) {
						     if (isupper(*tp2)) {
						        *tp2 = 'a' + *tp2 - 'A';
						     }
						     tp++;
						     tp2++;
						}
					}
					tp = tmpbuf;
				}
				if (ntflag) {
					tp = dotrans(tp);
				}
				if (mapflag) {
					tp = domap(tp);
				}
D 29
				sendrequest((sunique) ? "STOU" : "STOR", cp,tp);
E 29
I 29
				sendrequest((sunique) ? "STOU" : "STOR",
				    cp, tp, cp != tp || !interactive);
E 29
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm("Continue with","mput")) {
						mflag++;
					}
					interactive = ointer;
				}
			}
		}
		(void) signal(SIGINT, oldintr);
		mflag = 0;
		return;
	}
E 15
D 4
	if (argc == 3)  {
		if (!globulize(&argv[1]))
E 4
I 4
D 7
	cpp = argv + 1;
	if (doglob) {
		gargs = glob(cpp);
E 7
I 7
	for (i = 1; i < argc; i++) {
D 44
		register char **cpp, **gargs;
E 44
I 44
		char **cpp, **gargs;
I 47
		glob_t gl;
D 48
		int gflags;
E 48
I 48
		int flags;
E 48
E 47
E 44

		if (!doglob) {
D 15
			if (confirm(argv[0], argv[i]))
				sendrequest("STOR", argv[i], argv[i]);
E 15
I 15
			if (mflag && confirm(argv[0], argv[i])) {
				tp = (ntflag) ? dotrans(argv[i]) : argv[i];
				tp = (mapflag) ? domap(tp) : tp;
				sendrequest((sunique) ? "STOU" : "STOR",
D 29
				            argv[i], tp);
E 29
I 29
				    argv[i], tp, tp != argv[i] || !interactive);
E 29
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm("Continue with","mput")) {
						mflag++;
					}
					interactive = ointer;
				}
			}
E 15
			continue;
		}
D 39
		gargs = glob(argv[i]);
E 39
I 39
D 47
		gargs = ftpglob(argv[i]);
E 39
E 7
		if (globerr != NULL) {
			printf("%s\n", globerr);
D 22
			if (gargs)
E 22
I 22
			if (gargs) {
E 22
				blkfree(gargs);
I 22
D 33
				free(gargs);
E 33
I 33
				free((char *)gargs);
E 33
			}
E 47
I 47

		memset(&gl, 0, sizeof(gl));
D 48
		gflags = GLOB_BRACE|GLOB_QUOTE|GLOB_TILDE;
		if (glob(argv[i], gflags, NULL, &gl) || gl.gl_pathc == 0) {
E 48
I 48
		flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_QUOTE|GLOB_TILDE;
		if (glob(argv[i], flags, NULL, &gl) || gl.gl_pathc == 0) {
E 48
			warnx("%s: not found", argv[i]);
			globfree(&gl);
E 47
E 22
E 4
D 7
			return;
E 7
I 7
			continue;
E 7
D 4
		sendrequest("STOR", argv[1], argv[2]);
		return;
	}
	/*
	 * Check for shell metacharacters which we might
	 * want to expand into a list of file names.
	 */
	for (i = 1; i < argc; i++) {
		if (!doglob) {
			if (!skip(argv[0], argv[i]))
				sendrequest("STOR", argv[i], argv[i]);
			continue;
E 4
		}
I 7
D 15
		for (cpp = gargs; cpp && *cpp != NULL; cpp++)
			if (confirm(argv[0], *cpp))
				sendrequest("STOR", *cpp, *cpp);
E 15
I 15
D 47
		for (cpp = gargs; cpp && *cpp != NULL; cpp++) {
E 47
I 47
		for (cpp = gl.gl_pathv; cpp && *cpp != NULL; cpp++) {
E 47
			if (mflag && confirm(argv[0], *cpp)) {
				tp = (ntflag) ? dotrans(*cpp) : *cpp;
				tp = (mapflag) ? domap(tp) : tp;
				sendrequest((sunique) ? "STOU" : "STOR",
D 29
					   *cpp, tp);
E 29
I 29
				    *cpp, tp, *cpp != tp || !interactive);
E 29
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm("Continue with","mput")) {
						mflag++;
					}
					interactive = ointer;
				}
			}
		}
E 15
D 22
		if (gargs != NULL)
E 22
I 22
D 47
		if (gargs != NULL) {
E 22
			blkfree(gargs);
I 22
D 33
			free(gargs);
E 33
I 33
			free((char *)gargs);
E 33
		}
E 47
I 47
		globfree(&gl);
E 47
E 22
E 7
D 4
		cpp = glob(argv[i]);
		if (globerr != NULL) {
			printf("%s: %s\n", argv[i], globerr);
			if (cpp)
				blkfree(cpp);
			continue;
		}
		if (cpp == NULL) {
			printf("%s: no match\n", argv[i]);
			continue;
		}
		while (*cpp != NULL) {
			if (!skip(argv[0], *cpp))
				sendrequest("STOR", *cpp, *cpp);
			free(*cpp), cpp++;
		}
E 4
	}
I 15
	(void) signal(SIGINT, oldintr);
	mflag = 0;
E 15
I 4
D 7
	if (gargs != NULL)
		cpp = gargs;
	for (; *cpp != NULL; cpp++)
		if (confirm(argv[0], *cpp))
			sendrequest("STOR", *cpp, *cpp);
	if (gargs != NULL)
		blkfree(gargs);
E 7
E 4
}

I 44
void
E 44
I 26
D 27
#ifdef RESTART
E 26
I 24
reget(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
I 44

E 44
	(void) getit(argc, argv, 1, "r+w");
}
E 27

I 44
void
E 44
D 27
get(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
I 44

E 44
	(void) getit(argc, argv, 0, restart_point ? "r+w" : "w" );
}
I 26
#endif
E 26

E 27
E 24
/*
 * Receive one file.
 */
I 44
int
E 44
I 26
D 27
#ifdef RESTART
E 26
E 3
D 24
get(argc, argv)
E 24
I 24
getit(argc, argv, restartit, mode)
I 37
	int argc;
E 37
I 26
#else
E 27
get(argc, argv)
D 27
#endif
E 27
E 26
E 24
	char *argv[];
I 26
D 27
#ifdef RESTART
E 26
I 24
	char *mode;
I 44
	int restartit;
E 44
I 26
#endif
E 27
E 26
E 24
{
I 15
	int loc = 0;
I 29
	char *oldargv1, *oldargv2;
E 29
E 15
D 3
	int fd;
	register int n, addr;
	register char *cp;
	char *src;
E 3

D 4
	if (!connected) {
		printf("Not connected.\n");
		return;
	}
E 4
D 15
	if (argc == 2)
		argc++, argv[2] = argv[1];
E 15
I 15
	if (argc == 2) {
		argc++;
		argv[2] = argv[1];
		loc++;
	}
E 15
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(remote-file) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "remote-file"))
		goto usage;
	if (argc < 3 && !another(&argc, &argv, "local-file")) {
E 37
usage:
D 3
		printf("%s remote-file local-file\n", argv[0]);
E 3
I 3
D 15
		printf("%s remote-file [ local-file ]\n", argv[0]);
E 15
I 15
		printf("usage: %s remote-file [ local-file ]\n", argv[0]);
		code = -1;
I 26
D 27
#ifndef RESTART
E 27
		return;
D 27
#else
E 26
E 15
E 3
D 24
		return;
E 24
I 24
D 25
		return 0;
E 25
I 25
		return (0);
I 26
#endif
E 27
E 26
E 25
E 24
	}
D 37
	if (argc < 3) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(local-file) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 3) 
		goto usage;
E 37
I 29
	oldargv1 = argv[1];
	oldargv2 = argv[2];
E 29
I 3
D 15
	if (!globulize(&argv[2]))
E 15
I 15
	if (!globulize(&argv[2])) {
		code = -1;
I 26
D 27
#ifndef RESTART
E 27
		return;
D 27
#else
E 26
E 15
D 24
		return;
E 24
I 24
D 25
		return 0;
E 25
I 25
		return (0);
I 26
#endif
E 27
E 26
E 25
E 24
I 15
	}
	if (loc && mcase) {
		char *tp = argv[1], *tp2, tmpbuf[MAXPATHLEN];

		while (*tp && !islower(*tp)) {
			tp++;
		}
		if (!*tp) {
			tp = argv[2];
			tp2 = tmpbuf;
			while ((*tp2 = *tp) != NULL) {
				if (isupper(*tp2)) {
					*tp2 = 'a' + *tp2 - 'A';
				}
				tp++;
				tp2++;
			}
			argv[2] = tmpbuf;
		}
	}
D 25
	if (loc && ntflag) {
E 25
I 25
	if (loc && ntflag)
E 25
		argv[2] = dotrans(argv[2]);
D 25
	}
	if (loc && mapflag) {
E 25
I 25
	if (loc && mapflag)
E 25
		argv[2] = domap(argv[2]);
I 26
D 27
#ifdef RESTART
E 26
D 25
	}
E 25
E 15
E 3
D 4
	recvrequest("RETR", argv[2], argv[1]);
E 4
I 4
D 24
	recvrequest("RETR", argv[2], argv[1], "w");
E 24
I 24
	if (restartit) {
		struct stat stbuf;
		int ret;
I 25

E 25
		ret = stat(argv[2], &stbuf);
		if (restartit == 1) {
			if (ret < 0) {
D 34
				perror(argv[2]);
E 34
I 34
D 44
				fprintf(stderr, "local: %s: %s\n", argv[2],
					strerror(errno));
E 44
I 44
				warn("local: %s", argv[2]);
E 44
E 34
D 25
				return 0;
E 25
I 25
				return (0);
E 25
			}
			restart_point = stbuf.st_size;
		} else {
			if (ret == 0) {
				int overbose;
D 25
				overbose = verbose; verbose = -1;
E 25
I 25

				overbose = verbose;
				if (debug == 0)
					verbose = -1;
E 25
				if (command("MDTM %s", argv[1]) == COMPLETE) {
					int yy, mo, day, hour, min, sec;
					struct tm *tm;
					verbose = overbose;
					sscanf(reply_string,
					    "%*s %04d%02d%02d%02d%02d%02d",
					    &yy, &mo, &day, &hour, &min, &sec);
					tm = gmtime(&stbuf.st_mtime);
					tm->tm_mon++;
					if (tm->tm_year > yy%100)
D 25
						return 1;
E 25
I 25
						return (1);
E 25
D 41
					else if (tm->tm_year == yy%100) {
						if (tm->tm_mon > mo)
D 25
							return 1;
E 25
I 25
							return (1);
E 25
					} else if (tm->tm_mon == mo) {
						if (tm->tm_mday > day)
D 25
							return 1;
E 25
I 25
							return (1);
E 25
					} else if (tm->tm_mday == day) {
						if (tm->tm_hour > hour)
D 25
							return 1;
E 25
I 25
							return (1);
E 25
					} else if (tm->tm_hour == hour) {
						if (tm->tm_min > min)
D 25
							return 1;
E 25
I 25
							return (1);
E 25
					} else if (tm->tm_min == min) {
						if (tm->tm_sec > sec)
D 25
							return 1;
E 25
I 25
							return (1);
E 25
					}
E 41
I 41
					if ((tm->tm_year == yy%100 && 
					    tm->tm_mon > mo) ||
					   (tm->tm_mon == mo && 
					    tm->tm_mday > day) ||
					   (tm->tm_mday == day && 
					    tm->tm_hour > hour) ||
					   (tm->tm_hour == hour && 
					    tm->tm_min > min) ||
					   (tm->tm_min == min && 
					    tm->tm_sec > sec))
						return (1);
E 41
				} else {
D 33
					fputs(reply_string, stdout);
E 33
I 33
					printf("%s\n", reply_string);
E 33
					verbose = overbose;
D 25
					return 0;
E 25
I 25
					return (0);
E 25
				}
			}
		}
	}

D 29
	recvrequest("RETR", argv[2], argv[1], mode);
E 29
I 29
	recvrequest("RETR", argv[2], argv[1], mode,
	    argv[1] != oldargv1 || argv[2] != oldargv2);
E 29
	restart_point = 0;
D 25
	return 0;
E 25
I 25
	return (0);
I 26
#else
E 27
	recvrequest("RETR", argv[2], argv[1], "w");
D 27
#endif
E 27
E 26
E 25
E 24
E 4
}

I 44
/* ARGSUSED */
E 44
I 33
D 35
sig_t
E 35
I 35
void
E 35
E 33
I 15
D 44
mabort()
E 44
I 44
mabort(signo)
	int signo;
E 44
{
	int ointer;
D 44
	extern jmp_buf jabort;
E 44

	printf("\n");
	(void) fflush(stdout);
	if (mflag && fromatty) {
		ointer = interactive;
		interactive = 1;
		if (confirm("Continue with", mname)) {
			interactive = ointer;
			longjmp(jabort,0);
		}
		interactive = ointer;
	}
	mflag = 0;
	longjmp(jabort,0);
}

E 15
I 3
/*
 * Get multiple files.
 */
I 44
void
E 44
mget(argc, argv)
D 35
	char *argv[];
E 35
I 35
	int argc;
	char **argv;
E 35
{
D 4
	char temp[16], *dst, dstpath[MAXPATHLEN], buf[MAXPATHLEN];
	FILE *ftemp;
	int madedir = 0, oldverbose;
	struct stat stb;
E 4
I 4
D 5
	register char *cp;
E 5
I 5
D 15
	char *cp;
E 15
I 15
D 35
	char *cp, *tp, *tp2, tmpbuf[MAXPATHLEN];
D 33
	int ointer, (*oldintr)(), mabort();
E 33
I 33
	int ointer;
	sig_t (*oldintr)(), mabort();
E 35
E 33
D 44
	extern jmp_buf jabort;
E 44
I 35
	sig_t oldintr;
D 41
	int ointer;
E 41
I 41
	int ch, ointer;
E 41
	char *cp, *tp, *tp2, tmpbuf[MAXPATHLEN];
D 44
	void mabort();
E 44
E 35
E 15
E 5
E 4

D 4
	if (!connected) {
		printf("Not connected.\n");
		return;
	}
	if (argc == 2)
		argc++, argv[2] = argv[1];
E 4
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
D 5
		printf("(remote-directory) ");
E 5
I 5
		printf("(remote-files) ");
E 5
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
D 4
usage:
		printf("%s remote-directory [ local-directory ], or\n",
			argv[0]);
		printf("%s remote-files local-directory\n", argv[0]);
E 4
I 4
D 15
		printf("%s remote-files\n", argv[0]);
E 15
I 15
		printf("usage:%s remote-files\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "remote-files")) {
		printf("usage: %s remote-files\n", argv[0]);
E 37
		code = -1;
E 15
E 4
		return;
	}
D 4
	if (argc < 3) {
		strcat(line, " ");
		printf("(local-directory) ");
		gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
E 4
I 4
D 15
	while ((cp = remglob(argc, argv)) != NULL)
		if (confirm(argv[0], cp))
			recvrequest("RETR", cp, cp, "w");
E 15
I 15
	mname = argv[0];
	mflag = 1;
D 44
	oldintr = signal(SIGINT,mabort);
E 44
I 44
	oldintr = signal(SIGINT, mabort);
E 44
	(void) setjmp(jabort);
D 16
	while ((cp = remglob(argc, argv, proxy)) != NULL) {
E 16
I 16
	while ((cp = remglob(argv,proxy)) != NULL) {
E 16
		if (*cp == '\0') {
			mflag = 0;
			continue;
		}
		if (mflag && confirm(argv[0], cp)) {
			tp = cp;
			if (mcase) {
D 41
				while (*tp && !islower(*tp)) {
					tp++;
				}
				if (!*tp) {
					tp = cp;
					tp2 = tmpbuf;
					while ((*tp2 = *tp) != NULL) {
						if (isupper(*tp2)) {
							*tp2 = 'a' + *tp2 - 'A';
						}
						tp++;
						tp2++;
					}
				}
E 41
I 41
				for (tp2 = tmpbuf; ch = *tp++;)
					*tp2++ = isupper(ch) ? tolower(ch) : ch;
E 41
				tp = tmpbuf;
			}
			if (ntflag) {
				tp = dotrans(tp);
			}
			if (mapflag) {
				tp = domap(tp);
			}
D 29
			recvrequest("RETR", tp, cp, "w");
E 29
I 29
			recvrequest("RETR", tp, cp, "w",
			    tp != cp || !interactive);
E 29
			if (!mflag && fromatty) {
				ointer = interactive;
				interactive = 1;
				if (confirm("Continue with","mget")) {
					mflag++;
				}
				interactive = ointer;
			}
		}
	}
	(void) signal(SIGINT,oldintr);
	mflag = 0;
E 15
}

char *
D 15
remglob(argc, argv)
E 15
I 15
D 16
remglob(argc, argv, doswitch)
	int argc, doswitch;
E 16
I 16
remglob(argv,doswitch)
E 16
E 15
	char *argv[];
I 16
	int doswitch;
E 16
{
D 5
	char temp[16], *cp;
E 5
I 5
	char temp[16];
E 5
	static char buf[MAXPATHLEN];
	static FILE *ftemp = NULL;
	static char **args;
D 7
	int oldverbose;
E 7
I 7
	int oldverbose, oldhash;
E 7
I 5
	char *cp, *mode;
E 5

I 15
	if (!mflag) {
		if (!doglob) {
			args = NULL;
		}
		else {
			if (ftemp) {
D 16
				fclose(ftemp);
E 16
I 16
				(void) fclose(ftemp);
E 16
				ftemp = NULL;
			}
		}
D 44
		return(NULL);
E 44
I 44
		return (NULL);
E 44
	}
E 15
	if (!doglob) {
D 5
		if (argc == NULL)
E 5
I 5
		if (args == NULL)
E 5
			args = argv;
		if ((cp = *++args) == NULL)
			args = NULL;
		return (cp);
E 4
	}
D 4
	if (argc < 3) 
		goto usage;
	dst = argv[argc - 1];
	if (!globulize(&dst))
		return;
	/*
	 * If destination doesn't exist,
	 * try and create it.
	 */
	if (stat(dst, &stb) < 0) {
		if (mkdir(dst, 0777) < 0) {
			perror(dst);
E 4
I 4
	if (ftemp == NULL) {
D 16
		strcpy(temp, "/tmp/ftpXXXXXX");
		mktemp(temp);
E 16
I 16
D 31
		(void) strcpy(temp, "/tmp/ftpXXXXXX");
E 31
I 31
		(void) strcpy(temp, _PATH_TMP);
E 31
		(void) mktemp(temp);
E 16
		oldverbose = verbose, verbose = 0;
I 7
		oldhash = hash, hash = 0;
I 15
		if (doswitch) {
			pswitch(!proxy);
		}
E 15
E 7
D 5
		recvrequest("NLST", temp, argv[1], "w");
E 5
I 5
		for (mode = "w"; *++argv != NULL; mode = "a")
D 29
			recvrequest ("NLST", temp, *argv, mode);
E 29
I 29
			recvrequest ("NLST", temp, *argv, mode, 0);
E 29
I 15
		if (doswitch) {
			pswitch(!proxy);
		}
E 15
E 5
D 7
		verbose = oldverbose;
E 7
I 7
		verbose = oldverbose; hash = oldhash;
E 7
		ftemp = fopen(temp, "r");
D 16
		unlink(temp);
E 16
I 16
		(void) unlink(temp);
E 16
		if (ftemp == NULL) {
			printf("can't find list of remote files, oops\n");
E 4
D 5
			return;
E 5
I 5
			return (NULL);
E 5
		}
D 4
		madedir++;
	} else {
		if ((stb.st_mode & S_IFMT) != S_IFDIR) {
			printf("%s: not a directory\n", dst);
			return;
		}
E 4
	}
D 4
	/*
	 * Multiple files, just get each one without an nlst.
	 */
	if (argc > 3) {
		int i;

		for (i = 1; i < argc - 1; i++)
			recvrequest("RETR",
			  sprintf(dstpath, "%s/%s", dst, argv[i]), argv[i]);
		return;
E 4
I 4
	if (fgets(buf, sizeof (buf), ftemp) == NULL) {
D 16
		fclose(ftemp), ftemp = NULL;
E 16
I 16
		(void) fclose(ftemp), ftemp = NULL;
E 16
		return (NULL);
E 4
	}
D 4
	/*
	 * Get a directory full of files.  Perform an
	 * nlst to find the file names, then retrieve
	 * each individually.  If prompting is on, ask
	 * before grabbing each file.
	 */
	strcpy(temp, "/tmp/ftpXXXXXX");
	mktemp(temp);
	oldverbose = verbose, verbose = 0;
	recvrequest("NLST", temp, argv[1]);
	verbose = oldverbose;
	ftemp = fopen(temp, "r");
	unlink(temp);
	if (ftemp == NULL) {
		printf("can't find list of remote files, oops\n");
		if (madedir)
			(void) rmdir(dst);
		return;
	}
	while (fgets(buf, sizeof (buf), ftemp) != NULL) {
		char *cp = index(buf, '\n');

		if (cp)
			*cp = '\0';
		if (skip(argv[0], buf))
			continue;
		recvrequest("RETR", sprintf(dstpath, "%s/%s", dst, buf), buf);
	}
	fclose(ftemp);
E 4
I 4
D 44
	if ((cp = index(buf, '\n')) != NULL)
E 44
I 44
	if ((cp = strchr(buf, '\n')) != NULL)
E 44
		*cp = '\0';
	return (buf);
E 4
}

E 3
char *
onoff(bool)
	int bool;
{

	return (bool ? "on" : "off");
}

/*
 * Show status.
 */
I 16
/*ARGSUSED*/
I 44
void
E 44
E 16
status(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
I 15
	int i;
E 15

	if (connected)
		printf("Connected to %s.\n", hostname);
	else
		printf("Not connected.\n");
I 15
	if (!proxy) {
		pswitch(1);
		if (connected) {
			printf("Connected for proxy commands to %s.\n", hostname);
		}
		else {
			printf("No proxy connection.\n");
		}
		pswitch(0);
	}
E 15
	printf("Mode: %s; Type: %s; Form: %s; Structure: %s\n",
		modename, typename, formname, structname);
D 3
	printf("Verbose: %s; Bell: %s; Prompting: %s\n", 
		onoff(verbose), onoff(bell), onoff(interactive));
E 3
I 3
	printf("Verbose: %s; Bell: %s; Prompting: %s; Globbing: %s\n", 
		onoff(verbose), onoff(bell), onoff(interactive),
		onoff(doglob));
I 15
	printf("Store unique: %s; Receive unique: %s\n", onoff(sunique),
		onoff(runique));
	printf("Case: %s; CR stripping: %s\n",onoff(mcase),onoff(crflag));
	if (ntflag) {
		printf("Ntrans: (in) %s (out) %s\n", ntin,ntout);
	}
	else {
		printf("Ntrans: off\n");
	}
	if (mapflag) {
		printf("Nmap: (in) %s (out) %s\n", mapin, mapout);
	}
	else {
		printf("Nmap: off\n");
	}
E 15
I 4
D 7
	printf("Hash mark printing: %s; Use of PORT cmds: %s\n",
		onoff(hash), onoff(sendport));
E 7
I 7
D 9
	printf("Hash mark printing: %s; Use of PORT cmds: %s; Linger: %s\n",
		onoff(hash), onoff(sendport), onoff(linger));
E 9
I 9
	printf("Hash mark printing: %s; Use of PORT cmds: %s\n",
		onoff(hash), onoff(sendport));
I 15
	if (macnum > 0) {
		printf("Macros:\n");
		for (i=0; i<macnum; i++) {
			printf("\t%s\n",macros[i].mac_name);
		}
	}
	code = 0;
E 15
E 9
E 7
E 4
E 3
}

/*
 * Set beep on cmd completed mode.
 */
/*VARARGS*/
D 44
setbell()
E 44
I 44
void
setbell(argc, argv)
	int argc;
	char *argv[];
E 44
{

	bell = !bell;
	printf("Bell mode %s.\n", onoff(bell));
I 15
	code = bell;
E 15
}

/*
 * Turn on packet tracing.
 */
/*VARARGS*/
D 44
settrace()
E 44
I 44
void
settrace(argc, argv)
	int argc;
	char *argv[];
E 44
{

	trace = !trace;
	printf("Packet tracing %s.\n", onoff(trace));
I 15
	code = trace;
E 15
}

/*
I 4
 * Toggle hash mark printing during transfers.
 */
/*VARARGS*/
D 44
sethash()
E 44
I 44
void
sethash(argc, argv)
	int argc;
	char *argv[];
E 44
{

	hash = !hash;
	printf("Hash mark printing %s", onoff(hash));
I 15
	code = hash;
E 15
	if (hash)
D 28
		printf(" (%d bytes/hash mark)", BUFSIZ);
E 28
I 28
		printf(" (%d bytes/hash mark)", 1024);
E 28
	printf(".\n");
}

/*
E 4
 * Turn on printing of server echo's.
 */
/*VARARGS*/
D 44
setverbose()
E 44
I 44
void
setverbose(argc, argv)
	int argc;
	char *argv[];
E 44
{

	verbose = !verbose;
	printf("Verbose mode %s.\n", onoff(verbose));
I 15
	code = verbose;
E 15
}

/*
I 4
 * Toggle PORT cmd use before each data connection.
 */
/*VARARGS*/
D 44
setport()
E 44
I 44
void
setport(argc, argv)
	int argc;
	char *argv[];
E 44
{

	sendport = !sendport;
	printf("Use of PORT cmds %s.\n", onoff(sendport));
I 15
	code = sendport;
E 15
}

/*
E 4
 * Turn on interactive prompting
 * during mget, mput, and mdelete.
 */
/*VARARGS*/
D 44
setprompt()
E 44
I 44
void
setprompt(argc, argv)
	int argc;
	char *argv[];
E 44
{

	interactive = !interactive;
	printf("Interactive mode %s.\n", onoff(interactive));
I 15
	code = interactive;
E 15
}

/*
I 3
 * Toggle metacharacter interpretation
 * on local file names.
 */
/*VARARGS*/
D 44
setglob()
E 44
I 44
void
setglob(argc, argv)
	int argc;
	char *argv[];
E 44
{
	
	doglob = !doglob;
	printf("Globbing %s.\n", onoff(doglob));
I 15
	code = doglob;
E 15
}

/*
E 3
 * Set debugging mode on/off and/or
 * set level of debugging.
 */
I 5
/*VARARGS*/
I 44
void
E 44
E 5
D 3
/*VARARGS*/
E 3
setdebug(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
	int val;

	if (argc > 1) {
		val = atoi(argv[1]);
		if (val < 0) {
			printf("%s: bad debugging value.\n", argv[1]);
I 15
			code = -1;
E 15
			return;
		}
	} else
		val = !debug;
	debug = val;
	if (debug)
		options |= SO_DEBUG;
	else
		options &= ~SO_DEBUG;
	printf("Debugging %s (debug=%d).\n", onoff(debug), debug);
I 15
	code = debug > 0;
E 15
D 9
}

/*
I 7
 * Set linger on data connections on/off.
 */
/*VARARGS*/
setlinger(argc, argv)
	char *argv[];
{

	if (argc == 1)
		linger = !linger;
	else
		linger = atoi(argv[1]);
	if (argc == 1 || linger == 0) {
		printf("Linger on data connection close %s.\n", onoff(linger));
		return;
	}
	printf("Will linger for %d seconds on close of data connections.\n",
	   linger);
E 9
}

/*
E 7
 * Set current working directory
 * on remote machine.
 */
I 44
void
E 44
cd(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

D 5
	if (!connected) {
		printf("Not connected.\n");
		return;
	}
E 5
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(remote-directory) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
D 15
		printf("%s remote-directory\n", argv[0]);
E 15
I 15
		printf("usage:%s remote-directory\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "remote-directory")) {
		printf("usage: %s remote-directory\n", argv[0]);
E 37
		code = -1;
E 15
		return;
	}
D 28
	(void) command("CWD %s", argv[1]);
E 28
I 28
	if (command("CWD %s", argv[1]) == ERROR && code == 500) {
		if (verbose)
			printf("CWD command not recognized, trying XCWD\n");
		(void) command("XCWD %s", argv[1]);
	}
E 28
}

D 3
#include <pwd.h>

E 3
/*
 * Set current working directory
 * on local machine.
 */
I 44
void
E 44
lcd(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
D 3
	static struct passwd *pw = NULL;
E 3
I 3
	char buf[MAXPATHLEN];
I 33
D 44
	extern char *getwd();
E 44
E 33
D 5
	extern char *home;
E 5
E 3

D 3
	if (argc < 2) {
		if (pw == NULL) {
			pw = getpwnam(getlogin());
			if (pw == NULL)
				pw = getpwuid(getuid());
		}
		if (pw == NULL) {
			printf("ftp: can't find home directory.\n");
			return;
		}
		argc++, argv[1] = pw->pw_dir;
	}
E 3
I 3
	if (argc < 2)
		argc++, argv[1] = home;
E 3
	if (argc != 2) {
D 15
		printf("%s local-directory\n", argv[0]);
E 15
I 15
D 37
		printf("usage:%s local-directory\n", argv[0]);
E 37
I 37
		printf("usage: %s local-directory\n", argv[0]);
E 37
		code = -1;
E 15
		return;
	}
D 3
	if (chdir(argv[1]) < 0)
E 3
I 3
D 15
	if (!globulize(&argv[1]))
E 15
I 15
	if (!globulize(&argv[1])) {
		code = -1;
E 15
		return;
I 15
	}
E 15
	if (chdir(argv[1]) < 0) {
E 3
D 34
		perror(argv[1]);
E 34
I 34
D 44
		fprintf(stderr, "local: %s: %s\n", argv[1], strerror(errno));
E 44
I 44
		warn("local: %s", argv[1]);
E 44
E 34
I 15
		code = -1;
E 15
I 3
		return;
	}
D 47
	printf("Local directory now %s\n", getwd(buf));
E 47
I 47
	if (getwd(buf) != NULL)
		printf("Local directory now %s\n", buf);
	else
		warnx("getwd: %s", buf);
E 47
I 15
	code = 0;
E 15
E 3
}

/*
 * Delete a single file.
 */
I 44
void
E 44
delete(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(remote-file) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
D 15
		printf("%s remote-file\n", argv[0]);
E 15
I 15
		printf("usage:%s remote-file\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "remote-file")) {
		printf("usage: %s remote-file\n", argv[0]);
E 37
		code = -1;
E 15
		return;
	}
	(void) command("DELE %s", argv[1]);
}

/*
I 4
 * Delete multiple files.
 */
I 44
void
E 44
mdelete(argc, argv)
D 35
	char *argv[];
E 35
I 35
	int argc;
	char **argv;
E 35
{
D 35
	char *cp;
I 15
D 33
	int ointer, (*oldintr)(), mabort();
E 33
I 33
	int ointer;
	sig_t (*oldintr)(), mabort();
E 35
E 33
D 44
	extern jmp_buf jabort;
E 44
I 35
	sig_t oldintr;
	int ointer;
	char *cp;
D 44
	void mabort();
E 44
E 35
E 15

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(remote-files) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
D 15
		printf("%s remote-files\n", argv[0]);
E 15
I 15
		printf("usage:%s remote-files\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "remote-files")) {
		printf("usage: %s remote-files\n", argv[0]);
E 37
		code = -1;
E 15
		return;
	}
D 15
	while ((cp = remglob(argc, argv)) != NULL)
		if (confirm(argv[0], cp))
E 15
I 15
	mname = argv[0];
	mflag = 1;
	oldintr = signal(SIGINT, mabort);
	(void) setjmp(jabort);
D 16
	while ((cp = remglob(argc, argv, 0)) != NULL) {
E 16
I 16
	while ((cp = remglob(argv,0)) != NULL) {
E 16
		if (*cp == '\0') {
			mflag = 0;
			continue;
		}
		if (mflag && confirm(argv[0], cp)) {
E 15
			(void) command("DELE %s", cp);
I 15
			if (!mflag && fromatty) {
				ointer = interactive;
				interactive = 1;
				if (confirm("Continue with", "mdelete")) {
					mflag++;
				}
				interactive = ointer;
			}
		}
	}
	(void) signal(SIGINT, oldintr);
	mflag = 0;
E 15
}
I 5

E 5
/*
E 4
 * Rename a remote file.
 */
I 44
void
E 44
renamefile(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(from-name) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "from-name"))
		goto usage;
	if (argc < 3 && !another(&argc, &argv, "to-name")) {
E 37
usage:
		printf("%s from-name to-name\n", argv[0]);
I 15
		code = -1;
E 15
		return;
	}
D 37
	if (argc < 3) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(to-name) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 3) 
		goto usage;
E 37
	if (command("RNFR %s", argv[1]) == CONTINUE)
		(void) command("RNTO %s", argv[2]);
}

/*
 * Get a directory listing
 * of remote files.
 */
I 44
void
E 44
ls(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
D 4
	char *cmd;
E 4
I 4
D 5
	char *cmd, *mode;
	int i;
E 5
I 5
	char *cmd;
E 5
E 4

	if (argc < 2)
		argc++, argv[1] = NULL;
	if (argc < 3)
		argc++, argv[2] = "-";
I 5
	if (argc > 3) {
		printf("usage: %s remote-directory local-file\n", argv[0]);
I 15
		code = -1;
E 15
		return;
	}
E 5
D 4
	if (argc > 3) {
		printf("usage: %s remote-directory local-file\n", argv[0]);
		return;
	}
E 4
D 24
	cmd = argv[0][0] == 'l' ? "NLST" : "LIST";
E 24
I 24
	cmd = argv[0][0] == 'n' ? "NLST" : "LIST";
E 24
I 3
D 15
	if (strcmp(argv[2], "-") && !globulize(&argv[2]))
E 15
I 15
	if (strcmp(argv[2], "-") && !globulize(&argv[2])) {
		code = -1;
E 15
		return;
I 15
	}
I 17
	if (strcmp(argv[2], "-") && *argv[2] != '|')
		if (!globulize(&argv[2]) || !confirm("output to local-file:", argv[2])) {
			code = -1;
			return;
	}
E 17
E 15
E 3
D 4
	recvrequest(cmd, argv[2], argv[1]);
E 4
I 4
D 5
	mode = argc > 3 ? "a" : "w";
	for (i = 1; i < argc - 1; i++)
		recvrequest(cmd, argv[argc - 1], argv[i], mode);
E 5
I 5
D 29
	recvrequest(cmd, argv[2], argv[1], "w");
E 29
I 29
	recvrequest(cmd, argv[2], argv[1], "w", 0);
E 29
E 5
E 4
}

/*
I 5
 * Get a directory listing
 * of multiple remote files.
 */
I 44
void
E 44
mls(argc, argv)
D 35
	char *argv[];
E 35
I 35
	int argc;
	char **argv;
E 35
{
D 7
	char *cmd, *mode;
	int i, dest;
E 7
I 7
D 15
	char *cmd, *mode, *cp, *dest;
E 15
I 15
D 35
	char *cmd, mode[1], *dest;
D 33
	int ointer, i, (*oldintr)(), mabort();
E 33
I 33
	int ointer, i;
	sig_t (*oldintr)(), mabort();
E 35
E 33
D 44
	extern jmp_buf jabort;
E 44
I 35
	sig_t oldintr;
	int ointer, i;
	char *cmd, mode[1], *dest;
D 44
	void mabort();
E 44
E 35
E 15
E 7

D 7
	if (argc < 2)
		argc++, argv[1] = NULL;
	if (argc < 3)
		argc++, argv[2] = "-";
	dest = argc - 1;
	cmd = argv[0][1] == 'l' ? "NLST" : "LIST";
	if (strcmp(argv[dest], "-") != 0)
		if (globulize(&argv[dest]) && confirm("local-file", argv[dest]))
E 7
I 7
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(remote-files) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 3) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(local-file) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 3) {
D 15
		printf("%s remote-files local-file\n", argv[0]);
E 15
I 15
		printf("usage:%s remote-files local-file\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "remote-files"))
		goto usage;
	if (argc < 3 && !another(&argc, &argv, "local-file")) {
usage:
		printf("usage: %s remote-files local-file\n", argv[0]);
E 37
		code = -1;
E 15
		return;
	}
	dest = argv[argc - 1];
	argv[argc - 1] = NULL;
D 15
	if (strcmp(dest, "-"))
D 10
		if (globulize(&dest) && confirm("local-file", dest))
E 10
I 10
		if (!globulize(&dest) || !confirm("local-file", dest))
E 15
I 15
	if (strcmp(dest, "-") && *dest != '|')
D 37
		if (!globulize(&dest) || !confirm("output to local-file:", dest)) {
E 37
I 37
		if (!globulize(&dest) ||
		    !confirm("output to local-file:", dest)) {
E 37
			code = -1;
E 15
E 10
E 7
			return;
I 15
	}
E 15
D 7
	for (i = 1, mode = "w"; i < dest; i++, mode = "a")
		recvrequest(cmd, argv[dest], argv[i], mode);
E 7
I 7
D 24
	cmd = argv[0][1] == 'l' ? "NLST" : "LIST";
E 24
I 24
D 25
	cmd = argv[0][1] == 'n' ? "NLST" : "LIST";
E 25
I 25
	cmd = argv[0][1] == 'l' ? "NLST" : "LIST";
E 25
E 24
D 15
	for (mode = "w"; cp = remglob(argc, argv); mode = "a")
		if (confirm(argv[0], cp))
			recvrequest(cmd, dest, cp, mode);
E 15
I 15
	mname = argv[0];
	mflag = 1;
	oldintr = signal(SIGINT, mabort);
	(void) setjmp(jabort);
	for (i = 1; mflag && i < argc-1; ++i) {
		*mode = (i == 1) ? 'w' : 'a';
D 29
		recvrequest(cmd, dest, argv[i], mode);
E 29
I 29
		recvrequest(cmd, dest, argv[i], mode, 0);
E 29
		if (!mflag && fromatty) {
			ointer = interactive;
			interactive = 1;
			if (confirm("Continue with", argv[0])) {
				mflag ++;
			}
			interactive = ointer;
		}
	}
	(void) signal(SIGINT, oldintr);
	mflag = 0;
E 15
E 7
}

/*
E 5
 * Do a shell escape
 */
I 16
/*ARGSUSED*/
I 44
void
E 44
E 16
shell(argc, argv)
D 35
	char *argv[];
E 35
I 35
	int argc;
	char **argv;
E 35
{
I 5
D 15
	int pid, status, (*old1)(), (*old2)();
	char shellnam[40], *shell, *namep;
	char **cpp, **gargs;
E 15
I 15
D 16
	int i, pid, status, (*old1)(), (*old2)();
E 16
I 16
D 33
	int pid, (*old1)(), (*old2)();
E 33
I 33
D 44
	int pid;
E 44
I 44
	pid_t pid;
E 44
D 35
	sig_t (*old1)(), (*old2)();
E 35
I 35
	sig_t old1, old2;
E 35
E 33
E 16
	char shellnam[40], *shell, *namep; 
I 16
	union wait status;
E 16
E 15
E 5

D 5
	printf("Sorry, this function is unimplemented.\n");
E 5
I 5
	old1 = signal (SIGINT, SIG_IGN);
	old2 = signal (SIGQUIT, SIG_IGN);
	if ((pid = fork()) == 0) {
		for (pid = 3; pid < 20; pid++)
D 16
			close(pid);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
E 16
I 16
			(void) close(pid);
		(void) signal(SIGINT, SIG_DFL);
		(void) signal(SIGQUIT, SIG_DFL);
E 16
I 14
		shell = getenv("SHELL");
		if (shell == NULL)
D 31
			shell = "/bin/sh";
E 31
I 31
			shell = _PATH_BSHELL;
E 31
D 44
		namep = rindex(shell,'/');
E 44
I 44
		namep = strrchr(shell,'/');
E 44
		if (namep == NULL)
			namep = shell;
E 14
D 15
		if (argc <= 1) {
D 14
			shell = getenv("SHELL");
			if (shell == NULL)
				shell = "/bin/sh";
			namep = rindex(shell,'/');
			if (namep == NULL)
				namep = shell;
			strcpy(shellnam,"-");
			strcat(shellnam, ++namep);
			if (strcmp(namep, "sh") != 0)
				shellnam[0] = '+';
E 14
			if (debug) {
				printf ("%s\n", shell);
				fflush (stdout);
			}
D 14
			execl(shell, shellnam, 0);
			perror(shell);
			exit(1);
		}
		cpp = &argv[1];
		if (argc > 2) {
			if ((gargs = glob(cpp)) != NULL)
				cpp = gargs;
			if (globerr != NULL) {
				printf("%s\n", globerr);
				exit(1);
E 14
I 14
			execl(shell, shell, (char *)0);
		} else {
			char *args[4];	/* "sh" "-c" <command> NULL */

			args[0] = shell;
			args[1] = "-c";
			args[2] = argv[1];
			args[3] = NULL;
			if (debug) {
				printf("%s -c %s\n", shell, argv[1]);
				fflush(stdout);
E 14
			}
I 14
			execv(shell, args);
E 15
I 15
D 16
		strcpy(shellnam,"-");
		strcat(shellnam, ++namep);
E 16
I 16
		(void) strcpy(shellnam,"-");
		(void) strcat(shellnam, ++namep);
E 16
		if (strcmp(namep, "sh") != 0)
			shellnam[0] = '+';
		if (debug) {
			printf ("%s\n", shell);
D 16
			fflush (stdout);
E 16
I 16
			(void) fflush (stdout);
E 16
E 15
E 14
		}
I 15
		if (argc > 1) {
			execl(shell,shellnam,"-c",altarg,(char *)0);
		}
		else {
			execl(shell,shellnam,(char *)0);
		}
E 15
D 14
		if (debug) {
			register char **zip = cpp;

			printf("%s", *zip);
			while (*++zip != NULL)
				printf(" %s", *zip);
			printf("\n");
			fflush(stdout);
		}
		execvp(argv[1], cpp);
		perror(argv[1]);
E 14
I 14
D 44
		perror(shell);
E 44
I 44
		warn("%s", shell);
E 44
I 15
		code = -1;
E 15
E 14
		exit(1);
D 15
	}
E 15
I 15
D 44
		}
E 44
I 44
	}
E 44
E 15
	if (pid > 0)
D 38
		while (wait(&status) != pid)
E 38
I 38
		while (wait((int *)&status) != pid)
E 38
			;
D 16
	signal(SIGINT, old1);
	signal(SIGQUIT, old2);
E 16
I 16
	(void) signal(SIGINT, old1);
	(void) signal(SIGQUIT, old2);
E 16
D 15
	if (pid == -1)
E 15
I 15
	if (pid == -1) {
E 15
D 44
		perror("Try again later");
E 44
I 44
		warn("%s", "Try again later");
E 44
I 15
		code = -1;
	}
	else {
		code = 0;
	}
E 15
D 44
	return (0);
E 44
E 5
}

/*
 * Send new user information (re-login)
 */
I 44
void
E 44
user(argc, argv)
	int argc;
	char **argv;
{
D 16
	char acct[80], *getpass();
E 16
I 16
D 20
	char acct[80], *mygetpass();
E 20
I 20
D 44
	char acct[80], *getpass();
E 44
I 44
	char acct[80];
E 44
E 20
E 16
D 15
	int n;
E 15
I 15
	int n, aflag = 0;
E 15

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(username) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc > 4) {
E 37
I 37
	if (argc < 2)
		(void) another(&argc, &argv, "username");
	if (argc < 2 || argc > 4) {
E 37
		printf("usage: %s username [password] [account]\n", argv[0]);
I 15
		code = -1;
E 15
D 5
		return;
E 5
I 5
D 44
		return (0);
E 44
I 44
		return;
E 44
E 5
	}
	n = command("USER %s", argv[1]);
	if (n == CONTINUE) {
		if (argc < 3 )
D 16
			argv[2] = getpass("Password: "), argc++;
E 16
I 16
D 20
			argv[2] = mygetpass("Password: "), argc++;
E 20
I 20
			argv[2] = getpass("Password: "), argc++;
E 20
E 16
		n = command("PASS %s", argv[2]);
	}
	if (n == CONTINUE) {
		if (argc < 4) {
			printf("Account: "); (void) fflush(stdout);
			(void) fgets(acct, sizeof(acct) - 1, stdin);
			acct[strlen(acct) - 1] = '\0';
			argv[3] = acct; argc++;
		}
D 15
		n = command("ACCT %s", acct);
E 15
I 15
		n = command("ACCT %s", argv[3]);
		aflag++;
E 15
	}
	if (n != COMPLETE) {
D 16
		fprintf(stderr, "Login failed.\n");
E 16
I 16
		fprintf(stdout, "Login failed.\n");
E 16
D 44
		return (0);
E 44
I 44
		return;
E 44
	}
I 15
	if (!aflag && argc == 4) {
		(void) command("ACCT %s", argv[3]);
	}
E 15
D 44
	return (1);
E 44
}

/*
 * Print working directory.
 */
/*VARARGS*/
D 44
pwd()
E 44
I 44
void
pwd(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 28
	int oldverbose = verbose;
E 28
D 5
	if (!connected) {
		printf("Not connected.\n");
		return;
	}
E 5
I 5

E 5
D 15
	(void) command("XPWD");
E 15
I 15
D 28
	(void) command("PWD");
E 28
I 28
	/*
	 * If we aren't verbose, this doesn't do anything!
	 */
	verbose = 1;
	if (command("PWD") == ERROR && code == 500) {
		printf("PWD command not recognized, trying XPWD\n");
		(void) command("XPWD");
	}
	verbose = oldverbose;
E 28
E 15
}

/*
 * Make a directory.
 */
I 44
void
E 44
makedir(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(directory-name) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "directory-name")) {
E 37
D 15
		printf("%s directory-name\n", argv[0]);
E 15
I 15
		printf("usage: %s directory-name\n", argv[0]);
		code = -1;
E 15
		return;
	}
D 15
	(void) command("XMKD %s", argv[1]);
E 15
I 15
D 28
	(void) command("MKD %s", argv[1]);
E 28
I 28
	if (command("MKD %s", argv[1]) == ERROR && code == 500) {
		if (verbose)
			printf("MKD command not recognized, trying XMKD\n");
		(void) command("XMKD %s", argv[1]);
	}
E 28
E 15
}

/*
 * Remove a directory.
 */
I 44
void
E 44
removedir(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(directory-name) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "directory-name")) {
E 37
D 15
		printf("%s directory-name\n", argv[0]);
E 15
I 15
		printf("usage: %s directory-name\n", argv[0]);
		code = -1;
E 15
		return;
	}
D 15
	(void) command("XRMD %s", argv[1]);
E 15
I 15
D 28
	(void) command("RMD %s", argv[1]);
E 28
I 28
	if (command("RMD %s", argv[1]) == ERROR && code == 500) {
		if (verbose)
			printf("RMD command not recognized, trying XRMD\n");
		(void) command("XRMD %s", argv[1]);
	}
E 28
E 15
}

/*
 * Send a line, verbatim, to the remote machine.
 */
I 44
void
E 44
quote(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
D 37
	int i;
	char buf[BUFSIZ];
E 37

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(command line to send) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "command line to send")) {
E 37
		printf("usage: %s line-to-send\n", argv[0]);
I 15
		code = -1;
E 15
		return;
	}
D 16
	strcpy(buf, argv[1]);
E 16
I 16
D 37
	(void) strcpy(buf, argv[1]);
E 16
	for (i = 2; i < argc; i++) {
D 16
		strcat(buf, " ");
		strcat(buf, argv[i]);
E 16
I 16
		(void) strcat(buf, " ");
		(void) strcat(buf, argv[i]);
E 16
	}
D 15
	(void) command(buf);
E 15
I 15
	if (command(buf) == PRELIM) {
		while (getreply(0) == PRELIM);
	}
E 37
I 37
	quote1("", argc, argv);
E 37
E 15
}

/*
I 28
 * Send a SITE command to the remote machine.  The line
D 37
 * is sent almost verbatim to the remote machine, the
 * first argument is changed to SITE.
E 37
I 37
 * is sent verbatim to the remote machine, except that the
 * word "SITE" is added at the front.
E 37
 */
I 44
void
E 44
D 37

E 37
site(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
D 37
	int i;
	char buf[BUFSIZ];
E 37

D 37
	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(arguments to SITE command) ");
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "arguments to SITE command")) {
E 37
		printf("usage: %s line-to-send\n", argv[0]);
		code = -1;
		return;
	}
D 37
	(void) strcpy(buf, "SITE ");
	(void) strcat(buf, argv[1]);
	for (i = 2; i < argc; i++) {
		(void) strcat(buf, " ");
		(void) strcat(buf, argv[i]);
E 37
I 37
	quote1("SITE ", argc, argv);
}

/*
 * Turn argv[1..argc) into a space-separated string, then prepend initial text.
 * Send the result as a one-line command and get response.
 */
I 44
void
E 44
quote1(initial, argc, argv)
	char *initial;
	int argc;
	char **argv;
{
D 44
	register int i, len;
E 44
I 44
	int i, len;
E 44
	char buf[BUFSIZ];		/* must be >= sizeof(line) */

	(void) strcpy(buf, initial);
	if (argc > 1) {
		len = strlen(buf);
		len += strlen(strcpy(&buf[len], argv[1]));
		for (i = 2; i < argc; i++) {
			buf[len++] = ' ';
			len += strlen(strcpy(&buf[len], argv[i]));
		}
E 37
	}
	if (command(buf) == PRELIM) {
D 44
		while (getreply(0) == PRELIM);
E 44
I 44
		while (getreply(0) == PRELIM)
			continue;
E 44
	}
}

I 44
void
E 44
do_chmod(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
D 37
	if (argc == 2) {
E 37
I 37

	if (argc < 2 && !another(&argc, &argv, "mode"))
		goto usage;
	if (argc < 3 && !another(&argc, &argv, "file-name")) {
usage:
E 37
		printf("usage: %s mode file-name\n", argv[0]);
		code = -1;
		return;
	}
D 37
	if (argc < 3) {
		(void) strcat(line, " ");
		printf("(mode and file-name) ");
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc != 3) {
		printf("usage: %s mode file-name\n", argv[0]);
		code = -1;
		return;
	}
	(void)command("SITE CHMOD %s %s", argv[1], argv[2]);
E 37
I 37
	(void) command("SITE CHMOD %s %s", argv[1], argv[2]);
E 37
}

I 44
void
E 44
do_umask(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
	int oldverbose = verbose;

	verbose = 1;
	(void) command(argc == 1 ? "SITE UMASK" : "SITE UMASK %s", argv[1]);
	verbose = oldverbose;
}

I 44
void
E 44
idle(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
	int oldverbose = verbose;

	verbose = 1;
	(void) command(argc == 1 ? "SITE IDLE" : "SITE IDLE %s", argv[1]);
	verbose = oldverbose;
}

/*
E 28
 * Ask the other side for help.
 */
I 44
void
E 44
rmthelp(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
	int oldverbose = verbose;

	verbose = 1;
	(void) command(argc == 1 ? "HELP" : "HELP %s", argv[1]);
	verbose = oldverbose;
}

/*
 * Terminate session and exit.
 */
/*VARARGS*/
D 44
quit()
E 44
I 44
void
quit(argc, argv)
	int argc;
	char *argv[];
E 44
{

D 11
	disconnect();
E 11
I 11
	if (connected)
D 44
		disconnect();
E 44
I 44
		disconnect(0, 0);
E 44
I 15
	pswitch(1);
	if (connected) {
D 44
		disconnect();
E 44
I 44
		disconnect(0, 0);
E 44
	}
E 15
E 11
	exit(0);
}

/*
 * Terminate session, but don't exit.
 */
D 44
disconnect()
E 44
I 44
void
disconnect(argc, argv)
	int argc;
	char *argv[];
E 44
{
D 44
	extern FILE *cout;
	extern int data;
E 44

	if (!connected)
		return;
	(void) command("QUIT");
D 15
	(void) fclose(cout);
E 15
I 15
	if (cout) {
		(void) fclose(cout);
	}
E 15
	cout = NULL;
	connected = 0;
	data = -1;
I 15
	if (!proxy) {
		macnum = 0;
	}
E 15
I 3
}

I 44
int
E 44
D 4
skip(cmd, file)
E 4
I 4
confirm(cmd, file)
E 4
	char *cmd, *file;
{
	char line[BUFSIZ];

	if (!interactive)
D 4
		return (0);
E 4
I 4
		return (1);
E 4
	printf("%s %s? ", cmd, file);
D 16
	fflush(stdout);
	gets(line);
E 16
I 16
	(void) fflush(stdout);
D 37
	(void) gets(line);
E 37
I 37
	if (fgets(line, sizeof line, stdin) == NULL)
		return (0);
E 37
E 16
D 4
	return (*line == 'y');
E 4
I 4
	return (*line != 'n' && *line != 'N');
E 4
}

I 44
void
E 44
fatal(msg)
	char *msg;
{

D 16
	fprintf(stderr, "ftp: %s\n");
E 16
I 16
D 44
	fprintf(stderr, "ftp: %s\n", msg);
E 16
	exit(1);
E 44
I 44
	errx(1, "%s", msg);
E 44
}

/*
 * Glob a local file name specification with
 * the expectation of a single return value.
 * Can't control multiple values being expanded
 * from the expression, we return only the first.
 */
I 44
int
E 44
globulize(cpp)
	char **cpp;
{
D 47
	char **globbed;
E 47
I 47
	glob_t gl;
I 48
	int flags;
E 48
E 47

	if (!doglob)
		return (1);
D 39
	globbed = glob(*cpp);
E 39
I 39
D 47
	globbed = ftpglob(*cpp);
E 39
	if (globerr != NULL) {
		printf("%s: %s\n", *cpp, globerr);
D 22
		if (globbed)
E 22
I 22
		if (globbed) {
E 22
			blkfree(globbed);
I 22
D 33
			free(globbed);
E 33
I 33
			free((char *)globbed);
E 33
		}
E 47
I 47

I 48
	flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_QUOTE|GLOB_TILDE;
E 48
	memset(&gl, 0, sizeof(gl));
D 48
	if (glob(*cpp, GLOB_BRACE|GLOB_QUOTE|GLOB_TILDE, NULL, &gl) ||
E 48
I 48
	if (glob(*cpp, flags, NULL, &gl) ||
E 48
	    gl.gl_pathc == 0) {
		warnx("%s: not found", *cpp);
		globfree(&gl);
E 47
E 22
		return (0);
	}
D 47
	if (globbed) {
		*cpp = *globbed++;
		/* don't waste too much memory */
D 22
		if (*globbed)
E 22
I 22
D 44
		if (*globbed) {
E 22
D 40
			blkfree(globbed);
I 22
D 33
			free(globbed);
E 33
I 33
			free((char *)globbed);
E 40
I 40
			blkfree(*globbed);
E 44
I 44
		if (globbed) {
			blkfree(globbed);
E 44
			free((char *)*globbed);
E 40
E 33
		}
E 22
	}
E 47
I 47
	*cpp = strdup(gl.gl_pathv[0]);	/* XXX - wasted memory */
	globfree(&gl);
E 47
	return (1);
I 15
}

I 44
void
E 44
account(argc,argv)
D 21

E 21
	int argc;
	char **argv;
{
D 16
	char acct[50], *getpass(), *ap;
E 16
I 16
D 20
	char acct[50], *mygetpass(), *ap;
E 20
I 20
D 47
	char acct[50], *getpass(), *ap;
E 47
I 47
	char acct[50], *ap;
E 47
E 20
E 16

	if (argc > 1) {
		++argv;
		--argc;
		(void) strncpy(acct,*argv,49);
D 21
		acct[50] = '\0';
E 21
I 21
		acct[49] = '\0';
E 21
		while (argc > 1) {
			--argc;
			++argv;
			(void) strncat(acct,*argv, 49-strlen(acct));
		}
		ap = acct;
	}
	else {
D 16
		ap = getpass("Account:");
E 16
I 16
D 20
		ap = mygetpass("Account:");
E 20
I 20
		ap = getpass("Account:");
E 20
E 16
	}
	(void) command("ACCT %s", ap);
}

jmp_buf abortprox;

I 33
D 35
sig_t
E 35
I 35
void
E 35
E 33
proxabort()
{
D 44
	extern int proxy;
E 44

	if (!proxy) {
		pswitch(1);
	}
	if (connected) {
		proxflag = 1;
	}
	else {
		proxflag = 0;
	}
	pswitch(0);
	longjmp(abortprox,1);
}

D 44
doproxy(argc,argv)
E 44
I 44
void
doproxy(argc, argv)
E 44
	int argc;
	char *argv[];
{
D 33
	int (*oldintr)(), proxabort();
E 33
I 33
D 35
	sig_t (*oldintr)(), proxabort();
E 33
	register struct cmd *c;
	struct cmd *getcmd();
E 35
D 44
	extern struct cmd cmdtab[];
	extern jmp_buf abortprox;
I 35
	register struct cmd *c;
	struct cmd *getcmd();
E 44
I 44
	struct cmd *c;
E 44
	sig_t oldintr;
D 44
	void proxabort();
E 44
E 35

D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(command) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage:%s command\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "command")) {
		printf("usage: %s command\n", argv[0]);
E 37
		code = -1;
		return;
	}
	c = getcmd(argv[1]);
	if (c == (struct cmd *) -1) {
		printf("?Ambiguous command\n");
D 16
		fflush(stdout);
E 16
I 16
		(void) fflush(stdout);
E 16
		code = -1;
		return;
	}
	if (c == 0) {
		printf("?Invalid command\n");
D 16
		fflush(stdout);
E 16
I 16
		(void) fflush(stdout);
E 16
		code = -1;
		return;
	}
	if (!c->c_proxy) {
		printf("?Invalid proxy command\n");
D 16
		fflush(stdout);
E 16
I 16
		(void) fflush(stdout);
E 16
		code = -1;
		return;
	}
	if (setjmp(abortprox)) {
		code = -1;
		return;
	}
	oldintr = signal(SIGINT, proxabort);
	pswitch(1);
	if (c->c_conn && !connected) {
		printf("Not connected\n");
D 16
		fflush(stdout);
E 16
I 16
		(void) fflush(stdout);
E 16
		pswitch(0);
		(void) signal(SIGINT, oldintr);
		code = -1;
		return;
	}
	(*c->c_handler)(argc-1, argv+1);
	if (connected) {
		proxflag = 1;
	}
	else {
		proxflag = 0;
	}
	pswitch(0);
	(void) signal(SIGINT, oldintr);
}

D 44
setcase()
E 44
I 44
void
setcase(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
	mcase = !mcase;
	printf("Case mapping %s.\n", onoff(mcase));
	code = mcase;
}

D 44
setcr()
E 44
I 44
void
setcr(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
	crflag = !crflag;
	printf("Carriage Return stripping %s.\n", onoff(crflag));
	code = crflag;
}

I 44
void
E 44
setntrans(argc,argv)
	int argc;
	char *argv[];
{
	if (argc == 1) {
		ntflag = 0;
		printf("Ntrans off.\n");
		code = ntflag;
		return;
	}
	ntflag++;
	code = ntflag;
	(void) strncpy(ntin, argv[1], 16);
	ntin[16] = '\0';
	if (argc == 2) {
		ntout[0] = '\0';
		return;
	}
	(void) strncpy(ntout, argv[2], 16);
	ntout[16] = '\0';
}

char *
dotrans(name)
	char *name;
{
	static char new[MAXPATHLEN];
	char *cp1, *cp2 = new;
D 44
	register int i, ostop, found;
E 44
I 44
	int i, ostop, found;
E 44

D 44
	for (ostop = 0; *(ntout + ostop) && ostop < 16; ostop++);
E 44
I 44
	for (ostop = 0; *(ntout + ostop) && ostop < 16; ostop++)
		continue;
E 44
	for (cp1 = name; *cp1; cp1++) {
		found = 0;
		for (i = 0; *(ntin + i) && i < 16; i++) {
			if (*cp1 == *(ntin + i)) {
				found++;
				if (i < ostop) {
					*cp2++ = *(ntout + i);
				}
				break;
			}
		}
		if (!found) {
			*cp2++ = *cp1;
		}
	}
	*cp2 = '\0';
D 44
	return(new);
E 44
I 44
	return (new);
E 44
}

I 44
void
E 44
setnmap(argc, argv)
	int argc;
	char *argv[];
{
	char *cp;

	if (argc == 1) {
		mapflag = 0;
		printf("Nmap off.\n");
		code = mapflag;
		return;
	}
D 37
	if (argc < 3) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(mapout) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 3) {
E 37
I 37
	if (argc < 3 && !another(&argc, &argv, "mapout")) {
E 37
		printf("Usage: %s [mapin mapout]\n",argv[0]);
		code = -1;
		return;
	}
	mapflag = 1;
	code = 1;
D 44
	cp = index(altarg, ' ');
E 44
I 44
	cp = strchr(altarg, ' ');
E 44
	if (proxy) {
D 44
		while(*++cp == ' ');
E 44
I 44
		while(*++cp == ' ')
			continue;
E 44
		altarg = cp;
D 44
		cp = index(altarg, ' ');
E 44
I 44
		cp = strchr(altarg, ' ');
E 44
	}
	*cp = '\0';
	(void) strncpy(mapin, altarg, MAXPATHLEN - 1);
D 44
	while (*++cp == ' ');
E 44
I 44
	while (*++cp == ' ')
		continue;
E 44
	(void) strncpy(mapout, cp, MAXPATHLEN - 1);
}

char *
domap(name)
	char *name;
{
	static char new[MAXPATHLEN];
D 44
	register char *cp1 = name, *cp2 = mapin;
E 44
I 44
	char *cp1 = name, *cp2 = mapin;
E 44
	char *tp[9], *te[9];
D 23
	int i, toks[9], toknum, match = 1;
E 23
I 23
	int i, toks[9], toknum = 0, match = 1;
E 23

	for (i=0; i < 9; ++i) {
		toks[i] = 0;
	}
	while (match && *cp1 && *cp2) {
		switch (*cp2) {
			case '\\':
				if (*++cp2 != *cp1) {
					match = 0;
				}
				break;
			case '$':
				if (*(cp2+1) >= '1' && (*cp2+1) <= '9') {
					if (*cp1 != *(++cp2+1)) {
						toks[toknum = *cp2 - '1']++;
						tp[toknum] = cp1;
						while (*++cp1 && *(cp2+1)
							!= *cp1);
						te[toknum] = cp1;
					}
					cp2++;
					break;
				}
D 24
				/* intentional drop through */
E 24
I 24
				/* FALLTHROUGH */
E 24
			default:
				if (*cp2 != *cp1) {
					match = 0;
				}
				break;
		}
D 23
		if (*cp1) {
E 23
I 23
		if (match && *cp1) {
E 23
			cp1++;
		}
D 23
		if (*cp2) {
E 23
I 23
		if (match && *cp2) {
E 23
			cp2++;
		}
I 23
	}
	if (!match && *cp1) /* last token mismatch */
	{
		toks[toknum] = 0;
E 23
	}
	cp1 = new;
	*cp1 = '\0';
	cp2 = mapout;
	while (*cp2) {
		match = 0;
		switch (*cp2) {
			case '\\':
				if (*(cp2 + 1)) {
					*cp1++ = *++cp2;
				}
				break;
			case '[':
LOOP:
				if (*++cp2 == '$' && isdigit(*(cp2+1))) { 
					if (*++cp2 == '0') {
						char *cp3 = name;

						while (*cp3) {
							*cp1++ = *cp3++;
						}
						match = 1;
					}
					else if (toks[toknum = *cp2 - '1']) {
						char *cp3 = tp[toknum];

						while (cp3 != te[toknum]) {
							*cp1++ = *cp3++;
						}
						match = 1;
					}
				}
				else {
					while (*cp2 && *cp2 != ',' && 
					    *cp2 != ']') {
						if (*cp2 == '\\') {
							cp2++;
						}
						else if (*cp2 == '$' &&
   						        isdigit(*(cp2+1))) {
							if (*++cp2 == '0') {
							   char *cp3 = name;

							   while (*cp3) {
								*cp1++ = *cp3++;
							   }
							}
							else if (toks[toknum =
							    *cp2 - '1']) {
							   char *cp3=tp[toknum];

							   while (cp3 !=
								  te[toknum]) {
								*cp1++ = *cp3++;
							   }
							}
						}
						else if (*cp2) {
							*cp1++ = *cp2++;
						}
					}
					if (!*cp2) {
						printf("nmap: unbalanced brackets\n");
D 44
						return(name);
E 44
I 44
						return (name);
E 44
					}
					match = 1;
					cp2--;
				}
				if (match) {
					while (*++cp2 && *cp2 != ']') {
					      if (*cp2 == '\\' && *(cp2 + 1)) {
							cp2++;
					      }
					}
					if (!*cp2) {
						printf("nmap: unbalanced brackets\n");
D 44
						return(name);
E 44
I 44
						return (name);
E 44
					}
					break;
				}
				switch (*++cp2) {
					case ',':
						goto LOOP;
					case ']':
						break;
					default:
						cp2--;
						goto LOOP;
				}
				break;
			case '$':
				if (isdigit(*(cp2 + 1))) {
					if (*++cp2 == '0') {
						char *cp3 = name;

						while (*cp3) {
							*cp1++ = *cp3++;
						}
					}
					else if (toks[toknum = *cp2 - '1']) {
						char *cp3 = tp[toknum];

						while (cp3 != te[toknum]) {
							*cp1++ = *cp3++;
						}
					}
					break;
				}
				/* intentional drop through */
			default:
				*cp1++ = *cp2;
				break;
		}
		cp2++;
	}
	*cp1 = '\0';
	if (!*new) {
D 44
		return(name);
E 44
I 44
		return (name);
E 44
	}
D 44
	return(new);
E 44
I 44
	return (new);
E 44
}

D 44
setsunique()
E 44
I 44
void
I 49
setpassive(argc, argv)
	int argc;
	char *argv[];
{

	passivemode = !passivemode;
	printf("Passive mode %s.\n", onoff(passivemode));
	code = passivemode;
}

void
E 49
setsunique(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
	sunique = !sunique;
	printf("Store unique %s.\n", onoff(sunique));
	code = sunique;
}

D 44
setrunique()
E 44
I 44
void
setrunique(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
	runique = !runique;
	printf("Receive unique %s.\n", onoff(runique));
	code = runique;
}

/* change directory to perent directory */
D 44
cdup()
E 44
I 44
void
cdup(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
D 28
	(void) command("CDUP");
E 28
I 28
	if (command("CDUP") == ERROR && code == 500) {
		if (verbose)
			printf("CDUP command not recognized, trying XCUP\n");
		(void) command("XCUP");
	}
E 28
}

I 26
D 27
#ifdef RESTART
E 26
I 24
/* restart transfer at specific point */
I 44
void
E 44
restart(argc, argv)
	int argc;
	char *argv[];
{
D 44
	extern long atol();
E 44
I 44

E 44
	if (argc != 2)
		printf("restart: offset not specified\n");
	else {
		restart_point = atol(argv[1]);
D 25
		printf("restarting at %ld. execute get, put or append to initiate transfer\n",
			restart_point);
E 25
I 25
D 44
		printf("restarting at %ld. %s\n", restart_point,
E 44
I 44
		printf("restarting at %qd. %s\n", restart_point,
E 44
		    "execute get, put or append to initiate transfer");
E 25
	}
}
I 26
#endif
E 27
E 26

/* show remote system type */
D 44
syst()
E 44
I 44
void
syst(argc, argv)
	int argc;
	char *argv[];
E 44
{
I 44

E 44
	(void) command("SYST");
}

I 44
void
E 44
E 24
macdef(argc, argv)
	int argc;
	char *argv[];
{
	char *tmp;
	int c;

	if (macnum == 16) {
		printf("Limit of 16 macros have already been defined\n");
		code = -1;
		return;
	}
D 37
	if (argc < 2) {
D 16
		strcat(line, " ");
E 16
I 16
		(void) strcat(line, " ");
E 16
		printf("(macro name) ");
D 16
		gets(&line[strlen(line)]);
E 16
I 16
		(void) gets(&line[strlen(line)]);
E 16
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc != 2) {
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "macro name")) {
E 37
		printf("Usage: %s macro_name\n",argv[0]);
		code = -1;
		return;
	}
	if (interactive) {
		printf("Enter macro line by line, terminating it with a null line\n");
	}
D 16
	strncpy(macros[macnum].mac_name, argv[1], 8);
E 16
I 16
	(void) strncpy(macros[macnum].mac_name, argv[1], 8);
E 16
	if (macnum == 0) {
		macros[macnum].mac_start = macbuf;
	}
	else {
		macros[macnum].mac_start = macros[macnum - 1].mac_end + 1;
	}
	tmp = macros[macnum].mac_start;
	while (tmp != macbuf+4096) {
		if ((c = getchar()) == EOF) {
			printf("macdef:end of file encountered\n");
			code = -1;
			return;
		}
		if ((*tmp = c) == '\n') {
			if (tmp == macros[macnum].mac_start) {
				macros[macnum++].mac_end = tmp;
				code = 0;
				return;
			}
			if (*(tmp-1) == '\0') {
				macros[macnum++].mac_end = tmp - 1;
				code = 0;
				return;
			}
			*tmp = '\0';
		}
		tmp++;
	}
	while (1) {
D 24
		while ((c = getchar()) != '\n' && c != EOF);
E 24
I 24
		while ((c = getchar()) != '\n' && c != EOF)
			/* LOOP */;
E 24
		if (c == EOF || getchar() == '\n') {
			printf("Macro not defined - 4k buffer exceeded\n");
			code = -1;
			return;
		}
	}
I 24
}

/*
 * get size of file on remote machine
 */
I 44
void
E 44
sizecmd(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{

D 37
	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(filename) ");
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage:%s filename\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "filename")) {
		printf("usage: %s filename\n", argv[0]);
E 37
		code = -1;
		return;
	}
	(void) command("SIZE %s", argv[1]);
}

/*
 * get last modification time of file on remote machine
 */
I 44
void
E 44
modtime(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
	int overbose;

D 37
	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(filename) ");
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage:%s filename\n", argv[0]);
E 37
I 37
	if (argc < 2 && !another(&argc, &argv, "filename")) {
		printf("usage: %s filename\n", argv[0]);
E 37
		code = -1;
		return;
	}
D 25
	overbose = verbose; verbose = -1;
E 25
I 25
	overbose = verbose;
	if (debug == 0)
		verbose = -1;
E 25
	if (command("MDTM %s", argv[1]) == COMPLETE) {
		int yy, mo, day, hour, min, sec;
		sscanf(reply_string, "%*s %04d%02d%02d%02d%02d%02d", &yy, &mo,
			&day, &hour, &min, &sec);
		/* might want to print this in local time */
		printf("%s\t%02d/%02d/%04d %02d:%02d:%02d GMT\n", argv[1],
			mo, day, yy, hour, min, sec);
	} else
D 33
		fputs(reply_string, stdout);
E 33
I 33
		printf("%s\n", reply_string);
E 33
	verbose = overbose;
}

/*
D 26
 * show status on reomte machine
E 26
I 26
 * show status on remote machine
E 26
 */
I 44
void
E 44
rmtstatus(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
I 44

E 44
	(void) command(argc > 1 ? "STAT %s" : "STAT" , argv[1]);
}
I 26
D 27
#ifdef RESTART
E 26

/*
 * get file if modtime is more recent than current file
 */
I 44
void
E 44
newer(argc, argv)
I 37
	int argc;
E 37
	char *argv[];
{
I 44

E 44
	if (getit(argc, argv, -1, "w"))
		printf("Local file \"%s\" is newer than remote file \"%s\"\n",
D 42
			argv[1], argv[2]);
E 42
I 42
			argv[2], argv[1]);
E 42
E 24
E 15
E 3
}
I 26
#endif
E 27
E 26
E 1
