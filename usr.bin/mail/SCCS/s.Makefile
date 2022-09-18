h35244
s 00001/00001/00018
d D 8.3 95/04/20 09:59:04 dab 50 49
c Add support for "inc" command and "autoinc" variable.
c Recognize timestamps in From lines created by SysV/Solaris
c Recognize MAILRC env variable for .mailrc location
c Change tty handling from sgtty to termios
c Turn off EXTPROC when editing headers so that it works
c correctly with Linemode telnet.
e
s 00002/00002/00017
d D 8.2 94/01/25 09:01:17 bostic 49 48
c mail.rc should be root.wheel, to avoid NFS problems
e
s 00000/00000/00019
d D 8.1 93/06/06 15:09:02 bostic 48 47
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00002/00014
d D 5.16 91/06/19 15:07:57 bostic 47 46
c rename Mail.{rc,tildehelp,help} -> mail.{rc,tildehelp,help}
c move mail.rc from /usr/share/misc to /etc
e
s 00009/00050/00007
d D 5.15 90/05/11 15:22:24 bostic 46 45
c first pass for new make
e
s 00004/00014/00053
d D 5.14 90/04/03 10:40:05 bostic 45 44
c move fmt to its own directory
e
s 00008/00008/00059
d D 5.13 89/05/11 09:43:55 bostic 44 43
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00066
d D 5.12 89/04/01 13:09:29 edward 43 42
c added -DUSE_OLD_TTY
e
s 00019/00184/00048
d D 5.11 88/09/16 14:27:40 bostic 42 41
c move man pages here, move depend to .depend
e
s 00006/00011/00226
d D 5.10 88/07/07 04:16:36 edward 41 40
c compile with -R
e
s 00001/00001/00236
d D 5.9 88/06/29 21:07:18 bostic 40 39
c missed an xhead.c
e
s 00072/00110/00165
d D 5.8 88/06/29 20:54:19 bostic 39 38
c remove massaging to share strings, only saves 5K;
c install approved copyright notice
e
s 00010/00005/00265
d D 5.7 88/06/29 18:23:35 bostic 38 37
c install approved copyright notice
e
s 00083/00074/00187
d D 5.6 88/06/16 17:41:45 edward 37 36
c prehistoric (e.g., pre-sendmail) code removed
e
s 00173/00271/00088
d D 5.5 88/02/18 16:59:41 bostic 36 35
c add Berkeley header, remove strings on clean, use install, not copy
c for misc installation
e
s 00328/00071/00031
d D 5.4 87/07/27 17:00:48 bostic 35 33
c new template
e
s 00004/00008/00094
d R 5.4 87/05/18 12:28:24 edward 34 33
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00012/00004/00090
d D 5.3 86/01/11 20:26:41 lepreau 33 32
c fix up make of fmt
e
s 00001/00001/00093
d D 5.2 85/09/17 10:40:28 mckusick 32 31
c also install Mail.rc
e
s 00006/00001/00088
d D 5.1 85/06/06 14:17:12 dist 31 30
c Add copyright
e
s 00001/00001/00088
d D 2.18 85/06/06 12:26:29 edward 30 29
c don't load with -n
e
s 00001/00013/00088
d D 2.17 84/07/26 11:00:56 ralph 29 28
c cleanup odd unused entries.
e
s 00002/00002/00099
d D 2.16 84/07/19 15:42:56 ralph 28 27
c use flock for mailbox locking
e
s 00019/00021/00082
d D 2.15 83/08/18 17:22:00 sam 27 26
c make fmt as well, don't wait for install
e
s 00003/00002/00100
d D 2.14 83/06/19 17:44:42 sam 26 25
c need fmt also
e
s 00001/00001/00101
d D 2.13 83/06/12 11:16:47 sam 25 24
c new signals
e
s 00001/00001/00101
d D 2.12 83/01/31 13:45:57 leres 24 23
c Made install depend of Mail
e
s 00000/00003/00102
d D 2.11 82/09/02 12:39:04 mckusick 23 22
c no longer compile config.c read only since we futz the
c netmach table for hosts that have the gethostname() system call
e
s 00003/00003/00102
d D 2.10 82/08/12 08:43:25 kurt 22 21
c fixes per Bruce Jerrick:  s/makefile/Makefile/;
c changed DESTDIR to /;
c Fixed install to find Mail.help* in misc/
e
s 00002/00007/00103
d D 2.9 82/07/28 15:30:49 kurt 21 20
c Removed errlst.? stuff since its gilding the lilies 
c 
e
s 00006/00002/00104
d D 2.8 82/03/25 09:30:36 kurt 20 19
c added version.c file to keep track of version number 
c and to hang general sccs comments onto. 
c 
e
s 00003/00002/00103
d D 2.7 81/12/07 15:48:25 kurt 19 18
c removed silly dependence on tags; 
c changed to silence echo of final load command, which is long 
c 
e
s 00002/00002/00103
d D 2.6 81/09/10 19:35:22 kurt 18 17
c fixed entry for tags to "get" needed stuff
e
s 00006/00005/00099
d D 2.5 81/09/10 08:41:04 kurt 17 16
c put source file popen.c back in, sigh.  Needs to execute /bin/csh to work on
c more for some reason
e
s 00000/00000/00104
d D 2.4 81/09/09 14:07:45 kurt 16 10
i 15 14 13 12
c added in nifty changes from branch to make easier to compile
e
s 00001/00008/00103
d D 2.3.2.4 81/09/09 12:47:33 kurt 15 14
c Removed silly npopen.c stuff, removed silly version.c stuff
c now we do the version thing with sccs
e
s 00001/00001/00110
d D 2.3.2.3 81/09/09 12:34:05 kurt 14 13
c removed npopen.o from list of object files
e
s 00001/00001/00110
d D 2.3.2.2 81/09/09 12:16:11 kurt 13 12
c fixed invocation of sccs to work if sccs is really a hook
e
s 00000/00000/00111
d D 2.3.2.1 81/09/09 12:14:31 kurt 12 10
c branch-place-holder
e
s 00000/00000/00111
d D 2.3.1.1 81/09/09 12:08:28 kurt 11 10
c branch-place-holder
e
s 00016/00006/00095
d D 2.3 81/09/09 12:03:24 kurt 10 9
c added source files config.c configdefs.h;
c added stuff to make dirtclod style index in listings of mail
e
s 00001/00001/00100
d D 2.2 81/07/20 17:09:54 kurt 9 8
c oops, processing of errlst.c forgot -c flag to cc
e
s 00000/00000/00101
d D 2.1 81/07/01 11:11:38 kurt 8 7
c Release to Heidi Stettner
e
s 00002/00001/00099
d D 1.7 81/05/18 15:53:28 kurt 7 6
c changed location of cgraf
e
s 00008/00010/00092
d D 1.6 81/04/01 13:02:10 kurt 6 5
c changed to use cc -R to do read only stuff and to remove some temporary
c files while compiling
e
s 00005/00005/00097
d D 1.5 81/01/05 18:13:45 kas 5 4
c now uses cc -R for read only stuff; has entry for call graph
e
s 00001/00000/00101
d D 1.4 80/10/17 00:43:01 kas 4 3
c now we remove Mail before linking into it; thus if we are
c executing the old version we won't screw up the make
e
s 00001/00002/00100
d D 1.3 80/10/10 12:02:24 kas 3 2
c removed str.c from the list of sccs gettable files
e
s 00001/00001/00101
d D 1.2 80/10/08 09:59:18 kas 2 1
c oops, forgot to "get" local.h
e
s 00102/00000/00000
d D 1.1 80/10/08 09:56:30 kas 1 0
c date and time created 80/10/08 09:56:30 by kas
e
u
U
f b 
t
T
I 27
D 31
#	%M%	%I%	%E%
E 31
I 31
D 46
#
D 35
# Copyright (c) 1980 Regents of the University of California.
E 35
I 35
# Copyright (c) 1987 Regents of the University of California.
E 35
D 36
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 36
I 36
# All rights reserved.
E 36
#
I 36
# Redistribution and use in source and binary forms are permitted
D 38
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 38
I 38
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
E 38
#
E 46
E 36
#	%W% (Berkeley) %G%
E 31
E 27
I 1
D 46
#
D 27
# Unix version 7.
E 27
I 27
D 36
# Berkeley Mail
E 27
#
E 36
D 27
# Sccs Id = "%W% %G%";
#

