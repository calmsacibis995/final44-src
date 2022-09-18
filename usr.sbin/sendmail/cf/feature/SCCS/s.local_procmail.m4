h51190
s 00000/00001/00018
d D 8.2 94/11/13 16:47:38 eric 2 1
c + is now default in confOPERATORS
e
s 00019/00000/00000
d D 8.1 94/11/13 16:24:31 eric 1 0
c date and time created 94/11/13 16:24:31 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1994 Eric P. Allman
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#

divert(0)
VERSIONID(`%W% (Berkeley) %G%')
divert(-1)

define(`PROCMAIL_PATH',
	ifelse(_ARG_, `', `/usr/local/bin/procmail', `_ARG_'))
define(`LOCAL_MAILER_FLAGS', `SPfhn')
define(`LOCAL_MAILER_PATH', PROCMAIL_PATH)
define(`LOCAL_MAILER_ARGS', `procmail -a $h -d $u')
D 2
define(`confOPERATORS', confOPERATORS`+')
E 2
E 1
