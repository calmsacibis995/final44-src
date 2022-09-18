h29851
s 00001/00001/00014
d D 8.4 94/02/01 11:51:30 eric 7 6
c don't turn off case mapping in local users
e
s 00003/00000/00012
d D 8.3 93/11/27 09:29:25 eric 6 5
c updates for Irix 4.0.5H
e
s 00001/00001/00011
d D 8.2 93/08/08 09:59:17 eric 5 4
c require "m" in LOCAL_MAILER_FLAGS
e
s 00002/00002/00010
d D 8.1 93/06/07 10:11:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00012
d D 6.1 92/12/21 16:12:08 eric 3 2
c Release 6
e
s 00002/00004/00010
d D 2.2 92/11/14 00:04:45 eric 2 1
c put VERSIONID in diversion 0
e
s 00014/00000/00000
d D 2.1 92/11/14 00:00:40 eric 1 0
c date and time created 92/11/14 00:00:40 by eric
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
D 2
VERSIONID(`%W% (Berkeley) %G%')
#
E 2

D 2
define(`LOCAL_MAILER_FLAGS', Ehu)dnl

E 2
divert(0)
I 2
VERSIONID(`%W% (Berkeley) %G%')
D 5
define(`LOCAL_MAILER_FLAGS', Ehu)dnl
E 5
I 5
D 7
define(`LOCAL_MAILER_FLAGS', Ehmu)dnl
E 7
I 7
define(`LOCAL_MAILER_FLAGS', Ehm)dnl
E 7
I 6
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
define(`ALIAS_FILE', /usr/lib/aliases)dnl
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
E 6
E 5
E 2
E 1
