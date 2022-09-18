h34343
s 00002/00002/00009
d D 8.1 93/06/07 10:12:02 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00011
d D 6.1 92/12/21 16:12:07 eric 6 5
c Release 6
e
s 00001/00002/00010
d D 2.5 92/11/14 00:04:44 eric 5 4
c put VERSIONID in diversion 0
e
s 00001/00001/00011
d D 2.4 92/11/13 22:56:02 eric 4 3
c quote versionid to avoid # problems
e
s 00000/00006/00012
d D 2.3 91/12/12 10:51:05 eric 3 2
c normalize locations of system files
e
s 00002/00002/00016
d D 2.2 91/11/19 15:29:01 eric 2 1
c fix some pathname errors
e
s 00018/00000/00000
d D 2.1 91/10/02 14:48:45 eric 1 0
c date and time created 91/10/02 14:48:45 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 7
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 7
I 7
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 7
#
# %sccs.include.redist.sh%
#
D 4
VERSIONID(%W% (Berkeley) %G%)
E 4
I 4
D 5
VERSIONID(`%W% (Berkeley) %G%')
E 4
#
E 5

D 3
define(`ALIAS_FILE', /etc/aliases)dnl
define(`HELP_FILE', /usr/lib/sendmail.hf)dnl
D 2
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
E 2
I 2
define(`QUEUE_DIR', /var/spool/mqueue)dnl
define(`STATUS_FILE', /etc/sendmail.st)dnl
E 2
define(`LOCAL_MAILER', /bin/mail)dnl

E 3
divert(0)
I 5
VERSIONID(`%W% (Berkeley) %G%')
E 5
E 1
