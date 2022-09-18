h28998
s 00001/00001/00013
d D 8.3 93/08/07 12:04:13 eric 5 4
c don't include .db on the end of map names -- this is added automatically
e
s 00001/00001/00013
d D 8.2 93/07/28 10:17:50 eric 4 3
c fix botch with -o flag on default maps; also, add .db on them
e
s 00002/00002/00012
d D 8.1 93/06/07 10:10:30 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00013
d D 6.2 93/05/21 19:49:39 eric 2 1
c don't include .db on database file names
e
s 00014/00000/00000
d D 6.1 93/03/23 16:11:32 eric 1 0
c date and time created 93/03/23 16:11:32 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 3
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 3
I 3
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 3
#
# %sccs.include.redist.sh%
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
divert(-1)

D 2
define(`MAILER_TABLE', ifelse(_ARG_, `', `hash /etc/mailertable.db -o', `_ARG_'))dnl
E 2
I 2
D 4
define(`MAILER_TABLE', ifelse(_ARG_, `', `hash /etc/mailertable -o', `_ARG_'))dnl
E 4
I 4
D 5
define(`MAILER_TABLE', ifelse(_ARG_, `', `hash -o /etc/mailertable.db', `_ARG_'))dnl
E 5
I 5
define(`MAILER_TABLE', ifelse(_ARG_, `', `hash -o /etc/mailertable', `_ARG_'))dnl
E 5
E 4
E 2
E 1
