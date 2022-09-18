h00047
s 00000/00000/00005
d R 8.2 93/06/06 14:36:01 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00005
d D 8.1 93/06/06 14:31:09 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00066/00003
d D 4.10 90/05/11 15:14:28 bostic 12 11
c first pass for new make
e
s 00006/00009/00063
d D 4.9 89/05/11 09:46:27 bostic 11 10
c file reorg, pathnames.h, paths.h
e
s 00024/00024/00046
d D 4.8 88/10/22 16:57:58 bostic 10 9
c cleanup, add manual page
e
s 00053/00067/00017
d D 4.7 87/11/16 17:42:34 bostic 9 6
c new template
e
s 00053/00067/00017
d R 4.7 87/10/26 15:52:09 bostic 8 6
c new template
e
s 00053/00067/00017
d R 4.7 87/06/18 15:42:34 bostic 7 6
c new template
e
s 00002/00000/00082
d D 4.6 87/05/31 21:28:01 bostic 6 5
c added depend label
e
s 00001/00001/00081
d D 4.5 83/06/30 14:06:57 sam 5 4
c from sun
e
s 00002/00001/00080
d D 4.4 83/02/11 16:08:18 rrh 4 3
c define DESTDIR, add forgotten dependencies
e
s 00024/00013/00057
d D 4.3 82/11/06 17:36:39 rrh 3 2
c added sccs get; changed to refer to the .sh files; removed deroff
e
s 00006/00004/00064
d D 4.2 82/11/06 14:34:59 rrh 2 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00068/00000/00000
d D 4.1 82/11/06 13:48:00 rrh 1 0
c Oldest available version at Berkeley
e
u
U
t
T
I 1
D 12
#
D 9
#	%W%	(Berkeley)	%E%
E 9
I 9
D 10
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 10
I 10
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 10
E 9
#
D 9
#	make file for STYLE and DICTION
E 9
I 9
D 10
#	%W%	(Berkeley)	%G%
E 10
I 10
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
E 9
#
E 12
I 10
#	%W% (Berkeley) %G%
D 12
#
E 10
D 9
#	BIN is the directory for storing the object code
#		for the 3 programs that make up style
#	DICT is the full pathname of the file dict.d, the
#		dictionary file used by DICTION
#
I 4
DESTDIR=
E 4
I 3
SRCS = \
	abbrev.c conp.h dict.c dict.d \
	diction.c diction.sh edict.c ehash.c \
	explain.d \
	end.l getopt.c names.h nhash.c \
	nwords.l outp.c part.l pscan.c \
	style.h style.sh explain.sh ydict.c \
	README
E 9
I 9
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	diction.c nwords.c end.c part.c pscan.c outp.c
OBJS=	nwords.o end.o part.o pscan.o outp.o
I 10
MAN=	diction.0 style.0
E 12
E 10
E 9

E 3
D 9
BIN = ${DESTDIR}/usr/lib
DICT= -DDICT=\"/usr/lib/dict.d\"
E 9
I 9
D 12
all: dprog style1 style2 style3
E 12
I 12
SUBDIR=	diction explain style style1 style2 style3
E 12
E 9

D 2
all: diction style explain deroff
E 2
I 2
D 3
all: diction style suggest deroff
E 3
I 3
D 9
all: diction style
E 9
I 9
D 12
dprog: diction.c ${LIBC}
D 11
	${CC} ${CFLAGS} -DDICT=\"/usr/lib/dict.d\" diction.c -o $@
E 11
I 11
	${CC} ${CFLAGS} diction.c -o $@
E 11
E 9

E 3
E 2
D 9
style: style1 style2 style3
E 9
I 9
style1: nwords.o ${LIBC}
	${CC} nwords.o -o $@ -ll
E 9

D 3
install: style diction
E 3
I 3
D 9
install: style diction style.sh diction.sh explain.sh dict.d explain.d
E 3
	install -s style1 ${DESTDIR}/usr/lib
	install -s style2 ${DESTDIR}/usr/lib
	install -s style3 ${DESTDIR}/usr/lib
	install -s dprog ${DESTDIR}/usr/lib
D 3
	install -s deroff ${DESTDIR}/usr/lib
	rm -f ${DESTDIR}/usr/bin/deroff
	ln ${DESTDIR}/usr/lib/deroff ${DESTDIR}/usr/bin/deroff
	install -c style ${DESTDIR}/usr/bin
	install -c diction ${DESTDIR}/usr/bin
	install -c explain ${DESTDIR}/usr/bin
E 3
I 3
	install -c style.sh ${DESTDIR}/usr/bin/style
	install -c diction.sh ${DESTDIR}/usr/bin/diction
	install -c explain.sh ${DESTDIR}/usr/bin/explain
E 3
	install -c dict.d ${DESTDIR}/usr/lib
	install -c explain.d ${DESTDIR}/usr/lib
I 2
#	ln ${DESTDIR}/usr/bin/explain ${DESTDIR}/usr/bin/suggest
E 9
I 9
style2: end.o ${LIBC}
	${CC} end.o -o $@ -ll
E 9
D 3
#	ln ${DESTDIR}/usr/lib/explain.d ${DESTDIR}/usr/bin/suggest.d
E 3
E 2

D 9
clean:
	rm -f prtlex.c wdslex.c endlex.c
	rm -f *.o style1 style2 style3 dprog
E 9
I 9
style3: part.o pscan.o outp.o ${LIBC}
	${CC} part.o pscan.o outp.o -o $@ -ll
