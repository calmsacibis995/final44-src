h28282
s 00000/00000/00050
d D 8.1 93/06/05 13:26:49 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00039/00081/00011
d D 5.5 90/05/11 13:56:04 bostic 5 4
c first pass for new make
e
s 00002/00002/00090
d D 5.4 90/05/10 16:19:58 bostic 4 3
c checkpoint for pmake
e
s 00064/00087/00028
d D 5.3 89/03/06 11:43:33 bostic 3 2
c move man pages into source tree
e
s 00010/00005/00105
d D 5.2 88/07/09 11:25:32 bostic 2 1
c install approved copyright notice
e
s 00110/00000/00000
d D 5.1 87/12/12 18:28:39 bostic 1 0
c date and time created 87/12/12 18:28:39 by bostic
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 3
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
E 2
#
E 5
#	%W% (Berkeley) %G%
D 5
#
D 3
MDIR=	/usr/man/cat3f
SRCS=	abort.3 access.3 alarm.3 bessel.3 bit.3 chdir.3 chmod.3 etime.3 \
	exit.3 fdate.3 flmin.3 flush.3 fork.3 fseek.3 getarg.3 getc.3 \
	getcwd.3 getenv.3 getlog.3 getpid.3 getuid.0 getuid.3 hostnm.3 \
	idate.3 index.3 intro.3 ioinit.3 kill.3 link.3 loc.3 long.3 \
	malloc.3 perror.3 plot.3 putc.3 qsort.3 rand.3 random.3 rename.3 \
	signal.3 sleep.3 stat.3 system.3 time.3 topen.3 traper.3 trapov.3 \
	trpfpe.3 ttynam.3 unlink.3 wait.3
E 3
I 3
D 4
MDIR=	${DESTDIR}/usr/man/cat3f
E 4
I 4
MDIR=	${DESTDIR}/usr/share/man/cat3f
E 4
E 3
OBJS=	abort.0 access.0 alarm.0 bessel.0 bit.0 chdir.0 chmod.0 etime.0 \
E 5
I 5

MAN3F=	abort.0 access.0 alarm.0 bessel.0 bit.0 chdir.0 chmod.0 etime.0 \
E 5
	exit.0 fdate.0 flmin.0 flush.0 fork.0 fseek.0 getarg.0 getc.0 \
	getcwd.0 getenv.0 getlog.0 getpid.0 getuid.0 getuid.0 hostnm.0 \
	idate.0 index.0 intro.0 ioinit.0 kill.0 link.0 loc.0 long.0 \
	malloc.0 perror.0 plot.0 putc.0 qsort.0 rand.0 random.0 rename.0 \
	signal.0 sleep.0 stat.0 system.0 time.0 topen.0 traper.0 trapov.0 \
	trpfpe.0 ttynam.0 unlink.0 wait.0
I 5
MLINKS=	bessel.3f besj0.3f bessel.3f besj1.3f bessel.3f besjn.3f bessel.3f \
	besy0.3f bessel.3f besy1.3f bessel.3f besyn.3f bessel.3f dbesj0.3f \
	bessel.3f dbesj1.3f bessel.3f dbesjn.3f bessel.3f dbesy0.3f bessel.3f \
	dbesy1.3f bessel.3f dbesyn.3f
MLINKS+=etime.3f dtime.3f
MLINKS+=flmin.3f dffrac.3f flmin.3f dflmax.3f flmin.3f dflmin.3f flmin.3f \
	ffrac.3f flmin.3f flmax.3f flmin.3f inmax.3f
MLINKS+=fseek.3f ftell.3f
MLINKS+=getarg.3f iargc.3f
MLINKS+=getc.3f fgetc.3f
MLINKS+=getuid.3f getgid.3f
MLINKS+=idate.3f itime.3f
MLINKS+=index.3f len.3f index.3f lnblnk.3f index.3f rindex.3f
MLINKS+=intro.3f fortran.3f
MLINKS+=link.3f symlnk.3f
MLINKS+=long.3f short.3f
MLINKS+=malloc.3f falloc.3f
MLINKS+=perror.3f gerror.3f perror.3f ierrno.3f
MLINKS+=plot.3f box.3f
MLINKS+=putc.3f fputc.3f
MLINKS+=rand.3f drand.3f rand.3f irand.3f
MLINKS+=random.3f drandm.3f random.3f irandm.3f
MLINKS+=stat.3f fstat.3f stat.3f lstat.3f
MLINKS+=time.3f ctime.3f time.3f gmtime.3f time.3f ltime.3f
MLINKS+=topen.3f tclose.3f topen.3f tread.3f topen.3f trewin.3f topen.3f \
	tskipf.3f topen.3f tstate.3f topen.3f twrite.3f
