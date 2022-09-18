h15277
s 00002/00002/00015
d D 8.1 93/06/07 10:07:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00017
d D 6.1 92/12/21 16:09:30 eric 4 3
c Release 6
e
s 00002/00002/00015
d D 1.3 91/12/17 13:15:26 rwh 3 2
c Change hera to diva for Masquerade.
e
s 00000/00001/00017
d D 1.2 91/10/11 21:52:43 eric 2 1
c doesn't need /etc/sendmail.cw
e
s 00018/00000/00000
d D 1.1 91/10/10 11:51:17 eric 1 0
c date and time created 91/10/10 11:51:17 by eric
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

include(`../m4/cf.m4')
VERSIONID(%W% (Berkeley) %G%)
OSTYPE(hpux)dnl
DOMAIN(cs.exposed)dnl
D 3
define(`LOCAL_RELAY', hera.Berkeley.EDU)dnl
define(`MASQUERADE_NAME', hera.Berkeley.EDU)dnl
E 3
I 3
define(`LOCAL_RELAY', diva.Berkeley.EDU)dnl
define(`MASQUERADE_NAME', diva.Berkeley.EDU)dnl
E 3
MAILER(local)dnl
MAILER(smtp)dnl
D 2
Fw/etc/sendmail.cw
E 2
E 1
