h18529
s 00001/00001/00018
d D 6.2 93/02/12 12:11:08 eric 6 5
c make everything configurable on M4 macros
e
s 00000/00000/00019
d D 6.1 92/12/21 16:11:52 eric 5 4
c Release 6
e
s 00002/00001/00017
d D 2.4 92/11/14 00:09:09 eric 4 3
c put VERSIONID in diversion 0
e
s 00001/00001/00017
d D 2.3 92/11/13 22:57:18 eric 3 2
c quote versionid to avoid # problems
e
s 00001/00001/00017
d D 2.2 92/11/13 21:51:06 eric 2 1
c make more portable to other versions of m4
e
s 00018/00000/00000
d D 2.1 91/10/02 14:49:25 eric 1 0
c date and time created 91/10/02 14:49:25 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh%
#

I 4
divert(0)
E 4
D 3
VERSIONID(%W% (Berkeley) %G%)
E 3
I 3
VERSIONID(`%W% (Berkeley) %G%')
I 4
divert(-1)
E 4
E 3

# If specified, this asserts that we have no wildcard MX records
# in our domain.  This allows us to do fewer name server lookups
# and thus get better performance.

D 2
define(`_NO_WILDCARD_MX_')dnl
E 2
I 2
D 6
define(`_NO_WILDCARD_MX_', `')dnl
E 6
I 6
define(`confNO_WILDCARD_MX', `True')dnl
E 6
E 2
D 4

E 4
divert(0)
E 1
