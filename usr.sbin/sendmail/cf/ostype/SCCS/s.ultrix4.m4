h07642
s 00000/00001/00011
d D 8.2 94/07/02 08:16:31 eric 10 9
c delete OLD_SENDMAIL support
e
s 00002/00002/00010
d D 8.1 93/06/07 10:12:05 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00012
d D 6.1 92/12/21 16:12:07 eric 8 7
c Release 6
e
s 00002/00004/00010
d D 2.7 92/11/14 00:04:44 eric 7 6
c put VERSIONID in diversion 0
e
s 00002/00002/00012
d D 2.6 92/11/13 22:56:03 eric 6 5
c quote versionid to avoid # problems
e
s 00001/00001/00013
d D 2.5 91/12/17 15:54:41 eric 5 4
c make NEWSENDMAIL the default
e
s 00000/00005/00014
d D 2.4 91/12/12 10:51:06 eric 4 3
c normalize locations of system files
e
s 00003/00003/00016
d D 2.3 91/11/22 14:58:03 eric 3 2
c reality check
e
s 00001/00000/00018
d D 2.2 91/10/03 01:23:11 eric 2 1
c specify that domains must be specified manually
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
D 9
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 9
I 9
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 9
#
# %sccs.include.redist.sh%
#
D 6
VERSIONID(%W% (Berkeley) %G%)
E 6
I 6
D 7
VERSIONID(`%W% (Berkeley) %G%')
E 6
#
E 7

D 3
define(`ALIAS_FILE', /usr/lib/aliases)dnl
E 3
I 3
D 4
define(`ALIAS_FILE', /etc/aliases)dnl
E 3
define(`HELP_FILE', /usr/lib/sendmail.hf)dnl
D 3
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
E 3
I 3
define(`QUEUE_DIR', /var/spool/mqueue)dnl
define(`STATUS_FILE', /etc/sendmail.st)dnl
E 3
define(`LOCAL_MAILER', /bin/mail)dnl
E 4
I 2
D 5
define(`NEED_DOMAIN')dnl
E 5
I 5
D 6
ifdef(`_OLD_SENDMAIL_', `define(`NEED_DOMAIN')')dnl
E 6
I 6
D 7
ifdef(`_OLD_SENDMAIL_', `define(`NEED_DOMAIN', `')')dnl
E 6
E 5
E 2

E 7
divert(0)
I 7
VERSIONID(`%W% (Berkeley) %G%')
D 10
ifdef(`_OLD_SENDMAIL_', `define(`NEED_DOMAIN', `')')dnl
E 10
E 7
E 1
