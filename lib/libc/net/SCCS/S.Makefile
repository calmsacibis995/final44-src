h05290
s 00001/00001/00147
d D 5.25 93/01/29 17:08:08 sklower 37 36
c include man page for primitive iso & link layer address functions
e
s 00007/00007/00141
d D 5.24 90/03/15 21:53:41 mckusick 36 35
c update for separate machine compilation
e
s 00113/00024/00035
d D 5.23 90/03/11 18:15:12 bostic 35 34
c major reorganization; add installation of man pages
e
s 00002/00002/00057
d D 5.22 89/01/06 19:38:22 karels 34 33
c rm ruserpass (obsolete)
e
s 00003/00000/00056
d D 5.21 88/09/20 16:43:22 bostic 33 32
c add cleandir
e
s 00000/00063/00056
d D 5.20 88/08/30 16:12:36 bostic 32 31
c remove dependency list
e
s 00010/00005/00109
d D 5.19 88/06/27 17:13:07 bostic 31 30
c install approved copyright notice
e
s 00001/00000/00113
d D 5.18 88/05/20 14:55:32 bostic 30 29
c set DEFS to compile in SCCS ids.
e
s 00013/00013/00100
d D 5.17 88/05/20 13:38:37 bostic 29 28
c restructuring libc
e
s 00034/00017/00079
d D 5.16 88/03/14 13:04:19 bostic 28 27
c add res_query.c, Berkeley specific header
e
s 00002/00002/00094
d D 5.15 87/11/21 16:25:58 karels 27 26
c add herror.c (for bostic)
e
s 00015/00035/00081
d D 5.14 87/06/06 14:34:13 bostic 26 25
c new template
e
s 00009/00003/00107
d D 5.13 86/03/18 09:59:03 kjd 25 24
c make depend - after moving resolv.h to /usr/include
e
s 00022/00002/00088
d D 5.12 86/03/16 22:45:03 bloom 24 23
c move resolver routines so that they are always included in libc (gethostby*
c not moved to preserve lookup choice)
e
s 00003/00003/00087
d D 5.11 85/09/09 19:43:18 bloom 23 22
c add includes to rcmd.c
e
s 00003/00001/00087
d D 5.10 85/09/06 16:51:14 bloom 22 21
c change in rcmd.c includes
e
s 00049/00001/00039
d D 5.9 85/09/05 11:44:27 bloom 21 19
c fix make clean and add make depend
e
s 00049/00001/00039
d R 5.9 85/09/05 10:21:12 bloom 20 19
c fix make clean and add make depend
e
s 00002/00027/00038
d D 5.8 85/09/04 19:01:36 bloom 19 18
c fix for proper host lookup
e
s 00002/00000/00063
d D 5.7 85/07/18 17:42:59 kjd 18 17
c Changes to get makeing resolvers work right
e
s 00005/00003/00058
d D 5.6 85/07/13 22:05:52 mckusick 17 16
c spelling; force recompilation
e
s 00001/00001/00060
d D 5.5 85/07/13 21:39:53 mckusick 16 15
c must pass down DEFS
e
s 00022/00004/00039
d D 5.4 85/07/12 16:33:36 kjd 15 13
c Add verable RESOLVER to determine which resolver to compile in
e
s 00021/00003/00040
d R 5.4 85/07/12 15:52:16 kjd 14 13
c Add verable RESOLVE to determine which resolver is used
e
s 00001/00001/00042
d D 5.3 85/06/18 22:49:01 mckusick 13 12
c add DEFS
e
s 00013/00001/00030
d D 5.2 85/05/30 22:35:12 sam 12 11
c add tags
e
s 00006/00001/00025
d D 5.1 85/05/30 11:59:40 dist 11 10
c Add copyright
e
s 00001/00001/00025
d D 4.10 84/01/31 16:50:17 ralph 10 9
c replaced gethostbyname and gethostbyaddr with gethostnamadr.
e
s 00003/00002/00023
d D 4.9 83/06/30 19:50:00 sam 9 8
c clean out everything
e
s 00006/00001/00019
d D 4.8 83/06/27 18:25:32 root 8 7
c new organization
e
s 00001/00001/00019
d D 4.7 83/05/28 15:01:02 sam 7 6
c bye bye raddr/rhost
e
s 00002/00006/00018
d D 4.6 82/12/17 17:10:28 sam 6 5
c no more asm.sed
e
s 00000/00002/00024
d D 4.5 82/11/14 14:07:24 sam 5 4
c archive built by Makefile one level up
e
s 00001/00001/00025
d D 4.4 82/11/14 13:55:25 sam 4 3
c merge off 4.1b with 4.1c; and random conversion to netdb library
e
s 00002/00000/00024
d D 4.3 82/10/10 18:20:28 sam 3 2
c reorganize directory structure
e
s 00004/00007/00020
d D 4.2 82/10/07 17:02:03 sam 2 1
c sundries
e
s 00027/00000/00000
d D 4.1 82/10/06 21:16:05 sam 1 0
c date and time created 82/10/06 21:16:05 by sam
e
u
U
t
T
I 1
D 9
# %W% %G%
E 9
I 9
D 11
# 	%M%	%I%	%E%
E 11
I 11
#
D 28
# Copyright (c) 1983 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 28
I 28
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
E 28
#
I 28
# Redistribution and use in source and binary forms are permitted
D 31
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 31
I 31
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
E 31
#
E 28
#	%W% (Berkeley) %G%
E 11
#
I 35
OBJS=	gethostnamadr.o getnetbyaddr.o getnetbyname.o getnetent.o \
	getproto.o getprotoent.o getprotoname.o getservbyname.o \
	getservbyport.o getservent.o herror.o htonl.o htons.o inet_addr.o \
	inet_lnaof.o inet_makeaddr.o inet_netof.o inet_network.o \
	inet_ntoa.o iso_addr.o ns_addr.o ns_ntoa.o ntohl.o ntohs.o \
	rcmd.o recv.o res_comp.o res_debug.o res_init.o res_mkquery.o \
	res_query.o res_send.o send.o sethostent.o
