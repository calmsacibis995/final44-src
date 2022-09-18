h43313
s 00003/00002/00034
d D 8.7 95/04/21 08:52:48 eric 23 22
c new DOMAIN names
e
s 00009/00000/00027
d D 8.6 95/04/21 08:39:04 eric 22 21
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00001/00001/00026
d D 8.5 95/02/20 13:24:39 eric 21 20
c use eecs.hidden domain
e
s 00001/00001/00026
d D 8.4 95/02/06 13:56:59 eric 20 19
c fix COE problems (getting mapped into @EECS)
e
s 00001/00001/00026
d D 8.3 95/01/06 14:06:49 eric 19 18
c get order of user databases correct
e
s 00000/00001/00027
d D 8.2 94/11/13 15:51:37 eric 18 17
c delete notsticky; add stickyhost
e
s 00002/00002/00026
d D 8.1 93/06/07 10:07:11 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00027
d D 6.5 93/05/01 14:40:21 eric 16 15
c USERDB_SPEC => confUSERDB_SPEC
e
s 00001/00000/00027
d D 6.4 93/03/06 10:30:58 eric 15 14
x 13
c need forwarder info after all -- but get it from /etc/sendmail.cw
e
s 00001/00000/00017
d D 6.3 93/03/06 09:49:02 eric 14 13
c add FEATURE(notsticky)
e
s 00001/00010/00016
d D 6.2 93/03/06 08:54:12 eric 13 12
c don't use $=F when $=w will do
e
s 00000/00000/00026
d D 6.1 92/12/21 16:09:36 eric 12 11
c Release 6
e
s 00001/00001/00025
d D 2.11 92/11/13 22:56:57 eric 11 10
c quote versionid to avoid # problems
e
s 00001/00001/00025
d D 2.10 92/07/24 10:27:02 eric 10 9
c oops... ultrix => ultrix4.1
e
s 00003/00003/00023
d D 2.9 92/07/24 10:26:19 eric 9 8
c convert mail.cs.mc => mail.eecs.mc
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
D 17
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 17
I 17
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 17
#
# %sccs.include.redist.sh%
#

I 22
#
#  This is a Berkeley-specific configuration file for a specific
#  machine in Electrical Engineering and Computer Sciences at Berkeley,
#  and should not be used elsewhere.   It is provided on the sendmail
#  distribution as a sample only.
#
#  This file is for the primary EECS mail server.
#

E 22
include(`../m4/cf.m4')
D 11
VERSIONID(%W% (Berkeley) %G%)
E 11
I 11
VERSIONID(`%W% (Berkeley) %G%')
E 11
D 9
OSTYPE(hpux)dnl
D 3
DOMAIN(cs.exposed)dnl
E 3
I 3
D 7
DOMAIN(cs.hidden)dnl
E 7
I 7
DOMAIN(cs.exposed)dnl
E 9
I 9
D 10
OSTYPE(ultrix)dnl
E 10
I 10
D 23
OSTYPE(ultrix4.1)dnl
E 10
D 20
DOMAIN(eecs.hidden)dnl
E 20
I 20
D 21
DOMAIN(eecs.exposed)dnl
E 21
I 21
DOMAIN(eecs.hidden)dnl
E 23
I 23
OSTYPE(ultrix4)dnl
DOMAIN(EECS.Berkeley.EDU)dnl
MASQUERADE_AS(EECS.Berkeley.EDU)dnl
E 23
E 21
E 20
I 13
FEATURE(use_cw_file)dnl
I 14
D 18
FEATURE(notsticky)dnl
E 18
E 14
E 13
E 9
E 7
E 3
MAILER(local)dnl
MAILER(smtp)dnl
I 6
D 16
define(`USERDB_SPEC', `/usr/local/lib/users.cs.db,/usr/local/lib/users.eecs.db')dnl
E 16
I 16
D 19
define(`confUSERDB_SPEC', `/usr/local/lib/users.cs.db,/usr/local/lib/users.eecs.db')dnl
E 19
I 19
define(`confUSERDB_SPEC', `/usr/local/lib/users.eecs.db,/usr/local/lib/users.cs.db,/usr/local/lib/users.coe.db')dnl
E 19
E 16
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
D 9
CF CS ucbarpa arpa ucbernie ernie renoir monet dali
E 9
I 9
CF EECS
I 15
FF/etc/sendmail.cw
E 15
E 9
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
