h56663
s 00001/00000/00014
d D 8.4 95/03/20 09:39:40 eric 4 3
c fix local timezones
e
s 00001/00001/00013
d D 8.3 93/08/08 09:59:18 eric 3 2
c require "m" in LOCAL_MAILER_FLAGS
e
s 00001/00000/00013
d D 8.2 93/07/13 12:59:46 eric 2 1
c minor changes
e
s 00013/00000/00000
d D 8.1 93/07/13 06:22:10 eric 1 0
c date and time created 93/07/13 06:22:10 by eric
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
define(`LOCAL_MAILER_PATH', /bin/bellmail)dnl
define(`LOCAL_MAILER_ARGS', mail $u)dnl
I 2
D 3
define(`LOCAL_MAILER_FLAGS', `n')dnl
E 3
I 3
define(`LOCAL_MAILER_FLAGS', `mn')dnl
I 4
define(`confTIME_ZONE', `USE_TZ')dnl
E 4
E 3
E 2
E 1