CFLAGS=-O -DVMUNIX -DV7
XSTR=/usr/ucb/xstr
D 22
DESTDIR=/usr/src
E 22
I 22
DESTDIR=/
E 22
CTAGS=/usr/ucb/ctags -w
D 10
VPRINT=/usr/ucb/vprint
E 10
I 10
VPRINT=/usr/ucb/print
E 10
I 7
CGRAF=/ja/rigel/rigel/bin/cgraf
I 10
CGRAPH=/ja/rigel/rigel/bin/cgraph
E 27
I 27
D 35
CFLAGS=	-O -DVMUNIX -DV7
XSTR=	/usr/ucb/xstr
DESTDIR=
CTAGS=	/usr/ucb/ctags -w
VPRINT=	/usr/ucb/print
D 29
CGRAF=	/ja/rigel/rigel/bin/cgraf
CGRAPH=	/ja/rigel/rigel/bin/cgraph
E 27
NMKINDEX=/ja/rigel/rigel/bin/nmkindex
DIRTCLOD=/ja/rigel/rigel/bin/dirtclod
E 29
E 10
E 7
D 25
LIBES=-ljobs
E 25
I 25
LIBES=
E 25
D 27
ED=-ed
AS=-as
RM=-rm
D 10
OBJS=aux.o cmd1.o cmd2.o cmd3.o cmdtab.o collect.o edit.o fio.o \
E 10
I 10
D 20
OBJS=aux.o cmd1.o cmd2.o cmd3.o cmdtab.o collect.o config.o edit.o fio.o \
E 20
I 20
OBJS=version.o aux.o cmd1.o cmd2.o cmd3.o cmdtab.o collect.o \
E 27
I 27
D 29
ED=	-ed
E 29
AS=	-as
RM=	-rm
OBJS=	version.o aux.o cmd1.o cmd2.o cmd3.o cmdtab.o collect.o \
E 27
	config.o edit.o fio.o \
E 20
E 10
D 17
	getname.o head.o v7.local.o lock.o optim.o names.o lex.o list.o main.o \
	quit.o send.o strings.o temp.o tty.o vars.o version.o \
D 6
	errlst.o str.o
E 6
I 6
D 14
	errlst.o str.o npopen.o
E 14
I 14
	errlst.o str.o
E 17
I 17
D 28
	getname.o head.o v7.local.o lock.o lex.o list.o main.o \
E 28
I 28
	getname.o head.o v7.local.o lex.o list.o main.o \
E 28
	names.o optim.o popen.o quit.o send.o strings.o temp.o tty.o \
D 20
	vars.o version.o errlst.o str.o
E 20
I 20
D 21
	vars.o errlst.o str.o
E 21
I 21
	vars.o str.o
E 35
I 35
D 41
CFLAGS=	-O
E 41
I 41
D 43
CFLAGS=	-O -R
E 43
I 43
CFLAGS=	-O -R -DUSE_OLD_TTY
E 43
E 41
LIBC=	/lib/libc.a
E 46
I 46

PROG=	mail
D 50
CFLAGS+=-R -DUSE_OLD_TTY
E 50
I 50
CFLAGS+=-R
E 50
E 46
E 35
E 21
E 20
E 17
E 14
E 6
D 27

D 10
SRCS=aux.c cmd1.c cmd2.c cmd3.c cmdtab.c collect.c edit.c fio.c \
E 10
I 10
SRCS=aux.c cmd1.c cmd2.c cmd3.c cmdtab.c collect.c config.c edit.c fio.c \
E 27
I 27
D 37
SRCS=	aux.c cmd1.c cmd2.c cmd3.c cmdtab.c collect.c config.c edit.c fio.c \
E 27
E 10
D 17
	getname.c head.c v7.local.c lock.c optim.c names.c lex.c list.c main.c \