SRCS=	gethostnamadr.c getnetbyaddr.c getnetbyname.c getnetent.c \
	getproto.c getprotoent.c getprotoname.c getservbyname.c \
	getservbyport.c getservent.c herror.c inet_addr.c \
	inet_lnaof.c inet_makeaddr.c inet_netof.c inet_network.c \
	inet_ntoa.c iso_addr.c ns_addr.c ns_ntoa.c \
	rcmd.c recv.c res_comp.c res_debug.c res_init.c \
	res_mkquery.c res_query.c res_send.c send.c sethostent.c
MAN=	byteorder.0 gethostbyname.0 getnetent.0 getprotoent.0 getservent.0 \
D 37
	inet.0 ns.0 rcmd.0 resolver.0
E 37
I 37
	inet.0 iso_addr.0 linkaddr.0 ns.0 rcmd.0 resolver.0
E 37

# Tahoe specific sources
TSRC=	${SRCS}
TASRC=	htonl.s htons.s ntohl.s ntohs.s

# Vax specific sources
D 36
#VSRC=	${SRCS}
#VASRC=	htonl.s htons.s ntohl.s ntohs.s
E 36
I 36
VSRC=	${SRCS}
VASRC=	htonl.s htons.s ntohl.s ntohs.s
E 36

VPATH=	${MACHINE}
E 35
I 30
DEFS=	-DLIBC_SCCS
I 35
FLAGS=	-I../${MACHINE} ${DEFS}
E 35
E 30
I 29
CFLAGS=	-O ${DEFS}
E 29
E 9
I 8
D 15

I 12
SRCS=	gethostent.c gethostnamadr.c \
	getnetbyaddr.c getnetent.c getnetbyname.c \
E 15
I 15
D 19
#*********************************************************************
#								     #
#	RESOLVER defines which resolver is to be compiled into libc  #
#								     #
#		defining RESOLVER to res_named, compiles the         #
#		routines which the BIND nameserver uses into libc    #
#---------------------------------------------------------------------
#RESOLVER=	res_named
#---------------------------------------------------------------------
#		defining RESOLVER to res_static, compiles            #
#		the routines which use the old method of             #
#		hostname resolveing. (ie /etc/HOSTS )                #
#---------------------------------------------------------------------
RESOLVER=	res_static
#*********************************************************************
SRCS=	gethostent.c getnetbyaddr.c getnetent.c getnetbyname.c \
E 19
I 19
D 28
SRCS=	getnetbyaddr.c getnetent.c getnetbyname.c \
E 19
E 15
	getproto.c getprotoent.c getprotoname.c \
	getservent.c getservbyport.c getservbyname.c \
