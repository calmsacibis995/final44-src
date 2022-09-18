h22234
s 00010/00001/00016
d D 8.2 93/12/13 15:02:06 mckusick 22 21
c add queue.3 (and associated functions
e
s 00000/00000/00017
d D 8.1 93/06/05 13:23:02 bostic 21 20
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00016
d D 5.19 93/06/02 17:28:23 bostic 20 19
c move moncontrol into lib/libc/gmon
e
s 00002/00001/00015
d D 5.18 91/06/29 14:47:39 bostic 19 18
c more links for stdarg.3
e
s 00002/00003/00014
d D 5.17 91/05/22 10:59:47 mckusick 18 16
c monitor.3 => moncontrol.3
e
s 00002/00003/00014
d D 5.16.1.1 91/05/07 21:48:49 bostic 17 16
c branch for the 2nd network distribution
e
s 00003/00002/00014
d D 5.16 91/04/24 14:21:57 bostic 16 15
c move varargs.3 to stdarg.3
e
s 00001/00001/00015
d D 5.15 90/06/08 16:06:49 bostic 15 14
c use prog.mk
e
s 00011/00027/00005
d D 5.14 90/05/11 13:56:44 bostic 14 13
c first pass for new make
e
s 00002/00277/00030
d D 5.13 90/05/10 16:17:04 bostic 13 12
c checkpoint for pmake
e
s 00270/00264/00037
d D 5.12 89/03/06 10:54:58 bostic 12 11
c move man pages into source tree
e
s 00008/00033/00293
d D 5.11 88/10/19 13:45:14 bostic 11 10
c cleanup
e
s 00005/00005/00321
d D 5.10 88/08/03 14:57:05 bostic 10 9
c treewalk is real; replace ftw with it
e
s 00001/00000/00325
d D 5.9 88/07/23 16:27:44 bostic 9 8
c add strtol
e
s 00002/00000/00323
d D 5.8 88/07/14 22:37:11 bostic 8 7
c add ftw and strpbrk
e
s 00010/00005/00313
d D 5.7 88/07/09 11:40:12 bostic 7 6
c install approved copyright notice
e
s 00002/00000/00316
d D 5.6 88/06/08 18:08:02 bostic 6 5
c add tempnam(BA_LIB) and tmpfile(BA_LIB)
e
s 00015/00041/00301
d D 5.5 88/06/06 12:11:41 bostic 5 4
c remove LINK; add compat-sys5 man page
e
s 00006/00006/00336
d D 5.4 88/05/19 18:17:10 bostic 4 3
c make regexp separate from regex
e
s 00002/00002/00340
d D 5.3 88/03/13 18:12:20 bostic 3 2
c it's strncasecmp, not strcasencmp
e
s 00001/00000/00341
d D 5.2 87/12/14 11:34:37 bostic 2 1
c link tzset to ctime
e
s 00341/00000/00000
d D 5.1 87/12/12 18:18:20 bostic 1 0
c date and time created 87/12/12 18:18:20 by bostic
e
u
U
f b 
t
T
I 1
D 14
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 7
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 7
I 7
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 12
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
E 7
#
E 14
#	%W% (Berkeley) %G%
D 14
#
D 12
MDIR=	/usr/man/cat3
E 12
I 12
D 13
MDIR=	${DESTDIR}/usr/man/cat3
E 12
D 5
SRCS=	abort.3 abs.3 alarm.3 asinh.3 assert.3 atof.3 \
	bstring.3 byteorder.3 crypt.3 ctime.3 ctype.3 curses.3 dbm.3 \
E 5
I 5
D 11
SRCS=	abort.3 abs.3 alarm.3 asinh.3 assert.3 atof.3 bstring.3 byteorder.3 \
	compat-sys5.3 crypt.3 ctime.3 ctype.3 curses.3 dbm.3 \
E 5
	directory.3 ecvt.3 end.3 erf.3 execl.3 exit.3 exp.3 fclose.3 \
	ferror.3 floor.3 fopen.3 fread.3 frexp.3 fseek.3 getc.3 \
	getdiskbyname.3 getenv.3 getfsent.3 getgrent.3 gethostbyname.3 \
	getlogin.3 getnetent.3 getopt.3 getpass.3 getprotoent.3 getpw.3 \
	getpwent.3 gets.3 getservent.3 getttyent.3 getusershell.3 getwd.3 \
	hypot.3 ieee.3 inet.3 infnan.3 initgroups.3 insque.3 intro.3 \
	j0.3 lgamma.3 lib2648.3 malloc.3 math.3 mktemp.3 monitor.3 \
	mp.3 ndbm.3 nice.3 nlist.3 ns.3 pause.3 perror.3 plot.3 popen.3 \
	printf.3 psignal.3 putc.3 puts.3 qsort.3 rand.3 random.3 rcmd.3 \
D 4
	regex.3 resolver.3 rexec.3 scandir.3 scanf.3 setbuf.3 \
E 4
I 4
	regex.3 regexp.3 resolver.3 rexec.3 scandir.3 scanf.3 setbuf.3 \
E 4
	setjmp.3 \
	setuid.3 siginterrupt.3 signal.3 sin.3 sinh.3 sleep.3 sqrt.3 \
	stdio.3 string.3 stty.3 swab.3 syslog.3 system.3 termcap.3 time.3 \
D 10
	times.3 ttyname.3 ualarm.3 ungetc.3 usleep.3 utime.3 valloc.3 \
	varargs.3 vlimit.3 vtimes.3
E 10
I 10
	times.3 treewalk.3 ttyname.3 ualarm.3 ungetc.3 usleep.3 utime.3 \
	valloc.3 varargs.3 vlimit.3 vtimes.3
E 11
E 10
D 5
OBJS=	abort.0 abs.0 alarm.0 asinh.0 assert.0 atof.0 \
	bstring.0 byteorder.0 crypt.0 ctime.0 ctype.0 curses.0 dbm.0 \
E 5
I 5
OBJS=	abort.0 abs.0 alarm.0 asinh.0 assert.0 atof.0 bstring.0 byteorder.0 \
	compat-sys5.0 crypt.0 ctime.0 ctype.0 curses.0 dbm.0 \
E 5
	directory.0 ecvt.0 end.0 erf.0 execl.0 exit.0 exp.0 fclose.0 \
	ferror.0 floor.0 fopen.0 fread.0 frexp.0 fseek.0 getc.0 \
	getdiskbyname.0 getenv.0 getfsent.0 getgrent.0 gethostbyname.0 \
	getlogin.0 getnetent.0 getopt.0 getpass.0 getprotoent.0 getpw.0 \
	getpwent.0 gets.0 getservent.0 getttyent.0 getusershell.0 getwd.0 \
	hypot.0 ieee.0 inet.0 infnan.0 initgroups.0 insque.0 intro.0 \
	j0.0 lgamma.0 lib2648.0 malloc.0 math.0 mktemp.0 monitor.0 \
	mp.0 ndbm.0 nice.0 nlist.0 ns.0 pause.0 perror.0 plot.0 popen.0 \
	printf.0 psignal.0 putc.0 puts.0 qsort.0 rand.0 random.0 rcmd.0 \
D 4
	regex.0 resolver.0 rexec.0 scandir.0 scanf.0 setbuf.0 \
E 4
I 4
	regex.0 regexp.0 resolver.0 rexec.0 scandir.0 scanf.0 setbuf.0 \
E 4
D 11
	setjmp.0 \
	setuid.0 siginterrupt.0 signal.0 sin.0 sinh.0 sleep.0 sqrt.0 \
	stdio.0 string.0 stty.0 swab.0 syslog.0 system.0 termcap.0 time.0 \
D 10
	times.0 ttyname.0 ualarm.0 ungetc.0 usleep.0 utime.0 valloc.0 \
	varargs.0 vlimit.0 vtimes.0
E 10
I 10
	times.0 treewalk.0 ttyname.0 ualarm.0 ungetc.0 usleep.0 utime.0 \
	valloc.0 varargs.0 vlimit.0 vtimes.0
E 11
I 11
	setjmp.0 setuid.0 siginterrupt.0 signal.0 sin.0 sinh.0 sleep.0 \
D 12
	sqrt.0 stdio.0 string.0 stty.0 swab.0 syslog.0 system.0 termcap.0 \
E 12
I 12
	sqrt.0 stdio.0 string.0 strtok.0 stty.0 swab.0 syslog.0 system.0 \
	termcap.0 \
E 12
	time.0 times.0 treewalk.0 ttyname.0 ualarm.0 ungetc.0 usleep.0 \
	utime.0 valloc.0 varargs.0 vlimit.0 vtimes.0
E 13
I 13
MDIR=	${DESTDIR}/usr/share/man/cat3
OBJS=	assert.0 bitstring.0 end.0 intro.0 monitor.0 varargs.0
E 14
E 13
E 11
E 10
D 5
LINKS=	edata.0 etext.0 j1.0 jn.0 y0.0 y1.0 yn.0 acos.0 ns_addr.0 ns_ntoa.0 \
	asin.0 atan.0 atan2.0 atoi.0 atol.0 cos.0 dbm_clearerr.0 dbm_close.0 \
	dbm_delete.0 dbm_error.0 dbm_fetch.0 dbm_firstkey.0 dbm_nextkey.0 \
	dbm_open.0 dbm_store.0 dbminit.0 delete.0 erfc.0 expm1.0 fcvt.0 \
	fetch.0 firstkey.0 gcvt.0 log.0 log10.0 log1p.0 nextkey.0 pow.0 \
	rresvport.0 ruserok.0 store.0 tan.0 exec.0 addr.0 arc.0 asctime.0 \
	cbrt.0 circle.0 comp.0 cont.0 copysign.0 cosh.0 drem.0 encrypt.0 \
	erase.0 execle.0 execlp.0 exect.0 execv.0 execve.0 execvp.0 fgetc.0 \
	fgets.0 finite.0 fputc.0 fputs.0 ftime.0 getchar.0 getw.0 gmtime.0 \
	gtty.0 inet_addr.0 inet_lnaof.0 inet_makeaddr.0 inet_netof.0 \
	inet_network.0 inet_ntoa.0 isalnum.0 isalpha.0 isascii.0 iscntrl.0 \
	isdigit.0 islower.0 isprint.0 ispunct.0 isspace.0 isupper.0 \
	isxdigit.0 label.0 ldexp.0 line.0 linemod.0 localtime.0 logb.0 \
	modf.0 move.0 network.0 ntoa.0 openpl.0 pclose.0 point.0 putchar.0 \
	putw.0 re_comp.0 re_exec.0 scalb.0 setkey.0 space.0 srand.0 tanh.0 \
	timezone.0 toascii.0 tolower.0 toupper.0 _longjmp.0 _setjmp.0 acosh.0 \
	alloca.0 atanh.0 cabs.0 calloc.0 ceil.0 closelog.0 errlist.0 fabs.0 \
	fdopen.0 free.0 freopen.0 fscanf.0 ftell.0 fwrite.0 index.0 \
	initstate.0 longjmp.0 openlog.0 realloc.0 remque.0 rewind.0 \
	rindex.0 setegid.0 seteuid.0 setgid.0 setlogmask.0 setrgid.0 \
D 3
	setruid.0 setstate.0 srandom.0 sscanf.0 strcasecmp.0 strcasencmp.0 \
E 3
I 3
	setruid.0 setstate.0 srandom.0 sscanf.0 strcasecmp.0 strncasecmp.0 \
E 3
	strcat.0 strcmp.0 strcpy.0 \
	strlen.0 strncat.0 strncmp.0 strncpy.0 sys.0 sys_errlist.0 sys_nerr.0 \
	mkstemp.0 rint.0 setenv.0 unsetenv.0 alphasort.0 bcmp.0 bcopy.0 \
	bzero.0 clearerr.0 feof.0 fflush.0 ffs.0 fileno.0 fprintf.0 isatty.0 \
	moncontrol.0 monstartup.0 setbuffer.0 setlinebuf.0 sprintf.0 \
	sys_siglist.0 ttyslot.0 gamma.0 endfsent.0 endgrent.0 endpwent.0 \
	getfsfile.0 getfsspec.0 getfstype.0 getgrgid.0 getgrnam.0 getpwnam.0 \
	getpwuid.0 setfsent.0 setgrent.0 setgrfile.0 setpwent.0 setpwfile.0 \
	tgetent.0 \
	tgetflag.0 tgetnum.0 tgetstr.0 tgoto.0 tputs.0 closedir.0 endttyent.0 \
	getttynam.0 opendir.0 readdir.0 rewinddir.0 seekdir.0 setttyent.0 \
	telldir.0 endnetent.0 getnetbyaddr.0 getnetbyname.0 htonl.0 htons.0 \
	ntohl.0 ntohs.0 setnetent.0 endservent.0 getservbyname.0 \
	getservbyport.0 setservent.0 endprotoent.0 endusershell.0 \
	g getprotobyname.0 getprotobynumber.0 setprotoent.0 setusershell.0 \
	endhostent.0 gethostbyaddr.0 sethostent.0 sethostfile.0 gethostent.0
E 5

D 11
.SUFFIXES: .3 .0
E 11
I 11
D 12
all depend lint tags:
E 12
I 12
D 14
all clean depend lint tags:
E 14
I 14
D 16
MAN3=	assert.0 bitstring.0 end.0 intro.0 monitor.0 varargs.0
MLINKS=	end.3 edata.3 end.3 etext.3 monitor.3 moncontrol.3 monitor.3 \
E 16
I 16
D 17
D 18
MAN3=	assert.0 bitstring.0 end.0 intro.0 monitor.0 stdarg.0
MLINKS+=end.3 edata.3 end.3 etext.3 monitor.3 moncontrol.3 monitor.3 \
E 16
	monstartup.3
E 18
I 18
D 20
MAN3=	assert.0 bitstring.0 end.0 intro.0 moncontrol.0 stdarg.0
E 20
I 20
D 22
MAN3=	assert.0 bitstring.0 end.0 intro.0 stdarg.0
E 22
I 22
MAN3=	assert.0 bitstring.0 end.0 intro.0 queue.0 stdarg.0
E 22
E 20
MLINKS+=end.3 edata.3 end.3 etext.3 moncontrol.3 monstartup.3
I 22
MLINKS+=queue.3 list_entry.3 queue.3 list_head.3 queue.3 list_init.3
MLINKS+=queue.3 list_insert_after.3 queue.3 list_insert_head.3
MLINKS+=queue.3 list_remove.3 queue.3 tailq_entry.3 queue.3 tailq_head.3
MLINKS+=queue.3 tailq_init.3 queue.3 tailq_insert_after.3
MLINKS+=queue.3 tailq_insert_head.3 queue.3 tailq_insert_tail.3
MLINKS+=queue.3 tailq_remove.3 queue.3 circleq_entry.3 queue.3 circleq_head.3
MLINKS+=queue.3 circleq_init.3 queue.3 circleq_insert_after.3
MLINKS+=queue.3 circleq_insert_before.3 queue.3 circleq_insert_head.3
MLINKS+=queue.3 circleq_insert_tail.3 queue.3 circleq_remove.3
E 22
E 18
E 17
I 17
MAN3=	assert.0 bitstring.0 end.0 intro.0 stdarg.0
MLINKS+=end.3 edata.3 end.3 etext.3
E 17
I 16
D 19
MLINKS+=stdarg.3 varargs.3
E 19
I 19
MLINKS+=stdarg.3 varargs.3 stdarg.3 va_arg.3 stdarg.3 va_end.3
MLINKS+=stdarg.3 va_start.3
E 19
E 16
E 14
E 12
E 11

I 14
all: ${MAN3}

clean depend lint tags:

E 14
D 11
.3.0:
	${DESTDIR}/usr/man/manroff $*.3 > $*.0

all: ${OBJS}

clean: FRC
E 11
I 11
D 12
clean cleandir:
E 12
I 12
cleandir:
E 12
E 11
D 14
	rm -f ${OBJS}
E 14
I 14
	rm -f ${MAN3}
E 14

D 11
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
E 11
I 11
D 14
install: ${OBJS}
D 12
	(cd ${DESTDIR}${MDIR}; rm -f *)
E 11
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/end.0 ${DESTDIR}${MDIR}/edata.0
	ln ${DESTDIR}${MDIR}/end.0 ${DESTDIR}${MDIR}/etext.0
	ln ${DESTDIR}${MDIR}/j0.0 ${DESTDIR}${MDIR}/j1.0
	ln ${DESTDIR}${MDIR}/j0.0 ${DESTDIR}${MDIR}/jn.0
	ln ${DESTDIR}${MDIR}/j0.0 ${DESTDIR}${MDIR}/y0.0
	ln ${DESTDIR}${MDIR}/j0.0 ${DESTDIR}${MDIR}/y1.0
	ln ${DESTDIR}${MDIR}/j0.0 ${DESTDIR}${MDIR}/yn.0
	ln ${DESTDIR}${MDIR}/ns.0 ${DESTDIR}${MDIR}/ns_addr.0
	ln ${DESTDIR}${MDIR}/ns.0 ${DESTDIR}${MDIR}/ns_ntoa.0
	ln ${DESTDIR}${MDIR}/sin.0 ${DESTDIR}${MDIR}/acos.0
	ln ${DESTDIR}${MDIR}/sin.0 ${DESTDIR}${MDIR}/asin.0
	ln ${DESTDIR}${MDIR}/sin.0 ${DESTDIR}${MDIR}/atan.0
	ln ${DESTDIR}${MDIR}/sin.0 ${DESTDIR}${MDIR}/atan2.0
	ln ${DESTDIR}${MDIR}/atof.0 ${DESTDIR}${MDIR}/atoi.0
	ln ${DESTDIR}${MDIR}/atof.0 ${DESTDIR}${MDIR}/atol.0
	ln ${DESTDIR}${MDIR}/sin.0 ${DESTDIR}${MDIR}/cos.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_clearerr.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_close.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_delete.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_error.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_fetch.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_firstkey.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_nextkey.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_open.0
	ln ${DESTDIR}${MDIR}/ndbm.0 ${DESTDIR}${MDIR}/dbm_store.0
	ln ${DESTDIR}${MDIR}/dbm.0 ${DESTDIR}${MDIR}/dbminit.0
	ln ${DESTDIR}${MDIR}/dbm.0 ${DESTDIR}${MDIR}/delete.0
	ln ${DESTDIR}${MDIR}/erf.0 ${DESTDIR}${MDIR}/erfc.0
	ln ${DESTDIR}${MDIR}/exp.0 ${DESTDIR}${MDIR}/expm1.0
	ln ${DESTDIR}${MDIR}/ecvt.0 ${DESTDIR}${MDIR}/fcvt.0
	ln ${DESTDIR}${MDIR}/dbm.0 ${DESTDIR}${MDIR}/fetch.0
	ln ${DESTDIR}${MDIR}/dbm.0 ${DESTDIR}${MDIR}/firstkey.0
	ln ${DESTDIR}${MDIR}/ecvt.0 ${DESTDIR}${MDIR}/gcvt.0
	ln ${DESTDIR}${MDIR}/exp.0 ${DESTDIR}${MDIR}/log.0
	ln ${DESTDIR}${MDIR}/exp.0 ${DESTDIR}${MDIR}/log10.0
	ln ${DESTDIR}${MDIR}/exp.0 ${DESTDIR}${MDIR}/log1p.0
	ln ${DESTDIR}${MDIR}/dbm.0 ${DESTDIR}${MDIR}/nextkey.0
	ln ${DESTDIR}${MDIR}/exp.0 ${DESTDIR}${MDIR}/pow.0
	ln ${DESTDIR}${MDIR}/rcmd.0 ${DESTDIR}${MDIR}/rresvport.0
	ln ${DESTDIR}${MDIR}/rcmd.0 ${DESTDIR}${MDIR}/ruserok.0
	ln ${DESTDIR}${MDIR}/dbm.0 ${DESTDIR}${MDIR}/store.0
	ln ${DESTDIR}${MDIR}/sin.0 ${DESTDIR}${MDIR}/tan.0
	ln ${DESTDIR}${MDIR}/execl.0 ${DESTDIR}${MDIR}/exec.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/addr.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/arc.0
	ln ${DESTDIR}${MDIR}/ctime.0 ${DESTDIR}${MDIR}/asctime.0
	ln ${DESTDIR}${MDIR}/sqrt.0 ${DESTDIR}${MDIR}/cbrt.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/circle.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/cont.0
	ln ${DESTDIR}${MDIR}/ieee.0 ${DESTDIR}${MDIR}/copysign.0
	ln ${DESTDIR}${MDIR}/sinh.0 ${DESTDIR}${MDIR}/cosh.0
	ln ${DESTDIR}${MDIR}/ieee.0 ${DESTDIR}${MDIR}/drem.0
	ln ${DESTDIR}${MDIR}/crypt.0 ${DESTDIR}${MDIR}/encrypt.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/erase.0
	ln ${DESTDIR}${MDIR}/execl.0 ${DESTDIR}${MDIR}/execle.0
	ln ${DESTDIR}${MDIR}/execl.0 ${DESTDIR}${MDIR}/execlp.0
	ln ${DESTDIR}${MDIR}/execl.0 ${DESTDIR}${MDIR}/exect.0
	ln ${DESTDIR}${MDIR}/execl.0 ${DESTDIR}${MDIR}/execv.0
	ln ${DESTDIR}${MDIR}/execl.0 ${DESTDIR}${MDIR}/execve.0
	ln ${DESTDIR}${MDIR}/execl.0 ${DESTDIR}${MDIR}/execvp.0
	ln ${DESTDIR}${MDIR}/getc.0 ${DESTDIR}${MDIR}/fgetc.0
	ln ${DESTDIR}${MDIR}/gets.0 ${DESTDIR}${MDIR}/fgets.0
	ln ${DESTDIR}${MDIR}/ieee.0 ${DESTDIR}${MDIR}/finite.0
	ln ${DESTDIR}${MDIR}/putc.0 ${DESTDIR}${MDIR}/fputc.0
	ln ${DESTDIR}${MDIR}/puts.0 ${DESTDIR}${MDIR}/fputs.0
	ln ${DESTDIR}${MDIR}/time.0 ${DESTDIR}${MDIR}/ftime.0
	ln ${DESTDIR}${MDIR}/getc.0 ${DESTDIR}${MDIR}/getchar.0
	ln ${DESTDIR}${MDIR}/getc.0 ${DESTDIR}${MDIR}/getw.0
	ln ${DESTDIR}${MDIR}/ctime.0 ${DESTDIR}${MDIR}/gmtime.0
	ln ${DESTDIR}${MDIR}/stty.0 ${DESTDIR}${MDIR}/gtty.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/inet_addr.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/inet_lnaof.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/inet_makeaddr.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/inet_netof.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/inet_network.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/inet_ntoa.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isalnum.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isalpha.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isascii.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/iscntrl.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isdigit.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/islower.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isprint.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/ispunct.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isspace.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isupper.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/isxdigit.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/label.0
	ln ${DESTDIR}${MDIR}/frexp.0 ${DESTDIR}${MDIR}/ldexp.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/line.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/linemod.0
	ln ${DESTDIR}${MDIR}/ctime.0 ${DESTDIR}${MDIR}/localtime.0
	ln ${DESTDIR}${MDIR}/ieee.0 ${DESTDIR}${MDIR}/logb.0
	ln ${DESTDIR}${MDIR}/frexp.0 ${DESTDIR}${MDIR}/modf.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/move.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/network.0
	ln ${DESTDIR}${MDIR}/inet.0 ${DESTDIR}${MDIR}/ntoa.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/openpl.0
	ln ${DESTDIR}${MDIR}/popen.0 ${DESTDIR}${MDIR}/pclose.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/point.0
	ln ${DESTDIR}${MDIR}/putc.0 ${DESTDIR}${MDIR}/putchar.0
	ln ${DESTDIR}${MDIR}/putc.0 ${DESTDIR}${MDIR}/putw.0
	ln ${DESTDIR}${MDIR}/regex.0 ${DESTDIR}${MDIR}/re_comp.0
	ln ${DESTDIR}${MDIR}/regex.0 ${DESTDIR}${MDIR}/re_exec.0
D 4
	ln ${DESTDIR}${MDIR}/regex.0 ${DESTDIR}${MDIR}/regcomp.0
	ln ${DESTDIR}${MDIR}/regex.0 ${DESTDIR}${MDIR}/regexec.0
	ln ${DESTDIR}${MDIR}/regex.0 ${DESTDIR}${MDIR}/regsub.0
	ln ${DESTDIR}${MDIR}/regex.0 ${DESTDIR}${MDIR}/regerror.0
E 4
I 4
	ln ${DESTDIR}${MDIR}/regexp.0 ${DESTDIR}${MDIR}/regcomp.0
	ln ${DESTDIR}${MDIR}/regexp.0 ${DESTDIR}${MDIR}/regexec.0
	ln ${DESTDIR}${MDIR}/regexp.0 ${DESTDIR}${MDIR}/regsub.0
	ln ${DESTDIR}${MDIR}/regexp.0 ${DESTDIR}${MDIR}/regerror.0
E 4
	ln ${DESTDIR}${MDIR}/ieee.0 ${DESTDIR}${MDIR}/scalb.0
	ln ${DESTDIR}${MDIR}/crypt.0 ${DESTDIR}${MDIR}/setkey.0
	ln ${DESTDIR}${MDIR}/plot.0 ${DESTDIR}${MDIR}/space.0
	ln ${DESTDIR}${MDIR}/rand.0 ${DESTDIR}${MDIR}/srand.0
	ln ${DESTDIR}${MDIR}/sinh.0 ${DESTDIR}${MDIR}/tanh.0
	ln ${DESTDIR}${MDIR}/ctime.0 ${DESTDIR}${MDIR}/timezone.0
I 2
	ln ${DESTDIR}${MDIR}/ctime.0 ${DESTDIR}${MDIR}/tzset.0
E 2
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/toascii.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/tolower.0
	ln ${DESTDIR}${MDIR}/ctype.0 ${DESTDIR}${MDIR}/toupper.0
	ln ${DESTDIR}${MDIR}/setjmp.0 ${DESTDIR}${MDIR}/_longjmp.0
	ln ${DESTDIR}${MDIR}/setjmp.0 ${DESTDIR}${MDIR}/_setjmp.0
	ln ${DESTDIR}${MDIR}/asinh.0 ${DESTDIR}${MDIR}/acosh.0
	ln ${DESTDIR}${MDIR}/malloc.0 ${DESTDIR}${MDIR}/alloca.0
	ln ${DESTDIR}${MDIR}/asinh.0 ${DESTDIR}${MDIR}/atanh.0
	ln ${DESTDIR}${MDIR}/hypot.0 ${DESTDIR}${MDIR}/cabs.0
	ln ${DESTDIR}${MDIR}/malloc.0 ${DESTDIR}${MDIR}/calloc.0
	ln ${DESTDIR}${MDIR}/floor.0 ${DESTDIR}${MDIR}/ceil.0
	ln ${DESTDIR}${MDIR}/syslog.0 ${DESTDIR}${MDIR}/closelog.0
	ln ${DESTDIR}${MDIR}/perror.0 ${DESTDIR}${MDIR}/errlist.0
	ln ${DESTDIR}${MDIR}/floor.0 ${DESTDIR}${MDIR}/fabs.0
	ln ${DESTDIR}${MDIR}/fopen.0 ${DESTDIR}${MDIR}/fdopen.0
	ln ${DESTDIR}${MDIR}/malloc.0 ${DESTDIR}${MDIR}/free.0
	ln ${DESTDIR}${MDIR}/fopen.0 ${DESTDIR}${MDIR}/freopen.0
	ln ${DESTDIR}${MDIR}/scanf.0 ${DESTDIR}${MDIR}/fscanf.0
	ln ${DESTDIR}${MDIR}/fseek.0 ${DESTDIR}${MDIR}/ftell.0
	ln ${DESTDIR}${MDIR}/fread.0 ${DESTDIR}${MDIR}/fwrite.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/index.0
	ln ${DESTDIR}${MDIR}/random.0 ${DESTDIR}${MDIR}/initstate.0
	ln ${DESTDIR}${MDIR}/setjmp.0 ${DESTDIR}${MDIR}/longjmp.0
	ln ${DESTDIR}${MDIR}/syslog.0 ${DESTDIR}${MDIR}/openlog.0
	ln ${DESTDIR}${MDIR}/malloc.0 ${DESTDIR}${MDIR}/realloc.0
	ln ${DESTDIR}${MDIR}/insque.0 ${DESTDIR}${MDIR}/remque.0
	ln ${DESTDIR}${MDIR}/fseek.0 ${DESTDIR}${MDIR}/rewind.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/rindex.0
	ln ${DESTDIR}${MDIR}/setuid.0 ${DESTDIR}${MDIR}/setegid.0
	ln ${DESTDIR}${MDIR}/setuid.0 ${DESTDIR}${MDIR}/seteuid.0
	ln ${DESTDIR}${MDIR}/setuid.0 ${DESTDIR}${MDIR}/setgid.0
	ln ${DESTDIR}${MDIR}/syslog.0 ${DESTDIR}${MDIR}/setlogmask.0
	ln ${DESTDIR}${MDIR}/setuid.0 ${DESTDIR}${MDIR}/setrgid.0
	ln ${DESTDIR}${MDIR}/setuid.0 ${DESTDIR}${MDIR}/setruid.0
	ln ${DESTDIR}${MDIR}/random.0 ${DESTDIR}${MDIR}/setstate.0
	ln ${DESTDIR}${MDIR}/random.0 ${DESTDIR}${MDIR}/srandom.0
	ln ${DESTDIR}${MDIR}/scanf.0 ${DESTDIR}${MDIR}/sscanf.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strcat.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strcmp.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strcpy.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strlen.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strncat.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strncmp.0
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strcasecmp.0
D 3
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strcasencmp.0
E 3
I 3
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strncasecmp.0
E 3
	ln ${DESTDIR}${MDIR}/string.0 ${DESTDIR}${MDIR}/strncpy.0
	ln ${DESTDIR}${MDIR}/perror.0 ${DESTDIR}${MDIR}/sys.0
	ln ${DESTDIR}${MDIR}/perror.0 ${DESTDIR}${MDIR}/sys_errlist.0
	ln ${DESTDIR}${MDIR}/perror.0 ${DESTDIR}${MDIR}/sys_nerr.0
	ln ${DESTDIR}${MDIR}/mktemp.0 ${DESTDIR}${MDIR}/mkstemp.0
	ln ${DESTDIR}${MDIR}/floor.0 ${DESTDIR}${MDIR}/rint.0
	ln ${DESTDIR}${MDIR}/getenv.0 ${DESTDIR}${MDIR}/setenv.0
	ln ${DESTDIR}${MDIR}/getenv.0 ${DESTDIR}${MDIR}/unsetenv.0
	ln ${DESTDIR}${MDIR}/scandir.0 ${DESTDIR}${MDIR}/alphasort.0
	ln ${DESTDIR}${MDIR}/bstring.0 ${DESTDIR}${MDIR}/bcmp.0
	ln ${DESTDIR}${MDIR}/bstring.0 ${DESTDIR}${MDIR}/bcopy.0
	ln ${DESTDIR}${MDIR}/bstring.0 ${DESTDIR}${MDIR}/bzero.0
	ln ${DESTDIR}${MDIR}/ferror.0 ${DESTDIR}${MDIR}/clearerr.0
	ln ${DESTDIR}${MDIR}/ferror.0 ${DESTDIR}${MDIR}/feof.0
	ln ${DESTDIR}${MDIR}/fclose.0 ${DESTDIR}${MDIR}/fflush.0
	ln ${DESTDIR}${MDIR}/bstring.0 ${DESTDIR}${MDIR}/ffs.0
	ln ${DESTDIR}${MDIR}/ferror.0 ${DESTDIR}${MDIR}/fileno.0
	ln ${DESTDIR}${MDIR}/printf.0 ${DESTDIR}${MDIR}/fprintf.0
	ln ${DESTDIR}${MDIR}/ttyname.0 ${DESTDIR}${MDIR}/isatty.0
	ln ${DESTDIR}${MDIR}/monitor.0 ${DESTDIR}${MDIR}/moncontrol.0
	ln ${DESTDIR}${MDIR}/monitor.0 ${DESTDIR}${MDIR}/monstartup.0
	ln ${DESTDIR}${MDIR}/setbuf.0 ${DESTDIR}${MDIR}/setbuffer.0
	ln ${DESTDIR}${MDIR}/setbuf.0 ${DESTDIR}${MDIR}/setlinebuf.0
	ln ${DESTDIR}${MDIR}/printf.0 ${DESTDIR}${MDIR}/sprintf.0
	ln ${DESTDIR}${MDIR}/psignal.0 ${DESTDIR}${MDIR}/sys_siglist.0
	ln ${DESTDIR}${MDIR}/ttyname.0 ${DESTDIR}${MDIR}/ttyslot.0
	ln ${DESTDIR}${MDIR}/lgamma.0 ${DESTDIR}${MDIR}/gamma.0
	ln ${DESTDIR}${MDIR}/getfsent.0 ${DESTDIR}${MDIR}/endfsent.0
	ln ${DESTDIR}${MDIR}/getgrent.0 ${DESTDIR}${MDIR}/endgrent.0
	ln ${DESTDIR}${MDIR}/getpwent.0 ${DESTDIR}${MDIR}/endpwent.0
	ln ${DESTDIR}${MDIR}/getfsent.0 ${DESTDIR}${MDIR}/getfsfile.0
	ln ${DESTDIR}${MDIR}/getfsent.0 ${DESTDIR}${MDIR}/getfsspec.0
	ln ${DESTDIR}${MDIR}/getfsent.0 ${DESTDIR}${MDIR}/getfstype.0
	ln ${DESTDIR}${MDIR}/getgrent.0 ${DESTDIR}${MDIR}/getgrgid.0
	ln ${DESTDIR}${MDIR}/getgrent.0 ${DESTDIR}${MDIR}/getgrnam.0
	ln ${DESTDIR}${MDIR}/getpwent.0 ${DESTDIR}${MDIR}/getpwnam.0
	ln ${DESTDIR}${MDIR}/getpwent.0 ${DESTDIR}${MDIR}/getpwuid.0
	ln ${DESTDIR}${MDIR}/getfsent.0 ${DESTDIR}${MDIR}/setfsent.0
	ln ${DESTDIR}${MDIR}/getgrent.0 ${DESTDIR}${MDIR}/setgrent.0
	ln ${DESTDIR}${MDIR}/getgrent.0 ${DESTDIR}${MDIR}/setgrfile.0
	ln ${DESTDIR}${MDIR}/getpwent.0 ${DESTDIR}${MDIR}/setpwent.0
	ln ${DESTDIR}${MDIR}/getpwent.0 ${DESTDIR}${MDIR}/setpwfile.0
	ln ${DESTDIR}${MDIR}/termcap.0 ${DESTDIR}${MDIR}/tgetent.0
	ln ${DESTDIR}${MDIR}/termcap.0 ${DESTDIR}${MDIR}/tgetflag.0
	ln ${DESTDIR}${MDIR}/termcap.0 ${DESTDIR}${MDIR}/tgetnum.0
	ln ${DESTDIR}${MDIR}/termcap.0 ${DESTDIR}${MDIR}/tgetstr.0
	ln ${DESTDIR}${MDIR}/termcap.0 ${DESTDIR}${MDIR}/tgoto.0
	ln ${DESTDIR}${MDIR}/termcap.0 ${DESTDIR}${MDIR}/tputs.0
	ln ${DESTDIR}${MDIR}/directory.0 ${DESTDIR}${MDIR}/closedir.0
	ln ${DESTDIR}${MDIR}/directory.0 ${DESTDIR}${MDIR}/dirfd.0
	ln ${DESTDIR}${MDIR}/getttyent.0 ${DESTDIR}${MDIR}/endttyent.0
	ln ${DESTDIR}${MDIR}/getttyent.0 ${DESTDIR}${MDIR}/getttynam.0
	ln ${DESTDIR}${MDIR}/directory.0 ${DESTDIR}${MDIR}/opendir.0
	ln ${DESTDIR}${MDIR}/directory.0 ${DESTDIR}${MDIR}/readdir.0
	ln ${DESTDIR}${MDIR}/directory.0 ${DESTDIR}${MDIR}/rewinddir.0
	ln ${DESTDIR}${MDIR}/directory.0 ${DESTDIR}${MDIR}/seekdir.0
	ln ${DESTDIR}${MDIR}/getttyent.0 ${DESTDIR}${MDIR}/setttyent.0
	ln ${DESTDIR}${MDIR}/directory.0 ${DESTDIR}${MDIR}/telldir.0
	ln ${DESTDIR}${MDIR}/getnetent.0 ${DESTDIR}${MDIR}/endnetent.0
	ln ${DESTDIR}${MDIR}/getnetent.0 ${DESTDIR}${MDIR}/getnetbyaddr.0
	ln ${DESTDIR}${MDIR}/getnetent.0 ${DESTDIR}${MDIR}/getnetbyname.0
	ln ${DESTDIR}${MDIR}/byteorder.0 ${DESTDIR}${MDIR}/htonl.0
	ln ${DESTDIR}${MDIR}/byteorder.0 ${DESTDIR}${MDIR}/htons.0
	ln ${DESTDIR}${MDIR}/byteorder.0 ${DESTDIR}${MDIR}/ntohl.0
	ln ${DESTDIR}${MDIR}/byteorder.0 ${DESTDIR}${MDIR}/ntohs.0
	ln ${DESTDIR}${MDIR}/getnetent.0 ${DESTDIR}${MDIR}/setnetent.0
	ln ${DESTDIR}${MDIR}/getservent.0 ${DESTDIR}${MDIR}/endservent.0
	ln ${DESTDIR}${MDIR}/getservent.0 ${DESTDIR}${MDIR}/getservbyname.0
	ln ${DESTDIR}${MDIR}/getservent.0 ${DESTDIR}${MDIR}/getservbyport.0
	ln ${DESTDIR}${MDIR}/getservent.0 ${DESTDIR}${MDIR}/setservent.0
	ln ${DESTDIR}${MDIR}/getprotoent.0 ${DESTDIR}${MDIR}/endprotoent.0
	ln ${DESTDIR}${MDIR}/getusershell.0 ${DESTDIR}${MDIR}/endusershell.0
	ln ${DESTDIR}${MDIR}/getprotoent.0 ${DESTDIR}${MDIR}/getprotobyname.0
	ln ${DESTDIR}${MDIR}/getprotoent.0 ${DESTDIR}${MDIR}/getprotobynumber.0
	ln ${DESTDIR}${MDIR}/getprotoent.0 ${DESTDIR}${MDIR}/setprotoent.0
	ln ${DESTDIR}${MDIR}/getusershell.0 ${DESTDIR}${MDIR}/setusershell.0
	ln ${DESTDIR}${MDIR}/gethostbyname.0 ${DESTDIR}${MDIR}/endhostent.0
	ln ${DESTDIR}${MDIR}/gethostbyname.0 ${DESTDIR}${MDIR}/gethostbyaddr.0
	ln ${DESTDIR}${MDIR}/gethostbyname.0 ${DESTDIR}${MDIR}/sethostent.0
	ln ${DESTDIR}${MDIR}/gethostbyname.0 ${DESTDIR}${MDIR}/sethostfile.0
	ln ${DESTDIR}${MDIR}/gethostbyname.0 ${DESTDIR}${MDIR}/gethostent.0
I 8
D 10
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/ftw.0
E 10
I 10
	ln ${DESTDIR}${MDIR}/treewalk.0 ${DESTDIR}${MDIR}/ftw.0
E 10
E 8
I 5
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/memccpy.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/memchr.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/memcmp.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/memcpy.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/memset.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/strchr.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/strcspn.0
I 8
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/strpbrk.0
E 8
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/strrchr.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/strspn.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/strtok.0
I 9
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/strtol.0
E 9
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/tmpnam.0
I 6
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/tmpfile.0
	ln ${DESTDIR}${MDIR}/compat-sys5.0 ${DESTDIR}${MDIR}/tempnam.0
E 12
I 12
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/edata.0; ln ${MDIR}/end.0 ${MDIR}/edata.0
	rm -f ${MDIR}/etext.0; ln ${MDIR}/end.0 ${MDIR}/etext.0
D 13
	rm -f ${MDIR}/j1.0; ln ${MDIR}/j0.0 ${MDIR}/j1.0
	rm -f ${MDIR}/jn.0; ln ${MDIR}/j0.0 ${MDIR}/jn.0
	rm -f ${MDIR}/y0.0; ln ${MDIR}/j0.0 ${MDIR}/y0.0
	rm -f ${MDIR}/y1.0; ln ${MDIR}/j0.0 ${MDIR}/y1.0
	rm -f ${MDIR}/yn.0; ln ${MDIR}/j0.0 ${MDIR}/yn.0
	rm -f ${MDIR}/ns_addr.0; ln ${MDIR}/ns.0 ${MDIR}/ns_addr.0
	rm -f ${MDIR}/ns_ntoa.0; ln ${MDIR}/ns.0 ${MDIR}/ns_ntoa.0
	rm -f ${MDIR}/acos.0; ln ${MDIR}/sin.0 ${MDIR}/acos.0
	rm -f ${MDIR}/asin.0; ln ${MDIR}/sin.0 ${MDIR}/asin.0
	rm -f ${MDIR}/atan.0; ln ${MDIR}/sin.0 ${MDIR}/atan.0
	rm -f ${MDIR}/atan2.0; ln ${MDIR}/sin.0 ${MDIR}/atan2.0
	rm -f ${MDIR}/atoi.0; ln ${MDIR}/atof.0 ${MDIR}/atoi.0
	rm -f ${MDIR}/atol.0; ln ${MDIR}/atof.0 ${MDIR}/atol.0
	rm -f ${MDIR}/cos.0; ln ${MDIR}/sin.0 ${MDIR}/cos.0
	rm -f ${MDIR}/dbm_clearerr.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_clearerr.0
	rm -f ${MDIR}/dbm_close.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_close.0
	rm -f ${MDIR}/dbm_delete.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_delete.0
	rm -f ${MDIR}/dbm_error.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_error.0
	rm -f ${MDIR}/dbm_fetch.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_fetch.0
	rm -f ${MDIR}/dbm_firstkey.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_firstkey.0
	rm -f ${MDIR}/dbm_nextkey.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_nextkey.0
	rm -f ${MDIR}/dbm_open.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_open.0
	rm -f ${MDIR}/dbm_store.0; ln ${MDIR}/ndbm.0 ${MDIR}/dbm_store.0
	rm -f ${MDIR}/dbminit.0; ln ${MDIR}/dbm.0 ${MDIR}/dbminit.0
	rm -f ${MDIR}/delete.0; ln ${MDIR}/dbm.0 ${MDIR}/delete.0
	rm -f ${MDIR}/erfc.0; ln ${MDIR}/erf.0 ${MDIR}/erfc.0
	rm -f ${MDIR}/expm1.0; ln ${MDIR}/exp.0 ${MDIR}/expm1.0
	rm -f ${MDIR}/fcvt.0; ln ${MDIR}/ecvt.0 ${MDIR}/fcvt.0
	rm -f ${MDIR}/fetch.0; ln ${MDIR}/dbm.0 ${MDIR}/fetch.0
	rm -f ${MDIR}/firstkey.0; ln ${MDIR}/dbm.0 ${MDIR}/firstkey.0
	rm -f ${MDIR}/gcvt.0; ln ${MDIR}/ecvt.0 ${MDIR}/gcvt.0
	rm -f ${MDIR}/log.0; ln ${MDIR}/exp.0 ${MDIR}/log.0
	rm -f ${MDIR}/log10.0; ln ${MDIR}/exp.0 ${MDIR}/log10.0
	rm -f ${MDIR}/log1p.0; ln ${MDIR}/exp.0 ${MDIR}/log1p.0
	rm -f ${MDIR}/nextkey.0; ln ${MDIR}/dbm.0 ${MDIR}/nextkey.0
	rm -f ${MDIR}/pow.0; ln ${MDIR}/exp.0 ${MDIR}/pow.0
	rm -f ${MDIR}/rresvport.0; ln ${MDIR}/rcmd.0 ${MDIR}/rresvport.0
	rm -f ${MDIR}/ruserok.0; ln ${MDIR}/rcmd.0 ${MDIR}/ruserok.0
	rm -f ${MDIR}/store.0; ln ${MDIR}/dbm.0 ${MDIR}/store.0
	rm -f ${MDIR}/tan.0; ln ${MDIR}/sin.0 ${MDIR}/tan.0
	rm -f ${MDIR}/exec.0; ln ${MDIR}/execl.0 ${MDIR}/exec.0
	rm -f ${MDIR}/addr.0; ln ${MDIR}/inet.0 ${MDIR}/addr.0
	rm -f ${MDIR}/arc.0; ln ${MDIR}/plot.0 ${MDIR}/arc.0
	rm -f ${MDIR}/asctime.0; ln ${MDIR}/ctime.0 ${MDIR}/asctime.0
	rm -f ${MDIR}/cbrt.0; ln ${MDIR}/sqrt.0 ${MDIR}/cbrt.0
	rm -f ${MDIR}/circle.0; ln ${MDIR}/plot.0 ${MDIR}/circle.0
	rm -f ${MDIR}/cont.0; ln ${MDIR}/plot.0 ${MDIR}/cont.0
	rm -f ${MDIR}/copysign.0; ln ${MDIR}/ieee.0 ${MDIR}/copysign.0
	rm -f ${MDIR}/cosh.0; ln ${MDIR}/sinh.0 ${MDIR}/cosh.0
	rm -f ${MDIR}/drem.0; ln ${MDIR}/ieee.0 ${MDIR}/drem.0
	rm -f ${MDIR}/encrypt.0; ln ${MDIR}/crypt.0 ${MDIR}/encrypt.0
	rm -f ${MDIR}/erase.0; ln ${MDIR}/plot.0 ${MDIR}/erase.0
	rm -f ${MDIR}/execle.0; ln ${MDIR}/execl.0 ${MDIR}/execle.0
	rm -f ${MDIR}/execlp.0; ln ${MDIR}/execl.0 ${MDIR}/execlp.0
	rm -f ${MDIR}/exect.0; ln ${MDIR}/execl.0 ${MDIR}/exect.0
	rm -f ${MDIR}/execv.0; ln ${MDIR}/execl.0 ${MDIR}/execv.0
	rm -f ${MDIR}/execve.0; ln ${MDIR}/execl.0 ${MDIR}/execve.0
	rm -f ${MDIR}/execvp.0; ln ${MDIR}/execl.0 ${MDIR}/execvp.0
	rm -f ${MDIR}/fgetc.0; ln ${MDIR}/getc.0 ${MDIR}/fgetc.0
	rm -f ${MDIR}/fgets.0; ln ${MDIR}/gets.0 ${MDIR}/fgets.0
	rm -f ${MDIR}/finite.0; ln ${MDIR}/ieee.0 ${MDIR}/finite.0
	rm -f ${MDIR}/fputc.0; ln ${MDIR}/putc.0 ${MDIR}/fputc.0
	rm -f ${MDIR}/fputs.0; ln ${MDIR}/puts.0 ${MDIR}/fputs.0
	rm -f ${MDIR}/ftime.0; ln ${MDIR}/time.0 ${MDIR}/ftime.0
	rm -f ${MDIR}/getchar.0; ln ${MDIR}/getc.0 ${MDIR}/getchar.0
	rm -f ${MDIR}/getw.0; ln ${MDIR}/getc.0 ${MDIR}/getw.0
	rm -f ${MDIR}/gmtime.0; ln ${MDIR}/ctime.0 ${MDIR}/gmtime.0
	rm -f ${MDIR}/gtty.0; ln ${MDIR}/stty.0 ${MDIR}/gtty.0
	rm -f ${MDIR}/inet_addr.0; ln ${MDIR}/inet.0 ${MDIR}/inet_addr.0
	rm -f ${MDIR}/inet_lnaof.0; ln ${MDIR}/inet.0 ${MDIR}/inet_lnaof.0
	rm -f ${MDIR}/inet_makeaddr.0; ln ${MDIR}/inet.0 ${MDIR}/inet_makeaddr.0
	rm -f ${MDIR}/inet_netof.0; ln ${MDIR}/inet.0 ${MDIR}/inet_netof.0
	rm -f ${MDIR}/inet_network.0; ln ${MDIR}/inet.0 ${MDIR}/inet_network.0
	rm -f ${MDIR}/inet_ntoa.0; ln ${MDIR}/inet.0 ${MDIR}/inet_ntoa.0
	rm -f ${MDIR}/isalnum.0; ln ${MDIR}/ctype.0 ${MDIR}/isalnum.0
	rm -f ${MDIR}/isalpha.0; ln ${MDIR}/ctype.0 ${MDIR}/isalpha.0
	rm -f ${MDIR}/isascii.0; ln ${MDIR}/ctype.0 ${MDIR}/isascii.0
	rm -f ${MDIR}/iscntrl.0; ln ${MDIR}/ctype.0 ${MDIR}/iscntrl.0
	rm -f ${MDIR}/isdigit.0; ln ${MDIR}/ctype.0 ${MDIR}/isdigit.0
	rm -f ${MDIR}/islower.0; ln ${MDIR}/ctype.0 ${MDIR}/islower.0
	rm -f ${MDIR}/isprint.0; ln ${MDIR}/ctype.0 ${MDIR}/isprint.0
	rm -f ${MDIR}/ispunct.0; ln ${MDIR}/ctype.0 ${MDIR}/ispunct.0
	rm -f ${MDIR}/isspace.0; ln ${MDIR}/ctype.0 ${MDIR}/isspace.0
	rm -f ${MDIR}/isupper.0; ln ${MDIR}/ctype.0 ${MDIR}/isupper.0
	rm -f ${MDIR}/isxdigit.0; ln ${MDIR}/ctype.0 ${MDIR}/isxdigit.0
	rm -f ${MDIR}/label.0; ln ${MDIR}/plot.0 ${MDIR}/label.0
	rm -f ${MDIR}/ldexp.0; ln ${MDIR}/frexp.0 ${MDIR}/ldexp.0
	rm -f ${MDIR}/line.0; ln ${MDIR}/plot.0 ${MDIR}/line.0
	rm -f ${MDIR}/linemod.0; ln ${MDIR}/plot.0 ${MDIR}/linemod.0
	rm -f ${MDIR}/localtime.0; ln ${MDIR}/ctime.0 ${MDIR}/localtime.0
	rm -f ${MDIR}/logb.0; ln ${MDIR}/ieee.0 ${MDIR}/logb.0
	rm -f ${MDIR}/modf.0; ln ${MDIR}/frexp.0 ${MDIR}/modf.0
	rm -f ${MDIR}/move.0; ln ${MDIR}/plot.0 ${MDIR}/move.0
	rm -f ${MDIR}/network.0; ln ${MDIR}/inet.0 ${MDIR}/network.0
	rm -f ${MDIR}/ntoa.0; ln ${MDIR}/inet.0 ${MDIR}/ntoa.0
	rm -f ${MDIR}/openpl.0; ln ${MDIR}/plot.0 ${MDIR}/openpl.0
	rm -f ${MDIR}/pclose.0; ln ${MDIR}/popen.0 ${MDIR}/pclose.0
	rm -f ${MDIR}/point.0; ln ${MDIR}/plot.0 ${MDIR}/point.0
	rm -f ${MDIR}/putchar.0; ln ${MDIR}/putc.0 ${MDIR}/putchar.0
	rm -f ${MDIR}/putw.0; ln ${MDIR}/putc.0 ${MDIR}/putw.0
	rm -f ${MDIR}/re_comp.0; ln ${MDIR}/regex.0 ${MDIR}/re_comp.0
	rm -f ${MDIR}/re_exec.0; ln ${MDIR}/regex.0 ${MDIR}/re_exec.0
	rm -f ${MDIR}/regcomp.0; ln ${MDIR}/regexp.0 ${MDIR}/regcomp.0
	rm -f ${MDIR}/regexec.0; ln ${MDIR}/regexp.0 ${MDIR}/regexec.0
	rm -f ${MDIR}/regsub.0; ln ${MDIR}/regexp.0 ${MDIR}/regsub.0
	rm -f ${MDIR}/regerror.0; ln ${MDIR}/regexp.0 ${MDIR}/regerror.0
	rm -f ${MDIR}/scalb.0; ln ${MDIR}/ieee.0 ${MDIR}/scalb.0
	rm -f ${MDIR}/setkey.0; ln ${MDIR}/crypt.0 ${MDIR}/setkey.0
	rm -f ${MDIR}/space.0; ln ${MDIR}/plot.0 ${MDIR}/space.0
	rm -f ${MDIR}/srand.0; ln ${MDIR}/rand.0 ${MDIR}/srand.0
	rm -f ${MDIR}/tanh.0; ln ${MDIR}/sinh.0 ${MDIR}/tanh.0
	rm -f ${MDIR}/timezone.0; ln ${MDIR}/ctime.0 ${MDIR}/timezone.0
	rm -f ${MDIR}/tzset.0; ln ${MDIR}/ctime.0 ${MDIR}/tzset.0
	rm -f ${MDIR}/toascii.0; ln ${MDIR}/ctype.0 ${MDIR}/toascii.0
	rm -f ${MDIR}/tolower.0; ln ${MDIR}/ctype.0 ${MDIR}/tolower.0
	rm -f ${MDIR}/toupper.0; ln ${MDIR}/ctype.0 ${MDIR}/toupper.0
	rm -f ${MDIR}/_longjmp.0; ln ${MDIR}/setjmp.0 ${MDIR}/_longjmp.0
	rm -f ${MDIR}/_setjmp.0; ln ${MDIR}/setjmp.0 ${MDIR}/_setjmp.0
	rm -f ${MDIR}/acosh.0; ln ${MDIR}/asinh.0 ${MDIR}/acosh.0
	rm -f ${MDIR}/alloca.0; ln ${MDIR}/malloc.0 ${MDIR}/alloca.0
	rm -f ${MDIR}/atanh.0; ln ${MDIR}/asinh.0 ${MDIR}/atanh.0
	rm -f ${MDIR}/cabs.0; ln ${MDIR}/hypot.0 ${MDIR}/cabs.0
	rm -f ${MDIR}/calloc.0; ln ${MDIR}/malloc.0 ${MDIR}/calloc.0
	rm -f ${MDIR}/ceil.0; ln ${MDIR}/floor.0 ${MDIR}/ceil.0
	rm -f ${MDIR}/closelog.0; ln ${MDIR}/syslog.0 ${MDIR}/closelog.0
	rm -f ${MDIR}/fabs.0; ln ${MDIR}/floor.0 ${MDIR}/fabs.0
	rm -f ${MDIR}/fdopen.0; ln ${MDIR}/fopen.0 ${MDIR}/fdopen.0
	rm -f ${MDIR}/free.0; ln ${MDIR}/malloc.0 ${MDIR}/free.0
	rm -f ${MDIR}/freopen.0; ln ${MDIR}/fopen.0 ${MDIR}/freopen.0
	rm -f ${MDIR}/fscanf.0; ln ${MDIR}/scanf.0 ${MDIR}/fscanf.0
	rm -f ${MDIR}/ftell.0; ln ${MDIR}/fseek.0 ${MDIR}/ftell.0
	rm -f ${MDIR}/fwrite.0; ln ${MDIR}/fread.0 ${MDIR}/fwrite.0
	rm -f ${MDIR}/index.0; ln ${MDIR}/string.0 ${MDIR}/index.0
	rm -f ${MDIR}/initstate.0; ln ${MDIR}/random.0 ${MDIR}/initstate.0
	rm -f ${MDIR}/longjmp.0; ln ${MDIR}/setjmp.0 ${MDIR}/longjmp.0
	rm -f ${MDIR}/openlog.0; ln ${MDIR}/syslog.0 ${MDIR}/openlog.0
	rm -f ${MDIR}/realloc.0; ln ${MDIR}/malloc.0 ${MDIR}/realloc.0
	rm -f ${MDIR}/remque.0; ln ${MDIR}/insque.0 ${MDIR}/remque.0
	rm -f ${MDIR}/rewind.0; ln ${MDIR}/fseek.0 ${MDIR}/rewind.0
	rm -f ${MDIR}/rindex.0; ln ${MDIR}/string.0 ${MDIR}/rindex.0
	rm -f ${MDIR}/setegid.0; ln ${MDIR}/setuid.0 ${MDIR}/setegid.0
	rm -f ${MDIR}/seteuid.0; ln ${MDIR}/setuid.0 ${MDIR}/seteuid.0
	rm -f ${MDIR}/setgid.0; ln ${MDIR}/setuid.0 ${MDIR}/setgid.0
	rm -f ${MDIR}/setlogmask.0; ln ${MDIR}/syslog.0 ${MDIR}/setlogmask.0
	rm -f ${MDIR}/vsyslog.0; ln ${MDIR}/syslog.0 ${MDIR}/vsyslog.0
	rm -f ${MDIR}/setrgid.0; ln ${MDIR}/setuid.0 ${MDIR}/setrgid.0
	rm -f ${MDIR}/setruid.0; ln ${MDIR}/setuid.0 ${MDIR}/setruid.0
	rm -f ${MDIR}/setstate.0; ln ${MDIR}/random.0 ${MDIR}/setstate.0
	rm -f ${MDIR}/srandom.0; ln ${MDIR}/random.0 ${MDIR}/srandom.0
	rm -f ${MDIR}/sscanf.0; ln ${MDIR}/scanf.0 ${MDIR}/sscanf.0
	rm -f ${MDIR}/strcat.0; ln ${MDIR}/string.0 ${MDIR}/strcat.0
	rm -f ${MDIR}/strcmp.0; ln ${MDIR}/string.0 ${MDIR}/strcmp.0
	rm -f ${MDIR}/strcpy.0; ln ${MDIR}/string.0 ${MDIR}/strcpy.0
	rm -f ${MDIR}/strlen.0; ln ${MDIR}/string.0 ${MDIR}/strlen.0
	rm -f ${MDIR}/strncat.0; ln ${MDIR}/string.0 ${MDIR}/strncat.0
	rm -f ${MDIR}/strncmp.0; ln ${MDIR}/string.0 ${MDIR}/strncmp.0
	rm -f ${MDIR}/strcasecmp.0; ln ${MDIR}/string.0 ${MDIR}/strcasecmp.0
	rm -f ${MDIR}/strncasecmp.0; ln ${MDIR}/string.0 ${MDIR}/strncasecmp.0
	rm -f ${MDIR}/strncpy.0; ln ${MDIR}/string.0 ${MDIR}/strncpy.0
	rm -f ${MDIR}/strerror.0; ln ${MDIR}/perror.0 ${MDIR}/strerror.0
	rm -f ${MDIR}/sys_errlist.0; ln ${MDIR}/perror.0 ${MDIR}/sys_errlist.0
	rm -f ${MDIR}/sys_nerr.0; ln ${MDIR}/perror.0 ${MDIR}/sys_nerr.0
	rm -f ${MDIR}/mkstemp.0; ln ${MDIR}/mktemp.0 ${MDIR}/mkstemp.0
	rm -f ${MDIR}/rint.0; ln ${MDIR}/floor.0 ${MDIR}/rint.0
	rm -f ${MDIR}/setenv.0; ln ${MDIR}/getenv.0 ${MDIR}/setenv.0
	rm -f ${MDIR}/unsetenv.0; ln ${MDIR}/getenv.0 ${MDIR}/unsetenv.0
	rm -f ${MDIR}/putenv.0; ln ${MDIR}/getenv.0 ${MDIR}/putenv.0
	rm -f ${MDIR}/alphasort.0; ln ${MDIR}/scandir.0 ${MDIR}/alphasort.0
	rm -f ${MDIR}/bcmp.0; ln ${MDIR}/bstring.0 ${MDIR}/bcmp.0
	rm -f ${MDIR}/bcopy.0; ln ${MDIR}/bstring.0 ${MDIR}/bcopy.0
	rm -f ${MDIR}/bzero.0; ln ${MDIR}/bstring.0 ${MDIR}/bzero.0
	rm -f ${MDIR}/clearerr.0; ln ${MDIR}/ferror.0 ${MDIR}/clearerr.0
	rm -f ${MDIR}/feof.0; ln ${MDIR}/ferror.0 ${MDIR}/feof.0
	rm -f ${MDIR}/fflush.0; ln ${MDIR}/fclose.0 ${MDIR}/fflush.0
	rm -f ${MDIR}/ffs.0; ln ${MDIR}/bstring.0 ${MDIR}/ffs.0
	rm -f ${MDIR}/fileno.0; ln ${MDIR}/ferror.0 ${MDIR}/fileno.0
	rm -f ${MDIR}/isatty.0; ln ${MDIR}/ttyname.0 ${MDIR}/isatty.0
E 13
	rm -f ${MDIR}/moncontrol.0; ln ${MDIR}/monitor.0 ${MDIR}/moncontrol.0
	rm -f ${MDIR}/monstartup.0; ln ${MDIR}/monitor.0 ${MDIR}/monstartup.0
E 14
I 14
install: maninstall

D 15
.include <bsd.man.mk>
E 15
I 15
.include <bsd.prog.mk>
E 15
E 14
D 13
	rm -f ${MDIR}/setbuffer.0; ln ${MDIR}/setbuf.0 ${MDIR}/setbuffer.0
	rm -f ${MDIR}/setlinebuf.0; ln ${MDIR}/setbuf.0 ${MDIR}/setlinebuf.0
	rm -f ${MDIR}/sprintf.0; ln ${MDIR}/printf.0 ${MDIR}/sprintf.0
	rm -f ${MDIR}/fprintf.0; ln ${MDIR}/printf.0 ${MDIR}/fprintf.0
	rm -f ${MDIR}/vprintf.0; ln ${MDIR}/printf.0 ${MDIR}/vprintf.0
	rm -f ${MDIR}/vsprintf.0; ln ${MDIR}/printf.0 ${MDIR}/vsprintf.0
	rm -f ${MDIR}/vfprintf.0; ln ${MDIR}/printf.0 ${MDIR}/vfprintf.0
	rm -f ${MDIR}/sys_siglist.0; ln ${MDIR}/psignal.0 ${MDIR}/sys_siglist.0
	rm -f ${MDIR}/ttyslot.0; ln ${MDIR}/ttyname.0 ${MDIR}/ttyslot.0
	rm -f ${MDIR}/gamma.0; ln ${MDIR}/lgamma.0 ${MDIR}/gamma.0
	rm -f ${MDIR}/endfsent.0; ln ${MDIR}/getfsent.0 ${MDIR}/endfsent.0
	rm -f ${MDIR}/endgrent.0; ln ${MDIR}/getgrent.0 ${MDIR}/endgrent.0
	rm -f ${MDIR}/endpwent.0; ln ${MDIR}/getpwent.0 ${MDIR}/endpwent.0
	rm -f ${MDIR}/getfsfile.0; ln ${MDIR}/getfsent.0 ${MDIR}/getfsfile.0
	rm -f ${MDIR}/getfsspec.0; ln ${MDIR}/getfsent.0 ${MDIR}/getfsspec.0
	rm -f ${MDIR}/getfstype.0; ln ${MDIR}/getfsent.0 ${MDIR}/getfstype.0
	rm -f ${MDIR}/getgrgid.0; ln ${MDIR}/getgrent.0 ${MDIR}/getgrgid.0
	rm -f ${MDIR}/getgrnam.0; ln ${MDIR}/getgrent.0 ${MDIR}/getgrnam.0
	rm -f ${MDIR}/getpwnam.0; ln ${MDIR}/getpwent.0 ${MDIR}/getpwnam.0
	rm -f ${MDIR}/getpwuid.0; ln ${MDIR}/getpwent.0 ${MDIR}/getpwuid.0
	rm -f ${MDIR}/setfsent.0; ln ${MDIR}/getfsent.0 ${MDIR}/setfsent.0
	rm -f ${MDIR}/setgrent.0; ln ${MDIR}/getgrent.0 ${MDIR}/setgrent.0
	rm -f ${MDIR}/setgrfile.0; ln ${MDIR}/getgrent.0 ${MDIR}/setgrfile.0
	rm -f ${MDIR}/setpwent.0; ln ${MDIR}/getpwent.0 ${MDIR}/setpwent.0
	rm -f ${MDIR}/setpwfile.0; ln ${MDIR}/getpwent.0 ${MDIR}/setpwfile.0
	rm -f ${MDIR}/tgetent.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetent.0
	rm -f ${MDIR}/tgetflag.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetflag.0
	rm -f ${MDIR}/tgetnum.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetnum.0
	rm -f ${MDIR}/tgetstr.0; ln ${MDIR}/termcap.0 ${MDIR}/tgetstr.0
	rm -f ${MDIR}/tgoto.0; ln ${MDIR}/termcap.0 ${MDIR}/tgoto.0
	rm -f ${MDIR}/tputs.0; ln ${MDIR}/termcap.0 ${MDIR}/tputs.0
	rm -f ${MDIR}/closedir.0; ln ${MDIR}/directory.0 ${MDIR}/closedir.0
	rm -f ${MDIR}/dirfd.0; ln ${MDIR}/directory.0 ${MDIR}/dirfd.0
	rm -f ${MDIR}/endttyent.0; ln ${MDIR}/getttyent.0 ${MDIR}/endttyent.0
	rm -f ${MDIR}/getttynam.0; ln ${MDIR}/getttyent.0 ${MDIR}/getttynam.0
	rm -f ${MDIR}/opendir.0; ln ${MDIR}/directory.0 ${MDIR}/opendir.0
	rm -f ${MDIR}/readdir.0; ln ${MDIR}/directory.0 ${MDIR}/readdir.0
	rm -f ${MDIR}/rewinddir.0; ln ${MDIR}/directory.0 ${MDIR}/rewinddir.0
	rm -f ${MDIR}/seekdir.0; ln ${MDIR}/directory.0 ${MDIR}/seekdir.0
	rm -f ${MDIR}/setttyent.0; ln ${MDIR}/getttyent.0 ${MDIR}/setttyent.0
	rm -f ${MDIR}/telldir.0; ln ${MDIR}/directory.0 ${MDIR}/telldir.0
	rm -f ${MDIR}/endnetent.0; ln ${MDIR}/getnetent.0 ${MDIR}/endnetent.0
	rm -f ${MDIR}/getnetbyaddr.0; ln ${MDIR}/getnetent.0 ${MDIR}/getnetbyaddr.0
	rm -f ${MDIR}/getnetbyname.0; ln ${MDIR}/getnetent.0 ${MDIR}/getnetbyname.0
	rm -f ${MDIR}/htonl.0; ln ${MDIR}/byteorder.0 ${MDIR}/htonl.0
	rm -f ${MDIR}/htons.0; ln ${MDIR}/byteorder.0 ${MDIR}/htons.0
	rm -f ${MDIR}/ntohl.0; ln ${MDIR}/byteorder.0 ${MDIR}/ntohl.0
	rm -f ${MDIR}/ntohs.0; ln ${MDIR}/byteorder.0 ${MDIR}/ntohs.0
	rm -f ${MDIR}/setnetent.0; ln ${MDIR}/getnetent.0 ${MDIR}/setnetent.0
	rm -f ${MDIR}/endservent.0; ln ${MDIR}/getservent.0 ${MDIR}/endservent.0
	rm -f ${MDIR}/getservbyname.0; ln ${MDIR}/getservent.0 ${MDIR}/getservbyname.0
	rm -f ${MDIR}/getservbyport.0; ln ${MDIR}/getservent.0 ${MDIR}/getservbyport.0
	rm -f ${MDIR}/setservent.0; ln ${MDIR}/getservent.0 ${MDIR}/setservent.0
	rm -f ${MDIR}/endprotoent.0; ln ${MDIR}/getprotoent.0 ${MDIR}/endprotoent.0
	rm -f ${MDIR}/endusershell.0; ln ${MDIR}/getusershell.0 ${MDIR}/endusershell.0
	rm -f ${MDIR}/getprotobyname.0; ln ${MDIR}/getprotoent.0 ${MDIR}/getprotobyname.0
	rm -f ${MDIR}/getprotobynumber.0; ln ${MDIR}/getprotoent.0 ${MDIR}/getprotobynumber.0
	rm -f ${MDIR}/setprotoent.0; ln ${MDIR}/getprotoent.0 ${MDIR}/setprotoent.0
	rm -f ${MDIR}/setusershell.0; ln ${MDIR}/getusershell.0 ${MDIR}/setusershell.0
	rm -f ${MDIR}/endhostent.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/endhostent.0
	rm -f ${MDIR}/gethostbyaddr.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/gethostbyaddr.0
	rm -f ${MDIR}/sethostent.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/sethostent.0
	rm -f ${MDIR}/sethostfile.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/sethostfile.0
	rm -f ${MDIR}/gethostent.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/gethostent.0
	rm -f ${MDIR}/herror.0; ln ${MDIR}/gethostbyname.0 ${MDIR}/herror.0
	rm -f ${MDIR}/ftw.0; ln ${MDIR}/treewalk.0 ${MDIR}/ftw.0
	rm -f ${MDIR}/memccpy.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/memccpy.0
	rm -f ${MDIR}/memchr.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/memchr.0
	rm -f ${MDIR}/memcmp.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/memcmp.0
	rm -f ${MDIR}/memcpy.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/memcpy.0
	rm -f ${MDIR}/memset.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/memset.0
	rm -f ${MDIR}/strchr.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/strchr.0
	rm -f ${MDIR}/strcspn.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/strcspn.0
	rm -f ${MDIR}/strpbrk.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/strpbrk.0
	rm -f ${MDIR}/strrchr.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/strrchr.0
	rm -f ${MDIR}/strspn.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/strspn.0
	rm -f ${MDIR}/strdup.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/strdup.0
	rm -f ${MDIR}/strsep.0; ln ${MDIR}/strtok.0 ${MDIR}/strsep.0
	rm -f ${MDIR}/strtol.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/strtol.0
	rm -f ${MDIR}/tmpnam.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/tmpnam.0
	rm -f ${MDIR}/tmpfile.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/tmpfile.0
	rm -f ${MDIR}/tempnam.0; ln ${MDIR}/compat-sys5.0 ${MDIR}/tempnam.0
E 13
E 12
E 6
E 5
D 11

FRC:
E 11
E 1
