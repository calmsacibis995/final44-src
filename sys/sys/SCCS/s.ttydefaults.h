h04257
s 00005/00000/00065
d D 8.4 94/01/21 17:25:24 bostic 17 16
c add USL's copyright notice
e
s 00004/00004/00061
d D 8.3 94/01/04 16:16:54 bostic 16 15
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00063
d D 8.2 93/11/30 16:26:01 mckusick 15 14
c lint
e
s 00002/00002/00063
d D 8.1 93/06/02 19:56:14 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00060
d D 7.9 91/05/09 20:55:53 bostic 13 12
c new copyright; att/bsd/shared
e
s 00003/00003/00061
d D 7.8 91/02/05 17:04:20 bostic 12 11
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00002/00002/00062
d D 7.7 90/07/01 00:33:09 marc 11 10
c add IXANY, crt erase/kill/ctlecho to default modes
e
s 00001/00000/00063
d D 7.6 90/06/21 16:30:53 marc 10 9
c put back CFLUSH as compatability
e
s 00001/00001/00062
d D 7.5 90/06/20 18:51:59 marc 9 8
c NCC -> NCCS
e
s 00002/00002/00061
d D 7.4 90/06/20 18:15:25 marc 8 7
c CINFO -> CSTATYS
e
s 00002/00003/00061
d D 7.3 90/06/15 14:02:19 marc 7 6
c CFLUSHO -> CDISCARD
e
s 00023/00023/00041
d D 7.2 89/11/20 18:13:45 marc 6 5
c more posix
e
s 00003/00003/00061
d D 7.1 89/09/04 15:04:33 karels 5 4
c IEXTEN is in lflag
e
s 00002/00001/00062
d D 1.4 89/09/04 15:03:31 sklower 4 3
c (checked in by karels) dunno what this is for
e
s 00003/00009/00060
d D 1.3 88/12/19 20:10:40 marc 3 2
c put back 4.3 style defaults
e
s 00009/00010/00060
d D 1.2 88/10/18 15:24:00 marc 2 1
c new terminal driver
e
s 00070/00000/00000
d D 1.1 88/03/25 17:38:10 marc 1 0
c date and time created 88/03/25 17:38:10 by marc
e
u
U
t
T
I 1
D 13
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
/*-
D 14
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
I 17
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 17
E 14
 *
 * %sccs.include.redist.c%
E 13
 *
D 3
 *	%W% (Berkeley) %G%
E 3
I 3
D 4
 *	@(#)ttydefaults.h	1.2 (Berkeley) 10/18/88
E 4
I 4
 *	%W% (Berkeley) %G%
E 4
E 3
 */

/*
D 6
 * System wide defaults of terminal state.
E 6
I 6
 * System wide defaults for terminal state.
E 6
 */
D 12
#ifndef _TTYDEFAULTS_
#define	_TTYDEFAULTS_
E 12
I 12
D 16
#ifndef _TTYDEFAULTS_H_
#define	_TTYDEFAULTS_H_
E 16
I 16
#ifndef _SYS_TTYDEFAULTS_H_
#define	_SYS_TTYDEFAULTS_H_
E 16
E 12

D 6
#define CTRL(x)	(x&037)
E 6
/*
I 6
 * Defaults on "first" open.
 */
D 11
#define	TTYDEF_IFLAG	(BRKINT | ISTRIP | ICRNL | IMAXBEL | IXON)
E 11
I 11
#define	TTYDEF_IFLAG	(BRKINT | ISTRIP | ICRNL | IMAXBEL | IXON | IXANY)
E 11
#define TTYDEF_OFLAG	(OPOST | ONLCR | OXTABS)
D 11
#define TTYDEF_LFLAG	(ECHO | ICANON | ISIG | IEXTEN)
E 11
I 11
#define TTYDEF_LFLAG	(ECHO | ICANON | ISIG | IEXTEN | ECHOE|ECHOKE|ECHOCTL)
E 11
#define TTYDEF_CFLAG	(CREAD | CS7 | PARENB | HUPCL)
#define TTYDEF_SPEED	(B9600)

/*
E 6
 * Control Character Defaults
 */
