h37319
s 00002/00002/00011
d D 8.1 93/06/06 13:59:54 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/00013
d D 5.4 93/02/26 11:40:03 torek 4 3
c rm __BEGIN_DECLS, __END_DECLS; the latter was misspelled and
c these are only for C++ to use C code anyway.  gcc1 was certainly
c forgiving about underscores!
e
s 00004/00029/00012
d D 5.3 92/09/15 10:52:04 elan 3 2
c Added SCCS keywords.
e
s 00033/00003/00008
d D 5.2 92/09/01 11:09:48 elan 2 1
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00011/00000/00000
d D 5.1 92/07/21 10:29:34 bostic 1 0
c date and time created 92/07/21 10:29:34 by bostic
e
u
U
t
T
I 1
D 3
/*-
 * Copyright (c) 1992 The Regents of the University of California.
E 3
I 3
/*
D 5
 * Copyright (c) 1989 The Regents of the University of California.
E 3
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 2
 * %sccs.include.redist.c%
E 2
I 2
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
E 2
D 4
 *
E 4
D 2
 *	%W% (Berkeley) %G%
E 2
I 2
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
 *	@(#)extern.h	5.2 (Berkeley) 7/30/92
E 3
I 3
 *      %W% (Berkeley) %G%
E 3
E 2
 */

I 2
#include <sys/cdefs.h>

D 4
__BEGIN_DECLS
E 4
E 2
void       printjob __P((void));
D 2
int        recvjob __P((void));
E 2
I 2
void       recvjob __P((void));
D 4
___END_DECLS
E 4
E 2
E 1
