h57968
s 00013/00002/00024
d D 8.2 95/04/21 08:39:08 eric 3 2
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00024
d D 8.1 93/06/07 10:07:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 6.1 93/05/01 09:00:46 eric 1 0
c date and time created 93/05/01 09:00:46 by eric
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
#  This is a Berkeley-specific configuration file for a specific
#  machine in the Computer Science Division at Berkeley, and should
#  not be used elsewhere.   It is provided on the sendmail distribution
#  as a sample only.
#
#  This file is for a home machine that wants to masquerade as an
#  on-campus machine.  Additionally, all addresses without a hostname
#  will be forwarded to that machine.
#

E 3
include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
OSTYPE(bsd4.4)dnl
D 3
DOMAIN(cs.exposed)dnl
E 3
I 3
DOMAIN(CS.Berkeley.EDU)dnl
E 3
define(`LOCAL_RELAY', vangogh.CS.Berkeley.EDU)dnl
D 3
define(`MASQUERADE_NAME', vangogh.CS.Berkeley.EDU)dnl
E 3
I 3
MASQUERADE_AS(vangogh.CS.Berkeley.EDU)dnl
E 3
MAILER(local)dnl
MAILER(smtp)dnl

# accept mail sent to the domain head
DDBostic.COM

LOCAL_RULE_0
# accept mail sent to the domain head
R< @ $D . > : $*		$@ $>7 $1		@here:... -> ...
R$* $=O $* < @ $D . >		$@ $>7 $1 $2 $3		...@here -> ...
R$* < @ $D . >			$#local $: $1		user@here -> user
E 1
