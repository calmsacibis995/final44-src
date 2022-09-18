h50181
s 00013/00002/00016
d D 8.4 95/04/21 08:39:15 eric 11 10
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00001/00006/00017
d D 8.3 95/04/03 15:52:21 eric 10 9
c byzantium is no longer special cased
e
s 00005/00000/00018
d D 8.2 94/05/22 09:13:29 eric 9 8
c add support for byzantium
e
s 00002/00002/00016
d D 8.1 93/06/07 10:06:46 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00018
d D 6.1 92/12/21 16:09:29 eric 7 6
c Release 6
e
s 00001/00001/00017
d D 2.5 92/11/13 22:56:52 eric 6 5
c quote versionid to avoid # problems
e
s 00000/00001/00018
d D 2.4 92/03/09 11:06:08 eric 5 4
c it's a new sendmail now
e
s 00001/00000/00018
d D 2.3 91/12/20 12:02:14 eric 4 2
c this is an old sendmail implementation (for the time being)
e
s 00000/00001/00017
d R 2.3 91/10/03 15:07:29 eric 3 2
c local mailer is automatic
e
s 00001/00000/00017
d D 2.2 91/10/03 10:33:06 eric 2 1
c make vangogh the local relay
e
s 00017/00000/00000
d D 2.1 91/10/03 01:54:53 eric 1 0
c date and time created 91/10/03 01:54:53 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 8
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 8
I 8
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 8
#
# %sccs.include.redist.sh%
#

I 11
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

E 11
include(`../m4/cf.m4')
D 6
VERSIONID(%W% (Berkeley) %G%)
E 6
I 6
VERSIONID(`%W% (Berkeley) %G%')
E 6
OSTYPE(bsd4.4)dnl
I 4
D 5
OLDSENDMAIL
E 5
E 4
D 11
DOMAIN(cs.exposed)dnl
E 11
I 11
DOMAIN(CS.Berkeley.EDU)dnl
E 11
I 2
define(`LOCAL_RELAY', vangogh.CS.Berkeley.EDU)dnl
E 2
D 11
define(`MASQUERADE_NAME', vangogh.CS.Berkeley.EDU)dnl
E 11
I 11
MASQUERADE_AS(vangogh.CS.Berkeley.EDU)dnl
E 11
I 10
FEATURE(use_cw_file)dnl
E 10
MAILER(local)dnl
MAILER(smtp)dnl
D 10
Fw/etc/sendmail.cw
I 9

LOCAL_RULE_0
# handle byzantium specially: no IP forwarding for now, so we map to
# it's name on a different network
R$* < @ Byzantium.$m. > $*	$#relay $@ byzantium-247.$m. $: $1 < @ Byzantium.$m. > $2
E 10
E 9
E 1
