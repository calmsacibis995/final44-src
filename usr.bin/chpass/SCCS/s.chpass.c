h01830
s 00002/00002/00164
d D 8.4 94/04/02 10:06:11 pendry 21 20
c add 1994 copyright
e
s 00001/00000/00165
d D 8.3 94/04/02 09:09:03 pendry 20 19
c new pw_copy.h file for passwd
e
s 00025/00019/00140
d D 8.2 94/04/02 07:56:58 pendry 19 18
c prettyness police
e
s 00005/00005/00154
d D 8.1 93/06/06 14:26:59 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00021/00130
d D 5.17 91/03/03 16:07:46 bostic 17 16
c get the temporary file and fd handling right.
e
s 00056/00395/00095
d D 5.16 91/02/12 22:37:51 bostic 16 15
c rework the password subsystem
e
s 00015/00024/00475
d D 5.15 90/06/29 00:17:56 marc 15 14
c new interface to strsep
e
s 00002/00000/00497
d D 5.14 90/04/04 12:09:53 bostic 14 13
c better error messages when user's editor doesn't exist
e
s 00015/00004/00482
d D 5.13 89/06/01 18:37:50 bostic 13 12
c handle user inserting new (restricted) fields into the file they edit
e
s 00025/00014/00461
d D 5.12 89/06/01 18:20:29 bostic 12 11
c add -s flag to allow command line change of shell
e
s 00003/00002/00472
d D 5.11 89/05/11 09:42:05 bostic 11 10
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00473
d D 5.10 89/03/26 18:24:57 bostic 10 9
c setgid before setuid; bug report 4.3BSD/bin/226
e
s 00001/00001/00473
d D 5.9 89/03/16 22:29:27 bostic 9 8
c use passwd.{pag,dir}
e
s 00069/00031/00405
d D 5.8 89/03/16 21:58:15 bostic 8 7
c allow re-editing of file if reject entries
e
s 00132/00072/00304
d D 5.7 89/03/12 11:39:30 bostic 7 6
c add -a option, minor cleanups
e
s 00004/00003/00372
d D 5.6 89/03/11 17:07:29 bostic 6 5
c allow root to edit encrypted passwords
e
s 00007/00009/00368
d D 5.5 89/03/09 15:28:24 bostic 5 4
c make empty fields work, get rid of pw_class keywords
e
s 00004/00002/00373
d D 5.4 89/03/08 08:23:33 bostic 4 3
c allow empty gecos fields
e
s 00007/00000/00368
d D 5.3 89/03/06 12:14:30 bostic 3 2
c don't run the editor setuid; more secure and fixes vi bug
e
s 00002/00002/00366
d D 5.2 89/02/23 21:42:01 bostic 2 1
c fix gecos field ordering to be backward compatible
e
s 00368/00000/00000
d D 5.1 89/02/22 17:23:47 bostic 1 0
c date and time created 89/02/22 17:23:47 by bostic
e
u
U
t
T
I 1
D 15
/*
E 15
I 15
/*-
E 15
D 18
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
D 21
 * Copyright (c) 1988, 1993
E 21
I 21
 * Copyright (c) 1988, 1993, 1994
E 21
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 15
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
 */

#ifndef lint
D 18
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 18
I 18
static char copyright[] =
D 21
"%Z% Copyright (c) 1988, 1993\n\
E 21
I 21
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 21
	The Regents of the University of California.  All rights reserved.\n";
E 18
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
D 16
#include <sys/file.h>
E 16
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <sys/resource.h>
I 19

#include <ctype.h>
#include <err.h>
#include <errno.h>
E 19
I 16
#include <fcntl.h>
E 16
D 7
#include </usr/src/include/pwd.h>
E 7
I 7
#include <pwd.h>
E 7
D 19
#include <errno.h>
E 19
#include <stdio.h>
D 19
#include <ctype.h>
E 19
I 19
#include <stdlib.h>
E 19
D 11
#include <chpass.h>
E 11
D 15
#include <strings.h>
E 15
I 15
#include <string.h>
I 19
#include <unistd.h>