D 3
	quit.c send.c strings.c temp.c tty.c vars.c \
	errlst.c str.c
E 3
I 3
D 15
	quit.c send.c strings.c temp.c tty.c vars.c errlst.c
E 15
I 15
	quit.c send.c strings.c temp.c tty.c vars.c errlst.c version.c
E 17
I 17
D 28
	getname.c head.c v7.local.c lock.c lex.c list.c main.c \
E 28
I 28
D 35
	getname.c head.c v7.local.c lex.c list.c main.c \
E 28
	names.c optim.c popen.c quit.c send.c strings.c temp.c tty.c vars.c \
D 21
	errlst.c version.c
E 21
I 21
	version.c
E 21
E 17
E 15
E 3
D 27

D 2
HDRS=rcv.h def.h glob.h v7.local.h
E 2
I 2
D 10
HDRS=rcv.h def.h glob.h v7.local.h local.h
E 10
I 10
HDRS=rcv.h configdefs.h def.h glob.h v7.local.h local.h
E 10
E 2

E 27
I 27
HDRS=	rcv.h configdefs.h def.h glob.h v7.local.h local.h
ALL=	Mail fmt
E 27
S = $(SRCS) $(HDRS)
E 35
I 35
	getname.c head.c v7.local.c lex.c list.c main.c names.c optim.c \
	popen.c quit.c send.c strings.c temp.c tty.c vars.c version.c
OBJS=	version.o aux.o cmd1.o cmd2.o cmd3.o cmdtab.o collect.o config.o \
	edit.o fio.o getname.o head.o v7.local.o lex.o list.o main.o \
	names.o optim.o popen.o quit.o send.o strings.o temp.o tty.o \
	vars.o str.o flsbuf.o
E 37
I 37
SRCS=	version.c aux.c cmd1.c cmd2.c cmd3.c cmdtab.c collect.c edit.c fio.c \
	getname.c head.c v7.local.c lex.c list.c main.c names.c popen.c \
	quit.c send.c strings.c temp.c tty.c vars.c
D 46
OBJS=	version.o aux.o cmd1.o cmd2.o cmd3.o cmdtab.o collect.o edit.o fio.o \
	getname.o head.o v7.local.o lex.o list.o main.o names.o popen.o \
D 39
	quit.o send.o strings.o temp.o tty.o vars.o str.o flsbuf.o
E 39
I 39
	quit.o send.o strings.o temp.o tty.o vars.o flsbuf.o
E 46
D 45
FSRCS=	fmt.c head.c
FOBJS=	fmt.o head.o
E 45
I 44
D 47
FILES=	Mail.help Mail.rc Mail.tildehelp
E 47
I 47
SFILES=	mail.help mail.tildehelp
EFILES=	mail.rc
E 47
E 44
I 42
D 45
MAN=	mail.0 fmt.0
E 45
I 45
D 46
MAN=	mail.0
E 46
I 46
LINKS=	${BINDIR}/mail ${BINDIR}/Mail
MLINKS=	mail.1 Mail.1
E 46
E 45
E 42
E 39
E 37
E 35

D 39
#
# Special massaging of C files for sharing of strings
#
.c.o:
D 35
	${CC} -E ${CFLAGS} $*.c | ${XSTR} -c -
	${CC} -c ${CFLAGS} x.c 
	mv x.o $*.o
I 6
	@$(RM) -f x.c
E 35
I 35
	${CC} -E ${CFLAGS} $*.c | xstr -c -
D 36
	${CC} -c -o $*.o ${CFLAGS} x.c 
E 36
I 36
	${CC} -c -o $*.o ${CFLAGS} x.c
E 36
	@rm -f x.c
E 35
E 6

E 39
I 27
D 35
all:	${ALL}
E 35
I 35
D 42
all: Mail fmt
E 42
I 42
D 45
all: mail fmt
E 45
I 45
D 46
all: mail
E 46
I 46
beforeinstall:
	cd ${.CURDIR}/misc; install -c -o ${BINOWN} -g ${BINGRP} \
D 47
	    -m 444 ${FILES} ${DESTDIR}/usr/share/misc
E 47
I 47
	    -m 444 ${SFILES} ${DESTDIR}/usr/share/misc
D 49
	cd ${.CURDIR}/misc; install -c -o ${BINOWN} -g ${BINGRP} \
	    -m 444 ${EFILES} ${DESTDIR}/etc
E 49
I 49
	cd ${.CURDIR}/misc; install -c -o root -g wheel \
	    -m 644 ${EFILES} ${DESTDIR}/etc
E 49
E 47
E 46
E 45
E 42
E 35

E 27
D 19
Mail:	$S $(OBJS) tags
E 19
I 19
D 35
Mail:	$S $(OBJS)
E 19
I 4
	$(RM) -f Mail
E 4
D 19
	$(CC) -n -o Mail $(OBJS) $(LIBES)
E 19
I 19
	@echo Loading ...
D 30
	@$(CC) -n -o Mail $(OBJS) $(LIBES)
E 30
I 30
	@$(CC) -o Mail $(OBJS) $(LIBES)
E 30
E 19
	@size Mail
E 35
I 35
D 39
Mail:	${OBJS} ${LIBC}
	${CC} -o Mail ${OBJS} ${LIBES}
E 39
I 39
D 42
Mail: ${OBJS} ${LIBC}
E 42
I 42
D 46
mail: ${OBJS} ${LIBC}
E 42
	${CC} -o $@ ${OBJS}
E 39
E 35

I 5
D 29
mail.g:	$(SRCS)
D 7
	/va/rigel/bin/cgraf $(SRCS) > mail.g
E 7
I 7
	$(CGRAF) $(SRCS) > mail.g
E 7

E 29
E 5
D 24
install:
E 24
I 24
D 26
install:	Mail
E 24
	install -s Mail ${DESTDIR}/usr/ucb
