h46984
s 00001/00003/00011
d D 8.2 93/08/21 17:06:50 eric 2 1
c more changes from Karl London <karl@borg.demon.co.uk>
e
s 00014/00000/00000
d D 8.1 93/08/08 14:08:58 eric 1 0
c date and time created 93/08/08 14:08:58 by eric
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
define(`LOCAL_MAILER_PATH', /usr/bin/lmail)dnl
define(`LOCAL_MAILER_ARGS', mail $u)dnl
define(`LOCAL_MAILER_FLAGS', `rm')dnl
E 2
I 2
define(`LOCAL_MAILER_PATH', /bin/mail.local)dnl
E 2
E 1
