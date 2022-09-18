h07263
s 00006/00006/00034
d D 5.7 90/06/23 13:14:54 bostic 13 12
c use right ld flags, don't need substitution, why was it there??
e
s 00009/00018/00031
d D 5.6 90/05/29 20:31:08 bostic 12 11
c use links so don't rebuild each time
e
s 00030/00079/00019
d D 5.5 90/05/11 12:51:17 bostic 11 10
c first pass for new make
e
s 00024/00121/00074
d D 5.4 89/05/10 22:37:37 bostic 10 9
c cleanups, remove dependencies
e
s 00001/00001/00194
d D 5.3 88/05/21 16:28:24 bostic 9 8
c remove mkvers when cleaning
e
s 00172/00177/00023
d D 5.2 87/06/19 10:54:10 bostic 8 7
c new template
e
s 00007/00001/00193
d D 5.1 85/06/07 23:33:21 kre 7 5
c Add copyright
e
s 00002/00000/00194
d R 1.6 85/05/15 16:27:46 libs 6 5
c add f77_dump_flag.{c,o} to facilitate dumps only when desired.
e
s 00000/00002/00194
d D 1.5 85/05/06 14:31:34 libs 5 4
c delete signal_.[o,c] as same as one in libF77.
e
s 00002/00000/00194
d D 1.4 85/03/28 11:04:04 ralph 4 3
c added malloc_.c
e
s 00001/00001/00193
d D 1.3 84/06/08 10:32:27 ralph 3 2
c ioinit.f should be in the library
e
s 00010/00002/00184
d D 1.2 84/06/07 13:54:18 ralph 2 1
c moved ioinit.f from libI77 to here (from dlw).
e
s 00186/00000/00000
d D 1.1 83/05/20 10:43:19 nicklin 1 0
c date and time created 83/05/20 10:43:19 by nicklin
e
u
U
t
T
I 7
D 11
#
D 8
# Copyright (c) 1980 Regents of the University of California.
E 8
I 8
# Copyright (c) 1987 Regents of the University of California.
E 8
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
D 8
#	%W% (Berkeley) %G%
E 8
I 8
#	%W%	(Berkeley)	%G%
E 8
#
E 7
I 1
D 8
# Makefile for f77 system lib, libU77.a
E 8
I 8
CFLAGS=	-O
LIBC=	/lib/libc.a
DEST=	${DESTDIR}/usr/lib
LIBRARY=	libU77.a
LIBRARY_P=	libU77_p.a
E 11
I 11
#	%W% (Berkeley) %G%

LIB=	U77
E 11
SRCS=	access_.c alarm_.c chdir_.c chmod_.c ctime_.c dtime_.c etime_.c \
	f77lid_.c fdate_.c fgetc_.c fork_.c fputc_.c fseek_.c fstat_.c \
	ftell_.c gerror_.c getarg_.c getc_.c getcwd_.c getenv_.c getgid_.c \
	getlog_.c getpid_.c getuid_.c gmtime_.c hostnm_.c iargc_.c idate_.c \
	ierrno_.c ioinit.f isatty_.c itime_.c kill_.c link_.c loc_.c \
	lstat_.c ltime_.c malloc_.c perror_.c putc_.c qsort_.c rename_.c \
	sleep_.c stat_.c symlnk_.c system_.c tapeio.c time_.c ttynam_.c \
	unlink_.c wait_.c
D 11
OBJS=	access_.o alarm_.o chdir_.o chmod_.o ctime_.o dtime_.o etime_.o \
	f77lid_.o fdate_.o fgetc_.o fork_.o fputc_.o fseek_.o fstat_.o \
	ftell_.o gerror_.o getarg_.o getc_.o getcwd_.o getenv_.o getgid_.o \
	getlog_.o getpid_.o getuid_.o gmtime_.o hostnm_.o iargc_.o idate_.o \
	ierrno_.o ioinit.o isatty_.o itime_.o kill_.o link_.o loc_.o \
	lstat_.o ltime_.o malloc_.o perror_.o putc_.o qsort_.o rename_.o \
	sleep_.o stat_.o symlnk_.o system_.o tapeio.o time_.o ttynam_.o \
	unlink_.o wait_.o
