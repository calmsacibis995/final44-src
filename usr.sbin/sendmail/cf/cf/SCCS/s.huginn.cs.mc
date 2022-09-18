h43919
s 00012/00002/00024
d D 8.4 95/04/21 08:39:12 eric 4 3
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00000/00001/00026
d D 8.3 94/11/13 15:51:40 eric 3 2
c delete notsticky; add stickyhost
e
s 00001/00002/00026
d D 8.2 94/06/26 15:37:53 eric 2 1
c be sure to get the user database
e
s 00028/00000/00000
d D 8.1 94/06/26 15:30:16 eric 1 0
c date and time created 94/06/26 15:30:16 by eric
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

I 4
#
#  This is a Berkeley-specific configuration file for a specific
#  machine in the Computer Science Division at Berkeley, and should
#  not be used elsewhere.   It is provided on the sendmail distribution
#  as a sample only.
#
#  This file is for the backup CS Division mail server.
#

E 4
include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
D 4
OSTYPE(hpux)dnl
D 2
DOMAIN(Berkeley)dnl
MASQUERADE_AS(CS.Berkeley.EDU)dnl
E 2
I 2
DOMAIN(cs.hidden)dnl
E 4
I 4
OSTYPE(hpux9)dnl
DOMAIN(CS.Berkeley.EDU)dnl
MASQUERADE_AS(CS.Berkeley.EDU)dnl
E 4
E 2
D 3
FEATURE(notsticky)dnl
E 3
MAILER(local)dnl
MAILER(smtp)dnl
DDBerkeley.EDU

# hosts for which we accept and forward mail (must be in .Berkeley.EDU)
CF CS
FF/etc/sendmail.cw

LOCAL_RULE_0
R< @ $=F . $D . > : $*		$@ $>7 $2		@here:... -> ...
R$* $=O $* < @ $=F . $D . >	$@ $>7 $1 $2 $3		...@here -> ...

R$* < @ $=F . $D . >		$#local $: $1		use UDB
E 1