E 9

I 6
D 9
depend:
E 9
I 9
D 10
clean: FRC
E 10
I 10
clean:
E 10
	rm -f ${OBJS} part.c nwords.c end.c style1 style2 style3 dprog
E 9

I 10
cleandir: clean
	rm -f ${MAN} tags .depend

E 10
E 6
D 9
style3: prtlex.o pscan.o outp.o
	cc prtlex.o pscan.o outp.o -ll  -o style3
prtlex.c: part.l
	lex part.l
	mv lex.yy.c prtlex.c
D 4
prtlex.o: names.h prtlex.c
E 4
I 4
prtlex.o: names.h prtlex.c conp.h style.h names.h
E 4
	cc -c -O prtlex.c
D 3
pscan.o: names.h conp.h
E 3
I 3
pscan.o: names.h conp.h pscan.c
E 3
	cc -c -O pscan.c
D 3
outp.o: names.h conp.h style.h 
E 3
I 3
outp.o: names.h conp.h style.h outp.c
E 3
	cc -c -O outp.c
E 9
I 9
D 11
depend: ${SRCS} FRC
E 11
I 11
depend: ${SRCS}
E 11
	mkdep ${CFLAGS} ${SRCS}
E 9

D 9
style1: wdslex.o
	cc wdslex.o -ll  -o style1
D 2
wdslex.o: wdslex.c nhash.c dict.c ydict.c names.h
E 2
I 2
wdslex.o: wdslex.c nhash.c dict.c ydict.c names.h abbrev.c
E 2
	cc -c wdslex.c
wdslex.c: nwords.l
	lex nwords.l
	mv lex.yy.c wdslex.c
E 9
I 9
D 10
install: FRC
E 10
I 10
install: ${MAN}
E 10
D 11
	install -s -o bin -g bin -m 755 style1 ${DESTDIR}/usr/lib
	install -s -o bin -g bin -m 755 style2 ${DESTDIR}/usr/lib
	install -s -o bin -g bin -m 755 style3 ${DESTDIR}/usr/lib
	install -s -o bin -g bin -m 755 dprog ${DESTDIR}/usr/lib
E 11
I 11
	install -s -o bin -g bin -m 755 dprog style1 style2 style3 \
	    ${DESTDIR}/usr/libexec
	install -c -o bin -g bin -m 755 dict.d explain.d \
	    ${DESTDIR}/usr/share/dict
E 11
	install -c -o bin -g bin -m 755 style.sh ${DESTDIR}/usr/bin/style
	install -c -o bin -g bin -m 755 diction.sh ${DESTDIR}/usr/bin/diction
	install -c -o bin -g bin -m 755 explain.sh ${DESTDIR}/usr/bin/explain
D 11
	install -c -o bin -g bin -m 755 dict.d ${DESTDIR}/usr/lib
	install -c -o bin -g bin -m 755 explain.d ${DESTDIR}/usr/lib
E 11
I 10
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/explain.0
	ln ${DESTDIR}/usr/man/cat1/diction.0 ${DESTDIR}/usr/man/cat1/explain.0
E 10
D 11
#	ln ${DESTDIR}/usr/bin/explain ${DESTDIR}/usr/bin/suggest
E 11
E 9

D 9
style2: endlex.o
	cc endlex.o -ll  -o style2
endlex.o: names.h endlex.c ehash.c edict.c
	cc -c endlex.c
endlex.c: end.l
	lex end.l
	mv lex.yy.c endlex.c
E 9
I 9
D 10
lint: ${SRCS} FRC
E 10
I 10
lint: ${SRCS}
E 10
	lint ${CFLAGS} nwords.c
	lint ${CFLAGS} end.c
	lint ${CFLAGS} part.c pscan.c outp.c
E 9

D 9
diction: dprog
dprog: diction.c
D 5
	cc -O $(DICT) diction.c -i -o dprog
E 5
I 5
	cc -O $(DICT) diction.c -o dprog
E 9
I 9
D 10
tags: ${SRCS} FRC
E 10
I 10
tags: ${SRCS}
E 10
	ctags nwords.c
	ctags -a end.c
	ctags -a part.c pscan.c outp.c
	sort -o tags tags
E 12
I 12
.include <bsd.subdir.mk>
E 12
E 9
E 5
D 10

D 2
deroff:	deroff.c
	cc -O deroff.c -i -o deroff
E 2
I 2
D 3
deroff:	deroff.c getopt.c
	cc -O deroff.c  getopt.c -i -o deroff
E 3
I 3
D 9
srcs:	sources
E 9
I 9
FRC:
E 9

D 9
sources: $(SRCS)
E 9
I 9
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 9

D 9
$(SRCS):
	sccs get $@
E 9
I 9
diction.o: diction.c /usr/include/stdio.h /usr/include/ctype.h
nwords.o: nwords.c /usr/include/stdio.h /usr/include/stdio.h
nwords.o: /usr/include/ctype.h names.h nhash.c dict.c ydict.c abbrev.c
end.o: end.c /usr/include/stdio.h /usr/include/stdio.h /usr/include/ctype.h
end.o: names.h ehash.c edict.c
part.o: part.c /usr/include/stdio.h style.h names.h conp.h
pscan.o: pscan.c names.h conp.h
outp.o: outp.c /usr/include/stdio.h /usr/include/ctype.h style.h names.h conp.h
E 9

I 9
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 10
E 9
E 3
E 2
E 1
