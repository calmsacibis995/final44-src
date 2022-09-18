h22373
s 00002/00002/00086
d D 8.1 93/06/04 15:41:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00087
d D 5.4 90/06/01 15:32:13 bostic 4 3
c new copyright notice
e
s 00058/00061/00040
d D 5.3 90/06/01 15:31:59 bostic 3 2
c new version from Chris Torek
e
s 00013/00008/00088
d D 5.2 88/06/27 18:16:36 bostic 2 1
c install approved copyright notice
e
s 00096/00000/00000
d D 5.1 88/06/03 18:56:41 bostic 1 0
c date and time created 88/06/03 18:56:41 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

D 2
#if defined(SYSLIBC_SCCS) && !defined(lint)
_sccsid:.asciz	"%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 2

D 3
#ifdef notdef
_sccsid:.asciz	"@(#)rindex.s	5.4 (Berkeley) 5/25/88"
#endif

E 3
/*
 * Find the last occurence of c in the string cp.
 * Return pointer to match or null pointer.
 *
 * char *
D 3
 * rindex(cp, c)
E 3
I 3
 * strrchr(cp, c)
E 3
 *	char *cp, c;
 */
#include "DEFS.h"

I 3
	.lcomm	tbl,256

E 3
ENTRY(strrchr, 0)
D 3
	movq	4(ap),r1	# r1 = cp; r2 = c
	tstl	r2		# check for special case c == '\0'
	bneq	2f
E 3
I 3
	movzwl	$65535,r4	/* handy 65535 */
	movq	4(ap),r1	/* r1 = cp; r2 = c */
	movzbl	r2,r2
	beql	Lzero		/* special case for c == '\0' */

	clrl	r5		/* r5 = pointer to last match */

/*
 * Fancy scanc version.  Alas, it is not reentrant.
 */
	movab	tbl,r3		/* r3 = address of table */
	bbss	$0,(r3),Lreent	/* ensure not reentering */
	movab	(r3)[r2],r4
	incb	(r4)		/* mark both '\0' and c */
0:
	scanc	$65535,(r1),(r3),$1	/* look for c or '\0' */
	beql	0b		/* keep looking */
	tstb	(r1)
	beql	1f		/* done if '\0' */
	movab	(r1)+,r5	/* save most recently found, and skip over it */
	jbr	0b		/* keep looking */
E 3
1:
D 3
	locc	$0,$65535,(r1)	# just find end of string
	beql	1b		# still looking
	movl	r1,r0		# found it
	ret
2:
	moval	tbl,r3		# r3 = address of table
	bbss	$0,(r3),5f	# insure not reentering
	movab	(r3)[r2],r5	# table entry for c
	incb	(r5)
	clrl	r4		# last found
3:
	scanc	$65535,(r1),(r3),$1	# look for c or '\0'
	beql	3b		# keep looking
	tstb	(r1)		# if have found '\0'
	beql	4f		#    we are done
	movl	r1,r4		# save most recently found
	incl	r1		# skip over character
	jbr	3b		# keep looking
4:
	movl	r4,r0		# return last found (if any)
	clrb	(r5)		# clean up table
E 3
I 3
	movl	r5,r0		/* return last found (if any) */
	clrb	(r4)		/* clean up table */
E 3
	clrb	(r3)
	ret

D 3
	.data
tbl:	.space	256
	.text
E 3
I 3
/*
 * Special case for \0.
 */
Lzero:
	locc	$0,r4,(r1)	/* just find end of string */
	beql	Lzero		/* still looking */
	movl	r1,r0		/* found it */
	ret
E 3

/*
D 3
 * Reentrant, but slower version of rindex
E 3
I 3
 * Slower reentrant version is two two-step searches.  The first
 * phase runs until we know where the string ends; it locates any
 * occurrences of c within a 65535-byte block.  Once we have found
 * the end of the string, we find any further occurrences before
 * that location.
E 3
 */
D 3
5:
E 3
I 3
Lreent:
0:	/* first phase */
E 3
	movl	r1,r3
D 3
	clrl	r4		# r4 = pointer to last match
6:
	locc	$0,$65535,(r3)	# look for '\0'
	bneq	8f
	decw	r0		# r0 = 65535
1:
	locc	r2,r0,(r3)	# look for c
	bneq	7f
	movl	r1,r3		# reset pointer and ...
	jbr	6b		# ... try again
7:
	movl	r1,r4		# stash pointer ...
	addl3	$1,r1,r3	# ... skip over match and ...
	decl	r0		# ... decrement count
	jbr	6b		# ... try again
8:
	subl3	r3,r1,r0	# length of short block
	incl	r0		# +1 for '\0'
9:
	locc	r2,r0,(r3)	# look for c
	beql	0f
	movl	r1,r4		# stash pointer ...
	addl3	$1,r1,r3	# ... skip over match ...
	decl	r0		# ... adjust count and ...
	jbr	9b		# ... try again
0:
	movl	r4,r0		# return stashed pointer
E 3
I 3
	locc	$0,r4,(r3)	/* look for '\0' */
	bneq	1f
	locc	r2,r4,(r3)	/* continue phase 1 search for c */
	beql	0b
	movab	(r1)+,r5	/* found c: save and increment pointer */
	brb	0b		/* and continue */

1:	/* second phase */
	subl3	r3,r1,r0	/* length of short block */
	movl	r3,r1
2:
	locc	r2,r0,(r1)	/* look for c */
	beql	3f		/* skip if not found */
	movab	(r1)+,r5	/* save pointer as before */
	sobgtr	r0,2b		/* adjust count and loop */
3:
	movl	r5,r0		/* return stashed pointer */
E 3
	ret
E 1
