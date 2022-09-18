h12921
s 00001/00001/00011
d D 8.2 95/04/21 08:41:50 eric 6 5
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00010
d D 8.1 93/06/07 10:09:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00012
d D 6.1 92/12/21 16:11:41 eric 4 3
c Release 6
e
s 00001/00001/00011
d D 2.3 92/12/20 13:13:51 eric 3 2
c use MASQUERADE_AS macro
e
s 00001/00001/00011
d D 2.2 92/11/13 22:56:27 eric 2 1
c quote versionid to avoid # problems
e
s 00012/00000/00000
d D 2.1 92/07/24 10:14:46 eric 1 0
c date and time created 92/07/24 10:14:46 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 5
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 5
I 5
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 5
#
# %sccs.include.redist.sh%
#
divert(0)
D 2
VERSIONID(%W% (Berkeley) %G%)
E 2
I 2
VERSIONID(`%W% (Berkeley) %G%')
E 2
D 6
DOMAIN(Berkeley)dnl
E 6
I 6
DOMAIN(Berkeley.EDU)dnl
E 6
D 3
define(`MASQUERADE_NAME', `EECS.Berkeley.EDU')dnl
E 3
I 3
MASQUERADE_AS(EECS.Berkeley.EDU)dnl
E 3
E 1
