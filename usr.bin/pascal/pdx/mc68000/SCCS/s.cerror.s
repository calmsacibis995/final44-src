h34609
s 00000/00000/00030
d D 8.1 93/06/06 15:40:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00028
d D 5.3 93/06/06 15:40:54 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00026
d D 5.2 91/04/16 15:19:30 bostic 2 1
c new copyright; att/bsd/shared
e
s 00029/00000/00000
d D 5.1 87/04/07 00:08:59 mckusick 1 0
c MC68000 Version
e
u
U
t
T
I 2
D 3
# Copyright (c) 1982 The Regents of the University of California.
# All rights reserved.
E 3
I 3
# Copyright (c) 1982, 1993
#	The Regents of the University of California.  All rights reserved.
E 3
E 2
I 1
#
D 2
# Copyright (c) 1982 Regents of the University of California.
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
	movl	d0,_errno
	jsr	_syserr		| new code
	moveq	#-1,d0
	rts

.globl	__mycerror		| clumsy way to get this loaded

__mycerror:
	.word	0
	rts
E 1
