h43821
s 00012/00013/00162
d D 8.2 95/04/27 15:47:30 bostic 32 31
c update, cleanup, lint for password field extraction
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00173
d D 8.1 93/06/04 12:03:18 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00174
d D 5.22 91/09/14 10:32:19 bostic 30 29
c hash_open -> dbopen
e
s 00001/00000/00174
d D 5.21 91/03/14 09:28:17 bostic 29 28
c don't check it in until it compiles...
e
s 00002/00009/00172
d D 5.20 91/03/13 16:36:08 bostic 28 27
c use syslog instead of writing directly to stderr
e
s 00027/00026/00154
d D 5.19 91/03/03 14:20:51 bostic 27 26
c convert from ndbm(3) to db(3) interface
e
s 00001/00001/00179
d D 5.18 91/02/25 09:59:25 bostic 26 25
c missed a sizeof when fixed the last one
e
s 00008/00018/00172
d D 5.17 91/02/25 09:01:23 bostic 25 24
c Databases don't like it when the sizes of their keys change based
c on the compiler they're using.  Also, might as well leave the secure db open
c the fd's are marked close-on-exec.
e
s 00018/00007/00172
d D 5.16 91/02/24 14:06:50 bostic 24 23
c don't use syslog, application may have already used it.
c Add include files to get prototype declarations, and fix bugs found.
e
s 00090/00201/00089
d D 5.15 91/02/12 20:43:09 bostic 23 22
c rework the password subsystem
e
s 00001/00011/00289
d D 5.14 90/06/01 14:11:05 bostic 22 21
c new copyright notice
e
s 00012/00010/00288
d D 5.13 90/05/11 18:24:03 marc 21 20
c new strsep
e
s 00038/00030/00260
d D 5.12 90/05/10 18:06:38 edward 20 19
c don't use database for getpwent; checked in by Keith Bostic
e
s 00007/00005/00283
d D 5.11 89/09/18 21:29:56 bostic 19 18
c get first key if dbm database reopened
e
s 00004/00002/00284
d D 5.10 89/05/17 21:33:15 bostic 18 17
c use #define, not constant
e
s 00008/00005/00278
d D 5.9 89/04/01 12:14:34 bostic 17 16
c null dereference!
e
s 00021/00013/00262
d D 5.8 89/03/16 22:23:17 bostic 16 15
c use passwd.{pag,dir} with master.passwd for backward compat
e
s 00001/00002/00274
d D 5.7 89/03/02 20:49:52 bostic 15 14
c _pw_set no longer used
e
s 00008/00016/00268
d D 5.6 89/02/22 18:20:42 bostic 14 13
c have to call geteuid each time, program may discard permissions
e
s 00211/00112/00073
d D 5.5 89/02/22 11:02:14 bostic 13 12
c shadow passwords
e
s 00010/00002/00175
d D 5.4 88/12/21 08:42:48 bostic 12 10
c since user can put information in the password file (gecos field)
c can get overrun and produce bad results; also, increase max line length to
c 1024, since gecos field used by lots of places for extra information.
c bug report 4.3BSD-tahoe/bin/13
e
s 00008/00002/00175
d R 5.4 88/12/20 23:10:48 bostic 11 10
c since user can put information in the password file (gecos field)
c can get overrun and produce bad results; also, increase max line length to
c 1024, since gecos field used by lots of places for extra information.
c bug report 4.3BSD-tahoe/bin/13
e
s 00143/00062/00034
d D 5.3 88/11/14 08:45:42 bostic 10 9
c from scratch
e
s 00002/00002/00094
d D 5.2 86/03/09 19:48:16 donn 9 8
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00086
d D 5.1 85/06/05 12:22:49 mckusick 8 7
c Add copyright
e
s 00010/00006/00077
d D 4.6 85/01/21 20:12:14 serge 7 5
c made setpwfile work with getpwnam and getpwuid
e
s 00010/00006/00077
d R 4.6 85/01/16 15:12:39 serge 6 5
c made setpwfile work with getpwnam and getpwuid
e
s 00003/00003/00080
d D 4.5 84/08/28 14:57:39 ralph 5 4
c unify dbm names, break pwent <-> pwnamuid dependencies.
e
s 00002/00002/00081
d D 4.4 84/06/19 15:50:54 karels 4 3
c cure cancer
e
s 00007/00001/00076
d D 4.3 84/05/17 14:13:17 ralph 3 2
c added setpwfile() so routines can be used with alternate pw files.
e
s 00020/00010/00057
d D 4.2 84/04/26 10:32:46 ralph 2 1
c added stayopen flag for database, defaults to old code if no db.
e
s 00067/00000/00000
d D 4.1 80/12/21 16:50:37 wnj 1 0
c date and time created 80/12/21 16:50:37 by wnj
e
u
U
t
T
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
D 8
/* %W% (Berkeley) %E% */
E 8
I 8
/*
D 10
 * Copyright (c) 1984 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
D 31
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
D 22
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
D 13
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 13
E 10
 */

