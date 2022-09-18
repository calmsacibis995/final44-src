h32231
s 00002/00002/00217
d D 8.2 94/04/18 14:02:30 bostic 4 3
c new version from Keith Muller (muller@sdcc3.ucsd.edu)
e
s 00002/00002/00217
d D 8.1 93/05/31 14:53:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00219
d D 1.2 93/05/21 14:36:44 bostic 2 1
c sys_errlist defined in stdio.h (in a complicated fashion...)
e
s 00220/00000/00000
d D 1.1 92/12/13 22:51:32 muller 1 0
c date and time created 92/12/13 22:51:32 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "pax.h"
#include "extern.h"
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

/*
 * routines that deal with I/O to and from the user
 */

#define DEVTTY          "/dev/tty"      /* device for interactive i/o */
static FILE *ttyoutf = NULL;		/* output pointing at control tty */
static FILE *ttyinf = NULL;		/* input pointing at control tty */
D 2
extern char *sys_errlist[];		/* errno printable strings */
E 2

/*
 * tty_init()
 *	try to open the controlling termina (if any) for this process. if the
 *	open fails, future ops that require user input will get an EOF
 */

#if __STDC__
int
tty_init(void)
#else
int
tty_init()
#endif
{
	int ttyfd;

        if ((ttyfd = open(DEVTTY, O_RDWR)) >= 0) {
		if ((ttyoutf = fdopen(ttyfd, "w")) != NULL) {
			if ((ttyinf = fdopen(ttyfd, "r")) != NULL)
				return(0);
			(void)fclose(ttyoutf);
		}
		(void)close(ttyfd);
	}

	if (iflag) {
		warn(1, "Fatal error, cannot open %s", DEVTTY);
		return(-1);
	}
	return(0);
}

/*
 * tty_prnt()
 *	print a message using the specified format to the controlling tty
 *	if there is no controlling terminal, just return.
 */

#if __STDC__
void
tty_prnt(char *fmt, ...)
#else
void
tty_prnt(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
#	if __STDC__
	va_start(ap, fmt);
#	else
	va_start(ap);
#	endif
	if (ttyoutf == NULL)
		return;
	(void)vfprintf(ttyoutf, fmt, ap);
	va_end(ap);
	(void)fflush(ttyoutf);
}

/*
 * tty_read()
 *	read a string from the controlling terminal if it is open into the
 *	supplied buffer
 * Return:
 *	0 if data was read, -1 otherwise.
 */

#if __STDC__
int
tty_read(char *str, int len)
#else
int
tty_read(str, len)
	char *str;
	int len;
#endif
{
	register char *pt;

	if ((--len <= 0) || (ttyinf == NULL) || (fgets(str,len,ttyinf) == NULL))
		return(-1);
	*(str + len) = '\0';

	/*
	 * strip off that trailing newline
	 */
	if ((pt = strchr(str, '\n')) != NULL)
		*pt = '\0';
	return(0);
}

/*
 * warn()
 *	write a warning message to stderr. if "set" the exit value of pax
 *	will be non-zero.
 */

#if __STDC__
void
warn(int set, char *fmt, ...)
#else
void
warn(set, fmt, va_alist)
	int set;
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
#	if __STDC__
	va_start(ap, fmt);
#	else
	va_start(ap);
#	endif
	if (set)
		exit_val = 1;
	/*
	 * when vflag we better ship out an extra \n to get this message on a
	 * line by itself
	 */
	if (vflag && vfpart) {
		(void)fputc('\n', stderr);
		vfpart = 0;
	}
D 4
	(void)fputs("pax: ", stderr);
E 4
I 4
	(void)fprintf(stderr, "%s: ", argv0);
E 4
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fputc('\n', stderr);
}

/*
 * syswarn()
 *	write a warning message to stderr. if "set" the exit value of pax
 *	will be non-zero.
 */

#if __STDC__
void
syswarn(int set, int errnum, char *fmt, ...)
#else
void
syswarn(set, errnum, fmt, va_alist)
	int set;
	int errnum;
	char *fmt;
	va_dcl
#endif
{
	va_list ap;
#	if __STDC__
	va_start(ap, fmt);
#	else
	va_start(ap);
#	endif
	if (set)
		exit_val = 1;
	/*
	 * when vflag we better ship out an extra \n to get this message on a
	 * line by itself
	 */
	if (vflag && vfpart) {
		(void)fputc('\n', stderr);
		vfpart = 0;
	}
D 4
	(void)fputs("pax: ", stderr);
E 4
I 4
	(void)fprintf(stderr, "%s: ", argv0);
E 4
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);

	/*
	 * format and print the errno
	 */
	if (errnum > 0)
		(void)fprintf(stderr, " <%s>", sys_errlist[errnum]);
	(void)fputc('\n', stderr);
}
E 1