#include <pw_scan.h>
#include <pw_util.h>
I 20
#include "pw_copy.h"
E 20

E 19
E 15
I 11
#include "chpass.h"
#include "pathnames.h"
E 11

D 16
char e1[] = ": ";
char e2[] = ":,";

D 6
int p_login(), p_uid(), p_gid(), p_hdir(), p_shell(), p_change(), p_class();
D 5
int p_expire(), p_save();
E 5
I 5
int p_expire(), p_gecos();
E 6
I 6
int p_change(), p_class(), p_expire(), p_gecos(), p_gid(), p_hdir();
int p_login(), p_passwd(), p_shell(), p_uid();
E 6
E 5

struct entry list[] = {
	{ "Login",		p_login,  1,   5, e1,   },
I 6
	{ "Password",		p_passwd, 1,   8, e1,   },
E 6
	{ "Uid",		p_uid,    1,   3, e1,   },
	{ "Gid",		p_gid,    1,   3, e1,   },
	{ "Class",		p_class,  1,   5, e1,   },
	{ "Change",		p_change, 1,   6, NULL, },
	{ "Expire",		p_expire, 1,   6, NULL, },
D 7
#define	E_NAME		6
E 7
I 7
#define	E_NAME		7
E 7
D 5
	{ "Full Name",		p_save,   0,   9, e2,   },
E 5
I 5
	{ "Full Name",		p_gecos,  0,   9, e2,   },
E 5
D 7
#define	E_BPHONE	7
E 7
I 7
#define	E_BPHONE	8
E 7
D 5
	{ "Office Phone",	p_save,   0,  12, e2,   },
E 5
I 5
	{ "Office Phone",	p_gecos,  0,  12, e2,   },
E 5
D 7
#define	E_HPHONE	8
E 7
I 7
#define	E_HPHONE	9
E 7
D 5
	{ "Home Phone",		p_save,   0,  10, e2,   },
E 5
I 5
	{ "Home Phone",		p_gecos,  0,  10, e2,   },
E 5
D 7
#define	E_LOCATE	9
E 7
I 7
#define	E_LOCATE	10
E 7
D 5
	{ "Location",		p_save,   0,   8, e2,   },
E 5
I 5
	{ "Location",		p_gecos,  0,   8, e2,   },
E 5
	{ "Home directory",	p_hdir,   1,  14, e1,   },
I 13
#define	E_SHELL		12
E 13
	{ "Shell",		p_shell,  0,   5, e1,   },
	{ NULL, 0, },
};

E 16
I 16
char *progname = "chpass";
char *tempname;
E 16
D 7
uid_t euid, uid;
E 7
I 7
uid_t uid;
E 7

I 19
void	baduser __P((void));
void	usage __P((void));