E 11
E 8
D 7
# %W% (Berkeley) %G%
E 7

D 8
CFLAGS	      = -O
E 8
I 8
D 11
.c.o:
D 10
	${CC} -p ${CFLAGS} -c $*.c
	-ld -x -r $*.o
	mv a.out profiled/$*.o
E 10
I 10
	@${CC} -p ${CFLAGS} -c $*.c
	@-ld -x -r $*.o
	@mv a.out profiled/$*.o
E 10
	${CC} ${CFLAGS} -c $*.c
D 10
	-ld -x -r $*.o
	mv a.out $*.o
E 10
I 10
	@-ld -x -r $*.o
	@mv a.out $*.o
E 11
I 11
LDADD=		Version.o
CLEANFILES+=	Version.o Version.c mkvers
E 11
E 10
E 8

D 8
DEST	      = $(DESTDIR)/usr/lib
E 8
I 8
D 11
.f.o:
D 10
	${FC} -p ${FFLAGS} -c $*.f
	-ld -x -r $*.o
	mv a.out profiled/$*.o
E 10
I 10
	@${FC} -p ${FFLAGS} -c $*.f
	@-ld -x -r $*.o
	@mv a.out profiled/$*.o
E 10
	${FC} ${FFLAGS} -c $*.f
D 10
	-ld -x -r $*.o
	mv a.out $*.o
E 10
I 10
	@-ld -x -r $*.o
	@mv a.out $*.o
E 11
I 11
all: Version.o
E 11
E 10
E 8

D 8
DESTDIR	      =
E 8
I 8
D 11
all: ${LIBRARY} ${LIBRARY_P}
E 11
I 11
Version.o: Version.c
D 13
	${CC} -c Version.c
E 13
I 13
	${CC} -R -c Version.c
E 13
E 11
E 8

D 8
EXTHDRS	      =
E 8
I 8
D 11
${LIBRARY}: ${OBJS} Version
D 10
	@echo "Loading ${LIBRARY} ... "
E 10
I 10
	@echo "Loading normal ${LIBRARY} ... "
E 10
	@ar cru ${LIBRARY} ${OBJS} ioinit.f Version
D 10
	@ranlib ${LIBRARY}
E 10
I 10
	ranlib ${LIBRARY}
E 11
I 11
Version.c: mkvers ${SRCS}
	mkvers libU77.a ${.ALLSRC:M*.c} > ${.TARGET}
E 11
E 10
E 8

D 8
HDRS	      =
E 8
I 8
D 11
${LIBRARY_P}: ${OBJS} Version
D 10
	@echo "Loading ${LIBRARY_P} ... "
E 10
I 10
	@echo "Loading profiled ${LIBRARY_P} ... "
E 10
	@cd profiled; ar cru ../${LIBRARY_P} ${OBJS} Version
D 10
	@ranlib ${LIBRARY_P}
E 10
I 10
	ranlib ${LIBRARY_P}
E 10
E 8

D 8
LIBRARY	      = libU77.a
E 8
I 8
Version: ${SRCS} mkvers
	@rm -f Version.c
	./mkvers ${LIBRARY} ${SRCS} > Version.c
	${CC} -c Version.c -o Version
	@rm -f profiled/Version
	ln Version profiled/Version
E 8

E 11
D 8
LIBRARY_P     = libU77_p.a
E 8
I 8
mkvers: mkvers.c
D 11
	${CC} mkvers.c -o $@
E 11
I 11
	${CC} ${CFLAGS} ${.CURDIR}/mkvers.c -o ${.TARGET}
E 11
E 8

