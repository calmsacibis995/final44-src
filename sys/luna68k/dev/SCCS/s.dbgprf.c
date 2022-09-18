h60980
s 00002/00002/00160
d D 8.1 93/06/10 22:16:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00159
d D 7.2 92/10/11 10:57:16 bostic 2 1
c make kernel includes standard
e
s 00162/00000/00000
d D 7.1 92/06/15 06:45:44 fujita 1 0
c date and time created 92/06/15 06:45:44 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
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
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * dbgprf.c -- batched printf for device driver debugging
 * by A.Fujita, May-3-1992
 */

#ifdef DEBUGPRINT

D 2
#include "sys/param.h"
#include "sys/systm.h"
E 2
I 2
#include <sys/param.h>
#include <sys/systm.h>
E 2

D 2
#include "machine/stdarg.h"
E 2
I 2
#include <machine/stdarg.h>
E 2

static char *sprintn __P((u_long num, int base, int *len));

#define DBG_LINES	 80
#define DBG_BUFS	300

struct dbgprf {
	struct dbgprf *dbg_forw;
	struct dbgprf *dbg_back;
	char dbg_buf[DBG_LINES];
};

struct dbgprf dbgprf[DBG_BUFS];

struct dbgprf dbgroot = {
	&dbgroot,
	&dbgroot,
};

int dbg_used = 0;

void
dbgprintall()
{
	register struct dbgprf *dbgp;

	for (dbgp = dbgroot.dbg_forw; dbgp != &dbgroot; dbgp = dbgp->dbg_forw) {
		printf("%s", dbgp->dbg_buf);
	}
}

void
#ifdef __STDC__
dbgprintf(const char *cfmt, ...)
#else
dbgprintf(cfmt /*, va_alist */)
	char *cfmt;
#endif
{
	register struct dbgprf *dbgp;
	register const char *fmt = cfmt;
	register char *p, *bp;
	register int ch, base;
	u_long ul;
	int lflag;
	va_list ap;

	if (dbg_used < DBG_BUFS) {
		dbgp = &dbgprf[dbg_used++];
	} else {
		dbgp = dbgroot.dbg_forw;
		remque(dbgp);
	}

	va_start(ap, cfmt);
	for (bp = dbgp->dbg_buf; ; ) {
		while ((ch = *(u_char *)fmt++) != '%')
			if ((*bp++ = ch) == '\0')
				goto done;

		lflag = 0;
reswitch:	switch (ch = *(u_char *)fmt++) {
		case 'l':
			lflag = 1;
			goto reswitch;
		case 'c':
			*bp++ = va_arg(ap, int);
			break;
		case 's':
			p = va_arg(ap, char *);
			while (*bp++ = *p++)
				;
			--bp;
			break;
		case 'd':
			ul = lflag ? va_arg(ap, long) : va_arg(ap, int);
			if ((long)ul < 0) {
				*bp++ = '-';
				ul = -(long)ul;
			}
			base = 10;
			goto number;
			break;
		case 'o':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 8;
			goto number;
			break;
		case 'u':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 10;
			goto number;
			break;
		case 'x':
			ul = lflag ? va_arg(ap, u_long) : va_arg(ap, u_int);
			base = 16;
number:			for (p = sprintn(ul, base, NULL); ch = *p--;)
				*bp++ = ch;
			break;
		default:
			*bp++ = '%';
			if (lflag)
				*bp++ = 'l';
			/* FALLTHROUGH */
		case '%':
			*bp++ = ch;
		}
	}
	va_end(ap);

 done:
	insque(dbgp, dbgroot.dbg_back);

/*	printf("%s", dbgp->dbg_buf);	*/
}

/*
 * Put a number (base <= 16) in a buffer in reverse order; return an
 * optional length and a pointer to the NULL terminated (preceded?)
 * buffer.
 */
static char *
sprintn(ul, base, lenp)
	register u_long ul;
	register int base, *lenp;
{					/* A long in base 8, plus NULL. */
	static char buf[sizeof(long) * NBBY / 3 + 2];
	register char *p;

	p = buf;
	do {
		*++p = "0123456789abcdef"[ul % base];
	} while (ul /= base);
	if (lenp)
		*lenp = p - buf;
	return (p);
}
#endif
E 1
