h01443
s 00004/00006/00894
d D 8.2 94/04/02 07:43:15 pendry 61 60
c prettyness police.
c avoid additional fork when doing local-local and remote-remote copies
e
s 00005/00005/00895
d D 8.1 93/05/31 15:08:17 bostic 60 59
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00050/00058/00850
d D 5.36 93/04/29 13:39:03 bostic 59 57
c use err/warn from the C library, lint, minor cleanups
e
s 00000/00037/00871
d D 5.35.1.1 92/12/02 16:52:51 mckusick 58 57
c delete data-stream encryption for the foreign sites (4.4BSD alpha)
e
s 00019/00016/00889
d D 5.35 92/10/17 14:10:58 bostic 57 56
c snprintf used incorrectly, lint; from Craig
e
s 00067/00038/00838
d D 5.34 92/06/30 08:43:31 andrew 56 55
c better error checking when reading/writing,
c handle read-only directories and NFS files; more of keith's clean-ups
e
s 00272/00354/00604
d D 5.33 92/06/20 12:29:36 bostic 55 53
c quads broke size transfer, add -K option
c not diffable, I broke out several utility functions into util.c, prototyped
c the world, generally cleaned up anything I didn't like
e
s 00000/00041/00917
d D 5.32.1.1 91/08/20 16:30:10 mckusick 54 53
c delete data-stream encryption for the foreign sites (Network, Release 2)
e
s 00064/00055/00894
d D 5.32 91/02/25 07:54:53 bostic 53 52
c ANSI fixes (plus one real bug fix the compiler found)
c convert sprintf(3) to snprintf(3); convert struct direct to struct dirent
e
s 00025/00024/00924
d D 5.31 90/11/28 11:52:55 torek 52 50
c watch ?: precedence; use <stdlib.h> headers; malloc argument now size_t;
c minor lint
e
s 00000/00041/00907
d D 5.30.1.1 90/10/21 21:18:07 mckusick 51 50
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00030/00004/00918
d D 5.30 90/10/21 21:14:03 mckusick 50 49
c break out processing of -x into ifdef CRYPT
e
s 00002/00002/00920
d D 5.29 90/06/29 19:01:17 karels 49 48
c fix perror message for tos
e
s 00016/00006/00906
d D 5.28 90/06/27 18:42:20 karels 48 47
c setreuid => seteuid; set IP type-of-service
e
s 00001/00011/00911
d D 5.27 90/05/31 20:38:15 bostic 47 46
c new copyright notice
e
s 00001/00000/00921
d D 5.26 90/05/31 11:57:51 bostic 46 45
c fix kerberos include stuff
e
s 00001/00001/00920
d D 5.25 90/05/15 19:40:35 bostic 45 44
c string.h is ANSI C include file
e
s 00001/00001/00920
d D 5.24 90/05/12 15:38:32 bostic 44 43
c krb in include/kerberosIV now
e
s 00002/00009/00919
d D 5.23 89/12/06 18:00:23 bostic 43 42
c get back reasonable header; don't need types.h
e
s 00146/00098/00782
d D 5.22 89/08/30 20:03:53 kfall 42 41
c Kerberized version.
e
s 00035/00025/00845
d D 5.21 89/07/17 18:53:50 bostic 41 40
c sink() returns multiple messages; bug report 4.3BSD-tahoe/bin/26
c NULL dereference; use strerror() rather than sys_errlist[]
e
s 00001/00001/00869
d D 5.20 89/05/23 18:29:32 bostic 40 39
c one more try, with feeling
e
s 00012/00011/00858
d D 5.19 89/05/23 14:14:14 bostic 39 38
c add <newlines> to error messages; don't allow overflow in error();
c minor fix to earlier changes, don't delete <newline> until error written
e
s 00173/00144/00696
d D 5.18 89/05/21 16:55:02 bostic 38 37
c buffer overflow; bug report 4.3BSD-tahoe/usr.sbin/3
e
s 00021/00010/00819
d D 5.17 89/05/21 15:16:01 bostic 37 36
c I will write on the blackboard 100 times: I will not only test the
c obscure cases, but also the blindingly obvious ones...
e
s 00326/00368/00503
d D 5.16 89/05/21 15:10:56 bostic 36 35
c break local/remote cases out of main loop; break Kerberos code
c out into its own routine; add getopt(3); some formatting/lint cleanup
e
s 00003/00003/00868
d D 5.15 89/03/05 21:49:47 bostic 35 34
c put sccsid's back in...
e
s 00008/00007/00863
d D 5.14 89/03/05 21:49:04 bostic 34 33
c add pathname.sh
e
s 00028/00001/00842
d D 5.13 89/01/25 17:59:01 kfall 33 32
c fix up case when Kerberos isn't available (switch kshell->shell)
e
s 00116/00003/00727
d D 5.12 89/01/25 17:11:48 kfall 32 31
c add Kerberos ifdefs
e
s 00004/00004/00726
d D 5.11 88/09/22 16:59:46 bostic 31 30
c fixes for ANSI C; allocbuf returns NULL pointer, not -1
e
s 00017/00006/00713
d D 5.10 88/09/20 16:31:11 bostic 30 29
c Berkeley specific copyright
e
s 00001/00001/00718
d D 5.9 87/10/22 09:55:43 bostic 29 28
c ANSI C; sprintf now returns an int.
e
s 00006/00006/00713
d D 5.8 87/09/28 18:26:40 bostic 28 27
c change "file changed size" error to a real read error message
e
s 00015/00005/00704
d D 5.7 87/09/10 15:26:01 bostic 27 26
c usage for only 1 argument; do copy/truncate, not create 
c RCP clobbers files; bug report 4.3BSD/bin/24
e
s 00004/00002/00705
d D 5.6 87/07/27 16:28:38 bostic 26 25
c rcp dereferences NULL; bug report 4.3BSD/bin/36
e
s 00002/00002/00705
d D 5.5 87/05/05 08:49:41 bostic 25 24
c don't use search path for rsh, hardwire it in; bug report 4.3BSD/bin/65
e
s 00019/00061/00688
d D 5.4 85/09/12 16:14:41 bloom 24 23
c fix protocol error returns (karels), make work with named and remove old code
e
s 00008/00003/00741
d D 5.3 85/06/08 01:02:26 lepreau 23 21
c overload -p to also mean "preserve modes/ignore umask"
e
s 00007/00002/00742
d R 5.3 85/06/08 00:23:52 lepreau 22 21
c overload -p to also mean "preserve mode info/ignore umask"
e
s 00125/00052/00619
d D 5.2 85/06/08 00:09:58 lepreau 21 20
c add -p option to preserve file & dir a/mtimes
e
s 00014/00002/00657
d D 5.1 85/05/31 09:24:56 dist 20 19
c Add copyright
e
s 00073/00023/00586
d D 4.16 85/05/29 16:15:15 mckusick 19 18
c use a file system optimal blocksize
e
s 00051/00000/00558
d D 4.15 85/04/11 09:47:55 ralph 18 16
c make changes ifdef NAMESERVER for others to use.
e
s 00023/00035/00523
d R 4.15 85/04/11 09:11:34 ralph 17 16
c undo user@ change until nameser is really used.
e
s 00035/00023/00523
d D 4.14 85/03/05 16:15:23 ralph 16 15
c change to user@host:file to avoid conflicts with the nameserver.
e
s 00028/00063/00518
d D 4.13 85/02/27 11:45:21 ralph 15 14
c removed replaced makedir with mkdir, more speedups.
e
s 00010/00003/00571
d D 4.12 85/02/20 16:01:25 ralph 14 13
c use getservbyname() instead of constants.
e
s 00031/00039/00543
d D 4.11 85/02/16 17:49:52 serge 13 11
c streamline susystem() and makedir() by removing unnecessary fork's
e
s 00033/00039/00543
d R 4.11 85/01/09 18:26:08 serge 12 11
c streamline susystem() and makedir() by removing unnecessary fork's
e
s 00002/00001/00580
d D 4.10 84/02/13 15:49:44 ralph 11 9
c fix access check of parent directory for names like /foo.
e
s 00007/00010/00571
d R 4.10 84/01/30 15:10:13 ralph 10 9
c need to copy user name due to new getpwnam().
e
s 00006/00006/00575
d D 4.9 84/01/26 15:59:56 ralph 9 8
c fix 3rd party transfers
e
s 00017/00005/00564
d D 4.8 83/08/12 11:58:58 ralph 8 7
c fixes "No match." message from shell.
e
s 00001/00001/00568
d D 4.7 83/07/03 16:04:28 sam 7 6
c typo
e
s 00008/00002/00561
d D 4.6 83/07/01 03:01:53 sam 6 5
c default null name after : to "."
e
s 00005/00004/00558
d D 4.5 83/06/10 23:34:10 sam 5 4
c new signals, no libjobs
e
s 00005/00003/00557
d D 4.4 82/11/14 15:09:19 sam 4 3
c convert to 4.1c sys calls and directory layout
e
s 00002/00002/00558
d D 4.3 82/05/09 23:58:49 mckusick 3 2
c update to new fs
e
s 00007/00004/00553
d D 4.2 82/05/05 19:00:27 mckusick 2 1
c add tef's mods for pdp-11's
e
s 00557/00000/00000
d D 4.1 82/04/02 10:28:53 wnj 1 0
c date and time created 82/04/02 10:28:53 by wnj
e
u
U
f b 
t
T
I 42
D 43

E 43
E 42
I 20
/*
I 42
D 43
 *	$Source:$
 *	$Header:$
 */

/*
E 43
E 42
D 30
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 30
I 30
D 48
 * Copyright (c) 1983 The Regents of the University of California.
E 48
I 48
D 56
 * Copyright (c) 1983, 1990 The Regents of the University of California.
E 56
I 56
D 60
 * Copyright (c) 1983, 1990, 1992 The Regents of the University of California.
E 56
E 48
 * All rights reserved.
E 60
I 60
 * Copyright (c) 1983, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 60
 *
D 47
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
D 35
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 35
I 35
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 47
I 47
 * %sccs.include.redist.c%
E 47
E 35
E 30
 */

E 20
I 1
#ifndef lint
D 20
static char sccsid[] = "%W% %E%";
#endif
E 20
I 20
D 60
char copyright[] =
D 30
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 30
I 30
D 32
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 32
I 32
D 35
"@(#) Copyright (c) 1983 The Regents of the University of California.\n\
E 35
I 35
D 42
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 42
I 42
D 43
"@(#) Copyright (c) 1983 The Regents of the University of California.\n\
E 43
I 43
D 48
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 48
I 48
D 56
"%Z% Copyright (c) 1983, 1990 The Regents of the University of California.\n\
E 56
I 56
"%Z% Copyright (c) 1983, 1990, 1992 The Regents of the University of California.\n\
E 56
E 48
E 43
E 42
E 35
E 32
E 30
 All rights reserved.\n";
E 60
I 60
static char copyright[] =
"%Z% Copyright (c) 1983, 1990, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 60
D 30
#endif not lint
E 30
I 30
#endif /* not lint */
E 30

#ifndef lint
D 32
static char sccsid[] = "%W% (Berkeley) %G%";
E 32
I 32
D 35
static char sccsid[] = "@(#)rcp.c	5.11 (Berkeley) 9/22/88";
E 35
I 35
D 42
static char sccsid[] = "%W% (Berkeley) %G%";
E 42
I 42
D 43
static char sccsid[] = "@(#)rcp.c	5.21 (Berkeley) 7/17/89";
E 43
I 43
static char sccsid[] = "%W% (Berkeley) %G%";
E 43
E 42
E 35
E 32
D 30
#endif not lint
E 30
I 30
#endif /* not lint */
E 30
E 20

I 5
D 55
/*
 * rcp
 */
E 55
E 5
D 4
#include <stdio.h>
#include <signal.h>
E 4
D 3
#include <sys/types.h>
E 3
I 3
#include <sys/param.h>
I 42
D 43
#include <sys/types.h>
E 43
E 42
I 27
D 53
#include <sys/file.h>
E 53
E 27
E 3
#include <sys/stat.h>
I 21
#include <sys/time.h>
E 21
D 55
#include <sys/ioctl.h>
E 55
D 4
#include <net/in.h>
E 4
I 4
D 36

E 36
I 36
D 53
#include <sys/dir.h>
#include <sys/signal.h>
E 53
I 53
#include <sys/socket.h>
D 55
#include <sys/wait.h>
E 55
E 53
E 36
#include <netinet/in.h>
I 48
#include <netinet/in_systm.h>
#include <netinet/ip.h>
I 55

D 57
#include <signal.h>
#include <netdb.h>
E 57
I 57
#include <ctype.h>
E 57
E 55
I 53
#include <dirent.h>
I 59
#include <err.h>
E 59
I 57
#include <errno.h>
E 57
#include <fcntl.h>
I 57
#include <netdb.h>
E 57
D 55
#include <signal.h>
E 55
E 53
E 48
D 36

#include <stdio.h>
#include <signal.h>
E 36
E 4
#include <pwd.h>
D 36
#include <ctype.h>
E 36
I 14
D 55
#include <netdb.h>
E 55
E 14
D 57
#include <errno.h>
I 36
D 45
#include <strings.h>
E 45
I 45
D 53
#include <string.h>
E 53
I 53
#include <unistd.h>
E 57
I 57
#include <signal.h>
E 57
E 53
E 45
#include <stdio.h>
I 52
#include <stdlib.h>
I 53
#include <string.h>
E 53
E 52
D 57
#include <ctype.h>
E 57
I 57
#include <string.h>
#include <unistd.h>

E 57
E 36
I 34
#include "pathnames.h"
I 55
#include "extern.h"
E 55
E 34
D 5
/*
 * rcp
 */
E 5
I 5

I 32
D 36
#ifdef	KERBEROS
E 36
I 36
#ifdef KERBEROS
I 46
#include <kerberosIV/des.h>
E 46
E 36
D 42
#include <kerberos/krb.h>
D 36
char	krb_realm[REALM_SZ];
int	use_kerberos = 1, encrypt = 0;
CREDENTIALS	cred;
Key_schedule	schedule;
E 36
I 36

char krb_realm[REALM_SZ];
int use_kerberos = 1, encrypt = 0;
CREDENTIALS cred;
Key_schedule schedule;
E 42
I 42
D 44
#include <krb.h>
E 44
I 44
#include <kerberosIV/krb.h>
I 55

