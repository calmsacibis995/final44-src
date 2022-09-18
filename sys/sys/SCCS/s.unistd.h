h48924
s 00005/00003/00093
d D 8.2 94/01/07 17:01:11 bostic 21 20
c Chuck Karish of Mindcraft says that POSIX.1 requires that _POSIX_NO_TRUNC
c and _POSIX_CHOWN_RESTRICTED have to have values, and I think I agree.  4BSD
c "provides" both options, so we can use anything other than -1, and 0 seems
c 0 seems unsafe.
e
s 00002/00002/00094
d D 8.1 93/06/02 19:56:37 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00094
d D 5.17 93/05/23 13:38:54 bostic 19 18
c add _SC_STREAM_MAX and _SC_TZNAME_MAX for POSIX 1003.1
e
s 00009/00001/00085
d D 5.16 93/05/06 10:48:19 bostic 18 17
c describe the _POSIX_SAVED_IDS behavior
e
s 00038/00017/00048
d D 5.15 93/05/04 08:59:37 bostic 17 14
c fold rest of POSIX 1003.1, 1003.2 configurable system variables into sysctl
e
s 00005/00001/00073
d R 5.16 92/05/13 14:45:56 mckusick 16 15
c temporary change of lseek prototype from off_t to long
e
s 00009/00000/00065
d R 5.15 92/04/21 10:31:22 mckusick 15 14
c add definitions for lseek and access system calls
e
s 00003/00001/00062
d D 5.14 91/04/01 14:12:42 bostic 14 13
c shut gcc up (warning: `/*' within comment)
e
s 00003/00088/00060
d D 5.13 91/02/22 11:34:07 bostic 13 12
c break unistd.h up into <unistd.h> and <sys/unistd.h>
e
s 00011/00001/00137
d D 5.12 91/02/22 09:46:26 karels 12 11
c move old lseek values here from sys/file.h; #ifdef KERNEL prototypes
e
s 00000/00001/00138
d D 5.11 91/02/19 15:19:01 bostic 11 10
c 1990 POSIX.1 revision moved ctermid to <stdio.h>
e
s 00063/00003/00076
d D 5.10 91/02/18 16:47:49 donn 10 9
c A working version that contains declarations for POSIX functions.
e
s 00012/00009/00067
d D 5.9 91/02/05 17:04:01 bostic 9 8
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00010/00000/00066
d D 5.8 91/01/21 06:53:42 bostic 8 7
c add cuserid, ctermid, getlogin for POSIX 1003.1
e
s 00001/00011/00065
d D 5.7 90/06/28 22:01:50 bostic 7 6
c new copyright notice
e
s 00007/00006/00069
d D 5.6 90/05/13 16:58:11 bostic 6 5
c correct POSIX #defines, add value for _POSIX_VDISABLE
e
s 00003/00003/00072
d D 5.5 90/05/13 15:46:19 bostic 5 4
c access flags are really bit fields
e
s 00010/00004/00065
d D 5.4 89/10/08 12:03:56 bostic 4 3
c add fnmatch constants; proposed POSIX 1003.2
e
s 00002/00000/00067
d D 5.3 89/08/16 12:00:09 bostic 3 2
c lots of other places define NULL
e
s 00002/00000/00065
d D 5.2 89/05/24 18:22:30 bostic 2 1
c have to define NULL here
e
s 00065/00000/00000
d D 5.1 89/05/20 14:58:44 bostic 1 0
c date and time created 89/05/20 14:58:44 by bostic
e
u
U
t
T
I 1
/*
D 20
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */

I 9
D 13
#ifndef _UNISTD_H_
#define	_UNISTD_H_
E 13
I 13
#ifndef _SYS_UNISTD_H_
#define	_SYS_UNISTD_H_
E 13

E 9
/* compile-time symbolic constants */
D 6
#define	POSIX_JOB_CONTROL	/* implementation supports job control */
#define	POSIX_SAVED_IDS		/* saved set-user-ID and set-group-ID */
#define	POSIX_VERSION		198808L
E 6
I 6
#define	_POSIX_JOB_CONTROL	/* implementation supports job control */
D 14
/*#define	_POSIX_SAVED_IDS	/* saved set-user-ID and set-group-ID */
E 14
I 14
D 18
#ifdef _NOTYET
E 18
I 18

/*
 * Although we have saved user/group IDs, we do not use them in setuid
 * as described in POSIX 1003.1, because the feature does not work for
 * root.  We use the saved IDs in seteuid/setegid, which are not currently
 * part of the POSIX 1003.1 specification.
 */
#ifdef	_NOT_AVAILABLE
E 18
#define	_POSIX_SAVED_IDS	/* saved set-user-ID and set-group-ID */
#endif
I 18

E 18
E 14
#define	_POSIX_VERSION		198808L
I 17
#define	_POSIX2_VERSION		199212L
E 17
E 6

/* execution-time symbolic constants */
D 6
#define	POSIX_CHOWN_RESTRICTED	/* chown requires appropriate privileges */
#define	POSIX_NO_TRUNC		/* too-long path components generate errors */
#define	POSIX_VDISABLE		/* may disable terminal special characters */
E 6
I 6
D 21
#define	_POSIX_CHOWN_RESTRICTED	/* chown requires appropriate privileges */
#define	_POSIX_NO_TRUNC		/* too-long path components generate errors */
E 21
I 21
				/* chown requires appropriate privileges */
#define	_POSIX_CHOWN_RESTRICTED	1
				/* too-long path components generate errors */
#define	_POSIX_NO_TRUNC		1
E 21
				/* may disable terminal special characters */
D 21
#define	_POSIX_VDISABLE	((unsigned char)'\377')
E 21
I 21
#define	_POSIX_VDISABLE		((unsigned char)'\377')
E 21
E 6

/* access function */
D 5
#define	R_OK		4	/* test for read permission */
#define	W_OK		2	/* test for write permission */
#define	X_OK		1	/* test for execute or search permission */
E 5
#define	F_OK		0	/* test for existence of file */
I 5
#define	X_OK		0x01	/* test for execute or search permission */
#define	W_OK		0x02	/* test for write permission */
#define	R_OK		0x04	/* test for read permission */
E 5

D 12
/* lseek function */
E 12
I 12
/* whence values for lseek(2) */
E 12
#define	SEEK_SET	0	/* set file offset to offset */
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#define	SEEK_END	2	/* set file offset to EOF plus offset */

I 12
#ifndef _POSIX_SOURCE
/* whence values for lseek(2); renamed by POSIX 1003.1 */
#define	L_SET		SEEK_SET
#define	L_INCR		SEEK_CUR
#define	L_XTND		SEEK_END
#endif

E 12
D 13
/* map a stream pointer to a file descriptor */
D 4
#define	STDIN_FILENO		0	/* standard input value, stdin */
#define	STDOUT_FILENO		1	/* standard output value, stdout */
#define	STDERR_FILENO		2	/* standard error value, stdout */
E 4
I 4
#define	STDIN_FILENO	0	/* standard input value, stdin */
#define	STDOUT_FILENO	1	/* standard output value, stdout */
#define	STDERR_FILENO	2	/* standard error value, stdout */
E 4

I 4
/* fnmatch function */
#define	FNM_PATHNAME	0x01	/* match pathnames, not filenames */
#ifndef _POSIX_SOURCE
#define	FNM_QUOTE	0x02	/* escape special chars with \ */
#endif

E 4
I 3
#ifndef NULL
E 3
I 2
D 4
#define	NULL	0			/* null pointer constant */
E 4
I 4
#define	NULL		0	/* null pointer constant */
E 4
I 3
#endif
E 3

E 13
E 2
/* configurable pathname variables */
D 17
#define	_PC_LINK_MAX		1
#define	_PC_MAX_CANON		2
#define	_PC_MAX_INPUT		3
#define	_PC_NAME_MAX		4
#define	_PC_PATH_MAX		5
#define	_PC_PIPE_BUF		6
#define	_PC_CHOWN_RESTRICTED	7
#define	_PC_NO_TRUNC		8
#define	_PC_VDISABLE		9
E 17
I 17
#define	_PC_LINK_MAX		 1
#define	_PC_MAX_CANON		 2
#define	_PC_MAX_INPUT		 3
#define	_PC_NAME_MAX		 4
#define	_PC_PATH_MAX		 5
#define	_PC_PIPE_BUF		 6
#define	_PC_CHOWN_RESTRICTED	 7
#define	_PC_NO_TRUNC		 8
#define	_PC_VDISABLE		 9
E 17

/* configurable system variables */
D 17
#define	_SC_ARG_MAX		1
#define	_SC_CHILD_MAX		2
#define	_SC_CLK_TCK		3
#define	_SC_NGROUPS_MAX		4
#define	_SC_OPEN_MAX		5
#define	_SC_JOB_CONTROL		6
#define	_SC_SAVED_IDS		7
#define	_SC_VERSION		8
E 17
I 17
#define	_SC_ARG_MAX		 1
#define	_SC_CHILD_MAX		 2
#define	_SC_CLK_TCK		 3
#define	_SC_NGROUPS_MAX		 4
#define	_SC_OPEN_MAX		 5
#define	_SC_JOB_CONTROL		 6
#define	_SC_SAVED_IDS		 7
#define	_SC_VERSION		 8
#define	_SC_BC_BASE_MAX		 9
#define	_SC_BC_DIM_MAX		10
#define	_SC_BC_SCALE_MAX	11
#define	_SC_BC_STRING_MAX	12
#define	_SC_COLL_WEIGHTS_MAX	13
#define	_SC_EXPR_NEST_MAX	14
#define	_SC_LINE_MAX		15
#define	_SC_RE_DUP_MAX		16
#define	_SC_2_VERSION		17
#define	_SC_2_C_BIND		18
#define	_SC_2_C_DEV		19
#define	_SC_2_CHAR_TERM		20
#define	_SC_2_FORT_DEV		21
#define	_SC_2_FORT_RUN		22
#define	_SC_2_LOCALEDEF		23
#define	_SC_2_SW_DEV		24
#define	_SC_2_UPE		25
I 19
#define	_SC_STREAM_MAX		26
#define	_SC_TZNAME_MAX		27
E 19

/* configurable system strings */
#define	_CS_PATH		 1
E 17
I 8

I 10
D 13
/* POSIX.1 2.5 specifically requires that unistd.h define size_t */
#include <sys/types.h>

#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
#endif

/* ugly, but the only reasonable value for the time being */
typedef	int		ssize_t;		/* what read() returns */

I 12
#ifndef KERNEL
E 12
E 10
D 9
#if __STDC__ || c_plusplus
char	*cuserid(const char *);
char	*ctermid();
char	*getlogin(void);
#else
char	*cuserid();
char	*ctermid();
char	*getlogin();
#endif
E 9
I 9
#include <sys/cdefs.h>

__BEGIN_DECLS
D 10
char	*getlogin __P((void));
char	*ctermid __P(());
char	*cuserid __P((const char *));
E 10
I 10
void volatile	_exit __P((int));
int		access __P((const char *, int));
unsigned int	alarm __P((unsigned int));
int		chdir __P((const char *));
int		chown __P((const char *, uid_t, gid_t));
int		close __P((int));
D 11
char		*ctermid __P((char *));		/* not yet implemented */
E 11
char		*cuserid __P((const char *));
int		dup __P((int));
int		dup2 __P((int, int));
int		execl __P((const char *, const char *, ...));
int		execle __P((const char *, const char *, ...));
int		execlp __P((const char *, const char *, ...));
int		execv __P((const char *, char * const *));
int		execve __P((const char *, char * const *, char * const *));
int		execvp __P((const char *, char * const *));
pid_t		fork __P((void));
long		fpathconf __P((int, int));	/* not yet implemented */
char		*getcwd __P((char *, size_t));
gid_t		getegid __P((void));
uid_t		geteuid __P((void));
gid_t		getgid __P((void));
int		getgroups __P((int, gid_t *));
char		*getlogin __P((void));
pid_t		getpgrp __P((void));
pid_t		getpid __P((void));
pid_t		getppid __P((void));
uid_t		getuid __P((void));
int		isatty __P((int));
int		link __P((const char *, const char *));
off_t		lseek __P((int, off_t, int));
long		pathconf __P((const char *, int));	/* not yet */
int		pause __P((void));
int		pipe __P((int *));
ssize_t		read __P((int, void *, size_t));
int		rmdir __P((const char *));
int		setgid __P((gid_t));
int		setpgid __P((pid_t, pid_t));
pid_t		setsid __P((void));
int		setuid __P((uid_t));
unsigned int	sleep __P((unsigned int));
long		sysconf __P((int));			/* not yet */
pid_t		tcgetpgrp __P((int));
pid_t		tcsetpgrp __P((int, pid_t));
char		*ttyname __P((int));
int		unlink __P((const char *));
ssize_t		write __P((int, const void *, size_t));

#ifndef	_POSIX_SOURCE
/* a number of BSD-specific declarations will go here */
#endif
I 12

#endif /* KERNEL */
E 12

E 10
__END_DECLS

#endif /* !_UNISTD_H_ */
E 13
I 13
#endif /* !_SYS_UNISTD_H_ */
E 13
E 9
E 8
E 1