D 24
	rcmd.c rexec.c ruserpass.c
E 24
I 24
D 27
	rcmd.c rexec.c ruserpass.c \
E 27
I 27
	herror.c rcmd.c rexec.c ruserpass.c \
E 27
	res_comp.c res_debug.c res_init.c res_mkquery.c res_send.c
E 28
I 28
D 35
SRCS=	getnetbyaddr.c getnetent.c getnetbyname.c getproto.c getprotoent.c \
	getprotoname.c getservent.c getservbyport.c getservbyname.c \
D 34
	herror.c rcmd.c rexec.c ruserpass.c res_comp.c res_debug.c \
E 34
I 34
	herror.c rcmd.c rexec.c res_comp.c res_debug.c \
E 34
	res_init.c res_mkquery.c res_query.c res_send.c
OBJS=	getnetbyaddr.o getnetent.o getnetbyname.o getproto.o getprotoent.o \
	getprotoname.o getservent.o getservbyport.o getservbyname.o \
D 34
	herror.o rcmd.o rexec.o ruserpass.o res_comp.o res_debug.o \
E 34
I 34
	herror.o rcmd.o rexec.o res_comp.o res_debug.o \
E 34
	res_init.o res_mkquery.o res_query.o res_send.o
E 35
E 28
D 29

E 24
E 12
E 8
D 10
OBJS=	gethostbyname.o gethostbyaddr.o gethostent.o \
E 10
I 10
D 15
OBJS=	gethostent.o gethostnamadr.o \
E 15
I 15
D 19
OBJS=	gethostent.o gethostbyname.o gethostbyaddr.o \
E 15
E 10
	getnetbyaddr.o getnetent.o getnetbyname.o \
E 19
I 19
D 28
OBJS=	getnetbyaddr.o getnetent.o getnetbyname.o \
E 19
	getproto.o getprotoent.o getprotoname.o \
	getservent.o getservbyport.o getservbyname.o \
D 2
	inet_addr.o \
E 2
D 4
	raddr.o rexec.o rhost.o ruserpass.o
E 4
I 4
D 7
	raddr.o rcmd.o rexec.o rhost.o ruserpass.o
E 7
I 7
D 24
	rcmd.o rexec.o ruserpass.o
E 24
I 24
D 27
	rcmd.o rexec.o ruserpass.o \
E 27
I 27
	herror.o rcmd.o rexec.o ruserpass.o \
E 27
	res_comp.o res_debug.o res_init.o res_mkquery.o res_send.o

E 28
E 24
E 7
E 4
D 13
CFLAGS=	-O
E 13
I 13
CFLAGS=	-O ${DEFS}
E 29
E 13
I 12
TAGSFILE=tags
I 35
MDIR=	${DESTDIR}/usr/man/cat3
E 35
E 12

I 35
.SUFFIXES:
.SUFFIXES: .o .s .c .3 .0

.s.o:
	@${CPP} -E ${FLAGS} -DPROF $< | ${AS} -o $*.o
	@ld -X -o profiled/$*.o -r $*.o
	${CPP} -E ${FLAGS} $< | ${AS} -o $*.o
	@ld -x -r $*.o
D 36
	@mv a.out $*.o
E 36
I 36
	@mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 36

E 35
.c.o:
D 6
	${CC} -p -S ${CFLAGS} $*.c
D 2
	sed -f asm.sed $*.s | as -o $*.o
E 2
I 2
	sed -f ../asm.sed $*.s | as -o $*.o
E 2
	rm -f $*.s
E 6
I 6
D 29
	${CC} -p -c ${CFLAGS} $*.c
E 6
	-ld -X -r $*.o
	mv a.out profiled/$*.o
E 29
I 29
D 35
	@${CC} -p -c ${CFLAGS} $*.c
E 35
I 35
	@${CC} -p ${CFLAGS} -c $<
E 35
	@-ld -X -o profiled/$*.o -r $*.o
