h15328
s 00011/00001/00014
d D 8.2 95/04/21 08:39:03 eric 2 1
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00015/00000/00000
d D 8.1 93/10/15 13:57:16 eric 1 0
c date and time created 93/10/15 13:57:16 by eric
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

I 2
#
#  This is a Berkeley-specific configuration file for OSF/1.
#  It applies only the the Computer Science Division at Berkeley,
#  and should not be used elsewhere.   It is provided on the sendmail
#  distribution as a sample only.  To create your own configuration
#  file, create an appropriate domain file in ../domain, change the
#  `DOMAIN' macro below to reference that file, and copy the result
#  to a name of your own choosing.
#

E 2
include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
OSTYPE(osf1)dnl
D 2
DOMAIN(cs.exposed)dnl
E 2
I 2
DOMAIN(CS.Berkeley.EDU)dnl
E 2
MAILER(local)dnl
MAILER(smtp)dnl
E 1
