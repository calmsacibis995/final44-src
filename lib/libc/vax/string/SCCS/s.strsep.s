h63234
s 00002/00002/00057
d D 8.1 93/06/04 15:41:47 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00059/00000/00000
d D 5.1 90/05/15 21:34:43 bostic 1 0
c date and time created 90/05/15 21:34:43 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/*
 * Get next word from string *stringp, where words are
 * strings separated by characters from delim.
 *
 * Writes NULs into the string at *stringp to end tokens.
 * On return, *stringp points past the last NUL written (if there might
 * be further tokens), or is NULL (if there are definitely no more tokens).
 *
 * If *stringp is NULL, strtoken returns NULL.
 *
 * char *
 * strtoken(stringp, delim)
 *	register char **stringp;
 *	register char const *delim;
 */
#include "DEFS.h"

ENTRY(strsep, 0)
	tstl	*4(ap)		/* if (*stringp == NULL) */
	bneq	0f
	clrl	r0		#	return (NULL);
	ret

0:
	subl2	$32,sp		/* make room for 256 bit table */
	movc5	$0,(sp),$0,$32,(sp)
	movq	4(ap),r1	/* r1 = stringp, r2 = delim */

	/* turn on bit for each character in s2, including '\0' */
1:
	movzbl	(r2)+,r0
	bbss	r0,(sp),1b
	bneq	1b

	movl	(r1),r3		/* r3 = s = *stringp */
	movl	r3,r0		/* save return value */

	/* scan for delimiters */
2:
	movzbl	(r3)+,r2	/* c = *s++ */
	bbc	r2,(sp),2b	/* loop until c is in table */
	beql	3f
	clrb	-1(r3)		/* if c!='\0', s[-1] = 0 */
	movl	r3,(r1)		/* and *stringp = s */
	ret
3:
	clrl	(r1)		/* else *stringp = NULL */
	ret
E 1
