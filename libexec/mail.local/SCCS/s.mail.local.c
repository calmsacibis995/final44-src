h24528
s 00001/00000/00841
d D 8.22 95/06/21 08:24:22 eric 75 74
c close passwd file before setuid -- for paranoia
e
s 00009/00007/00832
d D 8.21 95/06/20 10:40:47 eric 74 73
c portability fixes for OSF/1
e
s 00007/00040/00832
d D 8.20 95/05/22 21:43:33 eric 73 72
c has to seteuid(0) at the end always; might as well just use
c the setreuid trick to simplify the code
e
s 00074/00013/00798
d D 8.19 95/05/22 17:57:42 eric 72 71
c write file as recipient user so quotas work properly
e
s 00009/00000/00802
d D 8.18 95/01/25 08:00:53 eric 71 70
c add System V comment
e
s 00023/00003/00779
d D 8.17 95/01/25 07:54:04 eric 70 69
c clean up a few possible problems & one real bug
e
s 00001/00001/00781
d D 8.16 95/01/18 12:06:20 eric 69 68
c typo
e
s 00007/00000/00775
d D 8.15 95/01/18 12:04:00 eric 68 67
c arrange for some open files and a reasonable umask
e
s 00124/00004/00651
d D 8.14 95/01/18 05:58:30 eric 67 66
c change ultrix version of mkstemp to avoid race condition
e
s 00006/00006/00649
d D 8.13 95/01/16 21:03:01 eric 66 65
c fix a couple of other small potential problems
e
s 00003/00011/00652
d D 8.12 95/01/16 20:45:16 eric 65 64
c avoid link during locking -- the target follows slinks,
c which allows you to create random empty files as root
e
s 00005/00001/00658
d D 8.11 94/12/07 12:30:38 eric 64 63
c check ownership of mailbox file
e
s 00003/00001/00656
d D 8.10 94/12/01 17:11:52 eric 63 62
c deal with systems that don't have quads
e
s 00001/00001/00656
d D 8.9 94/11/29 14:24:20 eric 62 61
c hmm..... make sure no one can predict the lock temp name
e
s 00067/00000/00590
d D 8.8 94/11/29 14:15:58 eric 61 60
c restore old mailbox locking (user.lock) so that NFS-mounted
c mail partitions have some chance of working
e
s 00113/00008/00477
d D 8.7 94/10/17 15:00:06 eric 60 59
c make so it's portable to SunOS and Ultrix.  Yes, I know it's ugly.
e
s 00007/00004/00478
d D 8.6 94/04/08 10:36:24 bostic 59 58
c retry the lstat if the create fails because the file exists,
c so we can detect symbolic link replacement
e
s 00014/00011/00468
d D 8.5 94/04/08 09:39:05 bostic 58 57
c Eric points out that you can compare the stat structures, which
c detects if open went through a symbolic link
e
s 00019/00004/00460
d D 8.4 94/04/08 08:52:30 bostic 57 56
c make the symbolic link race harder to hit by checking after the
c open as well as before
e
s 00001/00001/00463
d D 8.3 94/01/07 12:14:44 bostic 56 55
c don't use __dead here, it hoses portability
e
s 00002/00001/00462
d D 8.2 93/11/30 16:32:37 mckusick 55 54
c ANSI C lint
e
s 00005/00005/00458
d D 8.1 93/06/04 18:56:21 bostic 54 53
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00460
d D 5.13 93/05/17 11:14:26 bostic 53 52
c bcmp -> memcmp, bcopy -> memmove
e
s 00254/00084/00208
d D 5.12 93/04/30 18:33:44 bostic 52 51
c try to get the error/failed mail returns right
c minor cleanups, major portability hacks
e
s 00006/00003/00286
d D 5.11 93/03/02 18:31:00 bostic 51 50
c speedup/cleanliness not worth enough, just always write to stderr
e
s 00003/00000/00286
d D 5.10 93/03/02 18:18:05 bostic 50 49
c if LOG_PERROR not defined, write to stderr ourselves
e
s 00013/00007/00273
d D 5.9 93/01/21 15:36:56 bostic 49 48
c use snprintf(3), it's safer than sprintf(3)
e
s 00004/00006/00276
d D 5.8 92/06/22 13:36:33 bostic 48 47
c lseek takes a quad, now
e
s 00001/00001/00281
d D 5.7 91/11/13 09:29:03 bostic 47 46
c typo
e
s 00040/00019/00242
d D 5.6 91/06/19 14:12:10 bostic 46 45
c ANSI cleanups
e
s 00002/00001/00259
d D 5.5 91/03/07 16:57:30 donn 45 44
c Fixed mkstemp() on string constant.
e
s 00006/00005/00254
d D 5.4 91/02/25 17:05:37 bostic 44 43
c ANSI fixes
e
s 00005/00008/00254
d D 5.3 91/02/22 14:25:07 bostic 43 42
c use stdarg.h, not varargs.h
e
s 00002/00002/00260
d D 5.2 91/02/22 11:20:30 bostic 42 41
c fsync the mailbox file descriptor
e
s 00002/00002/00260
d D 5.1 91/01/19 13:06:59 bostic 41 40
c from set by sendmail -- don't reset it!
e
s 00194/00665/00068
d D 4.38 91/01/17 14:39:28 bostic 40 39
c from scratch -- /bin/mail was a security problem, and not worth fixing
e
s 00002/00001/00731
d D 4.37 90/06/24 23:39:06 bostic 39 38
c ugly hack because _PATH_MAILDIR doesn't have trailing slash
e
s 00005/00006/00727
d D 4.36 89/04/21 09:46:27 bostic 38 37
c file reorganization, pathnames.h
e
s 00002/00002/00731
d D 4.35 88/12/30 11:58:46 bostic 37 36
c bogus fdopen calls; bug report 4.3BSD/bin/222
e
s 00001/00001/00732
d D 4.34 88/09/20 17:44:30 bostic 36 35
c strcmpn -> strncmp
e
s 00001/00001/00732
d D 4.33 88/02/27 14:11:16 bostic 35 34
c 2.10BSD int/long fixes
e
s 00008/00009/00725
d D 4.32 88/02/27 14:01:11 bostic 34 33
c 2.10BSD int/long fixes
e
s 00004/00016/00730
d D 4.31 88/01/12 22:10:10 bostic 33 32
c check getpwuid(getuid()) in all cases; minor cleanup
e
s 00003/00003/00743
d D 4.30 87/10/22 09:52:09 bostic 32 31
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00744
d D 4.29 87/09/16 13:57:16 bostic 31 30
c getpwnam fix; bug report 4.3BSD/bin/67
e
s 00002/00001/00744
d D 4.28 87/05/30 16:45:17 bostic 30 29
c check return of socket call
e
s 00001/00001/00744
d D 4.27 86/08/12 15:54:54 karels 29 28
c fix keywords
e
s 00023/00017/00722
d D 4.26 86/08/12 15:48:24 karels 28 27
c fix buffer overrun with -r; don't loop on faults
e
s 00008/00001/00731
d D 4.25 85/05/01 16:29:51 miriam 27 26
c Close getlogin problem
e
s 00003/00004/00729
d D 4.24 84/12/18 14:03:54 ralph 26 25
c use mkstemp so people can't substitute a symlink for the temp file.
e
s 00022/00025/00711
d D 4.23 84/08/27 09:24:00 ralph 25 24
c fix uucp mail when given -d option.
e
s 00230/00310/00506
d D 4.22 84/07/19 15:39:55 ralph 24 23
c use flock for mailbox locking
e
s 00000/00000/00816
d D 4.21 83/11/01 10:02:02 karels 23 22
x 21 20
c un-protect -r (removing deltas 4.18, 4.19), so sendmail
c doesn't have to be setuid root and uucp can be known by other names
e
s 00001/00000/00820
d D 4.20 83/10/27 17:00:59 karels 22 21
c usage() sets error status EX_USAGE
e
s 00010/00011/00810
d D 4.19 83/10/25 09:04:27 eric 21 20
c fix botch in 4.18 that rejects all incoming UUCP mail; -r by a normal user
c how just ignores the -r flag rather than rejecting the mail.
e
s 00006/00000/00815
d D 4.18 83/09/09 16:11:07 ralph 20 19
c protects the -r option.
e
s 00001/00001/00814
d D 4.17 83/09/07 09:29:53 ralph 19 18
c only trap signals SIGHUP to SIGTERM, not 0 - 20.
e
s 00004/00002/00811
d D 4.16 83/08/11 19:52:44 sam 18 17
c sccs keyword fixes
e
s 00001/00001/00812
d D 4.15 83/04/12 02:53:41 leres 17 16
c Changed mode of created mail to 600; just like they do in the real world.
e
s 00008/00003/00805
d D 4.14 83/04/10 16:40:46 eric 16 15
c move call to lock before the fopen for append; change decl of "k" in
c copylet from int to long for PDP-11's.  Thanks to Jay Lepreau for these.
e
s 00001/00002/00807
d D 4.13 83/02/09 09:23:59 eric 15 14
c check uux exit status in the forward case; this doesn't happen with
c sendmail, but it offends my sensibilities anyhow.
e
s 00016/00004/00793
d D 4.12 83/01/31 21:18:18 eric 14 13
c patch BIG security hole with symbolic links (oh boy, was this one big!)
e
s 00014/00010/00783
d D 4.11 83/01/10 17:28:55 sam 13 12
c fix biff (rah rah -- sis boom bah)
e
s 00005/00005/00788
d D 4.10 82/12/26 21:34:43 eric 12 11
c change delivermail to sendmail throughout
e
s 00003/00003/00790
d D 4.9 82/11/14 16:33:19 sam 11 10
c convert to 4.1c sys calls and directory layout
e
s 00004/00001/00789
d D 4.8 82/03/31 12:02:35 root 10 9
c no more wellknown.h
e
s 00005/00073/00785
d D 4.7 82/03/15 04:18:08 root 9 8
c machine independent
e
s 00017/00009/00841
d D 4.6 82/02/28 23:59:42 wnj 8 7
c security merged with biff
e
s 00001/00000/00849
d D 4.5 81/10/03 17:45:05 root 7 6
c setuid(getuid()) before execv(DELIVERMAIL)
e
s 00001/00001/00848
d D 4.4 81/10/03 15:52:47 root 6 5
c typo
e
s 00005/00001/00844
d D 4.3 81/10/03 15:46:15 root 5 4
c don't write to mail files with > 1 link
e
s 00010/00000/00835
d D 4.2 81/05/08 15:02:21 wnj 4 3
c added biff to /bin/mail
e
s 00000/00000/00835
d D 4.1 80/10/01 16:39:20 bill 3 2
c Define 4.1
e
s 00013/00002/00822
d D 1.2 80/08/04 23:13:56 eric 2 1
c took out some stuff that delivermail does better (but made it
c 
e
s 00824/00000/00000
d D 1.1 80/08/04 22:59:44 root 1 0
c date and time created 80/08/04 22:59:44 by root
e
u
U
t
T
I 40
/*-
D 54
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 54
I 54
D 57
 * Copyright (c) 1990, 1993
E 57
I 57
 * Copyright (c) 1990, 1993, 1994
E 57
 *	The Regents of the University of California.  All rights reserved.
E 54
 *
 * %sccs.include.redist.c%
 */

E 40
I 18
#ifndef lint
I 40
D 54
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 54
I 54
static char copyright[] =
D 57
"%Z% Copyright (c) 1990, 1993\n\
E 57
I 57
"%Z% Copyright (c) 1990, 1993, 1994\n\
E 57
	The Regents of the University of California.  All rights reserved.\n";
E 54
#endif /* not lint */

#ifndef lint
E 40
D 28
static char sccsid[] = "%W% (Berkeley) %G%";
E 28
I 28
D 29
static char sccsid[] = "@(#)mail.c	4.25 (Berkeley) 5/1/85";
E 29
I 29
static char sccsid[] = "%W% (Berkeley) %G%";
E 29
E 28
D 40
#endif
E 40
I 40
#endif /* not lint */
E 40

I 71
/*
 * This is not intended to compile on System V derived systems
 * such as Solaris or HP-UX, since they use a totally different
 * approach to mailboxes (essentially, they have a setgid program
 * rather than setuid, and they rely on the ability to "give away"
 * files to do their work).  IT IS NOT A BUG that this doesn't
 * compile on such architectures.
 */

E 71
I 24
D 28
#include <sys/types.h>
E 28
I 28
#include <sys/param.h>
E 28
#include <sys/stat.h>
D 44
#include <sys/file.h>
E 44
D 40

E 24
E 18
I 1
#include <ctype.h>
#include <stdio.h>
E 40
I 40
#include <sys/socket.h>
I 49

E 49
D 44
#include <sys/syslog.h>
E 44
D 46
#include <sys/errno.h>
E 46
#include <netinet/in.h>
I 44
D 49
#include <syslog.h>
E 49
I 49

#include <errno.h>
E 49
#include <fcntl.h>
E 44
#include <netdb.h>
E 40
#include <pwd.h>
D 40
#include <utmp.h>
#include <signal.h>
D 24
#include <sys/types.h>
#include <sys/stat.h>
E 24
#include <setjmp.h>
D 9
#include <whoami.h>
E 9
#include <sysexits.h>
E 40
I 40
D 49
#include <time.h>
D 43
#include <varargs.h>
E 43
D 44
#include <stdio.h>
E 44
I 43
#include <unistd.h>
I 46
#include <errno.h>
E 49
E 46
E 43
D 44
#include <string.h>
E 44
I 44
#include <stdio.h>
E 44
#include <stdlib.h>
I 44
#include <string.h>
I 52
#include <sysexits.h>
E 52
I 49
#include <syslog.h>
#include <time.h>
#include <unistd.h>
I 70
#include <ctype.h>
E 70

I 52
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 52
E 49
E 44
E 40
I 38
D 60
#include "pathnames.h"
E 60
I 60
#ifndef LOCK_EX
# include <sys/file.h>
#endif
E 60
E 38
D 18

I 2
static char SccsId[] = "%W%	%G%";
E 18

I 60
#ifdef BSD4_4
# include "pathnames.h"
#endif

#ifndef __P
# ifdef __STDC__
#  define __P(protos)	protos
# else
#  define __P(protos)	()
#  define const
# endif
#endif
#ifndef __dead
# if defined(__GNUC__) && (__GNUC__ < 2 || __GNUC_MINOR__ < 5) && !defined(__STRICT_ANSI__)
#  define __dead	__volatile
# else
#  define __dead
# endif
#endif

#ifndef BSD4_4
# define _BSD_VA_LIST_	va_list
extern char	*strerror __P((int));
I 72
extern int	snprintf __P((char *, int, const char *, ...));
E 72
#endif

I 72
/*
D 73
 * Compile with -DHAS_SAVED_IDS=0 if you don't have saved uids.  It will
 * swap the effective uid (root) into the real uid using setreuid(),
 * setting the effective uid to the recipient user, and then swap root
 * back to effective uid when done.
 *
 * Use -DHAS_SAVED_IDS=1 if you can use seteuid(x) several times for
 * various values of "x" -- that is, if your system will notice that you
 * were originally invoked as root, and hence will allow future swaps.
 *
 * The following heuristic works for most common systems.  Note that
 * SunOS claims to have _POSIX_SAVED_IDS, but doesn't -- but it does
 * have an older version of _POSIX_VERSION.
 *
 * If you have a pure Posix system that does not have seteuid() or
 * setreuid() (emulations don't count!) then you are out of luck.
E 73
I 73
 * If you don't have setreuid, and you have saved uids, and you have
 * a seteuid() call that doesn't try to emulate using setuid(), then
 * you can try defining USE_SETEUID.
E 73
 */
D 73

#ifndef HASSAVEDUIDS
# if defined(_POSIX_SAVED_IDS) && _POSIX_VERSION >= 199009L
#  define HAS_SAVED_IDS	1
# else
#  define HAS_SAVED_IDS	0
# endif
E 73
I 73
#ifdef USE_SETEUID
# define setreuid(r, e)		seteuid(e)
E 73
#endif

D 73
#ifdef __hpux
# define seteuid(e)	setresuid(-1, e, -1)
#endif

E 73
E 72
#ifndef _PATH_LOCTMP
# define _PATH_LOCTMP	"/tmp/local.XXXXXX"
#endif
#ifndef _PATH_MAILDIR
# define _PATH_MAILDIR	"/var/spool/mail"
#endif

D 66
#ifndef S_ISLNK
# define S_ISLNK(mode)	(((mode) & _S_IFMT) == S_IFLNK)
E 66
I 66
#ifndef S_ISREG
# define S_ISREG(mode)	(((mode) & _S_IFMT) == S_IFREG)
E 66
#endif

E 60
E 2
D 12
#define DELIVERMAIL	"/etc/delivermail"
E 12
I 12
D 38
#define SENDMAIL	"/usr/lib/sendmail"
E 12

E 38
I 24
D 40
	/* copylet flags */
#define REMOTE		1		/* remote mail, add rmtmsg */
#define ORDINARY	2
#define ZAP		3		/* zap header and trailing empty line */
#define	FORWARD		4
E 40
I 40
D 52
#define	FATAL		1
#define	NOTFATAL	0
E 52
I 52
int eval = EX_OK;			/* sysexits.h error value. */
E 52
E 40
E 24

I 46
D 52
int	deliver __P((int, char *));
void	err __P((int, const char *, ...));
void	notifybiff __P((char *));
int	store __P((char *));
void	usage __P((void));
E 52
I 52
void		deliver __P((int, char *));
void		e_to_sys __P((int));
__dead void	err __P((const char *, ...));
void		notifybiff __P((char *));
int		store __P((char *));
void		usage __P((void));
void		vwarn __P((const char *, _BSD_VA_LIST_));
void		warn __P((const char *, ...));
E 52

I 49
int
E 49
E 46
D 24
/*copylet flags */
	/*remote mail, add rmtmsg */
#define REMOTE	1
	/* zap header and trailing empty line */
#define ZAP	3
#define ORDINARY 2
#define	FORWARD	4
#define	LSIZE	256
#define	MAXLET	300	/* maximum number of letters */
D 17
#define	MAILMODE (~0644)		/* mode of created mail */
E 17
I 17
#define	MAILMODE (~0600)		/* mode of created mail */
E 24
I 24
D 40
#define	LSIZE		256
#define	MAXLET		300		/* maximum number of letters */
#define	MAILMODE	0600		/* mode of created mail */
E 24
E 17
I 2
D 9
# ifndef DELIVERMAIL
E 2
#define	RMAIL	"/usr/net/bin/sendberkmail"
#define LOCNAM1	"csvax"
#define LOCNAM2	"ucbvax"
#define LOCNAM3	"vax"
#define LOCNAM4	"v"
I 2
# endif
E 9
E 2

char	line[LSIZE];
char	resp[LSIZE];
struct let {
	long	adr;
	char	change;
} let[MAXLET];
int	nlet	= 0;
char	lfil[50];
long	iop, time();
char	*getenv();
char	*index();
D 38
char	lettmp[] = "/tmp/maXXXXX";
char	maildir[] = "/usr/spool/mail/";
E 38
I 38
char	lettmp[] = _PATH_TMP;
D 39
char	maildir[] = _PATH_MAILDIR;
E 39
I 39
char	maildir[sizeof(_PATH_MAILDIR) + 5] = _PATH_MAILDIR;
E 39
E 38
char	mailfile[] = "/usr/spool/mail/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
char	dead[] = "dead.letter";
D 9
char	*thissys = sysname;
E 9
D 24
char	*netname = "vax";
E 24
char	forwmsg[] = " forwarded\n";
FILE	*tmpf;
FILE	*malf;
D 28
char	*my_name;
E 28
I 28
char	my_name[60];
E 28
char	*getlogin();
D 24
struct	passwd	*getpwuid();
E 24
int	error;
int	changed;
int	forward;
char	from[] = "From ";
long	ftell();
D 24
int	delete();
E 24
I 24
int	delex();
E 24
char	*ctime();
int	flgf;
int	flgp;
int	delflg = 1;
int	hseqno;
jmp_buf	sjbuf;
int	rmail;

E 40
main(argc, argv)
D 40
char **argv;
{
D 33
	register i;
E 33
I 33
	register int i;
E 33
I 28
	char *name;
E 28
I 27
	struct passwd *pwent;
E 27
D 24
	char sobuf[BUFSIZ];
E 24

I 39
	(void)strcat(maildir, "/");
E 39
D 24
	setbuf(stdout, sobuf);
E 24
D 26
	mktemp(lettmp);
	unlink(lettmp);
E 26
D 28
	my_name = getlogin();
D 24
	if (my_name == NULL || strlen(my_name) == 0) {
E 24
I 24
	if (my_name == NULL || *my_name == '\0') {
E 28
I 28
D 33
	name = getlogin();
	if (name == NULL || *name == '\0') {
E 33
I 33
	if (!(name = getlogin()) || !*name || !(pwent = getpwnam(name)) ||
	    getuid() != pwent->pw_uid) 
E 33
E 28
E 24
D 27
		struct passwd *pwent;
E 27
		pwent = getpwuid(getuid());
D 33
		if (pwent==NULL)
D 28
			my_name = "???";
E 28
I 28
			name = "???";
E 28
		else
D 28
			my_name = pwent->pw_name;
E 28
I 28
			name = pwent->pw_name;
E 28
I 27
	}
	else {
D 31
		pwent = getpwnam(my_name);
		if ( getuid() != pwent->pw_uid) {
E 31
I 31
		pwent = getpwnam(name);
		if (!pwent || getuid() != pwent->pw_uid) {
E 31
			pwent = getpwuid(getuid());
D 28
			my_name = pwent->pw_name;
E 28
I 28
			name = pwent->pw_name;
E 28
		}
E 27
	}
I 28
	strncpy(my_name, name, sizeof(my_name)-1);
E 33
I 33
	strncpy(my_name, pwent ? pwent->pw_name : "???", sizeof(my_name)-1);
E 33
E 28
D 24
	if(setjmp(sjbuf)) done();
D 19
	for (i=0; i<20; i++)
E 19
I 19
	for (i=SIGHUP; i<=SIGTERM; i++)
E 19
		setsig(i, delete);
	tmpf = fopen(lettmp, "w");
	if (tmpf == NULL) {
		fprintf(stderr, "mail: cannot open %s for writing\n", lettmp);
E 24
I 24
	if (setjmp(sjbuf))
E 24
		done();
D 24
	}
E 24
I 24
	for (i=SIGHUP; i<=SIGTERM; i++)
		setsig(i, delex);
D 26
	tmpf = fopen(lettmp, "w+r");
	if (tmpf == NULL)
E 26
I 26
	i = mkstemp(lettmp);
D 37
	tmpf = fdopen(i, "r+w");
E 37
I 37
	tmpf = fdopen(i, "r+");
E 37
	if (i < 0 || tmpf == NULL)
E 26
		panic("mail: %s: cannot open for writing", lettmp);
	/*
	 * This protects against others reading mail from temp file and
	 * if we exit, the file will be deleted already.
	 */
	unlink(lettmp);
E 24
	if (argv[0][0] == 'r')
		rmail++;
	if (argv[0][0] != 'r' &&	/* no favors for rmail*/
	   (argc == 1 || argv[1][0] == '-' && !any(argv[1][1], "rhd")))
		printmail(argc, argv);
	else
D 8
		sendmail(argc, argv);
E 8
I 8
		bulkmail(argc, argv);
E 8
	done();
}

setsig(i, f)
int i;
int (*f)();
{
D 24
	if(signal(i, SIG_IGN)!=SIG_IGN)
E 24
I 24
	if (signal(i, SIG_IGN) != SIG_IGN)
E 24
		signal(i, f);
}

any(c, str)
	register int c;
	register char *str;
{

	while (*str)
		if (c == *str++)
			return(1);
	return(0);
}

printmail(argc, argv)
E 40
I 40
	int argc;
E 40
D 24
char **argv;
E 24
I 24
D 52
	char **argv;
E 52
I 52
	char *argv[];
E 52
E 24
{
D 40
	int flg, i, j, print;
	char *p, *getarg();
	struct stat statb;
E 40
I 40
D 48
	extern int optind;
	extern char *optarg;
E 48
	struct passwd *pw;
D 52
	int ch, fd, eval;
E 52
I 52
	int ch, fd;
E 52
	uid_t uid;
	char *from;
I 60
	extern char *optarg;
	extern int optind;
E 60
E 40

I 68
	/* make sure we have some open file descriptors */
	for (fd = 10; fd < 30; fd++)
		(void) close(fd);

	/* use a reasonable umask */
D 69
	(void) umask(0077)
E 69
I 69
	(void) umask(0077);
E 69

E 68
I 60
#ifdef LOG_MAIL
E 60
D 40
	setuid(getuid());
	cat(mailfile, maildir, my_name);
I 24
#ifdef notdef
E 24
	if (stat(mailfile, &statb) >= 0
	    && (statb.st_mode & S_IFMT) == S_IFDIR) {
		strcat(mailfile, "/");
		strcat(mailfile, my_name);
	}
D 24
	for (; argc>1; argv++, argc--) {
		if (argv[1][0]=='-') {
			if (argv[1][1]=='q')
				delflg = 0;
			else if (argv[1][1]=='p') {
				flgp++;
				delflg = 0;
			} else if (argv[1][1]=='f') {
				if (argc>=3) {
					strcpy(mailfile, argv[2]);
					argv++;
					argc--;
				}
			} else if (argv[1][1]=='r') {
				forward = 1;
			} else if (argv[1][1]=='h') {
				forward = 1;
			} else {
				fprintf(stderr, "mail: unknown option %c\n", argv[1][1]);
				done();
E 24
I 24
#endif
	for (; argc > 1; argv++, argc--) {
		if (argv[1][0] != '-')
			break;
		switch (argv[1][1]) {
E 40
I 40
D 51
	openlog("mail.local", LOG_PERROR, LOG_MAIL);
E 51
I 51
	openlog("mail.local", 0, LOG_MAIL);
I 60
#else
	openlog("mail.local", 0);
#endif
E 60
E 51
E 40

D 40
		case 'p':
			flgp++;
			/* fall thru... */
		case 'q':
			delflg = 0;
E 40
I 40
	from = NULL;
	while ((ch = getopt(argc, argv, "df:r:")) != EOF)
		switch(ch) {
D 52
		case 'd':		/* backward compatible */
E 52
I 52
		case 'd':		/* Backward compatible. */
E 52
E 40
			break;
D 40

E 40
		case 'f':
D 40
			if (argc >= 3) {
				strcpy(mailfile, argv[2]);
				argv++, argc--;
E 24
			}
E 40
I 40
D 52
		case 'r':		/* backward compatible */
			if (from)
D 46
			    error(FATAL, "multiple -f options.");
E 46
I 46
			    err(FATAL, "multiple -f options");
E 52
I 52
		case 'r':		/* Backward compatible. */
			if (from != NULL) {
				warn("multiple -f options");
				usage();
			}
E 52
E 46
			from = optarg;
E 40
D 24
		} else
E 24
			break;
I 24
D 40

		case 'b':
			forward = 1;
			break;

E 40
I 40
		case '?':
E 40
		default:
D 40
			panic("unknown option %c", argv[1][1]);
			/*NOTREACHED*/
E 40
I 40
			usage();
E 40
		}
E 24
D 40
	}
	malf = fopen(mailfile, "r");
	if (malf == NULL) {
D 24
		fprintf(stdout, "No mail.\n");
E 24
I 24
		printf("No mail.\n");
E 24
		return;
	}
D 24
	lock(mailfile);
E 24
I 24
	flock(fileno(malf), LOCK_SH);
E 24
	copymt(malf, tmpf);
D 24
	fclose(malf);
	fclose(tmpf);
	unlock();
	tmpf = fopen(lettmp, "r");
E 24
I 24
	fclose(malf);			/* implicit unlock */
D 34
	fseek(tmpf, 0, L_SET);
E 34
I 34
	fseek(tmpf, 0L, L_SET);
E 40
I 40
	argc -= optind;
	argv += optind;
E 40
E 34
E 24

D 40
	changed = 0;
	print = 1;
	for (i = 0; i < nlet; ) {
		j = forward ? i : nlet - i - 1;
D 24
		if(setjmp(sjbuf)) {
			print=0;
E 24
I 24
		if (setjmp(sjbuf)) {
			print = 0;
E 24
		} else {
			if (print)
				copylet(j, stdout, ORDINARY);
			print = 1;
		}
		if (flgp) {
			i++;
			continue;
		}
		setjmp(sjbuf);
D 24
		fprintf(stdout, "? ");
E 24
I 24
		fputs("? ", stdout);
E 24
		fflush(stdout);
		if (fgets(resp, LSIZE, stdin) == NULL)
			break;
		switch (resp[0]) {
E 40
I 40
	if (!*argv)
		usage();
E 40

D 40
		default:
D 24
			fprintf(stderr, "usage\n");
E 24
I 24
			printf("usage\n");
E 24
		case '?':
			print = 0;
D 24
			fprintf(stderr, "q\tquit\n");
			fprintf(stderr, "x\texit without changing mail\n");
			fprintf(stderr, "p\tprint\n");
			fprintf(stderr, "s[file]\tsave (default mbox)\n");
			fprintf(stderr, "w[file]\tsame without header\n");
			fprintf(stderr, "-\tprint previous\n");
			fprintf(stderr, "d\tdelete\n");
			fprintf(stderr, "+\tnext (no delete)\n");
			fprintf(stderr, "m user\tmail to user\n");
			fprintf(stderr, "! cmd\texecute cmd\n");
E 24
I 24
			printf("q\tquit\n");
			printf("x\texit without changing mail\n");
			printf("p\tprint\n");
			printf("s[file]\tsave (default mbox)\n");
			printf("w[file]\tsame without header\n");
			printf("-\tprint previous\n");
			printf("d\tdelete\n");
			printf("+\tnext (no delete)\n");
			printf("m user\tmail to user\n");
			printf("! cmd\texecute cmd\n");
E 24
			break;
E 40
I 40
	/*
	 * If from not specified, use the name from getlogin() if the
	 * uid matches, otherwise, use the name from the password file
	 * corresponding to the uid.
	 */
	uid = getuid();
D 41
	if (!from || !(from = getlogin()) ||
	    !(pw = getpwnam(from)) || pw->pw_uid != uid)
E 41
I 41
	if (!from && (!(from = getlogin()) ||
	    !(pw = getpwnam(from)) || pw->pw_uid != uid))
E 41
		from = (pw = getpwuid(uid)) ? pw->pw_name : "???";
E 40

D 40
		case '+':
		case 'n':
		case '\n':
			i++;
			break;
		case 'x':
			changed = 0;
		case 'q':
			goto donep;
		case 'p':
			break;
		case '^':
		case '-':
			if (--i < 0)
				i = 0;
			break;
		case 'y':
		case 'w':
		case 's':
			flg = 0;
			if (resp[1] != '\n' && resp[1] != ' ') {
				printf("illegal\n");
				flg++;
				print = 0;
				continue;
			}
			if (resp[1] == '\n' || resp[1] == '\0') {
				p = getenv("HOME");
D 24
				if(p != 0)
E 24
I 24
				if (p != 0)
E 24
					cat(resp+1, p, "/mbox");
				else
					cat(resp+1, "", "mbox");
			}
			for (p = resp+1; (p = getarg(lfil, p)) != NULL; ) {
				malf = fopen(lfil, "a");
				if (malf == NULL) {
D 24
					fprintf(stdout, "mail: cannot append to %s\n", lfil);
E 24
I 24
					printf("mail: %s: cannot append\n",
					    lfil);
E 24
					flg++;
					continue;
				}
				copylet(j, malf, resp[0]=='w'? ZAP: ORDINARY);
				fclose(malf);
			}
			if (flg)
				print = 0;
			else {
				let[j].change = 'd';
				changed++;
				i++;
			}
			break;
		case 'm':
			flg = 0;
			if (resp[1] == '\n' || resp[1] == '\0') {
				i++;
				continue;
			}
			if (resp[1] != ' ') {
				printf("invalid command\n");
				flg++;
				print = 0;
				continue;
			}
			for (p = resp+1; (p = getarg(lfil, p)) != NULL; )
D 24
				if (!sendrmt(j, lfil, "/bin/mail"))	/* couldn't send it */
E 24
I 24
D 25
				if (!sendrmt(j, lfil, "/bin/mail"))
E 25
I 25
				if (!sendmail(j, lfil, my_name))
E 25
E 24
					flg++;
			if (flg)
				print = 0;
			else {
				let[j].change = 'd';
				changed++;
				i++;
			}
			break;
		case '!':
			system(resp+1);
			printf("!\n");
			print = 0;
			break;
		case 'd':
			let[j].change = 'd';
			changed++;
			i++;
			if (resp[1] == 'q')
				goto donep;
			break;
		}
	}
   donep:
	if (changed)
		copyback();
E 40
I 40
D 52
	fd = store(from);
	for (eval = 0; *argv; ++argv)
		eval |= deliver(fd, *argv);
E 52
I 52
	/*
	 * There is no way to distinguish the error status of one delivery
	 * from the rest of the deliveries.  So, if we failed hard on one
	 * or more deliveries, but had no failures on any of the others, we
	 * return a hard failure.  If we failed temporarily on one or more
	 * deliveries, we return a temporary failure regardless of the other
	 * failures.  This results in the delivery being reattempted later
	 * at the expense of repeated failures and multiple deliveries.
	 */
	for (fd = store(from); *argv; ++argv)
		deliver(fd, *argv);
E 52
	exit(eval);
E 40
}

I 49
int
E 49
D 24
copyback()	/* copy temp or whatever back to /usr/spool/mail */
E 24
I 24
D 40
/* copy temp or whatever back to /usr/spool/mail */
copyback()
E 40
I 40
store(from)
	char *from;
E 40
E 24
{
D 24
	register i, n, c;
	int new = 0;
E 24
I 24
D 34
	register i, c;
	int fd, new = 0, oldmask;
E 34
I 34
D 40
	register int i, c;
	long oldmask;
	int fd, new = 0;
E 34
E 24
	struct stat stbuf;
E 40
I 40
	FILE *fp;
	time_t tval;
	int fd, eline;
D 60
	char *tn, line[2048];
E 60
I 60
	char line[2048];
	char tmpbuf[sizeof _PATH_LOCTMP + 1];
E 60
E 40

D 24
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	lock(mailfile);
	stat(mailfile, &stbuf);
E 24
I 24
D 34
#define	mask(s)	(1 << ((s) - 1))
	oldmask = sigblock(mask(SIGINT)|mask(SIGHUP)|mask(SIGQUIT));
#undef mask
E 34
I 34
D 40
	oldmask = sigblock(sigmask(SIGINT)|sigmask(SIGHUP)|sigmask(SIGQUIT));
E 34
	fd = open(mailfile, O_RDWR | O_CREAT, MAILMODE);
	if (fd >= 0) {
		flock(fd, LOCK_EX);
D 37
		malf = fdopen(fd, "r+w");
E 37
I 37
		malf = fdopen(fd, "r+");
E 37
	}
	if (fd < 0 || malf == NULL)
		panic("can't rewrite %s", lfil);
	fstat(fd, &stbuf);
E 24
	if (stbuf.st_size != let[nlet].adr) {	/* new mail has arrived */
D 24
		malf = fopen(mailfile, "r");
		if (malf == NULL) {
			fprintf(stdout, "mail: can't re-read %s\n", mailfile);
			done();
		}
		fseek(malf, let[nlet].adr, 0);
		fclose(tmpf);
		tmpf = fopen(lettmp, "a");
		fseek(tmpf, let[nlet].adr, 0);
		while ((c = fgetc(malf)) != EOF)
			fputc(c, tmpf);
		fclose(malf);
		fclose(tmpf);
		tmpf = fopen(lettmp, "r");
E 24
I 24
		fseek(malf, let[nlet].adr, L_SET);
		fseek(tmpf, let[nlet].adr, L_SET);
		while ((c = getc(malf)) != EOF)
			putc(c, tmpf);
E 24
		let[++nlet].adr = stbuf.st_size;
		new = 1;
I 24
D 34
		fseek(malf, 0, L_SET);
E 34
I 34
		fseek(malf, 0L, L_SET);
E 34
E 24
	}
D 24
	malf = fopen(mailfile, "w");
	if (malf == NULL) {
		fprintf(stderr, "mail: can't rewrite %s\n", lfil);
		done();
	}
	n = 0;
E 24
I 24
D 34
	ftruncate(fd, 0);
E 34
I 34
	ftruncate(fd, 0L);
E 34
E 24
	for (i = 0; i < nlet; i++)
D 24
		if (let[i].change != 'd') {
E 24
I 24
		if (let[i].change != 'd')
E 24
			copylet(i, malf, ORDINARY);
D 24
			n++;
		}
	fclose(malf);
E 24
I 24
	fclose(malf);		/* implict unlock */
E 24
	if (new)
D 24
		fprintf(stdout, "new mail arrived\n");
	unlock();
E 24
I 24
		printf("New mail has arrived.\n");
	sigsetmask(oldmask);
E 24
}
E 40
I 40
D 45
	tn = _PATH_LOCTMP;
E 45
I 45
D 60
	tn = strdup(_PATH_LOCTMP);
E 45
D 49
	if ((fd = mkstemp(tn)) == -1 || !(fp = fdopen(fd, "w+")))
E 49
I 49
D 52
	if ((fd = mkstemp(tn)) == -1 || (fp = fdopen(fd, "w+")) == NULL)
E 49
D 46
		error(FATAL, "unable to open temporary file.");
E 46
I 46
		err(FATAL, "unable to open temporary file");
E 52
I 52
	if ((fd = mkstemp(tn)) == -1 || (fp = fdopen(fd, "w+")) == NULL) {
E 60
I 60
	strcpy(tmpbuf, _PATH_LOCTMP);
	if ((fd = mkstemp(tmpbuf)) == -1 || (fp = fdopen(fd, "w+")) == NULL) {
E 60
		e_to_sys(errno);
		err("unable to open temporary file");
	}
E 52
E 46
D 60
	(void)unlink(tn);
I 45
	free(tn);
E 60
I 60
	(void)unlink(tmpbuf);
E 60
E 45
E 40

D 24
copymt(f1, f2)	/* copy mail (f1) to temp (f2) */
FILE *f1, *f2;
E 24
I 24
D 40
/* copy mail (f1) to temp (f2) */
copymt(f1, f2)
	FILE *f1, *f2;
E 24
{
	long nextadr;
E 40
I 40
	(void)time(&tval);
	(void)fprintf(fp, "From %s %s", from, ctime(&tval));
E 40

D 40
	nlet = nextadr = 0;
	let[0].adr = 0;
	while (fgets(line, LSIZE, f1) != NULL) {
		if (isfrom(line))
			let[nlet++].adr = nextadr;
		nextadr += strlen(line);
		fputs(line, f2);
E 40
I 40
	line[0] = '\0';
	for (eline = 1; fgets(line, sizeof(line), stdin);) {
		if (line[0] == '\n')
			eline = 1;
		else {
D 53
			if (eline && line[0] == 'F' && !bcmp(line, "From ", 5))
E 53
I 53
			if (eline && line[0] == 'F' &&
			    !memcmp(line, "From ", 5))
E 53
				(void)putc('>', fp);
			eline = 0;
		}
		(void)fprintf(fp, "%s", line);
D 52
		if (ferror(fp))
			break;
E 52
I 52
		if (ferror(fp)) {
			e_to_sys(errno);
			err("temporary file write error");
		}
E 52
E 40
	}
D 40
	let[nlet].adr = nextadr;	/* last plus 1 */
}
E 40

D 16
copylet(n, f, type) FILE *f;
{	int ch, k;
E 16
I 16
D 40
copylet(n, f, type)
	FILE *f;
{
	int ch;
	long k;
I 24
D 28
	char hostname[32];
E 28
I 28
	char hostname[MAXHOSTNAMELEN];
E 40
I 40
	/* If message not newline terminated, need an extra. */
D 52
	if (!index(line, '\n'))
E 52
I 52
	if (!strchr(line, '\n'))
E 52
		(void)putc('\n', fp);
	/* Output a newline; note, empty messages are allowed. */
	(void)putc('\n', fp);
E 40
E 28
E 24

E 16
D 24
	fseek(tmpf, let[n].adr, 0);
E 24
I 24
D 40
	fseek(tmpf, let[n].adr, L_SET);
E 24
	k = let[n+1].adr - let[n].adr;
D 24
	while(k-- > 1 && (ch=fgetc(tmpf))!='\n')
		if(type!=ZAP) fputc(ch,f);
D 9
	if(type==REMOTE)
		fprintf(f, " remote from %s\n", thissys);
	else if (type==FORWARD)
E 9
I 9
	if(type==REMOTE) {
		char hostname[32];
E 24
I 24
	while (k-- > 1 && (ch = getc(tmpf)) != '\n')
		if (type != ZAP)
			putc(ch, f);
	switch (type) {

	case REMOTE:
E 24
		gethostname(hostname, sizeof (hostname));
		fprintf(f, " remote from %s\n", hostname);
D 24
	} else if (type==FORWARD)
E 24
I 24
		break;

	case FORWARD:
E 24
E 9
		fprintf(f, forwmsg);
D 24
	else if(type==ORDINARY)
		fputc(ch,f);
	while(k-->1)
		fputc(ch=fgetc(tmpf), f);
	if(type!=ZAP || ch!= '\n')
		fputc(fgetc(tmpf), f);
E 24
I 24
		break;

	case ORDINARY:
		putc(ch, f);
		break;

I 25
	case ZAP:
		break;

E 25
	default:
		panic("Bad letter type %d to copylet.", type);
	}
	while (k-- > 1) {
		ch = getc(tmpf);
		putc(ch, f);
	}
	if (type != ZAP || ch != '\n')
		putc(getc(tmpf), f);
E 40
I 40
D 52
	(void)fflush(fp);
	if (ferror(fp))
D 46
		error(FATAL, "temporary file write error.");
E 46
I 46
		err(FATAL, "temporary file write error");
E 46
	return(fd);
E 52
I 52
	if (fflush(fp) == EOF || ferror(fp)) {
		e_to_sys(errno);
		err("temporary file write error");
	}
	return (fd);
E 52
E 40
E 24
}

I 49
D 52
int
E 52
I 52
void
E 52
E 49
D 40
isfrom(lp)
register char *lp;
E 40
I 40
deliver(fd, name)
	int fd;
	char *name;
E 40
{
D 40
	register char *p;
E 40
I 40
D 58
	struct stat sb;
E 58
I 58
	struct stat fsb, sb;
E 58
	struct passwd *pw;
D 52
	int created, mbfd, nr, nw, off, rval;
E 52
I 52
	int mbfd, nr, nw, off;
I 70
	char *p;
E 70
E 52
	char biffmsg[100], buf[8*1024], path[MAXPATHLEN];
D 48
	off_t curoff, lseek();
E 48
I 48
	off_t curoff;
E 48
E 40

D 40
	for (p = from; *p; )
		if (*lp++ != *p++)
			return(0);
	return(1);
}
E 40
I 40
	/*
	 * Disallow delivery to unknown names -- special mailboxes can be
	 * handled in the sendmail aliases file.
	 */
	if (!(pw = getpwnam(name))) {
D 46
		error(NOTFATAL, "unknown name: %s.", name);
E 46
I 46
D 52
		err(NOTFATAL, "unknown name: %s", name);
E 46
		return(1);
E 52
I 52
		if (eval != EX_TEMPFAIL)
			eval = EX_UNAVAILABLE;
		warn("unknown name: %s", name);
		return;
E 52
	}
I 75
	endpwent();
E 75
E 40

I 70
	/*
	 * Keep name reasonably short to avoid buffer overruns.
	 *	This isn't necessary on BSD because of the proper
	 *	definition of snprintf(), but it can cause problems
	 *	on other systems.
	 * Also, clear out any bogus characters.
	 */

	if (strlen(name) > 40)
		name[40] = '\0';
	for (p = name; *p != '\0'; p++)
	{
		if (!isascii(*p))
			*p &= 0x7f;
		else if (!isprint(*p))
			*p = '.';
	}

E 70
D 8
sendmail(argc, argv)
E 8
I 8
D 40
bulkmail(argc, argv)
E 8
char **argv;
{
D 28
	char truename[100];
E 28
I 28
	char *truename;
E 28
	int first;
	register char *cp;
D 28
	int gaver = 0;
E 28
D 9
# ifdef DELIVERMAIL
E 9
	char *newargv[1000];
	register char **ap;
	register char **vp;
	int dflag;
E 40
I 40
D 49
	(void)sprintf(path, "%s/%s", _PATH_MAILDIR, name);
E 49
I 49
	(void)snprintf(path, sizeof(path), "%s/%s", _PATH_MAILDIR, name);
E 49
E 40

D 40
	dflag = 0;
I 28
	delflg = 0;
E 28
D 24
	if (argc < 1)
E 24
I 24
	if (argc < 1) {
E 24
		fprintf(stderr, "puke\n");
I 24
		return;
E 40
I 40
D 52
	if (!(created = lstat(path, &sb)) &&
	    (sb.st_nlink != 1 || S_ISLNK(sb.st_mode))) {
D 46
		error(NOTFATAL, "%s: linked file.", path);
E 46
I 46
		err(NOTFATAL, "%s: linked file", path);
E 46
		return(1);
E 40
	}
E 24
D 40
	for (vp = argv, ap = newargv + 1; (*ap = *vp++) != 0; ap++)
D 24
	{
E 24
		if (ap[0][0] == '-' && ap[0][1] == 'd')
			dflag++;
D 24
	}
	if (!dflag)
	{
E 24
I 24
	if (!dflag) {
E 24
D 12
		/* give it to delivermail, rah rah! */
E 12
I 12
		/* give it to sendmail, rah rah! */
E 12
		unlink(lettmp);
		ap = newargv+1;
		if (rmail)
			*ap-- = "-s";
D 12
		*ap = "-delivermail";
E 12
I 12
		*ap = "-sendmail";
E 12
I 7
		setuid(getuid());
E 7
D 12
		execv(DELIVERMAIL, ap);
		perror(DELIVERMAIL);
E 12
I 12
D 38
		execv(SENDMAIL, ap);
		perror(SENDMAIL);
E 38
I 38
		execv(_PATH_SENDMAIL, ap);
		perror(_PATH_SENDMAIL);
E 38
E 12
		exit(EX_UNAVAILABLE);
	}
E 40
D 9
# endif DELIVERMAIL
E 9

E 52
D 28
	truename[0] = 0;
E 28
I 28
D 40
	truename = 0;
E 28
	line[0] = '\0';

E 40
	/*
D 40
	 * When we fall out of this, argv[1] should be first name,
	 * argc should be number of names + 1.
E 40
I 40
D 52
	 * There's a race here -- two processes think they both created
	 * the file.  This means the file cannot be unlinked.
E 52
I 52
D 57
	 * If the mailbox is a linked or a symlink, fail.
E 57
I 57
	 * If the mailbox is linked or a symlink, fail.  There's an obvious
	 * race here, that the file was replaced with a symbolic link after
D 58
	 * the lstat returned, but before the open.  Mail.local cannot detect
	 * this race.  Furthermore, it's a symptom of a larger problem, that
	 * the mail spooling directory is writeable by the wrong users.  NB:
	 * if that directory is writeable, system security is compromised for
	 * other reasons, and it cannot be fixed here.  Be that as it may, we
	 * we make the race harder by checking after the open as well.
E 58
I 58
	 * the lstat returned, but before the open.  We attempt to detect
	 * this by comparing the original stat information and information
	 * returned by an fstat of the file descriptor returned by the open.
E 58
E 57
	 *
I 58
	 * NB: this is a symptom of a larger problem, that the mail spooling
	 * directory is writeable by the wrong users.  If that directory is
	 * writeable, system security is compromised for other reasons, and
	 * it cannot be fixed here.
	 *
E 58
	 * If we created the mailbox, set the owner/group.  If that fails,
	 * just return.  Another process may have already opened it, so we
	 * can't unlink it.  Historically, binmail set the owner/group at
	 * each mail delivery.  We no longer do this, assuming that if the
	 * ownership or permissions were changed there was a reason.
	 *
	 * XXX
	 * open(2) should support flock'ing the file.
E 52
E 40
	 */
I 59
tryagain:
I 61
	lockmbox(path);
E 61
E 59
I 40
D 52
	if ((mbfd =
	    open(path, O_APPEND|O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR)) < 0) {
D 46
		error(NOTFATAL, "%s: %s.", path, strerror(errno));
E 46
I 46
		err(NOTFATAL, "%s: %s", path, strerror(errno));
E 46
		return(1);
E 52
I 52
	if (lstat(path, &sb)) {
D 59
		if ((mbfd = open(path,
		    O_APPEND|O_CREAT|O_EXCL|O_WRONLY, S_IRUSR|S_IWUSR)) < 0)
			mbfd = open(path, O_APPEND|O_WRONLY, 0);
		else if (fchown(mbfd, pw->pw_uid, pw->pw_gid)) {
E 59
I 59
		mbfd = open(path,
		    O_APPEND|O_CREAT|O_EXCL|O_WRONLY, S_IRUSR|S_IWUSR);
		if (mbfd == -1) {
			if (errno == EEXIST)
				goto tryagain;
		} else if (fchown(mbfd, pw->pw_uid, pw->pw_gid)) {
E 59
			e_to_sys(errno);
			warn("chown %u.%u: %s", pw->pw_uid, pw->pw_gid, name);
I 61
D 72
			unlockmbox();
E 61
			return;
E 72
I 72
			goto err1;
E 72
		}
D 66
	} else if (sb.st_nlink != 1 || S_ISLNK(sb.st_mode)) {
E 66
I 66
	} else if (sb.st_nlink != 1 || !S_ISREG(sb.st_mode)) {
E 66
		e_to_sys(errno);
D 66
		warn("%s: linked file", path);
E 66
I 66
		warn("%s: irregular file", path);
E 66
I 61
D 72
		unlockmbox();
E 61
		return;
E 72
I 72
		goto err0;
E 72
I 64
	} else if (sb.st_uid != pw->pw_uid) {
		warn("%s: wrong ownership (%d)", path, sb.st_uid);
		unlockmbox();
		return;
E 64
D 57
	} else
E 57
I 57
	} else {
E 57
		mbfd = open(path, O_APPEND|O_WRONLY, 0);
I 57
D 58
		if (mbfd != -1 && (lstat(path, &sb) ||
		    sb.st_nlink != 1 || S_ISLNK(sb.st_mode))) {
			e_to_sys(errno);
			warn("%s: missing or linked file", path);
E 58
I 58
		if (mbfd != -1 &&
		    (fstat(mbfd, &fsb) || fsb.st_nlink != 1 ||
D 66
		    S_ISLNK(fsb.st_mode) || sb.st_dev != fsb.st_dev ||
D 64
		    sb.st_ino != fsb.st_ino)) {
E 64
I 64
		    sb.st_ino != fsb.st_ino) || sb.st_uid != fsb.st_uid) {
E 66
I 66
		    !S_ISREG(fsb.st_mode) || sb.st_dev != fsb.st_dev ||
		    sb.st_ino != fsb.st_ino || sb.st_uid != fsb.st_uid)) {
E 66
E 64
			warn("%s: file changed after open", path);
E 58
D 72
			(void)close(mbfd);
I 61
			unlockmbox();
E 61
			return;
E 72
I 72
			goto err1;
E 72
		}
	}
E 57

	if (mbfd == -1) {
		e_to_sys(errno);
		warn("%s: %s", path, strerror(errno));
I 61
D 72
		unlockmbox();
E 61
		return;
E 72
I 72
		goto err0;
E 72
E 52
	}
E 40

D 40
	while (argc > 1 && *argv[1] == '-') {
		cp = *++argv;
		argc--;
		switch (cp[1]) {
		case 'r':
D 24
			if (argc <= 0) {
E 24
I 24
			if (argc <= 1)
E 24
				usage();
D 24
				done();
			}
E 24
I 20
D 21
			if (strcmp(my_name, "root") &&
			    strcmp(my_name, "daemon") &&
			    strcmp(my_name, "network")) {
				usage();
				done();
E 21
I 21
			if (strcmp(my_name, "root") == 0 ||
			    strcmp(my_name, "daemon") == 0 ||
			    strcmp(my_name, "network") == 0 ||
			    strcmp(my_name, "uucp")) {
				gaver++;
				strcpy(truename, argv[1]);
				fgets(line, LSIZE, stdin);
				if (strncmp("From", line, 4) == 0)
					line[0] = '\0';
E 21
			}
E 20
D 21
D 28
			gaver++;
			strcpy(truename, argv[1]);
E 28
I 28
			truename = argv[1];
E 28
			fgets(line, LSIZE, stdin);
D 36
			if (strcmpn("From", line, 4) == 0)
E 36
I 36
			if (strncmp("From", line, 4) == 0)
E 36
				line[0] = '\0';
E 21
			argv++;
			argc--;
			break;
E 40
I 40
D 52
	rval = 0;
	/* XXX: Open should allow flock'ing the file; see 4.4BSD. */
E 52
I 52
	/* Wait until we can get a lock on the file. */
E 52
	if (flock(mbfd, LOCK_EX)) {
D 46
		error(NOTFATAL, "%s: %s.", path, strerror(errno));
E 46
I 46
D 52
		err(NOTFATAL, "%s: %s", path, strerror(errno));
E 46
		rval = 1;
		goto bad;
E 52
I 52
		e_to_sys(errno);
		warn("%s: %s", path, strerror(errno));
I 61
D 72
		unlockmbox();
E 72
E 61
		goto err1;
E 52
	}
E 40

I 52
	/* Get the starting offset of the new message for biff. */
E 52
D 40
		case 'h':
D 24
			if (argc <= 0) {
E 24
I 24
			if (argc <= 1)
E 24
				usage();
D 24
				done();
			}
E 24
			hseqno = atoi(argv[1]);
			argv++;
			argc--;
			break;

D 9
# ifdef DELIVERMAIL
E 9
		case 'd':
			break;
D 9
# endif DELIVERMAIL
E 9
		
		default:
			usage();
D 24
			done();
E 24
		}
E 40
I 40
D 48
	curoff = lseek(mbfd, 0L, SEEK_END);
	(void)sprintf(biffmsg, "%s@%ld\n", name, curoff);
	if (lseek(fd, 0L, SEEK_SET) == (off_t)-1) {
E 48
I 48
	curoff = lseek(mbfd, (off_t)0, SEEK_END);
D 49
	(void)sprintf(biffmsg, "%s@%qd\n", name, curoff);
E 49
I 49
D 63
	(void)snprintf(biffmsg, sizeof(biffmsg), "%s@%qd\n", name, curoff);
E 63
I 63
	(void)snprintf(biffmsg, sizeof(biffmsg),
		sizeof curoff > sizeof(long) ? "%s@%qd\n" : "%s@%ld\n", 
		name, curoff);
E 63
I 52

	/* Copy the message into the file. */
E 52
E 49
	if (lseek(fd, (off_t)0, SEEK_SET) == (off_t)-1) {
E 48
D 46
		error(FATAL, "temporary file: %s.", strerror(errno));
E 46
I 46
D 52
		err(FATAL, "temporary file: %s", strerror(errno));
E 46
		rval = 1;
		goto bad;
E 52
I 52
		e_to_sys(errno);
		warn("temporary file: %s", strerror(errno));
		goto err1;
E 52
E 40
	}
I 72
D 73
#if HAS_SAVED_IDS
	if (seteuid(pw->pw_uid) < 0) {
		e_to_sys(errno);
		warn("seteuid(%d): %s", pw->pw_uid, strerror(errno));
		goto err1;
	}
#else
E 73
	if (setreuid(0, pw->pw_uid) < 0) {
		e_to_sys(errno);
		warn("setreuid(0, %d): %s (r=%d, e=%d)",
		     pw->pw_uid, strerror(errno), getuid(), geteuid());
		goto err1;
	}
D 73
#endif
E 73
#ifdef DEBUG
	printf("new euid = %d\n", geteuid());
#endif
E 72
D 24
	if (argc <= 1) {
E 24
I 24
D 40
	if (argc <= 1)
E 24
		usage();
D 24
		done();
	}
E 24
D 28
	if (gaver == 0)
		strcpy(truename, my_name);
E 28
I 28
	if (truename == 0)
		truename = my_name;
E 28
D 24
	/*
	if (argc > 4 && strcmp(argv[1], "-r") == 0) {
		strcpy(truename, argv[2]);
		argc -= 2;
		argv += 2;
		fgets(line, LSIZE, stdin);
D 21
		if (strcmpn("From", line, 4) == 0)
E 21
I 21
		if (strncmp("From", line, 4) == 0)
E 21
			line[0] = '\0';
	} else
		strcpy(truename, my_name);
	*/
E 24
	time(&iop);
	fprintf(tmpf, "%s%s %s", from, truename, ctime(&iop));
	iop = ftell(tmpf);
D 24
	flgf = 1;
	for (first = 1;; first = 0) {
		if (first && line[0] == '\0' && fgets(line, LSIZE, stdin) == NULL)
E 24
I 24
	flgf = first = 1;
	for (;;) {
		if (first) {
			first = 0;
			if (*line == '\0' && fgets(line, LSIZE, stdin) == NULL)
				break;
		} else {
			if (fgets(line, LSIZE, stdin) == NULL)
				break;
		}
		if (*line == '.' && line[1] == '\n' && isatty(fileno(stdin)))
E 24
			break;
D 24
		if (!first && fgets(line, LSIZE, stdin) == NULL)
			break;
		if (line[0] == '.' && line[1] == '\n' && isatty(fileno(stdin)))
			break;
E 24
		if (isfrom(line))
D 24
			fputs(">", tmpf);
E 24
I 24
			putc('>', tmpf);
E 24
		fputs(line, tmpf);
		flgf = 0;
	}
D 24
	fputs("\n", tmpf);
E 24
I 24
	putc('\n', tmpf);
E 24
	nlet = 1;
	let[0].adr = 0;
	let[1].adr = ftell(tmpf);
D 24
	fclose(tmpf);
E 24
	if (flgf)
		return;
D 24
	tmpf = fopen(lettmp, "r");
	if (tmpf == NULL) {
		fprintf(stderr, "mail: cannot reopen %s for reading\n", lettmp);
		return;
	}
D 8
	while (--argc > 0)
		if (!send(0, *++argv, truename))
E 8
I 8
	while (--argc > 0) {
E 24
I 24
	while (--argc > 0)
E 24
		if (!sendmail(0, *++argv, truename))
E 8
			error++;
I 8
D 24
	}
E 24
E 8
D 14
	if (error) {
E 14
I 14
	if (error && safefile(dead)) {
E 14
		setuid(getuid());
		malf = fopen(dead, "w");
		if (malf == NULL) {
D 24
			fprintf(stdout, "mail: cannot open %s\n", dead);
E 24
I 24
			printf("mail: cannot open %s\n", dead);
E 24
			fclose(tmpf);
			return;
		}
		copylet(0, malf, ZAP);
		fclose(malf);
D 24
		fprintf(stdout, "Mail saved in %s\n", dead);
E 24
I 24
		printf("Mail saved in %s\n", dead);
E 24
	}
	fclose(tmpf);
}
E 40
D 52

E 52
D 25
sendrmt(n, name, rcmd)
E 25
I 25
D 40
sendrmt(n, name)
E 25
char *name;
D 25
char *rcmd;
E 25
{
	FILE *rmf, *popen();
	register char *p;
	char rsys[64], cmd[64];
D 25
	register local, pid;
E 25
I 25
	register pid;
E 25
	int sts;

D 25
	local = 0;
	if (index(name, '^')) {
E 25
I 25
#ifdef notdef
	if (any('^', name)) {
E 25
		while (p = index(name, '^'))
			*p = '!';
		if (strncmp(name, "researc", 7)) {
			strcpy(rsys, "research");
			if (*name != '!')
				--name;
			goto skip;
		}
E 40
I 40
	while ((nr = read(fd, buf, sizeof(buf))) > 0)
D 70
		for (off = 0; off < nr; nr -= nw, off += nw)
			if ((nw = write(mbfd, buf + off, nr)) < 0) {
E 70
I 70
		for (off = 0; off < nr; off += nw)
			if ((nw = write(mbfd, buf + off, nr - off)) < 0) {
E 70
D 46
				error(NOTFATAL,
				    "%s: %s.", path, strerror(errno));
E 46
I 46
D 52
				err(NOTFATAL, "%s: %s", path, strerror(errno));
E 46
				goto trunc;
E 52
I 52
				e_to_sys(errno);
				warn("%s: %s", path, strerror(errno));
D 72
				goto err2;;
E 72
I 72
				goto err3;
E 72
E 52
			}
	if (nr < 0) {
D 46
		error(FATAL, "temporary file: %s.", strerror(errno));
E 46
I 46
D 52
		err(FATAL, "temporary file: %s", strerror(errno));
E 46
trunc:		(void)ftruncate(mbfd, curoff);
		rval = 1;
E 52
I 52
		e_to_sys(errno);
		warn("temporary file: %s", strerror(errno));
D 72
		goto err2;;
E 72
I 72
		goto err3;
E 72
E 52
E 40
	}
D 25
	if (*name=='!')
		name++;
	for(p=rsys; *name!='!'; *p++ = *name++)
		if (*name=='\0') {
			local++;
			break;
		}
E 25
I 25
D 40
#endif
	for (p=rsys; *name!='!'; *p++ = *name++)
		if (*name=='\0')
			return(0);	/* local address, no '!' */
E 25
	*p = '\0';
D 25
	if ((!local && *name=='\0') || (local && *rsys=='\0')) {
E 25
I 25
	if (name[1]=='\0') {
E 25
D 24
		fprintf(stdout, "null name\n");
E 24
I 24
		printf("null name\n");
E 24
		return(0);
	}
skip:
	if ((pid = fork()) == -1) {
		fprintf(stderr, "mail: can't create proc for remote\n");
		return(0);
	}
	if (pid) {
		while (wait(&sts) != pid) {
			if (wait(&sts)==-1)
				return(0);
		}
		return(!sts);
	}
	setuid(getuid());
D 25
	if (local)
		sprintf(cmd, "%s %s", rcmd, rsys);
	else {
		if (index(name+1, '!'))
			sprintf(cmd, "uux - %s!rmail \\(%s\\)", rsys, name+1);
		else
			sprintf(cmd, "uux - %s!rmail %s", rsys, name+1);
	}
E 25
I 25
	if (any('!', name+1))
D 32
		sprintf(cmd, "uux - %s!rmail \\(%s\\)", rsys, name+1);
E 32
I 32
		(void)sprintf(cmd, "uux - %s!rmail \\(%s\\)", rsys, name+1);
E 32
	else
D 32
		sprintf(cmd, "uux - %s!rmail %s", rsys, name+1);
E 32
I 32
		(void)sprintf(cmd, "uux - %s!rmail %s", rsys, name+1);
E 32
E 25
	if ((rmf=popen(cmd, "w")) == NULL)
		exit(1);
D 25
	copylet(n, rmf, local ? !strcmp(rcmd, "/bin/mail") ? FORWARD : ORDINARY : REMOTE);
E 25
I 25
	copylet(n, rmf, REMOTE);
E 25
D 15
	pclose(rmf);
	exit(0);
E 15
I 15
	exit(pclose(rmf) != 0);
E 15
}
E 40

I 2
D 9
# ifndef DELIVERMAIL
E 2
/*
 * Send mail on the Berkeley network.
 * Sorry Bill, sendrmt() is so awful we just gave up.
 */

sendberkmail(n, name, fromaddr)
	char name[];
	char fromaddr[];
{
	char cmd[200];
	register FILE *cmdf;

	sprintf(cmd, "%s -h %d -f %s -t %s", RMAIL, hseqno, fromaddr, name);
	if ((cmdf = popen(cmd, "w")) == NULL) {
		perror(RMAIL);
		return(0);
	}
	copylet(n, cmdf, ORDINARY);
	pclose(cmdf);
	return(9);
}
I 2
# endif
E 2

E 9
D 40
usage()
{
E 40
I 40
D 52
	/*
	 * Set the owner and group.  Historically, binmail repeated this at
	 * each mail delivery.  We no longer do this, assuming that if the
	 * ownership or permissions were changed there was a reason for doing
	 * so.
	 */
bad:	if (created) 
		(void)fchown(mbfd, pw->pw_uid, pw->pw_gid);
E 52
I 52
	/* Flush to disk, don't wait for update. */
	if (fsync(mbfd)) {
		e_to_sys(errno);
		warn("%s: %s", path, strerror(errno));
I 72
err3:
D 73
#if !HAS_SAVED_IDS
E 73
		if (setreuid(0, 0) < 0) {
			e_to_sys(errno);
			warn("setreuid(0, 0): %s", strerror(errno));
		}
D 73
# ifdef DEBUG
E 73
I 73
#ifdef DEBUG
E 73
		printf("reset euid = %d\n", geteuid());
D 73
# endif
E 73
#endif
E 72
err2:		(void)ftruncate(mbfd, curoff);
err1:		(void)close(mbfd);
I 61
D 72
		unlockmbox();
E 72
I 72
err0:		unlockmbox();
E 72
E 61
		return;
	}
		
	/* Close and check -- NFS doesn't write until the close. */
	if (close(mbfd)) {
		e_to_sys(errno);
		warn("%s: %s", path, strerror(errno));
I 61
		unlockmbox();
E 61
		return;
	}
E 52
E 40

I 72
D 73
#if !HAS_SAVED_IDS
E 73
	if (setreuid(0, 0) < 0) {
		e_to_sys(errno);
		warn("setreuid(0, 0): %s", strerror(errno));
	}
D 73
# ifdef DEBUG
E 73
I 73
#ifdef DEBUG
E 73
	printf("reset euid = %d\n", geteuid());
D 73
# endif
E 73
#endif
E 72
I 61
	unlockmbox();
E 61
D 40
	fprintf(stderr, "Usage: mail [ -f ] people . . .\n");
I 22
	error = EX_USAGE;
I 24
	done();
E 40
I 40
D 42
	/* Implicit unlock. */
	(void)close(mbfd);
E 42
I 42
D 52
	(void)fsync(mbfd);		/* Don't wait for update. */
	(void)close(mbfd);		/* Implicit unlock. */
E 42

	if (!rval)
		notifybiff(biffmsg);
	return(rval);
E 52
I 52
	notifybiff(biffmsg);
I 61
}

/*
 * user.lock files are necessary for compatibility with other
 * systems, e.g., when the mail spool file is NFS exported.
 * Alas, mailbox locking is more than just a local matter.
 * EPA 11/94.
 */

D 70
char	lockname[50];
E 70
I 70
char	lockname[MAXPATHLEN];
E 70
int	locked = 0;

lockmbox(path)
	char *path;
{
D 65
	char locktmp[50];
E 65
	int statfailed = 0;

	if (locked)
		return;
	sprintf(lockname, "%s.lock", path);
D 65
	sprintf(locktmp, "%s/tmXXXXXX", _PATH_MAILDIR);
	mktemp(locktmp);
	unlink(locktmp);
E 65
	for (;; sleep(5)) {
		int fd;
		struct stat st;
		time_t now;

D 62
		fd = creat(locktmp, 0);
E 62
I 62
D 65
		fd = open(locktmp, O_WRONLY|O_EXCL|O_CREAT, 0);
E 62
		if (fd < 0)
			continue;
		close(fd);
		if (link(locktmp, lockname) >= 0) {
			unlink(locktmp);
E 65
I 65
		fd = open(lockname, O_WRONLY|O_EXCL|O_CREAT, 0);
		if (fd >= 0) {
E 65
			locked = 1;
I 65
			close(fd);
E 65
			return;
		}
D 65
		unlink(locktmp);
E 65
		if (stat(lockname, &st) < 0) {
			if (statfailed++ > 5)
				return;
			continue;
		}
		statfailed = 0;
		time(&now);
		if (now < st.st_ctime + 300)
			continue;
		unlink(lockname);
	}
}

unlockmbox()
{
	if (!locked)
		return;
	unlink(lockname);
	locked = 0;
E 61
E 52
E 40
E 24
E 22
}

I 46
void
E 46
D 8
send(n, name, fromaddr)
E 8
I 8
D 40
#include <sys/socket.h>
D 11
#include <net/in.h>
E 11
I 11
#include <netinet/in.h>
E 11
D 10
#include <wellknown.h>
E 10
D 13
struct sockaddr_in biffaddr = { AF_INET, IPPORT_BIFFUDP };
char *localhost = "localhost";
E 13
I 13
#include <netdb.h>
D 24
struct sockaddr_in biffaddr;
E 24
E 13

E 40
I 24
notifybiff(msg)
	char *msg;
{
	static struct sockaddr_in addr;
	static int f = -1;
I 40
	struct hostent *hp;
	struct servent *sp;
	int len;
E 40

D 40
	if (addr.sin_family == 0) {
		struct hostent *hp = gethostbyname("localhost");
		struct servent *sp = getservbyname("biff", "udp");

		if (hp && sp) {
			addr.sin_family = hp->h_addrtype;
			bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
			addr.sin_port = sp->s_port;
E 40
I 40
	if (!addr.sin_family) {
		/* Be silent if biff service not available. */
		if (!(sp = getservbyname("biff", "udp")))
			return;
		if (!(hp = gethostbyname("localhost"))) {
D 46
			error(NOTFATAL, "localhost: %s.", strerror(errno));
E 46
I 46
D 52
			err(NOTFATAL, "localhost: %s", strerror(errno));
E 52
I 52
			warn("localhost: %s", strerror(errno));
E 52
E 46
			return;
E 40
		}
I 40
		addr.sin_family = hp->h_addrtype;
D 53
		bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
E 53
I 53
D 60
		memmove(&addr.sin_addr, hp->h_addr, hp->h_length);
E 60
I 60
		memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);
E 60
E 53
		addr.sin_port = sp->s_port;
E 40
	}
D 40
	if (addr.sin_family) {
		if (f < 0)
			f = socket(AF_INET, SOCK_DGRAM, 0);
D 30
		sendto(f, msg, strlen(msg)+1, 0, &addr, sizeof (addr));
E 30
I 30
		if (f >= 0)
			sendto(f, msg, strlen(msg)+1, 0, &addr, sizeof (addr));
E 40
I 40
	if (f < 0 && (f = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
D 46
		error(NOTFATAL, "socket: %s.", strerror(errno));
E 46
I 46
D 52
		err(NOTFATAL, "socket: %s", strerror(errno));
E 52
I 52
		warn("socket: %s", strerror(errno));
E 52
E 46
		return;
E 40
E 30
	}
I 40
	len = strlen(msg) + 1;
D 44
	if (sendto(f, msg, len, 0, &addr, sizeof(addr)) != len)
E 44
I 44
	if (sendto(f, msg, len, 0, (struct sockaddr *)&addr, sizeof(addr))
	    != len)
E 44
D 46
		error(NOTFATAL, "sendto biff: %s.", strerror(errno));
E 46
I 46
D 52
		err(NOTFATAL, "sendto biff: %s", strerror(errno));
E 52
I 52
		warn("sendto biff: %s", strerror(errno));
E 52
E 46
E 40
}

I 46
void
E 46
E 24
D 40
sendmail(n, name, fromaddr)
E 8
D 24
int n;
char *name;
char *fromaddr;
E 24
I 24
	int n;
	char *name, *fromaddr;
E 40
I 40
usage()
E 40
E 24
{
D 24
	char file[100];
	register char *p;
	register mask;
	struct passwd *pw, *getpwnam();
E 24
I 24
D 40
	char file[256];
	int mask, fd;
	struct passwd *pw;
#ifdef notdef
E 24
	struct stat statb;
I 24
#endif
E 24
I 4
	char buf[128];
D 24
	int f;
I 13
	struct hostent *hp = NULL;
	struct servent *sp = NULL;
E 24
E 13
E 4

I 2
D 9
# ifndef DELIVERMAIL
E 2
	stripfx(LOCNAM1, &name);
	stripfx(LOCNAM2, &name);
	stripfx(LOCNAM3, &name);
	stripfx(LOCNAM4, &name);
	if(*name == ':')name++;		/* skip colon in to-name */
D 2
	for(p=name; *p!=':' &&*p!='\0'; p++);
E 2
I 2
	for(p=name; *p!=':' && *p!='!' && *p!='^' &&*p!='\0'; p++);
E 2
	/* if(*p == ':') return(sendrmt(n, name, RMAIL)); */
	if (*p == ':')
		return(sendberkmail(n, name, fromaddr));
D 2
	else if (strcmp(name, "msgs") == 0) return(sendrmt(n, "-s", "/usr/ucb/msgs"));
E 2
I 2
	else if (*p=='\0' && strcmp(name, "msgs") == 0)
		return(sendrmt(n, "-s", "/usr/ucb/msgs"));
# endif
E 9
E 2
D 24
	for(p=name; *p!='!'&&*p!='^' &&*p!='\0'; p++)
		;
	if (*p == '!'|| *p=='^')
		return(sendrmt(n, name, 0));
E 24
I 24
D 25
	if (any(name, "!^"))
		return (sendrmt(n, name, 0));
E 25
I 25
	if (*name=='!')
		name++;
	if (any('!', name))
		return (sendrmt(n, name));
E 25
E 24
	if ((pw = getpwnam(name)) == NULL) {
D 24
		fprintf(stdout, "mail: can't send to %s\n", name);
E 24
I 24
		printf("mail: can't send to %s\n", name);
E 24
		return(0);
	}
	cat(file, maildir, name);
I 24
#ifdef notdef
E 24
	if (stat(file, &statb) >= 0 && (statb.st_mode & S_IFMT) == S_IFDIR) {
		strcat(file, "/");
		strcat(file, name);
	}
D 24
	mask = umask(MAILMODE);
E 24
I 24
#endif
E 24
I 5
D 6
	if (stat(file, &stat) >= 0 && stat.st_nlink != 1) {
E 6
I 6
D 14
	if (stat(file, &statb) >= 0 && statb.st_nlink != 1) {
E 6
		fprintf(stdout, "mail: %s's mail file has more than one link\n", name);
E 14
I 14
	if (!safefile(file))
E 14
		return(0);
I 16
D 24
	lock(file);
E 16
D 14
	}
E 14
E 5
	malf = fopen(file, "a");
I 5
D 8
	chown(file, pw->pw_uid, pw->pw_gid);
E 8
E 5
	umask(mask);
	if (malf == NULL) {
I 16
		unlock();
E 16
		fprintf(stdout, "mail: cannot append to %s\n", file);
E 24
I 24
	fd = open(file, O_WRONLY | O_CREAT, MAILMODE);
	if (fd >= 0) {
		flock(fd, LOCK_EX);
		malf = fdopen(fd, "a");
	}
	if (fd < 0 || malf == NULL) {
		close(fd);
		printf("mail: %s: cannot append\n", file);
E 24
		return(0);
	}
D 16
	lock(file);
E 16
I 8
D 24
	chown(file, pw->pw_uid, pw->pw_gid);
E 8
D 5
	chown(file, pw->pw_uid, pw->pw_gid);
E 5
I 4
	{
D 8
		f = open("/dev/mail", 1);
E 8
I 8
D 11
		f = socket(SOCK_DGRAM, 0, 0, 0);
E 11
I 11
D 13
		f = socket(0, SOCK_DGRAM, 0, 0);
E 11
E 8
		sprintf(buf, "%s@%d\n", name, ftell(malf)); 
E 13
I 13
		hp = gethostbyname("localhost");
		sp = getservbyname("biff", "udp");
		if (hp && sp) {
			f = socket(AF_INET, SOCK_DGRAM, 0, 0);
			sprintf(buf, "%s@%d\n", name, ftell(malf)); 
		}
E 13
	}
E 24
I 24
	fchown(fd, pw->pw_uid, pw->pw_gid);
D 32
	sprintf(buf, "%s@%d\n", name, ftell(malf)); 
E 32
I 32
D 34
	(void)sprintf(buf, "%s@%d\n", name, ftell(malf));
E 34
I 34
	(void)sprintf(buf, "%s@%ld\n", name, ftell(malf));
E 34
E 32
E 24
E 4
	copylet(n, malf, ORDINARY);
I 8
	fclose(malf);
E 8
I 4
D 13
	if (f >= 0) {
D 8
		write(f, buf, strlen(buf)+1);
E 8
I 8
		biffaddr.sin_addr.s_addr = rhost(&localhost);
I 10
#if vax
		biffaddr.sin_port =
		    ((biffaddr.sin_port<<8)&0xff00)|((biffaddr.sin_port>>8)&0xff);
#endif
E 13
I 13
D 24
	if (hp && sp) {
		biffaddr.sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, &biffaddr.sin_addr, hp->h_length);
		biffaddr.sin_port = sp->s_port;
E 13
E 10
D 11
		send(f, &biffaddr, buf, strlen(buf)+1);
E 11
I 11
		sendto(f, buf, strlen(buf)+1, 0, &biffaddr, sizeof (biffaddr));
E 11
E 8
		close(f);
	}
E 4
D 8
	fclose(malf);
E 8
	unlock();
E 24
I 24
	notifybiff(buf);
E 24
	return(1);
E 40
I 40
D 46
	error(FATAL, "usage: mail.local [-f from] user ...");
E 46
I 46
D 52
	err(FATAL, "usage: mail.local [-f from] user ...");
E 52
I 52
	eval = EX_USAGE;
	err("usage: mail.local [-f from] user ...");
E 52
E 46
E 40
}

I 52
D 55
void
E 55
E 52
D 24
delete(i)
E 24
I 24
D 40
delex(i)
E 40
I 40
D 46
/* VARARGS */
D 43
error(va_alist)
va_dcl
E 40
E 24
{
D 24
	setsig(i, delete);
	fprintf(stderr, "\n");
	if(delflg)
E 24
I 24
D 28
	setsig(i, delex);
E 28
I 28
D 40
	if (i != SIGINT) {
		setsig(i, SIG_DFL);
D 35
		sigsetmask(sigblock(0) &~ sigmask(i));
E 35
I 35
		sigsetmask(sigblock(0L) &~ sigmask(i));
E 35
	}
E 28
	putc('\n', stderr);
	if (delflg)
E 24
		longjmp(sjbuf, 1);
I 28
	if (error == 0)
		error = i;
E 28
	done();
}
E 40
I 40
	va_list ap;
E 43
I 43
error(isfatal, fmt)
E 46
I 46
#if __STDC__
I 55
D 56
__dead void
E 56
I 56
void
E 56
E 55
D 52
#include <stdarg.h>
E 52
I 52
err(const char *fmt, ...)
E 52
#else
I 55
void
E 55
D 52
#include <varargs.h>
E 52
I 52
err(fmt, va_alist)
	const char *fmt;
	va_dcl
E 52
#endif
I 52
{
	va_list ap;
E 52

I 52
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	vwarn(fmt, ap);
	va_end(ap);

	exit(eval);
}

E 52
void
#if __STDC__
D 52
err(int isfatal, const char *fmt, ...)
E 52
I 52
warn(const char *fmt, ...)
E 52
#else
D 47
err(isfatal, fmt)
E 47
I 47
D 52
err(isfatal, fmt, va_alist)
E 47
E 46
E 43
	int isfatal;
	char *fmt;
E 52
I 52
warn(fmt, va_alist)
	const char *fmt;
E 52
I 46
	va_dcl
#endif
E 46
I 43
{
	va_list ap;
I 52

E 52
E 43
E 40
D 46

E 46
I 46
#if __STDC__
E 46
D 24
/*
 * Lock the specified mail file by setting the file mailfile.lock.
 * We must, of course, be careful to unlink the lock file by a call
 * to unlock before we stop.  The algorithm used here is to see if
 * the lock exists, and if it does, to check its modify time.  If it
 * is older than 30 seconds, we assume error and set our own file.
 * Otherwise, we wait for 5 seconds and try again.
 */

char	*maillock	= ".lock";		/* Lock suffix for mailname */
char	*lockname	= "/usr/spool/mail/tmXXXXXX";
char	locktmp[30];				/* Usable lock temporary */
char	curlock[50];				/* Last used name of lock */
int	locked;					/* To note that we locked it */

lock(file)
char *file;
{
	register int f;
	struct stat sbuf;
	long curtime;
	int statfailed;

	if (locked || flgf)
		return(0);
	strcpy(curlock, file);
	strcat(curlock, maillock);
	strcpy(locktmp, lockname);
	mktemp(locktmp);
	unlink(locktmp);
	statfailed = 0;
	for (;;) {
		f = lock1(locktmp, curlock);
		if (f == 0) {
			locked = 1;
			return(0);
		}
		if (stat(curlock, &sbuf) < 0) {
			if (statfailed++ > 5)
				return(-1);
			sleep(5);
			continue;
		}
		statfailed = 0;
		time(&curtime);
		if (curtime < sbuf.st_ctime + 30) {
			sleep(5);
			continue;
		}
		unlink(curlock);
	}
}

/*
 * Remove the mail lock, and note that we no longer
 * have it locked.
 */

unlock()
{

	unlink(curlock);
	locked = 0;
}

/*
 * Attempt to set the lock by creating the temporary file,
 * then doing a link/unlink.  If it fails, return -1 else 0
 */

lock1(tempfile, name)
	char tempfile[], name[];
{
	register int fd;

	fd = creat(tempfile, 0);
	if (fd < 0)
		return(-1);
	close(fd);
	if (link(tempfile, name) < 0) {
		unlink(tempfile);
		return(-1);
	}
	unlink(tempfile);
	return(0);
}

E 24
D 40
done()
{
D 24
	if(locked)
		unlock();
E 24
I 24

E 24
	unlink(lettmp);
D 24
	unlink(locktmp);
E 24
	exit(error);
}

cat(to, from1, from2)
D 24
char *to, *from1, *from2;
E 24
I 24
	char *to, *from1, *from2;
E 24
{
D 24
	int i, j;
E 24
I 24
	register char *cp, *dp;
E 24

D 24
	j = 0;
	for (i=0; from1[i]; i++)
		to[j++] = from1[i];
	for (i=0; from2[i]; i++)
		to[j++] = from2[i];
	to[j] = 0;
E 24
I 24
	cp = to;
	for (dp = from1; *cp = *dp++; cp++)
		;
	for (dp = from2; *cp++ = *dp++; )
		;
E 24
}

D 24
char *getarg(s, p)	/* copy p... into s, update p */
register char *s, *p;
E 24
I 24
/* copy p... into s, update p */
char *
getarg(s, p)
	register char *s, *p;
E 24
{
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == '\n' || *p == '\0')
		return(NULL);
	while (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\0')
		*s++ = *p++;
	*s = '\0';
	return(p);
I 14
}

safefile(f)
	char *f;
{
	struct stat statb;

	if (lstat(f, &statb) < 0)
		return (1);
	if (statb.st_nlink != 1 || (statb.st_mode & S_IFMT) == S_IFLNK) {
D 24
		fprintf(stderr, "mail: %s has more than one link or is a symbolic link\n", f);
E 24
I 24
		fprintf(stderr,
		    "mail: %s has more than one link or is a symbolic link\n",
		    f);
E 24
		return (0);
	}
	return (1);
I 24
}

panic(msg, a1, a2, a3)
	char *msg;
{

	fprintf(stderr, "mail: ");
	fprintf(stderr, msg, a1, a2, a3);
	fprintf(stderr, "\n");
	done();
E 40
I 40
D 43
	va_start(ap);
	isfatal = va_arg(ap, int);
	fmt = va_arg(ap, char *);
E 43
I 43
	va_start(ap, fmt);
I 46
#else
	va_start(ap);
#endif
I 52
	vwarn(fmt, ap);
	va_end(ap);
}

void
vwarn(fmt, ap)
	const char *fmt;
	_BSD_VA_LIST_ ap;
{
E 52
I 50
D 51
#ifndef LOG_PERROR
E 51
I 51
	/*
D 52
	 * Don't use LOG_PERROR as an openlog() flag to do this, it's
	 * not portable enough.
E 52
I 52
	 * Log the message to stderr.
	 *
	 * Don't use LOG_PERROR as an openlog() flag to do this,
	 * it's not portable enough.
E 52
	 */
I 52
	if (eval != EX_USAGE)
		(void)fprintf(stderr, "mail.local: ");
E 52
E 51
	(void)vfprintf(stderr, fmt, ap);
D 51
#endif
E 51
I 51
	(void)fprintf(stderr, "\n");
I 52

I 60
D 74
#ifndef ultrix
E 74
I 74
#if !defined(ultrix) && !defined(__osf__)
E 74
E 60
	/* Log the message to syslog. */
E 52
E 51
E 50
E 46
E 43
	vsyslog(LOG_ERR, fmt, ap);
I 60
#else
	{
		char fmtbuf[10240];

		(void) sprintf(fmtbuf, fmt, ap);
		syslog(LOG_ERR, "%s", fmtbuf);
	}
#endif
E 60
D 52
	va_end(ap);
	if (isfatal)
		exit(1);
E 52
I 52
}

/*
 * e_to_sys --
 *	Guess which errno's are temporary.  Gag me.
 */
void
e_to_sys(num)
	int num;
{
	/* Temporary failures override hard errors. */
	if (eval == EX_TEMPFAIL)
		return;

	switch(num) {		/* Hopefully temporary errors. */
#ifdef EAGAIN
	case EAGAIN:		/* Resource temporarily unavailable */
#endif
#ifdef EDQUOT
	case EDQUOT:		/* Disc quota exceeded */
#endif
#ifdef EBUSY
	case EBUSY:		/* Device busy */
#endif
#ifdef EPROCLIM
	case EPROCLIM:		/* Too many processes */
#endif
#ifdef EUSERS
	case EUSERS:		/* Too many users */
#endif
#ifdef ECONNABORTED
	case ECONNABORTED:	/* Software caused connection abort */
#endif
#ifdef ECONNREFUSED
	case ECONNREFUSED:	/* Connection refused */
#endif
#ifdef ECONNRESET
	case ECONNRESET:	/* Connection reset by peer */
#endif
#ifdef EDEADLK
	case EDEADLK:		/* Resource deadlock avoided */
#endif
#ifdef EFBIG
	case EFBIG:		/* File too large */
#endif
#ifdef EHOSTDOWN
	case EHOSTDOWN:		/* Host is down */
#endif
#ifdef EHOSTUNREACH
	case EHOSTUNREACH:	/* No route to host */
#endif
#ifdef EMFILE
	case EMFILE:		/* Too many open files */
#endif
#ifdef ENETDOWN
	case ENETDOWN:		/* Network is down */
#endif
#ifdef ENETRESET
	case ENETRESET:		/* Network dropped connection on reset */
#endif
#ifdef ENETUNREACH
	case ENETUNREACH:	/* Network is unreachable */
#endif
#ifdef ENFILE
	case ENFILE:		/* Too many open files in system */
#endif
#ifdef ENOBUFS
	case ENOBUFS:		/* No buffer space available */
#endif
#ifdef ENOMEM
	case ENOMEM:		/* Cannot allocate memory */
#endif
#ifdef ENOSPC
	case ENOSPC:		/* No space left on device */
#endif
#ifdef EROFS
	case EROFS:		/* Read-only file system */
#endif
#ifdef ESTALE
	case ESTALE:		/* Stale NFS file handle */
#endif
#ifdef ETIMEDOUT
	case ETIMEDOUT:		/* Connection timed out */
#endif
D 60
#if defined(EWOULDBLOCK) && (EWOULDBLOCK != EAGAIN)
E 60
I 60
#if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN && EWOULDBLOCK != EDEADLK
E 60
	case EWOULDBLOCK:	/* Operation would block. */
#endif
		eval = EX_TEMPFAIL;
		break;
	default:
		eval = EX_UNAVAILABLE;
		break;
	}
E 52
E 40
E 24
E 14
}
I 60

#ifndef BSD4_4

I 74
# ifndef __osf__
E 74
char *
strerror(eno)
	int eno;
{
	extern int sys_nerr;
	extern char *sys_errlist[];
	static char ebuf[60];

	if (eno >= 0 && eno <= sys_nerr)
		return sys_errlist[eno];
	(void) sprintf(ebuf, "Error %d", eno);
	return ebuf;
}
I 74
# endif
E 74

D 74
#if __STDC__
E 74
I 74
# if __STDC__
E 74
snprintf(char *buf, int bufsiz, const char *fmt, ...)
D 74
#else
E 74
I 74
# else
E 74
snprintf(buf, bufsiz, fmt, va_alist)
	char *buf;
	int bufsiz;
	const char *fmt;
	va_dcl
D 74
#endif
E 74
I 74
# endif
E 74
{
	va_list ap;

D 74
#if __STDC__
E 74
I 74
# if __STDC__
E 74
	va_start(ap, fmt);
D 74
#else
E 74
I 74
# else
E 74
	va_start(ap);
D 74
#endif
E 74
I 74
# endif
E 74
	vsprintf(buf, fmt, ap);
	va_end(ap);
}

#endif

#ifdef ultrix

D 67
int
mkstemp(template)
	char *template;
E 67
I 67
/*
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)mktemp.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

static int _gettemp();

mkstemp(path)
	char *path;
E 67
{
	int fd;

D 67
	return open(mktemp(template), O_RDWR|O_CREAT|O_EXCL, 0600);
E 67
I 67
	return (_gettemp(path, &fd) ? fd : -1);
}

/*
char *
mktemp(path)
	char *path;
{
	return(_gettemp(path, (int *)NULL) ? path : (char *)NULL);
}
*/

static
_gettemp(path, doopen)
	char *path;
	register int *doopen;
{
	extern int errno;
	register char *start, *trv;
	struct stat sbuf;
	u_int pid;

	pid = getpid();
	for (trv = path; *trv; ++trv);		/* extra X's get set to 0's */
	while (*--trv == 'X') {
		*trv = (pid % 10) + '0';
		pid /= 10;
	}

	/*
	 * check the target directory; if you have six X's and it
	 * doesn't exist this runs for a *very* long time.
	 */
	for (start = trv + 1;; --trv) {
		if (trv <= path)
			break;
		if (*trv == '/') {
			*trv = '\0';
			if (stat(path, &sbuf))
				return(0);
			if (!S_ISDIR(sbuf.st_mode)) {
				errno = ENOTDIR;
				return(0);
			}
			*trv = '/';
			break;
		}
	}

	for (;;) {
		if (doopen) {
			if ((*doopen =
			    open(path, O_CREAT|O_EXCL|O_RDWR, 0600)) >= 0)
				return(1);
			if (errno != EEXIST)
				return(0);
		}
		else if (stat(path, &sbuf))
			return(errno == ENOENT ? 1 : 0);

		/* tricky little algorithm for backward compatibility */
		for (trv = start;;) {
			if (!*trv)
				return(0);
			if (*trv == 'z')
				*trv++ = 'a';
			else {
				if (isdigit(*trv))
					*trv = 'a';
				else
					++*trv;
				break;
			}
		}
	}
	/*NOTREACHED*/
E 67
}

#endif
E 60
I 2
D 9
# ifndef DELIVERMAIL
E 2
/*
	stripfx(prefix string, pointer to string)

	takes a ptr to string and compares it to prefix string.
	may be called multiple times
*/
stripfx(pfx, name)
	char *pfx;
	char **name;
{
	register char *cp = *name;

	while (*pfx && (*cp == *pfx || *cp == toupper(*pfx)))
		cp++, pfx++;
	if (*cp != ':' || *pfx != 0)
		return;
	*name = cp;
}
I 2
# endif
E 9
E 2
E 1
