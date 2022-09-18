h02520
s 00000/00001/00014
d D 8.2 94/07/02 08:16:31 eric 4 3
c delete OLD_SENDMAIL support
e
s 00002/00002/00013
d D 8.1 93/06/07 10:11:53 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00015
d D 6.1 92/12/21 16:12:08 eric 2 1
c Release 6
e
s 00015/00000/00000
d D 2.1 92/11/16 20:03:07 eric 1 0
c date and time created 92/11/16 20:03:07 by eric
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
D 4
ifdef(`_OLD_SENDMAIL_', `define(`NEED_DOMAIN', `')')dnl
E 4
define(`ALIAS_FILE', /usr/adm/sendmail/aliases)dnl
define(`STATUS_FILE', /usr/adm/sendmail/sendmail.st)dnl
define(`HELP_FILE', /usr/share/lib/sendmail.hf)dnl
E 1
