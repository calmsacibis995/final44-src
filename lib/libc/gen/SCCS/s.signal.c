h25602
s 00002/00002/00032
d D 8.1 93/06/04 12:05:21 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00033
d D 5.6 91/09/03 15:19:42 bostic 9 8
c use SIG_ERR, not BADSIG
e
s 00001/00011/00033
d D 5.5 90/06/01 14:16:03 bostic 8 7
c new copyright notice
e
s 00015/00018/00029
d D 5.4 89/08/26 17:00:53 karels 7 6
c posix signals
e
s 00014/00003/00033
d D 5.3 88/08/02 21:09:34 bostic 6 5
c add Berkeley specific header
e
s 00002/00002/00034
d D 5.2 86/03/09 19:56:48 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00027
d D 5.1 85/06/05 12:36:01 mckusick 4 3
c Add copyright
e
s 00023/00020/00005
d D 4.3 85/03/11 22:33:17 mckusick 3 2
c properly track SV_INTERRUPT, SV_ONSTACK, and mask
e
s 00001/00001/00024
d D 4.2 85/01/15 15:09:47 ralph 2 1
c ENTRY macro changed.
e
s 00025/00000/00000
d D 4.1 84/05/16 15:19:24 ralph 1 0
c date and time created 84/05/16 15:19:24 by ralph
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 7
 * Copyright (c) 1985 Regents of the University of California.
E 7
I 7
D 10
 * Copyright (c) 1985, 1989 Regents of the University of California.
E 7
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1985, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 */

D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5
E 4
I 3

E 3
/*
 * Almost backwards compatible signal.
D 3
 *	int (*signal(s, a))() int s, (*a)();
E 3
 */
D 3
#include <syscall.h>
#include "DEFS.h"
E 3
I 3
#include <signal.h>
E 3

D 2
ENTRY(signal)
E 2
I 2
D 3
ENTRY(signal, 0)
E 2
	subl2	$24,sp			# struct sigvec osv, sv;
	movl	8(ap),-24(fp)		# sv.sv_handler = a;
	clrq	-20(fp)			# sv.sv_mask = sv.sv_onstack = 0;
	pushal	-12(fp)			# &osv
	pushal	-24(fp)			# &sv
	pushl	4(ap)			# s
	moval	-4(sp),ap
	chmk	$SYS_sigvec		# sigvec(s, &sv, &osv)
	jcs	err
	movl	-12(fp),r0		# return osv.sv_handler;
	ret
err:
	.globl	_errno
	movl	r0,_errno
	mnegl	$1,r0
	ret
E 3
I 3
D 7
int (*
signal(s, a))()
	int s, (*a)();
E 7
I 7
sigset_t _sigintr;		/* shared with siginterrupt */

sig_t
signal(s, a)
	int s;
	sig_t a;
E 7
{
D 7
	struct sigvec osv, sv;
	static int mask[NSIG];
	static int flags[NSIG];
E 7
I 7
	struct sigaction sa, osa;
E 7

D 7
	sv.sv_handler = a;
	sv.sv_mask = mask[s];
	sv.sv_flags = flags[s];
	if (sigvec(s, &sv, &osv) < 0)
E 7
I 7
	sa.sa_handler = a;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (!sigismember(&_sigintr, s))
		sa.sa_flags |= SA_RESTART;
	if (sigaction(s, &sa, &osa) < 0)
E 7
D 9
		return (BADSIG);
E 9
I 9
		return (SIG_ERR);
E 9
D 7
	if (sv.sv_mask != osv.sv_mask || sv.sv_flags != osv.sv_flags) {
		mask[s] = sv.sv_mask = osv.sv_mask;
		flags[s] = sv.sv_flags = osv.sv_flags;
		if (sigvec(s, &sv, 0) < 0)
			return (BADSIG);
	}
	return (osv.sv_handler);
E 7
I 7
	return (osa.sa_handler);
E 7
}
E 3
E 1
