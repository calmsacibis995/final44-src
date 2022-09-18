h08303
s 00011/00001/00073
d D 8.3 95/04/21 08:39:01 eric 13 12
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00000/00001/00074
d D 8.2 94/11/13 15:51:36 eric 12 11
c delete notsticky; add stickyhost
e
s 00002/00002/00073
d D 8.1 93/06/07 10:07:42 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00073
d D 6.4 93/03/06 10:30:56 eric 10 9
x 8
c need forwarder info after all -- but get it from /etc/sendmail.cw
e
s 00001/00000/00067
d D 6.3 93/03/06 09:49:03 eric 9 8
c add FEATURE(notsticky)
e
s 00002/00008/00065
d D 6.2 93/03/06 08:54:11 eric 8 7
c don't use $=F when $=w will do
e
s 00000/00000/00073
d D 6.1 92/12/21 16:09:28 eric 7 6
c Release 6
e
s 00001/00001/00072
d D 2.5 92/11/13 22:56:52 eric 6 5
c quote versionid to avoid # problems
e
s 00001/00001/00072
d D 2.4 91/12/15 15:12:06 eric 5 4
c fix botch in =F rules
e
s 00011/00002/00062
d D 2.3 91/12/12 10:48:56 eric 4 3
c modifications for CS subdomain server
e
s 00008/00004/00056
d D 2.2 91/10/05 12:31:04 eric 3 1
c make sure Berkeley.EDU has a trailing dot
e
s 00000/00001/00059
d R 2.2 91/10/03 15:07:29 eric 2 1
c local mailer is automatic
e
s 00060/00000/00000
d D 2.1 91/10/03 00:56:36 eric 1 0
c date and time created 91/10/03 00:56:36 by eric
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
#  This machine has been decommissioned at Berkeley, and hence should
#  not be considered to be tested.  This file is provided as an example
#  only, of how you might set up a fairly complex configuration.
#  Ucbvax was our main relay (both SMTP and UUCP) for many years.
#  At this point I recommend using `FEATURE(mailertable)' instead of
#  `SITECONFIG' for routing of UUCP within your domain.
#

E 13
include(`../m4/cf.m4')
D 6
VERSIONID(%W% (Berkeley) %G%)
E 6
I 6
VERSIONID(`%W% (Berkeley) %G%')
E 6
OSTYPE(bsd4.3)
D 13
DOMAIN(cs.hidden)
E 13
I 13
DOMAIN(CS.Berkeley.EDU)
MASQUERADE_AS(CS.Berkeley.EDU)
E 13
I 8
FEATURE(use_cw_file)
I 9
D 12
FEATURE(notsticky)
E 12
E 9
E 8
MAILER(local)
MAILER(smtp)
MAILER(uucp)
undefine(`UUCP_RELAY')dnl
I 3
DDBerkeley.EDU
E 3

D 4
# additional names we are known by
Fw	/etc/sendmail.cw
E 4
I 4
D 8
# names for which we act as a local forwarding agent
D 10
CF CS ucbarpa arpa ucbernie ernie renoir
E 10
I 10
CF CS
FF/etc/sendmail.cw
E 10
E 4

E 8
# local UUCP connections, and our local uucp name
SITECONFIG(uucp.ucbvax, ucbvax, U)

# remote UUCP connections, and the machine they are on
SITECONFIG(uucp.ucbarpa, ucbarpa.Berkeley.EDU, W)

SITECONFIG(uucp.cogsci, cogsci.Berkeley.EDU, X)

LOCAL_RULE_3
# map old UUCP names into Internet names
UUCPSMTP(bellcore,	bellcore.com)
UUCPSMTP(decvax,	decvax.dec.com)
UUCPSMTP(decwrl,	decwrl.dec.com)
UUCPSMTP(hplabs,	hplabs.hp.com)
UUCPSMTP(lbl-csam,	lbl-csam.arpa)
UUCPSMTP(pur-ee,	ecn.purdue.edu)
UUCPSMTP(purdue,	purdue.edu)
UUCPSMTP(research,	research.att.com)
UUCPSMTP(sdcarl,	sdcarl.ucsd.edu)
UUCPSMTP(sdcsvax,	sdcsvax.ucsd.edu)
UUCPSMTP(ssyx,		ssyx.ucsc.edu)
UUCPSMTP(sun,		sun.com)
UUCPSMTP(ucdavis,	ucdavis.ucdavis.edu)
UUCPSMTP(ucivax,	ics.uci.edu)
UUCPSMTP(ucla-cs,	cs.ucla.edu)
UUCPSMTP(ucla-se,	seas.ucla.edu)
UUCPSMTP(ucsbcsl,	ucsbcsl.ucsb.edu)
UUCPSMTP(ucscc,		c.ucsc.edu)
UUCPSMTP(ucsd,		ucsd.edu)
UUCPSMTP(ucsfcgl,	cgl.ucsf.edu)
UUCPSMTP(unmvax,	unmvax.cs.unm.edu)
UUCPSMTP(uwvax,		spool.cs.wisc.edu)

LOCAL_RULE_0
I 4

E 4
I 3
# make sure we handle the local domain as absolute
R$* <  @ $* $D > $*		$: $1 < @ $2 $D . > $3
I 4

D 8
# handle names we forward for as though they were local, so we will use UDB
D 5
R< @ $=F . $D . > : $*		$@ $>7 $1		@here:... -> ...
E 5
I 5
R< @ $=F . $D . > : $*		$@ $>7 $2		@here:... -> ...
E 8
I 8
# handle Berkeley.EDU as local, so we will use UDB
E 8
E 5
R< @ $D . > : $*		$@ $>7 $1		@here:... -> ...
D 8
R$* $=O $* < @ $=F . $D . >	$@ $>7 $1 $2 $3		...@here -> ...
E 8
R$* $=O $* < @ $D . >		$@ $>7 $1 $2 $3		...@here -> ...
D 8

R$* < @ $=F . $D . >		$#local $: $1		use UDB
E 8
E 4

E 3
# handle local UUCP connections in the Berkeley.EDU domain
D 3
R$+<@cnmat.Berkeley.EDU>	$#uucp$@cnmat$:$1
R$+<@cnmat.CS.Berkeley.EDU>	$#uucp$@cnmat$:$1
R$+<@craig.Berkeley.EDU>	$#uucp$@craig$:$1
R$+<@craig.CS.Berkeley.EDU>	$#uucp$@craig$:$1
E 3
I 3
R$+<@cnmat.$D . >		$#uucp$@cnmat$:$1
R$+<@cnmat.CS.$D . >		$#uucp$@cnmat$:$1
R$+<@craig.$D . >		$#uucp$@craig$:$1
R$+<@craig.CS.$D . >		$#uucp$@craig$:$1
E 3
E 1