D 9
#ifndef lint
E 9
I 9
#if defined(LIBC_SCCS) && !defined(lint)
E 9
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 10
#endif LIBC_SCCS and not lint
E 10
I 10
#endif /* LIBC_SCCS and not lint */
E 10
E 9

I 10
D 23
#include <sys/types.h>
#include <sys/file.h>
E 10
E 8
E 4
#include <stdio.h>
E 23
I 23
#include <sys/param.h>
#include <fcntl.h>
I 27
#include <db.h>
I 29
#include <syslog.h>
E 29
E 27
E 23
#include <pwd.h>
I 2
D 27
#include <ndbm.h>
E 27
I 23
D 24
#include <unistd.h>
#include <syslog.h>
E 24
#include <utmp.h>
I 24
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
E 24
#include <limits.h>
E 23
E 2

I 32
/*
 * The lookup techniques and data extraction code here must be kept
 * in sync with that in `pwd_mkdb'.
 */

E 32
I 13
D 14
#define static
E 14
E 13
D 3
static char PASSWD[]	= "/etc/passwd";
E 3
I 3
D 7
static char *PASSWD = "/etc/passwd";
E 7
E 3
D 10
static char EMPTY[] = "";
static FILE *pwf = NULL;
static char line[BUFSIZ+1];
static struct passwd passwd;
E 10
I 10
D 23
static DBM *_pw_db;
static FILE *_pw_fp;
static struct passwd _pw_passwd;
D 13
static int _pw_set;
static char *_pw_file = "/etc/passwd";
E 13
I 13
D 14
static int _pw_euid = -1, _pw_fd, _pw_rewind = 1, _pw_set, _pw_stayopen;
E 14
I 14
D 15
static int _pw_fd, _pw_rewind = 1, _pw_set, _pw_stayopen;
E 15
I 15
D 16
static int _pw_fd, _pw_rewind = 1, _pw_stayopen;
E 15
E 14
static char _pw_flag, *_pw_file = _PATH_MASTERPASSWD;
E 16
I 16
D 19
static int _pw_rewind = 1, _pw_stayopen;
E 19
I 19
static int _pw_getfirstkey, _pw_stayopen;
E 19
D 20
static char _pw_flag, *_pw_file = _PATH_PASSWD;
E 20
I 20
static char _pw_flag, *_pw_file = _PATH_PASSWD, _pw_master;
E 23
I 23
static struct passwd _pw_passwd;	/* password structure */
D 27
static DBM *_pw_db;			/* password database */
E 27
I 27
static DB *_pw_db;			/* password database */
E 27
static int _pw_keynum;			/* key counter */
static int _pw_stayopen;		/* keep fd's open */
D 25
static int _pw_euid;
E 25
D 24
static __hashpw(), __initdb();
E 24
I 24
static int __hashpw(), __initdb();
E 24
E 23
E 20
E 16
E 13
E 10
I 2
D 5
extern DBM *_pw_db;
extern int _pw_stayopen;
E 5
I 5
D 7
DBM *_pw_db;
int _pw_stayopen;
E 7
E 5
E 2

I 7
D 10
/*
 * The following are shared with getpwnamuid.c
 */
char	*_pw_file = "/etc/passwd";
DBM	*_pw_db;
int	_pw_stayopen;
E 10
I 10
D 12
#define	MAXLINELENGTH	200
E 12
I 12
D 23
#define	MAXLINELENGTH	1024
E 12
static char line[MAXLINELENGTH];
E 10

