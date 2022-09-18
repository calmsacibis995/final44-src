h05263
s 00025/00000/00000
d D 8.1 95/04/21 08:40:04 eric 1 0
c date and time created 95/04/21 08:40:04 by eric
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
#  This is a Berkeley-specific configuration file for Solaris 2.x.
#  It applies only the the Computer Science Division at Berkeley,
#  and should not be used elsewhere.   It is provided on the sendmail
#  distribution as a sample only.  To create your own configuration
#  file, create an appropriate domain file in ../domain, change the
#  `DOMAIN' macro below to reference that file, and copy the result
#  to a name of your own choosing.
#

include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
OSTYPE(solaris2)dnl
DOMAIN(CS.Berkeley.EDU)dnl
MAILER(local)dnl
MAILER(smtp)dnl
E 1
