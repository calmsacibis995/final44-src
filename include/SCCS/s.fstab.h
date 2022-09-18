h02855
s 00002/00002/00051
d D 8.1 93/06/02 20:05:26 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00048
d D 5.12 91/04/03 16:10:30 bostic 16 15
c protect all user-level include files against reinclusion
e
s 00009/00013/00039
d D 5.11 91/02/05 17:10:46 bostic 15 14
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00051
d D 5.10 90/06/01 14:00:36 bostic 14 13
c new copyright notice
e
s 00001/00001/00061
d D 5.9 90/05/29 19:26:45 bostic 13 12
c C++ wants the prototypes, too
e
s 00013/00005/00049
d D 5.8 90/03/06 15:41:13 bostic 12 11
c add ANSI C prototypes
e
s 00005/00005/00049
d D 5.7 89/08/18 18:09:14 mckusick 11 10
c reorder fields to be in same order as fstab itself
e
s 00002/00000/00052
d D 5.6 89/07/15 14:08:31 mckusick 10 9
c update for NFS fields (from Rick Macklem)
e
s 00013/00013/00039
d D 5.5 89/06/27 17:04:39 bostic 9 8
c minor reformat, add _PATH_ prefix to FSTAB, deprecate old version
e
s 00000/00001/00052
d D 5.4 88/09/17 11:37:39 bostic 8 7
c getfstype has been removed
e
s 00001/00001/00052
d D 5.3 88/09/16 17:10:04 bostic 7 6
c endfsent doesn't return anything
e
s 00013/00002/00040
d D 5.2 88/08/13 15:20:02 bostic 6 5
c add Berkeley copyright
e
s 00007/00001/00035
d D 5.1 85/05/30 09:36:18 dist 5 4
c Add copyright
e
s 00001/00001/00035
d D 4.4 83/05/24 13:46:46 sam 4 3
c typo....blast
e
s 00011/00008/00025
d D 4.3 83/05/24 10:39:55 sam 3 2
c quota file now fixed name, new type and function to search by type
e
s 00004/00009/00029
d D 4.2 83/05/19 17:41:42 sam 2 1
c byte the bullet and allow variable length names
e
s 00038/00000/00000
d D 4.1 83/05/03 13:47:58 sam 1 0
c date and time created 83/05/03 13:47:58 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 17
 * Copyright (c) 1980 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 14
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 5

I 16
#ifndef _FSTAB_H_
#define _FSTAB_H_

E 16
/*
D 9
 * File system table, see fstab (5)
E 9
I 9
 * File system table, see fstab(5).
E 9
 *
 * Used by dump, mount, umount, swapon, fsck, df, ...
 *
D 3
 * The fs_spec field is the block special name.
 * Programs that want to use the character special name must
 * create that name by prepending a 'r' after the right most slash.
E 3
I 3
D 9
 * The fs_spec field is the block special name.  Programs
 * that want to use the character special name must create
 * that name by prepending a 'r' after the right most slash.
 * Quota files are always named "quotas", so if type is "rq",
 * then use concatenation of fs_file and "quotas" to locate
E 9
I 9
D 11
 * The fs_spec field is the block special name.  Programs that want to use
 * the character special name must create that name by prepending a 'r'
E 11
I 11
 * For ufs fs_spec field is the block special name.  Programs that want to
 * use the character special name must create that name by prepending a 'r'
E 11
 * after the right most slash.  Quota files are always named "quotas", so
 * if type is "rq", then use concatenation of fs_file and "quotas" to locate
E 9
 * quota file.
E 3
 */
D 3

E 3
D 9
#define	FSTAB		"/etc/fstab"
E 9
I 9
#define	_PATH_FSTAB	"/etc/fstab"
#define	FSTAB		"/etc/fstab"	/* deprecated */
E 9
D 2
#define	FSNMLG		32
E 2

D 2
#define	FSTABFMT	"%32s:%32s:%2s:%d:%d\n"
#define	FSTABARG(p)	(p)->fs_spec, (p)->fs_file, \
			(p)->fs_type, &(p)->fs_freq, &(p)->fs_passno
#define FSTABNARGS	5

E 2
D 3
#define	FSTAB_RW	"rw"	/* read write device */
#define	FSTAB_RO	"ro"	/* read only device */
E 3
I 3
D 9
#define	FSTAB_RW	"rw"	/* read/write device */
D 4
#define	FSTAB_RQ	"rq",	/* read/write with quotas */
E 4
I 4
#define	FSTAB_RQ	"rq"	/* read/write with quotas */
E 4
#define	FSTAB_RO	"ro"	/* read-only device */
E 3
#define	FSTAB_SW	"sw"	/* swap device */
#define	FSTAB_XX	"xx"	/* ignore totally */
E 9
I 9
#define	FSTAB_RW	"rw"		/* read/write device */
#define	FSTAB_RQ	"rq"		/* read/write with quotas */
#define	FSTAB_RO	"ro"		/* read-only device */
#define	FSTAB_SW	"sw"		/* swap device */
#define	FSTAB_XX	"xx"		/* ignore totally */
E 9

D 9
struct	fstab{
E 9
I 9
struct fstab {
E 9
D 2
	char	fs_spec[FSNMLG];	/* block special device name */
	char	fs_file[FSNMLG];	/* file system path prefix */
	char	fs_type[3];		/* rw,ro,sw or xx */
E 2
I 2
	char	*fs_spec;		/* block special device name */
	char	*fs_file;		/* file system path prefix */
D 3
	char	*fs_type;		/* rw,ro,sw or xx */
	char	*fs_quotafile;		/* name of quota file if used */
E 3
I 3
D 11
	char	*fs_type;		/* FSTAB_* */
E 3
E 2
	int	fs_freq;		/* dump frequency, in days */
	int	fs_passno;		/* pass number on parallel dump */
E 11
I 10
	char	*fs_vfstype;		/* File system type, ufs, nfs */
	char	*fs_mntops;		/* Mount options ala -o */
I 11
	char	*fs_type;		/* FSTAB_* from fs_mntops */
	int	fs_freq;		/* dump frequency, in days */
	int	fs_passno;		/* pass number on parallel dump */
E 11
E 10
};

D 12
struct	fstab *getfsent();
struct	fstab *getfsspec();
struct	fstab *getfsfile();
I 3
D 8
struct	fstab *getfstype();
E 8
E 3
int	setfsent();
D 7
int	endfsent();
E 7
I 7
void	endfsent();
E 12
I 12
D 13
#ifdef __STDC__
E 13
I 13
D 15
#if __STDC__ || c_plusplus
E 13
extern struct fstab *getfsent(void);
extern struct fstab *getfsspec(const char *);
extern struct fstab *getfsfile(const char *);
extern int setfsent(void);
extern void endfsent(void);
#else
extern struct fstab *getfsent();
extern struct fstab *getfsspec();
extern struct fstab *getfsfile();
extern int setfsent();
extern void endfsent();
#endif
E 15
I 15
#include <sys/cdefs.h>

__BEGIN_DECLS
struct fstab *getfsent __P((void));
struct fstab *getfsspec __P((const char *));
struct fstab *getfsfile __P((const char *));
int setfsent __P((void));
void endfsent __P((void));
__END_DECLS
I 16

#endif /* !_FSTAB_H_ */
E 16
E 15
E 12
E 7
E 1
