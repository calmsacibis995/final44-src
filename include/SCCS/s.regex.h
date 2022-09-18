h22017
s 00001/00001/00079
d D 8.2 94/01/03 17:56:08 bostic 6 5
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00002/00002/00078
d D 8.1 93/06/02 20:06:20 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00078
d D 5.4 93/05/30 12:48:42 bostic 4 3
c include cdefs early on for the const in the regex_t
e
s 00032/00024/00048
d D 5.3 93/05/21 13:03:59 bostic 3 2
c Henry Spencer's Alpha 3.0 regex release
e
s 00011/00006/00061
d D 5.2 92/09/30 14:30:59 bostic 2 1
c convert to 4BSD style prototypes, includes
c alpha2.1 release from Henry Spencer
e
s 00067/00000/00000
d D 5.1 92/08/28 18:13:08 bostic 1 0
c date and time created 92/08/28 18:13:08 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Henry Spencer.
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Henry Spencer of the University of Toronto.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _REGEX_H_
#define	_REGEX_H_

I 4
#include <sys/cdefs.h>

E 4
/* types */
typedef off_t regoff_t;

typedef struct {
	int re_magic;
	size_t re_nsub;		/* number of parenthesized subexpressions */
I 3
D 6
	const char *re_endp;	/* end pointer for REG_PEND */
E 6
I 6
	__const char *re_endp;	/* end pointer for REG_PEND */
E 6
E 3
	struct re_guts *re_g;	/* none of your business :-) */
} regex_t;

typedef struct {
	regoff_t rm_so;		/* start of match */
	regoff_t rm_eo;		/* end of match */
} regmatch_t;

D 2
int	regcomp __P((regex_t *, const char *, int));
size_t	regerror __P((int, const regex_t *, char *, size_t));
int	regexec __P((const regex_t *,
	    const char *, size_t, regmatch_t [], int));
void	regfree __P((regex_t *));

E 2
/* regcomp() flags */
D 3
#define	REG_EXTENDED	001
#define	REG_ICASE	002
#define	REG_NOSUB	004
#define	REG_NEWLINE	010
E 3
I 3
#define	REG_BASIC	0000
#define	REG_EXTENDED	0001
#define	REG_ICASE	0002
#define	REG_NOSUB	0004
#define	REG_NEWLINE	0010
#define	REG_NOSPEC	0020
#define	REG_PEND	0040
#define	REG_DUMP	0200
E 3

I 3
/* regerror() flags */
#define	REG_NOMATCH	 1
#define	REG_BADPAT	 2
#define	REG_ECOLLATE	 3
#define	REG_ECTYPE	 4
#define	REG_EESCAPE	 5
#define	REG_ESUBREG	 6
#define	REG_EBRACK	 7
#define	REG_EPAREN	 8
#define	REG_EBRACE	 9
#define	REG_BADBR	10
#define	REG_ERANGE	11
#define	REG_ESPACE	12
#define	REG_BADRPT	13
#define	REG_EMPTY	14
#define	REG_ASSERT	15
#define	REG_INVARG	16
#define	REG_ATOI	255	/* convert name to number (!) */
#define	REG_ITOA	0400	/* convert number to name (!) */

E 3
/* regexec() flags */
#define	REG_NOTBOL	00001
#define	REG_NOTEOL	00002
#define	REG_STARTEND	00004
D 3
#define	REG_TRACE	00400	/* debugging tracing */
#define	REG_LARGE	01000	/* force large state model for debug */
I 2
#define	REG_BACKR	02000
E 2

/* errors */
#define	REG_NOMATCH	(1)
#define	REG_BADPAT	(2)
#define	REG_ECOLLATE	(3)
#define	REG_ECTYPE	(4)
#define	REG_EESCAPE	(5)
#define	REG_ESUBREG	(6)
#define	REG_EBRACK	(7)
#define	REG_EPAREN	(8)
#define	REG_EBRACE	(9)
#define	REG_BADBR	(10)
#define	REG_ERANGE	(11)
#define	REG_ESPACE	(12)
#define	REG_BADRPT	(13)
#define	REG_EMPTY	(14)	/* empty component */
#define	REG_ASSERT	(15)	/* assertion failure */
E 3
I 3
#define	REG_TRACE	00400	/* tracing of execution */
#define	REG_LARGE	01000	/* force large representation */
#define	REG_BACKR	02000	/* force use of backref code */
E 3
I 2
D 4

#include <sys/cdefs.h>
E 4

__BEGIN_DECLS
int	regcomp __P((regex_t *, const char *, int));
size_t	regerror __P((int, const regex_t *, char *, size_t));
int	regexec __P((const regex_t *,
	    const char *, size_t, regmatch_t [], int));
void	regfree __P((regex_t *));
__END_DECLS
E 2

#endif /* !_REGEX_H_ */
E 1
