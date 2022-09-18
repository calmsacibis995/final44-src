h07299
s 00001/00001/00020
d D 8.3 95/05/26 07:41:59 eric 3 2
c use -a$g for UUCP calls
e
s 00001/00000/00020
d D 8.2 95/05/19 12:38:17 eric 2 1
c /bin/sh has moved
e
s 00020/00000/00000
d D 8.1 95/04/25 16:33:11 eric 1 0
c date and time created 95/04/25 16:33:11 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')

define(`QUEUE_DIR', /var/spool/mqueue)dnl
define(`ALIAS_FILE', /etc/mail/aliases)dnl
define(`STATUS_FILE', /etc/mail/sendmail.st)dnl
define(`LOCAL_MAILER_PATH', /usr/bin/rmail)dnl
define(`LOCAL_MAILER_FLAGS', `m')dnl
define(`LOCAL_MAILER_ARGS', `rmail -d $u')dnl
I 2
define(`LOCAL_SHELL_PATH', /usr/bin/sh)dnl
E 2
D 3
define(`UUCP_MAILER_ARGS', `uux - -r -a$f -gC $h!rmail ($u)')dnl
E 3
I 3
define(`UUCP_MAILER_ARGS', `uux - -r -a$g -gC $h!rmail ($u)')dnl
E 3
define(`confTIME_ZONE', `USE_TZ')dnl
E 1