int
E 19
main(argc, argv)
	int argc;
	char **argv;
{
D 7
	extern int errno;
E 7
I 7
D 16
	extern int errno, optind;
E 16
I 16
D 19
	extern int optind;
E 16
	extern char *optarg;
E 7
D 16
	register char *p;
D 7
	struct passwd *pw;
E 7
I 7
	struct passwd lpw, *pw;
E 7
	struct rlimit rlim;
	FILE *temp_fp;
D 7
	int fd;
	char *fend, *passwd, *temp, *tend, buf[1024];
E 7
I 7
	int aflag, ch, fd;
D 12
	char *fend, *passwd, *temp, *tend;
E 12
I 12
	char *fend, *newsh, *passwd, *temp, *tend;
E 12
E 7
	char from[MAXPATHLEN], to[MAXPATHLEN];
	char *getusershell();
E 16
I 16
	register enum { NEWSH, LOADENTRY, EDITENTRY } op;
	register struct passwd *pw;
	struct passwd lpw;
E 19
I 19
	enum { NEWSH, LOADENTRY, EDITENTRY } op;
	struct passwd *pw, lpw;
E 19
	int ch, pfd, tfd;
	char *arg;
E 16

D 7
	euid = geteuid();
E 7
D 16
	uid = getuid();
D 7
	switch(--argc) {
	case 0:
		if (!(pw = getpwuid(uid))) {
			fprintf(stderr, "chpass: unknown user: uid %u\n", uid);
			exit(1);
E 7
I 7
	aflag = 0;
D 12
	while ((ch = getopt(argc, argv, "a:")) != EOF)
E 12
I 12
	newsh = NULL;
E 16
I 16
	op = EDITENTRY;
E 16
	while ((ch = getopt(argc, argv, "a:s:")) != EOF)
E 12
		switch(ch) {
		case 'a':
D 12
			if (uid) {
				(void)fprintf(stderr,
				    "chpass: %s\n", strerror(EACCES));
				exit(1);
			}
E 12
I 12
D 16
			if (uid)
				baduser();
E 12
			loadpw(optarg, pw = &lpw);
			aflag = 1;
E 16
I 16
			op = LOADENTRY;
			arg = optarg;
E 16
			break;
I 12
		case 's':
D 16
			newsh = optarg;
			/* protect p_field -- it thinks NULL is /bin/sh */
			if (!*newsh)
				usage();
E 16
I 16
			op = NEWSH;
			arg = optarg;
E 16
			break;
E 12
		case '?':
		default:
			usage();
E 7
		}
D 7
		break;
	case 1:
		if (!(pw = getpwnam(argv[1]))) {
			fprintf(stderr, "chpass: unknown user %s.\n", argv[1]);
			exit(1);
E 7
I 7
	argc -= optind;
	argv += optind;

D 16
	if (!aflag)
E 16
I 16
	uid = getuid();

	if (op == EDITENTRY || op == NEWSH)
E 16
		switch(argc) {
		case 0:
D 19
			if (!(pw = getpwuid(uid))) {
				(void)fprintf(stderr,
				    "chpass: unknown user: uid %u\n", uid);
				exit(1);
			}
E 19
I 19
			if (!(pw = getpwuid(uid)))
				errx(1, "unknown user: uid %u", uid);
E 19
			break;
		case 1:
D 19
			if (!(pw = getpwnam(*argv))) {
				(void)fprintf(stderr,
				    "chpass: unknown user %s.\n", *argv);
				exit(1);
			}
E 19
I 19
			if (!(pw = getpwnam(*argv)))
				errx(1, "unknown user: %s", *argv);
E 19
D 12
			if (uid && uid != pw->pw_uid) {
				(void)fprintf(stderr,
				    "chpass: %s\n", strerror(EACCES));
				exit(1);
			}
E 12
I 12
			if (uid && uid != pw->pw_uid)
				baduser();
E 12
			break;
		default:
			usage();
E 7
		}
D 7
		if (uid && uid != pw->pw_uid) {
			fprintf(stderr, "chpass: %s\n", strerror(EACCES));
			exit(1);
		}
		break;
	default:
		fprintf(stderr, "usage: chpass [user]\n");
		exit(1);
	}
E 7

D 16
	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGTSTP, SIG_IGN);

	rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
	(void)setrlimit(RLIMIT_CPU, &rlim);
	(void)setrlimit(RLIMIT_FSIZE, &rlim);

	(void)umask(0);

	temp = _PATH_PTMP;
	if ((fd = open(temp, O_WRONLY|O_CREAT|O_EXCL, 0600)) < 0) {
		if (errno == EEXIST) {
D 7
			fprintf(stderr,
E 7
I 7
			(void)fprintf(stderr,
E 7
			    "chpass: password file busy -- try again later.\n");
			exit(1);
		}
D 7
		fprintf(stderr, "chpass: %s: %s", temp, strerror(errno));
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: %s: %s", temp, strerror(errno));
E 8
I 8
		(void)fprintf(stderr, "chpass: %s: %s; ",
		    temp, strerror(errno));
E 8
E 7
		goto bad;
E 16
I 16
	if (op == NEWSH) {
		/* protect p_shell -- it thinks NULL is /bin/sh */
		if (!arg[0])
			usage();
		if (p_shell(arg, pw, (ENTRY *)NULL))
			pw_error((char *)NULL, 0, 1);
E 16
	}
D 16
	if (!(temp_fp = fdopen(fd, "w"))) {
D 7
		fprintf(stderr, "chpass: can't write %s", temp);
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't write %s", temp);
E 8
I 8
		(void)fprintf(stderr, "chpass: can't write %s; ", temp);
E 8
E 7
		goto bad;
	}
E 16

D 7
	if (!info(pw))
E 7
I 7
D 12
	if (!aflag && !info(pw))
E 12
I 12
D 16
	if (newsh) {
		if (p_shell(newsh, pw, (struct entry *)NULL))
			goto bad;
	}
	else if (!aflag && !info(pw))
E 12
E 7
		goto bad;

D 7
	/*
	 * special checks...
	 *
	 * there has to be a limit on the size of the gecos fields,
	 * otherwise getpwent(3) can choke.
	 * ``if I swallow anything evil, put your fingers down my throat...''
	 *	-- The Who
	 */
	if (strlen(list[E_NAME].save) + strlen(list[E_BPHONE].save) +
	    strlen(list[E_HPHONE].save) + strlen(list[E_LOCATE].save)
	    > 512) {
		fprintf(stderr, "chpass: gecos field too large.\n");
		exit(1);
	}
	(void)sprintf(pw->pw_gecos = buf, "%s,%s,%s,%s",
D 2
	    list[E_NAME].save, list[E_BPHONE].save, list[E_HPHONE].save,
	    list[E_LOCATE].save);
E 2
I 2
D 4
	    list[E_NAME].save, list[E_LOCATE].save, list[E_BPHONE].save,
	    list[E_HPHONE].save);
E 4
I 4
D 5
	    list[E_NAME].save ? list[E_NAME].save : "",
	    list[E_LOCATE].save ? list[E_LOCATE].save : "",
	    list[E_BPHONE].save ? list[E_BPHONE].save : "",
	    list[E_HPHONE].save ? list[E_HPHONE].save : "");
E 5
I 5
	    list[E_NAME].save, list[E_LOCATE].save, list[E_BPHONE].save,
	    list[E_HPHONE].save);
E 5
E 4
E 2

E 7
	/* root should have a 0 uid and a reasonable shell */
	if (!strcmp(pw->pw_name, "root")) {
		if (pw->pw_uid) {
D 7
			fprintf(stderr, "chpass: root uid should be 0.");
E 7
I 7
			(void)fprintf(stderr, "chpass: root uid should be 0.");
E 16
I 16
	if (op == LOADENTRY) {
		if (uid)
			baduser();
		pw = &lpw;
		if (!pw_scan(arg, pw))
E 16
E 7
			exit(1);
D 16
		}
		setusershell();
		for (;;)
			if (!(p = getusershell())) {
D 7
				fprintf(stderr,
E 7
I 7
				(void)fprintf(stderr,
E 7
				    "chpass: warning, unknown root shell.");
				break;
			}
			else if (!strcmp(pw->pw_shell, p))
				break;
E 16
	}

D 16
	passwd = _PATH_MASTERPASSWD;
	if (!freopen(passwd, "r", stdin)) {
D 7
		fprintf(stderr, "chpass: can't read %s", passwd);
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't read %s", passwd);
E 8
I 8
		(void)fprintf(stderr, "chpass: can't read %s; ", passwd);
E 8
E 7
		goto bad;
	}
	if (!copy(pw, temp_fp))
		goto bad;

	(void)fclose(temp_fp);
	(void)fclose(stdin);

	switch(fork()) {
	case 0:
		break;
	case -1:
D 7
		fprintf(stderr, "chpass: can't fork");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't fork");
E 8
I 8
		(void)fprintf(stderr, "chpass: can't fork; ");
E 8
E 7
		goto bad;
		/* NOTREACHED */
	default:
		exit(0);
		/* NOTREACHED */
	}

	if (makedb(temp)) {
D 7
		fprintf(stderr, "chpass: mkpasswd failed");
bad:		fprintf(stderr, "; information unchanged.\n");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: mkpasswd failed");
bad:		(void)fprintf(stderr, "; information unchanged.\n");
E 8
I 8
		(void)fprintf(stderr, "chpass: mkpasswd failed; ");
bad:		(void)fprintf(stderr, "%s unchanged.\n", _PATH_MASTERPASSWD);
E 8
E 7
		(void)unlink(temp);
		exit(1);
	}

E 16
	/*
D 16
	 * possible race; have to rename four files, and someone could slip
	 * in between them.  LOCK_EX and rename the ``passwd.dir'' file first
	 * so that getpwent(3) can't slip in; the lock should never fail and
	 * it's unclear what to do if it does.  Rename ``ptmp'' last so that
	 * passwd/vipw/chpass can't slip in.
E 16
I 16
D 17
	 * The file descriptor usage is a little tricky through here.
E 17
I 17
	 * The temporary file/file descriptor usage is a little tricky here.
E 17
	 * 1:	We start off with two fd's, one for the master password
D 17
	 *	file, and one for the temporary file.
	 * 2:	Get an fp for the temporary file, copy the info to be
	 *	edited into it, and close the fp (closing the underlying
	 *	fd).
E 17
I 17
	 *	file (used to lock everything), and one for a temporary file.
	 * 2:	Display() gets an fp for the temporary file, and copies the
	 *	user's information into it.  It then gives the temporary file
	 *	to the user and closes the fp, closing the underlying fd.
E 17
	 * 3:	The user edits the temporary file some number of times.
D 17
	 * 4:	Get an fp for the temporary file, and verify the contents.
	 *	We can't use the fp from step 2, because the user's editor
	 *	may have created a new instance of the file.  Close the
	 *	fp when done.
	 * 5:	Get an fp for the temporary file, truncating it as we do
	 *	so.  Get an fp for the master password file.  Copy the
	 *	master password file into the temporary file, replacing the
	 *	user record with a new one.  Close the temporary file fp
	 *	when done -- can't close the password fp, or we'd lose the
	 *	lock.
	 * 6:	Call pw_mkdb() and exit.  The exit closes the master password
	 *	fd from step 1, and the master password fp from step 5.
E 17
I 17
	 * 4:	Verify() gets an fp for the temporary file, and verifies the
	 *	contents.  It can't use an fp derived from the step #2 fd,
	 *	because the user's editor may have created a new instance of
	 *	the file.  Once the file is verified, its contents are stored
	 *	in a password structure.  The verify routine closes the fp,
	 *	closing the underlying fd.
	 * 5:	Delete the temporary file.
	 * 6:	Get a new temporary file/fd.  Pw_copy() gets an fp for it
	 *	file and copies the master password file into it, replacing
	 *	the user record with a new one.  We can't use the first
	 *	temporary file for this because it was owned by the user.
	 *	Pw_copy() closes its fp, flushing the data and closing the
	 *	underlying file descriptor.  We can't close the master
	 *	password fp, or we'd lose the lock.
	 * 7:	Call pw_mkdb() (which renames the temporary file) and exit.
	 *	The exit closes the master passwd fp/fd.
E 17
E 16
	 */
D 16
	(void)setpriority(PRIO_PROCESS, 0, -20);
	fend = strcpy(from, temp) + strlen(temp);
D 9
	tend = strcpy(to, passwd) + strlen(passwd);
E 9
I 9
	tend = strcpy(to, _PATH_PASSWD) + strlen(_PATH_PASSWD);
E 9
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
}
E 16
I 16
	pw_init();
	pfd = pw_lock();
	tfd = pw_tmp();
E 16

D 16
info(pw)
	struct passwd *pw;
{
D 8
	register struct entry *ep;
	register char *p;
I 7
	static char buf[1024];
E 8
E 7
	struct stat begin, end;
	FILE *fp;
	int fd, rval;
D 7
	char *tfile, buf[1024], *getenv();
E 7
I 7
D 8
	char *tfile, *getenv();
E 8
I 8
	char *tfile;
E 16
I 16
D 17
	if (op == EDITENTRY) 
		edit(tfd, pw);
E 16
E 8
E 7

D 11
	tfile = "/tmp/passwd.XXXXXX";
E 11
I 11
D 16
	tfile = _PATH_TMP;
E 11
	if ((fd = mkstemp(tfile)) == -1 || !(fp = fdopen(fd, "w+"))) {
D 7
		fprintf(stderr, "chpass: no temporary file");
E 7
I 7
		(void)fprintf(stderr, "chpass: no temporary file");
E 7
		return(0);
	}
E 16
I 16
	pw_copy(pfd, pw);
E 17
I 17
	if (op == EDITENTRY) {
		display(tfd, pw);
		edit(pw);
		(void)unlink(tempname);
		tfd = pw_tmp();
	}
		
	pw_copy(pfd, tfd, pw);
E 17
E 16

D 13
	print(fp, pw);
E 13
I 13
D 16
	/*
	 * if print doesn't print out a shell field, make it restricted.
	 * Not particularly pretty, but print is the routine that checks
	 * to see if the user can change their shell.
	 */
	if (!print(fp, pw))
		list[E_SHELL].restricted = 1;
E 13
	(void)fflush(fp);

I 3
	/*
	 * give the file to the real user; setuid permissions
	 * are discarded in edit()
	 */
	(void)fchown(fd, getuid(), getgid());
E 3
D 8
	(void)fstat(fd, &begin);
	rval = edit(tfile);
	(void)unlink(tfile);
E 8

D 8
	if (rval) {
D 7
		fprintf(stderr, "chpass: edit failed");
E 7
I 7
		(void)fprintf(stderr, "chpass: edit failed");
E 7
		return(0);
E 8
I 8
	for (rval = 0;;) {
		(void)fstat(fd, &begin);
		if (edit(tfile)) {
			(void)fprintf(stderr, "chpass: edit failed; ");
			break;
		}
		(void)fstat(fd, &end);
		if (begin.st_mtime == end.st_mtime) {
			(void)fprintf(stderr, "chpass: no changes made; ");
			break;
		}
		(void)rewind(fp);
		if (check(fp, pw)) {
			rval = 1;
			break;
		}
		(void)fflush(stderr);
		if (prompt())
			break;
E 8
	}
D 8
	(void)fstat(fd, &end);
	if (begin.st_mtime == end.st_mtime) {
D 7
		fprintf(stderr, "chpass: no changes made");
E 7
I 7
		(void)fprintf(stderr, "chpass: no changes made");
E 7
		return(0);
	}
	(void)rewind(fp);
E 8
I 8
	(void)fclose(fp);
	(void)unlink(tfile);
	return(rval);
}

check(fp, pw)
	FILE *fp;
	struct passwd *pw;
{
	register struct entry *ep;
	register char *p;
	static char buf[1024];

E 8
	while (fgets(buf, sizeof(buf), fp)) {
D 8
		if (!buf[0])
E 8
I 8
		if (!buf[0] || buf[0] == '#')
E 8
			continue;
		if (!(p = index(buf, '\n'))) {
D 7
			fprintf(stderr, "chpass: line too long");
E 7
I 7
D 8
			(void)fprintf(stderr, "chpass: line too long");
E 8
I 8
			(void)fprintf(stderr, "chpass: line too long.\n");
E 8
E 7
			return(0);
		}
		*p = '\0';
D 8
		for (ep = list; ep->prompt; ++ep)
E 8
I 8
		for (ep = list;; ++ep) {
			if (!ep->prompt) {
				(void)fprintf(stderr,
				    "chpass: unrecognized field.\n");
				return(0);
			}
E 8
			if (!strncasecmp(buf, ep->prompt, ep->len)) {
D 7
				if (ep->restricted && euid)
E 7
I 7
D 13
				if (ep->restricted && uid)
E 7
D 8
					continue;
E 8
I 8
					break;
E 13
I 13
				if (ep->restricted && uid) {
					(void)fprintf(stderr,
					    "chpass: you may not change the %s field.\n",
					    ep->prompt);
					return(0);
				}
E 13
E 8
				if (!(p = index(buf, ':'))) {
D 7
					fprintf(stderr,
E 7
I 7
					(void)fprintf(stderr,
E 7
D 8
					    "chpass: line corrupted");
E 8
I 8
					    "chpass: line corrupted.\n");
E 8
					return(0);
				}
				while (isspace(*++p));
				if (ep->except && strpbrk(p, ep->except)) {
D 7
					fprintf(stderr,
E 7
I 7
					(void)fprintf(stderr,
E 7
D 8
					   "chpass: illegal character in the \"%s\" field",
E 8
I 8
D 13
					   "chpass: illegal character in the \"%s\" field.\n",
E 13
I 13
					    "chpass: illegal character in the \"%s\" field.\n",
E 13
E 8
					    ep->prompt);
					return(0);
				}
				if ((ep->func)(p, pw, ep))
					return(0);
				break;
			}
I 8
		}
E 8
	}
D 8
	(void)fclose(fp);
E 8
I 7
	/*
	 * special checks...
	 *
	 * there has to be a limit on the size of the gecos fields,
	 * otherwise getpwent(3) can choke.
	 * ``if I swallow anything evil, put your fingers down my throat...''
	 *	-- The Who
	 */
	if (strlen(list[E_NAME].save) + strlen(list[E_BPHONE].save) +
	    strlen(list[E_HPHONE].save) + strlen(list[E_LOCATE].save)
	    > 512) {
		(void)fprintf(stderr, "chpass: gecos field too large.\n");
		exit(1);
	}
	(void)sprintf(pw->pw_gecos = buf, "%s,%s,%s,%s",
	    list[E_NAME].save, list[E_LOCATE].save, list[E_BPHONE].save,
	    list[E_HPHONE].save);
E 7
	return(1);
}

copy(pw, fp)
	struct passwd *pw;
	FILE *fp;
{
	register int done;
	register char *p;
	char buf[1024];

	for (done = 0; fgets(buf, sizeof(buf), stdin);) {
		/* skip lines that are too big */
		if (!index(buf, '\n')) {
D 7
			fprintf(stderr, "chpass: line too long");
E 7
I 7
D 8
			(void)fprintf(stderr, "chpass: line too long");
E 8
I 8
			(void)fprintf(stderr, "chpass: line too long; ");
E 8
E 7
			return(0);
		}
		if (done) {
D 7
			fprintf(fp, "%s", buf);
E 7
I 7
			(void)fprintf(fp, "%s", buf);
E 7
			continue;
		}
		if (!(p = index(buf, ':'))) {
D 7
			fprintf(stderr, "chpass: corrupted entry");
E 7
I 7
D 8
			(void)fprintf(stderr, "chpass: corrupted entry");
E 8
I 8
			(void)fprintf(stderr, "chpass: corrupted entry; ");
E 8
E 7
			return(0);
		}
		*p = '\0';
		if (strcmp(buf, pw->pw_name)) {
			*p = ':';
D 7
			fprintf(fp, "%s", buf);
E 7
I 7
			(void)fprintf(fp, "%s", buf);
E 7
			continue;
		}
D 7
		fprintf(fp, "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s\n",
E 7
I 7
		(void)fprintf(fp, "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s\n",
E 7
		    pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid,
		    pw->pw_class, pw->pw_change, pw->pw_expire, pw->pw_gecos,
		    pw->pw_dir, pw->pw_shell);
		done = 1;
	}
	if (!done)
D 7
		fprintf(fp, "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s\n",
E 7
I 7
		(void)fprintf(fp, "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s\n",
E 7
D 6
		    pw->pw_name, "NOLOGIN", pw->pw_uid, pw->pw_gid,
E 6
I 6
		    pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid,
E 6
		    pw->pw_class, pw->pw_change, pw->pw_expire, pw->pw_gecos,
		    pw->pw_dir, pw->pw_shell);
	return(1);
}

makedb(file)
	char *file;
{
	int status, pid, w;

	if (!(pid = vfork())) {
		execl(_PATH_MKPASSWD, "mkpasswd", "-p", file, NULL);
I 14
		(void)fprintf(stderr, "chpass: can't find \"mkpasswd\".\n");
E 14
		_exit(127);
	}
	while ((w = wait(&status)) != pid && w != -1);
	return(w == -1 || status);
}

edit(file)
	char *file;
{
	int status, pid, w;
	char *p, *editor, *getenv();

	if (editor = getenv("EDITOR")) {
		if (p = rindex(editor, '/'))
			++p;
		else
			p = editor;
	}
	else
		p = editor = "vi";
	if (!(pid = vfork())) {
I 3
D 10
		(void)setuid(getuid());
E 10
		(void)setgid(getgid());
I 10
		(void)setuid(getuid());
E 10
E 3
		execlp(editor, p, file, NULL);
I 14
		(void)fprintf(stderr, "chpass: can't find \"%s\".\n", editor);
E 14
		_exit(127);
	}
	while ((w = wait(&status)) != pid && w != -1);
	return(w == -1 || status);
I 7
}

loadpw(arg, pw)
	char *arg;
	register struct passwd *pw;
{
	register char *cp;
I 15
	char *bp = arg;
E 15
	long atol();
	char *strsep();

D 15
	pw->pw_name = strsep(arg, ":");
	pw->pw_passwd = strsep((char *)NULL, ":");
	if (!(cp = strsep((char *)NULL, ":")))
E 15
I 15
	pw->pw_name = strsep(&bp, ":");
	pw->pw_passwd = strsep(&bp, ":");
	if (!(cp = strsep(&bp, ":")))
E 15
		goto bad;
	pw->pw_uid = atoi(cp);
D 15
	if (!(cp = strsep((char *)NULL, ":")))
E 15
I 15
	if (!(cp = strsep(&bp, ":")))
E 15
		goto bad;
	pw->pw_gid = atoi(cp);
D 15
	pw->pw_class = strsep((char *)NULL, ":");
	if (!(cp = strsep((char *)NULL, ":")))
E 15
I 15
	pw->pw_class = strsep(&bp, ":");
	if (!(cp = strsep(&bp, ":")))
E 15
		goto bad;
	pw->pw_change = atol(cp);
D 15
	if (!(cp = strsep((char *)NULL, ":")))
E 15
I 15
	if (!(cp = strsep(&bp, ":")))
E 15
		goto bad;
	pw->pw_expire = atol(cp);
D 15
	pw->pw_gecos = strsep((char *)NULL, ":");
	pw->pw_dir = strsep((char *)NULL, ":");
	pw->pw_shell = strsep((char *)NULL, ":");
	if (!pw->pw_shell || strsep((char *)NULL, ":")) {
E 15
I 15
	pw->pw_gecos = strsep(&bp, ":");
	pw->pw_dir = strsep(&bp, ":");
	pw->pw_shell = strsep(&bp, ":");
	if (!pw->pw_shell || strsep(&bp, ":")) {
E 15
bad:		(void)fprintf(stderr, "chpass: bad password list.\n");
		exit(1);
	}
I 8
}

prompt()
{
	register int c;

	for (;;) {
		(void)printf("re-edit the password file? [y]: ");
		(void)fflush(stdout);
		c = getchar();
		if (c != EOF && c != (int)'\n')
			while (getchar() != (int)'\n');
		return(c == (int)'n');
	}
	/* NOTREACHED */
E 16
I 16
	if (!pw_mkdb())
		pw_error((char *)NULL, 0, 1);
	exit(0);
E 16
E 8
}

I 19
void
E 19
I 12
baduser()
{
D 19
	(void)fprintf(stderr, "chpass: %s\n", strerror(EACCES));
	exit(1);
E 19
I 19

	errx(1, "%s", strerror(EACCES));
E 19
}

I 19
void
E 19
E 12
usage()
{
I 19

E 19
D 12
	(void)fprintf(stderr, "usage: chpass [-a list] [user]\n");
E 12
I 12
	(void)fprintf(stderr, "usage: chpass [-a list] [-s shell] [user]\n");
E 12
	exit(1);
E 7
}
E 1