E 23
I 13
struct passwd *
getpwent()
{
I 23
D 27
	datum key;
E 27
I 27
	DBT key;
E 27
D 25
	int rval;
E 25
	char bf[sizeof(_pw_keynum) + 1];
E 23
D 20
	datum key;
	int rval;
E 20

D 20
	if (!_pw_db && !_pw_fp && !start_pw())
E 20
I 20
D 23
	if (!_pw_fp && !start_pw(1))
E 23
I 23
	if (!_pw_db && !__initdb())
E 23
E 20
		return((struct passwd *)NULL);
D 20
	do {
		if (_pw_db) {
			key.dptr = NULL;
			rval = fetch_pw(key);
		} else /* _pw_fp */
			rval = scanpw();
	} while (rval && _pw_flag != _PW_KEYBYNAME);
D 14
	if (_pw_euid == -1)
		_pw_euid = geteuid();
	if (!_pw_euid)
		getpw();
E 14
I 14
D 17
	getpw();
E 17
I 17
	if (rval)
		getpw();
E 17
E 14
	return(rval ? &_pw_passwd : (struct passwd *)NULL);
E 20
I 20
D 23
	if (!scanpw())
		return((struct passwd *)NULL);
	getpw();
	return(&_pw_passwd);
E 23
I 23

	++_pw_keynum;
	bf[0] = _PW_KEYBYNUM;
	bcopy((char *)&_pw_keynum, bf + 1, sizeof(_pw_keynum));
D 27
	key.dptr = bf;
	key.dsize = sizeof(_pw_keynum) + 1;
D 25
	rval = __hashpw(key);

	/* Can't leave secure database open. */
	if (!_pw_euid) {
		(void)dbm_close(_pw_db);
		_pw_db = (DBM *)NULL;
	}
	return(rval ? &_pw_passwd : (struct passwd *)NULL);
E 25
I 25
	return(__hashpw(key) ? &_pw_passwd : (struct passwd *)NULL);
E 27
I 27
	key.data = (u_char *)bf;
	key.size = sizeof(_pw_keynum) + 1;
	return(__hashpw(&key) ? &_pw_passwd : (struct passwd *)NULL);
E 27
E 25
E 23
E 20
}

struct passwd *
D 23
getpwnam(nam)
	char *nam;
E 23
I 23
getpwnam(name)
D 24
	char *name;
E 24
I 24
	const char *name;
