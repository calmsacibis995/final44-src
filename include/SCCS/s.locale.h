h59311
s 00002/00002/00052
d D 8.1 93/06/02 20:05:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00007/00048
d D 5.2 91/02/24 10:40:28 bostic 2 1
c first pass at function prototypes with cdefs.h
e
s 00055/00000/00000
d D 5.1 91/02/18 00:39:04 torek 1 0
c date and time created 91/02/18 00:39:04 by torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _LOCALE_H_
#define _LOCALE_H_

struct lconv {
	char	*decimal_point;
	char	*thousands_sep;
	char	*grouping;
	char	*int_curr_symbol;
	char	*currency_symbol;
	char	*mon_decimal_point;
	char	*mon_thousands_sep;
	char	*mon_grouping;
	char	*positive_sign;
	char	*negative_sign;
	char	int_frac_digits;
	char	frac_digits;
	char	p_cs_precedes;
	char	p_sep_by_space;
	char	n_cs_precedes;
	char	n_sep_by_space;
	char	p_sign_posn;
	char	n_sign_posn;
};

#ifndef NULL
#define	NULL	0
#endif

#define	LC_ALL		0
#define	LC_COLLATE	1
#define	LC_CTYPE	2
#define	LC_MONETARY	3
#define	LC_NUMERIC	4
#define	LC_TIME		5

#define	_LC_LAST	6		/* marks end */

D 2
#if __STDC__ || c_plusplus
char	*setlocale(int _category, const char *_locale);
struct	lconv *localeconv(void);
#else
char	*setlocale();
struct	lconv *localeconv();
#endif
E 2
I 2
#include <sys/cdefs.h>

__BEGIN_DECLS
struct lconv	*localeconv __P((void));
char		*setlocale __P((int, const char *));
__END_DECLS
E 2

#endif /* _LOCALE_H_ */
E 1
