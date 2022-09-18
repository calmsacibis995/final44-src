h21286
s 00002/00002/00009
d D 8.1 93/06/07 10:11:59 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00011
d D 6.1 92/12/21 16:12:06 eric 5 4
c Release 6
e
s 00001/00002/00010
d D 2.4 92/11/14 00:04:43 eric 4 3
c put VERSIONID in diversion 0
e
s 00001/00001/00011
d D 2.3 92/11/13 22:56:02 eric 3 2
c quote versionid to avoid # problems
e
s 00000/00006/00012
d D 2.2 91/12/12 10:51:04 eric 2 1
c normalize locations of system files
e
s 00018/00000/00000
d D 2.1 91/10/02 14:48:44 eric 1 0
c date and time created 91/10/02 14:48:44 by eric
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
D 3
VERSIONID(%W% (Berkeley) %G%)
E 3
I 3
D 4
VERSIONID(`%W% (Berkeley) %G%')
E 3
#
E 4

D 2
define(`ALIAS_FILE', /usr/lib/aliases)dnl
define(`HELP_FILE', /usr/lib/sendmail.hf)dnl
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
define(`LOCAL_MAILER', /bin/mail)dnl

E 2
divert(0)
I 4
VERSIONID(`%W% (Berkeley) %G%')
E 4
E 1
