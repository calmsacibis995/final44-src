h06475
s 00002/00005/00019
d D 8.3 94/05/16 11:23:32 mckusick 9 8
c update for 4.4BSD manual production
e
s 00001/00001/00023
d D 8.2 94/04/20 12:05:22 mckusick 8 7
c shuffle vi/ex documents
e
s 00000/00000/00024
d D 8.1 93/08/14 11:27:23 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00005/00010
d D 5.5 93/06/08 13:55:12 mckusick 6 5
c document numbering changes for 4.4BSD
e
s 00005/00006/00010
d D 5.4 93/06/05 17:31:21 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00000/00001/00016
d D 5.3 93/03/18 13:13:07 bostic 4 3
c move 11.notes to archives
e
s 00001/00001/00016
d D 5.2 93/03/18 13:06:01 bostic 3 1
c move 09.newsread and 10.etiq into the archives
e
s 00008/00007/00010
d D 5.1.1.1 91/05/07 21:38:27 bostic 2 1
c branch for the 2nd network distribution
e
s 00017/00000/00000
d D 5.1 90/07/01 10:21:10 bostic 1 0
c date and time created 90/07/01 10:21:10 by bostic
e
u
U
f b 
t
T
I 1
#	%W% (Berkeley) %G%

I 6
# The following modules do not build/install:
# 08.mh

E 6
D 2
D 5
# 08.mh		doesn't work right
E 5
D 4
# 11.notes	deprecate
E 4
E 2
I 2
#Missing: 01.begin 02.learn 03.shell 05.dc 06.bc 08.mh 12.edtut 13.edadv
#	  17.jove 18.sed 19.awk 20.msmacros 24.troff 25.trofftut 26.eqn
#	  27.eqnguide 28.tbl 29.refer 30.invert 31.bib 32.diction
E 2
BINDIR=	/usr/share/doc/usd
D 9
FILES=	00.contents Makefile Title
E 9
I 9
FILES=	Makefile Title
E 9
D 2
D 5
SUBDIR=	01.begin 02.learn 03.shell 04.csh 05.dc 06.bc 07.Mail \
D 3
	09.newsread 10.etiq 12.edtut 13.edadv 14.edit 15.vi \
E 3
I 3
	12.edtut 13.edadv 14.edit 15.vi \
E 3
	16.ex 17.jove 18.sed 19.awk 20.msmacros 21.msdiffs 22.memacros \
	23.meref 24.troff 25.trofftut 26.eqn 27.eqnguide 28.tbl 29.refer \
	30.invert 31.bib 32.diction 33.rogue 34.trek
E 5
I 5
D 6
SUBDIR=	01.begin 02.learn 03.shell 04.csh 05.dc 06.bc 07.mail 08.mh \
	09.edtut 10.edadv 11.edit 12.vi 13.ex 14.jove 15.sed 16.awk \
	17.msmacros 18.msdiffs 19.memacros 20.meref 21.troff 22.trofftut \
	23.eqn 24.eqnguide 25.tbl 26.refer 27.invert 28.bib 29.diction \
	30.rogue 31.trek
E 6
I 6
SUBDIR=	01.begin 02.learn 03.shell 04.csh 05.dc 06.bc 07.mail 09.edtut \
D 8
	10.edadv 11.edit 12.vi 13.ex 14.jove 15.sed 16.awk 17.msmacros \
E 8
I 8
	10.edadv 11.vitut 12.exref 13.viref 14.jove 15.sed 16.awk 17.msmacros \
E 8
	18.msdiffs 19.memacros 20.meref 21.troff 22.trofftut 23.eqn \
	24.eqnguide 25.tbl 26.refer 27.invert 28.bib 29.diction 30.rogue \
	31.trek

Title.ps: ${FILES}
D 9
	groff Title > ${.TARGET}

contents.ps: ${FILES}
	groff -ms 00.contents > ${.TARGET}
E 9
I 9
	groff -ms Title > ${.TARGET}
E 9
E 6
E 5
E 2
I 2
SUBDIR=	04.csh 07.Mail \
	09.newsread 10.etiq 14.edit 15.vi \
	16.ex 21.msdiffs 22.memacros \
	23.meref \
	33.rogue 34.trek
E 2

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}

.include <bsd.subdir.mk>
E 1
