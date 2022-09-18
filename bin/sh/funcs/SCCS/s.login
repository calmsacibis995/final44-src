h53697
s 00000/00000/00012
d D 8.2 95/05/04 18:03:25 christos 3 2
c No changes
e
s 00002/00002/00010
d D 8.1 93/05/31 15:17:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00000/00000
d D 5.1 91/03/07 20:21:32 bostic 1 0
c date and time created 91/03/07 20:21:32 by bostic
e
u
U
t
T
I 1
D 2
# Copyright (c) 1991 The Regents of the University of California.
# All rights reserved.
E 2
I 2
# Copyright (c) 1991, 1993
#	The Regents of the University of California.  All rights reserved.
E 2
#
# This code is derived from software contributed to Berkeley by
# Kenneth Almquist.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%

# replaces the login builtin in the BSD shell
login () exec login "$@"
E 1
