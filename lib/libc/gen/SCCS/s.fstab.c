h06057
s 00002/00002/00174
d D 8.1 93/06/04 12:01:51 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00175
d D 5.17 92/12/14 15:53:34 bostic 22 21
c put a space before the error message
e
s 00005/00003/00170
d D 5.16 92/10/04 12:54:08 bostic 21 20
c <sys/errno.h> -> <errno.h>
e
s 00005/00004/00168
d D 5.15 91/02/23 19:49:40 donn 20 19
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00171
d D 5.14 90/11/28 17:02:46 bostic 19 18
c EBADFORMAT -> EFTYPE
e
s 00020/00005/00152
d D 5.13 90/11/28 00:13:10 bostic 18 17
c make error messages a little better, use constants in unistd.h
e
s 00025/00002/00132
d D 5.12 90/09/24 13:10:50 bostic 17 16
c add old-style fstab support on an #ifdef
e
s 00001/00011/00133
d D 5.11 90/06/01 14:10:19 bostic 16 15
c new copyright notice
e
s 00002/00000/00142
d D 5.10 90/05/10 21:12:09 bostic 15 14
c ignore empty entries or entries where first non-space char is a '#'
e
s 00001/00001/00141
d D 5.9 90/03/22 12:54:18 mckusick 14 13
c allow longer lines (from borman@cray.com)
e
s 00005/00001/00137
d D 5.8 89/08/21 17:33:29 mckusick 13 12
c do not return FSTAB_XX entries
e
s 00044/00012/00097
d D 5.7 89/08/18 18:11:12 mckusick 12 11
c update for new format used by NFS
e
s 00016/00008/00093
d D 5.6 89/05/23 16:56:55 bostic 11 10
c there's no way to distinguish between EOF and syntax error
e
s 00045/00053/00056
d D 5.5 88/11/14 08:44:47 bostic 10 8
c make consistent with getpwent and getgrent
e
s 00005/00003/00106
d R 5.5 88/09/16 14:53:15 bostic 9 8
c information hiding; don't need 1024 for /etc/fstab
e
s 00046/00100/00063
d D 5.4 88/08/15 12:24:22 bostic 8 7
c use correct buffer size; use strtok(3), delete fsskip() and fsdigit();
c change fstabscan to skip bad lines and continue on, also ignore lines with
c FSTAB_XX as the type field; delete getfstype(3); minor lint cleanups
e
s 00014/00003/00149
d D 5.3 88/08/13 15:20:45 bostic 7 6
c add Berkeley copyright
e
s 00002/00002/00150
d D 5.2 86/03/09 19:46:38 donn 6 5
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00145
d D 5.1 85/05/30 10:41:35 dist 5 4
c Add copyright
e
s 00004/00002/00142
d D 4.4 83/06/19 14:28:11 root 4 3
c thanks to wnj
e
s 00026/00014/00118
d D 4.3 83/05/24 10:35:37 sam 3 2
c instead of quotafile, use rq and "quotas"; add search by type
e
s 00093/00076/00039
d D 4.2 83/05/19 22:27:14 sam 2 1
c rewrite to allow variable length strings; add quota file
e
s 00115/00000/00000
d D 4.1 80/12/21 16:50:26 wnj 1 0
c date and time created 80/12/21 16:50:26 by wnj
e
u
U
t
T
I 5
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
E 8
I 8
D 23
 * Copyright (c) 1980, 1988 Regents of the University of California.
E 8
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1980, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
D 16
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 7
 */

E 5
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 6
#ifndef lint
E 6
I 6
#if defined(LIBC_SCCS) && !defined(lint)
E 6
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
D 6
#endif not lint
E 6
I 6
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 6
E 5

I 18
D 21
#include <sys/errno.h>
E 21
I 21
#include <errno.h>
E 21
E 18
E 2
#include <fstab.h>
I 11
D 21
#include <unistd.h>
E 21
E 11
#include <stdio.h>
I 20
#include <stdlib.h>
E 20
I 18
#include <string.h>
I 21
#include <unistd.h>
E 21
E 18
D 8
#include <ctype.h>
E 8

D 2
static	struct	fstab fs;
static	FILE	*fs_file = 0;
E 2
I 2
D 10
static	struct fstab fs;
I 8
static	FILE *fs_file = NULL;
E 8
static	char line[BUFSIZ+1];
E 10
I 10
static FILE *_fs_fp;
static struct fstab _fs_fstab;
I 20
D 21
static error();
E 21
I 21