I 6
#define CTRL(x)	(x&037)
E 6
#define	CEOF		CTRL('d')
D 2
#define	CEOL		POSIX_V_DISABLE
E 2
I 2
D 6
#define	CEOL		_POSIX_VDISABLE
E 6
I 6
D 15
#define	CEOL		((unsigned)'\377')	/* XXX avoid _POSIX_VDISABLE */
E 15
I 15
#define	CEOL		((unsigned char)'\377')	/* XXX avoid _POSIX_VDISABLE */
E 15
E 6
E 2
D 3
#ifdef DECSTYLE_DEFAULTS
E 3
#define	CERASE		0177
D 2
#define	CINTR		CTRL('c')	
#define	CKILL		CTRL('u')
E 2
I 2
#define	CINTR		CTRL('c')
E 2
D 3
#else
#define	CERASE		CTRL('h')
#define	CINTR		0177
D 2
#define	CKILL		CTRL('x')
E 2
#endif
E 3
I 2
D 6
#define	CERASE2		_POSIX_VDISABLE
E 6
I 6
D 8
#define	CINFO		((unsigned)'\377')	/* XXX avoid _POSIX_VDISABLE */
E 8
I 8
D 15
#define	CSTATUS		((unsigned)'\377')	/* XXX avoid _POSIX_VDISABLE */
E 15
I 15
#define	CSTATUS		((unsigned char)'\377')	/* XXX avoid _POSIX_VDISABLE */
E 15
E 8
E 6
#define	CKILL		CTRL('u')
E 2
#define	CMIN		1
D 3
#define	CQUIT		034	/* FS, ^\ */
E 3
I 3
#define	CQUIT		034		/* FS, ^\ */
E 3
#define	CSUSP		CTRL('z')
D 2
#define	CTIME		1
E 2
I 2
#define	CTIME		0
E 2
#define	CDSUSP		CTRL('y')
#define	CSTART		CTRL('q')
#define	CSTOP		CTRL('s')
#define	CLNEXT		CTRL('v')
D 7
#define	CFLUSHO 	CTRL('o')
E 7
I 7
#define	CDISCARD 	CTRL('o')
E 7
#define	CWERASE 	CTRL('w')
#define	CREPRINT 	CTRL('r')
I 4
D 6
#define CQUOTE		'\\'
E 6
E 4
D 3
#define CQUOTE		'\\'
E 3
#define	CEOT		CEOF
D 6

D 2
#ifdef COMPAT_43
E 2
I 2
D 5
/* COMPAT_43 */
E 5
I 5
/* aliases */
E 6
I 6
/* compat */
E 6
E 5
E 2
#define	CBRK		CEOL
#define CRPRNT		CREPRINT
I 10
#define	CFLUSH		CDISCARD
E 10
D 7
#define CFLUSH		CFLUSHO
E 7
D 2
#endif
E 2

D 6
/*
 * Settings on first open of a tty.
 */
D 2
#define	TTYDEF_IFLAG	(BRKINT | ISTRIP | IMAXBEL | IEXTEN)
E 2
I 2
D 5
#define	TTYDEF_IFLAG	(BRKINT | ISTRIP | IMAXBEL | IEXTEN | IXON)
E 5
I 5
#define	TTYDEF_IFLAG	(BRKINT | ISTRIP | IMAXBEL | IXON)
E 5
E 2
#define TTYDEF_OFLAG	(0)
D 5
#define TTYDEF_LFLAG	(ECHO | ICANON | ISIG)
E 5
I 5
#define TTYDEF_LFLAG	(ECHO | ICANON | ISIG | IEXTEN)
E 5
D 3
#define TTYDEF_CFLAG	(CREAD | CS7 | PARENB)
E 3
I 3
#define TTYDEF_CFLAG	(CREAD | CS7 | PARENB | HUPCL)
E 3
#define TTYDEF_SPEED	(B9600)
E 6
I 6
/* PROTECTED INCLUSION ENDS HERE */
D 12
#endif /* _TTYDEFAULTS_ */
E 12
I 12
D 16
#endif /* !_TTYDEFAULTS_H_ */
E 16
I 16
#endif /* !_SYS_TTYDEFAULTS_H_ */
E 16
E 12
E 6

D 6
#endif /*_TTYDEFAULTS_*/

E 6
/*
D 2
 * Define TTYDEFCHARS to include an array of default control characters.
E 2
I 2
D 6
 * define TTYDEFCHARS to include an array of default control characters.
E 6
I 6
 * #define TTYDEFCHARS to include an array of default control characters.
E 6
E 2
 */
#ifdef TTYDEFCHARS
D 6
u_char	ttydefchars[NCC] = {
	CEOF,	CEOL,	CEOL,	CERASE, CWERASE, CKILL, CREPRINT, CQUOTE,
	CINTR,	CQUIT,	CSUSP,	CDSUSP,	CSTART,	CSTOP,	CLNEXT,
D 2
	CFLUSHO, CMIN,	CTIME, POSIX_V_DISABLE, POSIX_V_DISABLE
E 2
I 2
	CFLUSHO, CMIN,	CTIME, CERASE2, _POSIX_VDISABLE
E 6
I 6
D 9
cc_t	ttydefchars[NCC] = {
E 9
I 9
cc_t	ttydefchars[NCCS] = {
E 9
	CEOF,	CEOL,	CEOL,	CERASE, CWERASE, CKILL, CREPRINT, 
	_POSIX_VDISABLE, CINTR,	CQUIT,	CSUSP,	CDSUSP,	CSTART,	CSTOP,	CLNEXT,
D 7
	CFLUSHO, CMIN,	CTIME,  CINFO, _POSIX_VDISABLE
E 7
I 7
D 8
	CDISCARD, CMIN,	CTIME,  CINFO, _POSIX_VDISABLE
E 8
I 8
	CDISCARD, CMIN,	CTIME,  CSTATUS, _POSIX_VDISABLE
E 8
E 7
E 6
E 2
};
D 6
#endif /*TTYDEFCHARS*/
E 6
I 6
#undef TTYDEFCHARS
D 16
#endif /* TTYDEFCHARS */
E 16
I 16
#endif
E 16
E 6
E 1
