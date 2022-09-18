h10887
s 00002/00002/00022
d D 8.1 93/06/06 13:59:00 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00022
d D 5.7 92/09/15 10:40:10 elan 7 6
c Added SCCS keywords.
e
s 00001/00029/00021
d D 5.6 92/09/15 10:39:05 elan 6 5
c Added SCCS keywords.
e
s 00028/00002/00022
d D 5.5 92/09/01 11:08:03 elan 5 4
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00001/00011/00023
d D 5.4 90/06/01 18:44:21 bostic 4 3
c new copyright notice
e
s 00002/00002/00032
d D 5.3 89/07/28 12:38:44 karels 3 2
c mv to /var/spool/output
e
s 00000/00001/00034
d D 5.2 89/06/04 10:02:30 bostic 2 1
c sendmail -> paths.h
e
s 00035/00000/00000
d D 5.1 89/05/11 14:41:18 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
D 5
 * %sccs.include.redist.c%
E 5
I 5
D 6
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
E 5
E 4
 *
D 5
 *	%W% (Berkeley) %G%
E 5
I 5
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
 *
 *	@(#)pathnames.h	5.5 (Berkeley) 8/6/92
E 6
I 6
 * %sccs.include.redist.c%
I 7
 *
 *      %W% (Berkeley) %G%
E 7
E 6
E 5
 */

#include <paths.h>

#define	_PATH_DEFDEVLP		"/dev/lp"
D 3
#define	_PATH_DEFSPOOL		"/var/spool/lpd"
E 3
I 3
#define	_PATH_DEFSPOOL		"/var/spool/output/lpd"
E 3
#define	_PATH_HOSTSEQUIV	"/etc/hosts.equiv"
#define	_PATH_HOSTSLPD		"/etc/hosts.lpd"
D 3
#define	_PATH_MASTERLOCK	"/var/spool/lpd.lock"
E 3
I 3
#define	_PATH_MASTERLOCK	"/var/spool/output/lpd.lock"
E 3
#define	_PATH_PR		"/usr/bin/pr"
#define	_PATH_PRINTCAP		"/etc/printcap"
D 2
#define	_PATH_SENDMAIL		"/usr/libexec/sendmail"
E 2
#define	_PATH_SOCKETNAME	"/var/run/printer"
#define	_PATH_VFONT		"/usr/libdata/vfont/"
#define	_PATH_VFONTB		"/usr/libdata/vfont/B"
#define	_PATH_VFONTI		"/usr/libdata/vfont/I"
#define	_PATH_VFONTR		"/usr/libdata/vfont/R"
#define	_PATH_VFONTS		"/usr/libdata/vfont/S"
E 1
