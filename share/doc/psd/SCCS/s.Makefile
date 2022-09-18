h08353
s 00001/00004/00018
d D 8.2 94/05/23 14:40:19 mckusick 8 7
c update for 4.4BSD manuals
e
s 00000/00000/00022
d D 8.1 93/06/08 18:42:42 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00021
d D 5.4 93/06/08 18:40:45 bostic 6 4
c ps1 -> psd
e
s 00000/00000/00022
d R 8.1 93/06/08 18:39:11 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00003/00011
d D 5.3 93/06/08 18:38:58 mckusick 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00003/00010
d D 5.2 93/06/05 16:02:43 bostic 3 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00007/00004/00009
d D 5.1.1.1 91/05/07 18:09:04 bostic 2 1
c branch for the 2nd network distribution
e
s 00013/00000/00000
d D 5.1 90/07/01 10:21:41 bostic 1 0
c date and time created 90/07/01 10:21:41 by bostic
e
u
U
f b 
t
T
I 1
#	%W% (Berkeley) %G%

I 4
# The following modules do not build/install:
# 10.gdb, 13.rcs

E 4
I 2
# Missing:  00.contents 01.Clang 02.f77 03.f77io 05.as 09.lint 10.adb 11.dbx
#	    12.make 15.yacc 16.lex 17.m4

E 2
D 6
BINDIR=	/usr/share/doc/ps1
E 6
I 6
BINDIR=	/usr/share/doc/psd
E 6
D 2
D 8
FILES=	00.contents Makefile Title
E 8
I 8
FILES=	Makefile Title
E 8
D 3
SUBDIR=	01.Clang 02.f77 03.f77io 04.pascal 05.as 06.sysman 07.ipctut \
	08.ipc 09.lint 10.adb 11.dbx 12.make 13.rcs 14.sccs 15.yacc \
	16.lex 17.m4 18.curses
E 3
I 3
SUBDIR=	01.cacm 02.implement 03.iosys 04.uprog 05.sysman 06.Clang \
D 4
	07.pascal 08.f77 09.f77io 10.gdb 11.adb 12.make 13.rcs \
	14.sccs 15.yacc 16.lex 17.m4 18.gprof 19.curses 20.ipctut \
	21.ipc
E 4
I 4
	07.pascal 08.f77 09.f77io 11.adb 12.make 14.sccs 15.yacc \
	16.lex 17.m4 18.gprof 19.curses 20.ipctut 21.ipc

Title.ps: ${FILES}
	groff Title > ${.TARGET}
D 8

contents.ps: ${FILES}
	groff -ms 00.contents > ${.TARGET}
E 8
E 4
E 3
E 2
I 2
FILES=	Makefile Title
SUBDIR=	04.pascal 06.sysman 07.ipctut \
	08.ipc 13.rcs 14.sccs \
	18.curses
E 2

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}

.include <bsd.subdir.mk>
E 1