MLINKS+=trpfpe.3f fpecnt.3f
MLINKS+=ttynam.3f isatty.3f
MLINKS+=bit.3f and.3f bit.3f lshift.3f bit.3f not.3f bit.3f or.3f bit.3f \
	rshift.3f bit.3f xor.3f
E 5
D 3
LINKS=	and.0 lshift.0 not.0 or.0 rshift.0 xor.0 box.0 ctime.0 drand.0 \
	fgetc.0 fputc.0 fstat.0 gmtime.0 irand.0 lstat.0 ltime.0 short.0 \
	symlnk.0 dffrac.0 dflmax.0 dflmin.0 dtime.0 ffrac.0 flmax.0 \
	fortran.0 ftell.0 inmax.0 itime.0 len.0 lnblnk.0 rindex.0 tclose.0 \
	tread.0 trewin.0 tskipf.0 tstate.0 twrite.0 drandm.0 falloc.0 \
	fpecnt.0 gerror.0 getgid.0 iargc.0 ierrno.0 irandm.0 isatty.0 \
	besj0.0 besj1.0 besjn.0 besy0.0 besy1.0 besyn.0 dbesj0.0 dbesj1.0 \
	dbesjn.0 dbesy0.0 dbesy1.0 dbesyn.0
E 3

D 3
.SUFFIXES: .3 .0
E 3
I 3
D 4
all clean depent lint tags:
E 4
I 4
D 5
all clean depend lint tags:
E 5
I 5
all: ${MAN3F}
E 5
E 4
E 3

I 5
clean depend lint tags:

E 5
D 3
.3.0:
	${DESTDIR}/usr/man/manroff $*.3 > $*.0

all: ${OBJS}

clean: FRC
E 3
I 3
cleandir:
E 3
D 5
	rm -f ${OBJS}
E 5
I 5
	rm -f ${MAN3F}
E 5

D 3
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/bit.0 ${DESTDIR}${MDIR}/and.0
	ln ${DESTDIR}${MDIR}/bit.0 ${DESTDIR}${MDIR}/lshift.0
	ln ${DESTDIR}${MDIR}/bit.0 ${DESTDIR}${MDIR}/not.0
	ln ${DESTDIR}${MDIR}/bit.0 ${DESTDIR}${MDIR}/or.0
	ln ${DESTDIR}${MDIR}/bit.0 ${DESTDIR}${MDIR}/rshift.0
	ln ${DESTDIR}${MDIR}/bit.0 ${DESTDIR}${MDIR}/xor.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/box.0
	ln ${DESTDIR}${MDIR}/time.0 ${DESTDIR}${MDIR}/ctime.0
	ln ${DESTDIR}${MDIR}/rand.0 ${DESTDIR}${MDIR}/drand.0
	ln ${DESTDIR}${MDIR}/getc.0 ${DESTDIR}${MDIR}/fgetc.0
	ln ${DESTDIR}${MDIR}/putc.0 ${DESTDIR}${MDIR}/fputc.0
	ln ${DESTDIR}${MDIR}/stat.0 ${DESTDIR}${MDIR}/fstat.0
	ln ${DESTDIR}${MDIR}/time.0 ${DESTDIR}${MDIR}/gmtime.0
	ln ${DESTDIR}${MDIR}/rand.0 ${DESTDIR}${MDIR}/irand.0
	ln ${DESTDIR}${MDIR}/stat.0 ${DESTDIR}${MDIR}/lstat.0
	ln ${DESTDIR}${MDIR}/time.0 ${DESTDIR}${MDIR}/ltime.0
	ln ${DESTDIR}${MDIR}/long.0 ${DESTDIR}${MDIR}/short.0
	ln ${DESTDIR}${MDIR}/link.0 ${DESTDIR}${MDIR}/symlnk.0
	ln ${DESTDIR}${MDIR}/flmin.0 ${DESTDIR}${MDIR}/dffrac.0
	ln ${DESTDIR}${MDIR}/flmin.0 ${DESTDIR}${MDIR}/dflmax.0
	ln ${DESTDIR}${MDIR}/flmin.0 ${DESTDIR}${MDIR}/dflmin.0
	ln ${DESTDIR}${MDIR}/etime.0 ${DESTDIR}${MDIR}/dtime.0
	ln ${DESTDIR}${MDIR}/flmin.0 ${DESTDIR}${MDIR}/ffrac.0
	ln ${DESTDIR}${MDIR}/flmin.0 ${DESTDIR}${MDIR}/flmax.0
	ln ${DESTDIR}${MDIR}/intro.0 ${DESTDIR}${MDIR}/fortran.0
	ln ${DESTDIR}${MDIR}/fseek.0 ${DESTDIR}${MDIR}/ftell.0
	ln ${DESTDIR}${MDIR}/flmin.0 ${DESTDIR}${MDIR}/inmax.0
	ln ${DESTDIR}${MDIR}/idate.0 ${DESTDIR}${MDIR}/itime.0
	ln ${DESTDIR}${MDIR}/index.0 ${DESTDIR}${MDIR}/len.0
	ln ${DESTDIR}${MDIR}/index.0 ${DESTDIR}${MDIR}/lnblnk.0
	ln ${DESTDIR}${MDIR}/index.0 ${DESTDIR}${MDIR}/rindex.0
	ln ${DESTDIR}${MDIR}/topen.0 ${DESTDIR}${MDIR}/tclose.0
	ln ${DESTDIR}${MDIR}/topen.0 ${DESTDIR}${MDIR}/tread.0
	ln ${DESTDIR}${MDIR}/topen.0 ${DESTDIR}${MDIR}/trewin.0
	ln ${DESTDIR}${MDIR}/topen.0 ${DESTDIR}${MDIR}/tskipf.0
	ln ${DESTDIR}${MDIR}/topen.0 ${DESTDIR}${MDIR}/tstate.0
	ln ${DESTDIR}${MDIR}/topen.0 ${DESTDIR}${MDIR}/twrite.0
	ln ${DESTDIR}${MDIR}/random.0 ${DESTDIR}${MDIR}/drandm.0
	ln ${DESTDIR}${MDIR}/malloc.0 ${DESTDIR}${MDIR}/falloc.0
	ln ${DESTDIR}${MDIR}/trpfpe.0 ${DESTDIR}${MDIR}/fpecnt.0
	ln ${DESTDIR}${MDIR}/perror.0 ${DESTDIR}${MDIR}/gerror.0
	ln ${DESTDIR}${MDIR}/getuid.0 ${DESTDIR}${MDIR}/getgid.0
	ln ${DESTDIR}${MDIR}/getarg.0 ${DESTDIR}${MDIR}/iargc.0
	ln ${DESTDIR}${MDIR}/perror.0 ${DESTDIR}${MDIR}/ierrno.0
	ln ${DESTDIR}${MDIR}/random.0 ${DESTDIR}${MDIR}/irandm.0
	ln ${DESTDIR}${MDIR}/ttynam.0 ${DESTDIR}${MDIR}/isatty.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/besj0.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/besj1.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/besjn.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/besy0.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/besy1.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/besyn.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/dbesj0.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/dbesj1.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/dbesjn.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/dbesy0.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/dbesy1.0
	ln ${DESTDIR}${MDIR}/bessel.0 ${DESTDIR}${MDIR}/dbesyn.0