E 26
I 26
D 27
install:	Mail fmt
E 27
I 27
D 35
install: all
E 27
	install -s Mail ${DESTDIR}/usr/ucb/Mail
E 26
D 22
	cp Mail.help* ${DESTDIR}/usr/lib
E 22
I 22
D 32
	cp misc/Mail.help* ${DESTDIR}/usr/lib
E 32
I 32
	cp misc/Mail.* ${DESTDIR}/usr/lib
E 32
I 26
	install -s fmt ${DESTDIR}/usr/ucb/fmt
E 26
E 22
	cd ${DESTDIR}/usr/ucb; rm -f mail; ln Mail mail
E 35
I 35
D 39
fmt: fmt.o xhead.o ${LIBC}
	${CC} ${CFLAGS} fmt.o xhead.o -o $@
E 39
I 39
D 45
fmt: ${FOBJS} ${LIBC}
	${CC} -o $@ ${FOBJS}
E 39
E 35
I 20

E 45
D 35
version.o:	version.c
	$(CC) -c -R version.c
E 35
I 35
D 39
version.o: version.c
	${CC} -c -R version.c
E 35
E 20

D 35
$S:
D 13
	sccs get $@
E 13
I 13
	sccs get $@;
E 35
I 35
xhead.c:
	ln -s head.c xhead.c
E 35
E 13

I 6
D 35
srcs:	$S
E 35
I 35
xhead.o:
	${CC} -c ${CFLAGS} xhead.c
E 35

E 6
D 18
tags:
	${CTAGS} *.c;
E 18
I 18
D 35
tags:	$(SRCS)
	${CTAGS} $(SRCS);
E 35
I 35
fmt.o:
	${CC} -c ${CFLAGS} fmt.c
E 35
E 18

D 35
clean:
	$(RM) -f *.o
D 33
	rm -f Mail a.out fmt x.c xs.c tags core
E 33
I 33
	rm -f Mail a.out fmt x.c xs.c tags core xhead.c
E 33
	cp /dev/null strings
E 35
I 35
str.o: strings
	xstr
	${CC} -R -c -o str.o xs.c
	rm -f xs.c
E 35
D 15
	cp /dev/null version.c
E 15

D 35
lint:
	lint $(CFLAGS) $(SRCS)
E 35
I 35
cmdtab.o: cmdtab.c
	${CC} -R -c ${CFLAGS} cmdtab.c
E 35

E 39
D 33
fmt:	fmt.c head.c
	$(CC) fmt.c head.c -o fmt
	$(RM) fmt.o head.o
E 33
I 33
D 35
fmt:	fmt.o xhead.o
	$(CC) $(CFLAGS) fmt.o xhead.o -o fmt
E 33
	size fmt
E 35
I 35
D 42
clean: FRC
D 36
	rm -f *.o Mail a.out fmt x.c xs.c tags core xhead.c
	cp /dev/null strings
E 36
I 36
D 39
	rm -f *.o Mail a.out fmt x.c xs.c tags core xhead.c strings
E 39
I 39
	rm -f ${FOBJS} ${OBJS} Mail a.out fmt tags core
E 42
I 42
clean:
D 45
	rm -f ${FOBJS} ${OBJS} mail a.out fmt core
E 45
I 45
	rm -f ${OBJS} mail a.out core
E 45
E 42
E 39
E 36
E 35
I 33

D 35
fmt.o:	fmt.c
	$(CC) $(CFLAGS) -c fmt.c
E 35
I 35
D 42
depend: FRC
E 42
I 42
cleandir: clean
	rm -f ${MAN} tags .depend

depend:
E 42
D 39
	mkdep ${SRCS}
E 39
I 39
D 45
	mkdep fmt.c ${SRCS}
E 45
I 45
	mkdep ${SRCS}
E 45
E 39
E 35

D 35
xhead.c:
	ln -s head.c xhead.c
E 35
I 35
D 42
install: FRC
	install -s -o bin -g bin -m 755 Mail ${DESTDIR}/usr/ucb/Mail
E 42
I 42
install: ${MAN}
D 44
	install -s -o bin -g bin -m 755 mail ${DESTDIR}/usr/ucb/mail
E 42
D 36
	cp misc/Mail.* ${DESTDIR}/usr/lib
E 36
	install -s -o bin -g bin -m 755 fmt ${DESTDIR}/usr/ucb/fmt
I 36
	install -c -o bin -g bin -m 444 misc/Mail.* ${DESTDIR}/usr/lib
E 36
D 42
	rm -f ${DESTDIR}/usr/ucb/mail
	ln ${DESTDIR}/usr/ucb/Mail ${DESTDIR}/usr/ucb/mail
E 42
I 42
	rm -f ${DESTDIR}/usr/ucb/Mail
	ln ${DESTDIR}/usr/ucb/mail ${DESTDIR}/usr/ucb/Mail
	install -c -o bin -g bin -m 444 mail.0 ${DESTDIR}/usr/man/cat1/mail.0
	install -c -o bin -g bin -m 444 fmt.0 ${DESTDIR}/usr/man/cat1/fmt.0
E 44
I 44
	install -s -o bin -g bin -m 755 mail ${DESTDIR}/usr/bin
D 45
	install -s -o bin -g bin -m 755 fmt ${DESTDIR}/usr/bin
E 45
	cd misc; install -c -o bin -g bin -m 444 ${FILES} \
	    ${DESTDIR}/usr/share/misc
	rm -f ${DESTDIR}/usr/bin/Mail
	ln ${DESTDIR}/usr/bin/mail ${DESTDIR}/usr/bin/Mail
D 45
	install -c -o bin -g bin -m 444 mail.0 fmt.0 ${DESTDIR}/usr/man/cat1
E 45
E 44
	rm -f ${DESTDIR}/usr/man/cat1/Mail.0
	ln ${DESTDIR}/usr/man/cat1/mail.0 ${DESTDIR}/usr/man/cat1/Mail.0
