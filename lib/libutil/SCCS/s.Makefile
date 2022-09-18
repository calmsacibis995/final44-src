h05715
s 00000/00000/00007
d D 8.1 93/06/04 17:31:38 bostic 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00005/00006
d D 5.13 93/05/22 10:21:21 bostic 14 13
c move daemon, getloadavg, pwcache into C library
e
s 00003/00007/00008
d D 5.12 92/04/13 12:33:41 bostic 13 12
c make a kvm library
e
s 00008/00005/00007
d D 5.11 92/04/03 14:53:46 mckusick 12 11
c update from Steve McCanne for Sun compatible kvm
e
s 00002/00001/00010
d D 5.10 91/05/06 18:07:56 karels 11 10
c kvm needs -I/sys
e
s 00001/00001/00010
d D 5.9 91/04/27 16:19:54 bostic 10 9
c doesn't need user.h anymore
e
s 00001/00001/00010
d D 5.8 91/04/27 16:12:15 bostic 9 8
c kvm.c needs -I/sys
e
s 00002/00000/00009
d D 5.7 91/04/01 09:00:03 bostic 8 6
c add man page links for pwcache (user_from_uid, group_from_gid)
e
s 00001/00001/00008
d R 5.7 91/01/15 14:03:38 bostic 7 6
c kernel reorg
e
s 00003/00002/00006
d D 5.6 90/06/27 15:51:57 marc 6 5
c add login_tty.c
e
s 00006/00063/00002
d D 5.5 90/05/11 12:49:27 bostic 5 4
c first pass for new make
e
s 00006/00003/00059
d D 5.4 90/03/19 16:24:17 bostic 4 3
c add kvm, pwcache, man page for pwcache
e
s 00017/00013/00045
d D 5.3 89/05/10 22:41:47 bostic 3 2
c build profiled library, minor cleanups
e
s 00003/00000/00055
d D 5.2 88/09/20 16:51:52 bostic 2 1
c add cleandir
e
s 00055/00000/00000
d D 5.1 88/08/31 23:01:12 bostic 1 0
c date and time created 88/08/31 23:01:12 by bostic
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such redistribution and
# use acknowledge that the software was developed by the University
# of California, Berkeley.  The name of the University may not be
# used to endorse or promote products derived from this software
# without specific prior written permission.  THIS SOFTWARE IS PROVIDED
# ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
# FITNESS FOR A PARTICULAR PURPOSE.
#
# %W% (Berkeley) %G%
#
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 5
DEFS=	-DLIBC_SCCS
CFLAGS=	-O ${DEFS}
D 4
SRCS=	login.c logout.c logwtmp.c
OBJS=	login.o logout.o logwtmp.o
E 4
I 4
SRCS=	login.c logout.c logwtmp.c kvm.c pwcache.c
OBJS=	login.o logout.o logwtmp.o kvm.o pwcache.o
MAN=	pwcache.0
MDIR=	${DESTDIR}/usr/man/cat3
E 5
I 5
LIB=	util
D 9
CFLAGS+=-DLIBC_SCCS
E 9
I 9
D 10
CFLAGS+=-DLIBC_SCCS -I/sys
E 10
I 10
D 11
CFLAGS+=-DLIBC_SCCS
E 11
I 11
D 12
# kvm.c needs -I/sys
E 12
CFLAGS+=-DLIBC_SCCS -I/sys
E 11
E 10
E 9
D 6
SRCS=	getloadavg.c login.c logout.c logwtmp.c kvm.c pwcache.c
MAN3=	pwcache.0
E 6
I 6
D 12
SRCS=	daemon.c getloadavg.c login.c login_tty.c logout.c logwtmp.c kvm.c \
	pty.c pwcache.c
MAN3=	getloadavg.0 pwcache.0
E 12
I 12
D 14
SRCS=	daemon.c getloadavg.c login.c login_tty.c logout.c logwtmp.c \
D 13
	kvm.c kvm_${MACHINE}.c kvm_proc.c pty.c pwcache.c
MAN3=	getloadavg.0 kvm.0 kvm_geterr.0 kvm_getprocs.0 kvm_nlist.0 \
	kvm_open.0 pwcache.0
E 13
I 13
	pty.c pwcache.c
MAN3=	getloadavg.0 pwcache.0
E 13
E 12
E 6
E 5
E 4

I 8
D 12
MLINKS+=pwcache.3 user_from_uid.3 pwcache.3 group_from_gid.3
E 12
I 12
D 13
MLINKS+=pwcache.3 user_from_uid.3 pwcache.3 group_from_gid.3 \
	kvm.3 kvm_read.3 kvm.3 kvm_write.3 \
	kvm_open.3 kvm_openfiles.3 kvm_open.3 kvm_close.3 \
	kvm_getprocs.3 kvm_getargv.3 kvm_getprocs.3 kvm_getenvv.3
E 13
I 13
MLINKS+=pwcache.3 user_from_uid.3 pwcache.3 group_from_gid.3
E 14
I 14
SRCS=	login.c login_tty.c logout.c logwtmp.c pty.c
E 14
E 13
E 12

E 8
D 5
.c.o:
	@${CC} -p ${CFLAGS} -c $*.c
	@-ld -X -o profiled/$*.o -r $*.o
	${CC} ${CFLAGS} -c $*.c
	@-ld -x -r $*.o
	@mv a.out $*.o

D 3
all: libutil libutil_p
E 3
I 3
all: libutil.a libutil_p.a llib-lutil.ln
E 3

D 3
libutil libutil_p: ${OBJS}
	@echo building profiled libutil
	@cd profiled; ar cu ../libutil_p ${OBJS}
	ranlib libutil_p
E 3
I 3
libutil.a libutil_p.a: ${OBJS}
E 3
	@echo building normal libutil
D 3
	@ar cu libutil ${OBJS}
	ranlib libutil
E 3
I 3
	@ar cu libutil.a ${OBJS}
	ranlib libutil.a
	@echo building profiled libutil
	@cd profiled; ar cu ../libutil_p.a ${OBJS}
	ranlib libutil_p.a
E 3

D 3
tags:
E 3
I 3
llib-lutil.ln: ${SRCS}
	lint -Cutil ${CFLAGS} ${SRCS}
E 3

clean:
D 3
	rm -f ${OBJS} profiled/*.o libutil libutil_p
E 3
I 3
	rm -f ${OBJS} profiled/*.o libutil.a libutil_p.a
E 3

I 2
cleandir: clean
	rm -f .depend

E 2
depend:
	mkdep ${CFLAGS} ${SRCS}

D 4
install:
E 4
I 4
install: ${MAN}
E 4
D 3
	install -o bin -g bin -m 644 libutil ${DESTDIR}/usr/lib/libutil.a
	ranlib ${DESTDIR}/usr/lib/libutil.a
	install -o bin -g bin -m 644 libutil_p ${DESTDIR}/usr/lib/libutil_p.a
	ranlib ${DESTDIR}/usr/lib/libutil_p.a
E 3
I 3
	install -o bin -g bin -m 644 libutil.a ${DESTDIR}/usr/lib
	ranlib -t ${DESTDIR}/usr/lib/libutil.a
	install -o bin -g bin -m 644 libutil_p.a ${DESTDIR}/usr/lib
	ranlib -t ${DESTDIR}/usr/lib/libutil_p.a
	install -o bin -g bin -m 644 llib-lutil.ln ${DESTDIR}/usr/libexec/lint
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
E 4
E 3

I 3
tags:
	ctags ${SRCS}
E 5
I 5
.include <bsd.lib.mk>
E 5
E 3
E 1
