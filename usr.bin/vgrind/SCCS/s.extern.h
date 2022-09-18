h58363
s 00002/00002/00037
d D 8.1 93/06/06 22:20:21 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00028/00036
d D 1.3 92/09/15 11:07:59 elan 3 2
c Added SCCS keywords.
e
s 00001/00001/00063
d D 1.2 92/09/01 12:08:08 elan 2 1
c Changed year on copyright.
e
s 00064/00000/00000
d D 1.1 92/09/01 12:07:29 elan 1 0
c date and time created 92/09/01 12:07:29 by elan
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1980 The Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1992 The Regents of the University of California.
E 3
I 3
D 4
 * Copyright (c) 1980 The Regents of the University of California.
E 3
E 2
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 3
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 3
 *
D 3
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
D 3
 *      @(#)extern.h	1.2 (Berkeley) 8/3/92
E 3
I 3
 *      %W% (Berkeley) %G%
E 3
 */

typedef int boolean;

extern boolean	 _escaped;             /* if last character was an escape */
extern char    *_start;                /* start of the current string */
extern char    *l_acmbeg;              /* string introducing a comment */
extern char    *l_acmend;              /* string ending a comment */
extern char    *l_blkbeg;              /* string begining of a block */
extern char    *l_blkend;              /* string ending a block */
extern char    *l_chrbeg;              /* delimiter for character constant */
extern char    *l_chrend;              /* delimiter for character constant */
extern char    *l_combeg;              /* string introducing a comment */
extern char    *l_comend;              /* string ending a comment */
extern char     l_escape;              /* character used to escape characters */
extern char    *l_keywds[];    	       /* keyword table address */
extern boolean  l_onecase;             /* upper and lower case are equivalent */
extern char    *l_prcbeg;              /* regular expr for procedure begin */
extern char    *l_strbeg;              /* delimiter for string constant */
extern char    *l_strend;              /* delimiter for string constant */
extern boolean  l_toplex;              /* procedures only defined at top lex level */
extern char    *language;              /* the language indicator */

#include <sys/cdefs.h>

__BEGIN_DECLS
extern int      STRNCMP __P((char *, char *, int));
extern char    *convexp __P((char *));
extern char    *expmatch __P((char *, char *, char *));
__END_DECLS

E 1
