h49970
s 00022/00000/00000
d D 8.1 95/04/21 08:40:05 eric 1 0
c date and time created 95/04/21 08:40:05 by eric
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
#  This is a generic configuration file for OSF/1.
#  It has support for local and SMTP mail only.  If you want to
#  customize it, copy it to a name appropriate for your environment
#  and do the modifications there.
#

include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
OSTYPE(osf1)dnl
DOMAIN(generic)dnl
MAILER(local)dnl
MAILER(smtp)dnl
E 1
