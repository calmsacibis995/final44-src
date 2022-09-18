h45841
s 00017/00000/00000
d D 8.1 93/09/02 11:21:57 eric 1 0
c date and time created 93/09/02 11:21:57 by eric
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
define(`ALIAS_FILE', /usr/lib/aliases)dnl
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
define(`STATUS_FILE', /usr/lib/sendmail.st)dnl
define(`UUCP_MAILER_PATH', /usr/bin/uux)dnl
define(`LOCAL_MAILER_FLAGS', mn)dnl
define(`LOCAL_MAILER_ARGS', `mail -d -r $f $u')dnl
E 1
