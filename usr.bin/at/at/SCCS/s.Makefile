h11080
s 00000/00000/00008
d D 8.1 93/06/06 14:21:02 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00006
d D 5.11 90/05/29 21:41:54 bostic 13 12
c needs to be setuid root
e
s 00003/00070/00003
d D 5.10 90/05/11 14:27:42 bostic 12 11
c first pass for new make
e
s 00002/00002/00071
d D 5.9 89/08/15 10:22:44 bostic 11 10
c reorg
e
s 00001/00001/00072
d D 5.8 89/05/11 14:06:16 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00027/00044/00046
d D 5.7 88/10/22 16:31:12 bostic 9 8
c cleanup, add manual page
e
s 00070/00070/00020
d D 5.6 87/06/18 14:55:18 bostic 8 6
c new template
e
s 00063/00063/00027
d R 5.6 87/06/18 14:48:26 bostic 7 6
c new template
e
s 00006/00005/00084
d D 5.5 87/01/18 19:05:38 karels 6 5
c it has to be root
e
s 00013/00008/00076
d D 5.4 85/10/09 10:46:54 bloom 5 4
c use DESTDIR for entire installation
e
s 00002/00002/00082
d D 5.3 85/07/29 10:00:58 mckusick 4 3
c allow at to run with user's permissions (from pur-ee!ks)
e
s 00001/00000/00083
d D 5.2 85/06/21 17:33:45 mckusick 3 2
c fix install script
e
s 00006/00001/00077
d D 5.1 85/06/06 09:50:43 dist 2 1
c Add copyright
e
s 00078/00000/00000
d D 4.1 84/08/02 10:13:15 mckusick 1 0
c date and time created 84/08/02 10:13:15 by mckusick
e
u
U
t
T
I 1
D 2
#	%W%	(Berkeley)	%E%
E 2
I 2
D 12
#
D 8
# Copyright (c) 1983 Regents of the University of California.
E 8
I 8
D 9
# Copyright (c) 1987 Regents of the University of California.
E 8
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 9
I 9
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 9
#
D 8
#	%W% (Berkeley) %G%
E 8
I 8
D 9
#	%W%	(Berkeley)	%G%
E 9
I 9
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
E 9
E 8
E 2
#
E 12
I 9
#	%W% (Berkeley) %G%
D 12
#
E 9
D 8
#       Makefile for at, atq, atrm, and atrun
#
ALL=		atq atrm at atrun
SRCS=		atq.c atrm.c at.c atrun.c
CFLAGS=		-O
INCPATH=
DESTDIR=
E 8
I 8
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	atq.c atrm.c at.c atrun.c
OBJS=	atq.o atrm.o at.o atrun.o
E 8
D 10
ATRUNDIR=	/usr/lib
E 10
I 10
ATRUNDIR=	/usr/libexec
E 10
D 11
SPOOLDIRS=	/usr/spool/at /usr/spool/at/past
SPOOLFILES=	/usr/spool/at/lasttimedone
E 11
I 11
SPOOLDIRS=	/var/spool/at /var/spool/at/past
SPOOLFILES=	/var/spool/at/lasttimedone
E 11
I 9
MAN=	at.0 atq.0 atrm.0
E 12
E 9
I 6
D 8
OWNER=		root
E 8
E 6

D 8
all: ${ALL}
E 8
I 8
D 12
all: atq atrm at atrun
E 12
I 12
PROG=	at
I 13
BINOWN=	root
BINMODE=4555
E 13
E 12
E 8

D 8
at: at.c
	$(CC) $(CFLAGS) -o at at.c
E 8
I 8
D 9
at: at.c ${LIBC}
	${CC} ${CFLAGS} -o $@ at.c
E 9
I 9
D 12
at atq atrm atrun: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 9
E 8

D 8
atq: atq.c
	$(CC) $(CFLAGS) -o atq atq.c
E 8
I 8
D 9
atq: atq.c ${LIBC}
	${CC} ${CFLAGS} -o $@ atq.c
E 8

D 8
atrm: atrm.c
	$(CC) $(CFLAGS) -o atrm atrm.c
E 8
I 8
atrm: atrm.c ${LIBC}
	${CC} ${CFLAGS} -o $@ atrm.c
E 8

D 8
atrun: atrun.c
	$(CC) $(CFLAGS) -o atrun atrun.c
E 8
I 8
atrun: atrun.c ${LIBC}
	${CC} ${CFLAGS} -o $@ atrun.c
E 8

D 8
install: all
D 5
	-mkdir $(SPOOLDIRS)
	chown daemon $(SPOOLDIRS)
	chgrp daemon $(SPOOLDIRS)
	chmod 755    $(SPOOLDIRS)
I 3
D 4
	for i in $(SPOOLFILES); do if [ ! -f $$i ]; then echo 0 > $$i; fi; done
E 4
I 4
	-for i in $(SPOOLFILES); do if [ ! -f $$i ]; then echo 0 > $$i; fi; done
E 4
E 3
	chown daemon $(SPOOLFILES)
	chgrp daemon $(SPOOLFILES)
	install -s atrun $(ATRUNDIR)
E 5
I 5
	-for i in $(SPOOLDIRS); \
		do mkdir $(DESTDIR)/$$i; \
D 6
		chown daemon $(DESTDIR)/$$i; \
E 6
I 6
		chown ${OWNER} $(DESTDIR)/$$i; \
E 6
		chgrp daemon $(DESTDIR)/$$i; \
		chmod 755    $(DESTDIR)/$$i; \
		done
	-for i in $(SPOOLFILES); \
		do if [ ! -f $(DESTDIR)/$$i ]; \
		then echo 0 > $(DESTDIR)/$$i; fi; \
