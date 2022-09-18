h40391
s 00001/00001/00036
d D 8.7 95/04/21 08:52:48 eric 24 23
c new DOMAIN names
e
s 00001/00001/00036
d D 8.6 95/04/21 08:50:46 eric 23 22
c ultrix4.1 => ultrix4
e
s 00009/00000/00028
d D 8.5 95/04/21 08:39:06 eric 22 21
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00000/00001/00028
d D 8.4 94/11/13 15:51:39 eric 21 20
c delete notsticky; add stickyhost
e
s 00002/00001/00027
d D 8.3 93/10/15 18:18:37 eric 20 19
c don't do CS subdomain hack
e
s 00001/00001/00027
d D 8.2 93/08/12 16:46:08 eric 19 18
c use hidden instead of exposed configuration
e
s 00002/00002/00026
d D 8.1 93/06/07 10:07:09 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00027
d D 6.7 93/05/01 14:40:21 eric 17 16
c USERDB_SPEC => confUSERDB_SPEC
e
s 00001/00001/00027
d D 6.6 93/03/07 07:18:17 eric 16 15
c fix typo
e
s 00002/00001/00026
d D 6.5 93/03/06 10:30:59 eric 15 14
x 13
c need forwarder info after all -- but get it from /etc/sendmail.cw
e
s 00001/00000/00017
d D 6.4 93/03/06 09:49:01 eric 14 13
c add FEATURE(notsticky)
e
s 00001/00010/00016
d D 6.3 93/03/06 08:51:40 eric 13 12
c don't use $=F class -- just set $=w instead
e
s 00001/00001/00025
d D 6.2 93/03/05 08:51:19 eric 12 11
c need extra quotes in USERDB_SPEC
e
s 00000/00000/00026
d D 6.1 92/12/21 16:09:37 eric 11 10
c Release 6
e
s 00001/00001/00025
d D 2.10 92/11/13 22:56:59 eric 10 9
c quote versionid to avoid # problems
e
s 00001/00001/00025
d D 2.9 92/08/06 16:31:15 craig 9 8
c hpux->ultrix
e
s 00001/00001/00025
d D 2.8 92/06/25 12:00:04 eric 8 7
c add monet and dali to the list of hosts we MX for
e
s 00001/00001/00025
d D 2.7 91/12/20 11:38:40 eric 7 6
c mail.cs should be exposed, so mail from root makes sense
e
s 00001/00000/00025
d D 2.6 91/12/20 10:23:30 eric 6 5
c look for databases on local disk; include eecs in match
e
s 00000/00001/00025
d D 2.5 91/12/17 15:54:24 eric 5 4
c make NEWSENDMAIL the default
e
s 00001/00001/00025
d D 2.4 91/12/15 15:12:04 eric 4 3
c fix botch in =F rules
e
s 00001/00001/00025
d D 2.3 91/12/13 14:26:57 eric 3 2
c mail.CS.Berkeley.EDU should masquerade as CS.Berkeley.EDU
e
s 00011/00000/00015
d D 2.2 91/12/12 10:48:58 eric 2 1
c modifications for CS subdomain server
e
s 00015/00000/00000
d D 2.1 91/12/11 12:50:44 eric 1 0
c date and time created 91/12/11 12:50:44 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 18
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 18
I 18
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 18
#
# %sccs.include.redist.sh%
#

I 22
#
#  This is a Berkeley-specific configuration file for a specific
#  machine in the Computer Science Division at Berkeley, and should
#  not be used elsewhere.   It is provided on the sendmail distribution
#  as a sample only.
#
#  This file is for the primary CS Division mail server.
#

E 22
include(`../m4/cf.m4')
D 10
VERSIONID(%W% (Berkeley) %G%)
E 10
I 10
VERSIONID(`%W% (Berkeley) %G%')
E 10
D 9
OSTYPE(hpux)dnl
E 9
I 9
D 23
OSTYPE(ultrix4.1)dnl
E 23
I 23
OSTYPE(ultrix4)dnl
E 23
E 9
D 3
DOMAIN(cs.exposed)dnl
E 3
I 3
D 7
DOMAIN(cs.hidden)dnl
E 7
I 7
D 19
DOMAIN(cs.exposed)dnl
E 19
I 19
D 20
DOMAIN(cs.hidden)dnl
E 20
I 20
D 24
DOMAIN(Berkeley)dnl
E 24
I 24
DOMAIN(Berkeley.EDU)dnl
E 24
MASQUERADE_AS(CS.Berkeley.EDU)dnl
E 20
E 19
I 13
FEATURE(use_cw_file)dnl
I 14
D 21
FEATURE(notsticky)dnl
E 21
E 14
E 13
E 7
E 3
MAILER(local)dnl
MAILER(smtp)dnl
I 6
D 12
define(`USERDB_SPEC', `/usr/local/lib/users.cs.db,/usr/local/lib/users.eecs.db')dnl
E 12
I 12
D 17
define(`USERDB_SPEC', ``/usr/local/lib/users.cs.db,/usr/local/lib/users.eecs.db'')dnl
E 17
I 17
define(`confUSERDB_SPEC', ``/usr/local/lib/users.cs.db,/usr/local/lib/users.eecs.db'')dnl
E 17
E 12
E 6
I 2
D 5
define(`NEWSENDMAIL')dnl
E 5
D 13
DDBerkeley.EDU

# hosts for which we accept and forward mail (must be in .Berkeley.EDU)
D 8
CF CS ucbarpa arpa ucbernie ernie renoir
E 8
I 8
D 15
CF CS ucbarpa arpa ucbernie ernie renoir monet dali
E 15
I 15
CF CS
D 16
CF/etc/sendmail.cw
E 16
I 16
FF/etc/sendmail.cw
E 16
E 15
E 8

LOCAL_RULE_0
D 4
R< @ $=F . $D . > : $*		$@ $>7 $1		@here:... -> ...
E 4
I 4
R< @ $=F . $D . > : $*		$@ $>7 $2		@here:... -> ...
E 4
R$* $=O $* < @ $=F . $D . >	$@ $>7 $1 $2 $3		...@here -> ...

R$* < @ $=F . $D . >		$#local $: $1		use UDB
E 13
E 2
E 1
