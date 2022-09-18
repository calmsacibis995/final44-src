h05300
s 00001/00001/00011
d D 8.2 95/04/21 08:41:49 eric 5 4
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00010
d D 8.1 93/06/07 10:09:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00012
d D 6.1 92/12/21 16:11:41 eric 3 2
c Release 6
e
s 00001/00001/00011
d D 2.2 92/12/20 13:13:51 eric 2 1
c use MASQUERADE_AS macro
e
s 00012/00000/00000
d D 2.1 92/11/14 00:09:52 eric 1 0
c date and time created 92/11/14 00:09:52 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 4
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
#
# %sccs.include.redist.sh%
#
divert(0)
VERSIONID(`%W% (Berkeley) %G%')
D 5
DOMAIN(cs.exposed)dnl
E 5
I 5
DOMAIN(CS.Berkeley.EDU)dnl
E 5
D 2
define(`MASQUERADE_NAME', `postgres.Berkeley.EDU')dnl
E 2
I 2
MASQUERADE_AS(postgres.Berkeley.EDU)dnl
E 2
E 1
