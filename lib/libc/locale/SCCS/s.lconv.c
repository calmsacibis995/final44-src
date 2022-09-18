h51754
s 00002/00002/00042
d D 8.1 93/06/04 12:43:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00043
d D 5.3 93/01/12 10:21:07 bostic 3 2
c empty has to be local for namespace reasons
e
s 00001/00000/00043
d D 5.2 91/02/24 10:41:04 bostic 2 1
c needs limits.h
e
s 00043/00000/00000
d D 5.1 91/02/18 00:45:06 torek 1 0
c date and time created 91/02/18 00:45:06 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
#include <limits.h>
E 2
#include <locale.h>

D 3
char	empty[] = "";
E 3
I 3
static char empty[] = "";
E 3

/*
 * Default (C) locale conversion.
 */
static struct lconv C_lconv = {
	".",			/* decimal_point */
	empty,			/* thousands_sep */
	empty,			/* grouping */
	empty,			/* int_curr_symbol */
	empty,			/* currency_symbol */
	empty,			/* mon_decimal_point */
	empty,			/* mon_thousands_sep */
	empty,			/* mon_grouping */
	empty,			/* positive_sign */
	empty,			/* negative_sign */
	CHAR_MAX,		/* int_frac_digits */
	CHAR_MAX,		/* frac_digits */
	CHAR_MAX,		/* p_cs_precedes */
	CHAR_MAX,		/* p_sep_by_space */
	CHAR_MAX,		/* n_cs_precedes */
	CHAR_MAX,		/* n_sep_by_space */
	CHAR_MAX,		/* p_sign_posn */
	CHAR_MAX,		/* n_sign_posn */
};

/*
 * Current locale conversion.
 */
struct lconv *__lconv = &C_lconv;
E 1