D 8
MAKEFILE      = Makefile
E 8
I 8
D 10
clean: FRC
E 10
I 10
D 11
clean:
E 10
D 9
	rm -f ${OBJS} profiled/*.o core ${LIBRARY} ${LIBRARY_P}
E 9
I 9
	rm -f ${OBJS} mkvers profiled/*.o core ${LIBRARY} ${LIBRARY_P}
E 11
I 11
.include <bsd.lib.mk>
E 11
E 9
E 8

D 8
OBJS	      = access_.o \
		alarm_.o \
		chdir_.o \
		chmod_.o \
		ctime_.o \
		dtime_.o \
		etime_.o \
		f77lid_.o \
		fdate_.o \
		fgetc_.o \
		fork_.o \
		fputc_.o \
		fseek_.o \
		fstat_.o \
		ftell_.o \
		gerror_.o \
		getarg_.o \
		getc_.o \
		getcwd_.o \
		getenv_.o \
		getgid_.o \
		getlog_.o \
		getpid_.o \
		getuid_.o \
		gmtime_.o \
		hostnm_.o \
		iargc_.o \
		idate_.o \
		ierrno_.o \
I 2
		ioinit.o \
E 2
		isatty_.o \
		itime_.o \
		kill_.o \
		link_.o \
		loc_.o \
		lstat_.o \
		ltime_.o \
I 4
		malloc_.o \
E 4
		perror_.o \
		putc_.o \
		qsort_.o \
		rename_.o \
D 5
		signal_.o \
E 5
		sleep_.o \
		stat_.o \
		symlnk_.o \
		system_.o \
		tapeio.o \
		time_.o \
		ttynam_.o \
		unlink_.o \
		wait_.o
E 8
I 8
D 10
depend: FRC
E 10
I 10
D 11
cleandir: clean
	rm -f ${MAN} tags .depend
E 11
I 11
D 12
.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 11

D 11
depend: ${SRCS}
E 10
	mkdep ${CFLAGS} ${SRCS}
E 11
I 11
.c.po:
	${CC} -p ${CFLAGS} -c ${.IMPSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 11
E 8

D 8
OLDDIR	      = $(DESTDIR)/usr/old/lib
E 8
I 8
D 10
install: FRC
E 10
I 10
D 11
install: ${MAN}
E 10
	install -o bin -g bin -m 644 ${LIBRARY} ${DEST}/${LIBRARY}
D 10
	ranlib ${DEST}/${LIBRARY}
E 10
I 10
	ranlib -t ${DEST}/${LIBRARY}
E 10
	install -o bin -g bin -m 644 ${LIBRARY_P} ${DEST}/${LIBRARY_P}
D 10
	ranlib ${DEST}/${LIBRARY_P}
E 10
I 10
	ranlib -t ${DEST}/${LIBRARY_P}
E 11
I 11
# Fortran compiler doesn't let you rename .o's, so we'll have to
# rebuild the .o's each time.
E 12
I 12
# Fortran compiler doesn't let you rename .o's, so we'll have to cheat.
E 12
.f.o:
D 12
	${FC} ${FFLAGS} -c ${.IMPSRC}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 12
I 12
	${FC} -p ${FFLAGS} -c ${.IMPSRC}
D 13
	${LD} -X -r ${.TARGET:S/.po/.o/}
	mv a.out ${.TARGET}
E 13
I 13
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 13
E 12
E 11
E 10
E 8

D 8
PRINT	      = pr
E 8
I 8
D 10
lint: FRC
E 10
I 10
D 11
lint: ${SRCS}
E 10
	lint ${CFLAGS} ${SRCS}
E 8

D 8
SRCS	      = access_.c \
		alarm_.c \
		chdir_.c \
		chmod_.c \
		ctime_.c \
		dtime_.c \
		etime_.c \
		f77lid_.c \
		fdate_.c \
		fgetc_.c \
		fork_.c \
		fputc_.c \
		fseek_.c \
		fstat_.c \
		ftell_.c \
		gerror_.c \
		getarg_.c \
		getc_.c \
		getcwd_.c \
		getenv_.c \
		getgid_.c \
		getlog_.c \
		getpid_.c \
		getuid_.c \
		gmtime_.c \
		hostnm_.c \
		iargc_.c \
		idate_.c \
		ierrno_.c \
I 2
		ioinit.f \
E 2
		isatty_.c \
		itime_.c \
		kill_.c \
		link_.c \
		loc_.c \
		lstat_.c \
		ltime_.c \
I 4
		malloc_.c \
E 4
		perror_.c \
		putc_.c \
		qsort_.c \
		rename_.c \
D 5
		signal_.c \
E 5
		sleep_.c \
		stat_.c \
		symlnk_.c \
		system_.c \
		tapeio.c \
		time_.c \
		ttynam_.c \
		unlink_.c \
		wait_.c
E 8
I 8
D 10
tags: FRC
E 10
I 10
tags: ${SRCS}
E 10
	ctags ${SRCS}
E 8

D 8
all:		$(LIBRARY) $(LIBRARY_P)
E 8
I 8
extract: FRC
	@ar xo ${DEST}/${LIBRARY}; rm -f __.SYMDEF
	@cd profiled; -ar xo ${DEST}/${LIBRARY_P}; rm -f __.SYMDEF
E 8

D 8
$(LIBRARY):	$(OBJS) Version
		@echo -n "Loading $(LIBRARY) ... "
D 3
		@ar cru $(LIBRARY) $(OBJS) Version
E 3
I 3
		@ar cru $(LIBRARY) $(OBJS) ioinit.f Version
E 3
		@ranlib $(LIBRARY)
		@echo "done"
E 8
I 8
update ${DEST}/${LIBRARY}: FRC
	@-ar xo ${DEST}/${LIBRARY}
	@cd profiled; -ar xo ${DEST}/${LIBRARY_P}
	@make DEST=${DEST} all install clean
E 8

D 8
$(LIBRARY_P):	$(OBJS) Version
		@echo -n "Loading $(LIBRARY_P) ... "
		@cd profiled; ar cru ../$(LIBRARY_P) $(OBJS) Version
		@ranlib $(LIBRARY_P)
		@echo "done"
E 8
I 8
FRC:
E 11
I 11
.f.po:
D 12
	${FC} -p ${FFLAGS} -c ${.IMPSRC}
	@${LD} -x -r ${.TARGET:S/.po/.o/}
	@mv a.out ${.TARGET}
E 12
I 12
	ln -s ${.IMPSRC} xxx.f
	${FC} -p ${FFLAGS} -c xxx.f
D 13
	${LD} -X -r xxx.o
	mv a.out ${.TARGET}
	rm -f xxx.f xxx.o
E 13
I 13
	@${LD} -X -r xxx.o
	@mv a.out ${.TARGET}
	@rm -f xxx.f xxx.o
E 13
E 12
E 11
E 8
D 10

D 8
Version:	$(SRCS) mkvers
		@rm -f Version.c
		./mkvers $(LIBRARY) $(SRCS) > Version.c
		$(CC) -c Version.c
		mv Version.o Version
		@rm -f profiled/Version
		ln Version profiled/Version
E 8
I 8
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 8

D 8
mkvers:		mkvers.c
		@$(CC) mkvers.c -o mkvers
E 8
I 8
access_.o: access_.c ../libI77/f_errno.h /usr/include/errno.h
access_.o: /usr/include/sys/param.h /usr/include/sys/types.h
access_.o: /usr/include/signal.h /usr/include/machine/machparam.h
alarm_.o: alarm_.c /usr/include/signal.h
chdir_.o: chdir_.c ../libI77/f_errno.h /usr/include/errno.h
chdir_.o: /usr/include/sys/param.h /usr/include/sys/types.h
chdir_.o: /usr/include/signal.h /usr/include/machine/machparam.h
chmod_.o: chmod_.c ../libI77/f_errno.h /usr/include/errno.h
chmod_.o: /usr/include/sys/param.h /usr/include/sys/types.h
chmod_.o: /usr/include/signal.h /usr/include/machine/machparam.h
ctime_.o: ctime_.c
dtime_.o: dtime_.c /usr/include/sys/types.h /usr/include/sys/times.h
etime_.o: etime_.c /usr/include/sys/types.h /usr/include/sys/times.h
f77lid_.o: f77lid_.c
fdate_.o: fdate_.c
fgetc_.o: fgetc_.c ../libI77/fiodefs.h /usr/include/stdio.h ../libI77/f_errno.h
fgetc_.o: /usr/include/errno.h ../libI77/f_errno.h /usr/include/errno.h
fork_.o: fork_.c ../libI77/fiodefs.h /usr/include/stdio.h ../libI77/f_errno.h
fork_.o: /usr/include/errno.h
fputc_.o: fputc_.c ../libI77/fiodefs.h /usr/include/stdio.h ../libI77/f_errno.h
fputc_.o: /usr/include/errno.h ../libI77/f_errno.h /usr/include/errno.h
fseek_.o: fseek_.c /usr/include/stdio.h ../libI77/f_errno.h
fseek_.o: /usr/include/errno.h ../libI77/fiodefs.h /usr/include/stdio.h
fseek_.o: ../libI77/f_errno.h /usr/include/errno.h
fstat_.o: fstat_.c /usr/include/sys/types.h /usr/include/sys/stat.h
fstat_.o: ../libI77/f_errno.h /usr/include/errno.h ../libI77/fiodefs.h
fstat_.o: /usr/include/stdio.h ../libI77/f_errno.h /usr/include/errno.h
ftell_.o: ftell_.c ../libI77/fiodefs.h /usr/include/stdio.h ../libI77/f_errno.h
ftell_.o: /usr/include/errno.h ../libI77/f_errno.h /usr/include/errno.h
gerror_.o: gerror_.c /usr/include/stdio.h ../libI77/f_errno.h
gerror_.o: /usr/include/errno.h
getarg_.o: getarg_.c
getc_.o: getc_.c ../libI77/f_errno.h /usr/include/errno.h ../libI77/fiodefs.h
getc_.o: /usr/include/stdio.h ../libI77/f_errno.h /usr/include/errno.h
getcwd_.o: getcwd_.c /usr/include/sys/param.h /usr/include/sys/types.h
getcwd_.o: /usr/include/signal.h /usr/include/machine/machparam.h
getenv_.o: getenv_.c
getgid_.o: getgid_.c
getlog_.o: getlog_.c
getpid_.o: getpid_.c
getuid_.o: getuid_.c
gmtime_.o: gmtime_.c
hostnm_.o: hostnm_.c
iargc_.o: iargc_.c
idate_.o: idate_.c /usr/include/sys/types.h /usr/include/sys/time.h
idate_.o: /usr/include/time.h
ierrno_.o: ierrno_.c
ioinit.o: ioinit.f
isatty_.o: isatty_.c ../libI77/fiodefs.h /usr/include/stdio.h
isatty_.o: ../libI77/f_errno.h /usr/include/errno.h
itime_.o: itime_.c /usr/include/sys/types.h /usr/include/sys/time.h
itime_.o: /usr/include/time.h
kill_.o: kill_.c ../libI77/f_errno.h /usr/include/errno.h
link_.o: link_.c ../libI77/f_errno.h /usr/include/errno.h
link_.o: /usr/include/sys/param.h /usr/include/sys/types.h
link_.o: /usr/include/signal.h /usr/include/machine/machparam.h
loc_.o: loc_.c
lstat_.o: lstat_.c /usr/include/sys/param.h /usr/include/sys/types.h
lstat_.o: /usr/include/signal.h /usr/include/machine/machparam.h
lstat_.o: /usr/include/sys/stat.h ../libI77/f_errno.h /usr/include/errno.h
ltime_.o: ltime_.c
malloc_.o: malloc_.c
perror_.o: perror_.c /usr/include/stdio.h ../libI77/fiodefs.h
perror_.o: /usr/include/stdio.h ../libI77/f_errno.h /usr/include/errno.h
perror_.o: ../libI77/f_errno.h /usr/include/errno.h
putc_.o: putc_.c ../libI77/f_errno.h /usr/include/errno.h ../libI77/fiodefs.h
putc_.o: /usr/include/stdio.h ../libI77/f_errno.h /usr/include/errno.h
qsort_.o: qsort_.c
rename_.o: rename_.c ../libI77/f_errno.h /usr/include/errno.h
rename_.o: /usr/include/sys/param.h /usr/include/sys/types.h
rename_.o: /usr/include/signal.h /usr/include/machine/machparam.h
sleep_.o: sleep_.c
stat_.o: stat_.c /usr/include/sys/param.h /usr/include/sys/types.h
stat_.o: /usr/include/signal.h /usr/include/machine/machparam.h
stat_.o: /usr/include/sys/stat.h ../libI77/f_errno.h /usr/include/errno.h
symlnk_.o: symlnk_.c /usr/include/sys/param.h /usr/include/sys/types.h
symlnk_.o: /usr/include/signal.h /usr/include/machine/machparam.h
symlnk_.o: ../libI77/f_errno.h /usr/include/errno.h
system_.o: system_.c ../libI77/fiodefs.h /usr/include/stdio.h
system_.o: ../libI77/f_errno.h /usr/include/errno.h ../libI77/f_errno.h
system_.o: /usr/include/errno.h /usr/include/sys/param.h
system_.o: /usr/include/sys/types.h /usr/include/signal.h
system_.o: /usr/include/machine/machparam.h /usr/include/signal.h
tapeio.o: tapeio.c /usr/include/ctype.h /usr/include/sys/ioctl.h
tapeio.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
tapeio.o: /usr/include/sys/types.h /usr/include/sys/mtio.h ../libI77/f_errno.h
tapeio.o: /usr/include/errno.h
time_.o: time_.c
ttynam_.o: ttynam_.c ../libI77/fiodefs.h /usr/include/stdio.h
ttynam_.o: ../libI77/f_errno.h /usr/include/errno.h
unlink_.o: unlink_.c ../libI77/f_errno.h /usr/include/errno.h
unlink_.o: /usr/include/sys/param.h /usr/include/sys/types.h
unlink_.o: /usr/include/signal.h /usr/include/machine/machparam.h
wait_.o: wait_.c
E 8

D 8
clean:;		@rm -f $(OBJS) profiled/*.o $(LIBRARY) $(LIBRARY_P)

depend:;	@echo Construct dependencies manually

extract:;	@ar xo $(DEST)/$(LIBRARY); rm -f __.SYMDEF
		@cd profiled; -ar xo $(DEST)/$(LIBRARY_P); rm -f __.SYMDEF

index:;		@ctags -wx $(HDRS) $(SRCS)

install:	$(LIBRARY) $(LIBRARY_P)
D 2
		@-mv $(DEST)/$(LIBRARY) $(OLDDIR)/$(LIBRARY)
E 2
		install -m 644 $(LIBRARY) $(DEST)/$(LIBRARY)
		ranlib $(DEST)/$(LIBRARY)
D 2
		@-mv $(DEST)/$(LIBRARY_P) $(OLDDIR)/$(LIBRARY_P)
E 2
		install -m 644 $(LIBRARY_P) $(DEST)/$(LIBRARY_P)
		ranlib $(DEST)/$(LIBRARY_P)

library:        $(LIBRARY) $(LIBRARY_P)

print:;		@$(PRINT) $(HDRS) $(SRCS)

tags:           $(HDRS) $(SRCS); @ctags $(HDRS) $(SRCS)

update:         $(DEST)/$(LIBRARY)

$(DEST)/$(LIBRARY): $(SRCS) $(HDRS) $(EXTHDRS)
		@-ar xo $(DEST)/$(LIBRARY)
		@cd profiled; -ar xo $(DEST)/$(LIBRARY_P)
		@make -f $(MAKEFILE) DEST=$(DEST) install clean
.c.o:
		$(CC) -p $(CFLAGS) -c $*.c
		-ld -x -r $*.o
		mv a.out profiled/$*.o
		$(CC) $(CFLAGS) -c $*.c
I 2
		-ld -x -r $*.o
		mv a.out $*.o

.f.o:
		$(FC) -p $(FFLAGS) -c $*.f
		-ld -x -r $*.o
		mv a.out profiled/$*.o
		$(FC) $(FFLAGS) -c $*.f
E 2
		-ld -x -r $*.o
		mv a.out $*.o
E 8
I 8
# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 10
E 8
E 1