E 24
E 23
{
D 23
	int rval;
E 23
I 23
D 27
	datum key;
E 27
I 27
	DBT key;
E 27
	int len, rval;
	char bf[UT_NAMESIZE + 1];
E 23

D 20
	if (!start_pw())
E 20
I 20
D 23
	if (!start_pw(0))
E 23
I 23
	if (!_pw_db && !__initdb())
E 23
E 20
		return((struct passwd *)NULL);
D 23
	if (_pw_db) {
		datum key;
E 23

D 23
		key.dptr = nam;
		key.dsize = strlen(nam);
		rval = fetch_pw(key);
	} else /* _pw_fp */
D 17
		while (scanpw())
E 17
I 17
		for (rval = 0; scanpw();)
E 17
			if (!strcmp(nam, _pw_passwd.pw_name)) {
				rval = 1;
				break;
			}
	if (!_pw_stayopen)
		endpwent();
D 14
	if (_pw_euid == -1)
		_pw_euid = geteuid();
	if (!_pw_euid)
		getpw();
E 14
I 14
D 17
	getpw();
E 17
I 17
	if (rval)
		getpw();
E 23
I 23
	bf[0] = _PW_KEYBYNAME;
	len = strlen(name);
	bcopy(name, bf + 1, MIN(len, UT_NAMESIZE));
D 27
	key.dptr = bf;
	key.dsize = len + 1;
	rval = __hashpw(key);
E 27
I 27
	key.data = (u_char *)bf;
	key.size = len + 1;
	rval = __hashpw(&key);
E 27

D 25
	/* Can't leave secure database open. */
	if (!_pw_stayopen || !_pw_euid) {
E 25
I 25
	if (!_pw_stayopen) {
E 25
D 27
		(void)dbm_close(_pw_db);
		_pw_db = (DBM *)NULL;
E 27
I 27
		(void)(_pw_db->close)(_pw_db);
		_pw_db = (DB *)NULL;
E 27
	}
E 23
E 17
E 14
	return(rval ? &_pw_passwd : (struct passwd *)NULL);
}

struct passwd *
I 24
D 32
#ifdef __STDC__
getpwuid(uid_t uid)
#else
E 32
E 24
getpwuid(uid)
D 32
	int uid;
I 24
#endif
E 32
I 32
	uid_t uid;
E 32
E 24
{
I 23
D 27
	datum key;
E 27
I 27
	DBT key;
E 27
E 23
D 25
	int rval;
E 25
I 25
	int keyuid, rval;
E 25
I 23
D 26
	char bf[sizeof(uid) + 1];
E 26
I 26
	char bf[sizeof(keyuid) + 1];
E 26
E 23

D 20
	if (!start_pw())
E 20
I 20
D 23
	if (!start_pw(0))
E 23
I 23
	if (!_pw_db && !__initdb())
E 23
E 20
		return((struct passwd *)NULL);
D 23
	if (_pw_db) {
		datum key;
E 23

D 23
		key.dptr = (char *)&uid;
		key.dsize = sizeof(uid);
		rval = fetch_pw(key);
	} else /* _pw_fp */
D 17
		while (scanpw())
E 17
I 17
		for (rval = 0; scanpw();)
E 17
			if (_pw_passwd.pw_uid == uid) {
				rval = 1;
				break;
			}
	if (!_pw_stayopen)
		endpwent();
D 14
	if (_pw_euid == -1)
		_pw_euid = geteuid();
	if (!_pw_euid)
		getpw();
E 14
I 14
D 17
	getpw();
E 17
I 17
	if (rval)
		getpw();
E 17
E 14
	return(rval ? &_pw_passwd : (struct passwd *)NULL);
}
E 23
I 23
	bf[0] = _PW_KEYBYUID;
D 25
	bcopy(&uid, bf + 1, sizeof(uid));
E 25
I 25
	keyuid = uid;
	bcopy(&keyuid, bf + 1, sizeof(keyuid));
E 25
D 27
	key.dptr = bf;
D 25
	key.dsize = sizeof(uid) + 1;
E 25
I 25
	key.dsize = sizeof(keyuid) + 1;
E 25
	rval = __hashpw(key);
E 27
I 27
	key.data = (u_char *)bf;
	key.size = sizeof(keyuid) + 1;
	rval = __hashpw(&key);
E 27
E 23

E 13
E 7
D 10
setpwent()
E 10
I 10
D 23
static
D 13
pwscan()
E 13
I 13
D 20
start_pw()
E 20
I 20
start_pw(want_fp)
	char want_fp;		/* open _pw_fp also */
E 20
E 13
E 10
{
I 16
	char *p;

E 16
I 13
	if (_pw_db) {
D 19
		_pw_rewind = 1;
E 19
I 19
		_pw_getfirstkey = 1;
E 19
D 20
		return(1);
E 20
I 20
		if (!want_fp)
			return(1);
E 23
I 23
D 25
	/* Can't leave secure database open. */
	if (!_pw_stayopen || !_pw_euid) {
E 25
I 25
	if (!_pw_stayopen) {
E 25
D 27
		(void)dbm_close(_pw_db);
		_pw_db = (DBM *)NULL;
E 27
I 27
		(void)(_pw_db->close)(_pw_db);
		_pw_db = (DB *)NULL;
E 27
E 23
E 20
	}
D 23
	if (_pw_fp) {
		rewind(_pw_fp);
		return(1);
	}
D 19
	if (_pw_db = dbm_open(_pw_file, O_RDONLY, 0))
E 19
I 19
D 20
	if (_pw_db = dbm_open(_pw_file, O_RDONLY, 0)) {
E 20
I 20
	if (!_pw_db && (_pw_db = dbm_open(_pw_file, O_RDONLY, 0))) {
E 20
		_pw_getfirstkey = 1;
E 19
D 20
		return(1);
E 20
I 20
		if (!want_fp)
			return(1);
E 20
I 19
	}
E 19
D 16
	if (_pw_fp = fopen(_pw_file, "r"))
E 16
I 16
	/*
	 * special case; if it's the official password file, look in
	 * the master password file, otherwise, look in the file itself.
	 */
	p = strcmp(_pw_file, _PATH_PASSWD) ? _pw_file : _PATH_MASTERPASSWD;
D 20
	if (_pw_fp = fopen(p, "r"))
E 20
I 20
	if (_pw_fp = fopen(p, "r")) {
		_pw_master = 1;
E 20
E 16
		return(1);
I 20
	}
	/*
	 * If we really want to set up _pw_fp, then try again
	 * with the old file.
	 */
	if (want_fp && p != _pw_file && (_pw_fp = fopen(_pw_file, "r"))) {
		_pw_master = 0;
		return(1);
	}
E 20
	return(0);
E 23
I 23
	return(rval ? &_pw_passwd : (struct passwd *)NULL);
E 23
}

I 24
int
E 24
D 23
setpwent()
{
	return(setpassent(0));
}

E 23
setpassent(stayopen)
	int stayopen;
{
D 20
	if (!start_pw())
E 20
I 20
D 23
	if (!start_pw(0))
E 20
		return(0);
E 23
I 23
	_pw_keynum = 0;
E 23
	_pw_stayopen = stayopen;
	return(1);
}

I 24
int
E 24
I 23
setpwent()
{
	_pw_keynum = 0;
	_pw_stayopen = 0;
	return(1);
}

E 23
void
endpwent()
{
I 23
	_pw_keynum = 0;
E 23
	if (_pw_db) {
D 23
		dbm_close(_pw_db);
E 23
I 23
D 27
		(void)dbm_close(_pw_db);
E 23
		_pw_db = (DBM *)NULL;
E 27
I 27
		(void)(_pw_db->close)(_pw_db);
		_pw_db = (DB *)NULL;
E 27
D 20
	} else if (_pw_fp) {
E 20
I 20
	}
D 23
	if (_pw_fp) {
E 20
		(void)fclose(_pw_fp);
		_pw_fp = (FILE *)NULL;
	}
E 23
D 16
	if (_pw_fd) {
		(void)close(_pw_fd);
		_pw_fd = NULL;
	}
E 16
}

D 23
void
setpwfile(file)
	char *file;
{
	_pw_file = file;
D 15
	_pw_set = 1;
E 15
}

E 23
static
D 23
scanpw()
E 23
I 23
__initdb()
E 23
{
E 13
D 2
	if( pwf == NULL )
		pwf = fopen( PASSWD, "r" );
E 2
I 2
D 10
	if (pwf == NULL)
D 7
		pwf = fopen(PASSWD, "r");
E 7
I 7
		pwf = fopen(_pw_file, "r");
E 7
E 2
	else
D 2
		rewind( pwf );
E 2
I 2
		rewind(pwf);
E 10
I 10
D 23
	register char *cp;
I 13
	long atol();
I 21
	char *bp;
E 21
E 13
D 12
	char *fgets(), *strsep();
E 12
I 12
	char *fgets(), *strsep(), *index();
E 23
I 23
	static int warned;
	char *p;
E 23
E 12

D 23
	for (;;) {
D 13
		if (!(cp = fgets(line, sizeof(line), _pw_fp)))
E 13
I 13
		if (!(fgets(line, sizeof(line), _pw_fp)))
E 13
			return(0);
I 21
		bp = line;
E 21
I 12
		/* skip lines that are too big */
D 13
		if (!index(cp, '\n')) {
E 13
I 13
		if (!index(line, '\n')) {
E 13
			int ch;

			while ((ch = getc(_pw_fp)) != '\n' && ch != EOF)
				;
			continue;
		}
E 12
D 13
		_pw_passwd.pw_name = strsep(cp, ":\n");
E 13
I 13
D 21
		_pw_passwd.pw_name = strsep(line, ":\n");
E 13
		_pw_passwd.pw_passwd = strsep((char *)NULL, ":\n");
		if (!(cp = strsep((char *)NULL, ":\n")))
E 21
I 21
		_pw_passwd.pw_name = strsep(&bp, ":\n");
		_pw_passwd.pw_passwd = strsep(&bp, ":\n");
		if (!(cp = strsep(&bp, ":\n")))
E 21
			continue;
		_pw_passwd.pw_uid = atoi(cp);
D 21
		if (!(cp = strsep((char *)NULL, ":\n")))
E 21
I 21
		if (!(cp = strsep(&bp, ":\n")))
E 21
			continue;
		_pw_passwd.pw_gid = atoi(cp);
I 13
D 20
		_pw_passwd.pw_class = strsep((char *)NULL, ":\n");
		if (!(cp = strsep((char *)NULL, ":\n")))
			continue;
		_pw_passwd.pw_change = atol(cp);
		if (!(cp = strsep((char *)NULL, ":\n")))
			continue;
		_pw_passwd.pw_expire = atol(cp);
E 20
I 20
		if (_pw_master) {
D 21
			_pw_passwd.pw_class = strsep((char *)NULL, ":\n");
			if (!(cp = strsep((char *)NULL, ":\n")))
E 21
I 21
			_pw_passwd.pw_class = strsep(&bp, ":\n");
			if (!(cp = strsep(&bp, ":\n")))
E 21
				continue;
			_pw_passwd.pw_change = atol(cp);
D 21
			if (!(cp = strsep((char *)NULL, ":\n")))
E 21
I 21
			if (!(cp = strsep(&bp, ":\n")))
E 21
				continue;
			_pw_passwd.pw_expire = atol(cp);
		}
E 20
E 13
D 21
		_pw_passwd.pw_gecos = strsep((char *)NULL, ":\n");
		_pw_passwd.pw_dir = strsep((char *)NULL, ":\n");
		_pw_passwd.pw_shell = strsep((char *)NULL, ":\n");
E 21
I 21
		_pw_passwd.pw_gecos = strsep(&bp, ":\n");
		_pw_passwd.pw_dir = strsep(&bp, ":\n");
		_pw_passwd.pw_shell = strsep(&bp, ":\n");
E 21
D 13
		if (_pw_passwd.pw_shell) {
			_pw_passwd.pw_quota = 0;
			_pw_passwd.pw_comment = "";
			return(1);
		}
E 13
I 13
		if (!_pw_passwd.pw_shell)
			continue;
E 23
I 23
D 25
	p = (_pw_euid = geteuid()) ? _PATH_MP_DB : _PATH_SMP_DB;
E 25
I 25
	p = (geteuid()) ? _PATH_MP_DB : _PATH_SMP_DB;
E 25
D 27
	if (_pw_db = dbm_open(p, O_RDONLY, 0))
E 27
I 27
D 30
	_pw_db = hash_open(p, O_RDONLY, 0, NULL);
E 30
I 30
	_pw_db = dbopen(p, O_RDONLY, 0, DB_HASH, NULL);
E 30
	if (_pw_db)
E 27
E 23
		return(1);
I 23
D 28
	if (!warned) {
D 24
		openlog("getpwent", LOG_CONS|LOG_PERROR);
		syslog(LOG_ALERT, "%s: %m", p);
		closelog();
E 24
I 24
		(void)write(STDERR_FILENO, "getpwent: ", 10);
		(void)write(STDERR_FILENO, p, strlen(p));
		(void)write(STDERR_FILENO, ": ", 2);
		p = strerror(errno);
		(void)write(STDERR_FILENO, p, strlen(p));
		(void)write(STDERR_FILENO, "\n", 1);
E 24
		warned = 1;
E 23
E 13
	}
E 28
I 28
	if (!warned)
		syslog(LOG_ERR, "%s: %m", p);
E 28
D 23
	/* NOTREACHED */
E 23
I 23
	return(0);
E 23
E 10
E 2
}

D 10
endpwent()
E 10
I 10
static
D 13
fetchpw(key)
E 13
I 13
D 23
fetch_pw(key)
E 23
I 23
__hashpw(key)
E 23
E 13
D 27
	datum key;
E 27
I 27
	DBT *key;
E 27
E 10
{
D 2
	if( pwf != NULL ){
		fclose( pwf );
E 2
I 2
D 10
	if (pwf != NULL) {
		fclose(pwf);
E 2
		pwf = NULL;
	}
I 2
	if (_pw_db != (DBM *)0) {
E 10
I 10
D 13
	register char *cp, *tp;
E 13
I 13
	register char *p, *t;
I 23
	static u_int max;
	static char *line;
D 27
	datum dp;
E 27
I 27
	DBT data;
E 27
E 23
E 13

D 13
	if (_pw_db == (DBM *)NULL &&
	    (_pw_db = dbm_open(_pw_file, O_RDONLY, 0)) == (DBM *)NULL)
E 13
I 13
D 23
	/*
	 * the .dir file is LOCK_EX locked by programs that are
	 * renaming the various password files.
	 */
	if (flock(dbm_dirfno(_pw_db), LOCK_SH))
E 23
I 23
D 27
	dp = dbm_fetch(_pw_db, key);
	if (!(p = dp.dptr))
E 27
I 27
	if ((_pw_db->get)(_pw_db, key, &data, 0))
E 27
E 23
E 13
		return(0);
D 13
	if (flock(dbm_dirfno(_pw_db), LOCK_SH)) {
E 10
D 5
		ndbmclose(_pw_db);
E 5
I 5
		dbm_close(_pw_db);
E 5
D 10
		_pw_db = (DBM *)0;
		_pw_stayopen = 0;
E 10
I 10
		_pw_db = NULL;
		return(0);
E 10
	}
I 10
	key = dbm_fetch(_pw_db, key);
E 13
I 13
D 23
	if (!key.dptr)
D 19
		if (_pw_rewind) {
			_pw_rewind = 0;
E 19
I 19
		if (_pw_getfirstkey) {
			_pw_getfirstkey = 0;
E 19
			key = dbm_firstkey(_pw_db);
		} else
			key = dbm_nextkey(_pw_db);
	if (key.dptr)
		key = dbm_fetch(_pw_db, key);
E 13
	(void)flock(dbm_dirfno(_pw_db), LOCK_UN);
D 13
	if ((cp = key.dptr) == 0)
E 13
I 13
	if (!(p = key.dptr))
E 23
I 23
D 27
	if (dp.dsize > max && !(line = (char *)realloc(line, max += 1024)))
E 27
I 27
	p = (char *)data.data;
	if (data.size > max && !(line = realloc(line, max += 1024)))
E 27
E 23
E 13
		return(0);
I 23

I 32
	/* THIS CODE MUST MATCH THAT IN pwd_mkdb. */
E 32
E 23
D 13

	tp = line;
#define	EXPAND(e)	_pw_passwd.e = tp; while (*tp++ = *cp++);
	EXPAND(pw_name);
	EXPAND(pw_passwd);
	bcopy(cp, (char *)&_pw_passwd.pw_uid, sizeof(int));
	cp += sizeof(int);
	bcopy(cp, (char *)&_pw_passwd.pw_gid, sizeof(int));
	cp += sizeof(int);
	bcopy(cp, (char *)&_pw_passwd.pw_quota, sizeof(int));
	cp += sizeof(int);
	EXPAND(pw_comment);
	EXPAND(pw_gecos);
	EXPAND(pw_dir);
	EXPAND(pw_shell);
E 13
I 13
	t = line;
#define	EXPAND(e)	e = t; while (*t++ = *p++);
I 32
#define	SCALAR(v)	memmove(&(v), p, sizeof v); p += sizeof v
E 32
	EXPAND(_pw_passwd.pw_name);
	EXPAND(_pw_passwd.pw_passwd);
D 32
	bcopy(p, (char *)&_pw_passwd.pw_uid, sizeof(int));
	p += sizeof(int);
	bcopy(p, (char *)&_pw_passwd.pw_gid, sizeof(int));
	p += sizeof(int);
	bcopy(p, (char *)&_pw_passwd.pw_change, sizeof(time_t));
	p += sizeof(time_t);
E 32
I 32
	SCALAR(_pw_passwd.pw_uid);
	SCALAR(_pw_passwd.pw_gid);
	SCALAR(_pw_passwd.pw_change);
E 32
	EXPAND(_pw_passwd.pw_class);
	EXPAND(_pw_passwd.pw_gecos);
	EXPAND(_pw_passwd.pw_dir);
	EXPAND(_pw_passwd.pw_shell);
D 32
	bcopy(p, (char *)&_pw_passwd.pw_expire, sizeof(time_t));
	p += sizeof(time_t);
E 32
I 32
	SCALAR(_pw_passwd.pw_expire);
E 32
D 23
	_pw_flag = *p;
E 23
E 13
	return(1);
E 10
E 2
D 23
}

I 18
#define	_MAX_PASSWD_SIZE	50
static char pwbuf[_MAX_PASSWD_SIZE];

E 18
D 10
static char *
pwskip(p)
register char *p;
E 10
I 10
D 13
struct passwd *
getpwent()
E 13
I 13
static
getpw()
E 13
E 10
{
D 2
	while( *p && *p != ':' )
E 2
I 2
D 4
	while (*p && *p != ':')
E 4
I 4
D 10
	while (*p && *p != ':' && *p != '\n')
E 4
E 2
		++p;
D 2
	if( *p ) *p++ = 0;
E 2
I 2
	if (*p)
		*p++ = 0;
E 2
	return(p);
E 10
I 10
D 13
	if (!_pw_fp && !setpwent() || !pwscan())
		return((struct passwd *)NULL);
	return(&_pw_passwd);
E 10
}
E 13
I 13
D 18
	static char pwbuf[50];
I 14
	off_t lseek();
E 18
E 14
	long pos, atol();
D 16
	int n;
E 16
I 16
	int fd, n;
E 16
	char *p;
I 18
	off_t lseek();
E 18
E 13

I 14
	if (geteuid())
		return;
E 14
D 13
struct passwd *
D 10
getpwent()
E 10
I 10
getpwnam(nam)
	char *nam;
E 10
{
D 10
	register char *p;
E 10
I 10
	datum key;
E 10

D 10
	if (pwf == NULL) {
D 2
		if( (pwf = fopen( PASSWD, "r" )) == NULL )
E 2
I 2
D 7
		if ((pwf = fopen( PASSWD, "r" )) == NULL)
E 7
I 7
		if ((pwf = fopen( _pw_file, "r" )) == NULL)
E 7
E 2
			return(0);
E 10
I 10
	key.dptr = nam;
	key.dsize = strlen(nam);
	if (!fetchpw(key)) {
		if (setpwent())
			while (pwscan())
				if (!strcmp(nam, _pw_passwd.pw_name))
					return(&_pw_passwd);
		return((struct passwd *)NULL);
E 10
	}
D 10
	p = fgets(line, BUFSIZ, pwf);
D 2
	if (p==NULL)
E 2
I 2
	if (p == NULL)
E 2
		return(0);
	passwd.pw_name = p;
	p = pwskip(p);
	passwd.pw_passwd = p;
	p = pwskip(p);
	passwd.pw_uid = atoi(p);
	p = pwskip(p);
	passwd.pw_gid = atoi(p);
	passwd.pw_quota = 0;
	passwd.pw_comment = EMPTY;
	p = pwskip(p);
	passwd.pw_gecos = p;
	p = pwskip(p);
	passwd.pw_dir = p;
	p = pwskip(p);
	passwd.pw_shell = p;
D 2
	while(*p && *p != '\n') p++;
E 2
I 2
	while (*p && *p != '\n')
		p++;
E 2
	*p = '\0';
	return(&passwd);
E 10
I 10
	return(&_pw_passwd);
E 10
I 3
}

I 10
struct passwd *
getpwuid(uid)
	uid_t uid;
{
	datum key;

	key.dptr = (char *)&uid;
	key.dsize = sizeof(uid);
	if (!fetchpw(key)) {
		if (setpwent())
			while (pwscan())
				if (_pw_passwd.pw_uid == uid)
					return(&_pw_passwd);
		return((struct passwd *)NULL);
	}
	return(&_pw_passwd);
}

void
E 10
setpwfile(file)
	char *file;
{
D 7
	PASSWD = file;
E 7
I 7
	_pw_file = file;
I 10
	_pw_set = 1;
}

setpwent()
{
	if (_pw_set)
		endpwent();
	if (_pw_fp)
		rewind(_pw_fp);
	else if ((_pw_fp = fopen(_pw_file, "r")) == NULL)
		return(0);
	_pw_set = 0;
	return(1);
}

void
endpwent()
{
	if (_pw_fp) {
		(void)fclose(_pw_fp);
		_pw_fp = (FILE *)NULL;
	}
	if (_pw_db) {
		dbm_close(_pw_db);
		_pw_db = (DBM *)NULL;
	}
E 13
I 13
D 16
	if (!_pw_fd && (_pw_fd = open(_pw_file, O_RDONLY, 0)) < 0)
		goto bad;
E 16
I 16
	/*
	 * special case; if it's the official password file, look in
	 * the master password file, otherwise, look in the file itself.
	 */
	p = strcmp(_pw_file, _PATH_PASSWD) ? _pw_file : _PATH_MASTERPASSWD;
	if ((fd = open(p, O_RDONLY, 0)) < 0)
		return;
E 16
	pos = atol(_pw_passwd.pw_passwd);
D 16
	if (lseek(_pw_fd, pos, L_SET) != pos)
E 16
I 16
	if (lseek(fd, pos, L_SET) != pos)
E 16
		goto bad;
D 16
	if ((n = read(_pw_fd, pwbuf, sizeof(pwbuf) - 1)) < 0)
E 16
I 16
	if ((n = read(fd, pwbuf, sizeof(pwbuf) - 1)) < 0)
E 16
		goto bad;
	pwbuf[n] = '\0';
	for (p = pwbuf; *p; ++p)
		if (*p == ':') {
			*p = '\0';
			_pw_passwd.pw_passwd = pwbuf;
			break;
		}
D 14
	if (!_pw_stayopen)
bad:		(void)close(_pw_fd);
E 14
I 14
D 16
bad:	(void)close(_pw_fd);
E 16
I 16
bad:	(void)close(fd);
E 23
E 16
E 14
E 13
E 10
E 7
E 3
}
E 1