E 29
D 6
	${CC} -S ${CFLAGS} -c $*.c
D 2
	sed -f asm.sed $*.s | as -o $*.o
E 2
I 2
	sed -f ../asm.sed $*.s | as -o $*.o
E 2
	rm -f $*.s
E 6
I 6
D 35
	${CC} ${CFLAGS} -c $*.c
E 35
I 35
	${CC} ${CFLAGS} -c $<
E 35
E 6
D 29
	-ld -x -r $*.o
	mv a.out $*.o
E 29
I 29
	@-ld -x -r $*.o
D 36
	@mv a.out $*.o
E 36
I 36
	@mv ${OBJDIR}a.out ${OBJDIR}$*.o
E 36
E 29

D 2
netlib netlib_p: ${OBJS}
	ar cru netlib ${OBJS}
	cd profiled; ar cru ../netlib_p ${OBJS}
E 2
I 2
D 8
all:	${OBJS}
E 8
I 8
D 29
netlib netlib_p: ${OBJS}
	@echo "building profiled netlib"
	@cd profiled; ar cru ../netlib_p ${OBJS}
	@echo "building normal netlib"
	@ar cru netlib ${OBJS}
E 29
I 29
all: ${OBJS}
E 29
I 18
D 19
	cd ${RESOLVER}; make netlib
E 19
D 35

I 29
link: ${OBJS}
	(cd ../library; rm -f ${OBJS})
	(cd ../profiled; rm -f ${OBJS})
E 35
I 35
	cd ../library; rm -f ${OBJS}
E 35
D 36
	ln ${OBJS} ../library
E 36
I 36
	cd ${OBJDIR}.; ln ${OBJS} ../library
E 36
D 35
	(cd profiled; ln ${OBJS} ../../profiled)
E 35
I 35
	cd ../profiled; rm -f ${OBJS}
D 36
	cd profiled; ln ${OBJS} ../../profiled
E 36
I 36
	cd ${OBJDIR}./profiled; ln ${OBJS} ../../profiled
E 36
E 35

E 29
E 18
E 8
I 3
D 5
	ar cru ../netlib ${OBJS}
	cd profiled; ar cru ../../netlib_p ${OBJS}
E 5
E 3
E 2
D 19

I 15
D 17
gethostbyname.o gethostbyaddr.o:
	@echo "useing " ${RESOLVER} " routines for " $*
D 16
	@cd ${RESOLVER}; make $*.o
E 16
I 16
	@cd ${RESOLVER}; make DEFS=${DEFS} $*.o
E 17
I 17
gethostbyname.o gethostbyaddr.o: REFS
	@echo "using " ${RESOLVER} " routines for " $*
	cd ${RESOLVER}; make DEFS=${DEFS} $*.o

REFS:
E 17
E 16

