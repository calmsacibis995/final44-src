h33956
s 00004/00000/00025
d D 5.12 92/07/15 09:27:48 bostic 15 14
c create the include/rpc directory first; should check to see if necessary
c but not worth the time right now
e
s 00000/00001/00025
d D 5.11 90/09/06 14:45:50 bostic 14 13
c .PATH not needed
e
s 00001/00001/00025
d D 5.10 90/08/25 19:05:09 mckusick 13 12
c fix include path
e
s 00002/00006/00024
d D 5.9 90/08/23 16:24:38 mckusick 12 11
c cleanup install
e
s 00014/00015/00016
d D 5.8 90/08/23 16:20:38 mckusick 11 10
c update for Sun RPC 4.0
e
s 00001/00000/00030
d D 5.7 90/07/01 10:48:31 bostic 10 9
c clean portmap
e
s 00001/00001/00029
d D 5.6 90/06/30 22:47:54 karels 9 8
c use daemon() call
e
s 00000/00001/00030
d D 5.5 90/06/08 14:04:06 bostic 8 7
c don't need own anymore
e
s 00002/00001/00029
d D 5.4 90/06/08 14:03:41 bostic 7 6
c ranlib so can make program
e
s 00001/00001/00029
d D 5.3 90/05/13 14:18:50 bostic 6 5
c portmap requires librpc.a
e
s 00001/00000/00029
d D 5.2 90/05/13 14:03:36 bostic 5 4
c needs BINOWN etc.
e
s 00023/00126/00006
d D 5.1 90/05/11 12:50:04 bostic 4 3
c first pass for new make
e
s 00010/00007/00122
d D 1.3 90/03/22 18:19:45 bostic 3 2
c checkpoint for pmake
e
s 00016/00008/00113
d D 1.2 89/07/11 18:48:45 mckusick 2 1
c update to install in the standard place
e
s 00121/00000/00000
d D 1.1 89/07/10 17:38:32 mckusick 1 0
c date and time created 89/07/10 17:38:32 by mckusick
e
u
U
t
T
I 1
D 4
#
# 	Makefile	1.3	85/02/08
#
DESTDIR=
E 4
I 4
#	%W% (Berkeley) %G%
E 4

D 4
SRC=	auth_none.c auth_unix.c authunix_prot.c \
	clnt_perror.c clnt_raw.c clnt_simple.c clnt_tcp.c clnt_udp.c \
	pmap_clnt.c pmap_getmaps.c pmap_getport.c pmap_prot.c pmap_rmt.c \
	rpc_prot.c \
	svc.c svc_auth.c svc_auth_unix.c svc_raw.c svc_simple.c \
	svc_tcp.c svc_udp.c xdr.c xdr_array.c xdr_float.c xdr_mem.c xdr_rec.c \
	xdr_reference.c xdr_stdio.c
E 4
I 4
LIB=	rpc
D 13
CFLAGS+=-I${.CURDIR}
E 13
I 13
CFLAGS+=-I${.CURDIR}/..
E 13
D 11
SRCS=	auth_none.c auth_unix.c authunix_prot.c clnt_perror.c clnt_raw.c \
	clnt_simple.c clnt_tcp.c clnt_udp.c pmap_clnt.c pmap_getmaps.c \
	pmap_getport.c pmap_prot.c pmap_rmt.c rpc_prot.c svc.c svc_auth.c \
	svc_auth_unix.c svc_raw.c svc_simple.c svc_tcp.c svc_udp.c xdr.c \
	xdr_array.c xdr_float.c xdr_mem.c xdr_rec.c xdr_reference.c \
	xdr_stdio.c
HDRS=	auth.h auth_unix.h clnt.h pmap_clnt.h pmap_prot.h rpc.h rpc_msg.h \
	svc.h svc_auth.h types.h xdr.h
MAN8=	portmap.0
.PATH: ${.CURDIR} ${.CURDIR}/doc
I 10
CLEANFILES=portmap
E 11
I 11
SRCS=	auth_none.c auth_unix.c  authunix_prot.c bindresvport.c \
	clnt_generic.c clnt_perror.c clnt_raw.c clnt_simple.c clnt_tcp.c \
	clnt_udp.c rpc_dtablesize.c get_myaddress.c getrpcent.c getrpcport.c \
	pmap_clnt.c pmap_getmaps.c pmap_getport.c pmap_prot.c \
	pmap_prot2.c pmap_rmt.c rpc_prot.c rpc_commondata.c rpc_callmsg.c \
	svc.c svc_auth.c svc_auth_unix.c svc_raw.c svc_run.c svc_simple.c \
	svc_tcp.c svc_udp.c xdr.c xdr_array.c xdr_mem.c \
	xdr_rec.c xdr_reference.c xdr_stdio.c
