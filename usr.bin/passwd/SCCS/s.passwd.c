h22972
s 00002/00002/00090
d D 8.3 94/04/02 09:47:03 pendry 52 51
c add 1994 copyright
e
s 00019/00020/00073
d D 8.2 94/04/02 09:35:27 pendry 51 50
c prettyness police
e
s 00005/00005/00088
d D 8.1 93/06/06 15:49:30 bostic 50 49
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00001/00087
d D 5.7 93/03/02 17:07:27 bostic 49 48
c getlogin() can theoretically fail
e
s 00001/00001/00087
d D 5.6 91/12/07 12:52:28 bostic 48 47
c argv[1] should be argv[0]
e
s 00004/00002/00084
d D 5.5 91/07/06 14:09:02 karels 47 46
c clarify error message (nobody understood the old one)
e
s 00004/00001/00082
d D 5.4 91/03/14 13:42:12 bostic 46 45
c always use getopt(3)
e
s 00016/00257/00067
d D 5.3 91/02/12 22:16:29 bostic 45 44
c rework the password subsystem
e
s 00002/00003/00322
d D 5.2 91/02/03 13:52:34 bostic 44 43
c structure not &structure in call to bzero; minor lint
e
s 00001/00262/00324
d D 5.1 91/02/03 13:36:11 bostic 43 42
c break Kerberos code out into krb_passwd.c
e
s 00004/00004/00582
d D 4.42 90/06/19 17:05:37 kfall 42 41
c fix argv for getopt
e
s 00315/00003/00271
d D 4.41 90/06/18 19:24:03 kfall 41 40
c 1st cut at kerberized passwd
e
s 00001/00011/00273
d D 4.40 90/06/01 17:28:22 bostic 40 39
c new copyright notice
e
s 00001/00001/00283
d D 4.39 90/05/15 19:54:40 bostic 39 38
c string.h is ANSI C include file
e
s 00024/00005/00260
d D 4.38 89/09/18 14:59:42 bostic 38 37
c minor editing; get read for Tom Truscott's new crypt
c original rewrite code was wrong in that it picked salt letters from too
c large an alphabet -- hopefully it hasn't been distributed over too large
c an area, although the shadow password package has it.
e
s 00015/00016/00250
d D 4.37 89/09/07 09:51:46 karels 37 36
c root gets to pick any passwd!  Use getlogin(): can now be trusted,
c but don't have to trust it anyway.
e
s 00004/00003/00262
d D 4.36 89/05/05 15:33:46 bostic 36 35
c use waitpid to get status
e
s 00001/00001/00264
d D 4.35 89/03/16 22:29:48 bostic 35 34
c use passwd.{pag,dir}
e
s 00023/00009/00242
d D 4.34 89/02/23 19:05:22 bostic 34 33
c setting the password clears the change value
e
s 00185/00594/00066
d D 4.33 89/02/22 17:22:32 bostic 33 32
c shadow passwords
e
s 00006/00004/00654
d D 4.32 88/01/21 10:26:40 bostic 32 31
c could indirect through uninitialized pointer
e
s 00007/00007/00651
d D 4.31 87/12/21 11:14:01 bostic 31 30
c make ANSI C compatible
e
s 00006/00002/00652
d D 4.30 87/11/30 12:47:33 bostic 30 29
c remove checkpass; just check for all lower case
e
s 00010/00008/00644
d D 4.29 87/10/06 21:53:24 bostic 29 28
c disallow ',' in gcos field; bug report 4.3BSD/bin/88
e
s 00143/00181/00509
d D 4.28 87/10/06 19:02:13 bostic 28 27
c don't use getlogin ever, use getuid instead 
c integrate checkpass routine to check against the dictionary 
c minor cleanups
e
s 00009/00014/00681
d D 4.27 87/06/22 10:11:24 bostic 27 26
c fall back to getuid() if getlogin fails.
e
s 00031/00024/00664
d D 4.26 86/11/17 16:40:17 bostic 26 25
c chsh/passwd improperly disallows valid shells; bug report 4.3BSD/bin/21
e
s 00001/00000/00687
d D 4.25 86/07/25 18:01:49 bloom 25 24
c reset shell list between lookups for normal users
e
s 00010/00000/00677
d D 4.24 86/05/28 15:40:34 mckusick 24 23
c do not allow users to change from a restricted shell
e
s 00001/00001/00676
d D 4.23 86/04/26 01:19:45 lepreau 23 22
c typo
e
s 00033/00082/00644
d D 4.22 85/11/08 18:16:23 mckusick 22 21
c getusershell() becomes a library routine
e
s 00074/00022/00652
d D 4.21 85/10/30 18:18:07 mckusick 21 20
c if present, /etc/shells is used to provide a list of acceptable shells
e
s 00002/00001/00672
d D 4.20 85/10/12 18:18:35 mckusick 20 19
c check for failed open before closing (from Chris Torek)
e
s 00014/00002/00659
d D 4.19 85/10/11 18:01:45 mckusick 19 18
c add copyright
e
s 00003/00026/00658
d D 4.18 85/08/28 16:49:52 bloom 18 17
c relax restrictions on office phone numbers
e
s 00001/00000/00683
d D 4.17 85/08/11 01:16:27 kre 17 16
c make sure ptmp is all written before we check for wrt errors,
c or errors writing the last buffer will be missed.
e
s 00009/00003/00674
d D 4.16 85/08/09 21:39:20 kre 16 15
c don't reply on errno being preserved over fprintf calls.
e
s 00008/00003/00669
d D 4.15 85/08/09 20:59:43 kre 15 14
c check for write errors on /etc/ptmp before renaming it to /etc/passwd
e
s 00023/00043/00649
d D 4.14 85/04/09 14:17:32 edward 14 13
c finger office address less Berkeley-centric
e
s 00015/00009/00677
d D 4.13 85/02/10 17:14:27 edward 13 12
c use rindex() instead index() to match argv[0]
c let chsh take shell from command line as before
e
s 00001/00001/00685
d D 4.12 85/01/23 16:15:33 lepreau 12 11
c ignore TSTP a little sooner, before ptmp file is created
e
s 00006/00003/00680
d D 4.11 85/01/10 09:15:55 ralph 11 10
c make code more portable.
e
s 00012/00002/00671
d D 4.10 85/01/09 10:38:29 ralph 10 9
c check argv[0] for chfn or chsh
e
s 00001/00001/00672
d D 4.9 84/12/08 14:13:06 lepreau 9 8
c fix bug with -f and room number
e
s 00545/00094/00128
d D 4.8 84/08/29 16:57:44 ralph 8 7
c -f option replaces chfn, -s option replaces chsh
e
s 00005/00001/00217
d D 4.7 84/08/17 15:46:47 bloom 7 6
c more coherent error messages
e
s 00050/00032/00168
d D 4.6 83/12/20 13:42:19 ralph 6 5
c modified to update dbm passwd database directly.
e
s 00039/00014/00161
d D 4.5 83/12/02 17:48:31 ralph 5 4
c rebuild passwd database.
e
s 00001/00000/00174
d D 4.4 83/07/10 17:52:49 sam 4 3
c beware of screwey user umaskas
e
s 00005/00013/00169
d D 4.3 83/06/10 23:14:20 sam 3 2
c use open locking; should use flock on /etc/passwd itself
e
s 00000/00001/00182
d D 4.2 83/02/09 13:21:19 sam 2 1
c extraneous if
e
s 00183/00000/00000
d D 4.1 83/01/01 13:24:54 sam 1 0
c date and time created 83/01/01 13:24:54 by sam
e
u
U
f b 
t
T
I 19
/*
D 33
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 33
I 33
D 50
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 50
I 50
D 52
 * Copyright (c) 1988, 1993
E 52
I 52
 * Copyright (c) 1988, 1993, 1994
E 52
 *	The Regents of the University of California.  All rights reserved.
E 50
 *
D 40
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
E 40
I 40
 * %sccs.include.redist.c%
E 40
E 33
 */

E 19
I 1
#ifndef lint
D 15
static char sccsid[] = "%W% (Berkeley) %G%";
E 15
I 15
D 19
static char sccsid[] = "%W% (Berkeley) %E%";
E 15
#endif
E 19
I 19
D 50
char copyright[] =
D 33
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 33
I 33
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
E 33
 All rights reserved.\n";
E 50
I 50
static char copyright[] =
D 52
"%Z% Copyright (c) 1988, 1993\n\
E 52
I 52
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 52
	The Regents of the University of California.  All rights reserved.\n";
E 50
D 33
#endif not lint
E 33
I 33
#endif /* not lint */
E 33

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 33
#endif not lint
E 33
I 33
#endif /* not lint */
E 33
E 19

I 51
#include <err.h>
E 51
I 49
#include <errno.h>
E 49
D 33
/*
D 3
 * enter a password in the password file
 * this program should be suid with owner
 * with an owner with write permission on /etc/passwd
E 3
I 3
D 8
 * Enter a password in the password file.
E 8
I 8
D 28
 * Modify a field in the password file (either
 * password, login shell, or gecos field).
E 8
 * This program should be suid with an owner
 * with write permission on /etc/passwd.
E 28
I 28
 * Modify a field in the password file (either password, login shell, or
 * gecos field).  This program should be suid with an owner with write
 * permission on /etc/passwd.
E 28
E 3
 */
I 8
D 21
#include <sys/types.h>
E 21
I 21
D 22
#include <sys/param.h>
E 22
I 22
#include <sys/types.h>
E 33
I 33
D 45
#include <sys/param.h>
E 33
E 22
E 21
E 8
#include <sys/file.h>
I 28
D 33
#include <sys/stat.h>
E 33
I 33
#include <sys/signal.h>
E 33
E 28
I 8
#include <sys/time.h>
#include <sys/resource.h>
I 36
#include <sys/wait.h>
E 36
I 21
D 22
#include <sys/stat.h>
E 22
E 21
E 8
D 33

