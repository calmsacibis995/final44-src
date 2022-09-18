h28500
s 00002/00000/00016
d D 8.4 93/11/30 09:01:48 eric 4 3
c portability issues
e
s 00002/00002/00014
d D 8.3 93/08/13 08:00:24 eric 3 2
c use standard installation locations instead of alternates
e
s 00004/00003/00012
d D 8.2 93/08/06 21:59:44 eric 2 1
c oops... include QUEUE_DIR
e
s 00015/00000/00000
d D 8.1 93/08/06 21:57:59 eric 1 0
c date and time created 93/08/06 21:57:59 by eric
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
D 2
define(`ALIAS_FILE',	   /etc/sendmail/aliases)dnl
define(`HELP_FILE',	   /etc/sendmail/sendmail.hf)dnl
define(`STATUS_FILE', 	   /etc/sendmail/sendmail.st)dnl
E 2
I 2
define(`ALIAS_FILE', /etc/sendmail/aliases)dnl
D 3
define(`HELP_FILE', /etc/sendmail/sendmail.hf)dnl
E 3
I 3
define(`HELP_FILE', /usr/lib/sendmail.hf)dnl
E 3
define(`STATUS_FILE', /etc/sendmail/sendmail.st)dnl
E 2
D 3
define(`UUCP_MAILER_PATH', /usr/local/lib/uucp/uux)dnl
E 3
I 3
define(`UUCP_MAILER_PATH', /usr/bin/uux)dnl
E 3
I 2
define(`QUEUE_DIR', /usr/spool/mqueue)dnl
I 4
define(`LOCAL_MAILER_FLAGS', `rmnP')dnl
define(`LOCAL_SHELL_FLAGS', `euP')dnl
E 4
E 2
E 1
