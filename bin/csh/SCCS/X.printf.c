h10130
s 00002/00001/00283
d D 5.4 91/06/16 15:11:43 christos 4 3
c Added missing include files
e
s 00023/00005/00261
d D 5.3 91/06/08 17:08:59 christos 3 2
c More prototype fixes, Removed TERMIOS define
e
s 00003/00002/00263
d D 5.2 91/06/07 11:13:46 bostic 2 1
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00265/00000/00000
d D 5.1 91/06/04 16:55:17 christos 1 0
c date and time created 91/06/04 16:55:17 by christos
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * tc.printf.c: A public-domain, minimal printf/sprintf routine that prints
 *	       through the putchar() routine.  Feel free to use for
 *	       anything...  -- 7/17/87 Paul Placeway
 */
D 4

E 4
I 4
#include <strings.h>
#include <stdlib.h>
E 4
I 3
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif
E 3
D 2
#include "sh.h"
#include "sh.char.h"
E 2
I 2
#include "csh.h"
#include "char.h"
#include "extern.h"
E 2
D 3
#include <varargs.h>
E 3

#ifdef lint
#undef va_arg
#define va_arg(a, b) (a ? (b) 0 : (b) 0)
#endif

#define INF	32766		/* should be bigger than any field to print */

static unsigned char buf[128];

static void
doprnt(addchar, sfmt, ap)
    void    (*addchar) ();
    char   *sfmt;
    va_list ap;
{
    register unsigned char *f, *bp;
    register long l;
    register unsigned long u;
    register int i;
    register int fmt;
    register unsigned char pad = ' ';
    int     flush_left = 0, f_width = 0, prec = INF, hash = 0, do_long = 0;
    int     sign = 0;

    f = (unsigned char *) sfmt;
    for (; *f; f++) {
	if (*f != '%') {	/* then just out the char */
	    (*addchar) ((int) (*f));
	}
	else {
	    f++;		/* skip the % */

	    if (*f == '-') {	/* minus: flush left */
		flush_left = 1;
		f++;
	    }

	    if (*f == '0' || *f == '.') {
		/* padding with 0 rather than blank */
		pad = '0';
		f++;
	    }
	    if (*f == '*') {	/* field width */
		f_width = va_arg(ap, int);
		f++;
	    }
	    else if (Isdigit(*f)) {
		f_width = atoi((char *) f);
		while (Isdigit(*f))
		    f++;	/* skip the digits */
	    }

	    if (*f == '.') {	/* precision */
		f++;
		if (*f == '*') {
		    prec = va_arg(ap, int);
		    f++;
		}
		else if (Isdigit(*f)) {
		    prec = atoi((char *) f);
		    while (Isdigit(*f))
			f++;	/* skip the digits */
		}
	    }

	    if (*f == '#') {	/* alternate form */
		hash = 1;
		f++;
	    }

	    if (*f == 'l') {	/* long format */
		do_long = 1;
		f++;
	    }

	    fmt = *f;
	    if (Isupper(fmt)) {
		do_long = 1;
		fmt = Tolower(fmt);
	    }
	    bp = buf;
	    switch (fmt) {	/* do the format */
	    case 'd':
		if (do_long)
		    l = va_arg(ap, long);
		else
		    l = (long) (va_arg(ap, int));
		if (l < 0) {
		    sign = 1;
		    l = -l;
		}
		do {
		    *bp++ = l % 10 + '0';
		} while ((l /= 10) > 0);
		if (sign)
		    *bp++ = '-';
		f_width = f_width - (bp - buf);
		if (!flush_left)
		    while (f_width-- > 0)
			(*addchar) ((int) (pad));
		for (bp--; bp >= buf; bp--)
		    (*addchar) ((int) (*bp));
		if (flush_left)
		    while (f_width-- > 0)
			(*addchar) ((int) (' '));
		break;

	    case 'o':
	    case 'x':
	    case 'u':
		if (do_long)
		    u = va_arg(ap, unsigned long);
		else
		    u = (unsigned long) (va_arg(ap, unsigned));
		if (fmt == 'u') {	/* unsigned decimal */
		    do {
			*bp++ = u % 10 + '0';
		    } while ((u /= 10) > 0);
		}
		else if (fmt == 'o') {	/* octal */
		    do {
			*bp++ = u % 8 + '0';
		    } while ((u /= 8) > 0);
		    if (hash)
			*bp++ = '0';
		}
		else if (fmt == 'x') {	/* hex */
		    do {
			i = u % 16;
			if (i < 10)
			    *bp++ = i + '0';
			else
			    *bp++ = i - 10 + 'a';
		    } while ((u /= 16) > 0);
		    if (hash) {
			*bp++ = 'x';
			*bp++ = '0';
		    }
		}
		i = f_width - (bp - buf);
		if (!flush_left)
		    while (i-- > 0)
			(*addchar) ((int) (pad));
		for (bp--; bp >= buf; bp--)
		    (*addchar) ((int) (*bp));
		if (flush_left)
		    while (i-- > 0)
			(*addchar) ((int) (' '));
		break;


	    case 'c':
		i = va_arg(ap, int);
		(*addchar) ((int) (i));
		break;

	    case 's':
		bp = va_arg(ap, unsigned char *);
		if (!bp)
		    bp = (unsigned char *) "(nil)";
		f_width = f_width - strlen((char *) bp);
		if (!flush_left)
		    while (f_width-- > 0)
			(*addchar) ((int) (pad));
		for (i = 0; *bp && i < prec; i++) {
		    (*addchar) ((int) (*bp));
		    bp++;
		}
		if (flush_left)
		    while (f_width-- > 0)
			(*addchar) ((int) (' '));

		break;

	    case '%':
		(*addchar) ((int) ('%'));
		break;
	    }
	    flush_left = 0, f_width = 0, prec = INF, hash = 0, do_long = 0;
	    sign = 0;
	    pad = ' ';
	}
    }
}


static unsigned char *xstring;
static void
xaddchar(c)
    int     c;
{
    *xstring++ = c;
}


void
I 3
#if __STDC__
xsprintf(char *str, char *fmt, ...)
#else
E 3
xsprintf(str, fmt, va_alist)
    char   *str;
    char   *fmt;
D 3

va_dcl
E 3
I 3
    va_dcl
#endif
E 3
{
    va_list va;

I 3
#if __STDC__
    va_start(va, fmt);
#else
E 3
    va_start(va);
I 3
#endif
E 3
    xstring = (unsigned char *) str;
    doprnt(xaddchar, fmt, va);
    va_end(va);
    *xstring++ = '\0';
}


void
I 3
#if __STDC__
xprintf(char *fmt, ...)
#else
E 3
xprintf(fmt, va_alist)
    char   *fmt;
D 3

va_dcl
E 3
I 3
    va_dcl
#endif
E 3
{
    va_list va;

I 3
#if __STDC__
    va_start(va, fmt);
#else
E 3
    va_start(va);
I 3
#endif
E 3
    doprnt(xputchar, fmt, va);
    va_end(va);
}


void
xvprintf(fmt, va)
    char   *fmt;
    va_list va;
{
    doprnt(xputchar, fmt, va);
}

void
xvsprintf(str, fmt, va)
    char   *str;
    char   *fmt;
    va_list va;
{
    xstring = (unsigned char *) str;
    doprnt(xaddchar, fmt, va);
    *xstring++ = '\0';
}
E 1
