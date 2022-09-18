h27076
s 00001/00001/00015
d D 8.6 95/04/21 08:41:48 eric 14 13
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00001/00001/00015
d D 8.5 94/02/18 13:04:16 eric 13 12
c change default BITNET gateway from jade to CMSA
e
s 00000/00001/00016
d D 8.4 93/12/20 10:49:10 eric 12 11
c delete CSNET domain
e
s 00003/00000/00014
d D 8.3 93/10/05 13:28:19 eric 11 10
c change Berkeley defaults somewhat
e
s 00001/00001/00013
d D 8.2 93/08/07 06:25:17 eric 10 9
c change CSNET relay
e
s 00002/00002/00012
d D 8.1 93/06/07 10:09:39 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00013
d D 6.3 93/02/20 14:20:29 eric 8 7
c add redirect feature
e
s 00000/00001/00013
d D 6.2 93/02/14 15:09:54 eric 7 6
c delete no_wildcard_MX
e
s 00000/00000/00014
d D 6.1 92/12/21 16:11:40 eric 6 5
c Release 6
e
s 00001/00001/00013
d D 2.5 92/11/13 22:56:26 eric 5 4
c quote versionid to avoid # problems
e
s 00001/00000/00013
d D 2.4 92/07/24 10:15:09 eric 4 3
c some cleanup for EECS subdomain
e
s 00000/00001/00013
d D 2.3 91/12/17 15:54:46 eric 3 2
c make NEWSENDMAIL the default
e
s 00001/00000/00013
d D 2.2 91/12/12 11:54:28 eric 2 1
c NEWSENDMAIL is the default
e
s 00013/00000/00000
d D 2.1 91/10/03 09:56:33 eric 1 0
c date and time created 91/10/03 09:56:33 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 9
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 9
I 9
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 9
#
# %sccs.include.redist.sh%
#
divert(0)
D 5
VERSIONID(%W% (Berkeley) %G%)
E 5
I 5
VERSIONID(`%W% (Berkeley) %G%')
E 5
D 14
define(`UUCP_RELAY', `ucbvax.Berkeley.EDU')dnl
E 14
I 14
DOMAIN(berkeley-only)dnl
E 14
D 13
define(`BITNET_RELAY', `jade.Berkeley.EDU')dnl
E 13
I 13
define(`BITNET_RELAY', `CMSA.Berkeley.EDU')dnl
E 13
D 10
define(`CSNET_RELAY', `Relay.Prime.COM')dnl
E 10
I 10
D 12
define(`CSNET_RELAY', `Relay.CV.COM')dnl
E 12
I 11
define(`confFORWARD_PATH', `$z/.forward.$w:$z/.forward')dnl
define(`confCW_FILE', `-o /etc/sendmail.cw')dnl
E 11
E 10
I 8
FEATURE(redirect)dnl
I 11
FEATURE(use_cw_file)dnl
E 11
E 8
I 4
D 7
ifdef(`_OLD_SENDMAIL_', `', `FEATURE(no_wildcard_MX)')dnl
E 7
E 4
I 2
D 3
define(`NEWSENDMAIL')dnl
E 3
E 2
E 1
