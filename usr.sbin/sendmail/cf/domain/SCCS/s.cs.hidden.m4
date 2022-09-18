h11362
s 00002/00002/00010
d D 8.1 93/06/07 10:09:44 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00012
d D 6.1 92/12/21 16:11:40 eric 5 4
c Release 6
e
s 00001/00001/00011
d D 2.4 92/12/20 13:13:50 eric 4 3
c use MASQUERADE_AS macro
e
s 00001/00001/00011
d D 2.3 92/11/13 22:56:25 eric 3 2
c quote versionid to avoid # problems
e
s 00001/00001/00011
d D 2.2 91/10/03 09:57:01 eric 2 1
c break off Berkeley (non-cs) definitions
e
s 00012/00000/00000
d D 2.1 91/10/02 14:49:44 eric 1 0
c date and time created 91/10/02 14:49:44 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 6
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 6
I 6
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 6
#
# %sccs.include.redist.sh%
#
divert(0)
D 3
VERSIONID(%W% (Berkeley) %G%)
E 3
I 3
VERSIONID(`%W% (Berkeley) %G%')
E 3
D 2
DOMAIN(`cs.exposed')dnl
E 2
I 2
DOMAIN(cs.exposed)dnl
E 2
D 4
define(`MASQUERADE_NAME', `CS.Berkeley.EDU')dnl
E 4
I 4
MASQUERADE_AS(CS.Berkeley.EDU)dnl
E 4
E 1
