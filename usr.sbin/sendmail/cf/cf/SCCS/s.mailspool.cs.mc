h32018
s 00018/00002/00014
d D 8.2 95/05/18 08:21:03 eric 3 2
c add mailspool.cs.mc
e
s 00002/00002/00014
d D 8.1 93/06/07 10:06:44 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00000/00000
d D 6.1 93/02/27 12:03:46 eric 1 0
c date and time created 93/02/27 12:03:46 by eric
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
#  This file is for our mail spool machine.  For a while we were using
#  "root.machinename" instead of "root+machinename", so this is included
#  for back compatibility.
#

E 3
include(`../m4/cf.m4')
VERSIONID(`%W% (Berkeley) %G%')
OSTYPE(sunos4.1)dnl
D 3
DOMAIN(cs.hidden)dnl
FEATURE(use_cw_file)dnl
E 3
I 3
DOMAIN(CS.Berkeley.EDU)dnl
E 3
MAILER(local)dnl
MAILER(smtp)dnl
I 3

LOCAL_CONFIG
CDroot sys-custodian

LOCAL_RULE_3
R$=D . $+		$1 + $2
E 3
E 1