#include <stdio.h>
#include <signal.h>
#include <pwd.h>
I 6
#include <ndbm.h>
E 33
E 6
#include <errno.h>
I 8
D 33
#include <strings.h>
E 33
I 33
#include <pwd.h>
E 45
#include <stdio.h>
I 51
#include <stdlib.h>
E 51
E 33
D 45
#include <ctype.h>
I 34
D 39
#include <strings.h>
E 39
I 39
#include <string.h>
E 45
I 45
#include <unistd.h>
E 45
E 39
E 34
E 8

I 51
#include "extern.h"

void	usage __P((void));

E 51
I 41
D 43
#ifdef	KERBEROS
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
#include "kpasswd_proto.h"
E 43
I 43
#ifdef KERBEROS
E 43
int use_kerberos = 1;
D 45
#define ARGSTR "l"
#else
#define ARGSTR ""
E 45
#endif

I 51
int
E 51
E 41
I 22
D 33
/*
 * This should be the first thing returned from a getloginshells()
 * but too many programs know that it is /bin/sh.
 */
D 28
#define DEFSHELL "/bin/sh"
E 28
I 28
#define	DEFSHELL	"/bin/sh"
E 33
I 33
D 45
uid_t uid;
E 33
E 28

E 45
E 22
I 5
D 28
char	temp[] = "/etc/ptmp";
D 6
char	temp_pag[] = "/etc/ptmp.pag";
char	temp_dir[] = "/etc/ptmp.dir";
E 6
E 5
char	passwd[] = "/etc/passwd";
I 21
D 22
char	shells[] = "/etc/shells";
E 22
E 21
D 5
char	temp[]	 = "/etc/ptmp";
E 5
I 5
D 6
char	passwd_pag[] = "/etc/passwd.pag";
char	passwd_dir[] = "/etc/passwd.dir";
E 6
E 5
D 8
struct	passwd *pwd;
D 5
struct	passwd *getpwent();
int	endpwent();
E 5
char	*strcpy();
char	*crypt();
E 8
char	*getpass();
D 27
char	*getlogin();
E 27
D 8
char	*pw;
char	pwbuf[10];
E 8
I 8
char	*getfingerinfo();
char	*getloginshell();
char	*getnewpasswd();
I 21
char	*malloc();
D 22
char	*calloc();
E 22
I 22
char	*getusershell();
E 22
E 21
E 8
extern	int errno;
E 28
I 28
D 33
#define	DICT		"/usr/dict/words"
#define	PASSWD		"/etc/passwd"
#define	PTEMP		"/etc/ptmp"
E 28

I 28
#define	EOS		'\0';

E 33
E 28
main(argc, argv)
D 28
	char *argv[];
E 28
I 28
D 33
	int	argc;
	char	**argv;
E 33
I 33
	int argc;
	char **argv;
