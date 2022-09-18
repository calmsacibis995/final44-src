h09239
s 00002/00002/00030
d D 8.1 93/06/04 12:02:51 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00018/00032
d D 5.10 93/01/12 10:32:26 bostic 15 14
c move cuserid() to libcompat, POSIX no longer requires it
e
s 00003/00003/00047
d D 5.9 91/02/23 19:49:43 donn 14 13
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00048
d D 5.8 90/06/24 16:02:15 karels 13 12
c use kernel MAXLOGNAME instead of UT_NAMESIZE (kernel's is bigger)
e
s 00001/00011/00049
d D 5.7 90/06/01 14:10:43 bostic 12 11
c new copyright notice
e
s 00011/00011/00049
d D 5.6 89/08/26 17:00:10 karels 11 10
c correct cuserid error case; make setlogin invalidate getlogin cache; KNF
e
s 00007/00007/00053
d D 5.5 89/04/20 12:01:28 bostic 10 9
c if kernel returns NULL string, return NULL to user; KNF
e
s 00048/00021/00012
d D 5.4 89/03/07 00:34:29 kfall 9 8
c new getlogin using getlogname syscall; plus cuserid library call
e
s 00002/00000/00031
d D 5.3 86/05/09 16:14:11 lepreau 8 6
c return 0 not null string when user has a ctty but no utmp entry
e
s 00002/00000/00031
d R 5.3 86/05/09 16:00:19 lepreau 7 6
c avoid return pointer to a null string; return 0 instead
e
s 00002/00002/00029
d D 5.2 86/03/09 19:47:51 donn 6 5
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00028
d D 5.1 85/06/05 12:45:28 mckusick 5 2
c Add copyright
e
s 00009/00001/00028
d R 5.1 85/06/05 12:20:57 mckusick 4 2
c Add copyright
e
s 00029/00012/00017
d R 4.3 84/04/27 10:32:15 ralph 3 2
c new versions which use getttyent(3).
e
s 00015/00012/00014
d D 4.2 82/11/14 13:59:06 sam 2 1
c merge of 4.1b and 4.1c
e
s 00026/00000/00000
d D 4.1 82/11/07 19:06:08 sam 1 0
c date and time created 82/11/07 19:06:08 by sam
e
u
U
t
T
I 9
/*
D 16
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
 */

E 9
I 1
D 2
/*	%W% (Berkeley) %G%	*/
E 2
I 2
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
D 6
#ifndef lint
E 6
I 6
#if defined(LIBC_SCCS) && !defined(lint)
E 6
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
D 9
#endif LIBC_SCCS and not lint
E 9
I 9
#endif /* LIBC_SCCS and not lint */
E 9
E 6
E 5

I 9
D 13
#include <sys/types.h>
E 13
I 13
#include <sys/param.h>
E 13
D 14
#include <stdio.h>
E 14
#include <pwd.h>
E 9
E 2
#include <utmp.h>
I 14
#include <stdio.h>
#include <string.h>
#include <unistd.h>
E 14

D 2
static	char	UTMP[]	= "/etc/utmp";
static	struct	utmp ubuf;
E 2
I 2
D 9
static	char UTMP[]	= "/etc/utmp";
static	struct utmp ubuf;
E 9
I 9
D 11
static	char	logname[UT_NAMESIZE+1];
E 11
I 11
int	_logname_valid;		/* known to setlogin() */
E 11
E 9
E 2

char *
getlogin()
{
D 2
	register me, uf;
E 2
I 2
D 9
	register int me, uf;
E 2
	register char *cp;
E 9
I 9
D 11
	static int notcalled = 1;
E 11
I 11
D 13
	static char logname[UT_NAMESIZE+1];
E 13
I 13
	static char logname[MAXLOGNAME + 1];
E 13
E 11
E 9

D 2
	if( !(me = ttyslot()) )
E 2
I 2
D 9
	if (!(me = ttyslot()))
E 2
		return(0);
D 2
	if( (uf = open( UTMP, 0 )) < 0 )
		return(0);
	lseek( uf, (long)(me*sizeof(ubuf)), 0 );
	if (read(uf, (char *)&ubuf, sizeof(ubuf)) != sizeof(ubuf))
		return(0);
E 2
I 2
	if ((uf = open(UTMP, 0)) < 0)
		return (0);
	lseek (uf, (long)(me*sizeof(ubuf)), 0);
	if (read(uf, (char *)&ubuf, sizeof (ubuf)) != sizeof (ubuf)) {
		close(uf);
		return (0);
E 9
I 9
D 11
	if (notcalled) {
D 10
		if(getlogname(logname, sizeof(logname) - 1) < 0)
			return((char *) 0);
E 10
I 10
		if (getlogname(logname, sizeof(logname) - 1) < 0)
			return((char *)NULL);
E 10
		notcalled = 0;
E 11
I 11
	if (_logname_valid == 0) {
		if (_getlogin(logname, sizeof(logname) - 1) < 0)
			return ((char *)NULL);
		_logname_valid = 1;
E 11
E 9
	}
E 2
D 9
	close(uf);
I 8
	if (ubuf.ut_name[0] == '\0')
		return (0);
E 8
	ubuf.ut_name[sizeof (ubuf.ut_name)] = ' ';
D 2
	for (cp=ubuf.ut_name; *cp++!=' ';)
E 2
I 2
	for (cp = ubuf.ut_name; *cp++ != ' '; )
E 2
		;
	*--cp = '\0';
D 2
	return( ubuf.ut_name );
E 2
I 2
	return (ubuf.ut_name);
E 9
I 9
D 10
	return(logname);
E 10
I 10
D 11
	return(*logname ? logname : (char *)NULL);
E 11
I 11
	return (*logname ? logname : (char *)NULL);
E 11
E 10
}
D 14

uid_t	geteuid();
E 14
D 15

char *
cuserid(s)
D 11
	char	*s;
E 11
I 11
	char *s;
E 11
{
	register struct passwd *pwd;

D 10
	if((pwd = getpwuid(geteuid())) == NULL) {
		if(s)
E 10
I 10
	if ((pwd = getpwuid(geteuid())) == NULL) {
		if (s)
E 10
			*s = '\0';
D 11
		return(NULL);
E 11
I 11
		return (s);
E 11
	}
D 10
	if(s) {
		(void) strncpy(s, pwd->pw_name, L_cuserid);
E 10
I 10
	if (s) {
		(void)strncpy(s, pwd->pw_name, L_cuserid);
E 10
D 11
		return(s);
E 11
I 11
		return (s);
E 11
	}
D 11
	return(pwd->pw_name);
E 11
I 11
	return (pwd->pw_name);
E 11
E 9
E 2
}
E 15
E 1
