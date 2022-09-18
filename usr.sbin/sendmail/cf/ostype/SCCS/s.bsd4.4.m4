h57473
s 00001/00001/00015
d D 8.3 95/05/26 07:41:59 eric 9 8
c use -a$g for UUCP calls
e
s 00001/00000/00015
d D 8.2 94/02/10 09:03:26 eric 8 7
c reverse sense of uux -z flag default
e
s 00002/00002/00013
d D 8.1 93/06/07 10:11:45 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00014
d D 6.2 93/02/19 20:28:48 eric 6 5
c LOCAL_MAILER => LOCAL_MAILER_PATH
e
s 00000/00000/00015
d D 6.1 92/12/21 16:12:05 eric 5 4
c Release 6
e
s 00002/00003/00013
d D 2.4 92/11/14 00:04:41 eric 4 3
c put VERSIONID in diversion 0
e
s 00001/00001/00015
d D 2.3 92/11/13 22:56:00 eric 3 2
c quote versionid to avoid # problems
e
s 00000/00002/00016
d D 2.2 91/12/12 10:51:02 eric 2 1
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
D 3
VERSIONID(%W% (Berkeley) %G%)
E 3
I 3
D 4
VERSIONID(`%W% (Berkeley) %G%')
E 4
E 3
#

I 4
divert(0)
VERSIONID(`%W% (Berkeley) %G%')
E 4
D 2
define(`ALIAS_FILE', /etc/aliases)dnl
E 2
define(`HELP_FILE', /usr/share/misc/sendmail.hf)dnl
D 2
define(`QUEUE_DIR', /var/spool/mqueue)dnl
E 2
define(`STATUS_FILE', /var/log/sendmail.st)dnl
D 6
define(`LOCAL_MAILER', /usr/libexec/mail.local)dnl
E 6
I 6
define(`LOCAL_MAILER_PATH', /usr/libexec/mail.local)dnl
I 8
D 9
define(`UUCP_MAILER_ARGS', `uux - -r -z -a$f $h!rmail ($u)')dnl
E 9
I 9
define(`UUCP_MAILER_ARGS', `uux - -r -z -a$g $h!rmail ($u)')dnl
E 9
E 8
E 6
D 4

divert(0)
E 4
E 1