static error __P((int));
static fstabscan __P((void));
E 21
E 20
E 10
D 8
static	FILE *fs_file = 0;
E 8
E 2

D 2
static	char	*fs_string(back, string, lg, end)
	char	*string, *back;
	int	lg;	/* length of field to stuff into */
	char	end;
E 2
I 2
D 8
static char *
fsskip(p)
	register char *p;
E 8
I 8
static
D 10
fstabscan(fsp)
	register struct fstab *fsp;
E 10
I 10
fstabscan()
E 10
E 8
E 2
{
D 2
	register	char	*cp;
	for (cp = string; *cp && *cp != end; cp++)
		continue;
	if (*cp == '\0') return(0);
	*cp = '\0';
	strncpy(back, string, lg-1);
	return(cp+1);
E 2
I 2
D 8

	while (*p && *p != ':')
		++p;
	if (*p)
		*p++ = 0;
	return (p);
E 2
}
D 2
static char *fs_digit(backp, string, end)
	int	*backp;
	char	*string;
	char	end;
E 2
I 2

static char *
fsdigit(backp, string, end)
	int *backp;
	char *string, end;
E 2
{
D 2
	register	int	value = 0;
	register	char	*cp;
	for (cp = string; *cp && isdigit(*cp); cp++){
E 2
I 2
	register int value = 0;
E 8
	register char *cp;
I 8
D 10
	char *fgets(), *strtok();
E 10
I 10
D 14
#define	MAXLINELENGTH	100
E 14
I 14
#define	MAXLINELENGTH	1024
E 14
	static char line[MAXLINELENGTH];
D 12
	char *fgets(), *strsep();
E 12
I 12
	char subline[MAXLINELENGTH];
D 20
	char *fgets(), *strtok();
E 20
I 13
	int typexx;
E 13
E 12
E 10
E 8

D 8
	for (cp = string; *cp && isdigit(*cp); cp++) {
E 2
		value *= 10;
		value += *cp - '0';
E 8
I 8
	for (;;) {
D 10
		if (!(cp = fgets(line, sizeof(line), fs_file)))
			return(1);
		fsp->fs_spec = strtok(cp, ":\n");
		fsp->fs_file = strtok((char *)NULL, ":\n");
		fsp->fs_type = strtok((char *)NULL, ":\n");
		if (fsp->fs_type && strcmp(fsp->fs_type, FSTAB_XX)) {
			if (!(cp = strtok((char *)NULL, ":\n")))
E 10
I 10
		if (!(cp = fgets(line, sizeof(line), _fs_fp)))
			return(0);
I 17
/* OLD_STYLE_FSTAB */
		if (!strpbrk(cp, " \t")) {
			_fs_fstab.fs_spec = strtok(cp, ":\n");
			_fs_fstab.fs_file = strtok((char *)NULL, ":\n");
			_fs_fstab.fs_type = strtok((char *)NULL, ":\n");
			if (_fs_fstab.fs_type) {
				if (!strcmp(_fs_fstab.fs_type, FSTAB_XX))
					continue;
				_fs_fstab.fs_mntops = _fs_fstab.fs_type;
				_fs_fstab.fs_vfstype =
				    strcmp(_fs_fstab.fs_type, FSTAB_SW) ?
				    "ufs" : "swap";
				if (cp = strtok((char *)NULL, ":\n")) {
					_fs_fstab.fs_freq = atoi(cp);
					if (cp = strtok((char *)NULL, ":\n")) {
						_fs_fstab.fs_passno = atoi(cp);
						return(1);
					}
				}
			}
			goto bad;
		}
/* OLD_STYLE_FSTAB */
E 17
D 12
		_fs_fstab.fs_spec = strsep(cp, ":\n");
		_fs_fstab.fs_file = strsep((char *)NULL, ":\n");
		_fs_fstab.fs_type = strsep((char *)NULL, ":\n");
D 11
		if (_fs_fstab.fs_type && strcmp(_fs_fstab.fs_type, FSTAB_XX)) {
			if (!(cp = strsep((char *)NULL, ":\n")))
E 11
I 11
		if (_fs_fstab.fs_type) {
			if (!strcmp(_fs_fstab.fs_type, FSTAB_XX))
E 12
I 12
		_fs_fstab.fs_spec = strtok(cp, " \t\n");
I 15
		if (!_fs_fstab.fs_spec || *_fs_fstab.fs_spec == '#')
			continue;
E 15
		_fs_fstab.fs_file = strtok((char *)NULL, " \t\n");
		_fs_fstab.fs_vfstype = strtok((char *)NULL, " \t\n");
		_fs_fstab.fs_mntops = strtok((char *)NULL, " \t\n");
		if (_fs_fstab.fs_mntops == NULL)
			goto bad;
		_fs_fstab.fs_freq = 0;
		_fs_fstab.fs_passno = 0;
		if ((cp = strtok((char *)NULL, " \t\n")) != NULL) {
			_fs_fstab.fs_freq = atoi(cp);
			if ((cp = strtok((char *)NULL, " \t\n")) != NULL)
				_fs_fstab.fs_passno = atoi(cp);
		}
		strcpy(subline, _fs_fstab.fs_mntops);
D 13
		for (cp = strtok(subline, ","); cp;
E 13
I 13
		for (typexx = 0, cp = strtok(subline, ","); cp;
E 13
		     cp = strtok((char *)NULL, ",")) {
			if (strlen(cp) != 2)
E 12
E 11
E 10
				continue;
D 10
			fsp->fs_freq = atoi(cp);
			if (!(cp = strtok((char *)NULL, ":\n")))
E 10
I 10
D 11
			_fs_fstab.fs_freq = atoi(cp);
			if (!(cp = strsep((char *)NULL, ":\n")))
E 10
				continue;
D 10
			fsp->fs_passno = atoi(cp);
			return(0);
E 10
I 10
			_fs_fstab.fs_passno = atoi(cp);
			return(1);
E 11
I 11
D 12
			if (cp = strsep((char *)NULL, ":\n")) {
				_fs_fstab.fs_freq = atoi(cp);
				if (cp = strsep((char *)NULL, ":\n")) {
					_fs_fstab.fs_passno = atoi(cp);
					return(1);
				}
E 12
I 12
			if (!strcmp(cp, FSTAB_RW)) {
				_fs_fstab.fs_type = FSTAB_RW;
				break;
E 12
			}
I 12
			if (!strcmp(cp, FSTAB_RQ)) {
				_fs_fstab.fs_type = FSTAB_RQ;
				break;
			}
			if (!strcmp(cp, FSTAB_RO)) {
				_fs_fstab.fs_type = FSTAB_RO;
				break;
			}
			if (!strcmp(cp, FSTAB_SW)) {
				_fs_fstab.fs_type = FSTAB_SW;
				break;
			}
			if (!strcmp(cp, FSTAB_XX)) {
				_fs_fstab.fs_type = FSTAB_XX;
I 13
				typexx++;
E 13
				break;
			}
E 12
E 11
E 10
		}
I 13
		if (typexx)
			continue;
E 13
I 12
		if (cp != NULL)
			return(1);
D 17
	bad:
E 12
I 11
		/* no way to distinguish between EOF and syntax error */
E 17
I 17

bad:		/* no way to distinguish between EOF and syntax error */
E 17
D 18
		(void)write(STDERR_FILENO, "fstab: ", 7);
		(void)write(STDERR_FILENO, _PATH_FSTAB,
		    sizeof(_PATH_FSTAB) - 1);
		(void)write(STDERR_FILENO, ": syntax error.\n", 16);
E 18
I 18
D 19
		write(EBADFORMAT);
E 19
I 19
D 20
		write(EFTYPE);
E 20
I 20
		error(EFTYPE);
E 20
E 19
E 18
E 11
E 8
	}
D 2
	if (*cp == '\0') return(0);
E 2
I 2
D 8
	if (*cp == '\0')
D 3
		return (0);
E 3
I 3
		return ((char *)0);
E 3
E 2
	*backp = value;
D 2
	while ( *cp && *cp != end)
E 2
I 2
	while (*cp && *cp != end)
E 2
		cp++;
D 2
	if (*cp == '\0') return(0);
	return(cp+1);
E 2
I 2
	if (*cp == '\0')
D 3
		return (0);
E 3
I 3
		return ((char *)0);
E 3
	return (cp+1);
E 8
I 8
	/* NOTREACHED */
E 8
E 2
}

D 2
static	int	fstabscan(fsp)
	struct	fstab *fsp;
E 2
I 2
D 8
static
fstabscan(fs)
	struct fstab *fs;
E 2
{
D 2
	register	char	*cp;
	char	buf[256];
	if (fgets(buf, 256, fs_file) == NULL)
		return(EOF);
	cp = buf;
	cp = fs_string(&fsp->fs_spec[0], cp, FSNMLG, ':');
	if (cp == 0)	return(0);
	cp = fs_string(&fsp->fs_file[0], cp, FSNMLG, ':');
	if (cp == 0)	return(1);
	cp = fs_string(&fsp->fs_type[0], cp, 3, ':');
	if (cp == 0)	return(2);
	cp = fs_digit(&fsp->fs_freq, cp, ':');
	if (cp == 0)	return(3);
	cp = fs_digit(&fsp->fs_passno, cp, '\n');
	if (cp == 0)	return(4);
	return(5);
E 2
I 2
	register char *cp;

	cp = fgets(line, 256, fs_file);
	if (cp == NULL)
		return (EOF);
	fs->fs_spec = cp;
	cp = fsskip(cp);
	fs->fs_file = cp;
	cp = fsskip(cp);
	fs->fs_type = cp;
	cp = fsskip(cp);
D 3
	fs->fs_quotafile = cp;
	cp = fsskip(cp);
E 3
	cp = fsdigit(&fs->fs_freq, cp, ':');
	if (cp == 0)
D 3
		return (4);
E 3
I 3
		return (3);
E 3
	cp = fsdigit(&fs->fs_passno, cp, '\n');
	if (cp == 0)
D 3
		return (5);
	return (6);
E 3
I 3
		return (4);
	return (5);
E 3
E 2
}
	
E 8
D 2
int	setfsent()
E 2
I 2
D 10
setfsent()
E 2
{
I 2
D 8

E 8
E 2
	if (fs_file)
D 8
		endfsent();
E 8
I 8
		(void)endfsent();
E 8
D 2
	if ( (fs_file = fopen(FSTAB, "r")) == NULL){
E 2
I 2
D 4
	if ((fs_file = fopen(FSTAB, "r")) == NULL){
E 4
I 4
	if ((fs_file = fopen(FSTAB, "r")) == NULL) {
E 4
E 2
D 8
		fs_file = 0;
D 2
		return(0);
E 2
I 2
		return (0);
E 8
I 8
		fs_file = NULL;
		return(0);
E 8
E 2
	}
D 2
	return(1);
E 2
I 2
D 8
	return (1);
E 8
I 8
	return(1);
E 8
E 2
}

D 2
int endfsent()
E 2
I 2
endfsent()
E 2
{
D 2
	if (fs_file){
E 2
I 2
D 8

E 8
D 4
	if (fs_file)
E 4
I 4
	if (fs_file) {
E 4
E 2
D 8
		fclose(fs_file);
I 4
		fs_file = 0;
E 8
I 8
		(void)fclose(fs_file);
		fs_file = NULL;
E 8
	}
E 4
D 2
	}
	return(1);
E 2
I 2
D 8
	return (1);
E 8
I 8
	return(1);
E 8
E 2
}

E 10
D 2
struct fstab *getfsent()
E 2
I 2
struct fstab *
getfsent()
E 2
{
D 2
	int	nfields;
E 2
I 2
D 8
	int nfields;
E 2

D 2
	if ( (fs_file == 0) && (setfsent() == 0) )
		return(0);
E 2
I 2
	if ((fs_file == 0) && (setfsent() == 0))
D 3
		return (0);
E 3
I 3
		return ((struct fstab *)0);
E 3
E 2
	nfields = fstabscan(&fs);
D 2
	if (nfields == EOF || nfields != FSTABNARGS)
		return(0);
	return(&fs);
E 2
I 2
D 3
	if (nfields == EOF || nfields != 6)
		return (0);
E 3
I 3
	if (nfields == EOF || nfields != 5)
		return ((struct fstab *)0);
E 3
	return (&fs);
E 8
I 8
D 10
	if (fs_file == NULL && !setfsent() || fstabscan(&fs))
E 10
I 10
	if (!_fs_fp && !setfsent() || !fstabscan())
E 10
		return((struct fstab *)NULL);
D 10
	return(&fs);
E 10
I 10
	return(&_fs_fstab);
E 10
E 8
E 2
}
D 2
struct fstab *getfsspec(name)
	char	*name;
E 2
I 2

struct fstab *
getfsspec(name)
D 8
	char *name;
E 8
I 8
D 20
	register char *name;
E 20
I 20
	register const char *name;
E 20
E 8
E 2
{
D 2
	register	struct	fstab *fsp;
E 2
I 2
D 10
	register struct fstab *fsp;

E 2
D 8
	if (setfsent() == 0)	/* start from the beginning */
D 2
		return(0);
	while( (fsp = getfsent()) != 0){
		if (strncmp(fsp->fs_spec, name, sizeof(fsp->fs_spec)) == 0)
			return(fsp);
	}
	return(0);
E 2
I 2
D 3
		return (0);
E 3
I 3
		return ((struct fstab *)0);
E 3
	while((fsp = getfsent()) != 0)
		if (strcmp(fsp->fs_spec, name) == 0)
			return (fsp);
D 3
	return (0);
E 3
I 3
	return ((struct fstab *)0);
E 8
I 8
	if (!setfsent())		/* start from the beginning */
		return((struct fstab *)NULL);
	while (fsp = getfsent())
		if (!strcmp(fsp->fs_spec, name))
			return(fsp);
E 10
I 10
	if (setfsent())
		while (fstabscan())
			if (!strcmp(_fs_fstab.fs_spec, name))
				return(&_fs_fstab);
E 10
	return((struct fstab *)NULL);
E 8
E 3
E 2
}
D 2
struct fstab *getfsfile(name)
	char	*name;
E 2
I 2

struct fstab *
getfsfile(name)
D 8
	char *name;
E 8
I 8
D 20
	register char *name;
E 20
I 20
	register const char *name;
E 20
E 8
E 2
{
D 2
	register	struct fstab *fsp;
E 2
I 2
D 10
	register struct fstab *fsp;

E 2
D 8
	if (setfsent() == 0)	/* start from the beginning */
D 2
		return(0);
	while ( (fsp = getfsent()) != 0){
		if (strncmp(fsp->fs_file, name, sizeof(fsp->fs_spec)) == 0)
			return(fsp);
	}
	return(0);
E 2
I 2
D 3
		return (0);
E 3
I 3
		return ((struct fstab *)0);
E 3
	while ((fsp = getfsent()) != 0)
		if (strcmp(fsp->fs_file, name) == 0)
			return (fsp);
D 3
	return (0);
E 3
I 3
	return ((struct fstab *)0);
}

struct fstab *
getfstype(type)
	char *type;
{
	register struct fstab *fs;

	if (setfsent() == 0)
		return ((struct fstab *)0);
	while ((fs = getfsent()) != 0)
		if (strcmp(fs->fs_type, type) == 0)
			return (fs);
	return ((struct fstab *)0);
E 8
I 8
	if (!setfsent())		/* start from the beginning */
		return((struct fstab *)NULL);
	while (fsp = getfsent())
		if (!strcmp(fsp->fs_file, name))
			return(fsp);
E 10
I 10
	if (setfsent())
		while (fstabscan())
			if (!strcmp(_fs_fstab.fs_file, name))
				return(&_fs_fstab);
E 10
	return((struct fstab *)NULL);
I 10
}

setfsent()
{
	if (_fs_fp) {
		rewind(_fs_fp);
		return(1);
	}
D 11
	return((_fs_fp = fopen(FSTAB, "r")) != NULL);
E 11
I 11
D 18
	return((_fs_fp = fopen(_PATH_FSTAB, "r")) != NULL);
E 18
I 18
	if (_fs_fp = fopen(_PATH_FSTAB, "r"))
		return(1);
	error(errno);
	return(0);
E 18
E 11
}

void
endfsent()
{
	if (_fs_fp) {
		(void)fclose(_fs_fp);
		_fs_fp = NULL;
	}
I 18
}

static
error(err)
	int err;
{
	char *p;

	(void)write(STDERR_FILENO, "fstab: ", 7);
	(void)write(STDERR_FILENO, _PATH_FSTAB, sizeof(_PATH_FSTAB) - 1);
I 22
	(void)write(STDERR_FILENO, ": ", 1);
E 22
	p = strerror(err);
	(void)write(STDERR_FILENO, p, strlen(p));
	(void)write(STDERR_FILENO, "\n", 1);
E 18
E 10
E 8
E 3
E 2
}
E 1
