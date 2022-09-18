h09507
s 00001/00001/00015
d D 8.3 95/05/29 11:55:38 eric 4 3
c quote some code that shouldn't be expanded
e
s 00004/00002/00012
d D 8.2 94/11/13 15:47:03 eric 3 2
c make it a no-op; use FEATURE(stickydomain) to get old behaviour
e
s 00002/00002/00012
d D 8.1 93/06/07 10:10:37 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00000/00000
d D 6.1 93/03/06 09:47:40 eric 1 0
c date and time created 93/03/06 09:47:40 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 2
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 2
I 2
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 2
#
# %sccs.include.redist.sh%
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
I 3
#
D 4
#  This is now the default.  Use FEATURE(stickydomain) if you want
E 4
I 4
#  This is now the default.  Use ``FEATURE(stickyhost)'' if you want
E 4
#  the old default behaviour.
#
E 3
divert(-1)
D 3

define(`_LOCAL_NOT_STICKY_', 1)
E 3
E 1