D 6
		chown daemon $(DESTDIR)/$$i; \
E 6
I 6
		chown ${OWNER} $(DESTDIR)/$$i; \
E 6
		chgrp daemon $(DESTDIR)/$$i; \
		done
	install -s atrun $(DESTDIR)/$(ATRUNDIR)
E 5
D 4
	install -s atq $(DESTDIR)/usr/bin
E 4
I 4
D 6
	install -s -o daemon -m 4755 atq $(DESTDIR)/usr/bin
E 4
	install -s -o daemon -m 4755 at $(DESTDIR)/usr/bin
	install -s -o daemon -m 4755 atrm $(DESTDIR)/usr/bin
E 6
I 6
	install -s -o ${OWNER} -m 4755 atq $(DESTDIR)/usr/bin
	install -s -o ${OWNER} -m 4755 at $(DESTDIR)/usr/bin
	install -s -o ${OWNER} -m 4755 atrm $(DESTDIR)/usr/bin
E 8
I 8
clean: FRC
E 9
I 9
clean:
E 9
	rm -f ${OBJS} core atq atrm at atrun
E 8
E 6

D 8
clean:
	rm -f $(ALL) errs *.o
E 8
I 8
D 9
depend: FRC
E 9
I 9
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 9
	mkdep -p ${CFLAGS} ${SRCS}
E 8

D 8
print:
	lpr ${SRCS}
E 8
I 8
D 9
install: FRC
E 9
I 9
install: ${MAN}
E 9
	-for i in ${SPOOLDIRS}; do \
		mkdir ${DESTDIR}/$$i > /dev/null 2>&1; \
		chown root ${DESTDIR}/$$i; \
		chgrp daemon ${DESTDIR}/$$i; \
		chmod 755 ${DESTDIR}/$$i; \
	done
	-for i in ${SPOOLFILES}; do \
		if [ ! -f ${DESTDIR}/$$i ]; then \
			echo 0 > ${DESTDIR}/$$i; \
		fi; \
		chown root ${DESTDIR}/$$i; \
		chgrp daemon ${DESTDIR}/$$i; \
	done
	install -s -o bin -g bin -m 755 atrun ${DESTDIR}/${ATRUNDIR}
	install -s -o root -g bin -m 4755 atq ${DESTDIR}/usr/bin
	install -s -o root -g bin -m 4755 at ${DESTDIR}/usr/bin
	install -s -o root -g bin -m 4755 atrm ${DESTDIR}/usr/bin
I 9
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 9
E 8

D 8
depend:
	cc -M ${INCPATH} ${SRCS} | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' > makedep
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 8
I 8
D 9
lint: FRC
E 9
I 9
lint: ${SRCS}
E 9
	lint ${CFLAGS} atq.c
	lint ${CFLAGS} atrm.c
	lint ${CFLAGS} at.c
	lint ${CFLAGS} atrun.c
E 8

D 8
# DO NOT DELETE THIS LINE -- make depend uses it
E 8
I 8
D 9
tags: FRC
E 9
I 9
tags: ${SRCS}
E 9
	ctags atq.c
	ctags -a atrm.c
	ctags -a at.c
	ctags -a atrun.c
	sort -o tags tags
E 12
I 12
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 12
E 8
D 9

I 8
FRC:
E 8

D 8
atq.o: atq.c /usr/include/stdio.h /usr/include/sys/types.h
atq.o: /usr/include/sys/file.h /usr/include/sys/dir.h /usr/include/sys/stat.h
atq.o: /usr/include/sys/time.h /usr/include/pwd.h /usr/include/ctype.h
atrm.o: atrm.c /usr/include/stdio.h /usr/include/pwd.h /usr/include/ctype.h
atrm.o: /usr/include/sys/types.h /usr/include/sys/dir.h /usr/include/sys/file.h
atrm.o: /usr/include/sys/stat.h
at.o: at.c /usr/include/stdio.h /usr/include/ctype.h /usr/include/signal.h
at.o: /usr/include/sys/time.h /usr/include/sys/file.h
atrun.o: atrun.c /usr/include/stdio.h /usr/include/sys/types.h
atrun.o: /usr/include/sys/dir.h /usr/include/sys/file.h /usr/include/sys/time.h
atrun.o: /usr/include/sys/stat.h /usr/include/pwd.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 8
I 8
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

atq: atq.c /usr/include/stdio.h /usr/include/sys/types.h
atq: /usr/include/sys/file.h /usr/include/sys/dir.h /usr/include/sys/stat.h
atq: /usr/include/sys/time.h /usr/include/time.h /usr/include/pwd.h
atq: /usr/include/ctype.h
atrm: atrm.c /usr/include/stdio.h /usr/include/pwd.h /usr/include/ctype.h
atrm: /usr/include/sys/types.h /usr/include/sys/dir.h /usr/include/sys/file.h
atrm: /usr/include/sys/stat.h
at: at.c /usr/include/stdio.h /usr/include/ctype.h /usr/include/signal.h
at: /usr/include/pwd.h /usr/include/sys/param.h /usr/include/sys/types.h
at: /usr/include/signal.h /usr/include/machine/machparam.h
at: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
atrun: atrun.c /usr/include/stdio.h /usr/include/sys/param.h
atrun: /usr/include/sys/types.h /usr/include/signal.h
atrun: /usr/include/machine/machparam.h /usr/include/sys/dir.h
atrun: /usr/include/sys/file.h /usr/include/sys/time.h /usr/include/time.h
atrun: /usr/include/sys/stat.h /usr/include/pwd.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 9
E 8
E 1
