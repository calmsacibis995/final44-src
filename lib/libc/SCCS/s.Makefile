h58122
s 00001/00001/00050
d D 8.2 94/02/03 07:18:05 bostic 55 54
c add index.c to the list of kernel sources for the Sparc
e
s 00000/00000/00051
d D 8.1 93/06/12 16:37:45 bostic 54 53
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00050
d D 5.10 93/06/12 16:37:25 bostic 53 51
c clean the tags file
e
s 00000/00000/00050
d R 8.1 93/06/04 12:11:18 bostic 52 51
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00049
d D 5.9 92/08/05 15:15:54 bostic 51 50
c add regex directory
e
s 00010/00003/00039
d D 5.8 92/07/12 15:49:16 torek 50 49
c allow machine-specific libkern sources
e
s 00003/00001/00039
d D 5.7 92/07/10 17:26:34 mckusick 49 47
c create gmon subdirectory
e
s 00001/00001/00039
d R 5.7 92/07/08 23:42:32 torek 48 47
c add to KSRCS, rather than replacing, so that we can have
c machine-specific libkern source files (for the sparc)
e
s 00001/00001/00039
d D 5.6 92/07/06 17:32:08 torek 47 46
c fix tags install
e
s 00010/00002/00030
d D 5.5 92/06/25 08:02:06 bostic 46 45
c split libkern into two parts, quad, non-quad; build tags in obj
e
s 00001/00000/00031
d D 5.4 92/06/02 16:04:58 bostic 45 44
c add quad library
e
s 00001/00001/00030
d D 5.3 91/11/12 11:10:03 bostic 44 43
c typo
e
s 00009/00005/00022
d D 5.2 91/03/05 16:23:03 bostic 43 42
c add db, locale; don't need to specially sort the library any more;
c make tags work
e
s 00005/00004/00022
d D 5.1 91/01/20 21:44:04 bostic 42 41
c checkpoint
e
s 00007/00382/00019
d D 4.40 90/06/25 00:56:37 bostic 41 40
c break up into subdirectory makefiles: Makefile.inc
e
s 00108/00056/00293
d D 4.39 90/06/23 11:07:19 bostic 40 39
c checkpoint before trying to break up into subdirectories
e
s 00175/00114/00174
d D 4.38 90/06/07 17:52:59 bostic 39 38
c checkpoint -- major changes.  Move machine directories up one level
c redo distribution, adding stdlib, add hp300, i386 suport, generate most 
c system calls, add GNU cc support routines for the hp300
e
s 00272/00104/00016
d D 4.37 90/05/11 12:49:38 bostic 38 37
c first pass for new make
e
s 00033/00000/00087
d D 4.36 90/03/19 16:10:26 mckusick 37 36
c code to create compilation directories or links 
c (this delta should probably go away eventually)
e
s 00045/00064/00042
d D 4.35 90/03/19 16:08:54 bostic 36 35
c new filesystem organization
e
s 00010/00005/00096
d D 4.34 88/07/09 11:10:44 bostic 35 34
c install approved copyright notice
e
s 00002/00005/00099
d D 4.33 88/06/04 10:19:18 bostic 34 33
c add compat-sys5.${MACHINE}; minor cleanups
e
s 00002/00001/00102
d D 4.32 88/05/25 17:41:50 bostic 33 32
c make tags by default, install tags on install:
e
s 00009/00002/00094
d D 4.31 88/05/24 08:56:13 bostic 32 31
c fix tags 
e
s 00045/00043/00051
d D 4.30 88/05/24 08:35:11 bostic 31 30
c restructure libc
e
s 00001/00001/00093
d D 4.29 88/05/19 17:50:26 bostic 30 29
c create compat-4.3
e
s 00001/00001/00093
d D 4.28 87/12/31 17:23:50 bostic 29 28
c remove libraries on clean
e
s 00001/00002/00093
d D 4.27 87/09/23 11:19:55 bostic 28 27
c just do rm -rf and don't bother ignoring exit
e
s 00003/00004/00092
d D 4.26 87/06/06 15:25:01 bostic 27 26
c install owner/group bin
e
s 00001/00001/00095
d D 4.25 87/05/30 14:24:50 bostic 26 25
c removed MACHINE/csu from depend list
e
s 00000/00004/00096
d D 4.24 87/05/28 18:16:27 bostic 25 24
c machine now defined in make
e
s 00001/00000/00099
d D 4.23 87/04/03 14:02:59 karels 24 23
x 22
c need hostlib
e
s 00000/00001/00098
d D 4.22 87/03/18 16:30:42 bostic 23 22
c install doesn't install tags, for make build
e
s 00002/00002/00097
d D 4.21 87/03/11 21:58:18 bostic 22 21
c changed install to include tags
e
s 00004/00001/00095
d D 4.20 86/10/13 17:14:36 sam 21 20
c we are tahoe
e
s 00005/00002/00091
d D 4.19 86/03/09 22:16:55 donn 20 19
c Change -Dlint feature (delete sccsid's) into LIBC_SCCS feature (preserve
c sccsid's).
e
s 00002/00002/00091
d D 4.18 86/03/08 19:55:00 kjd 19 18
c fix comment, Name server is two words
e
s 00004/00005/00089
d D 4.17 86/01/29 15:42:09 sklower 18 16
c Add xns addr conversion routines, make default named, fix bug in making tags.
e
s 00003/00004/00090
d R 4.17 86/01/29 15:37:05 sklower 17 16
c add xns i/o routines to libc, make named default for hostinfo.
e
s 00001/00000/00093
d D 4.16 85/09/15 14:58:21 bloom 16 15
c Make sure tmp is clean before building library
e
s 00015/00016/00078
d D 4.15 85/09/06 18:38:48 bloom 15 14
c cleanup comments, fix make clean, add make depend
e
s 00017/00012/00077
d D 4.14 85/09/04 18:56:32 bloom 14 13
c fix for proper host name lookup
e
s 00020/00000/00069
d D 4.13 85/07/12 15:50:26 kjd 13 12
c Add verable RESOLVE to determine which resolver is used
e
s 00005/00001/00064
d D 4.12 85/06/19 15:30:10 mckusick 12 11
c allow elimination of sccsid's
e
s 00000/00001/00065
d D 4.11 85/05/30 23:09:31 sam 11 10
c don't sort tags at this level
e
s 00012/00005/00054
d D 4.10 85/05/30 22:34:14 sam 10 9
c add tags
e
s 00008/00003/00051
d D 4.9 85/05/30 21:21:10 sam 9 8
c ci for ralph; rearrange libc dependency (exit follows findiop); add copyright
e
s 00001/00001/00053
d D 4.8 85/01/08 10:10:14 bloom 8 7
c fakcu.o added to libc.a twice instead of to libc_p.a
e
s 00002/00000/00052
d D 4.7 84/11/13 15:10:54 karels 7 6
c add fake cleanup()
e
s 00004/00003/00048
d D 4.6 83/07/02 23:53:33 root 6 5
c put str*n in sys5 compat library
c *** CHANGED *** 83/07/02 23:55:03 root
c make install work properly (sam)
e
s 00030/00031/00021
d D 4.5 83/06/27 18:24:55 root 5 4
c new organization
e
s 00009/00008/00043
d D 4.4 82/12/17 17:33:07 sam 4 3
c clean didn't work
e
s 00001/00001/00050
d D 4.3 82/12/15 22:03:50 clemc 3 2
c Fixed a bug so the mkdir tmp will not case an abort if the directory
c already exists.  Clem
e
s 00013/00014/00038
d D 4.2 82/12/04 18:38:28 mckusick 2 1
c changes to reintroduce mon.o
e
s 00052/00000/00000
d D 4.1 82/12/03 22:03:53 mckusick 1 0
c date and time created 82/12/03 22:03:53 by mckusick
e
u
U
t
T
I 13
D 18

E 18
E 13
I 1
D 4
#	%W%	(Berkeley)	%E%
E 4
I 4
D 6
#	%W%	{Berkeley}	%E%
E 6
I 6
D 9
#	%M%	%I%	%E%
E 9
E 6
E 4
D 38
#
I 9
D 31
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 31
I 31
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
E 31
#
I 31
# Redistribution and use in source and binary forms are permitted
D 35
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 35
I 35
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
E 35
#
E 38
E 31
#	%W% (Berkeley) %G%
I 38
#
# All library objects contain sccsid strings by default; they may be
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, delete -DLIBC_SCCS and -DSYSLIBC_SCCS
# from CFLAGS below.  To remove these strings from just the system call
# stubs, remove just -DSYSLIBC_SCCS from CFLAGS.
LIB=c
CFLAGS+=-DLIBC_SCCS -DSYSLIBC_SCCS
D 39
AINC=	-I${.CURDIR}/${MACHINE} -I${.CURDIR}/sys/${MACHINE}
E 39
I 39
AINC=	-I${.CURDIR}/${MACHINE}
I 53
CLEANFILES+=tags
E 53
E 39
E 38
D 36
#
I 13
D 31
#
E 13
E 9
I 2
D 5
#	The system has two monitoring schemes, utilizing either ``prof''
#	or ``gprof''. DFLMON determines the default profiler; mon.o
#	specifies that ``prof'' is the default, gmon.o specifies that
#	``gprof'' is the default.
E 5
I 5
# The system has two monitoring schemes, utilizing either ``prof''
# or ``gprof''. DFLMON determines the default profiler; mon.o
# specifies that ``prof'' is the default, gmon.o specifies that
# ``gprof'' is the default.
E 5
#
I 5
# Machine dependent routines are located in a subtree which parallels
# the top directories.  This subtree is identified by the machine name.
#
E 31
D 6
# Compatibility routines are kept in directories with a trailing ``compat''
E 6
I 6
# Compatibility routines are kept in directories with a prefixing
# ``compat'' (so they all sort together).
E 6
# 
# The C run-time startup code is always machine dependent and expected
# to be located in ${MACHINE}/csu
#
I 12
D 20
# All files contain sccsid strings. To compile a library that does
# not include these strings one must add -Dlint to DEFS below.
E 20
I 20
D 31
# All files contain sccsid strings, but these are not compiled into
# library objects by default, as a space-saving measure.  To produce
# a library that contains these strings in every object except
# system call stubs, add -DLIBC_SCCS to DEFS below; to put these
# strings into system call stubs, use -DSYSLIBC_SCCS.
E 20
#
E 31
I 13
D 15
#*********************************************************************
#=====================================================================
#							
E 15
D 14
# There are two types of resolvers, 'res_named' which uses the 
#  nameserver and 'res_static' which uses /etc/hosts.
E 14
I 14
# There are two possible methods of doing host name look up.  They are
D 15
# to use the nameserver or /etc/hosts.
E 14
#
D 14
#	RESOLVER defines which resolver is to be compiled into libc  
E 14
I 14
#	HOSTLOOKUP defines which method is to be compiled into libc  
E 15
I 15
D 19
# to use the nameserver or /etc/hosts. HOSTLOOKUP defines which method
E 19
I 19
# to use the name server or /etc/hosts. HOSTLOOKUP defines which method
E 19
# is to be compiled into libc  :
E 15
E 14
#								     
D 14
#		defining RESOLVER to res_named, compiles the         
E 14
I 14
D 15
#		defining HOSTLOOKUP to be "named", compiles the         
E 14
#		routines which the BIND nameserver uses into libc    
#---------------------------------------------------------------------
D 14
#RESOLVER=	res_named
E 14
I 14
#HOSTLOOKUP=	named
E 14
#---------------------------------------------------------------------
D 14
#		defining RESOLVER to res_static, compiles            #
#		the routines which use the old method of             #
#		hostname resolveing. (ie /etc/HOSTS )                #
E 14
I 14
#		defining HOSTLOOKUP to "hosttable", compiles
#		the routines which use the old method of
#		hostname lookup. (ie /etc/hosts )
E 14
#---------------------------------------------------------------------
E 15
I 15
#	defining HOSTLOOKUP to be "named", compiles the         
D 19
#	host lookup routines that use the BIND nameserver.
E 19
I 19
#	host lookup routines that use the BIND name server.
E 19
#
#	defining HOSTLOOKUP to be "hosttable", compiles
#	the host lookup routines that use /etc/hosts.
#
E 15
D 14
RESOLVER=	res_static
E 14
I 14
D 18
HOSTLOOKUP=	hosttable
I 15
#HOSTLOOKUP=	named
E 18
I 18
#HOSTLOOKUP=	hosttable
HOSTLOOKUP=	named
E 18
D 27
#							
E 27
I 27
#
E 36
I 36

I 42
D 44
.include "${.CURDIR}/compat-43/Makefile.inc"
E 44
I 43
.include "${.CURDIR}/db/Makefile.inc"
I 44
.include "${.CURDIR}/compat-43/Makefile.inc"
E 44
E 43
E 42
D 38
# The C run-time startup code is machine dependent and found in csu.
E 38
I 38
D 39
.PATH:	${.CURDIR}/gen/${MACHINE} ${.CURDIR}/gen ${.CURDIR}/gen/regexp \
	${.CURDIR}/sys/${MACHINE} ${.CURDIR}/sys \
	${.CURDIR}/stdio/${MACHINE} ${.CURDIR}/stdio \
	${.CURDIR}/net/${MACHINE} ${.CURDIR}/net \
	${.CURDIR}/string/${MACHINE} ${.CURDIR}/string \
	${.CURDIR}/sys5/${MACHINE} ${.CURDIR}/sys5 \
	${.CURDIR}/compat-43/${MACHINE} ${.CURDIR}/compat-43
E 39
I 39
D 41
.PATH:	${.CURDIR}/${MACHINE}/gen	${.CURDIR}/gen ${.CURDIR}/gen/regexp \
	${.CURDIR}/${MACHINE}/sys	${.CURDIR}/sys \
	${.CURDIR}/${MACHINE}/stdio	${.CURDIR}/stdio \
	${.CURDIR}/${MACHINE}/stdlib	${.CURDIR}/stdlib \
	${.CURDIR}/${MACHINE}/net	${.CURDIR}/net \
	${.CURDIR}/${MACHINE}/string	${.CURDIR}/string \
D 40
	${.CURDIR}/${MACHINE}/sys5	${.CURDIR}/sys5 \
E 40
	${.CURDIR}/${MACHINE}/compat-43	${.CURDIR}/compat-43
E 39
E 38

E 36
E 27
E 15
E 14
E 13
E 12
E 5
E 2
D 31
DESTDIR=
I 2
D 27
INSTALL=install -m 644
E 27
D 4
DFLMON=mon.o
E 4
I 4
DFLMON=	mon.o
D 5
ALL=	csu sys gen stdio net
E 5
I 5
D 21
MACHINE=vax
E 21
I 21
D 25
#ifdef vax
#MACHINE=vax
#endif
MACHINE=tahoe
E 25
E 21
I 12
DEFS=
E 12
D 6
COPMAT=	4.1compat
E 6
I 6
D 30
COMPAT=	compat-4.1 compat-sys5
E 30
I 30
COMPAT=	compat-4.1 compat-4.3 compat-sys5
E 30
E 6
D 18
ALL=	gen inet net stdio ${MACHINE} ${COMPAT}
E 18
I 18
ALL=	gen inet net ns stdio ${MACHINE} ${COMPAT}
E 31
I 31
D 38
# The system has two monitoring schemes, utilizing either ``prof''
# or ``gprof''. DFLMON determines the default profiler; mon.o
# specifies that ``prof'' is the default, gmon.o specifies that
# ``gprof'' is the default.
#DFLMON=	gmon.o
DFLMON=		mon.o
E 38
I 38
# compat-43 sources
D 40
SRCS=	creat.c killpg.c sigcompat.c
E 40
I 40
SRCS+=	creat.c killpg.c sigcompat.c
E 40
E 38
D 36
#
# All library object contain sccsid strings by default; they may be
E 36
I 36

D 38
# All library objects contain sccsid strings by default; they may be
E 36
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, remove -DLIBC_SCCS and -DSYSLIBC_SCCS
# from DEFS below.  To remove these strings from just the system call
# stubs, remove -DSYSLIBC_SCCS from DEFS below.
#DEFS=
DEFS="-DLIBC_SCCS -DSYSLIBC_SCCS"
E 38
I 38
MAN2+=	creat.0 killpg.0 sigblock.0 sigpause.0 sigsetmask.0 sigvec.0
E 38

I 39
# stdlib sources
SRCS+=	abort.c atexit.c atoi.c atol.c bsearch.c calloc.c div.c exit.c \
	getenv.c labs.c ldiv.c malloc.c putenv.c qsort.c rand.c setenv.c \
	strtol.c strtoul.c system.c

.if   (${MACHINE} == "hp300")
SRCS+=	abs.s atof.c
.elif (${MACHINE} == "i386")
SRCS+=	abs.s atof.c
.elif (${MACHINE} == "tahoe")
SRCS+=	abs.s atof.s
.elif (${MACHINE} == "vax")
SRCS+=	abs.s atof.s
.endif

MAN3+=	abort.0 abs.0 atexit.0 atof.0 atoi.0 atol.0 bsearch.0 div.0 \
	exit.0 getenv.0 labs.0 ldiv.0 malloc.0 qsort.0 rand.0 strtod.0 \
	strtol.0 strtoul.0 system.0

MLINKS+=malloc.3 alloca.3 malloc.3 calloc.3 malloc.3 free.3 malloc.3 realloc.3
MLINKS+=getenv.3 setenv.3 getenv.3 unsetenv.3 getenv.3 putenv.3
MLINKS+=rand.3 srand.3

E 39
D 34
ALL=	compat-4.1 compat-4.1/compat-4.1.${MACHINE} compat-4.3 \
	compat-sys5 gen gen/gen.${MACHINE} inet net net/net.${MACHINE} \
	net/${HOSTLOOKUP} ns stdio stdio/stdio.${MACHINE} \
	${MACHINE}/csu ${MACHINE}/sys
E 34
D 36
SUBDIR=	${ALL} net/hosttable net/named
I 32
ONE=	compat-4.1 compat-4.3 compat-sys5 gen inet net ns stdio
TWO=	compat-4.1/compat-4.1.${MACHINE} gen/gen.${MACHINE} \
	net/net.${MACHINE} net/${HOSTLOOKUP} stdio/stdio.${MACHINE} \
D 34
	${MACHINE}/csu ${MACHINE}/sys
E 34
I 34
	compat-sys5/compat-sys5.${MACHINE} ${MACHINE}/csu ${MACHINE}/sys
ALL=	${ONE} ${TWO}
E 36
I 36
D 38
CSU=	csu
I 37
ROOTOBJDIR=/usr/${OBJDIR}
E 37
SRCDIR=	compat-43 gen net stdio string sys sys5
SUBDIR=	${CSU} ${SRCDIR}
E 36
E 34
E 32
E 31
E 18
I 10
TAGSFILE=tags
I 36
TPATH=`pwd`/${TAGSFILE}
E 38
I 38
# gen sources
D 39
SRCS+=	_setjmp.s abort.c abs.s alarm.c alloca.s calloc.c cencode.c \
	clock.c closedir.c crypt.c ctime.c ctype_.c difftime.c \
	disklabel.c errlst.c execvp.c fabs.s fakcu.c fstab.c \
	genbuildname.c getenv.c getgrent.c getlogin.c getmntinfo.c \
	getpass.c getpwent.c getttyent.c getusershell.c getwd.c \
	initgroups.c insque.s isatty.c isctype.c ldexp.s \
	malloc.c modf.s nargs.s ndbm.c nice.c nlist.c opendir.c pause.c \
	perror.c popen.c psignal.c qsort.c random.c readdir.c regerror.c \
	regex.c regexp.c remove.c remque.s scandir.c seekdir.c setegid.c \
	setenv.c seteuid.c setgid.c setjmp.s setjmperr.c setmode.c \
	setrgid.c setruid.c setuid.c siglist.c signal.c sleep.c syslog.c \
	system.c telldir.c termios.c time.c timezone.c ttyname.c \
	ttyslot.c ualarm.c udiv.s urem.s usleep.c valloc.c wait.c \
	wait3.c waitpid.c
E 39
I 39
SRCS+=	alarm.c clock.c closedir.c crypt.c ctime.c ctype_.c difftime.c \
D 40
	disklabel.c errlst.c execvp.c fakcu.c fnmatch.c fstab.c \
	genbuildname.c getgrent.c getlogin.c getmntinfo.c getpass.c \
E 40
I 40
	disklabel.c errlst.c execvp.c fakcu.c fnmatch.c fstab.c fts.c \
	genbuildname.c getgrent.c getlogin.c getmntinfo.c getopt.c getpass.c \
E 40
	getpwent.c getttyent.c getusershell.c getwd.c glob.c initgroups.c \
D 40
	isatty.c isctype.c mktemp.c ndbm.c nice.c nlist.c \
	opendir.c pause.c perror.c popen.c psignal.c random.c readdir.c \
	regex.c remove.c rewinddir.c scandir.c seekdir.c \
	setegid.c seteuid.c setgid.c setjmperr.c setmode.c setrgid.c \
	setruid.c setuid.c siginterrupt.c sigsetjmp.c siglist.c signal.c \
E 40
I 40
	isatty.c isctype.c mktemp.c ndbm.c nice.c nlist.c opendir.c \
	pause.c perror.c popen.c psignal.c random.c readdir.c regex.c \
	remove.c rewinddir.c scandir.c seekdir.c setjmperr.c setmode.c \
	setrgid.c setruid.c siginterrupt.c sigsetjmp.c siglist.c signal.c \
E 40
	sigset.c sleep.c syslog.c telldir.c termios.c time.c timezone.c \
D 40
	ttyname.c ttyslot.c ualarm.c unvis.c usleep.c valloc.c vis.c \
E 40
I 40
	tmpnam.c ttyname.c ttyslot.c ualarm.c unvis.c usleep.c valloc.c vis.c \
E 40
	wait.c wait3.c waitpid.c
E 39
E 38
E 36
E 10
E 5
E 4
E 2

D 2
INSTALL=mv

all: libc.a libc_p.a crtx

libc.a libc_p.a:
E 2
I 2
D 4
libc.a libc_p.a: csu sys gen stdio net
E 4
I 4
D 5
libc.a libc_p.a: ${ALL}
E 4
	cd csu; make
E 2
	cd sys; make
	cd gen; make
	cd stdio; make
	cd net; make
E 5
I 5
D 14
libc.a libc_p.a: ${MACHINE}/csu ${ALL}
E 14
I 14
D 31
libc.a libc_p.a: ${MACHINE}/csu ${ALL} net/${HOSTLOOKUP}
I 16
	rm -rf t1 tmp
E 16
E 14
E 5
D 3
	mkdir tmp
E 3
I 3
	-mkdir tmp
E 3
D 5
	cd tmp; ar x ../sys/syslib
	cd tmp; ar x ../gen/genlib
	cd tmp; ar x ../stdio/stdiolib
	cd tmp; ar x ../net/netlib
E 5
I 5
	for i in ${ALL}; do (cd tmp; ar x ../$$i/$${i}lib); done
I 14
	cd tmp; ar x ../net/${HOSTLOOKUP}/hostlib
E 14
E 5
	ls tmp/*.o | sort -t/ +1 > t1
E 31
I 31
D 33
libc.a libc_p.a: mkdir ${ALL}
E 33
I 33
D 36
libc.a libc_p.a: mkdir ${ALL} tags
E 33
	ls library/*.o | sort -t/ +1 > t1
E 31
D 2
	ar ar libc.a `lorder \`cat t1\` | tsort`;
E 2
I 2
D 5
	ar cr libc.a `lorder \`cat t1\` | tsort` csu/${DFLMON}
E 5
I 5
	ar cr libc.a `lorder \`cat t1\` | tsort` ${MACHINE}/csu/${DFLMON}
E 5
E 2
D 9
	ar ma flsbuf.o libc.a exit.o
E 9
I 9
	ar ma findiop.o libc.a exit.o
E 9
I 7
	ar ma exit.o libc.a fakcu.o
E 7
D 31
	rm -f t1 tmp/*
D 5
	cd tmp; ar x ../sys/syslib_p
	cd tmp; ar x ../gen/genlib_p
	cd tmp; ar x ../stdio/stdiolib_p
	cd tmp; ar x ../net/netlib_p
E 5
I 5
	for i in ${ALL}; do (cd tmp; ar x ../$$i/$${i}lib_p); done
I 14
	cd tmp; ar x ../net/${HOSTLOOKUP}/hostlib_p
E 14
E 5
	ls tmp/*.o | sort -t/ +1 > t1
E 31
I 31
	ls profiled/*.o | sort -t/ +1 > t1
E 31
D 2
	ar ar libc_p.a `lorder \`cat t1\` | tsort`;
E 2
I 2
D 5
	ar cr libc_p.a `lorder \`cat t1\` | tsort` csu/${DFLMON}
E 5
I 5
	ar cr libc_p.a `lorder \`cat t1\` | tsort` ${MACHINE}/csu/${DFLMON}
E 5
E 2
D 9
	ar ma flsbuf.o libc_p.a exit.o
E 9
I 9
	ar ma findiop.o libc_p.a exit.o
E 9
I 7
D 8
	ar ma exit.o libc.a fakcu.o
E 8
I 8
	ar ma exit.o libc_p.a fakcu.o
E 8
E 7
D 31
	rm -rf t1 tmp
E 31
I 31
	rm -rf t1 library profiled
E 36
I 36
D 38
all: library ${SUBDIR}
	cd library; ls *.o | sort > t1; \
	ar cr libc.a `lorder \`cat t1\` | tsort` ../csu/${MACHINE}/${DFLMON}; \
	ar ma findiop.o libc.a exit.o; \
	ar ma exit.o libc.a fakcu.o; \
	rm -f t1
	cd profiled; ls *.o | sort > t1; \
	ar cr libc_p.a `lorder \`cat t1\` | tsort` ../csu/${MACHINE}/${DFLMON}; \
	ar ma findiop.o libc_p.a exit.o; \
	ar ma exit.o libc_p.a fakcu.o; \
	rm -f t1
E 38
I 38
D 39
.if (${MACHINE} == "tahoe")
SRCS+=	frexp.c
E 39
I 39
SRCS+=	regerror.c regexp.c regsub.c

.if   (${MACHINE} == "hp300")
SRCS+=	_setjmp.s alloca.s fabs.s frexp.s insque.s ldexp.s modf.s remque.s \
	setjmp.s
SRCS+=	adddf3.s addsf3.s ashlsi3.s ashrsi3.s cmpdf2.s cmpsf2.s divdf3.s \
	divsf3.s divsi3.s eprintf.c extendsfdf2.s fixdfsi.s fixunsdfsi.s \
	floatsidf.s lshlsi3.s lshrsi3.s modsi3.s muldf3.s mulsf3.s mulsi3.s \
	negdf2.s negsf2.s saveregs.c subdf3.s subsf3.s truncdfsf2.s udivsi3.s \
	umodsi3.s umulsi3.s
.elif (${MACHINE} == "i386")
SRCS+=	_setjmp.s alloca.s fabs.s frexp.c insque.c ldexp.c modf.c remque.c \
	setjmp.s
SRCS+=	divsi3.s fixdfsi.c udivsi3.s
.elif (${MACHINE} == "tahoe")
SRCS+=	_setjmp.s alloca.s fabs.s frexp.c insque.s ldexp.s modf.s remque.s \
	setjmp.s
SRCS+=	udiv.s urem.s
E 39
.elif (${MACHINE} == "vax")
D 39
SRCS+=	frexp.s
E 39
I 39
SRCS+=	_setjmp.s alloca.s fabs.s frexp.s insque.s ldexp.s modf.s remque.s \
	setjmp.s
SRCS+=	udiv.s urem.s
E 39
.endif
E 38
I 37

D 38
library:
	@echo 'must "make dirs" or "make links"'; exit 1
E 38
I 38
D 39
MAN3+=	abort.0 alarm.0 cencode.0 clock.0 crypt.0 ctime.0 ctype.0 \
	directory.0 execvp.0 frexp.0 genbuildname.0 getdiskbyname.0 \
	getenv.0 getfsent.0 getgrent.0 getlogin.0 getmntinfo.0 \
	getpass.0 getpwent.0 getttyent.0 getusershell.0 getwd.0 \
	initgroups.0 insque.0 malloc.0 ndbm.0 nice.0 nlist.0 \
	pause.0 perror.0 popen.0 psignal.0 qsort.0 random.0 regex.0 \
	regexp.0 scandir.0 setjmp.0 setmode.0 setuid.0 siginterrupt.0 \
	signal.0 sleep.0 syslog.0 system.0 time.0 ttyname.0 ualarm.0 \
	usleep.0 valloc.0
E 39
I 39
MAN3+=	alarm.0 clock.0 crypt.0 ctime.0 ctype.0 directory.0 execvp.0 \
D 40
	fnmatch.0 frexp.0 genbuildname.0 getdiskbyname.0 getfsent.0 \
	getgrent.0 getlogin.0 getmntinfo.0 getpass.0 getpwent.0 getttyent.0 \
	getusershell.0 getwd.0 glob.0 initgroups.0 insque.0 mktemp.0 \
	ndbm.0 nice.0 nlist.0 pause.0 perror.0 popen.0 psignal.0 random.0 \
	regex.0 regexp.0 scandir.0 setjmp.0 setmode.0 setuid.0 \
	siginterrupt.0 signal.0 sleep.0 syslog.0 time.0 ttyname.0 ualarm.0 \
	unvis.0 usleep.0 valloc.0 vis.0
E 40
I 40
	fnmatch.0 frexp.0 fts.0 genbuildname.0 getdiskbyname.0 getfsent.0 \
	getgrent.0 getlogin.0 getmntinfo.0 getopt.0 getpass.0 getpwent.0 \
	getttyent.0 getusershell.0 getwd.0 glob.0 initgroups.0 insque.0 \
	mktemp.0 ndbm.0 nice.0 nlist.0 pause.0 perror.0 popen.0 psignal.0 \
	random.0 regex.0 regexp.0 scandir.0 setjmp.0 setmode.0 setuid.0 \
	siginterrupt.0 signal.0 sleep.0 syslog.0 time.0 tmpnam.0 ttyname.0 \
	ualarm.0 unvis.0 usleep.0 valloc.0 vis.0
E 40
E 39
E 38

D 38
dirs:
	rm -rf library
	mkdir library
	rm -rf profiled
	mkdir profiled
	for i in ${SRCDIR} ${CSU}/${MACHINE}; \
		do (cd $$i; make ${MFLAGS} clean; \
		rm -rf profiled obj; \
		mkdir profiled); done
E 38
I 38
MLINKS=	crypt.3 encrypt.3 crypt.3 setkey.3
MLINKS+=ctime.3 asctime.3 ctime.3 difftime.3 ctime.3 gmtime.3 \
	ctime.3 localtime.3 ctime.3 timezone.3 ctime.3 tzset.3
MLINKS+=ctype.3 toascii.3 ctype.3 tolower.3 ctype.3 toupper.3 \
	ctype.3 isalnum.3 ctype.3 isalpha.3 ctype.3 isascii.3 \
	ctype.3 iscntrl.3 ctype.3 isdigit.3 ctype.3 isgraph.3 \
	ctype.3 islower.3 ctype.3 isprint.3 ctype.3 ispunct.3 \
	ctype.3 isspace.3 ctype.3 isupper.3 ctype.3 isxdigit.3
MLINKS+=directory.3 closedir.3 directory.3 dirfd.3 directory.3 opendir.3 \
	directory.3 readdir.3 directory.3 rewinddir.3 directory.3 seekdir.3 \
	directory.3 telldir.3
MLINKS+=execvp.3 execle.3 execvp.3 execlp.3 execvp.3 exect.3 \
	execvp.3 execv.3 execvp.3 execve.3 execvp.3 execl.3 \
	execvp.3 exec.3
MLINKS+=frexp.3 ldexp.3 frexp.3 modf.3
D 39
MLINKS+=getenv.3 setenv.3 getenv.3 unsetenv.3 getenv.3 putenv.3
E 39
MLINKS+=getfsent.3 endfsent.3 getfsent.3 getfsfile.3 getfsent.3 getfsspec.3 \
	getfsent.3 getfstype.3 getfsent.3 setfsent.3
MLINKS+=getgrent.3 endgrent.3 getgrent.3 setgroupent.3 getgrent.3 getgrgid.3 \
	getgrent.3 getgrnam.3 getgrent.3 setgrent.3 getgrent.3 setgrfile.3
MLINKS+=getpwent.3 endpwent.3 getpwent.3 setpassent.3 getpwent.3 getpwnam.3 \
	getpwent.3 getpwuid.3 getpwent.3 setpwent.3 getpwent.3 setpwfile.3
MLINKS+=getttyent.3 endttyent.3 getttyent.3 getttynam.3 getttyent.3 setttyent.3
MLINKS+=getusershell.3 endusershell.3 getusershell.3 setusershell.3
I 39
MLINKS+=glob.3 globfree.3
E 39
MLINKS+=insque.3 remque.3
D 39
MLINKS+=malloc.3 alloca.3 malloc.3 calloc.3 malloc.3 free.3 malloc.3 realloc.3
E 39
I 39
MLINKS+=mktemp.3 mkstemp.3
E 39
MLINKS+=ndbm.3 dbm_clearerr.3 ndbm.3 dbm_close.3 ndbm.3 dbm_delete.3 \
	ndbm.3 dbm_error.3 ndbm.3 dbm_fetch.3 ndbm.3 dbm_firstkey.3 \
	ndbm.3 dbm_nextkey.3 ndbm.3 dbm_open.3 ndbm.3 dbm_store.3
MLINKS+=perror.3 strerror.3 perror.3 sys_errlist.3 perror.3 sys_nerr.3
MLINKS+=popen.3 pclose.3
MLINKS+=psignal.3 sys_siglist.3
MLINKS+=random.3 initstate.3 random.3 setstate.3 random.3 srandom.3
MLINKS+=regex.3 re_comp.3 regex.3 re_exec.3 regexp.3 regcomp.3 \
	regexp.3 regexec.3 regexp.3 regsub.3 regexp.3 regerror.3
MLINKS+=scandir.3 alphasort.3
D 39
MLINKS+=setjmp.3 _longjmp.3 setjmp.3 _setjmp.3 setjmp.3 longjmp.3
E 39
I 39
MLINKS+=setjmp.3 _longjmp.3 setjmp.3 _setjmp.3 setjmp.3 longjmp.3 \
	setjmp.3 longjmperr.3
E 39
MLINKS+=setuid.3 setegid.3 setuid.3 seteuid.3 setuid.3 setgid.3 \
	setuid.3 setrgid.3 setuid.3 setruid.3
MLINKS+=syslog.3 closelog.3 syslog.3 openlog.3 syslog.3 setlogmask.3 \
	syslog.3 vsyslog.3
MLINKS+=ttyname.3 isatty.3 ttyname.3 ttyslot.3
MLINKS+=setmode.3 getmode.3
E 38

D 38
links:
	-if [ ! -d ${ROOTOBJDIR}lib/libc/library ]; then \
		mkdir -p ${ROOTOBJDIR}lib/libc/library; fi
	rm -rf library
	ln -s ${ROOTOBJDIR}lib/libc/library library
	-if [ ! -d ${ROOTOBJDIR}lib/libc/profiled ]; then \
		mkdir -p ${ROOTOBJDIR}lib/libc/profiled; fi
	rm -rf profiled
	ln -s ${ROOTOBJDIR}lib/libc/profiled profiled
	for i in ${SRCDIR} ${CSU}/${MACHINE}; \
		do (cd $$i; make ${MFLAGS} clean; \
		rm -rf profiled obj; \
		if [ ! -d ${ROOTOBJDIR}lib/libc/$$i ]; then \
			mkdir -p ${ROOTOBJDIR}lib/libc/$$i; fi; \
		ln -s ${ROOTOBJDIR}lib/libc/$$i obj; \
		if [ ! -d ${ROOTOBJDIR}lib/libc/$$i/profiled ]; then \
			mkdir -p ${ROOTOBJDIR}lib/libc/$$i/profiled; fi; \
		ln -s ${ROOTOBJDIR}lib/libc/$$i/profiled profiled); done
E 38
I 38
# net sources
SRCS+=	gethostnamadr.c getnetbyaddr.c getnetbyname.c getnetent.c \
	getproto.c getprotoent.c getprotoname.c getservbyname.c \
D 39
	getservbyport.c getservent.c herror.c htonl.s htons.s \
	inet_addr.c inet_lnaof.c inet_makeaddr.c inet_netof.c \
	inet_network.c inet_ntoa.c iso_addr.c ns_addr.c ns_ntoa.c \
	ntohl.s ntohs.s rcmd.c recv.c res_comp.c res_debug.c res_init.c \
	res_mkquery.c res_query.c res_send.c send.c sethostent.c
E 39
I 39
	getservbyport.c getservent.c herror.c inet_addr.c inet_lnaof.c \
	inet_makeaddr.c inet_netof.c inet_network.c inet_ntoa.c \
	iso_addr.c linkaddr.c ns_addr.c ns_ntoa.c rcmd.c recv.c res_comp.c \
	res_debug.c res_init.c res_mkquery.c res_query.c res_send.c \
	send.c sethostent.c
E 39
E 38
E 37
E 36
E 31

I 39
.if   (${MACHINE} == "hp300")
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
.elif (${MACHINE} == "i386")
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
.elif (${MACHINE} == "tahoe")
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
.elif (${MACHINE} == "vax")
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
.endif

E 39
D 2
crtx:
	cd csu; make

E 2
D 5
clean:
D 4
	for i in */.; do cd $$i; make clean; cd ..; done
E 4
I 4
	for i in ${ALL}; do cd $$i; make clean; cd ..; done
E 4
	rm -f t1 *.o
E 5
I 5
D 14
${MACHINE}/csu ${ALL}: FRC
E 14
I 14
D 31
${MACHINE}/csu ${ALL} net/${HOSTLOOKUP}: FRC
E 14
D 12
	cd $@; make ${MFLAGS}
E 12
I 12
	cd $@; make ${MFLAGS} DEFS=${DEFS}
E 31
I 31
D 36
mkdir: FRC
	rm -rf library profiled
	mkdir library profiled
E 36
I 36
D 38
${SUBDIR}: FRC
	cd $@; make ${MFLAGS} DEFS=${DEFS}
E 38
I 38
MAN3+=	byteorder.0 gethostbyname.0 getnetent.0 getprotoent.0 getservent.0 \
	inet.0 ns.0 rcmd.0 resolver.0 \
E 38
E 36
E 31
E 12
E 5

D 5
errlst.o: gen/errlst.c
	cc -S gen/errlst.c
	ed - <gen/:errfix errlst.s
	as -o errlst.o errlst.s
	rm errlst.s
E 5
I 5
D 31
FRC:
E 31
I 31
D 36
${ALL}: FRC
	cd $@; make ${MFLAGS} DEFS=${DEFS} link
E 31
E 5

D 2
install: all
E 2
I 2
D 5
install: libc.a libc_p.a
E 5
I 5
D 10
clean:
	for i in ${MACHINE}/csu ${ALL}; do (cd $$i; make ${MFLAGS} clean); done
	rm -f t1 tmp/*.o
	-rmdir tmp

E 10
install: 
E 5
E 2
D 4
	$(INSTALL) libc.a $(DESTDIR)/lib/libc.a
	ranlib $(DESTDIR)/lib/libc.a
	$(INSTALL) libc_p.a $(DESTDIR)/usr/lib/libc_p.a
	ranlib $(DESTDIR)/usr/lib/libc_p.a
E 4
I 4
D 27
	${INSTALL} libc.a ${DESTDIR}/lib/libc.a
E 27
I 27
	install -o bin -g bin -m 644 libc.a ${DESTDIR}/lib/libc.a
E 27
	ranlib ${DESTDIR}/lib/libc.a
D 27
	${INSTALL} libc_p.a ${DESTDIR}/usr/lib/libc_p.a
E 27
I 27
	install -o bin -g bin -m 644 libc_p.a ${DESTDIR}/usr/lib/libc_p.a
E 27
	ranlib ${DESTDIR}/usr/lib/libc_p.a
E 4
D 2
	cd csu; $(INSTALL) crt0.o $(DESTDIR)/lib
	cd csu; $(INSTALL) mcrt0.o $(DESTDIR)/lib
	cd csu; $(INSTALL) gcrt0.o $(DESTDIR)/usr/lib
E 2
I 2
D 5
	cd csu; make DESTDIR=${DESTDIR} install
E 5
I 5
	cd ${MACHINE}/csu; make DESTDIR=${DESTDIR} install
I 33
	install -o bin -g bin -m 444 ${TAGSFILE} ${DESTDIR}/usr/lib/${TAGSFILE}
E 33
I 22
D 23
	install -c ${TAGSFILE} ${DESTDIR}/usr/lib/${TAGSFILE}
E 23
E 22
I 10

tags:
D 32
	for i in ${ALL}; do \
D 31
		(cd $$i; make ${MFLAGS} TAGSFILE=../${TAGSFILE} tags); \
E 31
I 31
		(cd $$i; make ${MFLAGS} TAGSFILE=`pwd`/${TAGSFILE} tags); \
E 32
I 32
	for i in ${ONE}; do \
		(cd $$i; make ${MFLAGS} TAGSFILE=../${TAGSFILE} tags); \
	done
	for i in ${TWO}; do \
		(cd $$i; make ${MFLAGS} TAGSFILE=../../${TAGSFILE} tags); \
E 32
E 31
I 18
	done
E 18
I 14
D 22
D 31
	cd net/${HOSTLOOKUP}; \
		make ${MFLAGS} TAGSFILE=../../${TAGSFILE} tags
E 31
I 24
	sort -o ${TAGSFILE} ${TAGSFILE}
E 24
E 22
I 22
	/usr/bin/sort -o ${TAGSFILE} ${TAGSFILE}
E 22
E 14
D 18
	done
E 18
D 11
	sort -u +0 -1 tags -o tags
E 11

E 36
D 38
clean:
D 14
	for i in ${MACHINE}/csu ${ALL}; do (cd $$i; make ${MFLAGS} clean); done
E 14
I 14
D 15
	for i in ${MACHINE}/csu ${ALL} net/${HOSTLOOKUP}; \
E 15
I 15
D 31
	for i in ${MACHINE}/csu ${ALL} net/hosttable net/named; \
E 31
I 31
	for i in ${SUBDIR}; \
E 31
E 15
		do (cd $$i; make ${MFLAGS} clean); done
E 14
D 28
	rm -f t1 tmp/*.o
	-rmdir tmp
E 28
I 28
D 29
	rm -rf tmp t1
E 29
I 29
D 31
	rm -rf tmp t1 libc.a libc_p.a
E 31
I 31
D 36
	rm -rf libc.a libc_p.a library profiled
E 36
I 36
	rm -rf library/libc.a profiled/libc_p.a
E 38
I 38
MLINKS+=byteorder.3 htonl.3 byteorder.3 htons.3 byteorder.3 ntohl.3 \
	byteorder.3 ntohs.3
MLINKS+=gethostbyname.3 endhostent.3 gethostbyname.3 gethostbyaddr.3 \
	gethostbyname.3 sethostent.3 gethostbyname.3 sethostfile.3 \
	gethostbyname.3 gethostent.3 gethostbyname.3 herror.3
MLINKS+=getnetent.3 endnetent.3 getnetent.3 getnetbyaddr.3 \
	getnetent.3 getnetbyname.3 getnetent.3 setnetent.3
MLINKS+=getprotoent.3 endprotoent.3 getprotoent.3 getprotobyname.3 \
	getprotoent.3 getprotobynumber.3 getprotoent.3 setprotoent.3
MLINKS+=getservent.3 endservent.3 getservent.3 getservbyname.3 \
	getservent.3 getservbyport.3 getservent.3 setservent.3
MLINKS+=inet.3 addr.3 inet.3 inet_addr.3 inet.3 inet_lnaof.3 \
	inet.3 inet_makeaddr.3 inet.3 inet_netof.3 inet.3 inet_network.3 \
	inet.3 inet_ntoa.3 inet.3 network.3 inet.3 ntoa.3
MLINKS+=ns.3 ns_addr.3 ns.3 ns_ntoa.3
MLINKS+=rcmd.3 rresvport.3 rcmd.3 ruserok.3
E 38
E 36
E 31
E 29
E 28
I 15

I 36
D 38
cleandir: clean
	for i in ${SUBDIR}; \
		do (cd $$i; make ${MFLAGS} cleandir); done
E 38
I 38
# stdio sources
D 39
SRCS+=	clrerr.c doprnt.c doscan.c exit.c fdopen.c fgetc.c filbuf.c \
	findiop.c flsbuf.c fopen.c fprintf.c fputc.c fread.c freopen.c \
	fseek.c ftell.c fwrite.c getchar.c gets.c getw.c printf.c \
	putchar.c putw.c rew.c scanf.c setbuf.c setbuffer.c sprintf.c \
	ungetc.c vfprintf.c vprintf.c vsprintf.c
E 39
I 39
SRCS+=	clrerr.c doprnt.c doscan.c fdopen.c fgetc.c filbuf.c findiop.c \
	flsbuf.c fopen.c fprintf.c fputc.c fread.c freopen.c fseek.c \
	ftell.c fwrite.c getchar.c gets.c getw.c printf.c putchar.c \
	putw.c rew.c scanf.c setbuf.c setbuffer.c sprintf.c ungetc.c \
	vfprintf.c vprintf.c vsprintf.c
E 39
E 38

E 36
D 38
depend:
D 26
	for i in ${MACHINE}/csu ${ALL} net/hosttable net/named; \
E 26
I 26
D 31
	for i in ${ALL} net/hosttable net/named; \
E 31
I 31
	for i in ${SUBDIR}; \
E 31
E 26
D 36
		do (cd $$i; make ${MFLAGS} DEFS=${DEFS} depend); done
E 36
I 36
		do (cd $$i; make ${MFLAGS} DEFS=${DEFS} $@); done
E 38
I 38
D 39
.if (${MACHINE} == "vax")
SRCS+=	fgets.s fputs.s puts.s
.else
E 39
I 39
.if   (${MACHINE} == "hp300")
E 39
SRCS+=	fgets.c fputs.c puts.c
I 39
.elif (${MACHINE} == "i386")
SRCS+=	fgets.c fputs.c puts.c
.elif (${MACHINE} == "tahoe")
SRCS+=	fgets.c fputs.c puts.c
.elif (${MACHINE} == "vax")
SRCS+=	fgets.s fputs.s puts.s
E 39
.endif
E 38
E 36
I 31

D 36
FRC:
E 36
I 36
D 38
install: tags
	install -o bin -g bin -m 644 library/libc.a ${DESTDIR}/usr/lib/libc.a
	ranlib ${DESTDIR}/usr/lib/libc.a
	install -o bin -g bin -m 644 profiled/libc_p.a ${DESTDIR}/usr/lib/libc_p.a
	ranlib ${DESTDIR}/usr/lib/libc_p.a
	for i in ${SUBDIR}; \
		do (cd $$i; make DEFS=${DEFS} $@); done
	install -o bin -g bin -m 444 ${TAGSFILE} ${DESTDIR}/usr/libdata
E 38
I 38
D 39
MAN3+=	exit.0 fclose.0 ferror.0 fgets.0 fopen.0 fread.0 fseek.0 getc.0 \
E 39
I 39
MAN3+=	fclose.0 ferror.0 fgets.0 fopen.0 fread.0 fseek.0 getc.0 \
E 39
	gets.0 printf.0 putc.0 puts.0 scanf.0 setbuf.0 stdio.0 ungetc.0 \
E 38
E 36

I 36
D 38
tags:
	for i in ${SUBDIR}; do \
		(cd $$i; make TAGSFILE=tags tags); done
	rm -f tags
	for i in ${SUBDIR}; do \
		cat $$i/tags >> tags; done
	sort -o tags tags
E 38
I 38
MLINKS+=fclose.3 fflush.3
MLINKS+=ferror.3 clearerr.3 ferror.3 feof.3 ferror.3 fileno.3
MLINKS+=fopen.3 fdopen.3 fopen.3 freopen.3
MLINKS+=fread.3 fwrite.3
MLINKS+=fseek.3 ftell.3 fseek.3 rewind.3
MLINKS+=getc.3 fgetc.3 getc.3 getchar.3 getc.3 getw.3
MLINKS+=printf.3 fprintf.3 printf.3 sprintf.3 printf.3 vfprintf.3 \
	printf.3 vprintf.3 printf.3 vsprintf.3
MLINKS+=putc.3 fputc.3 putc.3 putchar.3 putc.3 putw.3
MLINKS+=puts.3 fputs.3
MLINKS+=scanf.3 fscanf.3 scanf.3 sscanf.3
MLINKS+=setbuf.3 setbuffer.3 setbuf.3 setlinebuf.3
E 38

D 38
FRC:
E 38
I 38
# string sources
D 39
SRCS+=	atof.s atoi.c atol.c bcmp.s bcopy.s bzero.s ffs.s fnmatch.c \
	mktemp.c strcasecmp.c strcat.s strcmp.s strcpy.s strerror.c \
	strftime.c strlen.s strmode.c strncat.s strncmp.s strncpy.s swab.c
E 39
I 39
D 40
SRCS+=	memccpy.c memcpy.c strcasecmp.c strcoll.c strdup.c strerror.c \
E 40
I 40
SRCS+=	memccpy.c strcasecmp.c strcoll.c strdup.c strerror.c \
E 40
	strftime.c strmode.c strtok.c strxfrm.c swab.c
E 39

D 39
.if (${MACHINE} == "vax")
SRCS+=	index.s rindex.s
.else
SRCS+=	index.c rindex.c
E 39
I 39
.if   (${MACHINE} == "hp300")
D 40
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.s memchr.c memcmp.c memmove.c \
	memset.c rindex.s strcat.c strchr.c strcmp.s strcpy.s strcspn.c \
	strlen.s strncat.c strncmp.s strncpy.s strpbrk.c strrchr.c strsep.c \
	strspn.c strstr.c
E 40
I 40
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.s memchr.c memcmp.c memset.c \
	rindex.s strcat.c strcmp.s strcpy.s strcspn.c strlen.s \
	strncat.c strncmp.s strncpy.s strpbrk.c strsep.c \
	strstr.c strstr.c
E 40
.elif (${MACHINE} == "i386")
D 40
SRCS+=	bcmp.c bcopy.c bzero.s ffs.c index.c memchr.c memcmp.c memmove.c \
	memset.c rindex.c strcat.c strchr.c strcmp.c strcpy.c strcspn.c \
	strlen.c strncat.c strncmp.c strncpy.c strpbrk.c strrchr.c strsep.c \
E 40
I 40
SRCS+=	bcmp.c bcopy.c bzero.s ffs.c index.c memchr.c memcmp.c memset.c \
	rindex.c strcat.c strcmp.c strcpy.c strcspn.c strlen.c \
	strncat.c strncmp.c strncpy.c strpbrk.c strsep.c \
E 40
	strspn.c strstr.c
.elif (${MACHINE} == "tahoe")
D 40
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.c memcmp.s memmove.s \
	memset.s rindex.c strcat.s strchr.c strcmp.s strcpy.s strcspn.c \
	strlen.s strncat.s strncmp.s strncpy.s strpbrk.c strrchr.c strsep.c \
E 40
I 40
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.c memcmp.s memset.s \
	rindex.c strcat.s strcmp.s strcpy.s strcspn.c strlen.s \
	strncat.s strncmp.s strncpy.s strpbrk.c strsep.c \
E 40
	strspn.c strstr.c
I 40
#SRCS+=	memmove.s
E 40
.elif (${MACHINE} == "vax")
D 40
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.s memcmp.s memmove.s \
	memset.s rindex.s strcat.s strchr.s strcmp.s strcpy.s strcspn.s \
	strlen.s strncat.s strncmp.s strncpy.s strpbrk.s strrchr.s strsep.s \
E 40
I 40
SRCS+=	bcmp.s bcopy.s bzero.s ffs.s index.c memchr.s memcmp.s memset.s \
	rindex.s strcat.s strcmp.s strcpy.s strcspn.s strlen.s \
	strncat.s strncmp.s strncpy.s strpbrk.s strsep.s \
E 40
	strspn.s strstr.s
I 40
SRCS+=	memmove.s strchr.s strrchr.s
E 40
E 39
.endif

I 40
# if no machine specific memmove(3), build one out of bcopy(3).
.if empty(SRCS:Mmemmove.s)
OBJS+=	memmove.o
memmove.o: bcopy.c
	${CC} -DMEMMOVE ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

memmove.po: bcopy.c
	${CC} -DMEMMOVE ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

# if no machine specific memcpy(3), build one out of bcopy(3).
.if empty(SRCS:Mmemcpy.s)
OBJS+=	memcpy.o
memcpy.o: bcopy.c
	${CC} -DMEMCOPY ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

memcpy.po: bcopy.c
	${CC} -DMEMCOPY ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

# if no machine specific strchr(3), build one out of index(3).
.if empty(SRCS:Mstrchr.s)
OBJS+=	strchr.o
strchr.o: index.c
	${CC} -DSTRCHR ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

strchr.po: index.c
	${CC} -DSTRCHR ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

# if no machine specific strrchr(3), build one out of rindex(3).
.if empty(SRCS:Mstrrchr.s)
OBJS+=	strrchr.o
strrchr.o: rindex.c
	${CC} -DSTRRCHR ${CFLAGS} -c ${.ALLSRC} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}

strrchr.po: rindex.c
	${CC} -DSTRRCHR ${CFLAGS} -c -p ${.ALLSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif

E 40
D 39
MAN3+=	atof.0 bstring.0 fnmatch.0 glob.0 mktemp.0 strftime.0 string.0 \
	strmode.0 strtok.0 swab.0 \
E 39
I 39
MAN3+=	bcmp.0 bcopy.0 bstring.0 bzero.0 ffs.0 index.0 memccpy.0 memchr.0 \
	memcmp.0 memcpy.0 memmove.0 memset.0 rindex.0 strcasecmp.0 strcat.0 \
	strchr.0 strcmp.0 strcoll.0 strcpy.0 strcspn.0 strftime.0 string.0 \
D 40
	strlen.0 strmode.0 strncasecmp.0 strncat.0 strncmp.0 strncpy.0 \
	strpbrk.0 strrchr.0 strsep.0 strspn.0 strstr.0 strtok.0 strxfrm.0 \
	swab.0
E 40
I 40
	strlen.0 strmode.0 strdup.0 strncasecmp.0 strncat.0 strncmp.0 \
	strncpy.0 strpbrk.0 strrchr.0 strsep.0 strspn.0 strstr.0 strtok.0 \
	strxfrm.0 swab.0
E 40
E 39

D 39
MLINKS+=atof.3 atoi.3 atof.3 atol.3
MLINKS+=bstring.3 bcmp.3 bstring.3 bcopy.3 bstring.3 bzero.3 \
	bstring.3 ffs.3
MLINKS+=string.3 index.3 string.3 rindex.3 string.3 strcat.3 \
	string.3 strcmp.3 string.3 strcpy.3 string.3 strlen.3 \
	string.3 strncat.3 string.3 strncmp.3 string.3 strcasecmp.3 \
	string.3 strncasecmp.3 string.3 strncpy.3
MLINKS+=strtok.3 strsep.3
MLINKS+=glob.3 globfree.3
MLINKS+=mktemp.3 mkstemp.3

E 39
# sys sources
I 40
# modules with non-default implementations on at least one architecture:
E 40
D 39
SRCS+=	Ovadvise.s Ovfork.s _exit.s _getlogin.s accept.s access.s \
	acct.s adjtime.s async_daemon.s bind.s brk.s cerror.s chdir.s \
	chflags.s chmod.s chown.s chroot.s close.s connect.s dup.s \
	dup2.s execl.s execle.s exect.s execv.s execve.s fchdir.s \
	fchflags.s fchmod.s fchown.s fcntl.s flock.s fork.s fstat.s \
	fstatfs.s fsync.s ftruncate.s getdirentries.s getdtablesize.s \
	getegid.s geteuid.s getfh.s getfsstat.s getgid.s getgroups.s \
	gethostid.s gethostname.s getitimer.s getkerninfo.s \
	getpagesize.s getpeername.s getpgrp.s getpid.s getppid.s \
	getpriority.s getrlimit.s getrusage.s getsockname.s getsockopt.s \
	gettimeofday.s getuid.s ioctl.s kill.s ktrace.s link.s listen.s \
	lseek.s lstat.s mkdir.s mkfifo.s mknod.s mmap.s mount.s nfssvc.s \
	open.s pipe.s profil.s ptrace.s quotactl.s read.s readlink.s \
	readv.s reboot.s recvfrom.s recvmsg.s rename.s rmdir.s sbrk.s \
	select.s sendmsg.s sendto.s setgroups.s sethostid.s \
	sethostname.s setitimer.s setlogin.s setpgrp.s setpriority.s \
	setregid.s setreuid.s setrlimit.s setsid.s \
	setsockopt.s settimeofday.s shutdown.s sigaction.s sigpending.s \
	sigprocmask.s sigreturn.s sigstack.s sigsuspend.s socket.s \
	socketpair.s stat.s statfs.s swapon.s symlink.s sync.s syscall.s \
	truncate.s umask.s unlink.s unmount.s utimes.s vhangup.s \
	wait4.s write.s writev.s
E 39
I 39
SRCS+=	Ovfork.s _exit.s _getlogin.s brk.s cerror.s execl.s execle.s exect.s \
D 40
	execv.s fork.s getegid.s geteuid.s getppid.s pipe.s ptrace.s reboot.s \
	sbrk.s setlogin.s sigpending.s sigprocmask.s sigreturn.s sigsuspend.s \
	syscall.s
E 40
I 40
	execv.s fork.s pipe.s ptrace.s reboot.s sbrk.s setlogin.s \
	sigpending.s sigprocmask.s sigreturn.s sigsuspend.s syscall.s
E 40
E 39

I 40
# modules with default implementations on all architectures:
E 40
I 39
BLDASM=	accept.o access.o acct.o adjtime.o async_daemon.o bind.o chdir.o \
	chflags.o chmod.o chown.o chroot.o close.o connect.o dup.o dup2.o \
	execve.o fchdir.o fchflags.o fchmod.o fchown.o fcntl.o flock.o \
	fstat.o fstatfs.o fsync.o ftruncate.o getdirentries.o getdtablesize.o \
D 40
	getfh.o getfsstat.o getgid.o getgroups.o gethostid.o gethostname.o \
	getitimer.o getkerninfo.o getpagesize.o getpeername.o getpgrp.o \
	getpid.o getpriority.o getrlimit.o getrusage.o getsockname.o \
	getsockopt.o gettimeofday.o getuid.o ioctl.o kill.o ktrace.o link.o \
	listen.o lseek.o lstat.o mkdir.o mkfifo.o mknod.o mmap.o mount.o \
	nfssvc.o open.o profil.o quotactl.o read.o readlink.o readv.o \
	recvfrom.o recvmsg.o rename.o revoke.o rmdir.o select.o sendmsg.o \
	sendto.o setgroups.o sethostid.o sethostname.o setitimer.o setpgrp.o \
	setpriority.o setregid.o setreuid.o setrlimit.o setsid.o \
	setsockopt.o settimeofday.o shutdown.o sigaction.o sigstack.o \
	socket.o socketpair.o stat.o statfs.o swapon.o symlink.o sync.o \
	truncate.o umask.o unlink.o unmount.o utimes.o vadvise.o wait4.o \
	write.o writev.o
E 40
I 40
	getegid.o geteuid.o getfh.o getfsstat.o getgid.o getgroups.o \
	gethostid.o gethostname.o getitimer.o getkerninfo.o getpagesize.o \
	getpeername.o getpgrp.o getpid.o getppid.o getpriority.o getrlimit.o \
	getrusage.o getsockname.o getsockopt.o gettimeofday.o getuid.o \
	ioctl.o kill.o ktrace.o link.o listen.o lseek.o lstat.o mkdir.o \
	mkfifo.o mknod.o mmap.o mount.o nfssvc.o open.o profil.o quotactl.o \
	read.o readlink.o readv.o recvfrom.o recvmsg.o rename.o revoke.o \
	rmdir.o select.o sendmsg.o sendto.o setegid.o seteuid.o setgid.o \
	setgroups.o sethostid.o sethostname.o setitimer.o setpgrp.o \
	setpriority.o setregid.o setreuid.o setrlimit.o setsid.o setsockopt.o \
	settimeofday.o setuid.o shutdown.o sigaction.o sigstack.o socket.o \
	socketpair.o stat.o statfs.o swapon.o symlink.o sync.o truncate.o \
	umask.o unlink.o unmount.o utimes.o vadvise.o wait4.o write.o writev.o
E 40

OBJS+=	${BLDASM}
POBJS+=	${BLDASM:.o=.po}
CLEANFILES+=${BLDASM} ${BLDASM:.o=.po}

D 40
${BLDASM}:
E 40
I 40
${BLDASM}: /usr/include/sys/syscall.h
E 40
	@echo creating ${.PREFIX}.o
	@printf '#include "SYS.h"\nSYSCALL(${.PREFIX})\nret\n' | \
	    ${CPP} ${CFLAGS:M-[ID]*} ${AINC} | ${AS} -o ${.PREFIX}.o
	@${LD} -x -r ${.PREFIX}.o
	@mv a.out ${.PREFIX}.o
	@echo creating ${.PREFIX}.po
	@printf '#include "SYS.h"\nSYSCALL(${.PREFIX})\nret\n' | \
	    ${CPP} -DPROF ${CFLAGS:M-[ID]*} ${AINC} | ${AS} -o ${.PREFIX}.po
	@${LD} -x -r ${.PREFIX}.po
	@mv a.out ${.PREFIX}.po

E 39
MAN2+=	accept.0 access.0 acct.0 adjtime.0 async_daemon.0 bind.0 brk.0 \
	chdir.0 chflags.0 chmod.0 chown.0 chroot.0 close.0 connect.0 \
D 39
	dup.0 execve.0 exit.0 fcntl.0 flock.0 fork.0 fsync.0 \
E 39
I 39
	dup.0 execve.0 _exit.0 fcntl.0 flock.0 fork.0 fsync.0 \
E 39
	getdirentries.0 getdtablesize.0 getfh.0 getfsstat.0 getgid.0 \
	getgroups.0 gethostid.0 gethostname.0 getitimer.0 getlogin.0 \
	getpagesize.0 getpeername.0 getpgrp.0 getpid.0 getpriority.0 \
	getrlimit.0 getrusage.0 getsockname.0 getsockopt.0 \
	gettimeofday.0 getuid.0 intro.0 ioctl.0 kill.0 link.0 listen.0 \
	lseek.0 mkdir.0 mkfifo.0 mknod.0 mount.0 nfssvc.0 open.0 pipe.0 \
	profil.0 ptrace.0 quotactl.0 read.0 readlink.0 reboot.0 recv.0 \
	rename.0 rmdir.0 select.0 send.0 setgroups.0 setpgrp.0 \
	setregid.0 setreuid.0 shutdown.0 sigreturn.0 \
	sigstack.0 socket.0 socketpair.0 stat.0 statfs.0 swapon.0 \
	symlink.0 sync.0 syscall.0 truncate.0 umask.0 unlink.0 utimes.0 \
D 39
	vfork.0 vhangup.0 wait.0 write.0
E 39
I 39
	vfork.0 wait.0 write.0
E 39

MLINKS+=brk.2 sbrk.2
MLINKS+=dup.2 dup2.2
MLINKS+=chdir.2 fchdir.2
MLINKS+=chflags.2 fchflags.2
MLINKS+=chmod.2 fchmod.2
MLINKS+=chown.2 fchown.2
MLINKS+=getgid.2 getegid.2
MLINKS+=gethostid.2 sethostid.2
MLINKS+=gethostname.2 sethostname.2
MLINKS+=getitimer.2 setitimer.2
MLINKS+=getlogin.2 setlogin.2
MLINKS+=getpid.2 getppid.2
MLINKS+=getpriority.2 setpriority.2
MLINKS+=getrlimit.2 setrlimit.2
MLINKS+=getsockopt.2 setsockopt.2
MLINKS+=gettimeofday.2 settimeofday.2
MLINKS+=getuid.2 geteuid.2
MLINKS+=intro.2 errno.2
MLINKS+=lseek.2 seek.2
MLINKS+=mount.2 unmount.2
MLINKS+=read.2 readv.2
MLINKS+=recv.2 recvfrom.2 recv.2 recvmsg.2
MLINKS+=send.2 sendmsg.2 send.2 sendto.2
MLINKS+=stat.2 fstat.2 stat.2 lstat.2
MLINKS+=statfs.2 fstatfs.2
MLINKS+=truncate.2 ftruncate.2
MLINKS+=wait.2 wait3.2 wait.2 wait4.2 wait.2 waitpid.2
MLINKS+=write.2 writev.2
D 40

# sys5 sources
D 39
SRCS+=	bsearch.c fts.c getopt.c memccpy.c memchr.c memcmp.c memcpy.c \
	memset.c putenv.c strcspn.c strdup.c strpbrk.c strsep.c strspn.c \
	strtok.c strtol.c strtoul.c tmpnam.c
E 39
I 39
SRCS+=	fts.c getopt.c tmpnam.c
E 39

D 39
.if (${MACHINE} == "vax")
SRCS+=	strchr.s strrchr.s
.else
SRCS+=	strchr.c strrchr.c
.endif

MAN3+=	bsearch.0 compat-sys5.0 fts.0 getopt.0

MLINKS+=compat-sys5.3 memccpy.3 compat-sys5.3 memchr.3 \
	compat-sys5.3 memcmp.3 compat-sys5.3 memcpy.3 \
	compat-sys5.3 memset.3 compat-sys5.3 strchr.3 \
	compat-sys5.3 strcspn.3 compat-sys5.3 strpbrk.3 \
	compat-sys5.3 strrchr.3 compat-sys5.3 strspn.3 \
	compat-sys5.3 strdup.3 compat-sys5.3 strtol.3 \
	compat-sys5.3 tmpnam.3 compat-sys5.3 tmpfile.3 \
	compat-sys5.3 tempnam.3
E 39
I 39
MAN3+=	fts.0 getopt.0
E 40
E 39

errlst.o:
	${CC} -S ${CFLAGS} ${.IMPSRC}
	ed - < ${.CURDIR}/gen/:errfix errlst.s
	${AS} -o errlst.o errlst.s
	cp errlst.o errlst.po
	rm -f errlst.s
E 41
I 41
.include "${.CURDIR}/gen/Makefile.inc"
I 49
.include "${.CURDIR}/gmon/Makefile.inc"
E 49
I 43
.include "${.CURDIR}/locale/Makefile.inc"
E 43
D 42
.include "${.CURDIR}/sys/Makefile.inc"
E 42
I 42
.include "${.CURDIR}/net/Makefile.inc"
I 45
.include "${.CURDIR}/quad/Makefile.inc"
I 51
.include "${.CURDIR}/regex/Makefile.inc"
E 51
E 45
E 42
.include "${.CURDIR}/stdio/Makefile.inc"
.include "${.CURDIR}/stdlib/Makefile.inc"
D 42
.include "${.CURDIR}/net/Makefile.inc"
E 42
.include "${.CURDIR}/string/Makefile.inc"
D 42
.include "${.CURDIR}/compat-43/Makefile.inc"
E 42
I 42
.include "${.CURDIR}/sys/Makefile.inc"
E 42
E 41

I 46
KQSRCS=	adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c iordi3.c \
	lshldi3.c lshrdi3.c moddi3.c muldi3.c negdi2.c notdi2.c qdivrem.c \
	subdi3.c ucmpdi2.c udivdi3.c umoddi3.c xordi3.c
I 50
D 55
KSRCS=	bcmp.c ffs.c mcount.c rindex.c strcat.c strcmp.c strcpy.c \
E 55
I 55
KSRCS=	bcmp.c ffs.c index.c mcount.c rindex.c strcat.c strcmp.c strcpy.c \
E 55
	strlen.c strncpy.c
E 50
D 49
KSRCS=	bcmp.c ffs.c strcat.c strcmp.c strcpy.c strlen.c strncpy.c
E 49
I 49

D 50
KSRCS=	bcmp.c ffs.c mcount.c strcat.c strcmp.c strcpy.c strlen.c strncpy.c
E 50
I 50
libkern: libkern.gen libkern.${MACHINE}
E 50
E 49

D 50
libkern: ${KQSRCS} ${KSRCS}
E 50
I 50
libkern.gen: ${KQSRCS} ${KSRCS}
E 50
	cp -p ${.CURDIR}/quad/quad.h ${.ALLSRC} /sys/libkern
D 50
	
E 50
I 50

libkern.${MACHINE}:: ${KMSRCS}
.if defined(KMSRCS) && !empty(KMSRCS)
	cp -p ${.ALLSRC} /sys/libkern/${MACHINE}
.endif

E 50
E 46
D 42
beforeinstall:
E 42
I 42
beforeinstall: tags
E 42
D 43
	ar ma findiop.o libc.a exit.o
	ar ma exit.o libc.a fakcu.o
	ar ma findiop.po libc_p.a exit.po
	ar ma exit.po libc_p.a fakcu.po
I 42
	install -c -o bin -g bin -m 444 ${.CURDIR}/tags /var/db
E 43
I 43
D 47
	install -c -o bin -g bin -m 444 ${.CURDIR}/tags /var/db/libc.tags
E 47
I 47
	install -c -o bin -g bin -m 444 tags /var/db/libc.tags
E 47

tags: ${SRCS}
D 46
	cd ${.CURDIR}; ctags ${.ALLSRC:M*.c}
	cd ${.CURDIR}; egrep -o "^ENTRY(.*)|^SYSCALL(.*)" ${.ALLSRC:M*.s} | \
E 46
I 46
	ctags ${.ALLSRC:M*.c}
	egrep -o "^ENTRY(.*)|^FUNC(.*)|^SYSCALL(.*)" ${.ALLSRC:M*.s} | \
E 46
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
	    >> tags; sort -o tags tags
E 43
E 42

.include <bsd.lib.mk>
E 38
E 36
E 31
E 15
E 10
E 5
E 2
E 1
