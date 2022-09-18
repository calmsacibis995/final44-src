h15729
s 00001/00000/00025
d D 8.2 95/05/29 10:44:29 eric 2 1
c HP-UX always hubs mail on mailspool.CS
e
s 00025/00000/00000
d D 8.1 95/04/25 16:34:58 eric 1 0
c date and time created 95/04/25 16:34:58 by eric
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
#  This is a Berkeley-specific configuration file for HP-UX 9.x.
#  It applies only the the Computer Science Division at Berkeley,
#  and should not be used elsewhere.   It is provided on the sendmail
#  distribution as a sample only.  To create your own configuration
#  file, create an appropriate domain file in ../domain, change the
#  `DOMAIN' macro below to reference that file, and copy the result
#  to a name of your own choosing.
#

include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
OSTYPE(hpux10)dnl
DOMAIN(CS.Berkeley.EDU)dnl
I 2
define(`MAIL_HUB', mailspool.CS.Berkeley.EDU)dnl
E 2
MAILER(local)dnl
MAILER(smtp)dnl
E 1
