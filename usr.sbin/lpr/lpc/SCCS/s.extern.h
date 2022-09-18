h64014
s 00002/00002/00030
d D 8.1 93/06/06 13:59:54 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00031
d D 5.4 93/04/05 21:53:29 ralph 4 3
c change start to startcmd to avoid conflict with start in crt0.o
e
s 00005/00029/00027
d D 5.3 92/09/15 10:48:20 elan 3 2
c Added SCCS keywords.
e
s 00034/00003/00022
d D 5.2 92/09/01 11:09:01 elan 2 1
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00025/00000/00000
d D 5.1 92/07/21 10:29:07 bostic 1 0
c date and time created 92/07/21 10:29:07 by bostic
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
 *
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
 *	@(#)extern.h	5.3 (Berkeley) 8/6/92
E 3
I 3
 *      %W% (Berkeley) %G%
E 3
E 2
 */
I 3

E 3

D 2
void	doabort __P((int, char **));
E 2
I 2
#include <sys/cdefs.h>


__BEGIN_DECLS
E 2
void	clean __P((int, char **));
void	disable __P((int, char **));
I 2
void	doabort __P((int, char **));
E 2
void	down __P((int, char **));
void	enable __P((int, char **));
void	help __P((int, char **));
void	quit __P((int, char **));
void	restart __P((int, char **));
D 4
void	start __P((int, char **));
E 4
I 4
void	startcmd __P((int, char **));
E 4
void	status __P((int, char **));
void	stop __P((int, char **));
void	topq __P((int, char **));
void	up __P((int, char **));
I 2
__END_DECLS
E 2

extern int NCMDS;
extern struct cmd cmdtab[];
E 1
