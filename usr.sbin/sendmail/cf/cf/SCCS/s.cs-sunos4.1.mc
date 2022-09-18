h45281
s 00011/00001/00014
d D 8.2 95/04/21 08:39:02 eric 5 4
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00013
d D 8.1 93/06/07 10:07:32 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00015
d D 6.1 92/12/21 16:09:31 eric 3 2
c Release 6
e
s 00001/00001/00014
d D 2.2 92/11/13 22:56:54 eric 2 1
c quote versionid to avoid # problems
e
s 00015/00000/00000
d D 2.1 91/11/07 23:47:16 eric 1 0
c date and time created 91/11/07 23:47:16 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 4
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
#
# %sccs.include.redist.sh%
#

I 5
#
#  This is a Berkeley-specific configuration file for SunOS 4.1.x.
#  It applies only the the Computer Science Division at Berkeley,
#  and should not be used elsewhere.   It is provided on the sendmail
#  distribution as a sample only.  To create your own configuration
#  file, create an appropriate domain file in ../domain, change the
#  `DOMAIN' macro below to reference that file, and copy the result
#  to a name of your own choosing.
#

E 5
include(`../m4/cf.m4')
D 2
VERSIONID(%W% (Berkeley) %G%)
E 2
I 2
VERSIONID(`%W% (Berkeley) %G%')
E 2
OSTYPE(sunos4.1)dnl
D 5
DOMAIN(cs.exposed)dnl
E 5
I 5
DOMAIN(CS.Berkeley.EDU)dnl
E 5
MAILER(local)dnl
MAILER(smtp)dnl
E 1