E 42
E 35

D 35
xhead.o: xhead.c
	$(CC) $(CFLAGS) -c xhead.c
E 35
I 35
D 42
lint: FRC
E 42
I 42
lint:
E 42
	lint ${CFLAGS} ${SRCS}
D 39
	lint ${CFLAGS} xhead.o fmt.o
E 39
I 39
D 45
	lint ${CFLAGS} fmt.c head.c
E 45
E 39
E 35
E 33

D 35
str.o: strings
	$(XSTR)
D 5
	$(CC) -S xs.c
	$(ED) - <:rofix xs.s
	$(AS) -o str.o xs.s
	$(RM) xs.s
	$(RM) xs.c
E 5
I 5
	$(CC) -R -c xs.c
	mv xs.o str.o
I 6
	$(RM) xs.c
E 35
I 35
D 40
tags: xhead.c FRC
E 40
I 40
D 42
tags: FRC
E 42
I 42
tags:
E 42
E 40
	ctags ${SRCS}
E 46
I 46
.include <bsd.prog.mk>
E 46
D 39
	ctags -a xhead.c fmt.c
E 39
I 39
D 45
	ctags -a fmt.c
E 39
	sort -o tags tags
E 45
E 35
E 6
E 5
D 44

E 44
I 35
D 42
FRC:
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

I 39
fmt.o: fmt.c /usr/include/stdio.h /usr/include/ctype.h
version.o: version.c
E 39
D 36
aux.o: aux.c
aux.o:rcv.h
aux.o:def.h
aux.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
aux.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
aux.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
aux.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
aux.o: /usr/include/ctype.h /usr/include/strings.h
aux.o:local.h
aux.o:v7.local.h
aux.o:glob.h
aux.o: /usr/include/setjmp.h /usr/include/sys/stat.h
cmd1.o: cmd1.c
cmd1.o:rcv.h
cmd1.o:def.h
cmd1.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
cmd1.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
cmd1.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
cmd1.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
cmd1.o: /usr/include/ctype.h /usr/include/strings.h
cmd1.o:local.h
cmd1.o:v7.local.h
cmd1.o:glob.h
cmd1.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/wait.h
cmd2.o: cmd2.c
cmd2.o:rcv.h
cmd2.o:def.h
cmd2.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
cmd2.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
cmd2.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
cmd2.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
cmd2.o: /usr/include/ctype.h /usr/include/strings.h
cmd2.o:local.h
cmd2.o:v7.local.h
cmd2.o:glob.h
cmd2.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/wait.h
cmd3.o: cmd3.c
cmd3.o:rcv.h
cmd3.o:def.h
cmd3.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
cmd3.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
cmd3.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
cmd3.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
cmd3.o: /usr/include/ctype.h /usr/include/strings.h
cmd3.o:local.h
cmd3.o:v7.local.h
cmd3.o:glob.h
cmd3.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/wait.h
E 35
I 10
D 23
config.o:	config.c
	$(CC) -R -c config.c

E 23
E 10
cmdtab.o: cmdtab.c
D 6
	$(CC) -S $(CFLAGS) cmdtab.c
	$(ED) - <:rofix cmdtab.s
	$(AS) -o cmdtab.o cmdtab.s
	$(RM) cmdtab.s
E 6
I 6
D 35
	$(CC) -R -c $(CFLAGS) cmdtab.c
