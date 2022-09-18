h06400
s 00001/00001/00013
d D 8.2 95/04/21 08:41:50 eric 20 19
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00002/00012
d D 8.1 93/06/07 10:09:42 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00012
d D 6.4 93/03/18 16:01:14 eric 18 17
c clean up confUSERDB_SPEC
e
s 00001/00001/00012
d D 6.3 93/03/18 15:51:04 eric 17 16
c fix USERDB_SPEC to have enough quotes
e
s 00001/00001/00012
d D 6.2 93/03/03 16:30:24 eric 16 15
c check both CS and EECS user databases
e
s 00000/00000/00013
d D 6.1 92/12/21 16:11:39 eric 15 14
c Release 6
e
s 00001/00001/00012
d D 2.14 92/11/13 22:56:25 eric 14 13
c quote versionid to avoid # problems
e
s 00000/00001/00013
d D 2.13 92/07/24 10:15:02 eric 13 12
c some cleanup for EECS subdomain
e
s 00001/00001/00013
d D 2.12 91/12/20 12:02:41 eric 12 11
c if we are running new sendmail, assume no_wildcard_MX
e
s 00001/00001/00013
d D 2.11 91/12/12 10:50:18 eric 11 10
c don't assume @cs in USERDB_SPEC
e
s 00001/00001/00013
d D 2.10 91/11/22 15:01:26 eric 10 9
c adjust user database specification
e
s 00001/00000/00013
d D 2.9 91/11/13 15:40:52 eric 9 8
c add definition of user database file
e
s 00001/00005/00012
d D 2.8 91/10/03 10:27:12 eric 8 7
c move CS subdomain hack into hack directory
e
s 00001/00003/00016
d D 2.7 91/10/03 09:57:00 eric 7 6
c break off Berkeley (non-cs) definitions
e
s 00001/00001/00018
d D 2.6 91/10/03 01:33:12 eric 6 5
c drop the wildcard thing until the new sendmail is installed
e
s 00002/00002/00017
d D 2.5 91/10/03 01:14:49 eric 5 4
c use $j as hostname instead of $w (so it can be qualified on ultrix)
e
s 00001/00001/00018
d D 2.4 91/10/02 23:26:08 eric 4 3
c csnet relay moved
e
s 00005/00000/00014
d D 2.3 91/10/02 21:42:22 eric 3 2
c hacks to recognize local names under Berkeley.EDU or CS.Berkeley.EDU
e
s 00001/00001/00013
d D 2.2 91/10/02 15:33:20 eric 2 1
c misnamed feature
e
s 00014/00000/00000
d D 2.1 91/10/02 14:49:44 eric 1 0
c date and time created 91/10/02 14:49:44 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 19
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 19
I 19
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 19
#
# %sccs.include.redist.sh%
#
divert(0)
D 14
VERSIONID(%W% (Berkeley) %G%)
E 14
I 14
VERSIONID(`%W% (Berkeley) %G%')
E 14
D 7
define(`UUCP_RELAY', `ucbvax.Berkeley.EDU')dnl
define(`BITNET_RELAY', `jade.Berkeley.EDU')dnl
D 4
define(`CSNET_RELAY', `Relay.CS.NET')dnl
E 4
I 4
define(`CSNET_RELAY', `Relay.Prime.COM')dnl
E 7
I 7
D 20
DOMAIN(Berkeley)dnl
E 20
I 20
DOMAIN(Berkeley.EDU)dnl
E 20
E 7
E 4
D 2
FEATURE(no_wildcard_mx)dnl
E 2
I 2
D 6
FEATURE(no_wildcard_MX)dnl
E 6
I 6
D 12
#FEATURE(no_wildcard_MX)dnl
E 12
I 12
D 13
ifdef(`_OLD_SENDMAIL_', `', `FEATURE(no_wildcard_MX)')dnl
E 13
E 12
E 6
I 3
D 8
LOCAL_RULE_0
# hacks to allow local hostnames as host.Berkeley.EDU or host.CS.Berkeley.EDU
D 5
R$* < @ $=w .CS.Berkeley.EDU > $*	$: $1 < @ $w > $3
R$* < @ $=w .Berkeley.EDU > $*		$: $1 < @ $w > $3
E 5
I 5
R$* < @ $=w .CS.Berkeley.EDU > $*	$: $1 < @ $j > $3
R$* < @ $=w .Berkeley.EDU > $*		$: $1 < @ $j > $3
E 5
divert(0)
E 8
I 8
HACK(cssubdomain)dnl
I 9
D 10
define(`USERDB_FILE', `/usr/sww/share/lib/users.cs.db')dnl
E 10
I 10
D 11
define(`USERDB_SPEC', `/usr/sww/share/lib/users.cs.db, @cs')dnl
E 11
I 11
D 16
define(`USERDB_SPEC', `/usr/sww/share/lib/users.cs.db')dnl
E 16
I 16
D 17
define(`USERDB_SPEC', `/usr/sww/share/lib/users.cs.db,/usr/sww/share/lib/users.eecs.db')dnl
E 17
I 17
D 18
define(`USERDB_SPEC', ``/usr/sww/share/lib/users.cs.db,/usr/sww/share/lib/users.eecs.db'')dnl
E 18
I 18
define(`confUSERDB_SPEC',
	`/usr/sww/share/lib/users.cs.db,/usr/sww/share/lib/users.eecs.db')dnl
E 18
E 17
E 16
E 11
E 10
E 9
E 8
E 3
E 2
E 1
