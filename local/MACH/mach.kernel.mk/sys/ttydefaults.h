/****************************************************************************
 * HISTORY
 * $Log:	ttydefaults.h,v $
 * Revision 2.2  91/02/15  21:12:13  mja
 * 	Undefine 4.3 conflicts during transition.
 * 
 ****************************************************************************/
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ttydefaults.h	7.7 (Berkeley) 7/1/90
 */

/*
 * System wide defaults for terminal state.
 */
#ifndef _TTYDEFAULTS_
#define	_TTYDEFAULTS_

/*
 * Defaults on "first" open.
 */
#define	TTYDEF_IFLAG	(BRKINT | ISTRIP | ICRNL | IMAXBEL | IXON | IXANY)
#define TTYDEF_OFLAG	(OPOST | ONLCR | OXTABS)
#define TTYDEF_LFLAG	(ECHO | ICANON | ISIG | IEXTEN | ECHOE|ECHOKE|ECHOCTL)
#define TTYDEF_CFLAG	(CREAD | CS7 | PARENB | HUPCL)
#define TTYDEF_SPEED	(B9600)

/*
 * Control Character Defaults
 */
#ifdef	CTRL	/* XXX 4.3 */
#undef	CTRL
#undef	CEOF
#undef	CERASE
#undef	CINTR
#undef	CKILL
#undef	CQUIT
#undef	CSUSP
#undef	CDSUSP
#undef	CSTART
#undef	CSTOP
#undef	CLNEXT
#undef	CWERASE
#undef	CEOT
#undef	CBRK
#undef	CRPRNT
#undef	CFLUSH
#endif		/* XXX 4.3 */
#define CTRL(x)	(x&037)
#define	CEOF		CTRL('d')
#define	CEOL		((unsigned)'\377')	/* XXX avoid _POSIX_VDISABLE */
#define	CERASE		0177
#define	CINTR		CTRL('c')
#define	CSTATUS		((unsigned)'\377')	/* XXX avoid _POSIX_VDISABLE */
#define	CKILL		CTRL('u')
#define	CMIN		1
#define	CQUIT		034		/* FS, ^\ */
#define	CSUSP		CTRL('z')
#define	CTIME		0
#define	CDSUSP		CTRL('y')
#define	CSTART		CTRL('q')
#define	CSTOP		CTRL('s')
#define	CLNEXT		CTRL('v')
#define	CDISCARD 	CTRL('o')
#define	CWERASE 	CTRL('w')
#define	CREPRINT 	CTRL('r')
#define	CEOT		CEOF
/* compat */
#define	CBRK		CEOL
#define CRPRNT		CREPRINT
#define	CFLUSH		CDISCARD

/* PROTECTED INCLUSION ENDS HERE */
#endif /* _TTYDEFAULTS_ */

/*
 * #define TTYDEFCHARS to include an array of default control characters.
 */
#ifdef TTYDEFCHARS
cc_t	ttydefchars[NCCS] = {
	CEOF,	CEOL,	CEOL,	CERASE, CWERASE, CKILL, CREPRINT, 
	_POSIX_VDISABLE, CINTR,	CQUIT,	CSUSP,	CDSUSP,	CSTART,	CSTOP,	CLNEXT,
	CDISCARD, CMIN,	CTIME,  CSTATUS, _POSIX_VDISABLE
};
#undef TTYDEFCHARS
#endif /* TTYDEFCHARS */
