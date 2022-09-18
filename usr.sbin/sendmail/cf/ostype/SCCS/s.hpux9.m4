h29793
s 00001/00001/00019
d D 8.8 95/05/26 07:42:01 eric 14 13
c use -a$g for UUCP calls
e
s 00001/00000/00019
d D 8.7 95/05/24 18:32:42 eric 13 12
c local mailer is /bin/rmail
e
s 00001/00000/00018
d D 8.6 95/04/07 13:09:20 eric 12 11
c must invoke mail as rmail
e
s 00001/00000/00017
d D 8.5 94/01/09 09:50:50 eric 11 10
c -z flag is different on HP-UX
e
s 00001/00000/00016
d D 8.4 93/08/24 20:31:54 eric 10 9
c use TZ envariable
e
s 00004/00001/00012
d D 8.3 93/08/24 14:59:15 eric 9 8
c reality therapy
e
s 00001/00001/00012
d D 8.2 93/08/08 09:59:16 eric 8 7
c require "m" in LOCAL_MAILER_FLAGS
e
s 00002/00002/00011
d D 8.1 93/06/07 10:11:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00013
d D 6.1 92/12/21 16:12:05 eric 6 5
c Release 6
e
s 00002/00004/00011
d D 2.5 92/11/14 00:04:42 eric 5 4
c put VERSIONID in diversion 0
e
s 00001/00001/00014
d D 2.4 92/11/13 22:56:00 eric 4 3
c quote versionid to avoid # problems
e
s 00001/00001/00014
d D 2.3 92/11/13 21:50:59 eric 3 2
c make more portable to other versions of m4
e
s 00001/00000/00014
d D 2.2 92/07/14 12:33:09 eric 2 1
c local mailer for HPUX doesn't accept r or n mailer flags
e
s 00014/00000/00000
d D 2.1 91/12/09 14:24:06 eric 1 0
c date and time created 91/12/09 14:24:06 by eric
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

I 5
divert(0)
VERSIONID(`%W% (Berkeley) %G%')
E 5
D 3
define(`_HPUX_')dnl
E 3
I 3
D 9
define(`_HPUX_', `')dnl
E 9
I 9

define(`QUEUE_DIR', /usr/spool/mqueue)dnl
define(`ALIAS_FILE', /usr/lib/aliases)dnl
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
I 13
define(`LOCAL_MAILER_PATH', `/bin/rmail')dnl
E 13
E 9
E 3
I 2
D 8
define(`LOCAL_MAILER_FLAGS', `')dnl
E 8
I 8
define(`LOCAL_MAILER_FLAGS', `m')dnl
I 12
define(`LOCAL_MAILER_ARGS', `rmail -d $u')dnl
E 12
I 11
D 14
define(`UUCP_MAILER_ARGS', `uux - -r -a$f -gC $h!rmail ($u)')dnl
E 14
I 14
define(`UUCP_MAILER_ARGS', `uux - -r -a$g -gC $h!rmail ($u)')dnl
E 14
E 11
I 10
define(`confTIME_ZONE', `USE_TZ')dnl
E 10
E 8
E 2
D 5

divert(0)
E 5
E 1
