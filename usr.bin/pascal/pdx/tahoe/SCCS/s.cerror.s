h25314
s 00000/00000/00024
d D 8.1 93/06/06 15:47:03 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00022
d D 5.3 93/06/06 15:47:00 bostic 3 2
c add 1993 to copyright
e
s 00004/00003/00020
d D 5.2 91/04/16 15:00:20 bostic 2 1
c new copyright; att/bsd/shared
e
s 00023/00000/00000
d D 5.1 87/04/07 00:07:19 mckusick 1 0
c CCI Version
e
u
U
t
T
I 2
D 3
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 3
I 3
# Copyright (c) 1987, 1993
#	The Regents of the University of California.  All rights reserved.
E 3
E 2
I 1
#
D 2
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
# %sccs.include.redist.sh%
E 2
#
#	%W% (Berkeley) %G%
#
I 2

E 2
# modified version of cerror
#
# The idea is that every time an error occurs in a system call
# I want a special function "syserr" called.  This function will
# either print a message and exit or do nothing depending on
# defaults and use of "onsyserr".
#

.globl	cerror
.comm	_errno,4

cerror:
	movl	r0,_errno
	callf	$4,_syserr	# new code
	mnegl	$1,r0
	ret
E 1
