h25079
s 00002/00002/00048
d D 8.3 95/02/14 10:34:48 cgd 22 21
c build syscall files the right way, for new args mechanism.
e
s 00002/00001/00048
d D 8.2 94/03/21 14:47:36 bostic 21 20
c add procfs, union
e
s 00000/00000/00049
d D 8.1 93/06/11 17:38:46 bostic 20 19
c 4.4BSD snapshot (revision 8.1)
e
s 00020/00017/00029
d D 7.18 93/06/11 17:38:25 bostic 19 17
c make tags, links work for 4.4BSD
e
s 00000/00000/00046
d R 8.1 93/06/10 21:55:04 bostic 18 17
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00045
d D 7.17 93/03/28 19:37:49 torek 17 16
c ARCH+=sparc
e
s 00005/00004/00041
d D 7.16 92/07/06 10:10:50 bostic 16 15
c not exactly fix the tags, but make them better anyway
e
s 00006/00010/00039
d D 7.15 92/03/18 18:19:51 karels 15 14
c new way of doing tags
e
s 00001/00001/00048
d D 7.14 91/09/06 15:24:09 ralph 14 13
c add pmax
e
s 00000/00007/00049
d D 7.13 91/05/09 21:15:29 bostic 13 12
c makefiles don't need copyrights
e
s 00037/00093/00019
d D 7.12 91/04/20 14:59:13 karels 12 11
c move machdep into ../$ARCH dirs
e
s 00021/00002/00091
d D 7.11 91/03/24 14:20:37 william 11 10
c (checked in by karels) add i386 tags
e
s 00019/00017/00074
d D 7.10 90/12/25 21:46:35 sklower 10 9
c make tags work
e
s 00001/00001/00090
d D 7.9 90/10/22 15:18:07 mckusick 9 8
c add vm subdirectory
e
s 00020/00006/00071
d D 7.8 90/06/21 22:23:05 karels 8 7
c make links via ../machine for common dirs; hp300;
c dependency on makesyscalls.sh
e
s 00035/00030/00042
d D 7.7 89/08/22 15:25:56 bostic 7 6
c more work on the tags
e
s 00014/00003/00058
d D 7.6 88/10/24 16:44:52 bostic 6 5
c Berkeley copyright
e
s 00012/00013/00049
d D 7.5 87/03/28 12:15:38 bostic 5 4
c cleanup
e
s 00010/00004/00052
d D 7.4 87/03/20 23:35:50 bostic 4 3
c added tags for assembly, fixed links
e
s 00036/00029/00020
d D 7.3 87/03/13 11:09:23 bostic 3 2
c changes to tags
e
s 00001/00001/00048
d D 7.2 87/03/13 00:55:27 bostic 2 1
c added typedefs flag to ctags args
e
s 00049/00000/00000
d D 7.1 86/06/05 21:55:03 mckusick 1 0
c first distributed with 4.3BSD
e
u
U
t
T
I 1
D 13
#
D 6
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
D 12
# Copyright (c) 1986 The Regents of the University of California.
E 12
I 12
# Copyright (c) 1986, 1991 The Regents of the University of California.
E 12
# All rights reserved.
#
D 12
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
D 7
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
# %sccs.include.redist.sh
E 12
E 7
E 6
#
E 13
#	%W% (Berkeley) %G%
D 13
#
E 13
D 7
# Put the ../h stuff near the end so that subroutine definitions win when
E 7
I 7
D 12
# Put the ../sys stuff near the end so that subroutine definitions win when
E 7
# there is a struct tag with the same name (eg., vmmeter).  The real
# solution would probably be for ctags to generate "struct vmmeter" tags.
E 12
D 3
CTAGS=	ctags
SRCS =	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] \
	../netns/*.[ch] ../sys/*.[ch] ../vaxif/*.[ch]  ../vaxmba/*.[ch] \
	../vaxuba/*.[ch] \
	../vax/autoconf.c ../vax/clock.c ../vax/clock.h ../vax/conf.c \
	../vax/cons.c ../vax/cons.h ../vax/cpu.h ../vax/cpudata.c \
	../vax/dkbad.c ../vax/dkio.h ../vax/flp.c ../vax/flp.h \
	../vax/frame.h \
	../vax/genassym.c ../vax/in_cksum.c ../vax/machdep.c \
	../vax/machparam.h ../vax/mem.c \
	../vax/mem.h ../vax/mscp.h ../vax/mtpr.h ../vax/nexus.h \
	../vax/pcb.h ../vax/psl.h ../vax/pte.h ../vax/pup_cksum.c \
	../vax/reg.h \
	../vax/rpb.h ../vax/rpb.s ../vax/rsp.h ../vax/scb.h \
	../vax/scb.s \
	../vax/swapgeneric.c ../vax/sys_machdep.c ../vax/trap.c \
	../vax/trap.h \
	../vax/tu.c ../vax/ufs_machdep.c ../vax/vm_machdep.c \
	../vax/vmparam.h \
	../h/*.h 
E 3
I 3
D 5
CTAGS=	/usr/ucb/ctags
E 5
E 3

I 7
D 12
COMM=	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] ../netns/*.[ch] \
D 9
	../kern/*.[ch] ../ufs/*.[ch] ../nfs/*.[ch]
E 9
I 9
D 10
	../kern/*.[ch] ../ufs/*.[ch] ../nfs/*.[ch] ../vm/*.[ch]
E 9
HDR=	../sys/*.h
E 10
I 10
	../netiso/*.[ch] ../netccitt/*.[ch] \
	../sys/*.h ../kern/*.c ../ufs/*.[ch] ../nfs/*.[ch] ../vm/*.[ch]
E 10
E 7
D 3
DIRS =	h net netimp netinet netns vax vaxif vaxmba vaxuba
E 3
I 3
TVAX=	../vax/tags
D 7
SVAX=	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] ../netns/*.[ch] \
	../sys/*.[ch] ../vaxif/*.[ch]  ../vaxmba/*.[ch] ../vaxuba/*.[ch] \
	../vax/*.[ch] ../h/*.h
E 7
I 7
D 10
SVAX=	../vaxif/*.[ch]  ../vaxmba/*.[ch] ../vaxuba/*.[ch] ../vax/*.[ch]
E 7
AVAX=	../vax/*.s
E 10
I 10
SVAX=	../vax/if/*.[ch]  ../vax/mba/*.[ch] ../vax/uba/*.[ch] \
	../vax/bi/*.[ch] ../vax/vax/*.[ch] ../vax/include/*.h
AVAX=	../vax/vax/*.s
E 12
I 12
D 15
# Makefile for kernel tags files, init_systent, etc.
E 15
I 15
# Makefile for kernel tags files, init_sysent, etc.
E 15
E 12
E 10
E 3

I 3
D 12
TTAHOE=	../tahoe/tags
D 7
STAHOE=	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] ../netns/*.[ch] \
	../sys/*.[ch] ../tahoeif/*.[ch]  ../tahoevba/*.[ch] ../tahoe/*.[ch] \
	../h/*.h
E 7
I 7
D 10
STAHOE=	../tahoeif/*.[ch]  ../tahoevba/*.[ch] ../tahoe/*.[ch]
E 7
ATAHOE=	../tahoe/*.s
E 10
I 10
STAHOE=	../tahoe/if/*.[ch]  ../tahoe/vba/*.[ch] ../tahoe/align/*.[ch] ../tahoe/math/*.h ../tahoe/tahoe/*.[ch] ../tahoe/include/*.h
ATAHOE=	../tahoe/tahoe/*.s ../tahoe/math/*.s
E 12
I 12
D 14
ARCH=	vax tahoe hp300 i386
E 14
I 14
D 17
ARCH=	vax tahoe hp300 i386 pmax
E 17
I 17
D 19
ARCH=	vax tahoe hp300 i386 pmax sparc
E 19
I 19
ARCH=	hp300 i386 luna68k news3400 pmax sparc tahoe vax
E 19
E 17
E 14
E 12
E 10

I 8
D 12
THP300=	../hp300/tags
D 10
SHP300=	 ../hpux/*.[ch]../hpdev/*.[ch] ../hp300/*.[ch]
AHP300=	../hp300/*.s
E 10
I 10
SHP300=	../hp300/hpux/*.[ch] ../hp300/dev/*.[ch] ../hp300/hp300/*.[ch] \
	../hp300/include/*.h
AHP300=	../hp300/hp300/*.s
E 12
I 12
all:
	@echo "make tags, make links or init_sysent.c only"
E 12
E 10

I 11
D 12
TI386=	../i386/tags
SI386=	../i386/isa/*.[ch] ../i386/i386/*.[ch] ../i386/include/*.h
AI386=	../i386/i386/*.s
E 12
I 12
D 22
init_sysent.c syscalls.c ../sys/syscall.h: makesyscalls.sh syscalls.master
E 22
I 22
init_sysent.c syscalls.c ../sys/syscall.h ../sys/syscallargs.h: makesyscalls.sh syscalls.master
E 22
	-mv -f init_sysent.c init_sysent.c.bak
	-mv -f syscalls.c syscalls.c.bak
	-mv -f ../sys/syscall.h ../sys/syscall.h.bak
D 22
	sh makesyscalls.sh syscalls.master
E 22
I 22
	sh makesyscalls.sh syscalls.conf syscalls.master
E 22
E 12

E 11
E 8
D 7
DGEN=	h sys net netimp netinet netns
E 7
I 7
D 12
# Directories in which to place tags links (other than primary T$MACH)
DGEN=	kern sys net netimp netinet netns ufs
E 7
D 10
DVAX=	vaxif vaxmba vaxuba
DTAHOE=	tahoeif tahoevba
I 8
DHP300=	hpdev hpux
E 10
I 10
DVAX=	vax/if vax/mba vax/uba vax/bi vax/vax vax/include
DTAHOE=	tahoe/if tahoe/vba tahoe/align tahoe/math tahoe/include tahoe/tahoe
DHP300=	hp300/dev hp300/hpux hp300/hp300 hp300/include
I 11
DI386=	i386/isa i386/i386 i386/include
E 12
I 12
# Kernel tags:
I 15
# Tags files are built in the top-level directory for each architecture,
D 19
# with a makefile listing the architecture-dependent files, etc.
# The list of common files is in ./Make.tags.inc.  Links to the
# correct tags file are placed in each source directory.
E 15
# We need to have links to tags files from the generic directories
# that are relative to the machine type, even via remote mounts;
# therefore we use symlinks to $SYSTAGS, which points at
E 19
I 19
# with a makefile listing the architecture-dependent files, etc.  The list
# of common files is in ./Make.tags.inc.  Links to the correct tags file
# are placed in each source directory.  We need to have links to tags files
# from the generic directories that are relative to the machine type, even
# via remote mounts; therefore we use symlinks to $SYSTAGS, which points at
E 19
# ${SYSDIR}/${MACHINE}/tags.
E 12
E 11
E 10
E 8

E 3
D 12
all:
	@echo "make tags or links only"
E 12
I 12
SYSTAGS=/var/db/sys_tags
SYSDIR=/sys
E 12

D 7
tags: FRC
D 3
	mv tags tags.old
	-cp ../machine/astags tags
D 2
	${CTAGS} -a ${SRCS}
E 2
I 2
	${CTAGS} -at ${SRCS}
E 2
	sort -o tags.new tags
	mv tags.new tags
	rm -f tags.old
E 3
I 3
	-mv ${TVAX} ${TVAX}.old
D 4
	${CTAGS} -atf ${TVAX} ${SVAX}
	/usr/bin/egrep "^SCBVEC(.*)|^ENTRY(.*)|^JSBENTRY(.*)" ${AVAX} | \
E 4
I 4
D 5
	${CTAGS} -dtf ${TVAX} ${SVAX}
	/usr/bin/egrep "^SCBVEC(.*)" ${AVAX} | \
/bin/sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);X\3 \1 /^\2(\3\4$$/;" \
E 5
I 5
	ctags -dtf ${TVAX} ${SVAX}
	egrep "^SCBVEC(.*)" ${AVAX} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);X\3 \1 /^\2(\3\4$$/;" \
E 5
		>> ${TVAX}
D 5
	/usr/bin/egrep "^ENTRY(.*)|^JSBENTRY(.*)" ${AVAX} | \
E 4
/bin/sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
E 5
I 5
	egrep "^ENTRY(.*)|^JSBENTRY(.*)" ${AVAX} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
E 5
		>> ${TVAX}
D 5
	/usr/bin/sort -o ${TVAX} ${TVAX}
E 5
I 5
	sort -o ${TVAX} ${TVAX}
E 5
	rm -f ${TVAX}.old
	-mv ${TTAHOE} ${TTAHOE}.old
D 4
	${CTAGS} -atf ${TTAHOE} ${STAHOE}
	/usr/bin/egrep "^SCBVEC(.*)|^ENTRY(.*)|^JSBENTRY(.*)" ${ATAHOE} | \
E 4
I 4
D 5
	${CTAGS} -dtf ${TTAHOE} ${STAHOE}
	/usr/bin/egrep "^SCBVEC(.*)" ${ATAHOE} | \
/bin/sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);X\3 \1 /^\2(\3\4$$/;" \
E 5
I 5
	ctags -dtf ${TTAHOE} ${STAHOE}
E 7
I 7
D 8
tags: tahoetags vaxtags
E 8
I 8
D 11
tags: tahoetags vaxtags hp300tags
E 11
I 11
D 12
tags: tahoetags vaxtags hp300tags i386tags
E 12
I 12
D 15
# Put the ../sys stuff near the end so that subroutine definitions win when
# there is a struct tag with the same name (eg., vmmeter).  The real
# solution would probably be for ctags to generate "struct vmmeter" tags.
E 12
E 11
E 8

D 12
tahoetags:
D 10
	-ctags -dtf ${TTAHOE} ${COMM} ${STAHOE} ${HDR}
E 10
I 10
	-ctags -dtf ${TTAHOE} ${COMM} ${STAHOE}
E 10
E 7
	egrep "^SCBVEC(.*)" ${ATAHOE} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);X\3 \1 /^\2(\3\4$$/;" \
E 5
		>> ${TTAHOE}
D 5
	/usr/bin/egrep "^ENTRY(.*)|^JSBENTRY(.*)" ${ATAHOE} | \
E 4
/bin/sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
E 5
I 5
	egrep "^ENTRY(.*)|^JSBENTRY(.*)" ${ATAHOE} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
E 5
		>> ${TTAHOE}
D 5
	/usr/bin/sort -o ${TTAHOE} ${TTAHOE}
E 5
I 5
	sort -o ${TTAHOE} ${TTAHOE}
I 11
	-ln -s /sys/tahoe/tags /var/db/sys_tags
E 12
I 12
COMM=	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] ../netns/*.[ch] \
	../netiso/*.[ch] ../netccitt/*.[ch] \
	../kern/*.c ../ufs/*.[ch] ../nfs/*.[ch] ../vm/*.[ch] ../sys/*.h
E 12
E 11
E 5
D 7
	rm -f ${TTAHOE}.old
E 7
E 3

E 15
I 7
D 12
vaxtags:
D 10
	-ctags -dtf ${TVAX} ${COMM} ${SVAX} ${HDR}
E 10
I 10
	-ctags -dtf ${TVAX} ${COMM} ${SVAX}
E 10
	egrep "^SCBVEC(.*)" ${AVAX} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);X\3 \1 /^\2(\3\4$$/;" \
		>> ${TVAX}
	egrep "^ENTRY(.*)|^JSBENTRY(.*)" ${AVAX} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
		>> ${TVAX}
	sort -o ${TVAX} ${TVAX}
I 11
	-ln -s /sys/vax/tags /var/db/sys_tags
E 12
I 12
# Directories in which to place tags links (other than machine-dependent)
D 16
DGEN=	kern sys net netimp netinet netns netccitt nfs ufs vm
E 16
I 16
D 19
DGEN=	kern sys net netimp netinet netns netccitt nfs ufs/ffs ufs/lfs \
	ufs/mfs ufs/ufs vm
E 19
I 19
DGEN=	conf \
	dev dev/scsi \
	hp hp/dev hp/hpux \
	kern libkern \
	miscfs miscfs/deadfs miscfs/fdesc miscfs/fifofs miscfs/kernfs \
D 21
	miscfs/lofs miscfs/nullfs miscfs/portal miscfs/specfs miscfs/umapfs \
E 21
I 21
	miscfs/lofs miscfs/nullfs miscfs/portal miscfs/procfs \
	miscfs/specfs miscfs/umapfs miscfs/union \
E 21
	net netccitt netinet netiso netns nfs scripts sys \
	ufs ufs/ffs ufs/lfs ufs/mfs ufs/ufs \
	vm
E 19
E 16
E 12
E 11

I 8
D 12
hp300tags:
D 10
	-ctags -dtf ${THP300} ${COMM} ${SHP300} ${HDR}
E 10
I 10
	-ctags -dtf ${THP300} ${COMM} ${SHP300}
E 10
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${AHP300} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
		>> ${THP300}
	sort -o ${THP300} ${THP300}
I 11
	-ln -s /sys/hp300/tags /var/db/sys_tags
E 12
I 12
D 19
tags: FRC
E 19
I 19
tags::
E 19
	-for i in ${ARCH}; do \
D 16
	    cd ../$$i && make ${MFLAGS} tags; done
E 16
I 16
	    (cd ../$$i && make ${MFLAGS} tags); done
E 16
E 12
E 11

I 11
D 12
i386tags:
	-ctags -dtf ${TI386} ${COMM} ${SI386}
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${AI386} | \
sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
		>> ${TI386}
	sort -o ${TI386} ${TI386}
	-ln -s /sys/i386/tags /var/db/sys_tags

E 11
E 8
E 7
links:
D 3
	-for i in ${DIRS}; do rm -f ../$$i/tags; \
	ln -s ../sys/tags ../$$i/tags; done
E 3
I 3
D 7
	-for i in ${DVAX}; do rm -f ../$$i/tags; \
	ln -s ../vax/tags ../$$i/tags; done
	-for i in ${DTAHOE}; do rm -f ../$$i/tags; \
	ln -s ../tahoe/tags ../$$i/tags; done
	-for i in ${DGEN}; do rm -f ../$$i/tags; \
	ln -s ../machine/tags ../$$i/tags; done
E 7
I 7
	-for i in ${DVAX}; do \
D 10
	    rm -f ../$$i/tags; ln -s ../vax/tags ../$$i/tags; done
E 10
I 10
	    rm -f ../$$i/tags; ln -s ../tags ../$$i/tags; done
E 10
	-for i in ${DTAHOE}; do \
D 10
	    rm -f ../$$i/tags; ln -s ../tahoe/tags ../$$i/tags; done
E 10
I 10
	    rm -f ../$$i/tags; ln -s ../tags ../$$i/tags; done
E 10
I 8
	-for i in ${DHP300}; do \
D 10
	    rm -f ../$$i/tags; ln -s ../tahoe/tags ../$$i/tags; done
E 10
I 10
	    rm -f ../$$i/tags; ln -s ../tags ../$$i/tags; done
I 11
	-for i in ${DI386}; do \
	    rm -f ../$$i/tags; ln -s ../tags ../$$i/tags; done
E 12
I 12
D 19
links: ${SYSTAGS}
E 19
I 19
links::
	rm -f ${SYSTAGS}
	ln -s ${SYSDIR}/${MACHINE}/tags ${SYSTAGS}
E 19
E 12
E 11
E 10
E 8
	-for i in ${DGEN}; do \
D 12
	    rm -f ../$$i/tags; \
D 8
	    ln -s ../tahoe/tags ../$$i/tags; done
E 8
I 8
D 11
	    ln -s ../machine/tags ../$$i/tags; done
E 11
I 11
	    ln -s ../tags ../$$i/tags; done
	-ln -s /var/db/sys_tags ../tags
E 12
I 12
D 15
	    cd $$i && rm -f tags; ln -s ${SYSTAGS} tags; done
E 15
I 15
D 16
	    cd ../$$i && { rm -f tags; ln -s ${SYSTAGS} tags; } done
E 16
I 16
	    (cd ../$$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done
E 16
E 15
	-for i in ${ARCH}; do \
D 16
	    cd ../$$i && make ${MFLAGS} links; done
E 16
I 16
D 19
	    (cd ../$$i && make ${MFLAGS} links); done
E 16
E 12
E 11
E 8
E 7
E 3

D 7
FRC:
E 7
I 7
D 8
init_sysent.c syscalls.c ../sys/syscall.h: syscalls.master
	-mv init_sysent.c init_sysent.c.bak
	-mv syscalls.c syscalls.c.bak
	-mv ../sys/syscall.h ../sys/syscall.h.bak
E 8
I 8
D 12
init_sysent.c syscalls.c ../sys/syscall.h: makesyscalls.sh syscalls.master
	-mv -f init_sysent.c init_sysent.c.bak
	-mv -f syscalls.c syscalls.c.bak
	-mv -f ../sys/syscall.h ../sys/syscall.h.bak
E 8
	sh makesyscalls.sh syscalls.master
E 12
I 12
${SYSTAGS}:
	ln -s ${SYSDIR}/${MACHINE}/tags ${SYSTAGS}

FRC:
E 19
I 19
	    (cd ../$$i && make ${MFLAGS} SYSTAGS=${SYSTAGS} links); done
E 19
E 12
E 7
E 1
