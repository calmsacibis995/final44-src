h38201
s 00016/00004/00139
d D 8.2 94/03/21 17:43:26 bostic 15 13
c The functions in getgrent.c don't work right, because gr_mem isn't set
c up properly to deal with emtpy groups or the end-of-line. The return
c value from strsep() is the buffer pointer given to strsep() so there's
c an extra blnak entry at the end of the user list.  The field can be zero
c length if there are extra space.
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00007/00001/00142
d R 8.2 94/03/21 17:40:47 bostic 14 13
c The functions in getgrent.c don't work right, because gr_mem isn't
c set up properly to deal with emtpy groups or the end-of-line. The return value
c from strsep() is the buffer pointer given to strsep() so there's an extra
c blnak entry at the end of the user list.  The field can be zero length if
c there are extra space.
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00002/00002/00141
d D 8.1 93/06/04 12:02:31 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00019/00133
d D 5.9 91/04/01 13:49:32 bostic 12 11
c delete setgrfile, ANSI style declarations, minor cleanups
e
s 00013/00004/00139
d D 5.8 91/02/23 19:49:42 donn 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00142
d D 5.7 90/06/24 21:35:24 bostic 10 9
c can't test gid, there are groups numbered 0.
e
s 00001/00011/00142
d D 5.6 90/06/01 14:10:35 bostic 9 8
c new copyright notice
e
s 00006/00004/00147
d D 5.5 90/05/11 18:24:01 marc 8 7
c new strsep
e
s 00124/00044/00027
d D 5.4 89/03/11 15:52:31 bostic 7 6
c redo from scratch; clean up semantics, make consistent with getpwent
e
s 00007/00001/00064
d D 5.3 87/11/05 14:35:17 bostic 6 5
c add setgrfile; bug report 4.3BSD/lib/96
e
s 00002/00002/00063
d D 5.2 86/03/09 19:47:14 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00062
d D 5.1 85/06/05 12:19:19 mckusick 4 3
c Add copyright
e
s 00001/00001/00062
d D 4.3 83/08/18 14:56:20 sam 3 2
c upped limit to keep sites with many users happy
e
s 00008/00009/00055
d D 4.2 82/03/29 01:47:11 wnj 2 1
c bounds checking
e
s 00064/00000/00000
d D 4.1 80/12/21 16:50:31 wnj 1 0
c date and time created 80/12/21 16:50:31 by wnj
e
u
U
t
T
I 7
/*
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

E 7
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 5
E 4
I 2

I 7
#include <sys/types.h>
E 7
E 2
#include <stdio.h>
I 11
#include <stdlib.h>
E 11
#include <grp.h>

D 2
#define	CL	':'
#define	CM	','
#define	NL	'\n'
E 2
D 3
#define	MAXGRP	100
E 3
I 3
D 7
#define	MAXGRP	200
E 7
I 7
static FILE *_gr_fp;
static struct group _gr_group;
static int _gr_stayopen;
D 11
static char *_gr_file = _PATH_GROUP;
E 11
I 11
D 12
static const char *_gr_file = _PATH_GROUP;
static start_gr();
static grscan();
E 12
I 12
static int grscan(), start_gr();
E 12
E 11
E 7
E 3

D 6
static char GROUP[] = "/etc/group";
E 6
I 6
D 7
static char *GROUP = "/etc/group";
E 6
static FILE *grf = NULL;
static char line[BUFSIZ+1];
static struct group group;
static char *gr_mem[MAXGRP];
E 7
I 7
#define	MAXGRP		200
static char *members[MAXGRP];
#define	MAXLINELENGTH	1024
static char line[MAXLINELENGTH];
E 7

D 7
setgrent()
E 7
I 7
struct group *
getgrent()
E 7
{
D 7
	if( !grf )
		grf = fopen( GROUP, "r" );
	else
		rewind( grf );
E 7
I 7
D 12
	if (!_gr_fp && !start_gr() || !grscan(0, 0, (char *)NULL))
		return((struct group *)NULL);
E 12
I 12
	if (!_gr_fp && !start_gr() || !grscan(0, 0, NULL))
		return(NULL);
E 12
	return(&_gr_group);
E 7
}

D 7
endgrent()
E 7
I 7
struct group *
getgrnam(name)
D 11
	char *name;
E 11
I 11
	const char *name;
E 11
E 7
{
D 7
	if( grf ){
		fclose( grf );
		grf = NULL;
E 7
I 7
	int rval;

	if (!start_gr())
D 12
		return((struct group *)NULL);
E 12
I 12
		return(NULL);
E 12
	rval = grscan(1, 0, name);
	if (!_gr_stayopen)
		endgrent();
D 12
	return(rval ? &_gr_group : (struct group *)NULL);
E 12
I 12
	return(rval ? &_gr_group : NULL);
E 12
}

struct group *
I 11
#ifdef __STDC__
getgrgid(gid_t gid)
#else
E 11
getgrgid(gid)
D 11
	int gid;
E 11
I 11
	gid_t gid;
#endif
E 11
{
	int rval;

	if (!start_gr())
D 12
		return((struct group *)NULL);
	rval = grscan(1, gid, (char *)NULL);
E 12
I 12
		return(NULL);
	rval = grscan(1, gid, NULL);
E 12
	if (!_gr_stayopen)
		endgrent();
D 12
	return(rval ? &_gr_group : (struct group *)NULL);
E 12
I 12
	return(rval ? &_gr_group : NULL);
E 12
}

static
start_gr()
{
	if (_gr_fp) {
		rewind(_gr_fp);
		return(1);
E 7
	}
I 7
D 12
	return((_gr_fp = fopen(_gr_file, "r")) ? 1 : 0);
E 12
I 12
	return((_gr_fp = fopen(_PATH_GROUP, "r")) ? 1 : 0);
E 12
E 7
}

I 11
int
E 11
D 7
static char *
grskip(p,c)
register char *p;
register c;
E 7
I 7
setgrent()
E 7
{
D 7
	while( *p && *p != c ) ++p;
	if( *p ) *p++ = 0;
	return( p );
E 7
I 7
	return(setgroupent(0));
E 7
}

I 11
int
E 11
D 7
struct group *
getgrent()
E 7
I 7
setgroupent(stayopen)
	int stayopen;
E 7
{
D 7
	register char *p, **q;
E 7
I 7
	if (!start_gr())
		return(0);
	_gr_stayopen = stayopen;
	return(1);
}
E 7

D 7
	if( !grf && !(grf = fopen( GROUP, "r" )) )
		return(NULL);
	if( !(p = fgets( line, BUFSIZ, grf )) )
		return(NULL);
	group.gr_name = p;
D 2
	group.gr_passwd = p = grskip(p,CL);
	group.gr_gid = atoi( p = grskip(p,CL) );
E 2
I 2
	group.gr_passwd = p = grskip(p,':');
	group.gr_gid = atoi( p = grskip(p,':') );
E 2
	group.gr_mem = gr_mem;
D 2
	p = grskip(p,CL);
	grskip(p,NL);
E 2
I 2
	p = grskip(p,':');
	grskip(p,'\n');
E 2
	q = gr_mem;
	while( *p ){
D 2
		*q++ = p;
		p = grskip(p,CM);
E 2
I 2
		if (q < &gr_mem[MAXGRP-1])
			*q++ = p;
		p = grskip(p,',');
E 7
I 7
void
endgrent()
{
	if (_gr_fp) {
		(void)fclose(_gr_fp);
D 12
		_gr_fp = (FILE *)NULL;
E 12
I 12
		_gr_fp = NULL;
E 12
E 7
E 2
	}
D 7
	*q = NULL;
	return( &group );
E 7
I 6
D 12
}

I 7
void
E 7
setgrfile(file)
D 11
	char *file;
E 11
I 11
	const char *file;
E 11
{
D 7
	GROUP = file;
E 7
I 7
	_gr_file = file;
E 12
}

static
grscan(search, gid, name)
	register int search, gid;
	register char *name;
{
	register char *cp, **m;
I 8
	char *bp;
E 8
	char *fgets(), *strsep(), *index();

	for (;;) {
		if (!fgets(line, sizeof(line), _gr_fp))
			return(0);
I 8
		bp = line;
E 8
		/* skip lines that are too big */
		if (!index(line, '\n')) {
			int ch;

			while ((ch = getc(_gr_fp)) != '\n' && ch != EOF)
				;
			continue;
		}
