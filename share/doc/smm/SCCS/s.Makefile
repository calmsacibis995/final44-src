h17735
s 00003/00012/00016
d D 8.2 94/05/10 17:22:06 mckusick 11 10
c update for 4.4BSD-Lite
e
s 00000/00000/00028
d D 8.1 93/06/10 17:58:29 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00025
d D 5.5 93/06/10 17:58:19 bostic 9 7
c remove 18.termdesc; 13.net -> 18.net, create 13.amd
e
s 00000/00000/00028
d R 8.1 93/06/08 17:41:57 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00004/00016
d D 5.4 93/06/08 16:56:02 mckusick 7 4
c document numbering changes for 4.4BSD
e
s 00000/00000/00020
d R 8.1 93/06/01 23:03:51 bostic 6 4
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00001/00015
d D 5.2.1.2 91/05/07 21:45:51 bostic 5 3
c only install setup on vaxen and tahoes
e
s 00007/00001/00013
d D 5.3 91/05/07 21:44:18 bostic 4 2
c setup only applies to VAX and tahoe, now
e
s 00006/00004/00010
d D 5.2.1.1 91/05/07 18:23:04 bostic 3 2
c branch for the 2nd network distribution
e
s 00001/00002/00013
d D 5.2 91/05/07 18:21:48 bostic 2 1
c put setup back in
e
s 00015/00000/00000
d D 5.1 90/06/30 15:06:41 bostic 1 0
c new doc makefiles
e
u
U
f b 
t
T
I 1
#	%W% (Berkeley) %G%

I 7
# The following modules do not build/install:
D 9
# 10.named
E 9
I 9
# 10.named, 13.amd
E 9

E 7
I 3
# Missing: 03.kdebug 09.uucpimpl 12.uchanges 13.kchanges 17.security
#	   18.password 19.porttour 21.uucpnet
E 3
D 2
# 01.setup isn't right yet.
E 2
BINDIR=	/usr/share/doc/smm
D 11
FILES=	00.contents Makefile Title
E 11
I 11
FILES=	Makefile Title
E 11
D 2
SUBDIR=	02.config 03.kdebug 04.quotas 05.fsck 06.lpd 07.sendmailop \
E 2
I 2
D 3
D 4
SUBDIR=	01.setup 02.config 03.kdebug 04.quotas 05.fsck 06.lpd 07.sendmailop \
E 4
I 4
D 7
SUBDIR=	02.config 03.kdebug 04.quotas 05.fsck 06.lpd 07.sendmailop \
E 4
E 2
	08.timedop 09.uucpimpl 10.newsop 11.named 12.uchanges 13.kchanges \
	14.fastfs 15.net 16.sendmail 17.security 18.password 19.porttour \
	20.termdesc 21.uucpnet 22.timed
E 7
I 7
SUBDIR=	01.setup 02.config 03.fsck 04.quotas 05.fastfs 06.nfs 07.lpd \
D 9
	08.sendmailop 09.sendmail 11.timedop 12.timed 13.net 14.uucpimpl \
	15.uucpnet 16.security 17.password 18.termdesc
E 9
I 9
	08.sendmailop 09.sendmail 11.timedop 12.timed 14.uucpimpl \
D 11
	15.uucpnet 16.security 17.password 18.net
E 11
I 11
	15.uucpnet 16.security 17.password 18.net 19.perl
E 11
E 9

Title.ps: ${FILES}
D 11
	groff Title > ${.TARGET}

contents.ps: ${FILES}
	groff -ms 00.contents > ${.TARGET}
E 7
I 4

.if	${MACHINE} == "tahoe"
SUBDIR+=01.setup
.elif	${MACHINE} == "vax"
SUBDIR+=01.setup
.endif
E 11
I 11
	groff -ms Title > ${.TARGET}
E 11
E 4
E 3
I 3
D 5
SUBDIR=	01.setup 02.config 04.quotas 05.fsck 06.lpd 07.sendmailop \
E 5
I 5
SUBDIR=	02.config 04.quotas 05.fsck 06.lpd 07.sendmailop \
E 5
	08.timedop 10.newsop 11.named \
	14.fastfs 15.net 16.sendmail \
	20.termdesc 22.timed
I 5

.if	${MACHINE} == "tahoe"
SUBDIR+=01.setup
.elif	${MACHINE} == "vax"
SUBDIR+=01.setup
.endif
E 5
E 3

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}

.include <bsd.subdir.mk>
E 1