E 55
E 44
char	dst_realm_buf[REALM_SZ];
char	*dest_realm = NULL;
D 50
int	use_kerberos = 1, encrypt = 0;
E 50
I 50
int	use_kerberos = 1;
E 50
CREDENTIALS 	cred;
Key_schedule	schedule;
extern	char	*krb_realmofhost();
I 50
D 51
D 54
D 58
#ifdef CRYPT
D 53
int	encrypt = 0;
E 50
#define	OPTIONS	"dfkprtx"
E 53
I 53
int	doencrypt = 0;
D 55
#define	OPTIONS	"dfk:prtx"
E 55
I 55
#define	OPTIONS	"dfKk:prtx"
E 55
E 53
#else
E 58
E 54
E 51
I 50
D 53
#define	OPTIONS	"dfkprt"
E 53
I 53
D 55
#define	OPTIONS	"dfk:prt"
E 55
I 55
#define	OPTIONS	"dfKk:prt"
E 55
E 53
D 51
D 54
D 58
#endif
E 58
E 54
E 51
#else
E 50
#define	OPTIONS "dfprt"
E 42
E 36
#endif

E 32
E 5
D 36
int	rem;
D 29
char	*colon(), *index(), *rindex(), *malloc(), *strcpy(), *sprintf();
E 29
I 29
char	*colon(), *index(), *rindex(), *malloc(), *strcpy();
E 29
int	errs;
int	lostconn();
D 21
int	iamremote;

E 21
int	errno;
char	*sys_errlist[];
int	iamremote, targetshouldbedirectory;
int	iamrecursive;
I 21
int	pflag;
E 21
struct	passwd *pwd;
struct	passwd *getpwuid();
I 14
D 15
struct	servent *sp;
E 15
I 15
int	userid;
int	port;
E 36
I 36
D 53
extern int errno;
E 53
D 41
extern char *sys_errlist[];
E 41
struct passwd *pwd;
D 42
int errs, pflag, port, rem, userid;
int iamremote, iamrecursive, targetshouldbedirectory;
E 42
I 42
u_short	port;
uid_t	userid;
int errs, rem;
int pflag, iamremote, iamrecursive, targetshouldbedirectory;
E 42
E 36
E 15
E 14

I 19
D 36
struct buffer {
E 36
I 36
D 38
char cmd[20];			/* must hold "rcp -r -p -d\0" */
E 38
I 38
D 42
#define	CMDNEEDS	20
E 42
I 42
#define	CMDNEEDS	64
E 42
char cmd[CMDNEEDS];		/* must hold "rcp -r -p -d\0" */
E 38

D 55
typedef struct _buf {
E 36
	int	cnt;
	char	*buf;
D 36
} *allocbuf();
E 36
I 36
} BUF;
E 55
I 55
#ifdef KERBEROS
int	 kerberos __P((char **, char *, char *, char *));
void	 oldw __P((const char *, ...));
#endif
int	 response __P((void));
void	 rsource __P((char *, struct stat *));
void	 sink __P((int, char *[]));
void	 source __P((int, char *[]));
void	 tolocal __P((int, char *[]));
void	 toremote __P((char *, int, char *[]));
void	 usage __P((void));
E 55
E 36

I 53
D 55
void lostconn();

E 55
I 55
int
E 55
E 53
E 19
D 36
/*VARARGS*/
int	error();

#define	ga()	 	(void) write(rem, "", 1)

E 36
main(argc, argv)
	int argc;
D 55
	char **argv;
E 55
I 55
	char *argv[];
