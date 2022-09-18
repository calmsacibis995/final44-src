h44180
s 00001/00000/00025
d D 8.3 95/05/29 10:44:29 eric 4 3
c HP-UX always hubs mail on mailspool.CS
e
s 00012/00002/00013
d D 8.2 95/04/21 08:39:12 eric 3 2
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00013
d D 8.1 93/06/07 10:07:01 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00000/00000
d D 6.1 93/04/19 16:50:57 eric 1 0
c date and time created 93/04/19 16:50:57 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 2
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 2
I 2
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 2
#
# %sccs.include.redist.sh%
#

I 3
#
#  This is a Berkeley-specific configuration file for HP-UX 9.x.
#  It applies only the the Computer Science Division at Berkeley,
#  and should not be used elsewhere.   It is provided on the sendmail
#  distribution as a sample only.  To create your own configuration
#  file, create an appropriate domain file in ../domain, change the
#  `DOMAIN' macro below to reference that file, and copy the result
#  to a name of your own choosing.
#

E 3
include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
D 3
OSTYPE(hpux)dnl
DOMAIN(cs.exposed)dnl
E 3
I 3
OSTYPE(hpux9)dnl
DOMAIN(CS.Berkeley.EDU)dnl
I 4
define(`MAIL_HUB', mailspool.CS.Berkeley.EDU)dnl
E 4
E 3
MAILER(local)dnl
MAILER(smtp)dnl
E 1