E 33
E 28
{
I 45
D 51
	extern int optind;
E 45
D 8
	char *p;
	int i;
	char saltc[2];
	long salt;
	int u;
	int insist;
	int ok, flags;
	int c, pwlen, fd;
E 8
I 8
D 28
	struct passwd *pwd;
D 10
	char *cp, *uname;
E 10
I 10
	char *cp, *uname, *progname;
E 10
D 16
	int fd, i, u, dochfn, dochsh;
E 16
I 16
D 21
	int fd, i, u, dochfn, dochsh, err;
E 21
I 21
D 27
	int fd, u, dochfn, dochsh, err;
E 27
I 27
	uid_t u;
	int fd, dochfn, dochsh, err;
E 27
E 21
E 16
E 8
	FILE *tf;
D 8
	char *uname;
E 8
I 6
	DBM *dp;
I 27
	char *getlogin();
E 28
I 28
D 33
	extern char	*optarg;
	extern int	errno, optind;
	struct passwd	*pwd;
	FILE	*tf;
	DBM	*dp;
	uid_t	uid, getuid();
	int	ch, fd, dochfn, dochsh;
	char	*cp, *uname, *progname, *umsg,
		*getfingerinfo(), *getloginshell(), *getnewpasswd(), *malloc();
E 33
I 33
D 41
	extern int errno;
E 41
I 41
	register int ch;
E 51
I 51
	int ch;
E 51
D 45
	extern int errno, optind;
D 44
	extern char *optarg;
E 44
E 41
	struct passwd *pw;
	struct rlimit rlim;
D 34
	uid_t euid;
E 34
	FILE *temp_fp;
	int fd;
D 37
	char *fend, *np, *passwd, *temp, *tend;
E 37
I 37
	char *fend, *np, *passwd, *temp, *tend, *uname;
E 37
	char from[MAXPATHLEN], to[MAXPATHLEN];
D 34
	char *getnewpasswd(), *strerror(), *strcpy();
E 34
I 34
D 37
	char *getnewpasswd();
E 37
I 37
	char *getnewpasswd(), *getlogin();
E 45
I 45
	char *uname;
E 45
E 37
E 34
E 33
E 28
E 27
E 6

I 10
D 13
	if ((progname = index(argv[0], '/')) == NULL)
E 13
I 13
D 28
	if ((progname = rindex(argv[0], '/')) == NULL)
E 13
		progname = argv[0];
E 28
I 28
D 33
	progname = (cp = rindex(*argv, '/')) ? cp + 1 : *argv;
	dochfn = dochsh = 0;
	if (!strcmp(progname, "chfn")) {
		dochfn = 1;
		umsg = "usage: chfn [username]\n";
	}
	else if (!strcmp(progname, "chsh")) {
		dochsh = 1;
		umsg = "usage: chsh [username]\n";
	}
E 28
	else
D 28
		progname++;
E 10
D 8
	insist = 0;
	if (argc < 2) {
E 8
I 8
	dochfn = 0, dochsh = 0;
	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		for (cp = &argv[0][1]; *cp; cp++) switch (*cp) {
E 28
I 28
		umsg = "usage: passwd [-fs] [username]\n";
E 28

I 28
	while ((ch = getopt(argc, argv, "fs")) != EOF)
		switch((char)ch) {
E 28
		case 'f':
			if (dochsh)
D 28
				goto bad;
E 28
I 28
				goto usage;
E 28
			dochfn = 1;
			break;
D 28

E 28
		case 's':
D 28
			if (dochfn) {
		bad:
				fprintf(stderr,
				   "passwd: Only one of -f and -s allowed.\n"); 
				exit(1);
			}
E 28
I 28
			if (dochfn)
				goto usage;
E 28
			dochsh = 1;
			break;
D 28

E 28
I 28
		case '?':
E 28
		default:
D 28
			fprintf(stderr, "passwd: -%c: unknown option.\n", *cp);
E 28
I 28
usage:			fputs(umsg, stderr);
E 28
			exit(1);
		}
D 28
		argc--, argv++;
E 28
I 28

E 33
I 33
D 34
	euid = geteuid();
E 34
E 33
D 45
	uid = getuid();
I 37
	uname = getlogin();
E 37
D 33
	if (argc - optind < 1) {
		if (!(pwd = getpwuid(uid))) {
			fprintf(stderr, "%s: %u: unknown user uid.\n", progname, uid);
E 33
I 33
D 41
	switch(--argc) {
E 41
I 41

#ifdef	KERBEROS
	while ((ch = getopt(argc, argv, ARGSTR)) != EOF)
E 45
I 45
D 51
#ifdef KERBEROS
E 51
	while ((ch = getopt(argc, argv, "l")) != EOF)
E 45
		switch (ch) {
I 51
#ifdef KERBEROS
E 51
D 45
		/* change local password file */
		case 'l':
E 45
I 45
		case 'l':		/* change local password file */
E 45
			use_kerberos = 0;
			break;
I 46
D 51
#else
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch (ch) {
E 51
#endif
E 46
		default:
		case '?':
			usage();
D 51
			exit(1);
E 51
		}

	argc -= optind;
	argv += optind;
D 46
#endif
E 46

I 45
D 49
	uname = getlogin();
E 49
I 49
D 51
	if ((uname = getlogin()) == NULL) {
		(void)fprintf(stderr, "passwd: getlogin: %s\n",
		    strerror(errno));
		exit (1);
	}
E 51
I 51
	if ((uname = getlogin()) == NULL)
		err(1, "getlogin");
E 51
E 49

E 45
	switch(argc) {
E 41
	case 0:
D 37
		if (!(pw = getpwuid(uid))) {
			fprintf(stderr, "passwd: unknown user: uid %u\n", uid);
E 33
			exit(1);
		}
E 37
D 33
		if (!(uname = malloc((u_int)(strlen(pwd->pw_name) + 1)))) {
			fprintf(stderr, "%s: out of space.\n", progname);
E 33
I 33
		break;
	case 1:
I 41
#ifdef	KERBEROS
D 45
		if (use_kerberos && (strcmp(argv[1],uname) != 0)) { 
			fprintf(stderr,
				"must kinit to change another's password\n");
E 45
I 45
D 48
		if (use_kerberos && strcmp(argv[1], uname)) {
E 48
I 48
D 51
		if (use_kerberos && strcmp(argv[0], uname)) {
E 48
D 47
			(void)fprintf(stderr,
			   "passwd: must kinit to change another's password\n");
E 47
I 47
			(void)fprintf(stderr, "passwd: %s\n\t%s\n%s\n",
"to change another user's Kerberos password, do",
"\"kinit user; passwd; kdestroy\";",
"to change a user's local passwd, use \"passwd -l user\"");
E 47
E 45
			exit(1);
		}
E 51
I 51
		if (use_kerberos && strcmp(argv[0], uname))
			errx(1,"%s\n\t%s\n%s\n",
		"to change another user's Kerberos password, do",
		"\"kinit user; passwd; kdestroy\";",
		"to change a user's local passwd, use \"passwd -l user\"");
E 51
#endif
E 41
D 37
		if (!(pw = getpwnam(argv[1]))) {
			fprintf(stderr, "passwd: unknown user %s.\n", argv[1]);
E 33
			exit(1);
		}
D 33
		(void)strcpy(uname, pwd->pw_name);
E 28
	}
I 10
D 28
	if (!dochfn && !dochsh) {
		if (strcmp(progname, "chfn") == 0)
			dochfn = 1;
		else if (strcmp(progname, "chsh") == 0)
			dochsh = 1;
E 28
I 28
	else {
		uname = *(argv + optind);
		if (!(pwd = getpwnam(uname))) {
			fprintf(stderr, "%s: %s: unknown user.\n", progname, uname);
E 33
I 33
		if (uid && uid != pw->pw_uid) {
			fprintf(stderr, "passwd: %s\n", strerror(EACCES));
E 33
			exit(1);
		}
E 37
I 37
D 42
		uname = argv[1];
E 42
I 42
		uname = argv[0];
E 42
E 37
E 28
D 33
	}
E 10
D 28
	if (argc < 1) {
E 8
D 27
		if ((uname = getlogin()) == NULL) {
D 8
			printf ("Usage: passwd user\n");
E 8
I 8
D 10
			fprintf(stderr, "Usage: passwd [-f] [-s] [user]\n");
E 10
I 10
			fprintf(stderr, "Usage: %s [-f] [-s] [user]\n", progname);
E 10
E 8
			exit(1);
		}
D 8
		printf("Changing password for %s\n", uname);
E 8
I 8
		printf("Changing %s for %s.\n",
		    dochfn ? "finger information" :
			dochsh ? "login shell" : "password",
		    uname);
E 8
	} else
E 27
I 27
		if (uname = getlogin())
			printf("Changing %s for %s.\n", dochfn ? "finger information" : dochsh ? "login shell" : "password", uname);
	}
	else
E 27
D 8
		uname = argv[1];
E 8
I 8
D 13
		uname = *argv;
E 13
I 13
		uname = *argv++;
E 13
E 8
D 5
	while (((pwd = getpwent()) != NULL) && strcmp(pwd->pw_name, uname))
		;
E 5
I 5
D 27
	pwd = getpwnam(uname);
I 7
	if (pwd == NULL) {
E 27
I 27
	u = getuid();
	if (!(pwd = uname ? getpwnam(uname) : getpwuid(u))) {
E 27
D 8
		printf("%s: unknown user\n", uname);
E 8
I 8
		fprintf(stderr, "passwd: %s: unknown user.\n", uname);
E 28
I 28
	if (uid && uid != pwd->pw_uid) {
		fputs("Permission denied.\n", stderr);
E 33
I 33
		break;
	default:
D 41
		fprintf(stderr, "usage: passwd [user]\n");
E 41
I 41
		usage();
E 41
E 33
E 28
E 8
D 51
		exit(1);
E 51
	}
I 41

#ifdef	KERBEROS
D 45
	if (use_kerberos) {
		exit(do_krb_passwd());
		/* NOTREACHED */
	}
E 45
I 45
	if (use_kerberos)
		exit(krb_passwd());
E 45
#endif
D 45

E 41
I 37
	if (!(pw = getpwnam(uname))) {
		fprintf(stderr, "passwd: unknown user %s.\n", uname);
		exit(1);
	}
	if (uid && uid != pw->pw_uid) {
		fprintf(stderr, "passwd: %s\n", strerror(EACCES));
		exit(1);
	}
E 37
E 7
E 5
D 27
	u = getuid();
E 27
D 7
	if (pwd == NULL || (u != 0 && u != pwd->pw_uid)) {
E 7
I 7
D 28
	if (u != 0 && u != pwd->pw_uid) {
E 7
		printf("Permission denied.\n");
		exit(1);
	}
E 28
I 28
D 33
	printf("Changing %s for %s.\n", dochfn ? "finger information" : dochsh ? "login shell" : "password", uname);
E 28
D 5
	endpwent();
E 5
D 8
	if (pwd->pw_passwd[0] && u != 0) {
		strcpy(pwbuf, getpass("Old password:"));
		pw = crypt(pwbuf, pwd->pw_passwd);
		if (strcmp(pw, pwd->pw_passwd) != 0) {
			printf("Sorry.\n");
			exit(1);
		}
	}
tryagain:
	strcpy(pwbuf, getpass("New password:"));
	pwlen = strlen(pwbuf);
	if (pwlen == 0) {
		printf("Password unchanged.\n");
		exit(1);
	}
	/*
	 * Insure password is of reasonable length and
	 * composition.  If we really wanted to make things
	 * sticky, we could check the dictionary for common
	 * words, but then things would really be slow.
	 */
	ok = 0;
	flags = 0;
	p = pwbuf;
	while (c = *p++) {
		if (c >= 'a' && c <= 'z')
			flags |= 2;
		else if (c >= 'A' && c <= 'Z')
			flags |= 4;
		else if (c >= '0' && c <= '9')
			flags |= 1;
		else
			flags |= 8;
	}
	if (flags >= 7 && pwlen >= 4)
		ok = 1;
	if ((flags == 2 || flags == 4) && pwlen >= 6)
		ok = 1;
	if ((flags == 3 || flags == 5 || flags == 6) && pwlen >= 5)
		ok = 1;
	if (!ok && insist < 2) {
D 2
		if (flags == 1)
E 2
		printf("Please use %s.\n", flags == 1 ?
			"at least one non-numeric character" :
			"a longer password");
		insist++;
		goto tryagain;
	}
	if (strcmp(pwbuf, getpass("Retype new password:")) != 0) {
		printf("Mismatch - password unchanged.\n");
		exit(1);
	}
	time(&salt);
	salt = 9 * getpid();
	saltc[0] = salt & 077;
	saltc[1] = (salt>>6) & 077;
	for (i = 0; i < 2; i++) {
		c = saltc[i] + '.';
		if (c > '9')
			c += 7;
		if (c > 'Z')
			c += 6;
		saltc[i] = c;
	}
	pw = crypt(pwbuf, saltc);
E 8
I 8
	if (dochfn)
D 21
		cp = getfingerinfo(pwd, u);
E 21
I 21
		cp = getfingerinfo(pwd);
E 21
	else if (dochsh)
D 13
		cp = getloginshell(pwd, u);
E 13
I 13
D 28
		cp = getloginshell(pwd, u, *argv);
E 28
I 28
		cp = getloginshell(pwd, uid);
E 28
E 13
	else
D 28
		cp = getnewpasswd(pwd, u);
E 28
I 28
		cp = getnewpasswd(pwd, uid);
E 28
E 8
D 21
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
I 12
	signal(SIGTSTP, SIG_IGN);
E 21
I 21
	(void) signal(SIGHUP, SIG_IGN);
	(void) signal(SIGINT, SIG_IGN);
	(void) signal(SIGQUIT, SIG_IGN);
	(void) signal(SIGTSTP, SIG_IGN);
E 21
E 12
I 4
	(void) umask(0);
E 4
D 3
	/*
	 * The mode here could be 644 except then old versions
	 * of passwd that don't honor the advisory locks might
	 * sneak in and mess things up.  If we could believe the
	 * locking were honored, then we could also eliminate the
	 * chmod below after the rename.
	 */
	fd = open(temp, FWRONLY|FCREATE|FEXLOCK|FNBLOCK, 0600);
E 3
I 3
D 28
	fd = open(temp, O_WRONLY|O_CREAT|O_EXCL, 0644);
E 3
	if (fd < 0) {
I 16
		err = errno;

E 16
		fprintf(stderr, "passwd: ");
D 3
		if (errno == EBUSY)
E 3
I 3
D 16
		if (errno == EEXIST)
E 16
I 16
		if (err == EEXIST)
E 16
E 3
			fprintf(stderr, "password file busy - try again.\n");
E 28
I 28
	if ((fd = open(PTEMP, O_WRONLY|O_CREAT|O_EXCL, 0644)) < 0) {
		if (errno == EEXIST)
			fprintf(stderr, "%s: password file busy - try again.\n", progname);
E 28
D 16
		else
E 16
I 16
		else {
D 28
			errno = err;
E 16
			perror(temp);
E 28
I 28
			fprintf(stderr, "%s: %s: ", progname, PTEMP);
			perror((char *)NULL);
E 28
I 16
		}
E 16
		exit(1);
	}
D 12
	signal(SIGTSTP, SIG_IGN);
E 12
	if ((tf = fdopen(fd, "w")) == NULL) {
D 28
		fprintf(stderr, "passwd: fdopen failed?\n");
E 28
I 28
		fprintf(stderr, "%s: fdopen failed.\n", progname);
E 28
		exit(1);
	}
I 6
D 8
	if ((dp = ndbmopen(passwd, O_RDWR, 0644)) == NULL) {
		fprintf(stderr, "Warning: dbminit failed: ");
E 8
I 8
D 28
	if ((dp = dbm_open(passwd, O_RDWR, 0644)) == NULL) {
I 16
		err = errno;
E 16
		fprintf(stderr, "Warning: dbm_open failed: ");
I 16
		errno = err;
E 16
E 8
		perror(passwd);
D 8
	} else if (flock(dp->db_dirf, LOCK_EX) < 0) {
E 8
I 8
	} else if (flock(dp->dbm_dirf, LOCK_EX) < 0) {
E 28
I 28
	if ((dp = dbm_open(PASSWD, O_RDWR, 0644)) == NULL) {
		fprintf(stderr, "Warning: dbm_open failed: %s: ", PASSWD);
		perror((char *)NULL);
	}
	else if (flock(dp->dbm_dirf, LOCK_EX) < 0) {
E 28
E 8
		perror("Warning: lock failed");
D 8
		ndbmclose(dp);
E 8
I 8
		dbm_close(dp);
E 8
		dp = NULL;
	}
I 8
	unlimit(RLIMIT_CPU);
	unlimit(RLIMIT_FSIZE);
E 8
E 6
	/*
	 * Copy passwd to temp, replacing matching lines
	 * with new password.
	 */
	while ((pwd = getpwent()) != NULL) {
D 5
		if (strcmp(pwd->pw_name,uname) == 0) {
E 5
I 5
D 28
		if (strcmp(pwd->pw_name, uname) == 0) {
E 5
D 6
			u = getuid();
E 6
			if (u && u != pwd->pw_uid) {
				fprintf(stderr, "passwd: permission denied.\n");
E 28
I 28
		if (!strcmp(pwd->pw_name, uname)) {
			if (uid && uid != pwd->pw_uid) {
				fprintf(stderr, "%s: permission denied.\n", progname);
E 28
D 5
				unlink(temp);
				exit(1);
E 5
I 5
				goto out;
E 5
			}
D 8
			pwd->pw_passwd = pw;
			if (pwd->pw_gecos[0] == '*')
E 8
I 8
			if (dochfn)
				pwd->pw_gecos = cp;
			else if (dochsh)
				pwd->pw_shell = cp;
			else
				pwd->pw_passwd = cp;
			if (pwd->pw_gecos[0] == '*')	/* ??? */
E 8
				pwd->pw_gecos++;
I 6
			replace(dp, pwd);
E 6
		}
D 28
		fprintf(tf,"%s:%s:%d:%d:%s:%s:%s\n",
E 28
I 28
		fprintf(tf, "%s:%s:%d:%d:%s:%s:%s\n",
E 28
			pwd->pw_name,
			pwd->pw_passwd,
			pwd->pw_uid,
			pwd->pw_gid,
			pwd->pw_gecos,
			pwd->pw_dir,
			pwd->pw_shell);
	}
	endpwent();
D 5
	if (rename(temp, passwd) < 0) {
		fprintf(stderr, "passwd: "); perror("rename");
		unlink(temp);
		exit(1);
	}
E 5
D 3
	chmod(passwd, 0644);
E 3
D 6
	fclose(tf);
I 5
	if (makedb(temp) < 0)
		fprintf(stderr, "passwd: mkpasswd failed\n");
	else if (rename(temp_pag, passwd_pag) < 0)
		fprintf(stderr, "passwd: "), perror(temp_pag);
	else if (rename(temp_dir, passwd_dir) < 0)
		fprintf(stderr, "passwd: "), perror(temp_dir);
	else if (rename(temp, passwd) < 0)
E 6
I 6
D 15
	(void) fclose(tf);
E 15
D 8
	ndbmclose(dp);
E 8
I 8
D 28
	if (dp != NULL && dbm_error(dp))
		fprintf(stderr, "Warning: dbm_store failed\n");
E 28
I 28
	if (dp && dbm_error(dp))
		fputs("Warning: dbm_store failed.\n", stderr);
E 28
I 17
D 21
	fflush(tf);
E 21
I 21
	(void) fflush(tf);
E 21
E 17
I 15
	if (ferror(tf)) {
D 28
		fprintf(stderr, "Warning: %s write error, %s not updated\n",
		    temp, passwd);
E 28
I 28
		fprintf(stderr, "Warning: %s write error, %s not updated.\n",
		    PTEMP, PASSWD);
E 28
		goto out;
	}
D 28
	(void) fclose(tf);
E 28
I 28
	(void)fclose(tf);
E 28
E 15
D 20
	dbm_close(dp);
E 20
I 20
	if (dp != NULL)
		dbm_close(dp);
E 20
E 8
D 28
	if (rename(temp, passwd) < 0) {
E 6
D 15
		fprintf(stderr, "passwd: "), perror("rename");
E 15
I 15
		perror("passwd: rename");
E 28
I 28
	if (rename(PTEMP, PASSWD) < 0) {
		perror(progname);
E 28
E 15
D 6
	else
		exit(0);
out:
	unlink(temp_pag);
	unlink(temp_dir);
	unlink(temp);
	exit(1);
E 6
I 6
	out:
D 21
		unlink(temp);
E 21
I 21
D 28
		(void) unlink(temp);
E 28
I 28
		(void)unlink(PTEMP);
E 28
E 21
		exit(1);
	}
	exit(0);
E 6
}
E 33

I 8
D 33
unlimit(lim)
I 28
	int	lim;
E 28
{
	struct rlimit rlim;
E 33
I 33
	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGTSTP, SIG_IGN);
E 33

	rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
D 28
	(void) setrlimit(lim, &rlim);
E 28
I 28
D 33
	(void)setrlimit(lim, &rlim);
E 28
}
E 33
I 33
	(void)setrlimit(RLIMIT_CPU, &rlim);
	(void)setrlimit(RLIMIT_FSIZE, &rlim);
E 33

E 8
D 6
makedb(file)
	char *file;
E 6
I 6
D 33
/*
 * Replace the password entry in the dbm data base with pwd.
 */
replace(dp, pwd)
	DBM *dp;
	struct passwd *pwd;
E 6
{
D 6
	int status, pid, w;
E 6
I 6
	datum key, content;
	register char *cp, *tp;
	char buf[BUFSIZ];
E 33
I 33
	(void)umask(0);
E 33
E 6

D 6
	if ((pid = vfork()) == 0) {
		execl("/etc/mkpasswd", "mkpasswd", file, 0);
		_exit(127);
	}
	while ((w = wait(&status)) != pid && w != -1)
		;
	if (w == -1 || status != 0)
		status = -1;
	return(status);
E 6
I 6
D 33
	if (dp == NULL)
		return;

	cp = buf;
D 31
#define	COMPACT(e)	tp = pwd->pw_/**/e; while (*cp++ = *tp++);
	COMPACT(name);
	COMPACT(passwd);
E 31
I 31
#define	COMPACT(e)	tp = pwd->e; while (*cp++ = *tp++);
	COMPACT(pw_name);
	COMPACT(pw_passwd);
E 31
D 11
	*(int *)cp = pwd->pw_uid; cp += sizeof (int);
	*(int *)cp = pwd->pw_gid; cp += sizeof (int);
	*(int *)cp = pwd->pw_quota; cp += sizeof (int);
E 11
I 11
	bcopy((char *)&pwd->pw_uid, cp, sizeof (int));
	cp += sizeof (int);
	bcopy((char *)&pwd->pw_gid, cp, sizeof (int));
	cp += sizeof (int);
	bcopy((char *)&pwd->pw_quota, cp, sizeof (int));
	cp += sizeof (int);
E 11
D 31
	COMPACT(comment);
	COMPACT(gecos);
	COMPACT(dir);
	COMPACT(shell);
E 31
I 31
	COMPACT(pw_comment);
	COMPACT(pw_gecos);
	COMPACT(pw_dir);
	COMPACT(pw_shell);
E 31
	content.dptr = buf;
	content.dsize = cp - buf;
	key.dptr = pwd->pw_name;
	key.dsize = strlen(pwd->pw_name);
D 8
	dbmstore(dp, key, content, DB_REPLACE);
E 8
I 8
	dbm_store(dp, key, content, DBM_REPLACE);
E 8
	key.dptr = (char *)&pwd->pw_uid;
	key.dsize = sizeof (int);
D 8
	dbmstore(dp, key, content, DB_REPLACE);
E 8
I 8
	dbm_store(dp, key, content, DBM_REPLACE);
}

char *
getnewpasswd(pwd, u)
	register struct passwd *pwd;
D 28
	int u;
E 28
I 28
	uid_t u;
E 28
{
D 28
	char saltc[2];
D 21
	time_t salt;
E 21
I 21
	long salt;
E 21
	int i, insist = 0, ok, flags;
	int c, pwlen;
	static char pwbuf[10];
I 21
	long time();
E 21
	char *crypt(), *pw, *p;
E 28
I 28
	time_t	salt, time();
	int	c, i, insist;
	char	*pw, pwbuf[10], pwcopy[10], saltc[2],
		*crypt(), *getpass();
E 28

	if (pwd->pw_passwd[0] && u != 0) {
D 21
		strcpy(pwbuf, getpass("Old password:"));
E 21
I 21
D 28
		(void) strcpy(pwbuf, getpass("Old password:"));
E 28
I 28
		(void)strcpy(pwbuf, getpass("Old password:"));
E 28
E 21
		pw = crypt(pwbuf, pwd->pw_passwd);
		if (strcmp(pw, pwd->pw_passwd) != 0) {
D 28
			printf("Sorry.\n");
E 28
I 28
			puts("Sorry.");
E 28
			exit(1);
E 33
I 33
	temp = _PATH_PTMP;
	if ((fd = open(temp, O_WRONLY|O_CREAT|O_EXCL, 0600)) < 0) {
		if (errno == EEXIST) {
			fprintf(stderr,
			    "passwd: password file busy -- try again later.\n");
			exit(0);
E 33
		}
I 33
		fprintf(stderr, "passwd: %s: %s", temp, strerror(errno));
		goto bad;
E 33
	}
D 28
tryagain:
D 21
	strcpy(pwbuf, getpass("New password:"));
E 21
I 21
	(void) strcpy(pwbuf, getpass("New password:"));
E 21
	pwlen = strlen(pwbuf);
	if (pwlen == 0) {
		printf("Password unchanged.\n");
		exit(1);
E 28
I 28
D 33
	for(;;) {
		(void)strcpy(pwbuf, getpass("New password:"));
		if (!*pwbuf) {
			puts("Password unchanged.");
			exit(1);
		}
		if (strcmp(pwbuf, pwcopy)) {
			insist = 1;
			(void)strcpy(pwcopy, pwbuf);
		}
		else if (++insist == 4)
			break;
D 30
		if (checkpass(pwbuf))
E 30
I 30
		if (strlen(pwbuf) <= 4)
			puts("Please enter a longer password.");
D 32
		else for (pw = pwbuf; *pw && islower(*pw); ++pw);
		if (*pw)
E 30
			break;
I 30
		puts("Please don't use an all-lower case password.\nUnusual capitalization, control characters or digits are suggested.");
E 32
I 32
		else {
			for (pw = pwbuf; *pw && islower(*pw); ++pw);
			if (*pw)
				break;
			puts("Please don't use an all-lower case password.\nUnusual capitalization, control characters or digits are suggested.");
		}
E 33
I 33
	if (!(temp_fp = fdopen(fd, "w"))) {
D 38
		fprintf(stderr, "passwd: can't write %s\n", temp);
E 38
I 38
		fprintf(stderr, "passwd: can't write %s", temp);
E 38
		goto bad;
E 33
E 32
E 30
E 28
	}
D 28
	/*
	 * Insure password is of reasonable length and
	 * composition.  If we really wanted to make things
	 * sticky, we could check the dictionary for common
	 * words, but then things would really be slow.
	 */
	ok = 0;
	flags = 0;
	p = pwbuf;
	while (c = *p++) {
		if (c >= 'a' && c <= 'z')
			flags |= 2;
		else if (c >= 'A' && c <= 'Z')
			flags |= 4;
		else if (c >= '0' && c <= '9')
			flags |= 1;
		else
			flags |= 8;
	}
	if (flags >= 7 && pwlen >= 4)
		ok = 1;
	if ((flags == 2 || flags == 4) && pwlen >= 6)
		ok = 1;
	if ((flags == 3 || flags == 5 || flags == 6) && pwlen >= 5)
		ok = 1;
	if (!ok && insist < 2) {
		printf("Please use %s.\n", flags == 1 ?
			"at least one non-numeric character" :
			"a longer password");
		insist++;
		goto tryagain;
	}
E 28
D 30
	if (strcmp(pwbuf, getpass("Retype new password:")) != 0) {
E 30
I 30
D 33
	if (strcmp(pwbuf, getpass("Retype new password:"))) {
E 30
D 28
		printf("Mismatch - password unchanged.\n");
E 28
I 28
		puts("Mismatch - password unchanged.");
E 28
		exit(1);
E 33
I 33
	passwd = _PATH_MASTERPASSWD;
	if (!freopen(passwd, "r", stdin)) {
D 38
		fprintf(stderr, "passwd: can't read %s\n", passwd);
E 38
I 38
		fprintf(stderr, "passwd: can't read %s", passwd);
E 38
		goto bad;
E 33
	}
D 21
	time(&salt);
E 21
I 21
D 28
	(void) time(&salt);
E 28
I 28
D 33
	(void)time(&salt);
E 28
E 21
	salt = 9 * getpid();
	saltc[0] = salt & 077;
	saltc[1] = (salt>>6) & 077;
	for (i = 0; i < 2; i++) {
		c = saltc[i] + '.';
		if (c > '9')
			c += 7;
		if (c > 'Z')
			c += 6;
		saltc[i] = c;
	}
D 28
	return (crypt(pwbuf, saltc));
E 28
I 28
	return(crypt(pwbuf, saltc));
E 28
}
E 33

D 22
#define	DEFSHELL	okshells[0]
I 21
/*
 * Do not add local shells here.  They should be added in /etc/shells
 */
E 21
char *okshells[] =
D 21
    { "/bin/sh", "/bin/csh", "/bin/oldcsh", "/bin/newcsh", "/usr/new/csh", 0 };
E 21
I 21
    { "/bin/sh", "/bin/csh", 0 };
E 21

E 22
D 33
char *
D 13
getloginshell(pwd, u)
E 13
I 13
D 28
getloginshell(pwd, u, arg)
E 28
I 28
getloginshell(pwd, u)
E 28
E 13
	struct passwd *pwd;
D 28
	int u;
I 13
	char *arg;
E 28
I 28
	uid_t u;
E 28
E 13
{
D 22
	static char newshell[256];
	register char **cpp;
	char *cp;
I 21
	char **sp;
	char **getlist();
E 22
I 22
	static char newshell[BUFSIZ];
	char *cp, *valid, *getusershell();
E 33
I 33
D 42
	printf("Changing password for %s.\n", pw->pw_name);
E 42
I 42
	printf("Changing local password for %s.\n", pw->pw_name);
E 42
	np = getnewpasswd(pw, temp);
E 33
E 22
E 21

D 33
	if (pwd->pw_shell == 0 || *pwd->pw_shell == '\0')
		pwd->pw_shell = DEFSHELL;
I 24
	if (u != 0) {
D 26
		for (valid = getusershell(); valid; valid = getusershell())
			if (strcmp(pwd->pw_shell, valid) == 0)
				break;
		if (valid == NULL) {
			printf("Cannot change from restricted shell %s\n",
				pwd->pw_shell);
			exit(1);
		}
E 26
I 26
		do {
			valid = getusershell();
			if (valid == NULL) {
				printf("Cannot change from restricted shell %s\n",
					pwd->pw_shell);
				exit(1);
			}
		} while (strcmp(pwd->pw_shell, valid) != 0);
E 26
	}
I 25
D 26
	setusershell();
E 26
E 25
E 24
D 13
	printf("Old shell: %s\nNew shell: ", pwd->pw_shell);
	fgets(newshell, sizeof (newshell) - 1, stdin);
	cp = index(newshell, '\n');
	if (cp)
		*cp = '\0';
E 13
I 13
D 28
	if (arg != 0) {
D 21
		strncpy(newshell, arg, sizeof newshell - 1);
E 21
I 21
		(void) strncpy(newshell, arg, sizeof newshell - 1);
E 21
D 26
		newshell[sizeof newshell - 1] = 0;
E 26
I 26
		newshell[sizeof newshell - 1] = '\0';
E 26
	} else {
		printf("Old shell: %s\nNew shell: ", pwd->pw_shell);
D 21
		fgets(newshell, sizeof (newshell) - 1, stdin);
E 21
I 21
		(void)fgets(newshell, sizeof (newshell) - 1, stdin);
E 21
		cp = index(newshell, '\n');
		if (cp)
			*cp = '\0';
I 26
		if (newshell[0] == 0) {
			puts("Login shell unchanged.");
			exit(1);
		}
E 28
I 28
	printf("Old shell: %s\nNew shell: ", pwd->pw_shell);
	(void)fgets(newshell, sizeof (newshell) - 1, stdin);
	cp = index(newshell, '\n');
	if (cp)
		*cp = '\0';
	if (newshell[0] == 0) {
		puts("Login shell unchanged.");
		exit(1);
E 28
E 26
	}
E 13
D 26
	if (newshell[0] == '\0' || strcmp(newshell, pwd->pw_shell) == 0) {
		printf("Login shell unchanged.\n");
		exit(1);
	}
E 26
I 21
D 22
	sp = getlist(okshells, shells);	/* get list of acceptable shells */
E 22
E 21
	/*
	 * Allow user to give shell name w/o preceding pathname.
	 */
D 22
	if (*cp != '/' && u != 0) {
D 21
		for (cpp = okshells; *cpp; cpp++) {
E 21
I 21
		for (cpp = sp; *cpp; cpp++) {
E 21
			cp = rindex(*cpp, '/');
			if (cp == 0)
				continue;
			if (strcmp(cp+1, newshell) == 0)
E 22
I 22
D 26
	if (u == 0) {
		valid = newshell;
	} else {
		for (valid = getusershell(); valid; valid = getusershell()) {
E 26
I 26
	if (u != 0 || newshell[0] != '/') {
		endusershell();
		do {
			valid = getusershell();
			if (valid == 0) {
				if (u == 0) {
					valid = newshell;
					break;
				}
				printf("%s is unacceptable as a new shell.\n",
					newshell);
				exit(1);
			}
E 26
			if (newshell[0] == '/') {
				cp = valid;
			} else {
				cp = rindex(valid, '/');
				if (cp == 0)
					cp = valid;
				else
					cp++;
			}
D 26
			if (strcmp(newshell, cp) == 0)
E 22
				break;
		}
E 26
I 26
		} while (strcmp(newshell, cp) != 0);
D 28
	} else {
		valid = newshell;
E 28
E 26
D 22
		if (*cpp)
D 21
			strcpy(newshell, *cpp);
E 21
I 21
			(void) strcpy(newshell, *cpp);
E 22
E 21
	}
I 28
	else
		valid = newshell;
E 28
D 22
	if (u != 0) {
D 21
		for (cpp = okshells; *cpp; cpp++)
E 21
I 21
		for (cpp = sp; *cpp; cpp++)
E 21
			if (strcmp(*cpp, newshell) == 0)
				break;
		if (*cpp == 0) {
			printf("%s is unacceptable as a new shell.\n",
			    newshell);
			exit(1);
		}
E 22
I 22
D 26
	if (valid == 0) {
		printf("%s is unacceptable as a new shell.\n",
		    newshell);
E 26
I 26
	if (strcmp(valid, pwd->pw_shell) == 0) {
		puts("Login shell unchanged.");
E 26
		exit(1);
E 22
	}
D 22
	if (access(newshell, X_OK) < 0) {
		printf("%s is unavailable.\n", newshell);
E 22
I 22
	if (access(valid, X_OK) < 0) {
		printf("%s is unavailable.\n", valid);
E 22
		exit(1);
	}
D 22
	if (strcmp(newshell, DEFSHELL) == 0)
		newshell[0] = '\0';
	return (newshell);
}
I 21
/*
 * Get a list of shells from SHELLS, if it exists.
 */
char **
getlist (list, file)
	char	**list;
	char	*file;
{
	register char **sp, *cp;
	char **shells;
	FILE *fp;
	struct stat statb;
E 21

I 21
	if ((fp = fopen(file, "r")) == (FILE *)0)
		return(list);
	if (fstat(fileno(fp), &statb) == -1) {
		(void)fclose(fp);
		return(list);
	}
	if ((cp = malloc((unsigned)statb.st_size)) == NULL) {
		(void)fclose(fp);
		return(list);
	}
	shells = (char **)calloc((unsigned)statb.st_size / 3, sizeof (char *));
	if (shells == NULL) {
		(void)fclose(fp);
		return(list);
	}
	sp = shells;
	while (fgets(cp, MAXPATHLEN + 1, fp) != NULL) {
		while (*cp != '/' && *cp != '\0')
			cp++;
		if (*cp == '\0')
			continue;
		*sp++ = cp;
		while (!isspace(*cp) && *cp != '#' && *cp != '\0')
			cp++;
		*cp++ = '\0';
	}
	*sp = (char *)0;
	(void)fclose(fp);
	return(shells);
E 22
I 22
	if (strcmp(valid, DEFSHELL) == 0)
		valid[0] = '\0';
	return (valid);
E 22
}
E 33
I 33
D 34
	if (!copy(pw->pw_name, np, temp_fp))
E 34
I 34
	if (!copy(pw->pw_name, np, temp_fp, pw))
E 34
		goto bad;
E 33

E 21
D 33
struct default_values {
	char *name;
	char *office_num;
	char *office_phone;
	char *home_phone;
};
E 33
I 33
	(void)fclose(temp_fp);
	(void)fclose(stdin);
E 33

D 33
/*
 * Get name, room number, school phone, and home phone.
 */
char *
D 21
getfingerinfo(pwd, u)
E 21
I 21
getfingerinfo(pwd)
E 21
	struct passwd *pwd;
D 21
	int u;
E 21
{
	char in_str[BUFSIZ];
	struct default_values *defaults, *get_defaults();
	static char answer[4*BUFSIZ];
E 33
I 33
	switch(fork()) {
	case 0:
		break;
	case -1:
		fprintf(stderr, "passwd: can't fork");
		goto bad;
		/* NOTREACHED */
	default:
		exit(0);
		/* NOTREACHED */
	}
E 33

D 33
	answer[0] = '\0';
	defaults = get_defaults(pwd->pw_gecos);
D 23
	printf("Default values are printed inside of of '[]'.\n");
E 23
I 23
D 28
	printf("Default values are printed inside of '[]'.\n");
E 23
	printf("To accept the default, type <return>.\n");
	printf("To have a blank entry, type the word 'none'.\n");
E 28
I 28
	puts("Default values are printed inside of '[]'.");
	puts("To accept the default, type <return>.");
	puts("To have a blank entry, type the word 'none'.");
E 28
	/*
	 * Get name.
	 */
	do {
		printf("\nName [%s]: ", defaults->name);
D 28
		(void) fgets(in_str, BUFSIZ, stdin);
E 28
I 28
		(void) fgets(in_str, BUFSIZ - 1, stdin);
E 28
		if (special_case(in_str, defaults->name)) 
			break;
	} while (illegal_input(in_str));
	(void) strcpy(answer, in_str);
	/*
	 * Get room number.
	 */
	do {
		printf("Room number (Exs: 597E or 197C) [%s]: ",
			defaults->office_num);
D 28
		(void) fgets(in_str, BUFSIZ, stdin);
E 28
I 28
		(void) fgets(in_str, BUFSIZ - 1, stdin);
E 28
		if (special_case(in_str, defaults->office_num))
			break;
	} while (illegal_input(in_str) || illegal_building(in_str));
	(void) strcat(strcat(answer, ","), in_str);
	/*
	 * Get office phone number.
D 18
	 * Remove hyphens and 642, x2, or 2 prefixes if present.
E 18
I 18
	 * Remove hyphens.
E 18
	 */
	do {
D 18
		printf("Office Phone (Ex: 1632) [%s]: ",
E 18
I 18
		printf("Office Phone (Ex: 6426000) [%s]: ",
E 18
			defaults->office_phone);
D 28
		(void) fgets(in_str, BUFSIZ, stdin);
E 28
I 28
		(void) fgets(in_str, BUFSIZ - 1, stdin);
E 28
		if (special_case(in_str, defaults->office_phone))
			break;
		remove_hyphens(in_str);
D 18
		if (strlen(in_str) == 8 && strcmpn(in_str, "642", 3) == 0)
			(void) strcpy(in_str, in_str+3);
		if (strlen(in_str) == 7 && strcmpn(in_str, "x2", 2) == 0)
			(void) strcpy(in_str, in_str+2);
		if (strlen(in_str) == 6 && in_str[0] == '2')
			(void) strcpy(in_str, in_str+1);
	} while (illegal_input(in_str) || not_all_digits(in_str)
		 || wrong_length(in_str, 4));
E 18
I 18
	} while (illegal_input(in_str) || not_all_digits(in_str));
E 18
	(void) strcat(strcat(answer, ","), in_str);
	/*
	 * Get home phone number.
	 * Remove hyphens if present.
	 */
	do {
		printf("Home Phone (Ex: 9875432) [%s]: ", defaults->home_phone);
D 28
		(void) fgets(in_str, BUFSIZ, stdin);
E 28
I 28
		(void) fgets(in_str, BUFSIZ - 1, stdin);
E 28
		if (special_case(in_str, defaults->home_phone))
			break;
		remove_hyphens(in_str);
	} while (illegal_input(in_str) || not_all_digits(in_str));
	(void) strcat(strcat(answer, ","), in_str);
	if (strcmp(answer, pwd->pw_gecos) == 0) {
D 28
		printf("Finger information unchanged.\n");
E 28
I 28
		puts("Finger information unchanged.");
E 33
I 33
	if (makedb(temp)) {
		fprintf(stderr, "passwd: mkpasswd failed");
bad:		fprintf(stderr, "; password unchanged.\n");
		(void)unlink(temp);
E 33
E 28
		exit(1);
	}
D 33
	return (answer);
}
E 33

D 33
/*
D 29
 * Prints an error message if a ':' or a newline is found in the string.
 * A message is also printed if the input string is too long.
 * The password file uses :'s as seperators, and are not allowed in the "gcos"
 * field.  Newlines serve as delimiters between users in the password file,
 * and so, those too, are checked for.  (I don't think that it is possible to
E 29
I 29
 * Prints an error message if a ':', ',' or a newline is found in the string.
 * A message is also printed if the input string is too long.  The password
 * file uses :'s as separators, and are not allowed in the "gcos" field;
 * commas are used as separators in the gcos field, so are disallowed.
 * Newlines serve as delimiters between users in the password file, and so,
 * those too, are checked for.  (I don't think that it is possible to
E 29
 * type them in, but better safe than sorry)
 *
D 29
 * Returns '1' if a colon or newline is found or the input line is too long.
E 29
I 29
 * Returns '1' if a colon, comma or newline is found or the input line is
 * too long.
E 29
 */
illegal_input(input_str)
	char *input_str;
{
	char *ptr;
	int error_flag = 0;
	int length = strlen(input_str);

D 29
	if (index(input_str, ':')) {
D 28
		printf("':' is not allowed.\n");
E 28
I 28
		puts("':' is not allowed.");
E 29
I 29
	if (strpbrk(input_str, ",:")) {
		puts("':' and ',' are not allowed.");
E 29
E 28
		error_flag = 1;
	}
	if (input_str[length-1] != '\n') {
		/* the newline and the '\0' eat up two characters */
		printf("Maximum number of characters allowed is %d\n",
			BUFSIZ-2);
		/* flush the rest of the input line */
		while (getchar() != '\n')
			/* void */;
		error_flag = 1;
	}
E 33
	/*
D 33
	 * Delete newline by shortening string by 1.
E 33
I 33
	 * possible race; have to rename four files, and someone could slip
	 * in between them.  LOCK_EX and rename the ``passwd.dir'' file first
	 * so that getpwent(3) can't slip in; the lock should never fail and
	 * it's unclear what to do if it does.  Rename ``ptmp'' last so that
	 * passwd/vipw/chpass can't slip in.
E 33
	 */
D 33
	input_str[length-1] = '\0';
	/*
	 * Don't allow control characters, etc in input string.
	 */
D 28
	for (ptr=input_str; *ptr != '\0'; ptr++) {
		if ((int) *ptr < 040) {
			printf("Control characters are not allowed.\n");
E 28
I 28
	for (ptr = input_str; *ptr; ptr++)
		if (!isprint(*ptr)) {
			puts("Control characters are not allowed.");
E 28
			error_flag = 1;
			break;
		}
D 28
	}
E 28
	return (error_flag);
E 33
I 33
	(void)setpriority(PRIO_PROCESS, 0, -20);
	fend = strcpy(from, temp) + strlen(temp);
D 35
	tend = strcpy(to, passwd) + strlen(passwd);
E 35
I 35
	tend = strcpy(to, _PATH_PASSWD) + strlen(_PATH_PASSWD);
E 35
	bcopy(".dir", fend, 5);
	bcopy(".dir", tend, 5);
	if ((fd = open(from, O_RDONLY, 0)) >= 0)
		(void)flock(fd, LOCK_EX);
	/* here we go... */
	(void)rename(from, to);
	bcopy(".pag", fend, 5);
	bcopy(".pag", tend, 5);
	(void)rename(from, to);
	bcopy(".orig", fend, 6);
	(void)rename(from, _PATH_PASSWD);
	(void)rename(temp, passwd);
	/* done! */
	exit(0);
E 45
I 45
	exit(local_passwd(uname));
E 45
E 33
}

I 51
void
E 51
D 33
/*
 * Removes '-'s from the input string.
 */
remove_hyphens(str)
	char *str;
E 33
I 33
D 34
copy(name, np, fp)
E 34
I 34
D 45
copy(name, np, fp, pw)
E 34
	char *name, *np;
	FILE *fp;
I 34
	struct passwd *pw;
E 34
E 33
{
I 34
	register int done;
E 34
D 33
	char *hyphen;
E 33
I 33
	register char *p;
D 34
	char buf[1024], *index();
E 34
I 34
	char buf[1024];
E 34
E 33

D 33
	while ((hyphen = index(str, '-')) != NULL)
		(void) strcpy(hyphen, hyphen+1);
}

/*
 *  Checks to see if 'str' contains only digits (0-9).  If not, then
 *  an error message is printed and '1' is returned.
 */
not_all_digits(str)
D 28
	char *str;
E 28
I 28
	register char *str;
E 28
{
D 28
	char *ptr;

	for (ptr = str; *ptr != '\0'; ++ptr)
		if (!isdigit(*ptr)) {
			printf("Phone numbers can only contain digits.\n");
			return (1);
E 28
I 28
	for (; *str; ++str)
		if (!isdigit(*str)) {
			puts("Phone numbers may only contain digits.");
			return(1);
E 33
I 33
D 34
	while (fgets(buf, sizeof(buf), stdin)) {
E 34
I 34
	for (done = 0; fgets(buf, sizeof(buf), stdin);) {
E 34
		/* skip lines that are too big */
		if (!index(buf, '\n')) {
			fprintf(stderr, "passwd: line too long.\n");
			return(0);
E 33
E 28
		}
I 34
		if (done) {
			fprintf(fp, "%s", buf);
			continue;
		}
E 34
D 18
	return (0);
}

/*
 * Returns 1 when the length of the input string is not zero or equal to n.
 * Prints an error message in this case.
 */
wrong_length(str, n)
	char *str;
	int n;
{

	if (strlen(str) != 0 && strlen(str) != n) {
		printf("The phone number should be %d digits long.\n", n);
		return (1);
	}
E 18
D 28
	return (0);
E 28
I 28
D 33
	return(0);
E 28
}

/*
D 14
 * Make sure that building is 'E' or 'C'.
 * Error correction is done if building is 'e', 'c', "evans", or "cory".
E 14
I 14
 * Deal with Berkeley buildings.  Abbreviating Cory to C and Evans to E.
E 14
 * Correction changes "str".
D 14
 * The finger program determines the building by looking at the last
 * character.  Currently, finger only allows that character to be 'E' or 'C'.
E 14
 *
 * Returns 1 if incorrect room format.
 * 
 * Note: this function assumes that the newline has been removed from str.
 */
illegal_building(str)
D 14
	char *str;
E 14
I 14
	register char *str;
E 14
{
	int length = strlen(str);
D 14
	char *last_ch, *ptr;
E 14
I 14
	register char *ptr;
E 14

	/*
D 14
	 * Zero length strings are acceptable input.
E 14
I 14
	 * If the string is [Ee]vans or [Cc]ory or ends in
	 * [ \t0-9][Ee]vans or [ \t0-9M][Cc]ory, then contract the name
	 * into 'E' or 'C', as the case may be, and delete leading blanks.
E 14
	 */
D 14
	if (length == 0)
		return (0);
	/*
	 * Delete "vans" and "ory".
	 */
	if (strcmpn(str+length-4, "vans", 4) == 0) {
		length -= 4;
		str[length] = '\0';
	}
	if (strcmpn(str+length-3, "ory", 3) == 0) {
		length -= 3;
		str[length] = '\0';
	}
	last_ch = str+length-1;
	/*
	 * Now change e to E or c to C.
	 */
	if (*last_ch == 'e')
		*last_ch = 'E';
	if (*last_ch == 'c')
		*last_ch = 'C';
	/*
	 * Delete any spaces before the E or C.
	 */
D 9
	for (ptr = last_ch - 1; ptr > str && *ptr != ' '; ptr--)
E 9
I 9
	for (ptr = last_ch - 1; ptr > str && *ptr == ' '; ptr--)
E 9
		;
	(void) strcpy(ptr+1, last_ch);
	/*
	 * Make sure building is evans or cory.
	 */
	if (*last_ch != 'E' && *last_ch != 'C') {
		printf("%s%s%s",
			"The finger program requires that your",
			" office be in Cory or Evans.\n",
			"Enter this as (for example) 597E or 197C.\n");
		return (1);
E 14
I 14
	if (length >= 5 && strcmp(ptr = str + length - 4, "vans") == 0 &&
	    (*--ptr == 'e' || *ptr == 'E') &&
	    (--ptr < str || isspace(*ptr) || isdigit(*ptr))) {
		for (; ptr > str && isspace(*ptr); ptr--)
			;
		ptr++;
		*ptr++ = 'E';
		*ptr = '\0';
	} else
	if (length >= 4 && strcmp(ptr = str + length - 3, "ory") == 0 &&
	    (*--ptr == 'c' || *ptr == 'C') &&
	    (--ptr < str || *ptr == 'M' || isspace(*ptr) || isdigit(*ptr))) {
		for (; ptr > str && isspace(*ptr); ptr--)
			;
		ptr++;
		*ptr++ = 'C';
		*ptr = '\0';
E 33
I 33
		if (!(p = index(buf, ':'))) {
			fprintf(stderr, "passwd: corrupted entry.\n");
			return(0);
		}
		*p = '\0';
		if (strcmp(buf, name)) {
			*p = ':';
			fprintf(fp, "%s", buf);
			continue;
		}
		if (!(p = index(++p, ':'))) {
			fprintf(stderr, "passwd: corrupted entry.\n");
			return(0);
		}
D 34
		fprintf(fp, "%s:%s%s", buf, np, p);
E 34
I 34
		/*
		 * reset change time to zero; when classes are implemented,
		 * go and get the "offset" value for this class and reset
		 * the timer.
		 */
		fprintf(fp, "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s\n",
		    pw->pw_name, np, pw->pw_uid, pw->pw_gid,
		    pw->pw_class, 0L, pw->pw_expire, pw->pw_gecos,
		    pw->pw_dir, pw->pw_shell);
		done = 1;
E 34
E 33
E 14
	}
D 33
	return (0);
E 33
I 33
	return(1);
E 33
}

D 33
/*
 * get_defaults picks apart "str" and returns a structure points.
 * "str" contains up to 4 fields separated by commas.
 * Any field that is missing is set to blank.
 */
struct default_values *
get_defaults(str)
	char *str;
E 33
I 33
char *
getnewpasswd(pw, temp)
	register struct passwd *pw;
	char *temp;
E 33
{
D 33
	struct default_values *answer;
I 28
	char	*malloc();
E 33
I 33
	register char *p, *t;
D 34
	char buf[10], salt[2], *crypt(), *getpass(), *strcpy();
E 34
I 34
D 38
	char buf[10], salt[2], *crypt(), *getpass();
E 38
I 38
	char buf[_PASSWORD_LEN+1], salt[2], *crypt(), *getpass();
E 38
I 37
	int tries = 0;
E 37
E 34
	time_t time();
E 33
E 28
D 21
	char *malloc();
E 21

D 33
	answer = (struct default_values *)
		malloc((unsigned)sizeof(struct default_values));
	if (answer == (struct default_values *) NULL) {
D 28
		fprintf(stderr,
			"\nUnable to allocate storage in get_defaults!\n");
E 28
I 28
		fputs("\nUnable to allocate storage in get_defaults!\n", stderr);
E 33
I 33
	if (uid && pw->pw_passwd &&
	    strcmp(crypt(getpass("Old password:"), pw->pw_passwd),
	    pw->pw_passwd)) {
		(void)printf("passwd: %s.\n", strerror(EACCES));
		(void)unlink(temp);
E 33
E 28
		exit(1);
	}
D 33
	/*
	 * Values if no corresponding string in "str".
	 */
	answer->name = str;
	answer->office_num = "";
	answer->office_phone = "";
	answer->home_phone = "";
	str = index(answer->name, ',');
	if (str == 0) 
		return (answer);
	*str = '\0';
	answer->office_num = str + 1;
	str = index(answer->office_num, ',');
	if (str == 0) 
		return (answer);
	*str = '\0';
	answer->office_phone = str + 1;
	str = index(answer->office_phone, ',');
	if (str == 0) 
		return (answer);
	*str = '\0';
	answer->home_phone = str + 1;
	return (answer);
E 33
I 33

	for (buf[0] = '\0';;) {
		p = getpass("New password:");
		if (!*p) {
			(void)printf("Password unchanged.\n");
			(void)unlink(temp);
			exit(0);
		}
D 37
		if (strlen(p) <= 5) {
E 37
I 37
		if (strlen(p) <= 5 && (uid != 0 || tries++ < 2)) {
E 37
			printf("Please enter a longer password.\n");
			continue;
		}
		for (t = p; *t && islower(*t); ++t);
D 37
		if (!*t) {
E 37
I 37
		if (!*t && (uid != 0 || tries++ < 2)) {
E 37
			printf("Please don't use an all-lower case password.\nUnusual capitalization, control characters or digits are suggested.\n");
			continue;
		}
		(void)strcpy(buf, p);
		if (!strcmp(buf, getpass("Retype new password:")))
			break;
		printf("Mismatch; try again, EOF to quit.\n");
	}
	/* grab a random printable character that isn't a colon */
	(void)srandom((int)time((time_t *)NULL));
D 38
	while ((salt[0] = random() % 93 + 33) == ':');
	while ((salt[1] = random() % 93 + 33) == ':');
E 38
I 38
#ifdef NEWSALT
	salt[0] = '_';
	to64(&salt[1], (long)(29*25), 4);
	to64(&salt[5], (long)random(), 4);
#else
	to64(&salt[0], (long)random(), 2);
#endif
E 38
	return(crypt(buf, salt));
I 38
}

static unsigned char itoa64[] =		/* 0..63 => ascii-64 */
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

to64(s, v, n)
	register char *s;
	register long v;
	register int n;
{
	while (--n >= 0) {
		*s++ = itoa64[v&0x3f];
		v >>= 6;
	}
E 38
E 33
}

D 33
/*
 *  special_case returns true when either the default is accepted
 *  (str = '\n'), or when 'none' is typed.  'none' is accepted in
 *  either upper or lower case (or any combination).  'str' is modified
 *  in these two cases.
 */
special_case(str,default_str)
	char *str, *default_str;
E 33
I 33
makedb(file)
	char *file;
E 33
{
D 33
	static char word[] = "none\n";
	char *ptr, *wordptr;
E 33
I 33
D 36
	int status, pid, w;
E 36
I 36
	union wait pstat;
D 44
	pid_t pid, waitpid();
E 44
I 44
	pid_t pid;
E 44
E 36
E 33

D 33
	/*
	 *  If the default is accepted, then change the old string do the 
	 *  default string.
	 */
	if (*str == '\n') {
		(void) strcpy(str, default_str);
		return (1);
E 33
I 33
	if (!(pid = vfork())) {
		execl(_PATH_MKPASSWD, "mkpasswd", "-p", file, NULL);
		_exit(127);
E 33
	}
D 33
	/*
	 *  Check to see if str is 'none'.  (It is questionable if case
	 *  insensitivity is worth the hair).
	 */
	wordptr = word-1;
	for (ptr = str; *ptr != '\0'; ++ptr) {
		++wordptr;
		if (*wordptr == '\0')	/* then words are different sizes */
			return (0);
		if (*ptr == *wordptr)
			continue;
		if (isupper(*ptr) && (tolower(*ptr) == *wordptr))
			continue;
		/*
		 * At this point we have a mismatch, so we return
		 */
		return (0);
	}
	/*
	 * Make sure that words are the same length.
	 */
	if (*(wordptr+1) != '\0')
		return (0);
	/*
	 * Change 'str' to be the null string
	 */
	*str = '\0';
	return (1);
E 33
I 33
D 36
	while ((w = wait(&status)) != pid && w != -1);
	return(w == -1 || status);
E 36
I 36
D 44
	return(waitpid(pid, &pstat, 0) == -1 ? -1 : pstat.w_status);
E 44
I 44
	return(waitpid(pid, (int *)&pstat, 0) == -1 ? -1 : pstat.w_status);
E 44
E 36
E 33
E 8
E 6
E 5
}
I 41

E 45
usage()
{
I 51

E 51
#ifdef	KERBEROS
D 45
	fprintf(stderr, "usage: passwd [-l] user\n");
E 45
I 45
	(void)fprintf(stderr, "usage: passwd [-l] user\n");
E 45
#else
D 45
	fprintf(stderr, "usage: passwd user\n");
E 45
I 45
	(void)fprintf(stderr, "usage: passwd user\n");
E 45
#endif
I 51
	exit(1);
E 51
}
D 43


#ifdef	KERBEROS 
KTEXT_ST	ticket;
long		authopts = 0L;
Key_schedule	random_schedule;
char		realm[REALM_SZ], krbhst[MAX_HSTNM];
static		struct	kpasswd_data	proto_data;
static		des_cblock		okey;
static		Key_schedule	osched;
int		sock;
int		finish();
#define		PROTO	"tcp"

static struct timeval	timeout = { CLIENT_KRB_TIMEOUT, 0 };

do_krb_passwd()
{
	struct servent *se;
	struct hostent *host;
	struct sockaddr_in sin;
	int rval;
D 42
	char pass[MAX_PW_LEN], password[MAX_PW_LEN];
E 42
I 42
	char pass[_PASSWORD_LEN], password[_PASSWORD_LEN];
E 42
	fd_set readfds;
	CREDENTIALS	cred;

	static struct rlimit rl = { 0, 0 };

	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGTSTP, SIG_IGN);

	if (setrlimit(RLIMIT_CORE, &rl) < 0) {
		perror("setrlimit");
		return(1);
	}

	if ((se = getservbyname(SERVICE, PROTO)) == NULL) {
		fprintf(stderr, "couldn't find entry for service %s/%s\n",
			SERVICE, PROTO);
		return(1);
	}

	if ((rval = krb_get_lrealm(realm,1)) != KSUCCESS) {
		fprintf(stderr, "couldn't get local Kerberos realm: %s\n",
			krb_err_txt[rval]);
		return(1);
	}

	if ((rval = krb_get_krbhst(krbhst, realm, 1)) != KSUCCESS) {
		fprintf(stderr, "couldn't get Kerberos host: %s\n",
			krb_err_txt[rval]);
		return(1);
	}

	if ((host = gethostbyname(krbhst)) == NULL) {
		fprintf(stderr, "couldn't get host entry for krb host %s\n",
			krbhst);
		return(1);
	}

	sin.sin_family = host->h_addrtype;
	bcopy(host->h_addr, (char *) &sin.sin_addr, host->h_length);
	sin.sin_port = se->s_port;

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		return(1);
	}

	if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("connect");
		close(sock);
		return(1);
	}

	rval = krb_sendauth(
		authopts,		/* NOT mutual */
		sock,
		&ticket,		/* (filled in) */
		SERVICE,
		krbhst,			/* instance (krbhst) */
		realm,			/* dest realm */
		(u_long) getpid(),	/* checksum */
		NULL,			/* msg data */
		NULL,			/* credentials */ 
		NULL,			/* schedule */
		NULL,			/* local addr */
		NULL,			/* foreign addr */
		"KPWDV0.1"
	);


	if (rval != KSUCCESS) {
		fprintf(stderr, "Kerberos sendauth error: %s\n",
			krb_err_txt[rval]);
		return(1);
	}

	krb_get_cred("krbtgt", realm, realm, &cred);

	printf("Changing Kerberos password for %s.%s@%s.\n",
		cred.pname, cred.pinst, realm);

	if (des_read_pw_string(pass,
	    sizeof(pass)-1, "Old Kerberos password:", 0)) {
		fprintf(stderr,
			"error reading old Kerberos password\n");
		return(1);
	}

	(void)des_string_to_key(pass, okey);
	(void)des_key_sched(okey, osched);
	(void)des_set_key(okey, osched);

	/* wait on the verification string */

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);

	rval =
	  select(sock + 1, &readfds, (fd_set *) 0, (fd_set *) 0, &timeout);

	if ((rval < 1) || !FD_ISSET(sock, &readfds)) {
		if(rval == 0) {
			fprintf(stderr, "timed out (aborted)\n");
			cleanup();
			return(1);
		}
		fprintf(stderr, "select failed (aborted)\n");
		cleanup();
		return(1);
	}

	/* read verification string */

	if (des_read(sock, &proto_data, sizeof(proto_data)) !=
	    sizeof(proto_data)) {
		fprintf(stderr,
		    "couldn't read verification string (aborted)\n");
		cleanup();
		return(1);
	}

	(void)signal(SIGHUP, finish);
	(void)signal(SIGINT, finish);

	if (strcmp(SECURE_STRING, proto_data.secure_msg) != 0) {
		cleanup();
		/* don't complain loud if user just hit return */
		if (pass == NULL || (!*pass))
			return(0);
		fprintf(stderr, "Sorry\n");
		return(1);
	}

	(void)des_key_sched(proto_data.random_key, random_schedule);
	(void)des_set_key(proto_data.random_key, random_schedule);
	(void)bzero(pass, sizeof(pass));

	if (des_read_pw_string(pass,
	    sizeof(pass)-1, "New Kerberos password:", 0)) {
		fprintf(stderr,
			"error reading new Kerberos password (aborted)\n");
		cleanup();
		return(1);
	}

	if (des_read_pw_string(password,
	    sizeof(password)-1, "Retype new Kerberos password:", 0)) {
		fprintf(stderr,
			"error reading new Kerberos password (aborted)\n");
		cleanup();
		return(1);
	}

	if (strcmp(password, pass) != 0) {
		fprintf(stderr, "password mismatch (aborted)\n");
		cleanup();
		return(1);
	}

	if (strlen(pass) == 0)
		printf("using NULL password\n");

	send_update(sock, password, SECURE_STRING);

	/* wait for ACK */

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);

	rval =
	  select(sock + 1, &readfds, (fd_set *) 0, (fd_set *) 0, &timeout);
	if ((rval < 1) || !FD_ISSET(sock, &readfds)) {
		if(rval == 0) {
			fprintf(stderr, "timed out reading ACK (aborted)\n");
			cleanup();
			exit(1);
		}
		fprintf(stderr, "select failed (aborted)\n");
		cleanup();
		exit(1);
	}

	recv_ack(sock);
	cleanup();
	exit(0);
}

send_update(dest, pwd, str)
	int	dest;
	char	*pwd, *str;
{
	static struct	update_data	ud;
D 42
	strncpy(ud.secure_msg, str, MAX_PW_LEN);
E 42
I 42
	strncpy(ud.secure_msg, str, _PASSWORD_LEN);
E 42
	strncpy(ud.pw, pwd, sizeof(ud.pw));
	if (des_write(dest, &ud, sizeof(ud)) != sizeof(ud)) {
		fprintf(stderr, "couldn't write pw update (abort)\n");
		bzero(ud, sizeof(ud));
		cleanup();
		exit(1);
	}
}

recv_ack(remote)
	int	remote;
{
	int	cc;
	char	buf[BUFSIZ];
	cc = des_read(remote, buf, sizeof(buf));
	if (cc <= 0) {
		fprintf(stderr, "error reading acknowledgement (aborted)\n");
		cleanup();
		exit(1);
	}
	printf("%s", buf);
}

cleanup()
{
	(void)bzero(&proto_data, sizeof(proto_data));
	(void)bzero(okey, sizeof(okey));
	(void)bzero(osched, sizeof(osched));
	(void)bzero(random_schedule, sizeof(random_schedule));
}

finish()
{
	(void)close(sock);
	exit(1);
}

#endif /* KERBEROS */
E 43
E 41
E 1