E 19
E 15
I 12
D 35
tags:
E 35
I 35
clean:
D 36
	rm -f *.o profiled/* a.out core
E 36
I 36
	rm -f ${OBJDIR}*.o profiled/* ${OBJDIR}a.out core
E 36

cleandir: clean
	rm -f ${MAN} tags .depend

depend: depend.${MACHINE}

depend.tahoe: ${TSRC}
	mkdep ${CFLAGS} ${TSRC}

depend.vax: ${VSRC}
	mkdep ${CFLAGS} ${VSRC}

tags: tags.${MACHINE}

tags.tahoe: ${TSRC} ${TASRC}
	rm -f ${TAGSFILE}
E 35
	cwd=`pwd`; \
D 35
	for i in ${SRCS}; do \
E 35
I 35
	for i in ${TSRC}; do \
E 35
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
I 35
	(P=`pwd`; \
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${TASRC} | sed \
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
	>> ${TAGSFILE})
E 35

E 12
D 35
clean:
I 15
D 19
	@cd ${RESOLVER}; make clean
E 19
E 15
D 2
	rm -f netlib netlib_p ${OBJS} profiled/*.o
E 2
I 2
D 9
	rm -f ${OBJS} profiled/*.o errs a.out core
E 9
I 9
D 12
	rm -f ${OBJS} profiled/*.o errs a.out core netlib netlib_p
E 12
I 12
D 21
	rm -f ${OBJS} profiled/*.o errs a.out core netlib netlib_p tags
E 21
I 21
D 26
	rm -f *.o profiled/*.o errs a.out core netlib netlib_p \
		tags Makefile.bak
E 26
I 26
D 29
	rm -f *.o profiled/*.o errs a.out core netlib netlib_p tags
E 29
I 29
	rm -f *.o profiled/* a.out core ${TAGSFILE}
E 35
I 35
tags.vax: ${VSRC} ${VASRC}
	rm -f ${TAGSFILE}
	cwd=`pwd`; \
	for i in ${VSRC}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
	(P=`pwd`; \
	egrep "^ENTRY(.*)|^SYSCALL(.*)" ${VASRC} | sed \
"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 $$P/\1 /^\2(\3\4$$/;" \
	>> ${TAGSFILE})
E 35
E 29
E 26

I 33
D 35
cleandir: clean
	rm -f .depend

E 33
depend:
D 26
	for i in ${SRCS}; do \
	    cc -M ${CFLAGS} $$i | awk ' { if ($$1 != prev) \
		{ if (rec != "") print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		else rec = rec " " $$2 } } \
		END { print rec } ' >> makedep; done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 26
I 26
	mkdep ${CFLAGS} ${SRCS}
E 35
I 35
install: ${MAN}
	install -c -o bin -g bin -m 444 ${MAN} ${MDIR}
	rm -f ${MDIR}/htonl.0; ln ${MDIR}/byteorder.0 ${MDIR}/htonl.0
	rm -f ${MDIR}/htons.0; ln ${MDIR}/byteorder.0 ${MDIR}/htons.0
	rm -f ${MDIR}/ntohl.0; ln ${MDIR}/byteorder.0 ${MDIR}/ntohl.0
	rm -f ${MDIR}/ntohs.0; ln ${MDIR}/byteorder.0 ${MDIR}/ntohs.0
	rm -f ${MDIR}/endhostent.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/endhostent.0
	rm -f ${MDIR}/gethostbyaddr.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/gethostbyaddr.0
	rm -f ${MDIR}/sethostent.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/sethostent.0
	rm -f ${MDIR}/sethostfile.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/sethostfile.0
	rm -f ${MDIR}/gethostent.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/gethostent.0
	rm -f ${MDIR}/herror.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/herror.0
	rm -f ${MDIR}/endnetent.0; ln ${MDIR}/getnetent.0 ${MDIR}/endnetent.0
	rm -f ${MDIR}/getnetbyaddr.0; ln ${MDIR}/getnetent.0 ${MDIR}/getnetbyaddr.0
	rm -f ${MDIR}/getnetbyname.0; ln ${MDIR}/getnetent.0 ${MDIR}/getnetbyname.0
	rm -f ${MDIR}/setnetent.0; ln ${MDIR}/getnetent.0 ${MDIR}/setnetent.0
	rm -f ${MDIR}/endprotoent.0; ln ${MDIR}/getprotoent.0 ${MDIR}/endprotoent.0
	rm -f ${MDIR}/getprotobyname.0; ln ${MDIR}/getprotoent.0 ${MDIR}/getprotobyname.0
	rm -f ${MDIR}/getprotobynumber.0; ln ${MDIR}/getprotoent.0 ${MDIR}/getprotobynumber.0
	rm -f ${MDIR}/setprotoent.0; ln ${MDIR}/getprotoent.0 ${MDIR}/setprotoent.0
	rm -f ${MDIR}/endservent.0; ln ${MDIR}/getservent.0 ${MDIR}/endservent.0
	rm -f ${MDIR}/getservbyname.0; ln ${MDIR}/getservent.0 ${MDIR}/getservbyname.0
	rm -f ${MDIR}/getservbyport.0; ln ${MDIR}/getservent.0 ${MDIR}/getservbyport.0
	rm -f ${MDIR}/setservent.0; ln ${MDIR}/getservent.0 ${MDIR}/setservent.0
	rm -f ${MDIR}/addr.0; ln ${MDIR}/inet.0 ${MDIR}/addr.0
	rm -f ${MDIR}/inet_addr.0; ln ${MDIR}/inet.0 ${MDIR}/inet_addr.0
	rm -f ${MDIR}/inet_lnaof.0; ln ${MDIR}/inet.0 ${MDIR}/inet_lnaof.0
	rm -f ${MDIR}/inet_makeaddr.0; ln ${MDIR}/inet.0 ${MDIR}/inet_makeaddr.0
	rm -f ${MDIR}/inet_netof.0; ln ${MDIR}/inet.0 ${MDIR}/inet_netof.0
	rm -f ${MDIR}/inet_network.0; ln ${MDIR}/inet.0 ${MDIR}/inet_network.0
	rm -f ${MDIR}/inet_ntoa.0; ln ${MDIR}/inet.0 ${MDIR}/inet_ntoa.0
	rm -f ${MDIR}/network.0; ln ${MDIR}/inet.0 ${MDIR}/network.0
	rm -f ${MDIR}/ntoa.0; ln ${MDIR}/inet.0 ${MDIR}/ntoa.0
	rm -f ${MDIR}/ns_addr.0; ln ${MDIR}/ns.0 ${MDIR}/ns_addr.0
	rm -f ${MDIR}/ns_ntoa.0; ln ${MDIR}/ns.0 ${MDIR}/ns_ntoa.0
	rm -f ${MDIR}/rresvport.0; ln ${MDIR}/rcmd.0 ${MDIR}/rresvport.0
	rm -f ${MDIR}/ruserok.0; ln ${MDIR}/rcmd.0 ${MDIR}/ruserok.0
E 35
E 26
D 32

D 26
# DO NOT DELETE THIS LINE -- make depend uses it
E 26
I 26
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 26

getnetbyaddr.o: getnetbyaddr.c /usr/include/netdb.h
getnetent.o: getnetent.c /usr/include/stdio.h /usr/include/sys/types.h
getnetent.o: /usr/include/sys/socket.h /usr/include/netdb.h
getnetent.o: /usr/include/ctype.h
getnetbyname.o: getnetbyname.c /usr/include/netdb.h
getproto.o: getproto.c /usr/include/netdb.h
I 25
D 26
getnetbyaddr.o: getnetbyaddr.c /usr/include/netdb.h
getnetent.o: getnetent.c /usr/include/stdio.h /usr/include/sys/types.h
getnetent.o: /usr/include/sys/socket.h /usr/include/netdb.h
getnetent.o: /usr/include/ctype.h
getnetbyname.o: getnetbyname.c /usr/include/netdb.h
getproto.o: getproto.c /usr/include/netdb.h
E 26
E 25
getprotoent.o: getprotoent.c /usr/include/stdio.h /usr/include/sys/types.h
getprotoent.o: /usr/include/sys/socket.h /usr/include/netdb.h
getprotoent.o: /usr/include/ctype.h
getprotoname.o: getprotoname.c /usr/include/netdb.h
D 28
getservent.o: getservent.c /usr/include/stdio.h /usr/include/sys/types.h
E 28
I 28
getservent.o: getservent.c /usr/include/stdio.h /usr/include/sys/param.h
getservent.o: /usr/include/sys/types.h /usr/include/signal.h
getservent.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
getservent.o: /usr/include/machine/endian.h /usr/include/sys/types.h
E 28
getservent.o: /usr/include/sys/socket.h /usr/include/netdb.h
getservent.o: /usr/include/ctype.h
getservbyport.o: getservbyport.c /usr/include/netdb.h
getservbyname.o: getservbyname.c /usr/include/netdb.h
I 28
herror.o: herror.c /usr/include/sys/types.h /usr/include/sys/uio.h
E 28
D 22
rcmd.o: rcmd.c /usr/include/stdio.h /usr/include/sys/types.h
E 22
I 22
D 23
rcmd.o: rcmd.c /usr/include/stdio.h /usr/include/ctype.h
E 23
I 23
rcmd.o: rcmd.c /usr/include/stdio.h /usr/include/ctype.h /usr/include/pwd.h
E 23
D 26
rcmd.o: /usr/include/sys/param.h /usr/include/machine/machparam.h
rcmd.o: /usr/include/signal.h /usr/include/sys/types.h
E 22
D 23
rcmd.o: /usr/include/sys/socket.h /usr/include/netinet/in.h
rcmd.o: /usr/include/netdb.h /usr/include/errno.h
E 23
I 23
rcmd.o: /usr/include/sys/socket.h /usr/include/sys/stat.h
rcmd.o: /usr/include/netinet/in.h /usr/include/netdb.h /usr/include/errno.h
E 26
I 26
rcmd.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
D 28
rcmd.o: /usr/include/machine/machparam.h /usr/include/sys/file.h
E 28
I 28
rcmd.o: /usr/include/machine/trap.h /usr/include/machine/machparam.h
rcmd.o: /usr/include/machine/endian.h /usr/include/sys/file.h
E 28
rcmd.o: /usr/include/sys/signal.h /usr/include/sys/socket.h
rcmd.o: /usr/include/sys/stat.h /usr/include/netinet/in.h /usr/include/netdb.h
rcmd.o: /usr/include/errno.h
E 26
E 23
rexec.o: rexec.c /usr/include/sys/types.h /usr/include/sys/socket.h
rexec.o: /usr/include/netinet/in.h /usr/include/stdio.h /usr/include/netdb.h
rexec.o: /usr/include/errno.h
ruserpass.o: ruserpass.c /usr/include/stdio.h /usr/include/utmp.h
ruserpass.o: /usr/include/ctype.h /usr/include/sys/types.h
ruserpass.o: /usr/include/sys/stat.h /usr/include/errno.h
I 24
res_comp.o: res_comp.c /usr/include/sys/types.h /usr/include/stdio.h
res_comp.o: /usr/include/arpa/nameser.h
res_debug.o: res_debug.c /usr/include/sys/types.h /usr/include/netinet/in.h
res_debug.o: /usr/include/stdio.h /usr/include/arpa/nameser.h
res_init.o: res_init.c /usr/include/sys/types.h /usr/include/sys/socket.h
res_init.o: /usr/include/netinet/in.h /usr/include/stdio.h
D 25
res_init.o: /usr/include/arpa/nameser.h /usr/include/arpa/resolv.h
E 25
I 25
res_init.o: /usr/include/arpa/nameser.h /usr/include/resolv.h
E 25
res_mkquery.o: res_mkquery.c /usr/include/stdio.h /usr/include/sys/types.h
res_mkquery.o: /usr/include/netinet/in.h /usr/include/arpa/nameser.h
D 25
res_mkquery.o: /usr/include/arpa/resolv.h
E 25
I 25
res_mkquery.o: /usr/include/resolv.h
I 28
res_query.o: res_query.c /usr/include/sys/param.h /usr/include/sys/types.h
res_query.o: /usr/include/signal.h /usr/include/machine/trap.h
res_query.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
res_query.o: /usr/include/sys/socket.h /usr/include/netinet/in.h
res_query.o: /usr/include/ctype.h /usr/include/netdb.h /usr/include/stdio.h
res_query.o: /usr/include/errno.h /usr/include/strings.h
res_query.o: /usr/include/arpa/inet.h /usr/include/arpa/nameser.h
res_query.o: /usr/include/resolv.h
E 28
E 25
D 26
res_send.o: res_send.c /usr/include/sys/param.h
res_send.o: /usr/include/machine/machparam.h /usr/include/signal.h
res_send.o: /usr/include/sys/types.h /usr/include/sys/time.h
res_send.o: /usr/include/time.h /usr/include/sys/socket.h
E 26
I 26
res_send.o: res_send.c /usr/include/sys/param.h /usr/include/sys/types.h
D 28
res_send.o: /usr/include/signal.h /usr/include/machine/machparam.h
E 28
I 28
res_send.o: /usr/include/signal.h /usr/include/machine/trap.h
res_send.o: /usr/include/machine/machparam.h /usr/include/machine/endian.h
E 28
res_send.o: /usr/include/sys/time.h /usr/include/time.h
res_send.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
E 26
res_send.o: /usr/include/netinet/in.h /usr/include/stdio.h /usr/include/errno.h
D 25
res_send.o: /usr/include/arpa/nameser.h /usr/include/arpa/resolv.h
E 25
I 25
res_send.o: /usr/include/arpa/nameser.h /usr/include/resolv.h
E 25
E 24
D 26
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 26
I 26

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 32
E 26
E 21
E 12
E 9
E 2
E 1
