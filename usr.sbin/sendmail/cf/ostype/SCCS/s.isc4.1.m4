h60789
s 00022/00000/00000
d D 8.1 95/06/12 08:58:24 eric 1 0
c date and time created 95/06/12 08:58:24 by eric
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
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
define(`ALIAS_FILE', /usr/lib/aliases)dnl
define(`HELP_FILE', /usr/lib/sendmail.hf)dnl
define(`LOCAL_MAILER_ARGS', `lmail -s $u')dnl
define(`LOCAL_MAILER_FLAGS', `humS')dnl
define(`LOCAL_MAILER_PATH', /bin/lmail)dnl
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
define(`UUCP_MAILER_ARGS', `uux - -r -gC $h!rmail ($u)')dnl
define(`UUCP_MAILER_PATH', /usr/bin/uux)dnl
define(`confTIME_ZONE', `USE_TZ')dnl
E 1
