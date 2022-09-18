h46276
s 00011/00001/00017
d D 8.3 95/04/21 08:39:00 eric 13 12
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00001/00016
d D 8.2 94/01/26 17:38:49 eric 12 11
c respond to python as well as okeeffe
e
s 00002/00002/00015
d D 8.1 93/06/07 10:07:59 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00016
d D 6.3 93/03/08 18:11:04 eric 10 9
c accept email for okeeffe
e
s 00001/00001/00015
d D 6.2 93/03/05 08:24:16 eric 9 8
c up MCI cache size
e
s 00000/00000/00016
d D 6.1 92/12/21 16:09:27 eric 8 7
c Release 6
e
s 00001/00004/00015
d D 2.7 92/12/20 13:11:42 eric 7 6
c change technique for setting connection cache size
e
s 00004/00000/00015
d D 2.6 92/11/14 00:44:53 eric 6 5
c set up the number of simultaneous connections
e
s 00001/00001/00014
d D 2.5 92/11/13 22:56:50 eric 5 4
c quote versionid to avoid # problems
e
s 00000/00001/00015
d D 2.4 91/12/17 15:54:23 eric 4 3
c make NEWSENDMAIL the default
e
s 00002/00000/00014
d D 2.3 91/10/05 12:37:57 eric 3 2
c has new sendmail support
e
s 00000/00001/00014
d D 2.2 91/10/03 15:07:26 eric 2 1
c local mailer is automatic
e
s 00015/00000/00000
d D 2.1 91/10/02 23:33:37 eric 1 0
c date and time created 91/10/02 23:33:37 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 11
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 11
I 11
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 11
#
# %sccs.include.redist.sh%
#

I 13
#
#  This is a Berkeley-specific configuration file for a specific
#  machine in the Computer Science Division at Berkeley, and should
#  not be used elsewhere.   It is provided on the sendmail distribution
#  as a sample only.
#
#  This file is for the BSD development machine; it has some parameters
#  set up (to stress sendmail) and accepts mail for some other machines.
#

E 13
include(`../m4/cf.m4')
D 5
VERSIONID(%W% (Berkeley) %G%)
E 5
I 5
VERSIONID(`%W% (Berkeley) %G%')
E 5
D 13
DOMAIN(cs.exposed)dnl
E 13
I 13
DOMAIN(CS.Berkeley.EDU)dnl
E 13
OSTYPE(bsd4.4)dnl
I 3
MAILER(local)dnl
E 3
D 2
MAILER(local)dnl
E 2
MAILER(smtp)dnl
I 6
D 7
LOCAL_CONFIG

# set up the number of simultaneous connections
Ok4
E 7
I 7
D 9
define(`MCI_CACHE_SIZE', 4)
E 9
I 9
define(`MCI_CACHE_SIZE', 5)
I 10
D 12
Cw okeeffe
E 12
I 12
Cw okeeffe.CS.Berkeley.EDU
Cw python.CS.Berkeley.EDU
E 12
E 10
E 9
E 7
E 6
I 3
D 4
define(`NEWSENDMAIL')dnl
E 4
E 3
E 1