E 11
E 10
E 4

D 4
OBJ=	auth_none.o auth_unix.o authunix_prot.o clnt_perror.o clnt_raw.o\
	clnt_simple.o clnt_tcp.o clnt_udp.o \
	pmap_clnt.o pmap_getmaps.o pmap_getport.o pmap_prot.o pmap_rmt.o \
	rpc_prot.o \
	svc.o svc_auth.o svc_auth_unix.o svc_raw.o svc_simple.o \
	svc_tcp.o svc_udp.o xdr.o xdr_array.o xdr_float.o xdr_mem.o xdr_rec.o \
	xdr_reference.o xdr_stdio.o
INC=	auth.h auth_unix.h clnt.h pmap_clnt.h\
	pmap_prot.h rpc.h rpc_msg.h svc.h svc_auth.h types.h xdr.h
E 4
I 4
D 11
all: portmap
E 11
I 11
UNSUPPORTED=	xdr_float.c 
E 11
E 4

I 2
D 4
MAN=	portmap.0 rpcinfo.0
E 4
I 4
D 6
portmap: portmap.c
E 6
I 6
D 11
portmap: portmap.c librpc.a
I 7
	ranlib librpc.a
E 7
E 6
D 9
	${CC} ${CFLAGS} ${.CURDIR}/portmap.c librpc.a -o ${.TARGET}
E 9
I 9
	${CC} ${CFLAGS} ${.CURDIR}/portmap.c librpc.a -lutil -o ${.TARGET}
E 11
I 11
D 12
HDRS=	auth.h auth_unix.h clnt.h netdb.h pmap_clnt.h \
E 12
I 12
HDRS=	auth.h auth_unix.h clnt.h pmap_clnt.h \
E 12
	pmap_prot.h pmap_rmt.h rpc.h rpc_msg.h svc.h svc_auth.h types.h xdr.h
D 14
.PATH: ${.CURDIR} ${.CURDIR}/doc
E 14

all: librpc.a
E 11
E 9
E 4

E 2
D 4
CFLAGS= -O -I.
E 4
I 4
D 12
beforeinstall: hdrs
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} portmap \
	    ${DESTDIR}/usr/sbin/portmap
E 4

D 4
.c.o:
D 3
	${CC} -p -c ${CFLAGS} $*.c
	-ld -X -r $*.o
	mv a.out profiled/$*.o
E 3
	${CC} ${CFLAGS} -c $*.c
D 3
	-ld -x -r $*.o
	mv a.out $*.o
E 3
I 3
	@-ld -x -r $*.o
	@mv a.out $*.o
	@${CC} -p -c ${CFLAGS} $*.c
	@-ld -X -r $*.o
	@mv a.out profiled/$*.o
E 4
I 4
hdrs: ${HDRS}
E 12
I 12
beforeinstall: ${HDRS}
I 15
	rm -rf ${DESTDIR}/usr/include/rpc
	mkdir ${DESTDIR}/usr/include/rpc
	chown bin.bin ${DESTDIR}/usr/include/rpc
	chmod 755 ${DESTDIR}/usr/include/rpc
E 15
E 12
D 7
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.ALLSRC} \
E 7
I 7
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${HDRS} \
E 7
	    ${DESTDIR}/usr/include/rpc
E 4
E 3

I 5
D 8
.include <bsd.own.mk>
E 8
E 5
D 2
all: rpclib portmap rpcinfo
E 2
I 2
D 4
all: rpclib portmap rpcinfo ${MAN}
E 2

portmap: portmap.o
D 3
	cc $(CFLAGS) portmap.o rpclib -o portmap
E 3
I 3
	${CC} $(CFLAGS) portmap.o rpclib -o portmap
E 3

rpcinfo: rpcinfo.o
D 3
	cc $(CFLAGS) rpcinfo.o rpclib -o rpcinfo
E 3
I 3
	${CC} $(CFLAGS) rpcinfo.o rpclib -o rpcinfo
E 3

rpclib rpclib_p: ${OBJ}
	@echo "building profiled rpclib"
	@cd profiled; ar cru ../rpclib_p ${OBJ}
	@echo "building normal rpclib"
	@ar cru rpclib ${OBJ}
	ranlib rpclib

I 2
rpcinfo.0: doc/rpcinfo.8
	nroff -man -h doc/rpcinfo.8 > rpcinfo.0

portmap.0: doc/portmap.8c
	nroff -man -h doc/portmap.8c > portmap.0

E 2
install: all
	-mkdir ${DESTDIR}/usr/include/rpc && \
		chmod 755 ${DESTDIR}/usr/include/rpc
	-for i in *.h; do \