FRC:
E 3
I 3
D 5
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/and.0; ln ${MDIR}/bit.0 ${MDIR}/and.0
	rm -f ${MDIR}/lshift.0; ln ${MDIR}/bit.0 ${MDIR}/lshift.0
	rm -f ${MDIR}/not.0; ln ${MDIR}/bit.0 ${MDIR}/not.0
	rm -f ${MDIR}/or.0; ln ${MDIR}/bit.0 ${MDIR}/or.0
	rm -f ${MDIR}/rshift.0; ln ${MDIR}/bit.0 ${MDIR}/rshift.0
	rm -f ${MDIR}/xor.0; ln ${MDIR}/bit.0 ${MDIR}/xor.0
	rm -f ${MDIR}/box.0; ln ${MDIR}/plot.0 ${MDIR}/box.0
	rm -f ${MDIR}/ctime.0; ln ${MDIR}/time.0 ${MDIR}/ctime.0
	rm -f ${MDIR}/drand.0; ln ${MDIR}/rand.0 ${MDIR}/drand.0
	rm -f ${MDIR}/fgetc.0; ln ${MDIR}/getc.0 ${MDIR}/fgetc.0
	rm -f ${MDIR}/fputc.0; ln ${MDIR}/putc.0 ${MDIR}/fputc.0
	rm -f ${MDIR}/fstat.0; ln ${MDIR}/stat.0 ${MDIR}/fstat.0
	rm -f ${MDIR}/gmtime.0; ln ${MDIR}/time.0 ${MDIR}/gmtime.0
	rm -f ${MDIR}/irand.0; ln ${MDIR}/rand.0 ${MDIR}/irand.0
	rm -f ${MDIR}/lstat.0; ln ${MDIR}/stat.0 ${MDIR}/lstat.0
	rm -f ${MDIR}/ltime.0; ln ${MDIR}/time.0 ${MDIR}/ltime.0
	rm -f ${MDIR}/short.0; ln ${MDIR}/long.0 ${MDIR}/short.0
	rm -f ${MDIR}/symlnk.0; ln ${MDIR}/link.0 ${MDIR}/symlnk.0
	rm -f ${MDIR}/dffrac.0; ln ${MDIR}/flmin.0 ${MDIR}/dffrac.0
	rm -f ${MDIR}/dflmax.0; ln ${MDIR}/flmin.0 ${MDIR}/dflmax.0
	rm -f ${MDIR}/dflmin.0; ln ${MDIR}/flmin.0 ${MDIR}/dflmin.0
	rm -f ${MDIR}/dtime.0; ln ${MDIR}/etime.0 ${MDIR}/dtime.0
	rm -f ${MDIR}/ffrac.0; ln ${MDIR}/flmin.0 ${MDIR}/ffrac.0
	rm -f ${MDIR}/flmax.0; ln ${MDIR}/flmin.0 ${MDIR}/flmax.0
	rm -f ${MDIR}/fortran.0; ln ${MDIR}/intro.0 ${MDIR}/fortran.0
	rm -f ${MDIR}/ftell.0; ln ${MDIR}/fseek.0 ${MDIR}/ftell.0
	rm -f ${MDIR}/inmax.0; ln ${MDIR}/flmin.0 ${MDIR}/inmax.0
	rm -f ${MDIR}/itime.0; ln ${MDIR}/idate.0 ${MDIR}/itime.0
	rm -f ${MDIR}/len.0; ln ${MDIR}/index.0 ${MDIR}/len.0
	rm -f ${MDIR}/lnblnk.0; ln ${MDIR}/index.0 ${MDIR}/lnblnk.0
	rm -f ${MDIR}/rindex.0; ln ${MDIR}/index.0 ${MDIR}/rindex.0
	rm -f ${MDIR}/tclose.0; ln ${MDIR}/topen.0 ${MDIR}/tclose.0
	rm -f ${MDIR}/tread.0; ln ${MDIR}/topen.0 ${MDIR}/tread.0
	rm -f ${MDIR}/trewin.0; ln ${MDIR}/topen.0 ${MDIR}/trewin.0
	rm -f ${MDIR}/tskipf.0; ln ${MDIR}/topen.0 ${MDIR}/tskipf.0
	rm -f ${MDIR}/tstate.0; ln ${MDIR}/topen.0 ${MDIR}/tstate.0
	rm -f ${MDIR}/twrite.0; ln ${MDIR}/topen.0 ${MDIR}/twrite.0
	rm -f ${MDIR}/drandm.0; ln ${MDIR}/random.0 ${MDIR}/drandm.0
	rm -f ${MDIR}/falloc.0; ln ${MDIR}/malloc.0 ${MDIR}/falloc.0
	rm -f ${MDIR}/fpecnt.0; ln ${MDIR}/trpfpe.0 ${MDIR}/fpecnt.0
	rm -f ${MDIR}/gerror.0; ln ${MDIR}/perror.0 ${MDIR}/gerror.0
	rm -f ${MDIR}/getgid.0; ln ${MDIR}/getuid.0 ${MDIR}/getgid.0
	rm -f ${MDIR}/iargc.0; ln ${MDIR}/getarg.0 ${MDIR}/iargc.0
	rm -f ${MDIR}/ierrno.0; ln ${MDIR}/perror.0 ${MDIR}/ierrno.0
	rm -f ${MDIR}/irandm.0; ln ${MDIR}/random.0 ${MDIR}/irandm.0
	rm -f ${MDIR}/isatty.0; ln ${MDIR}/ttynam.0 ${MDIR}/isatty.0
	rm -f ${MDIR}/besj0.0; ln ${MDIR}/bessel.0 ${MDIR}/besj0.0
	rm -f ${MDIR}/besj1.0; ln ${MDIR}/bessel.0 ${MDIR}/besj1.0
	rm -f ${MDIR}/besjn.0; ln ${MDIR}/bessel.0 ${MDIR}/besjn.0
	rm -f ${MDIR}/besy0.0; ln ${MDIR}/bessel.0 ${MDIR}/besy0.0
	rm -f ${MDIR}/besy1.0; ln ${MDIR}/bessel.0 ${MDIR}/besy1.0
	rm -f ${MDIR}/besyn.0; ln ${MDIR}/bessel.0 ${MDIR}/besyn.0
	rm -f ${MDIR}/dbesj0.0; ln ${MDIR}/bessel.0 ${MDIR}/dbesj0.0
	rm -f ${MDIR}/dbesj1.0; ln ${MDIR}/bessel.0 ${MDIR}/dbesj1.0
	rm -f ${MDIR}/dbesjn.0; ln ${MDIR}/bessel.0 ${MDIR}/dbesjn.0
	rm -f ${MDIR}/dbesy0.0; ln ${MDIR}/bessel.0 ${MDIR}/dbesy0.0
	rm -f ${MDIR}/dbesy1.0; ln ${MDIR}/bessel.0 ${MDIR}/dbesy1.0
	rm -f ${MDIR}/dbesyn.0; ln ${MDIR}/bessel.0 ${MDIR}/dbesyn.0
E 5
I 5
install: maninstall

.include <bsd.prog.mk>
E 5
E 3
E 1
