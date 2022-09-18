h40474
s 00009/00002/00016
d D 8.2 95/04/21 08:39:14 eric 6 5
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00016
d D 8.1 93/06/07 10:07:06 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00018
d D 6.1 92/12/21 16:09:29 eric 4 3
c Release 6
e
s 00001/00001/00017
d D 2.3 92/11/13 22:56:53 eric 3 2
c quote versionid to avoid # problems
e
s 00000/00001/00018
d D 2.2 91/10/03 15:07:30 eric 2 1
c local mailer is automatic
e
s 00019/00000/00000
d D 2.1 91/10/03 01:55:27 eric 1 0
c date and time created 91/10/03 01:55:27 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 5
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 5
I 5
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 5
#
# %sccs.include.redist.sh%
#

I 6
#
#  This is a Berkeley-specific configuration file for a specific
#  machine in the Computer Science Division at Berkeley, and should
#  not be used elsewhere.   It is provided on the sendmail distribution
#  as a sample only.
#

E 6
include(`../m4/cf.m4')
D 3
VERSIONID(%W% (Berkeley) %G%)
E 3
I 3
VERSIONID(`%W% (Berkeley) %G%')
E 3
D 6
OSTYPE(ultrix4.1)dnl
DOMAIN(cs.exposed)dnl
E 6
I 6
OSTYPE(hpux9)dnl
DOMAIN(CS.Berkeley.EDU)dnl
E 6
define(`LOCAL_RELAY', CS.Berkeley.EDU)dnl
D 2
MAILER(local)dnl
E 2
MAILER(smtp)dnl

# our local domain
DDCS.Berkeley.EDU
E 1