D 2
		(install -c -m 644 $$i ${DESTDIR}/usr/include/rpc) done
	install rpclib ${DESTDIR}/usr/new/lib/librpc.a
	ranlib ${DESTDIR}/usr/new/lib/librpc.a
	install -s portmap ${DESTDIR}/usr/new/portmap
	install -s rpcinfo ${DESTDIR}/usr/new/rpcinfo
	install -c -m 444 doc/rpcinfo.8 ${DESTDIR}/usr/man/mann/rpcinfo.n
	install -c -m 444 doc/portmap.8c ${DESTDIR}/usr/man/mann/portmap.n
E 2
I 2
		(install -c -m 444 $$i ${DESTDIR}/usr/include/rpc) done
	install rpclib ${DESTDIR}/usr/lib/librpc.a
	ranlib ${DESTDIR}/usr/lib/librpc.a
	install -s portmap ${DESTDIR}/usr/sbin/portmap
	install -c -o bin -g bin -m 444 portmap.0 ${DESTDIR}/usr/share/man/cat8
#	install -s rpcinfo ${DESTDIR}/usr/sbin/rpcinfo
#	install -c -o bin -g bin -m 444 rpcinfo.0 ${DESTDIR}/usr/share/man/cat8
E 2

tags: $(SRC) $(KSRC) $(INC)
	ctags -tw $(SRC) $(KSRC) $(INC)

ref: tags
	sed 's,	/.*,,' tags | \
	awk ' { printf("%-26s%-16s%s\n", $$1, $$2, $$3) }' > ref

lint:
	lint -bnuvx $(SRC)

print:
	pr $(INC) $(SRC) $(KSRC) | lpr -Pvp

clean:
	rm -f $(OBJ) librpc.a linted made profiled/*.o portmap.o rpcinfo.o
I 3

cleandir: clean
	rm -f $(MAN) tags .depend
E 3

depend:
	@-grep '^#include' $(SRC) | grep -v '<' | grep -v '../' | \
	sed 's/:[^"]*"\([^"]*\)".*/: \1/' | sed 's/\.[cs]:/.o:/' | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' >> makedep
	@echo '/^# DO NOT DELETE THIS LINE/+1,$$d' >eddep
	@echo '$$r makedep' >>eddep
	@echo 'w' >>eddep
	@cp Makefile makefile.bak
	@ed - Makefile < eddep
	@rm eddep makedep makefile.bak



# DO NOT DELETE THIS LINE

auth_none.o: types.h xdr.h auth.h
auth_unix.o: types.h xdr.h auth.h auth_unix.h
authunix_prot.o: types.h xdr.h auth.h auth_unix.h
clnt_perror.o: types.h xdr.h auth.h clnt.h rpc_msg.h
clnt_raw.o: types.h xdr.h auth.h clnt.h rpc_msg.h
clnt_tcp.o: types.h xdr.h auth.h clnt.h rpc_msg.h pmap_clnt.h
clnt_udp.o: types.h xdr.h auth.h clnt.h rpc_msg.h pmap_clnt.h
pmap_clnt.o: types.h xdr.h auth.h clnt.h rpc_msg.h pmap_prot.h pmap_clnt.h
pmap_getmaps.o: types.h xdr.h auth.h clnt.h rpc_msg.h pmap_prot.h pmap_clnt.h
pmap_getport.o: types.h xdr.h auth.h clnt.h rpc_msg.h pmap_prot.h pmap_clnt.h
pmap_prot.o: types.h xdr.h pmap_prot.h
pmap_rmt.o: types.h xdr.h auth.h clnt.h rpc_msg.h pmap_prot.h pmap_clnt.h
rpc_prot.o: types.h xdr.h auth.h clnt.h rpc_msg.h
svc.o: types.h xdr.h auth.h clnt.h rpc_msg.h svc.h svc_auth.h
svc_auth.o: types.h xdr.h auth.h clnt.h rpc_msg.h svc.h svc_auth.h
svc_auth_unix.o: types.h xdr.h auth.h clnt.h rpc_msg.h svc.h auth_unix.h
svc_auth_unix.o: svc_auth.h
svc_raw.o: types.h xdr.h auth.h clnt.h rpc_msg.h svc.h
svc_tcp.o: types.h xdr.h auth.h clnt.h rpc_msg.h svc.h
svc_udp.o: types.h xdr.h auth.h clnt.h rpc_msg.h svc.h
xdr.o: types.h xdr.h
xdr_array.o: types.h xdr.h
xdr_float.o: types.h xdr.h
xdr_mem.o: types.h xdr.h
xdr_rec.o: types.h xdr.h
xdr_reference.o: types.h xdr.h
xdr_stdio.o: types.h xdr.h
E 4
I 4
.include <bsd.lib.mk>
E 4
E 1