E 55
{
D 36
	char *targ, *host, *src;
I 18
D 24
#ifndef NAMESERVER
	char *suser, *tuser;
#else NAMESERVER
E 24
E 18
D 16
	char *suser, *tuser;
E 16
I 16
	char *suser, *tuser, *thost;
I 18
D 24
#endif NAMESERVER
E 24
E 18
E 16
	int i;
	char buf[BUFSIZ], cmd[16];
E 36
I 36
D 55
	extern int optind;
I 53
	extern char *optarg;
E 55
E 53
E 36
I 15
	struct servent *sp;
I 36
D 37
	int ch;
E 37
I 37
	int ch, fflag, tflag;
E 37
D 50
	char *targ, *colon();
E 50
I 50
D 55
	char *targ, *shell, *colon();
E 55
I 55
	char *targ, *shell;
E 55
E 50
D 53
	struct passwd *getpwuid();
	int lostconn();
E 53
E 36
E 15
D 14
	
E 14
I 14

I 33
D 36
#ifdef	KERBEROS
E 36
I 36
D 42
#ifdef KERBEROS
E 36
	sp = getservbyname("kshell", "tcp");
D 36
	if(sp == NULL) {
E 36
I 36
	if (sp == NULL) {
E 36
		use_kerberos = 0;
		old_warning("kshell service unknown");
		sp = getservbyname("kshell", "tcp");
	}
#else
E 33
	sp = getservbyname("shell", "tcp");
I 33
#endif
D 36

E 33
	if (sp == NULL) {
		fprintf(stderr, "rcp: shell/tcp: unknown service\n");
E 36
I 36
	if (!sp) {
		(void)fprintf(stderr, "rcp: shell/tcp: unknown service\n");
E 36
		exit(1);
	}
E 14
D 15
	setpwent();
	pwd = getpwuid(getuid());
	endpwent();
E 15
I 15
	port = sp->s_port;
D 36
	pwd = getpwuid(userid = getuid());
E 15
	if (pwd == 0) {
		fprintf(stderr, "who are you?\n");
E 36
I 36

	if (!(pwd = getpwuid(userid = getuid()))) {
		(void)fprintf(stderr, "rcp: unknown user %d.\n", userid);
E 36
		exit(1);
	}
D 21
	argc--, argv++;
	if (argc > 0 && !strcmp(*argv, "-r")) {
		iamrecursive++;
		argc--, argv++;
E 21
I 21

E 42
I 37
	fflag = tflag = 0;
E 37
D 36
	for (argc--, argv++; argc > 0 && **argv == '-'; argc--, argv++) {
		(*argv)++;
		while (**argv) switch (*(*argv)++) {

		    case 'r':
			iamrecursive++;
E 36
I 36
D 42
	while ((ch = getopt(argc, argv, "dfkprtx")) != EOF)
E 42
I 42
	while ((ch = getopt(argc, argv, OPTIONS)) != EOF)
E 42
D 55
		switch(ch) {
D 42
		case 'd':
			targetshouldbedirectory = 1;
E 36
			break;
D 36

I 32
#ifdef	KERBEROS
		    case 'x':
			encrypt = 1;
			des_set_key(cred.session, schedule);
			break;

		    case 'k':
E 36
I 36
		case 'f':			/* "from" */
D 37
			iamremote = 1;
			(void)response();
			(void)setuid(userid);
			source(--argc, ++argv);
			exit(errs);
E 37
I 37
			fflag = 1;
			break;
E 37
#ifdef KERBEROS
		case 'k':
E 36
			strncpy(krb_realm, ++argv, REALM_SZ);
			break;
#endif
E 42
I 42
		/* user-visible flags */
E 42
D 36

E 32
		    case 'p':		/* preserve mtimes and atimes */
			pflag++;
E 36
I 36
		case 'p':			/* preserve access/mod times */
			++pflag;
E 55
I 55
		switch(ch) {			/* User-visible flags. */
		case 'K':
#ifdef KERBEROS
			use_kerberos = 0;
#endif
E 55
E 36
			break;
D 36

		    /* The rest of these are not for users. */
		    case 'd':
			targetshouldbedirectory = 1;
E 36
I 36
D 55
		case 'r':
			++iamrecursive;
E 36
			break;
E 55
D 36

		    case 'f':		/* "from" */
E 36
I 36
D 42
		case 't':			/* "to" */
E 36
D 37
			iamremote = 1;
D 36
			(void) response();
			(void) setuid(userid);
			source(--argc, ++argv);
			exit(errs);

		    case 't':		/* "to" */
			iamremote = 1;
			(void) setuid(userid);
E 36
I 36
			(void)setuid(userid);
E 36
			sink(--argc, ++argv);
			exit(errs);
E 37
I 37
			tflag = 1;
E 42
I 42
#ifdef	KERBEROS
		case 'k':
D 53
			strncpy(dst_realm_buf, ++argv, REALM_SZ);
E 53
I 53
D 55
			strncpy(dst_realm_buf, optarg, REALM_SZ);
E 55
E 53
			dest_realm = dst_realm_buf;
I 55
			(void)strncpy(dst_realm_buf, optarg, REALM_SZ);
E 55
E 42
			break;
I 50
D 51
D 54
D 58
#ifdef CRYPT
E 50
E 37
D 36

		    default:
E 36
I 36
D 42
#ifdef KERBEROS
E 42
		case 'x':
D 53
			encrypt = 1;
E 53
I 53
			doencrypt = 1;
E 53
D 42
			des_set_key(cred.session, schedule);
E 42
I 42
			/* des_set_key(cred.session, schedule); */
E 42
			break;
E 58
E 54
E 51
#endif
I 50
D 51
D 54
D 58
#endif
E 58
E 54
E 51
E 50
I 42
D 55
		/* rshd-invoked options (server) */
E 55
I 55
		case 'p':
			pflag = 1;
			break;
		case 'r':
			iamrecursive = 1;
			break;
						/* Server options. */
E 55
		case 'd':
			targetshouldbedirectory = 1;
			break;
		case 'f':			/* "from" */
			iamremote = 1;
			fflag = 1;
			break;
		case 't':			/* "to" */
			iamremote = 1;
			tflag = 1;
			break;
D 56

E 56
E 42
		case '?':
		default:
E 36
D 27
			fprintf(stderr,
D 23
		"Usage: rcp [-rp] f1 f2, or: rcp [-rp] f1 ... fn d2\n");
E 23
I 23
		"Usage: rcp [-p] f1 f2; or: rcp [-rp] f1 ... fn d2\n");
E 23
			exit(1);
E 27
I 27
			usage();
E 27
		}
E 21
D 36
	}
E 36
I 36
	argc -= optind;
	argv += optind;
I 37

I 42
#ifdef KERBEROS
I 55
	if (use_kerberos) {
E 55
D 50
	sp = getservbyname((encrypt ? "ekshell" : "kshell"), "tcp");
E 50
I 50
D 51
D 54
D 58
#ifdef CRYPT
D 53
	shell = encrypt ? "ekshell" : "kshell";
E 53
I 53
D 55
	shell = doencrypt ? "ekshell" : "kshell";
E 55
I 55
		shell = doencrypt ? "ekshell" : "kshell";
E 55
E 53
#else
E 58
E 54
E 51
D 55
	shell = "kshell";
E 55
I 55
		shell = "kshell";
E 55
D 51
D 54
D 58
#endif
E 58
E 54
E 51
D 55
	sp = getservbyname(shell, "tcp");
E 50
	if (sp == NULL) {
		char	msgbuf[64];
		use_kerberos = 0;
D 53
		(void) sprintf(msgbuf, "can't get entry for %s/tcp service",
D 50
			(encrypt ? "ekshell" : "kshell"));
E 50
I 50
			shell);
E 53
I 53
		(void)snprintf(msgbuf, sizeof(msgbuf),
		    "can't get entry for %s/tcp service", shell);
E 53
E 50
		old_warning(msgbuf);
E 55
I 55
		if ((sp = getservbyname(shell, "tcp")) == NULL) {
			use_kerberos = 0;
			oldw("can't get entry for %s/tcp service", shell);
			sp = getservbyname(shell = "shell", "tcp");
		}
	} else
E 55
D 52
		sp = getservbyname("shell", "tcp");
E 52
I 52
		sp = getservbyname(shell = "shell", "tcp");
E 52
D 55
	}
E 55
#else
D 52
	sp = getservbyname("shell", "tcp");
E 52
I 52
	sp = getservbyname(shell = "shell", "tcp");
E 52
#endif
D 59
	if (sp == NULL) {
D 52
		(void)fprintf(stderr, "rcp: shell/tcp: unknown service\n");
E 52
I 52
		(void)fprintf(stderr, "rcp: %s/tcp: unknown service\n", shell);
E 52
		exit(1);
	}
E 59
I 59
	if (sp == NULL)
		errx(1, "%s/tcp: unknown service", shell);
E 59
	port = sp->s_port;

D 55
	if (!(pwd = getpwuid(userid = getuid()))) {
E 55
I 55
D 59
	if ((pwd = getpwuid(userid = getuid())) == NULL) {
E 55
D 52
		(void)fprintf(stderr, "rcp: unknown user %d.\n", userid);
E 52
I 52
		(void)fprintf(stderr, "rcp: unknown user %d.\n", (int)userid);
E 52
		exit(1);
	}
E 59
I 59
	if ((pwd = getpwuid(userid = getuid())) == NULL)
		errx(1, "unknown user %d", (int)userid);
E 59

E 42
D 55
	if (fflag) {
D 42
		iamremote = 1;
E 42
I 42
		/* follow "protocol", send data */
E 55
I 55
	rem = STDIN_FILENO;		/* XXX */

	if (fflag) {			/* Follow "protocol", send data. */
E 55
E 42
		(void)response();
		(void)setuid(userid);
		source(argc, argv);
		exit(errs);
	}

D 55
	if (tflag) {
D 42
		iamremote = 1;
E 42
I 42
		/* receive data */
E 55
I 55
	if (tflag) {			/* Receive data. */
E 55
E 42
		(void)setuid(userid);
		sink(argc, argv);
		exit(errs);
	}
E 37

E 36
D 21
	if (argc > 0 && !strcmp(*argv, "-d")) {
		targetshouldbedirectory = 1;
		argc--, argv++;
	}
	if (argc > 0 && !strcmp(*argv, "-f")) {
		argc--, argv++; iamremote = 1;
		(void) response();
D 15
		(void) setuid(getuid());
E 15
I 15
		(void) setuid(userid);
E 15
		source(argc, argv);
		exit(errs);
	}
	if (argc > 0 && !strcmp(*argv, "-t")) {
		argc--, argv++; iamremote = 1;
D 15
		(void) setuid(getuid());
E 15
I 15
		(void) setuid(userid);
E 15
		sink(argc, argv);
		exit(errs);
	}
E 21
D 27
	rem = -1;
E 27
I 27
	if (argc < 2)
		usage();
E 27
	if (argc > 2)
		targetshouldbedirectory = 1;
I 36

E 36
I 27
	rem = -1;
I 42
D 55
	/* command to be executed on remote system using "rsh" */
E 55
I 55
	/* Command to be executed on remote system using "rsh". */
E 55
#ifdef	KERBEROS
D 53
	(void)sprintf(cmd, "rcp%s%s%s%s", iamrecursive ? " -r" : "",
E 53
I 53
	(void)snprintf(cmd, sizeof(cmd),
	    "rcp%s%s%s%s", iamrecursive ? " -r" : "",
E 53
I 50
D 51
D 54
D 58
#ifdef CRYPT
E 50
D 53
	    ((encrypt && use_kerberos) ? " -x" : ""),
E 53
I 53
D 55
	    ((doencrypt && use_kerberos) ? " -x" : ""),
E 55
I 55
	    (doencrypt && use_kerberos ? " -x" : ""),
E 55
E 53
I 50
#else
E 58
E 54
E 51
	    "",
D 51
D 54
D 58
#endif
E 58
E 54
E 51
E 50
	    pflag ? " -p" : "", targetshouldbedirectory ? " -d" : "");
#else
E 42
E 27
D 21
	(void) sprintf(cmd, "rcp%s%s",
	    iamrecursive ? " -r" : "", targetshouldbedirectory ? " -d" : "");
D 5
	sigsys(SIGPIPE, lostconn);
E 5
I 5
	signal(SIGPIPE, lostconn);
E 21
I 21
D 36
	(void) sprintf(cmd, "rcp%s%s%s",
	    iamrecursive ? " -r" : "", pflag ? " -p" : "", 
	    targetshouldbedirectory ? " -d" : "");
	(void) signal(SIGPIPE, lostconn);
E 21
E 5
	targ = colon(argv[argc - 1]);
D 21
	if (targ) {
E 21
I 21
	if (targ) {				/* ... to remote */
E 21
		*targ++ = 0;
I 6
		if (*targ == 0)
			targ = ".";
I 18
D 24
#ifndef NAMESERVER
		tuser = rindex(argv[argc - 1], '.');
		if (tuser) {
			*tuser++ = 0;
			if (!okname(tuser))
				exit(1);
		} else
			tuser = pwd->pw_name;
#else NAMESERVER
E 24
E 18
E 6
D 16
		tuser = rindex(argv[argc - 1], '.');
		if (tuser) {
			*tuser++ = 0;
			if (!okname(tuser))
E 16
I 16
		thost = index(argv[argc - 1], '@');
		if (thost) {
			*thost++ = 0;
			tuser = argv[argc - 1];
			if (*tuser == '\0')
D 24
				tuser = pwd->pw_name;
E 24
I 24
				tuser = NULL;
E 24
			else if (!okname(tuser))
E 16
				exit(1);
D 16
		} else
E 16
I 16
		} else {
			thost = argv[argc - 1];
E 36
I 36
D 53
	(void)sprintf(cmd, "rcp%s%s%s", iamrecursive ? " -r" : "",
	    pflag ? " -p" : "", targetshouldbedirectory ? " -d" : "");
E 53
I 53
	(void)snprintf(cmd, sizeof(cmd), "rcp%s%s%s",
	    iamrecursive ? " -r" : "", pflag ? " -p" : "",
	    targetshouldbedirectory ? " -d" : "");
E 53
I 42
#endif
E 42

	(void)signal(SIGPIPE, lostconn);

D 55
	if (targ = colon(argv[argc - 1]))
D 42
		toremote(targ, argc, argv);
E 42
I 42
		toremote(targ, argc, argv);	/* destination is remote host */
E 55
I 55
	if (targ = colon(argv[argc - 1]))	/* Dest is remote host. */
		toremote(targ, argc, argv);
E 55
E 42
	else {
D 42
		tolocal(argc, argv);
E 42
I 42
D 55
		tolocal(argc, argv);		/* destination is local host */
E 55
I 55
		tolocal(argc, argv);		/* Dest is local host. */
E 55
E 42
		if (targetshouldbedirectory)
			verifydir(argv[argc - 1]);
	}
	exit(errs);
}

I 55
void
E 55
toremote(targ, argc, argv)
D 55
	char *targ;
E 55
I 55
	char *targ, *argv[];
E 55
	int argc;
D 55
	char **argv;
E 55
{
D 48
	int i;
E 48
I 48
D 53
	int i, tos;
E 53
I 53
	int i, len, tos;
E 53
E 48
D 38
	char *host, *src, *suser, *thost, *tuser;
	char buf[1024], *colon();
E 38
I 38
	char *bp, *host, *src, *suser, *thost, *tuser;
D 52
	char *colon(), *malloc();
E 52
I 52
D 55
	char *colon();
E 55
E 52
E 38

	*targ++ = 0;
	if (*targ == 0)
		targ = ".";

D 38
	thost = index(argv[argc - 1], '@');
	if (thost) {
E 38
I 38
D 59
	if (thost = index(argv[argc - 1], '@')) {
E 59
I 59
	if (thost = strchr(argv[argc - 1], '@')) {
E 59
I 42
		/* user@host */
E 42
E 38
		*thost++ = 0;
		tuser = argv[argc - 1];
		if (*tuser == '\0')
E 36
E 16
D 24
			tuser = pwd->pw_name;
E 24
I 24
			tuser = NULL;
E 24
I 16
D 36
		}
I 18
D 24
#endif NAMESERVER
E 24
E 18
E 16
		for (i = 0; i < argc - 1; i++) {
			src = colon(argv[i]);
D 21
			if (src) {
E 21
I 21
			if (src) {		/* remote to remote */
E 21
				*src++ = 0;
I 6
				if (*src == 0)
D 7
					*src = ".";
E 7
I 7
					src = ".";
I 18
D 24
#ifndef NAMESERVER
				suser = rindex(argv[i], '.');
				if (suser) {
					*suser++ = 0;
					if (!okname(suser))
#else NAMESERVER
E 24
E 18
E 7
E 6
D 16
				suser = rindex(argv[i], '.');
				if (suser) {
					*suser++ = 0;
					if (!okname(suser))
E 16
I 16
				host = index(argv[i], '@');
				if (host) {
					*host++ = 0;
					suser = argv[i];
					if (*suser == '\0')
						suser = pwd->pw_name;
					else if (!okname(suser))
I 18
D 24
#endif NAMESERVER
E 24
E 18
E 16
						continue;
I 18
D 24
#ifndef NAMESERVER
		(void) sprintf(buf, "rsh %s -l %s -n %s %s '%s.%s:%s'",
					    argv[i], suser, cmd, src,
					    argv[argc - 1], tuser, targ);
E 24
I 24
D 25
		(void) sprintf(buf, "rsh %s -l %s -n %s %s '%s%s%s:%s'",
E 25
I 25
D 34
		(void) sprintf(buf, "/usr/ucb/rsh %s -l %s -n %s %s '%s%s%s:%s'",
E 25
D 26
					    host, suser, cmd, src, tuser,
E 26
I 26
					    host, suser, cmd, src,
E 34
I 34
		(void) sprintf(buf, "%s %s -l %s -n %s %s '%s%s%s:%s'",
					    _PATH_RSH, host, suser, cmd, src,
E 34
					    tuser ? tuser : "",
E 26
					    tuser ? "@" : "",
					    thost, targ);
E 24
				} else
D 24
		(void) sprintf(buf, "rsh %s -n %s %s '%s.%s:%s'",
					    argv[i], cmd, src,
					    argv[argc - 1], tuser, targ);
#else NAMESERVER
E 18
D 2
		(void) sprintf(buf, "rsh %s -l %s %s %s '%s:%s' </dev/null",
E 2
I 2
D 8
		(void) sprintf(buf, "rsh %s -L %s %s %s '%s:%s' </dev/null",
E 8
I 8
D 9
		(void) sprintf(buf, "rsh %s -L %s -n %s %s '%s:%s'",
E 8
E 2
					    argv[i], suser, cmd,
					    src, argv[argc - 1], targ);
E 9
I 9
D 16
		(void) sprintf(buf, "rsh %s -l %s -n %s %s '%s.%s:%s'",
					    argv[i], suser, cmd, src,
					    argv[argc - 1], tuser, targ);
E 16
I 16
		(void) sprintf(buf, "rsh %s -l %s -n %s %s '%s@%s:%s'",
					    host, suser, cmd, src,
					    tuser, thost, targ);
E 16
E 9
				} else
D 8
		(void) sprintf(buf, "rsh %s %s %s '%s:%s' </dev/null",
E 8
I 8
D 9
		(void) sprintf(buf, "rsh %s -n %s %s '%s:%s'",
E 8
					    argv[i], cmd,
					    src, argv[argc - 1], targ);
E 9
I 9
D 16
		(void) sprintf(buf, "rsh %s -n %s %s '%s.%s:%s'",
E 16
I 16
		(void) sprintf(buf, "rsh %s -n %s %s '%s@%s:%s'",
E 16
					    argv[i], cmd, src,
D 16
					    argv[argc - 1], tuser, targ);
E 16
I 16
					    tuser, thost, targ);
I 18
#endif NAMESERVER
E 24
I 24
D 25
		(void) sprintf(buf, "rsh %s -n %s %s '%s%s%s:%s'",
E 25
I 25
D 34
		(void) sprintf(buf, "/usr/ucb/rsh %s -n %s %s '%s%s%s:%s'",
E 25
D 26
					    argv[i], cmd, src, tuser,
E 26
I 26
					    argv[i], cmd, src,
E 34
I 34
		(void) sprintf(buf, "%s %s -n %s %s '%s%s%s:%s'",
					    _PATH_RSH, argv[i], cmd, src,
E 34
					    tuser ? tuser : "",
E 26
					    tuser ? "@" : "",
					    thost, targ);
E 24
E 18
E 16
E 9
				(void) susystem(buf);
D 21
			} else {
E 21
I 21
			} else {		/* local to remote */
E 21
				if (rem == -1) {
					(void) sprintf(buf, "%s -t %s",
					    cmd, targ);
I 18
D 24
#ifndef NAMESERVER
					host = argv[argc - 1];
#else NAMESERVER
E 24
E 18
D 16
					host = argv[argc - 1];
E 16
I 16
					host = thost;
I 32
#ifdef	KERBEROS
try_again:
					if(use_kerberos) {
					    rem = KSUCCESS;
					    if(krb_realm[0] == '\0')
						    rem = krb_get_lrealm(krb_realm,1);
					    if(rem == KSUCCESS) {
						    if(encrypt) {
						        rem = krcmd_mutual(
							    &host, port,
							    tuser ? tuser
								    : pwd->pw_name,
							    buf, 0, krb_realm,
							    &cred, schedule);
						    } else {
						    	
						        rem = krcmd(
							    &host,
							    port,
					    		    tuser ? tuser 
							       : pwd->pw_name,
					    		    buf, 0,
							    krb_realm
					    	        );
						    }
					    } else {
						    fprintf(stderr,
						      "rcp: error getting local realm %s\n",
						      krb_err_txt[rem]);
						    exit(1);
					    }
					    if((rem < 0) && errno == ECONNREFUSED) {
						    use_kerberos = 0;
						    old_warning("remote host doesn't support Kerberos");
I 33
						    sp = getservbyname("shell", "tcp");
						    if(sp == NULL) {
							fprintf(stderr, "unknown service shell/tcp\n");
							exit(1);
						    }
						    port = sp->s_port;
E 33
						    goto try_again;
					    }
					} else {
					    rem = rcmd(&host, port, pwd->pw_name,
					        tuser ? tuser : pwd->pw_name,
					        buf, 0);
					}
#else
E 36
I 36
		else if (!okname(tuser))
			exit(1);
	} else {
		thost = argv[argc - 1];
		tuser = NULL;
	}
E 36

I 36
	for (i = 0; i < argc - 1; i++) {
		src = colon(argv[i]);
		if (src) {			/* remote to remote */
			*src++ = 0;
			if (*src == 0)
				src = ".";
D 59
			host = index(argv[i], '@');
E 59
I 59
			host = strchr(argv[i], '@');
E 59
I 38
D 52
			if (!(bp = malloc((u_int)(strlen(_PATH_RSH) +
E 52
I 52
D 53
			if (!(bp = malloc(strlen(_PATH_RSH) +
E 52
				    strlen(argv[i]) + strlen(src) +
D 41
				    strlen(tuser) + strlen(thost) +
E 41
I 41
D 52
				    tuser ? strlen(tuser) : 0 + strlen(thost) +
E 41
				    strlen(targ)) + CMDNEEDS + 20)))
E 52
I 52
				    (tuser ? strlen(tuser) : 0) +
				    strlen(thost) +
				    strlen(targ) + CMDNEEDS + 20)))
E 52
					nospace();
E 53
I 53
			len = strlen(_PATH_RSH) + strlen(argv[i]) +
			    strlen(src) + (tuser ? strlen(tuser) : 0) +
			    strlen(thost) + strlen(targ) + CMDNEEDS + 20;
			if (!(bp = malloc(len)))
D 59
				nospace();
E 59
I 59
				err(1, NULL);
E 59
E 53
E 38
			if (host) {
				*host++ = 0;
				suser = argv[i];
				if (*suser == '\0')
					suser = pwd->pw_name;
				else if (!okname(suser))
					continue;
D 38
				(void)sprintf(buf,
E 38
I 38
D 53
				(void)sprintf(bp,
E 53
I 53
				(void)snprintf(bp, len,
E 53
E 38
				    "%s %s -l %s -n %s %s '%s%s%s:%s'",
				    _PATH_RSH, host, suser, cmd, src,
				    tuser ? tuser : "", tuser ? "@" : "",
				    thost, targ);
			} else
D 38
				(void)sprintf(buf,
				    "%s %s -n %s %s '%s%s%s:%s'",
E 38
I 38
D 53
				(void)sprintf(bp, "%s %s -n %s %s '%s%s%s:%s'",
E 53
I 53
				(void)snprintf(bp, len,
D 61
				    "%s %s -n %s %s '%s%s%s:%s'",
E 61
I 61
				    "exec %s %s -n %s %s '%s%s%s:%s'",
E 61
E 53
E 38
				    _PATH_RSH, argv[i], cmd, src,
				    tuser ? tuser : "", tuser ? "@" : "",
				    thost, targ);
D 38
			(void)susystem(buf);
E 38
I 38
D 55
			(void)susystem(bp);
E 55
I 55
			(void)susystem(bp, userid);
E 55
			(void)free(bp);
E 38
		} else {			/* local to remote */
			if (rem == -1) {
D 38
				(void)sprintf(buf, "%s -t %s", cmd, targ);
E 38
I 38
D 52
				if (!(bp = malloc((u_int)strlen(targ) +
E 52
I 52
D 53
				if (!(bp = malloc(strlen(targ) +
E 52
				    CMDNEEDS + 20)))
E 53
I 53
				len = strlen(targ) + CMDNEEDS + 20;
				if (!(bp = malloc(len)))
E 53
D 59
					nospace();
E 59
I 59
					err(1, NULL);
E 59
D 53
				(void)sprintf(bp, "%s -t %s", cmd, targ);
E 53
I 53
				(void)snprintf(bp, len, "%s -t %s", cmd, targ);
E 53
E 38
				host = thost;
#ifdef KERBEROS
				if (use_kerberos)
D 38
					kerberos(buf, tuser ?
					    tuser : pwd->pw_name);
E 38
I 38
D 42
					kerberos(bp,
E 42
I 42
					rem = kerberos(&host, bp,
					    pwd->pw_name,
E 42
					    tuser ? tuser : pwd->pw_name);
E 38
				else
#endif
E 36
E 32
I 18
D 24
#endif NAMESERVER
E 18
E 16
D 14
					rem = rcmd(&host, IPPORT_CMDSERVER,
E 14
I 14
D 15
					rem = rcmd(&host, sp->s_port,
E 14
					    pwd->pw_name, tuser,
E 15
I 15
					rem = rcmd(&host, port, pwd->pw_name, tuser,
E 24
I 24
					rem = rcmd(&host, port, pwd->pw_name,
					    tuser ? tuser : pwd->pw_name,
E 24
E 15
D 38
					    buf, 0);
E 38
I 38
					    bp, 0);
E 38
I 32
D 36
#endif
E 32
					if (rem < 0)
						exit(1);
					if (response() < 0)
						exit(1);
I 15
					(void) setuid(userid);
E 15
				}
				source(1, argv+i);
E 36
I 36
				if (rem < 0)
					exit(1);
I 48
				tos = IPTOS_THROUGHPUT;
				if (setsockopt(rem, IPPROTO_IP, IP_TOS,
D 55
				    (char *)&tos, sizeof(int)) < 0)
D 49
					perror("Notice: set type-of-service failed: %m");
E 49
I 49
					perror("rcp: setsockopt TOS (ignored)");
E 55
I 55
				    &tos, sizeof(int)) < 0)
D 59
					(void)fprintf(stderr,
					    "rcp: TOS (ignored): %s\n",
					    strerror(errno));
E 59
I 59
					warn("TOS (ignored)");
E 59
E 55
E 49
E 48
				if (response() < 0)
					exit(1);
I 38
				(void)free(bp);
E 38
				(void)setuid(userid);
E 36
			}
I 36
			source(1, argv+i);
E 36
		}
D 21
	} else {
E 21
I 21
D 36
	} else {				/* ... to local */
E 21
		if (targetshouldbedirectory)
			verifydir(argv[argc - 1]);
		for (i = 0; i < argc - 1; i++) {
			src = colon(argv[i]);
D 21
			if (src == 0) {
				(void) sprintf(buf, "/bin/cp%s %s %s",
E 21
I 21
			if (src == 0) {		/* local to local */
D 34
				(void) sprintf(buf, "/bin/cp%s%s %s %s",
E 21
				    iamrecursive ? " -r" : "",
E 34
I 34
				(void) sprintf(buf, "%s%s%s %s %s",
				    _PATH_CP, iamrecursive ? " -r" : "",
E 34
I 21
				    pflag ? " -p" : "",
E 21
				    argv[i], argv[argc - 1]);
				(void) susystem(buf);
D 21
			} else {
E 21
I 21
			} else {		/* remote to local */
E 21
				*src++ = 0;
I 6
				if (*src == 0)
					src = ".";
I 18
D 24
#ifndef NAMESERVER
				suser = rindex(argv[i], '.');
				if (suser) {
					*suser++ = 0;
					if (!okname(suser))
#else NAMESERVER
E 24
E 18
E 6
D 16
				suser = rindex(argv[i], '.');
				if (suser) {
					*suser++ = 0;
					if (!okname(suser))
E 16
I 16
				host = index(argv[i], '@');
				if (host) {
					*host++ = 0;
					suser = argv[i];
					if (*suser == '\0')
						suser = pwd->pw_name;
					else if (!okname(suser))
I 18
D 24
#endif NAMESERVER
E 24
E 18
E 16
						continue;
I 18
D 24
#ifndef NAMESERVER
				} else
#else NAMESERVER
E 24
E 18
D 16
				} else
E 16
I 16
				} else {
					host = argv[i];
E 36
I 36
	}
}

I 55
void
E 55
tolocal(argc, argv)
	int argc;
D 55
	char **argv;
E 55
I 55
	char *argv[];
E 55
{
D 48
	int i;
E 48
I 48
D 53
	int i, tos;
E 53
I 53
	int i, len, tos;
E 53
E 48
D 38
	char *host, *src, *suser;
	char buf[1024], *colon();
E 38
I 38
	char *bp, *host, *src, *suser;
D 52
	char *colon(), *malloc();
E 52
I 52
D 55
	char *colon();
E 55
E 52
E 38

	for (i = 0; i < argc - 1; i++) {
D 38
		src = colon(argv[i]);
		if (src == 0) {			/* local to local */
			(void)sprintf(buf, "%s%s%s %s %s",
			    _PATH_CP, iamrecursive ? " -r" : "",
			    pflag ? " -p" : "", argv[i], argv[argc - 1]);
			(void)susystem(buf);
		} else {			/* remote to local */
			*src++ = 0;
			if (*src == 0)
				src = ".";
			host = index(argv[i], '@');
			if (host) {
				*host++ = 0;
				suser = argv[i];
				if (*suser == '\0')
E 36
I 18
D 24
#endif NAMESERVER
E 24
E 18
E 16
					suser = pwd->pw_name;
I 18
D 24
#ifdef NAMESERVER
E 24
E 18
I 16
D 36
				}
I 18
D 24
#endif NAMESERVER
E 24
E 18
E 16
				(void) sprintf(buf, "%s -f %s", cmd, src);
I 32
#ifdef	KERBEROS
one_more_time:
				if(use_kerberos) {
				    rem = KSUCCESS;
				    if(krb_realm[0] == '\0')
					    rem = krb_get_lrealm(krb_realm,1);
				    if(rem == KSUCCESS) {
					if(encrypt) {
					    rem = krcmd_mutual(
						    &host,
						    port,
						    suser,
						    buf, 0,
						    krb_realm,
						    &cred, schedule
					    );
					} else {
					    rem = krcmd(
						    &host,
						    port,
						    suser,
						    buf, 0,
						    krb_realm
					    );
					}
				    } else {
					    fprintf(stderr,
					      "rcp: error getting local realm %s\n",
					      krb_err_txt[rem]);
					    exit(1);
				    }
				    if((rem < 0) && errno == ECONNREFUSED) {
					use_kerberos = 0;
					old_warning("remote host doesn't suport Kerberos");
I 33
					sp = getservbyname("shell", "tcp");
					if(sp == NULL) {
						fprintf(stderr, "unknown service shell/tcp\n");
						exit(1);
					}
					port = sp->s_port;
E 33
					goto one_more_time;
				    }
				} else {
					rem = rcmd(&host, port, pwd->pw_name, suser,
			    			buf, 0);
				}
#else
E 32
I 18
D 24
#ifndef NAMESERVER
				host = argv[i];
#endif NAMESERVER
E 24
E 18
D 16
				host = argv[i];
E 16
D 14
				rem = rcmd(&host, IPPORT_CMDSERVER,
E 14
I 14
D 15
				rem = rcmd(&host, sp->s_port,
E 14
				    pwd->pw_name, suser,
E 15
I 15
				rem = rcmd(&host, port, pwd->pw_name, suser,
E 15
D 32
				    buf, 0);
E 32
I 32
			    		buf, 0);
#endif
E 32
				if (rem < 0)
E 36
I 36
				else if (!okname(suser))
E 36
D 16
					exit(1);
E 16
I 16
					continue;
E 16
I 15
D 36
				(void) setreuid(0, userid);
E 15
				sink(1, argv+argc-1);
I 15
				(void) setreuid(userid, 0);
E 15
				(void) close(rem);
				rem = -1;
E 36
I 36
			} else {
				host = argv[i];
E 38
I 38
D 55
		if (!(src = colon(argv[i]))) {	/* local to local */
E 55
I 55
		if (!(src = colon(argv[i]))) {		/* Local to local. */
E 55
D 52
			if (!(bp = malloc((u_int)(strlen(_PATH_CP) +
			    strlen(argv[i]) + strlen(argv[argc - 1])) + 20)))
E 52
I 52
D 53
			if (!(bp = malloc(strlen(_PATH_CP) +
			    strlen(argv[i]) + strlen(argv[argc - 1]) + 20)))
E 53
I 53
			len = strlen(_PATH_CP) + strlen(argv[i]) +
			    strlen(argv[argc - 1]) + 20;
			if (!(bp = malloc(len)))
E 53
E 52
D 59
				nospace();
E 59
I 59
				err(1, NULL);
E 59
D 53
			(void)sprintf(bp, "%s%s%s %s %s", _PATH_CP,
E 53
I 53
D 61
			(void)snprintf(bp, len, "%s%s%s %s %s", _PATH_CP,
E 61
I 61
			(void)snprintf(bp, len, "exec %s%s%s %s %s", _PATH_CP,
E 61
E 53
			    iamrecursive ? " -r" : "", pflag ? " -p" : "",
			    argv[i], argv[argc - 1]);
D 55
			(void)susystem(bp);
E 55
I 55
D 56
			(void)susystem(bp, userid);
E 56
I 56
			if (susystem(bp, userid))
				++errs;
E 56
E 55
			(void)free(bp);
			continue;
		}
		*src++ = 0;
		if (*src == 0)
			src = ".";
D 55
		host = index(argv[i], '@');
		if (host) {
E 55
I 55
D 59
		if ((host = index(argv[i], '@')) == NULL) {
E 59
I 59
		if ((host = strchr(argv[i], '@')) == NULL) {
E 59
			host = argv[i];
			suser = pwd->pw_name;
		} else {
E 55
			*host++ = 0;
			suser = argv[i];
			if (*suser == '\0')
E 38
				suser = pwd->pw_name;
E 36
D 38
			}
I 36
			(void)sprintf(buf, "%s -f %s", cmd, src);
#ifdef KERBEROS
			if (use_kerberos)
				kerberos(buf, suser);
			else
#endif
				rem = rcmd(&host, port, pwd->pw_name, suser,
				    buf, 0);
			if (rem < 0)
E 38
I 38
			else if (!okname(suser))
E 38
				continue;
D 38
			(void)setreuid(0, userid);
			sink(1, argv + argc - 1);
			(void)setreuid(userid, 0);
			(void)close(rem);
			rem = -1;
E 38
I 38
D 55
		} else {
			host = argv[i];
			suser = pwd->pw_name;
E 55
E 38
E 36
		}
I 38
D 52
		if (!(bp = malloc((u_int)(strlen(src)) + CMDNEEDS + 20)))
E 52
I 52
D 53
		if (!(bp = malloc(strlen(src) + CMDNEEDS + 20)))
E 53
I 53
		len = strlen(src) + CMDNEEDS + 20;
D 55
		if (!(bp = malloc(len)))
E 55
I 55
		if ((bp = malloc(len)) == NULL)
E 55
E 53
E 52
D 59
			nospace();
E 59
I 59
			err(1, NULL);
E 59
D 53
		(void)sprintf(bp, "%s -f %s", cmd, src);
E 53
I 53
		(void)snprintf(bp, len, "%s -f %s", cmd, src);
I 55
		rem = 
E 55
E 53
#ifdef KERBEROS
D 55
		if (use_kerberos)
D 42
			kerberos(bp, suser);
E 42
I 42
			rem = kerberos(&host, bp, pwd->pw_name, suser);
E 42
		else
E 55
I 55
		    use_kerberos ? 
			kerberos(&host, bp, pwd->pw_name, suser) : 
E 55
#endif
D 55
			rem = rcmd(&host, port, pwd->pw_name, suser, bp, 0);
E 55
I 55
			rcmd(&host, port, pwd->pw_name, suser, bp, 0);
E 55
		(void)free(bp);
D 56
		if (rem < 0)
E 56
I 56
		if (rem < 0) {
			++errs;
E 56
			continue;
I 56
		}
E 56
D 48
		(void)setreuid(0, userid);
E 48
I 48
		(void)seteuid(userid);
		tos = IPTOS_THROUGHPUT;
D 55
		if (setsockopt(rem, IPPROTO_IP, IP_TOS,
		    (char *)&tos, sizeof(int)) < 0)
D 49
			perror("Notice: set type-of-service failed: %m");
E 49
I 49
			perror("rcp: setsockopt TOS (ignored)");
E 55
I 55
		if (setsockopt(rem, IPPROTO_IP, IP_TOS, &tos, sizeof(int)) < 0)
D 59
			(void)fprintf(stderr, "rcp: TOS (ignored): %s\n",
			    strerror(errno));
E 59
I 59
			warn("TOS (ignored)");
E 59
E 55
E 49
E 48
		sink(1, argv + argc - 1);
D 48
		(void)setreuid(userid, 0);
E 48
I 48
		(void)seteuid(0);
E 48
		(void)close(rem);
		rem = -1;
E 38
	}
D 36
	exit(errs);
E 36
}

I 36
D 42
#ifdef KERBEROS
D 38
kerberos(buf, user)
	char *buf, *user;
E 38
I 38
kerberos(bp, user)
	char *bp, *user;
E 38
{
	struct servent *sp;
	char *host;

again:	rem = KSUCCESS;
	if (krb_realm[0] == '\0')
		rem = krb_get_lrealm(krb_realm, 1);
	if (rem == KSUCCESS) {
		if (encrypt)
D 38
			rem = krcmd_mutual(&host, port, user, buf,
			    0, krb_realm, &cred, schedule);
E 38
I 38
			rem = krcmd_mutual(&host, port, user, bp, 0,
			    krb_realm, &cred, schedule);
E 38
		else
D 38
			rem = krcmd(&host, port, user, buf, 0, krb_realm);
E 38
I 38
			rem = krcmd(&host, port, user, bp, 0, krb_realm);
E 38
	} else {
		(void)fprintf(stderr,
		    "rcp: error getting local realm %s\n", krb_err_txt[rem]);
		exit(1);
	}
	if (rem < 0 && errno == ECONNREFUSED) {
		use_kerberos = 0;
		old_warning("remote host doesn't support Kerberos");
		sp = getservbyname("shell", "tcp");
		if (sp == NULL) {
			(void)fprintf(stderr,
			    "rcp: unknown service shell/tcp\n");
			exit(1);
		}
		port = sp->s_port;
		goto again;
	}
}
#endif /* KERBEROS */

E 42
E 36
D 55
verifydir(cp)
	char *cp;
{
	struct stat stb;

D 15
	if (stat(cp, &stb) < 0)
		goto bad;
	if ((stb.st_mode & S_IFMT) == S_IFDIR)
		return;
	errno = ENOTDIR;
bad:
E 15
I 15
	if (stat(cp, &stb) >= 0) {
		if ((stb.st_mode & S_IFMT) == S_IFDIR)
			return;
		errno = ENOTDIR;
	}
E 15
D 41
	error("rcp: %s: %s.\n", cp, sys_errlist[errno]);
E 41
I 41
	error("rcp: %s: %s.\n", cp, strerror(errno));
E 41
	exit(1);
}

char *
colon(cp)
D 36
	char *cp;
E 36
I 36
	register char *cp;
E 36
{
D 36

	while (*cp) {
E 36
I 36
	for (; *cp; ++cp) {
E 36
		if (*cp == ':')
D 36
			return (cp);
E 36
I 36
			return(cp);
E 36
		if (*cp == '/')
D 36
			return (0);
		cp++;
E 36
I 36
			return(0);
E 36
	}
D 36
	return (0);
E 36
I 36
	return(0);
E 36
}

okname(cp0)
	char *cp0;
{
	register char *cp = cp0;
	register int c;

	do {
		c = *cp;
		if (c & 0200)
			goto bad;
		if (!isalpha(c) && !isdigit(c) && c != '_' && c != '-')
			goto bad;
D 38
		cp++;
	} while (*cp);
E 38
I 38
	} while (*++cp);
E 38
D 36
	return (1);
E 36
I 36
	return(1);
E 36
bad:
D 38
	fprintf(stderr, "rcp: invalid user name %s\n", cp0);
E 38
I 38
	(void)fprintf(stderr, "rcp: invalid user name %s\n", cp0);
E 38
D 36
	return (0);
E 36
I 36
	return(0);
E 36
}

D 13
susystem(buf)
	char *buf;
E 13
I 13
susystem(s)
	char *s;
E 13
{
I 13
	int status, pid, w;
D 42
	register int (*istat)(), (*qstat)();
E 42
I 42
	register sig_t istat, qstat;
E 42
E 13

D 13
	if (fork() == 0) {
		(void) setuid(getuid());
		(void) system(buf);
		_exit(0);
	} else
		(void) wait((int *)0);
E 13
I 13
	if ((pid = vfork()) == 0) {
D 15
		setuid(getuid());
E 15
I 15
D 21
		setuid(userid);
E 21
I 21
D 36
		(void) setuid(userid);
E 36
I 36
		(void)setuid(userid);
E 36
E 21
E 15
D 34
		execl("/bin/sh", "sh", "-c", s, (char *)0);
E 34
I 34
		execl(_PATH_BSHELL, "sh", "-c", s, (char *)0);
E 34
		_exit(127);
	}
	istat = signal(SIGINT, SIG_IGN);
	qstat = signal(SIGQUIT, SIG_IGN);
	while ((w = wait(&status)) != pid && w != -1)
		;
	if (w == -1)
		status = -1;
D 21
	signal(SIGINT, istat);
	signal(SIGQUIT, qstat);
E 21
I 21
D 36
	(void) signal(SIGINT, istat);
	(void) signal(SIGQUIT, qstat);
E 21
	return (status);
E 36
I 36
	(void)signal(SIGINT, istat);
	(void)signal(SIGQUIT, qstat);
	return(status);
E 36
E 13
}

E 55
I 55
void
E 55
source(argc, argv)
	int argc;
D 55
	char **argv;
E 55
I 55
	char *argv[];
E 55
{
D 36
	char *last, *name;
E 36
	struct stat stb;
D 19
	char buf[BUFSIZ];
D 2
	int x, sizerr, f, i;
E 2
I 2
	int x, sizerr, f;
E 19
I 19
D 36
	static struct buffer buffer;
	struct buffer *bp;
D 28
	int x, sizerr, f, amt;
E 28
I 28
	int x, readerr, f, amt;
E 36
I 36
	static BUF buffer;
	BUF *bp;
E 36
E 28
E 19
	off_t i;
I 19
D 36
	char buf[BUFSIZ];
E 36
I 36
D 55
	int x, readerr, f, amt;
E 55
I 55
D 56
	int fd, readerr, amt;
E 56
I 56
	int amt, fd, haderr, indx, result;
E 56
E 55
	char *last, *name, buf[BUFSIZ];
D 55
	BUF *allocbuf();
E 55
E 36
E 19
E 2

D 55
	for (x = 0; x < argc; x++) {
		name = argv[x];
D 15
		if (access(name, 4) < 0 || (f = open(name, 0)) < 0) {
E 15
I 15
D 36
		if ((f = open(name, 0)) < 0) {
E 36
I 36
		if ((f = open(name, O_RDONLY, 0)) < 0) {
E 36
E 15
D 41
			error("rcp: %s: %s\n", name, sys_errlist[errno]);
E 41
I 41
			error("rcp: %s: %s\n", name, strerror(errno));
E 41
			continue;
E 55
I 55
D 56
	while (name = *argv++) {
E 56
I 56
	for (indx = 0; indx < argc; ++indx) {
                name = argv[indx];
E 56
		if ((fd = open(name, O_RDONLY, 0)) < 0)
			goto syserr;
		if (fstat(fd, &stb)) {
D 59
syserr:			err("%s: %s", name, strerror(errno));
E 59
I 59
syserr:			run_err("%s: %s", name, strerror(errno));
E 59
			goto next;
E 55
		}
D 55
		if (fstat(f, &stb) < 0)
			goto notreg;
		switch (stb.st_mode&S_IFMT) {

E 55
I 55
		switch (stb.st_mode & S_IFMT) {
E 55
		case S_IFREG:
			break;
D 55

E 55
		case S_IFDIR:
			if (iamrecursive) {
D 36
				(void) close(f);
E 36
I 36
D 55
				(void)close(f);
E 55
E 36
D 21
				rsource(name, (int)stb.st_mode);
E 21
I 21
				rsource(name, &stb);
E 21
D 55
				continue;
E 55
I 55
				goto next;
E 55
			}
D 36
			/* fall into ... */
E 36
I 36
			/* FALLTHROUGH */
E 36
		default:
D 36
notreg:
			(void) close(f);
E 36
I 36
D 55
notreg:			(void)close(f);
E 36
			error("rcp: %s: not a plain file\n", name);
			continue;
E 55
I 55
D 59
			err("%s: not a regular file", name);
E 59
I 59
			run_err("%s: not a regular file", name);
E 59
			goto next;
E 55
		}
D 55
		last = rindex(name, '/');
		if (last == 0)
E 55
I 55
D 59
		if ((last = rindex(name, '/')) == NULL)
E 59
I 59
		if ((last = strrchr(name, '/')) == NULL)
E 59
E 55
			last = name;
		else
D 55
			last++;
E 55
I 55
			++last;
E 55
D 2
		(void) sprintf(buf, "C%04o %d %s\n",
E 2
I 2
D 21
		(void) sprintf(buf, "C%04o %D %s\n",
E 21
I 21
		if (pflag) {
			/*
			 * Make it compatible with possible future
			 * versions expecting microseconds.
			 */
D 36
			(void) sprintf(buf, "T%ld 0 %ld 0\n",
E 36
I 36
D 38
			(void)sprintf(buf, "T%ld 0 %ld 0\n",
E 36
			    stb.st_mtime, stb.st_atime);
E 38
I 38
D 53
			(void)sprintf(buf, "T%ld 0 %ld 0\n", stb.st_mtime,
			    stb.st_atime);
E 53
I 53
D 55
			(void)snprintf(buf, sizeof(buf),
			    "T%ld 0 %ld 0\n", stb.st_mtime, stb.st_atime);
E 53
E 38
D 36
			(void) write(rem, buf, strlen(buf));
E 36
I 36
D 52
			(void)write(rem, buf, strlen(buf));
E 52
I 52
			(void)write(rem, buf, (int)strlen(buf));
E 52
E 36
			if (response() < 0) {
D 36
				(void) close(f);
E 36
I 36
				(void)close(f);
E 36
				continue;
			}
E 55
I 55
D 57
			amt = snprintf(buf, sizeof(buf), "T%ld 0 %ld 0\n",
E 57
I 57
			(void)snprintf(buf, sizeof(buf), "T%ld 0 %ld 0\n",
E 57
			    stb.st_mtimespec.ts_sec, stb.st_atimespec.ts_sec);
D 57
			(void)write(rem, buf, amt);
E 57
I 57
			(void)write(rem, buf, strlen(buf));
E 57
			if (response() < 0)
				goto next;
E 55
		}
D 36
		(void) sprintf(buf, "C%04o %ld %s\n",
E 36
I 36
D 38
		(void)sprintf(buf, "C%04o %ld %s\n",
E 36
E 21
E 2
		    stb.st_mode&07777, stb.st_size, last);
E 38
I 38
D 53
		(void)sprintf(buf, "C%04o %ld %s\n", stb.st_mode&07777,
		    stb.st_size, last);
E 53
I 53
D 55
		(void)snprintf(buf, sizeof(buf),
		    "C%04o %ld %s\n", stb.st_mode&07777, stb.st_size, last);
E 53
E 38
D 36
		(void) write(rem, buf, strlen(buf));
E 36
I 36
D 52
		(void)write(rem, buf, strlen(buf));
E 52
I 52
		(void)write(rem, buf, (int)strlen(buf));
E 52
E 36
		if (response() < 0) {
D 36
			(void) close(f);
E 36
I 36
			(void)close(f);
E 36
			continue;
		}
I 19
D 31
		if ((bp = allocbuf(&buffer, f, BUFSIZ)) < 0) {
E 31
I 31
		if ((bp = allocbuf(&buffer, f, BUFSIZ)) == 0) {
E 31
D 36
			(void) close(f);
E 36
I 36
			(void)close(f);
E 36
			continue;
		}
E 55
I 55
#define	MODEMASK	(S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
D 57
		amt = snprintf(buf, sizeof(buf), "C%04o %qd %s\n",
E 57
I 57
		(void)snprintf(buf, sizeof(buf), "C%04o %qd %s\n",
E 57
		    stb.st_mode & MODEMASK, stb.st_size, last);
D 57
		(void)write(rem, buf, amt);
E 57
I 57
		(void)write(rem, buf, strlen(buf));
E 57
		if (response() < 0)
			goto next;
D 56
		if ((bp = allocbuf(&buffer, fd, BUFSIZ)) == NULL)
			goto next;
E 55
E 19
D 28
		sizerr = 0;
E 28
I 28
		readerr = 0;
E 28
D 19
		for (i = 0; i < stb.st_size; i += BUFSIZ) {
			int amt = BUFSIZ;
E 19
I 19
		for (i = 0; i < stb.st_size; i += bp->cnt) {
E 56
I 56
		if ((bp = allocbuf(&buffer, fd, BUFSIZ)) == NULL) {
next:			(void)close(fd);
			continue;
		}

		/* Keep writing after an error so that we stay sync'd up. */
		for (haderr = i = 0; i < stb.st_size; i += bp->cnt) {
E 56
			amt = bp->cnt;
E 19
			if (i + amt > stb.st_size)
				amt = stb.st_size - i;
D 19
			if (sizerr == 0 && read(f, buf, amt) != amt)
E 19
I 19
D 28
			if (sizerr == 0 && read(f, bp->buf, amt) != amt)
E 19
				sizerr = 1;
E 28
I 28
D 55
			if (readerr == 0 && read(f, bp->buf, amt) != amt)
				readerr = errno;
E 55
I 55
D 56
			if (read(fd, bp->buf, amt) != amt) {
				readerr = 1;
				err("%s: %s", name, strerror(errno));
				break;
E 56
I 56
			if (!haderr) {
				result = read(fd, bp->buf, amt);
				if (result != amt)
					haderr = result >= 0 ? EIO : errno;
E 56
			}
E 55
E 28
D 19
			(void) write(rem, buf, amt);
E 19
I 19
D 36
			(void) write(rem, bp->buf, amt);
E 36
I 36
D 56
			(void)write(rem, bp->buf, amt);
E 56
I 56
			if (haderr)
				(void)write(rem, bp->buf, amt);
			else {
				result = write(rem, bp->buf, amt);
				if (result != amt)
					haderr = result >= 0 ? EIO : errno;
			}
E 56
E 36
E 19
		}
D 36
		(void) close(f);
E 36
I 36
D 55
		(void)close(f);
E 36
D 28
		if (sizerr == 0)
E 28
I 28
		if (readerr == 0)
E 55
I 55
D 56
		if (!readerr)
E 56
I 56
		if (close(fd) && !haderr)
			haderr = errno;
		if (!haderr)
E 56
E 55
E 28
D 36
			ga();
E 36
I 36
			(void)write(rem, "", 1);
I 56
		else
D 59
			err("%s: %s", name, strerror(haderr));
E 59
I 59
			run_err("%s: %s", name, strerror(haderr));
E 59
E 56
E 36
D 55
		else
D 28
			error("rcp: %s: file changed size\n", name);
E 28
I 28
D 41
			error("rcp: %s: %s\n", name, sys_errlist[readerr]);
E 41
I 41
			error("rcp: %s: %s\n", name, strerror(readerr));
E 55
E 41
E 28
D 36
		(void) response();
E 36
I 36
		(void)response();
I 55
D 56

next:		(void)close(fd);
E 56
E 55
E 36
	}
}

I 55
void
E 55
D 3
#include <ndir.h>
E 3
I 3
D 6
#include <dir.h>
E 6
I 6
D 36
#include <sys/dir.h>
E 6
E 3

E 36
D 21
rsource(name, mode)
E 21
I 21
rsource(name, statp)
E 21
	char *name;
D 21
	int mode;
E 21
I 21
	struct stat *statp;
E 21
{
D 36
	DIR *d = opendir(name);
	char *last;
E 36
I 36
D 53
	DIR *d;
E 36
	struct direct *dp;
E 53
I 53
	DIR *dirp;
	struct dirent *dp;
I 55
D 57
	int amt;
E 57
E 55
E 53
D 36
	char buf[BUFSIZ];
	char *bufv[1];
E 36
I 36
D 38
	char *last, *bufv[1], buf[BUFSIZ];
E 38
I 38
	char *last, *vect[1], path[MAXPATHLEN];
E 38
E 36

D 36
	if (d == 0) {
E 36
I 36
D 53
	if (!(d = opendir(name))) {
E 53
I 53
	if (!(dirp = opendir(name))) {
E 53
E 36
D 15
		error("%s: %s\n", name, sys_errlist[errno]);
E 15
I 15
D 41
		error("rcp: %s: %s\n", name, sys_errlist[errno]);
E 41
I 41
D 55
		error("rcp: %s: %s\n", name, strerror(errno));
E 55
I 55
D 59
		err("%s: %s", name, strerror(errno));
E 59
I 59
		run_err("%s: %s", name, strerror(errno));
E 59
E 55
E 41
E 15
		return;
	}
D 59
	last = rindex(name, '/');
E 59
I 59
	last = strrchr(name, '/');
E 59
	if (last == 0)
		last = name;
	else
		last++;
D 21
	(void) sprintf(buf, "D%04o %d %s\n", mode&07777, 0, last);
E 21
I 21
	if (pflag) {
D 36
		(void) sprintf(buf, "T%ld 0 %ld 0\n",
E 36
I 36
D 38
		(void)sprintf(buf, "T%ld 0 %ld 0\n",
E 36
		    statp->st_mtime, statp->st_atime);
D 36
		(void) write(rem, buf, strlen(buf));
E 36
I 36
		(void)write(rem, buf, strlen(buf));
E 38
I 38
D 53
		(void)sprintf(path, "T%ld 0 %ld 0\n", statp->st_mtime,
		    statp->st_atime);
E 53
I 53
D 55
		(void)snprintf(path, sizeof(path),
		    "T%ld 0 %ld 0\n", statp->st_mtime, statp->st_atime);
E 53
D 52
		(void)write(rem, path, strlen(path));
E 52
I 52
		(void)write(rem, path, (int)strlen(path));
E 55
I 55
D 57
		amt = snprintf(path, sizeof(path), "T%ld 0 %ld 0\n",
E 57
I 57
		(void)snprintf(path, sizeof(path), "T%ld 0 %ld 0\n",
E 57
		    statp->st_mtimespec.ts_sec, statp->st_atimespec.ts_sec);
D 57
		(void)write(rem, path, amt);
E 57
I 57
		(void)write(rem, path, strlen(path));
E 57
E 55
E 52
E 38
E 36
		if (response() < 0) {
D 53
			closedir(d);
E 53
I 53
			closedir(dirp);
E 53
			return;
		}
	}
D 36
	(void) sprintf(buf, "D%04o %d %s\n", statp->st_mode&07777, 0, last);
E 21
	(void) write(rem, buf, strlen(buf));
E 36
I 36
D 38
	(void)sprintf(buf, "D%04o %d %s\n", statp->st_mode&07777, 0, last);
	(void)write(rem, buf, strlen(buf));
E 38
I 38
D 53
	(void)sprintf(path, "D%04o %d %s\n", statp->st_mode&07777, 0, last);
E 53
I 53
D 55
	(void)snprintf(path, sizeof(path),
	    "D%04o %d %s\n", statp->st_mode&07777, 0, last);
E 53
D 52
	(void)write(rem, path, strlen(path));
E 52
I 52
	(void)write(rem, path, (int)strlen(path));
E 55
I 55
D 57
	amt = snprintf(path, sizeof(path),
E 57
I 57
	(void)snprintf(path, sizeof(path),
E 57
	    "D%04o %d %s\n", statp->st_mode & MODEMASK, 0, last);
D 57
	(void)write(rem, path, amt);
E 57
I 57
	(void)write(rem, path, strlen(path));
E 57
E 55
E 52
E 38
E 36
	if (response() < 0) {
D 53
		closedir(d);
E 53
I 53
		closedir(dirp);
E 53
		return;
	}
D 53
	while (dp = readdir(d)) {
E 53
I 53
	while (dp = readdir(dirp)) {
E 53
		if (dp->d_ino == 0)
			continue;
		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			continue;
D 38
		if (strlen(name) + 1 + strlen(dp->d_name) >= BUFSIZ - 1) {
			error("%s/%s: Name too long.\n", name, dp->d_name);
E 38
I 38
		if (strlen(name) + 1 + strlen(dp->d_name) >= MAXPATHLEN - 1) {
D 55
			error("%s/%s: name too long.\n", name, dp->d_name);
E 55
I 55
D 59
			err("%s/%s: name too long", name, dp->d_name);
E 59
I 59
			run_err("%s/%s: name too long", name, dp->d_name);
E 59
E 55
E 38
			continue;
		}
D 36
		(void) sprintf(buf, "%s/%s", name, dp->d_name);
E 36
I 36
D 38
		(void)sprintf(buf, "%s/%s", name, dp->d_name);
E 36
		bufv[0] = buf;
		source(1, bufv);
E 38
I 38
D 53
		(void)sprintf(path, "%s/%s", name, dp->d_name);
E 53
I 53
		(void)snprintf(path, sizeof(path), "%s/%s", name, dp->d_name);
E 53
		vect[0] = path;
		source(1, vect);
E 38
	}
D 53
	closedir(d);
E 53
I 53
D 55
	closedir(dirp);
E 55
I 55
	(void)closedir(dirp);
E 55
E 53
D 36
	(void) write(rem, "E\n", 2);
	(void) response();
E 36
I 36
	(void)write(rem, "E\n", 2);
	(void)response();
E 36
}

D 55
response()
{
D 36
	char resp, c, rbuf[BUFSIZ], *cp = rbuf;
E 36
I 36
	register char *cp;
	char ch, resp, rbuf[BUFSIZ];
E 36

D 36
	if (read(rem, &resp, 1) != 1)
E 36
I 36
	if (read(rem, &resp, sizeof(resp)) != sizeof(resp))
E 36
		lostconn();
D 36
	switch (resp) {
E 36

I 36
	cp = rbuf;
	switch(resp) {
E 36
D 21
	case 0:
E 21
I 21
	case 0:				/* ok */
E 21
D 36
		return (0);

E 36
I 36
		return(0);
E 36
	default:
		*cp++ = resp;
D 36
		/* fall into... */
E 36
I 36
		/* FALLTHROUGH */
E 36
D 21
	case 1:
	case 2:
E 21
I 21
	case 1:				/* error, followed by err msg */
	case 2:				/* fatal error, "" */
E 21
		do {
D 36
			if (read(rem, &c, 1) != 1)
E 36
I 36
			if (read(rem, &ch, sizeof(ch)) != sizeof(ch))
E 36
				lostconn();
D 36
			*cp++ = c;
		} while (cp < &rbuf[BUFSIZ] && c != '\n');
		if (iamremote == 0)
			(void) write(2, rbuf, cp - rbuf);
		errs++;
E 36
I 36
			*cp++ = ch;
		} while (cp < &rbuf[BUFSIZ] && ch != '\n');

		if (!iamremote)
			(void)write(2, rbuf, cp - rbuf);
		++errs;
E 36
		if (resp == 1)
D 36
			return (-1);
E 36
I 36
			return(-1);
E 36
		exit(1);
	}
	/*NOTREACHED*/
}

E 55
I 53
void
E 53
D 55
lostconn()
{
D 36

	if (iamremote == 0)
		fprintf(stderr, "rcp: lost connection\n");
E 36
I 36
	if (!iamremote)
		(void)fprintf(stderr, "rcp: lost connection\n");
E 36
	exit(1);
}

E 55
sink(argc, argv)
	int argc;
D 55
	char **argv;
E 55
I 55
	char *argv[];
E 55
{
D 19
	char *targ;
	char cmdbuf[BUFSIZ], nambuf[BUFSIZ], buf[BUFSIZ], *cp;
D 2
	int of, mode, i, size, wrerr, exists;
E 2
I 2
D 8
	int of, mode, wrerr, exists;
E 8
I 8
	int of, mode, wrerr, exists, first;
E 8
	off_t i, size;
E 2
	char *whopp;
	struct stat stb; int targisdir = 0;
#define	SCREWUP(str)	{ whopp = str; goto screwup; }
E 19
I 19
D 38
	off_t i, j;
	char *targ, *whopp, *cp;
	int of, mode, wrerr, exists, first, count, amt, size;
D 36
	struct buffer *bp;
	static struct buffer buffer;
E 36
I 36
	BUF *bp;
E 38
I 38
D 55
	register char *cp;
E 55
E 38
	static BUF buffer;
I 55
D 61
	register char *cp;
E 61
E 55
E 36
	struct stat stb;
D 38
	int targisdir = 0;
E 19
	int mask = umask(0);
	char *myargv[1];
I 19
D 21
	char cmdbuf[BUFSIZ], nambuf[BUFSIZ], buf[BUFSIZ];
E 21
I 21
	char cmdbuf[BUFSIZ], nambuf[BUFSIZ];
	int setimes = 0;
E 38
	struct timeval tv[2];
I 41
	enum { YES, NO, DISPLAYED } wrerr;
E 41
I 36
D 38
	BUF *allocbuf();
E 36
#define atime	tv[0]
#define mtime	tv[1]
E 21
#define	SCREWUP(str)	{ whopp = str; goto screwup; }
E 38
I 38
D 55
	BUF *bp, *allocbuf();
E 55
I 55
	BUF *bp;
E 55
	off_t i, j;
D 56
	char ch, *targ, *why;
	int amt, count, exists, first, mask, mode;
D 41
	int ofd, setimes, size, targisdir, wrerr;
E 41
I 41
	int ofd, setimes, size, targisdir;
E 41
D 52
	char *np, *vect[1], buf[BUFSIZ], *malloc();
E 52
I 52
	char *np, *vect[1], buf[BUFSIZ];
E 56
I 56
	int amt, count, exists, first, mask, mode, ofd, omode;
	int setimes, size, targisdir, wrerrno;
D 61
	char ch, *np, *targ, *why, *vect[1], buf[BUFSIZ];
E 61
I 61
	char ch, *cp, *np, *targ, *why, *vect[1], buf[BUFSIZ];
E 61
E 56
E 52
E 38
E 19

I 38
#define	atime	tv[0]
#define	mtime	tv[1]
#define	SCREWUP(str)	{ why = str; goto screwup; }

	setimes = targisdir = 0;
	mask = umask(0);
E 38
D 21
	umask(mask);
E 21
I 21
D 23
	(void) umask(mask);
E 23
I 23
	if (!pflag)
D 36
		(void) umask(mask);
E 36
I 36
		(void)umask(mask);
E 36
E 23
E 21
D 15
	if (argc > 1) {
E 15
I 15
	if (argc != 1) {
E 15
D 55
		error("rcp: ambiguous target\n");
E 55
I 55
D 59
		err("ambiguous target");
E 59
I 59
		run_err("ambiguous target");
E 59
E 55
		exit(1);
	}
	targ = *argv;
	if (targetshouldbedirectory)
		verifydir(targ);
D 36
	ga();
E 36
I 36
	(void)write(rem, "", 1);
E 36
D 55
	if (stat(targ, &stb) == 0 && (stb.st_mode & S_IFMT) == S_IFDIR)
E 55
I 55
	if (stat(targ, &stb) == 0 && S_ISDIR(stb.st_mode))
E 55
		targisdir = 1;
D 8
	for (;;) {
E 8
I 8
D 38
	for (first = 1; ; first = 0) {
E 8
		cp = cmdbuf;
E 38
I 38
	for (first = 1;; first = 0) {
		cp = buf;
E 38
		if (read(rem, cp, 1) <= 0)
			return;
		if (*cp++ == '\n')
D 38
			SCREWUP("unexpected '\\n'");
E 38
I 38
			SCREWUP("unexpected <newline>");
E 38
		do {
D 38
			if (read(rem, cp, 1) != 1)
E 38
I 38
			if (read(rem, &ch, sizeof(ch)) != sizeof(ch))
E 38
				SCREWUP("lost connection");
D 38
		} while (*cp++ != '\n');
E 38
I 38
			*cp++ = ch;
		} while (cp < &buf[BUFSIZ - 1] && ch != '\n');
D 39
		if (ch == '\n')
			*--cp;
E 39
E 38
		*cp = 0;
D 38
		if (cmdbuf[0] == '\01' || cmdbuf[0] == '\02') {
E 38
I 38

		if (buf[0] == '\01' || buf[0] == '\02') {
E 38
			if (iamremote == 0)
D 6
				(void) write(2, cmdbuf, strlen(cmdbuf));
E 6
I 6
D 36
				(void) write(2, cmdbuf+1, strlen(cmdbuf+1));
E 36
I 36
D 38
				(void)write(2, cmdbuf+1, strlen(cmdbuf+1));
E 36
E 6
			if (cmdbuf[0] == '\02')
E 38
I 38
D 52
				(void)write(2, buf + 1, strlen(buf + 1));
E 52
I 52
D 55
				(void)write(2, buf + 1, (int)strlen(buf + 1));
E 55
I 55
				(void)write(STDERR_FILENO,
				    buf + 1, strlen(buf + 1));
E 55
E 52
			if (buf[0] == '\02')
E 38
				exit(1);
D 55
			errs++;
E 55
I 55
			++errs;
E 55
			continue;
		}
D 38
		*--cp = 0;
		cp = cmdbuf;
		if (*cp == 'E') {
E 38
I 38
		if (buf[0] == 'E') {
E 38
D 36
			ga();
E 36
I 36
			(void)write(rem, "", 1);
E 36
			return;
		}
I 21

I 39
		if (ch == '\n')
D 40
			--cp;
E 40
I 40
			*--cp = 0;
E 40

E 39
#define getnum(t) (t) = 0; while (isdigit(*cp)) (t) = (t) * 10 + (*cp++ - '0');
I 38
		cp = buf;
E 38
		if (*cp == 'T') {
			setimes++;
			cp++;
			getnum(mtime.tv_sec);
			if (*cp++ != ' ')
				SCREWUP("mtime.sec not delimited");
			getnum(mtime.tv_usec);
			if (*cp++ != ' ')
				SCREWUP("mtime.usec not delimited");
			getnum(atime.tv_sec);
			if (*cp++ != ' ')
				SCREWUP("atime.sec not delimited");
			getnum(atime.tv_usec);
			if (*cp++ != '\0')
				SCREWUP("atime.usec not delimited");
D 36
			ga();
E 36
I 36
			(void)write(rem, "", 1);
E 36
			continue;
		}
E 21
D 8
		if (*cp != 'C' && *cp != 'D')
E 8
I 8
		if (*cp != 'C' && *cp != 'D') {
			/*
			 * Check for the case "rcp remote:foo\* local:bar".
			 * In this case, the line "No match." can be returned
			 * by the shell before the rcp command on the remote is
			 * executed so the ^Aerror_message convention isn't
			 * followed.
			 */
			if (first) {
D 55
				error("%s\n", cp);
E 55
I 55
D 59
				err("%s", cp);
E 59
I 59
				run_err("%s", cp);
E 59
E 55
				exit(1);
			}
E 8
			SCREWUP("expected control record");
I 8
		}
E 8
D 38
		cp++;
E 38
		mode = 0;
D 38
		for (; cp < cmdbuf+5; cp++) {
E 38
I 38
		for (++cp; cp < buf + 5; cp++) {
E 38
			if (*cp < '0' || *cp > '7')
				SCREWUP("bad mode");
			mode = (mode << 3) | (*cp - '0');
		}
		if (*cp++ != ' ')
			SCREWUP("mode not delimited");
D 55
		size = 0;
D 23
		while (*cp >= '0' && *cp <= '9')
E 23
I 23
		while (isdigit(*cp))
E 55
I 55

		for (size = 0; isdigit(*cp);)
E 55
E 23
			size = size * 10 + (*cp++ - '0');
		if (*cp++ != ' ')
			SCREWUP("size not delimited");
D 38
		if (targisdir)
D 36
			(void) sprintf(nambuf, "%s%s%s", targ,
E 36
I 36
			(void)sprintf(nambuf, "%s%s%s", targ,
E 38
I 38
		if (targisdir) {
			static char *namebuf;
			static int cursize;
D 52
			int need;
E 52
I 52
			size_t need;
E 52

			need = strlen(targ) + strlen(cp) + 250;
			if (need > cursize) {
D 52
				if (!(namebuf = malloc((u_int)need)))
E 52
I 52
				if (!(namebuf = malloc(need)))
E 52
D 39
					error("out of memory");
E 39
I 39
D 55
					error("out of memory\n");
E 55
I 55
D 59
					err("%s", strerror(errno));
E 59
I 59
					run_err("%s", strerror(errno));
E 59
E 55
E 39
			}
D 53
			(void)sprintf(namebuf, "%s%s%s", targ,
E 53
I 53
			(void)snprintf(namebuf, need, "%s%s%s", targ,
E 53
E 38
E 36
			    *targ ? "/" : "", cp);
I 38
			np = namebuf;
D 56
		}
E 38
		else
E 56
I 56
		} else
E 56
D 36
			(void) strcpy(nambuf, targ);
E 36
I 36
D 38
			(void)strcpy(nambuf, targ);
E 36
		exists = stat(nambuf, &stb) == 0;
D 15
		if (exists && access(nambuf, 2) < 0)
			goto bad2;
		{ char *slash = rindex(nambuf, '/'), *dir;
		  if (slash == 0) {
			slash = "/";
			dir = ".";
		  } else {
			*slash = 0;
			dir = nambuf;
I 11
			if (*dir == '\0')
				dir = "/";
E 11
		  }
		  if (exists == 0 && access(dir, 2) < 0)
			goto bad;
		  *slash = '/';
		  if (cmdbuf[0] == 'D') {
			if (stat(nambuf, &stb) == 0) {
E 15
I 15
		if (cmdbuf[0] == 'D') {
E 38
I 38
			np = targ;
		exists = stat(np, &stb) == 0;
		if (buf[0] == 'D') {
I 56
			int mod_flag = pflag;
E 56
E 38
			if (exists) {
E 15
D 55
				if ((stb.st_mode&S_IFMT) != S_IFDIR) {
E 55
I 55
				if (!S_ISDIR(stb.st_mode)) {
E 55
					errno = ENOTDIR;
					goto bad;
				}
I 23
				if (pflag)
D 36
					(void) chmod(nambuf, mode);
E 36
I 36
D 38
					(void)chmod(nambuf, mode);
E 36
E 23
D 13
			} else if (mkdir(nambuf, mode) < 0)
E 13
I 13
D 15
			} else if (makedir(nambuf, mode) < 0)
E 15
I 15
			} else if (mkdir(nambuf, mode) < 0)
E 38
I 38
					(void)chmod(np, mode);
D 56
			} else if (mkdir(np, mode) < 0)
E 38
E 15
E 13
				goto bad;
E 56
I 56
			} else {
				/* Handle copying from a read-only directory */
				mod_flag = 1;
				if (mkdir(np, mode | S_IRWXU) < 0)
					goto bad;
			}
E 56
D 38
			myargv[0] = nambuf;
			sink(1, myargv);
E 38
I 38
			vect[0] = np;
			sink(1, vect);
E 38
I 21
			if (setimes) {
				setimes = 0;
D 38
				if (utimes(nambuf, tv) < 0)
					error("rcp: can't set times on %s: %s\n",
					    nambuf, sys_errlist[errno]);
E 38
I 38
				if (utimes(np, tv) < 0)
D 55
				    error("rcp: can't set times on %s: %s\n",
E 55
I 55
D 59
				    err("can't set times on %s: %s",
E 59
I 59
				    run_err("%s: set times: %s",
E 59
E 55
D 41
					np, sys_errlist[errno]);
E 41
I 41
					np, strerror(errno));
E 41
E 38
			}
I 56
			if (mod_flag)
				(void)chmod(np, mode);
E 56
E 21
			continue;
D 15
		  }
		  if ((of = creat(nambuf, mode)) < 0) {
E 15
I 15
		}
I 56
		omode = mode;
		mode |= S_IWRITE;
E 56
D 27
		if ((of = creat(nambuf, mode)) < 0) {
E 27
I 27
D 38
		if ((of = open(nambuf, O_WRONLY|O_CREAT, mode)) < 0) {
E 27
E 15
	bad:
D 15
			*slash = '/';
	bad2:
E 15
			error("rcp: %s: %s\n", nambuf, sys_errlist[errno]);
E 38
I 38
		if ((ofd = open(np, O_WRONLY|O_CREAT, mode)) < 0) {
D 41
bad:			error("rcp: %s: %s\n", np, sys_errlist[errno]);
E 41
I 41
D 55
bad:			error("rcp: %s: %s\n", np, strerror(errno));
E 55
I 55
D 59
bad:			err("%s: %s", np, strerror(errno));
E 59
I 59
bad:			run_err("%s: %s", np, strerror(errno));
E 59
E 55
E 41
E 38
			continue;
D 15
		  }
E 15
		}
I 23
D 56
		if (exists && pflag)
D 36
			(void) fchmod(of, mode);
E 23
D 15
		if (exists == 0) {
D 13
			(void) stat(nambuf, &stb);
			(void) chown(nambuf, pwd->pw_uid, stb.st_gid);
E 13
I 13
			(void) chown(nambuf, pwd->pw_uid, -1);
E 13
			(void) chmod(nambuf, mode &~ mask);
		}
E 15
I 15
D 21
		if (exists)
			(void) fchmod(of, mode &~ mask);
E 21
E 15
		ga();
E 36
I 36
D 38
			(void)fchmod(of, mode);
E 38
I 38
			(void)fchmod(ofd, mode);
E 56
E 38
		(void)write(rem, "", 1);
E 36
I 19
D 31
		if ((bp = allocbuf(&buffer, of, BUFSIZ)) < 0) {
E 31
I 31
D 38
		if ((bp = allocbuf(&buffer, of, BUFSIZ)) == 0) {
E 31
D 21
			close(of);
E 21
I 21
D 36
			(void) close(of);
E 36
I 36
			(void)close(of);
E 38
I 38
D 55
		if ((bp = allocbuf(&buffer, ofd, BUFSIZ)) == 0) {
E 55
I 55
		if ((bp = allocbuf(&buffer, ofd, BUFSIZ)) == NULL) {
E 55
			(void)close(ofd);
E 38
E 36
E 21
			continue;
		}
		cp = bp->buf;
D 56
		count = 0;
E 56
E 19
D 41
		wrerr = 0;
E 41
I 41
		wrerr = NO;
E 41
D 56
		for (i = 0; i < size; i += BUFSIZ) {
E 56
I 56
		for (count = i = 0; i < size; i += BUFSIZ) {
E 56
D 19
			int amt = BUFSIZ;
			char *cp = buf;

E 19
I 19
			amt = BUFSIZ;
E 19
			if (i + amt > size)
				amt = size - i;
I 19
			count += amt;
E 19
			do {
D 19
				int j = read(rem, cp, amt);

E 19
I 19
				j = read(rem, cp, amt);
E 19
D 24
				if (j <= 0)
E 24
I 24
				if (j <= 0) {
D 38
					if (j == 0)
					    error("rcp: dropped connection");
					else
					    error("rcp: %s\n",
						sys_errlist[errno]);
E 38
I 38
D 39
					error("rcp: %s",
E 39
I 39
D 55
					error("rcp: %s\n",
E 39
D 41
					    j ? sys_errlist[errno] :
E 41
I 41
					    j ? strerror(errno) :
E 55
I 55
D 59
					err("%s", j ? strerror(errno) :
E 59
I 59
					run_err("%s", j ? strerror(errno) :
E 59
E 55
E 41
					    "dropped connection");
E 38
E 24
					exit(1);
I 24
				}
E 24
				amt -= j;
				cp += j;
			} while (amt > 0);
D 19
			amt = BUFSIZ;
			if (i + amt > size)
				amt = size - i;
			if (wrerr == 0 && write(of, buf, amt) != amt)
				wrerr++;
E 19
I 19
			if (count == bp->cnt) {
D 41
				if (wrerr == 0 &&
E 41
I 41
D 56
				if (wrerr == NO &&
E 41
D 38
				    write(of, bp->buf, count) != count)
E 38
I 38
				    write(ofd, bp->buf, count) != count)
E 38
D 41
					wrerr++;
E 41
I 41
					wrerr = YES;
E 56
I 56
				/* Keep reading so we stay sync'd up. */
				if (wrerr == NO) {
					j = write(ofd, bp->buf, count);
					if (j != count) {
						wrerr = YES;
						wrerrno = j >= 0 ? EIO : errno; 
					}
				}
E 56
E 41
				count = 0;
				cp = bp->buf;
			}
E 19
		}
I 19
D 41
		if (count != 0 && wrerr == 0 &&
E 41
I 41
		if (count != 0 && wrerr == NO &&
E 41
D 38
		    write(of, bp->buf, count) != count)
E 38
I 38
D 57
		    write(ofd, bp->buf, count) != count)
E 57
I 57
		    (j = write(ofd, bp->buf, count)) != count) {
E 57
E 38
D 41
			wrerr++;
I 27
D 38
		if (ftruncate(of, size))
			error("rcp: can't truncate %s: %s\n",
			    nambuf, sys_errlist[errno]);
E 27
E 19
D 36
		(void) close(of);
		(void) response();
E 36
I 36
		(void)close(of);
E 38
I 38
		if (ftruncate(ofd, size))
E 41
I 41
			wrerr = YES;
I 57
			wrerrno = j >= 0 ? EIO : errno; 
		}
E 57
		if (ftruncate(ofd, size)) {
E 41
D 55
			error("rcp: can't truncate %s: %s\n", np,
E 55
I 55
D 56
			err("can't truncate %s: %s", np,
E 55
D 41
			    sys_errlist[errno]);
E 41
I 41
			    strerror(errno));
E 56
I 56
D 59
			err("can't truncate %s: %s", np, strerror(errno));
E 59
I 59
			run_err("%s: truncate: %s", np, strerror(errno));
E 59
E 56
			wrerr = DISPLAYED;
		}
I 56
		if (pflag) {
			if (exists || omode != mode)
D 59
				(void)fchmod(ofd, omode);
E 59
I 59
				if (fchmod(ofd, omode))
					run_err("%s: set mode: %s",
					    np, strerror(errno));
E 59
		} else {
			if (!exists && omode != mode)
D 59
				(void)fchmod(ofd, omode & ~mask);
E 59
I 59
				if (fchmod(ofd, omode & ~mask))
					run_err("%s: set mode: %s",
					    np, strerror(errno));
E 59
		}
E 56
E 41
		(void)close(ofd);
E 38
		(void)response();
E 36
I 21
D 41
		if (setimes) {
E 41
I 41
		if (setimes && wrerr == NO) {
E 41
			setimes = 0;
D 38
			if (utimes(nambuf, tv) < 0)
E 38
I 38
D 41
			if (utimes(np, tv) < 0)
E 41
I 41
			if (utimes(np, tv) < 0) {
E 41
E 38
D 55
				error("rcp: can't set times on %s: %s\n",
E 55
I 55
D 59
				err("can't set times on %s: %s",
E 59
I 59
				run_err("%s: set times: %s",
E 59
E 55
D 38
				    nambuf, sys_errlist[errno]);
E 38
I 38
D 41
				    np, sys_errlist[errno]);
E 38
		}				   
E 21
		if (wrerr)
D 21
			error("rcp: %s: %s\n", cp, sys_errlist[errno]);
E 21
I 21
D 38
			error("rcp: %s: %s\n", nambuf, sys_errlist[errno]);
E 38
I 38
			error("rcp: %s: %s\n", np, sys_errlist[errno]);
E 38
E 21
		else
E 41
I 41
				    np, strerror(errno));
				wrerr = DISPLAYED;
			}
		}
		switch(wrerr) {
		case YES:
D 55
			error("rcp: %s: %s\n", np, strerror(errno));
E 55
I 55
D 56
			err("%s: %s", np, strerror(errno));
E 56
I 56
D 59
			err("%s: %s", np, strerror(wrerrno));
E 59
I 59
			run_err("%s: %s", np, strerror(wrerrno));
E 59
E 56
E 55
			break;
		case NO:
E 41
D 36
			ga();
E 36
I 36
			(void)write(rem, "", 1);
I 41
			break;
		case DISPLAYED:
			break;
		}
E 41
E 36
	}
screwup:
D 38
	error("rcp: protocol screwup: %s\n", whopp);
E 38
I 38
D 55
	error("rcp: protocol screwup: %s\n", why);
E 55
I 55
D 56
	err("protocol screwup: %s", why);
E 56
I 56
D 59
	err("protocol error: %s", why);
E 59
I 59
	run_err("protocol error: %s", why);
E 59
E 56
E 55
E 38
	exit(1);
I 19
}

D 36
struct buffer *
E 36
I 36
D 55
BUF *
E 36
allocbuf(bp, fd, blksize)
D 36
	struct buffer *bp;
E 36
I 36
	BUF *bp;
E 36
	int fd, blksize;
{
	struct stat stb;
D 52
	int size;
I 36
	char *malloc();
E 52
I 52
	size_t size;
E 52
E 36

	if (fstat(fd, &stb) < 0) {
D 41
		error("rcp: fstat: %s\n", sys_errlist[errno]);
E 41
I 41
		error("rcp: fstat: %s\n", strerror(errno));
E 41
D 31
		return ((struct buffer *)-1);
E 31
I 31
D 36
		return ((struct buffer *)0);
E 36
I 36
		return(0);
E 36
E 31
	}
	size = roundup(stb.st_blksize, blksize);
	if (size == 0)
		size = blksize;
	if (bp->cnt < size) {
		if (bp->buf != 0)
			free(bp->buf);
D 21
		bp->buf = (char *)malloc(size);
E 21
I 21
D 36
		bp->buf = (char *)malloc((unsigned) size);
E 36
I 36
D 52
		bp->buf = (char *)malloc((u_int)size);
E 52
I 52
		bp->buf = malloc(size);
E 52
E 36
E 21
D 38
		if (bp->buf == 0) {
E 38
I 38
		if (!bp->buf) {
E 38
			error("rcp: malloc: out of memory\n");
D 31
			return ((struct buffer *)-1);
E 31
I 31
D 36
			return ((struct buffer *)0);
E 36
I 36
			return(0);
E 36
E 31
		}
	}
	bp->cnt = size;
D 36
	return (bp);
E 36
I 36
	return(bp);
E 36
E 19
}

D 21
/*VARARGS*/
E 21
I 21
D 36
/*VARARGS1*/
E 36
I 36
/* VARARGS1 */
E 36
E 21
D 38
error(fmt, a1, a2, a3, a4, a5)
E 38
I 38
error(fmt, a1, a2, a3)
E 38
	char *fmt;
D 38
	int a1, a2, a3, a4, a5;
E 38
I 38
	int a1, a2, a3;
E 38
{
D 36
	char buf[BUFSIZ], *cp = buf;
E 36
I 36
D 39
	int len;
	char buf[BUFSIZ];
E 39
I 39
	static FILE *fp;
E 39
E 36

D 36
	errs++;
	*cp++ = 1;
	(void) sprintf(cp, fmt, a1, a2, a3, a4, a5);
	(void) write(rem, buf, strlen(buf));
	if (iamremote == 0)
		(void) write(2, buf+1, strlen(buf+1));
E 36
I 36
	++errs;
D 39
	buf[0] = 0x01;
D 38
	(void)sprintf(buf + 1, fmt, a1, a2, a3, a4, a5);
E 38
I 38
	(void)sprintf(buf + 1, fmt, a1, a2, a3);
E 38
	len = strlen(buf);
	(void)write(rem, buf, len);
E 39
I 39
	if (!fp && !(fp = fdopen(rem, "w")))
		return;
	(void)fprintf(fp, "%c", 0x01);
	(void)fprintf(fp, fmt, a1, a2, a3);
	(void)fflush(fp);
E 39
	if (!iamremote)
D 39
		(void)write(2, buf + 1, len - 1);
E 39
I 39
		(void)fprintf(stderr, fmt, a1, a2, a3);
E 39
E 36
I 27
}

I 38
nospace()
{
	(void)fprintf(stderr, "rcp: out of memory.\n");
	exit(1);
}

D 42
#ifdef KERBEROS
old_warning(str)
	char *str;
{
	(void)fprintf(stderr, "rcp: warning: %s, using standard rcp\n", str);
}
#endif
E 42

E 38
usage()
{
E 55
I 33
D 36
#ifdef	KERBEROS
	fputs("usage: rcp [-k realm] [-x] [-p] f1 f2;\n", stderr);
	fputs("   or: rcp [-k realm] [-x] [-rp] f1 ... fn d2\n", stderr);
E 36
I 36
#ifdef KERBEROS
I 50
D 51
D 54
D 55
#ifdef CRYPT
E 54
E 51
E 50
	(void)fprintf(stderr, "%s\n\t%s\n",
D 51
D 54
	    "usage: rcp [-k realm] [-px] f1 f2",
	    "or: rcp [-k realm] [-rpx] f1 ... fn directory");
E 36
#else
I 50
	(void)fprintf(stderr, "%s\n\t%s\n",
E 54
E 51
	    "usage: rcp [-k realm] [-p] f1 f2",
	    "or: rcp [-k realm] [-rp] f1 ... fn directory");
D 51
D 54
#endif
E 54
E 51
#else
E 50
E 33
D 36
	fputs("usage: rcp [-p] f1 f2; or: rcp [-rp] f1 ... fn d2\n", stderr);
E 36
I 36
	(void)fprintf(stderr,
	    "usage: rcp [-p] f1 f2; or: rcp [-rp] f1 ... fn directory\n");
E 36
I 33
#endif
E 33
	exit(1);
E 27
D 15
}

D 13
mkdir(name, mode)
	char *name;
	int mode;
E 13
I 13
makedir(name, mode)
	register char *name;
	register int mode;
E 13
{
D 13
	char *argv[4];
	int pid, rc;
E 13
I 13
	register int _errno;
E 13

D 13
	argv[0] = "mkdir";
	argv[1] = name;
	argv[2] = 0;
	pid = fork();
	if (pid < 0) {
		perror("cp");
		return (1);
E 13
I 13
	if (mkdir(name, mode) < 0 || chown(name, getuid(), -1) < 0) {
		_errno = errno;
		rmdir(name);
		errno = _errno;
		return (-1);
E 13
	}
D 13
	if (pid) {
		while (wait(&rc) != pid)
			continue;
		if (rc == 0)
			if (chmod(name, mode) < 0) {
				perror(name);
				rc = 1;
			}
		return (rc);
	}
	(void) setuid(getuid());
	execv("/bin/mkdir", argv);
	execv("/usr/bin/mkdir", argv);
	perror("mkdir");
	_exit(1);
	/*NOTREACHED*/
E 13
I 13

	return (0);
E 15
E 13
}
I 42

#ifdef KERBEROS
old_warning(str)
	char *str;
{
	(void)fprintf(stderr, "rcp: warning: %s, using standard rcp\n", str);
}

E 55
int
kerberos(host, bp, locuser, user)
D 55

E 55
	char **host, *bp, *locuser, *user;
{
	struct servent *sp;

again:
	if (use_kerberos) {
		rem = KSUCCESS;
		errno = 0;
		if (dest_realm == NULL)
			dest_realm = krb_realmofhost(*host);
D 55

E 55
I 55
		rem = 
E 55
I 50
D 51
D 54
D 58
#ifdef CRYPT
E 50
D 53
		if (encrypt)
E 53
I 53
D 55
		if (doencrypt)
E 53
			rem = krcmd_mutual(
				host, port,
				user, bp, 0,
		    		dest_realm,
				&cred, schedule);
		else
E 55
I 55
		    doencrypt ? 
			krcmd_mutual(host,
			    port, user, bp, 0, dest_realm, &cred, schedule) :
E 55
I 50
#endif
E 58
E 54
E 51
E 50
D 55
			rem = krcmd(
				host, port,
				user, bp, 0, dest_realm);
E 55
I 55
			krcmd(host, port, user, bp, 0, dest_realm);
E 55

		if (rem < 0) {
			use_kerberos = 0;
D 55
			sp = getservbyname("shell", "tcp");
			if (sp == NULL) {
E 55
I 55
D 59
			if ((sp = getservbyname("shell", "tcp")) == NULL) {
E 55
				(void)fprintf(stderr,
			    	    "rcp: unknown service shell/tcp\n");
				exit(1);
			}
E 59
I 59
			if ((sp = getservbyname("shell", "tcp")) == NULL)
				errx(1, "unknown service shell/tcp");
E 59
			if (errno == ECONNREFUSED)
D 55
				old_warning(
				    "remote host doesn't support Kerberos");

			if (errno == ENOENT)
				old_warning(
				    "Can't provide Kerberos auth data");
E 55
I 55
			    oldw("remote host doesn't support Kerberos");
			else if (errno == ENOENT)
			    oldw("can't provide Kerberos authentication data");
E 55
			port = sp->s_port;
			goto again;
		}
	} else {
I 50
D 51
D 54
D 58
#ifdef CRYPT
E 50
D 53
		if (encrypt) {
E 53
I 53
D 59
		if (doencrypt) {
E 53
D 55
			fprintf(stderr,
			    "The -x option requires Kerberos authentication\n");
E 55
I 55
			(void)fprintf(stderr,
			    "the -x option requires Kerberos authentication\n");
E 55
			exit(1);
		}
E 59
I 59
		if (doencrypt)
			errx(1,
			   "the -x option requires Kerberos authentication");
E 59
I 50
#endif
E 58
E 54
E 51
E 50
D 57
		rem = rcmd(host, sp->s_port, locuser, user, bp, 0);
E 57
I 57
		rem = rcmd(host, port, locuser, user, bp, 0);
E 57
	}
D 55
	return(rem);
E 55
I 55
	return (rem);
E 55
}
#endif /* KERBEROS */
I 55

int
response()
{
D 61
	register char *cp;
	char ch, resp, rbuf[BUFSIZ];
E 61
I 61
	char ch, *cp, resp, rbuf[BUFSIZ];
E 61

	if (read(rem, &resp, sizeof(resp)) != sizeof(resp))
		lostconn(0);

	cp = rbuf;
	switch(resp) {
	case 0:				/* ok */
		return (0);
	default:
		*cp++ = resp;
		/* FALLTHROUGH */
	case 1:				/* error, followed by error msg */
	case 2:				/* fatal error, "" */
		do {
			if (read(rem, &ch, sizeof(ch)) != sizeof(ch))
				lostconn(0);
			*cp++ = ch;
		} while (cp < &rbuf[BUFSIZ] && ch != '\n');

		if (!iamremote)
			(void)write(STDERR_FILENO, rbuf, cp - rbuf);
		++errs;
		if (resp == 1)
			return (-1);
		exit(1);
	}
	/* NOTREACHED */
}

void
usage()
{
#ifdef KERBEROS
D 58
#ifdef CRYPT
E 58
	(void)fprintf(stderr, "%s\n\t%s\n",
D 58
	    "usage: rcp [-Kpx] [-k realm] f1 f2",
	    "or: rcp [-Kprx] [-k realm] f1 ... fn directory");
#else
	(void)fprintf(stderr, "%s\n\t%s\n",
E 58
	    "usage: rcp [-Kp] [-k realm] f1 f2",
	    "or: rcp [-Kpr] [-k realm] f1 ... fn directory");
D 58
#endif
E 58
#else
	(void)fprintf(stderr,
	    "usage: rcp [-p] f1 f2; or: rcp [-pr] f1 ... fn directory\n");
#endif
	exit(1);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#ifdef KERBEROS
void
#if __STDC__
oldw(const char *fmt, ...)
#else
oldw(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "rcp: ");
	(void)vfprintf(stderr, fmt, ap);
	(void)fprintf(stderr, ", using standard rcp\n");
	va_end(ap);
}
#endif

void
#if __STDC__
D 59
err(const char *fmt, ...)
E 59
I 59
run_err(const char *fmt, ...)
E 59
#else
D 59
err(fmt, va_alist)
E 59
I 59
run_err(fmt, va_alist)
E 59
	char *fmt;
        va_dcl
#endif
{
	static FILE *fp;
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif

	++errs;
D 59
	if (!fp && !(fp = fdopen(rem, "w")))
E 59
I 59
	if (fp == NULL && !(fp = fdopen(rem, "w")))
E 59
		return;
	(void)fprintf(fp, "%c", 0x01);
	(void)fprintf(fp, "rcp: ");
	(void)vfprintf(fp, fmt, ap);
	(void)fprintf(fp, "\n");
D 59
	if (!iamremote) {
		(void)fprintf(stderr, "rcp: ");
		(void)vfprintf(stderr, fmt, ap);
		(void)fprintf(stderr, "\n");
	}
	va_end(ap);
E 59
	(void)fflush(fp);
I 59

	if (!iamremote)
		vwarnx(fmt, ap);

	va_end(ap);
E 59
}
E 55
E 42
I 32
D 38

D 36
#ifdef	KERBEROS
E 36
I 36
#ifdef KERBEROS
E 36
old_warning(str)
D 36
	char	*str;
E 36
I 36
	char *str;
E 36
{
D 33
	fprintf(stderr,"Warning: %s, using standard rcp", str);
E 33
I 33
D 36
	fprintf(stderr,"Warning: %s, using standard rcp\n", str);
E 36
I 36
	(void)fprintf(stderr, "rcp: warning: %s, using standard rcp\n", str);
E 36
E 33
}
#endif
E 38
E 32
I 2
D 11

E 11
E 2
E 1
