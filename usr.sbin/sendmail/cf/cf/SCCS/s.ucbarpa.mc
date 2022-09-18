h43365
s 00009/00001/00016
d D 8.2 95/04/21 08:39:00 eric 6 5
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00015
d D 8.1 93/06/07 10:07:40 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00017
d D 6.1 92/12/21 16:09:28 eric 4 3
c Release 6
e
s 00001/00001/00016
d D 2.2 92/11/13 22:56:51 eric 3 1
c quote versionid to avoid # problems
e
s 00000/00001/00016
d R 2.2 91/10/03 15:07:27 eric 2 1
c local mailer is automatic
e
s 00017/00000/00000
d D 2.1 91/10/03 00:56:15 eric 1 0
c date and time created 91/10/03 00:56:15 by eric
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
#  This machine has been decommissioned at Berkeley, and hence should
#  not be considered to be tested.  This file is provided as an example
#  only, of how you might set up a joint SMTP/UUCP configuration.  At
#  this point I recommend using `FEATURE(mailertable)' instead of
#  `SITECONFIG'.  See also ucbvax.mc.
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
DOMAIN(cs.exposed)dnl
E 6
I 6
DOMAIN(CS.Berkeley.EDU)dnl
E 6
OSTYPE(bsd4.4)dnl
MAILER(local)dnl
MAILER(smtp)dnl
MAILER(uucp)dnl
SITECONFIG(uucp.ucbarpa, ucbarpa, U)
E 1