E 35
I 35
cmdtab.o:def.h
cmdtab.o: /usr/include/sys/param.h /usr/include/sys/types.h
cmdtab.o: /usr/include/signal.h /usr/include/machine/machparam.h
E 36
I 36
aux.o: aux.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
aux.o: /usr/include/signal.h /usr/include/machine/trap.h
aux.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
aux.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
aux.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
aux.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
aux.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
E 37
I 37
D 39
aux.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
aux.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
aux.o: /usr/include/setjmp.h /usr/include/sys/stat.h
E 39
I 39
aux.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
aux.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
E 39
E 37
cmd1.o: cmd1.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
cmd1.o: /usr/include/signal.h /usr/include/machine/trap.h
cmd1.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
cmd1.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
cmd1.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
cmd1.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
cmd1.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
cmd1.o: /usr/include/sys/wait.h
E 37
I 37
D 39
cmd1.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
cmd1.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
cmd1.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/wait.h
E 39
I 39
cmd1.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
D 41
cmd1.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
cmd1.o: /usr/include/sys/wait.h
E 41
I 41
cmd1.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 41
E 39
E 37
cmd2.o: cmd2.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
cmd2.o: /usr/include/signal.h /usr/include/machine/trap.h
cmd2.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
cmd2.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
cmd2.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
cmd2.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
cmd2.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
cmd2.o: /usr/include/sys/wait.h
E 37
I 37
D 39
cmd2.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
cmd2.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
cmd2.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/wait.h
E 39
I 39
cmd2.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
cmd2.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
cmd2.o: /usr/include/sys/wait.h
E 39
E 37
cmd3.o: cmd3.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
cmd3.o: /usr/include/signal.h /usr/include/machine/trap.h
cmd3.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
cmd3.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
cmd3.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
cmd3.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
cmd3.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
cmd3.o: /usr/include/sys/wait.h
E 37
I 37
D 39
cmd3.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
cmd3.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
cmd3.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/wait.h
E 39
I 39
cmd3.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
D 41
cmd3.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
cmd3.o: /usr/include/sys/wait.h
E 41
I 41
cmd3.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 41
E 39
E 37
cmdtab.o: cmdtab.c def.h /usr/include/sys/param.h /usr/include/sys/types.h
cmdtab.o: /usr/include/signal.h /usr/include/machine/trap.h
cmdtab.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
E 36
cmdtab.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
cmdtab.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
cmdtab.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
D 36
cmdtab.o:local.h
cmdtab.o:v7.local.h
collect.o: collect.c
collect.o:rcv.h
collect.o:def.h
collect.o: /usr/include/sys/param.h /usr/include/sys/types.h
collect.o: /usr/include/signal.h /usr/include/machine/machparam.h
collect.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
collect.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
collect.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
collect.o: /usr/include/strings.h
collect.o:local.h
collect.o:v7.local.h
collect.o:glob.h
collect.o: /usr/include/setjmp.h /usr/include/sys/stat.h
E 36
I 36
cmdtab.o: local.h v7.local.h
E 37
I 37
D 39
cmdtab.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
cmdtab.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
E 39
I 39
cmdtab.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
cmdtab.o: local.h v7.local.h
E 39
E 37
collect.o: collect.c rcv.h def.h /usr/include/sys/param.h
collect.o: /usr/include/sys/types.h /usr/include/signal.h
collect.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
collect.o: /usr/include/machine/endian.h /usr/include/sys/signal.h
collect.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
D 37
collect.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
collect.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
collect.o: glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
E 37
I 37
D 39
collect.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydefaults.h
collect.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
collect.o: /usr/include/strings.h local.h v7.local.h glob.h
collect.o: /usr/include/setjmp.h /usr/include/sys/stat.h
E 39
I 39
collect.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
collect.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
collect.o: glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
E 39
E 37
E 36
D 41
collect.o: /usr/include/sys/wait.h
E 41
D 36
config.o: config.c
config.o:configdefs.h
edit.o: edit.c
edit.o:rcv.h
edit.o:def.h
edit.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
edit.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
edit.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
edit.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
edit.o: /usr/include/ctype.h /usr/include/strings.h
edit.o:local.h
edit.o:v7.local.h
edit.o:glob.h
edit.o: /usr/include/setjmp.h /usr/include/stdio.h /usr/include/sys/stat.h
edit.o: /usr/include/sys/wait.h
fio.o: fio.c
fio.o:rcv.h
fio.o:def.h
fio.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
fio.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
fio.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
fio.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
fio.o: /usr/include/ctype.h /usr/include/strings.h
fio.o:local.h
fio.o:v7.local.h
fio.o:glob.h
fio.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/file.h
fio.o: /usr/include/sys/wait.h /usr/include/errno.h
getname.o: getname.c /usr/include/pwd.h
getname.o:rcv.h
getname.o:def.h
getname.o: /usr/include/sys/param.h /usr/include/sys/types.h
getname.o: /usr/include/signal.h /usr/include/machine/machparam.h
getname.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
getname.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
getname.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
getname.o: /usr/include/strings.h
getname.o:local.h
getname.o:v7.local.h
getname.o:glob.h
getname.o: /usr/include/setjmp.h
head.o: head.c
head.o:rcv.h
head.o:def.h
head.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
head.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
head.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
head.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
head.o: /usr/include/ctype.h /usr/include/strings.h
head.o:local.h
head.o:v7.local.h
head.o:glob.h
head.o: /usr/include/setjmp.h
v7.local.o: v7.local.c
v7.local.o:rcv.h
v7.local.o:def.h
v7.local.o: /usr/include/sys/param.h /usr/include/sys/types.h
v7.local.o: /usr/include/signal.h /usr/include/machine/machparam.h
v7.local.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
v7.local.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
v7.local.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
v7.local.o: /usr/include/strings.h
v7.local.o:local.h
v7.local.o:v7.local.h
v7.local.o:glob.h
v7.local.o: /usr/include/setjmp.h
lex.o: lex.c
lex.o:rcv.h
lex.o:def.h
lex.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
lex.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
lex.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
lex.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
lex.o: /usr/include/ctype.h /usr/include/strings.h
lex.o:local.h
lex.o:v7.local.h
lex.o:glob.h
lex.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/errno.h
list.o: list.c
list.o:rcv.h
list.o:def.h
list.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
list.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
list.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
list.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
list.o: /usr/include/ctype.h /usr/include/strings.h
list.o:local.h
list.o:v7.local.h
list.o:glob.h
list.o: /usr/include/setjmp.h /usr/include/ctype.h
main.o: main.c
main.o:rcv.h
main.o:def.h
main.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
main.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
main.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
main.o: /usr/include/ctype.h /usr/include/strings.h
main.o:local.h
main.o:v7.local.h
main.o:glob.h
main.o: /usr/include/setjmp.h /usr/include/sys/stat.h
names.o: names.c
names.o:rcv.h
names.o:def.h
names.o: /usr/include/sys/param.h /usr/include/sys/types.h
names.o: /usr/include/signal.h /usr/include/machine/machparam.h
E 36
I 36
D 37
config.o: config.c configdefs.h
E 37
edit.o: edit.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
edit.o: /usr/include/signal.h /usr/include/machine/trap.h
edit.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
edit.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
edit.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
edit.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
edit.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/stdio.h
edit.o: /usr/include/sys/stat.h /usr/include/sys/wait.h
E 37
I 37
D 39
edit.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
edit.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
edit.o: /usr/include/setjmp.h /usr/include/stdio.h /usr/include/sys/stat.h
edit.o: /usr/include/sys/wait.h
E 39
I 39
edit.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
D 41
edit.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/stdio.h
edit.o: /usr/include/sys/stat.h /usr/include/sys/wait.h
E 41
I 41
edit.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
E 41
E 39
E 37
fio.o: fio.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
fio.o: /usr/include/signal.h /usr/include/machine/trap.h
fio.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
fio.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
fio.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
fio.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
fio.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
fio.o: /usr/include/sys/file.h /usr/include/sys/wait.h /usr/include/errno.h
E 37
I 37
D 39
fio.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
fio.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
fio.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/file.h
fio.o: /usr/include/sys/wait.h /usr/include/errno.h
E 39
I 39
fio.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
fio.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
fio.o: /usr/include/sys/file.h /usr/include/sys/wait.h /usr/include/errno.h
E 39
E 37
getname.o: getname.c /usr/include/pwd.h rcv.h def.h /usr/include/sys/param.h
getname.o: /usr/include/sys/types.h /usr/include/signal.h
getname.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
getname.o: /usr/include/machine/endian.h /usr/include/sys/signal.h
getname.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
D 37
getname.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
getname.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
getname.o: glob.h /usr/include/setjmp.h
E 37
I 37
D 39
getname.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydefaults.h
getname.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
getname.o: /usr/include/strings.h local.h v7.local.h glob.h
getname.o: /usr/include/setjmp.h
E 39
I 39
getname.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
getname.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
getname.o: glob.h /usr/include/setjmp.h
E 39
E 37
head.o: head.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
head.o: /usr/include/signal.h /usr/include/machine/trap.h
head.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
head.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
head.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
head.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
head.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 37
I 37
D 39
head.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
head.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
head.o: /usr/include/setjmp.h
E 39
I 39
head.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
head.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 39
E 37
v7.local.o: v7.local.c rcv.h def.h /usr/include/sys/param.h
v7.local.o: /usr/include/sys/types.h /usr/include/signal.h
v7.local.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
v7.local.o: /usr/include/machine/endian.h /usr/include/sys/signal.h
v7.local.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
D 37
v7.local.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
v7.local.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
v7.local.o: glob.h /usr/include/setjmp.h
E 37
I 37
D 39
v7.local.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydefaults.h
v7.local.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
v7.local.o: /usr/include/strings.h local.h v7.local.h glob.h
v7.local.o: /usr/include/setjmp.h
E 39
I 39
v7.local.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
v7.local.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
v7.local.o: glob.h /usr/include/setjmp.h
E 39
E 37
lex.o: lex.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
lex.o: /usr/include/signal.h /usr/include/machine/trap.h
lex.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
lex.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
lex.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
lex.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
lex.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
lex.o: /usr/include/errno.h
E 37
I 37
D 39
lex.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
lex.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
lex.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/errno.h
E 39
I 39
lex.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
lex.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
lex.o: /usr/include/errno.h
E 39
E 37
list.o: list.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
list.o: /usr/include/signal.h /usr/include/machine/trap.h
list.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
list.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
list.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
list.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
list.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/ctype.h
E 37
I 37
D 39
list.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
list.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
list.o: /usr/include/setjmp.h /usr/include/ctype.h
E 39
I 39
list.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
list.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/ctype.h
E 39
E 37
main.o: main.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
main.o: /usr/include/signal.h /usr/include/machine/trap.h
main.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
main.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
main.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
main.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
main.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
E 37
I 37
D 39
main.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
main.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
main.o: /usr/include/setjmp.h /usr/include/sys/stat.h
E 39
I 39
main.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
main.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
E 39
E 37
names.o: names.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
names.o: /usr/include/signal.h /usr/include/machine/trap.h
names.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
E 36
names.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
names.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
names.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
D 36
names.o:local.h
names.o:v7.local.h
names.o:glob.h
names.o: /usr/include/setjmp.h /usr/include/sys/wait.h
optim.o: optim.c
optim.o:rcv.h
optim.o:def.h
optim.o: /usr/include/sys/param.h /usr/include/sys/types.h
optim.o: /usr/include/signal.h /usr/include/machine/machparam.h
E 36
I 36
names.o: local.h v7.local.h glob.h /usr/include/setjmp.h
names.o: /usr/include/sys/wait.h
optim.o: optim.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
optim.o: /usr/include/signal.h /usr/include/machine/trap.h
optim.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
E 36
optim.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
optim.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
optim.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
D 36
optim.o:local.h
optim.o:v7.local.h
optim.o:glob.h
optim.o: /usr/include/setjmp.h
optim.o:configdefs.h
E 36
I 36
optim.o: local.h v7.local.h glob.h /usr/include/setjmp.h configdefs.h
E 36
popen.o: popen.c /usr/include/stdio.h /usr/include/sys/signal.h
D 36
popen.o: /usr/include/sys/types.h /usr/include/sys/wait.h
popen.o: /usr/include/machine/machparam.h /usr/include/errno.h
quit.o: quit.c
quit.o:rcv.h
quit.o:def.h
quit.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
quit.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
quit.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
quit.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
quit.o: /usr/include/ctype.h /usr/include/strings.h
quit.o:local.h
quit.o:v7.local.h
quit.o:glob.h
quit.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/file.h
send.o: send.c
send.o:rcv.h
send.o:def.h
send.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
send.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
send.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
send.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
send.o: /usr/include/ctype.h /usr/include/strings.h
send.o:local.h
send.o:v7.local.h
send.o:glob.h
send.o: /usr/include/setjmp.h /usr/include/sys/wait.h /usr/include/sys/stat.h
strings.o: strings.c
strings.o:rcv.h
strings.o:def.h
strings.o: /usr/include/sys/param.h /usr/include/sys/types.h
strings.o: /usr/include/signal.h /usr/include/machine/machparam.h
strings.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
strings.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
strings.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
strings.o: /usr/include/strings.h
strings.o:local.h
strings.o:v7.local.h
strings.o:glob.h
strings.o: /usr/include/setjmp.h
temp.o: temp.c
temp.o:rcv.h
temp.o:def.h
temp.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
temp.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
temp.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
temp.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
temp.o: /usr/include/ctype.h /usr/include/strings.h
temp.o:local.h
temp.o:v7.local.h
temp.o:glob.h
temp.o: /usr/include/setjmp.h
tty.o: tty.c
tty.o:rcv.h
tty.o:def.h
tty.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
tty.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
tty.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
tty.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
tty.o: /usr/include/ctype.h /usr/include/strings.h
tty.o:local.h
tty.o:v7.local.h
tty.o:glob.h
tty.o: /usr/include/setjmp.h
vars.o: vars.c
vars.o:rcv.h
vars.o:def.h
vars.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
vars.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
vars.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
vars.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
vars.o: /usr/include/ctype.h /usr/include/strings.h
vars.o:local.h
vars.o:v7.local.h
vars.o:glob.h
vars.o: /usr/include/setjmp.h
E 36
I 36
popen.o: /usr/include/machine/trap.h /usr/include/sys/types.h
popen.o: /usr/include/sys/wait.h /usr/include/machine/endian.h
popen.o: /usr/include/errno.h
E 37
I 37
D 39
names.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
names.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
names.o: /usr/include/setjmp.h /usr/include/sys/wait.h
E 39
I 39
names.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
names.o: local.h v7.local.h glob.h /usr/include/setjmp.h
names.o: /usr/include/sys/wait.h
E 39
popen.o: popen.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
popen.o: /usr/include/signal.h /usr/include/machine/trap.h
popen.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
popen.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
popen.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 39
popen.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
popen.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
popen.o: /usr/include/setjmp.h /usr/include/stdio.h /usr/include/sys/signal.h
popen.o: /usr/include/sys/types.h /usr/include/sys/wait.h /usr/include/errno.h
E 39
I 39
popen.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
D 41
popen.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/stdio.h
popen.o: /usr/include/sys/signal.h /usr/include/sys/types.h
popen.o: /usr/include/sys/wait.h /usr/include/errno.h
E 41
I 41
popen.o: local.h v7.local.h glob.h /usr/include/setjmp.h
popen.o: /usr/include/sys/signal.h /usr/include/sys/wait.h
E 41
E 39
E 37
quit.o: quit.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
quit.o: /usr/include/signal.h /usr/include/machine/trap.h
quit.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
quit.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
quit.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
quit.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
quit.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
quit.o: /usr/include/sys/file.h
E 37
I 37
D 39
quit.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
quit.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
quit.o: /usr/include/setjmp.h /usr/include/sys/stat.h /usr/include/sys/file.h
E 39
I 39
quit.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
quit.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/stat.h
quit.o: /usr/include/sys/file.h
E 39
E 37
send.o: send.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
send.o: /usr/include/signal.h /usr/include/machine/trap.h
send.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
send.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
send.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
send.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
send.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/wait.h
send.o: /usr/include/sys/stat.h
E 37
I 37
D 39
send.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
send.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
send.o: /usr/include/setjmp.h /usr/include/sys/wait.h /usr/include/sys/stat.h
E 39
I 39
send.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
send.o: local.h v7.local.h glob.h /usr/include/setjmp.h /usr/include/sys/wait.h
send.o: /usr/include/sys/stat.h
E 39
E 37
strings.o: strings.c rcv.h def.h /usr/include/sys/param.h
strings.o: /usr/include/sys/types.h /usr/include/signal.h
strings.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
strings.o: /usr/include/machine/endian.h /usr/include/sys/signal.h
strings.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
D 37
strings.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
strings.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
strings.o: glob.h /usr/include/setjmp.h
E 37
I 37
D 39
strings.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydefaults.h
strings.o: /usr/include/sys/ttydev.h /usr/include/ctype.h
strings.o: /usr/include/strings.h local.h v7.local.h glob.h
strings.o: /usr/include/setjmp.h
E 39
I 39
strings.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
strings.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h
strings.o: glob.h /usr/include/setjmp.h
E 39
E 37
temp.o: temp.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
temp.o: /usr/include/signal.h /usr/include/machine/trap.h
temp.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
temp.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
temp.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
temp.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
temp.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 37
I 37
D 39
temp.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
temp.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
temp.o: /usr/include/setjmp.h
E 39
I 39
temp.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
temp.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 39
E 37
tty.o: tty.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
tty.o: /usr/include/signal.h /usr/include/machine/trap.h
tty.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
tty.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
tty.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
tty.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
tty.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 37
I 37
D 39
tty.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
tty.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
tty.o: /usr/include/setjmp.h
E 39
I 39
tty.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
tty.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 39
E 37
vars.o: vars.c rcv.h def.h /usr/include/sys/param.h /usr/include/sys/types.h
vars.o: /usr/include/signal.h /usr/include/machine/trap.h
vars.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
vars.o: /usr/include/sys/signal.h /usr/include/stdio.h /usr/include/sgtty.h
vars.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
D 37
vars.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
vars.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 37
I 37
D 39
vars.o: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
vars.o: /usr/include/ctype.h /usr/include/strings.h local.h v7.local.h glob.h
vars.o: /usr/include/setjmp.h
E 37
E 36
version.o: version.c
E 39
I 39
vars.o: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/strings.h
vars.o: local.h v7.local.h glob.h /usr/include/setjmp.h
E 39
E 35
E 6
D 21

