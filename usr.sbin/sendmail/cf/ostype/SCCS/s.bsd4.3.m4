h47684
s 00001/00001/00012
d D 8.3 95/05/26 07:42:01 eric 8 7
c use -a$g for UUCP calls
e
s 00001/00000/00012
d D 8.2 94/02/10 09:03:26 eric 7 6
c reverse sense of uux -z flag default
e
s 00002/00002/00010
d D 8.1 93/06/07 10:11:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00012
d D 6.1 92/12/21 16:12:03 eric 5 4
c Release 6
e
s 00002/00004/00010
d D 2.4 92/11/14 00:04:40 eric 4 3
c put VERSIONID in diversion 0
e
s 00001/00001/00013
d D 2.3 92/11/13 22:55:59 eric 3 2
c quote versionid to avoid # problems
e
s 00000/00004/00014
d D 2.2 91/12/12 10:51:01 eric 2 1
c normalize locations of system files
e
s 00018/00000/00000
d D 2.1 91/10/02 14:48:43 eric 1 0
c date and time created 91/10/02 14:48:43 by eric
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
E 2
D 4
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
D 2
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
define(`LOCAL_MAILER', /bin/mail)dnl
E 2

E 4
divert(0)
I 4
VERSIONID(`%W% (Berkeley) %G%')
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
I 7
D 8
define(`UUCP_MAILER_ARGS', `uux - -r -z -a$f $h!rmail ($u)')dnl
E 8
I 8
define(`UUCP_MAILER_ARGS', `uux - -r -z -a$g $h!rmail ($u)')dnl
E 8
E 7
E 4
E 1