D 8
		_gr_group.gr_name = strsep(line, ":\n");
E 8
I 8
		_gr_group.gr_name = strsep(&bp, ":\n");
E 8
		if (search && name && strcmp(_gr_group.gr_name, name))
			continue;
D 8
		_gr_group.gr_passwd = strsep((char *)NULL, ":\n");
		if (!(cp = strsep((char *)NULL, ":\n")))
E 8
I 8
		_gr_group.gr_passwd = strsep(&bp, ":\n");
		if (!(cp = strsep(&bp, ":\n")))
E 8
			continue;
		_gr_group.gr_gid = atoi(cp);
D 10
		if (search && gid && _gr_group.gr_gid != gid)
E 10
I 10
		if (search && name == NULL && _gr_group.gr_gid != gid)
E 10
			continue;
D 15
		for (m = _gr_group.gr_mem = members;; ++m) {
			if (m == &members[MAXGRP - 1]) {
				*m = NULL;
E 15
I 15
		cp = NULL;
		for (m = _gr_group.gr_mem = members;; bp++) {
			if (m == &members[MAXGRP - 1])
E 15
				break;
I 15
			if (*bp == ',') {
				if (cp) {
					*bp = '\0';
					*m++ = cp;
					cp = NULL;
				}
			} else if (*bp == '\0' || *bp == '\n' || *bp == ' ') {
				if (cp) {
					*bp = '\0';
					*m++ = cp;
E 15
			}
D 8
			if ((*m = strsep((char *)NULL, ", \n")) == NULL)
E 8
I 8
D 15
			if ((*m = strsep(&bp, ", \n")) == NULL)
E 15
E 8
				break;
I 15
			} else if (cp == NULL)
				cp = bp;
E 15
		}
I 15
		*m = NULL;
E 15
		return(1);
	}
	/* NOTREACHED */
E 7
E 6
}
E 1