errlst.o: errlst.c
	${CC} -E ${CFLAGS} errlst.c | ${XSTR} -c -
D 6
	${CC} ${CFLAGS} -S x.c
	${ED} - <:rofix x.s
	${AS} -o errlst.o x.s
	${RM} x.s
	${RM} x.c
E 6
I 6
D 9
	${CC} ${CFLAGS} -R x.c
E 9
I 9
	${CC} ${CFLAGS} -R -c x.c
E 9
	mv x.o errlst.o
E 21
E 6
D 15

#
# Make the version file.  /tmp is always changing.
#
version.c: #	/tmp
	/bin/sh version > version.c
E 15

D 10
print:
	@$(VPRINT) makefile rcv.h def.h glob.h local.h v7.local.h $(SRCS) fmt.c;
E 10
I 10
D 35
print:	$S fmt.c
D 29
	$(CGRAPH) > mail.g;
	$(NMKINDEX) > mail.i;
	$(DIRTCLOD) -x mail.i -p mail.g > mail.x
D 22
	@$(VPRINT) makefile mail.x rcv.h def.h glob.h local.h v7.local.h \
E 22
I 22
	@$(VPRINT) Makefile mail.x rcv.h def.h glob.h local.h v7.local.h \
E 22
	    $(SRCS) fmt.c;
E 29
I 29
	@$(VPRINT) Makefile rcv.h def.h glob.h local.h v7.local.h $(SRCS) fmt.c
E 29
E 10

wc:
	@wc rcv.h def.h glob.h local.h v7.local.h $(SRCS)

sc:
	@grep -c \; rcv.h def.h glob.h local.h v7.local.h $(SRCS)
E 35
I 35
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 42
E 35
E 1
