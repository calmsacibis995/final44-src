h38208
s 00000/00000/00177
d D 8.1 93/06/11 15:59:53 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00008/00169
d D 7.9 91/05/08 22:03:37 bostic 9 8
c make libsa/libsmsa subdirectories of stand
e
s 00005/00003/00172
d D 7.8 91/05/05 20:01:03 bostic 8 7
c I couldn't leave this, it was just too ugly.  Fixed
e
s 00003/00003/00172
d D 7.7 91/05/05 18:29:08 bostic 7 6
c build small library in separate directory -- really gross
e
s 00035/00036/00140
d D 7.6 91/05/05 16:29:52 bostic 6 5
c make bootfd and bootwd small enough; make libraries in ../../stand
e
s 00011/00009/00165
d D 7.5 91/05/05 14:39:24 bostic 5 4
c make it look like the other stand Makefiles, break up sys.c
e
s 00019/00024/00155
d D 7.4 91/05/04 16:03:31 bostic 4 3
c Bill was right all along, might as well just load the C library
e
s 00063/00113/00116
d D 7.3 91/05/04 15:31:34 bostic 3 2
c make it work more like other stand Makefiles, mostly cosmetic
e
s 00070/00134/00159
d D 7.2 91/04/28 17:56:15 william 2 1
c distrib cleanup
e
s 00293/00000/00000
d D 7.1 90/04/24 19:56:14 william 1 0
c date and time created 90/04/24 19:56:14 by william
e
u
U
t
T
I 1
D 3
#-
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# William Jolitz.
#
#
# Copying or redistribution in any form is explicitly forbidden
# unless prior written permission is obtained from William Jolitz or an
# authorized representative of the University of California, Berkeley.
#
# Freely redistributable copies of this code will be available in
# the near future; for more information contact William Jolitz or
# the Computer Systems Research Group at the University of California,
# Berkeley.
#
# The name of the University may not be used to endorse or promote
# products derived from this software without specific prior written
# permission.  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.
E 3
#	%W% (Berkeley) %G%
D 3
#
E 3
I 2

E 2
DESTDIR=/
D 2
INCPATH=-I. -I../h -I../AT386
CC=gcc
E 2
I 2
D 3
INCPATH=-I. -I../../sys -I../../  -I../../stand
CC=cc -traditional
CPP= cpp -traditional ${INCPATH} -DSTANDALONE -DAT386
E 2
CFLAGS=	${COPTS} 
COPTS=	-O ${INCPATH} -DSTANDALONE -DAT386
E 3
I 3
STAND=	../../stand
INCPATH=-I../../sys -I../../  -I${STAND}
VPATH=	${STAND}
I 6
STANDDIR= ${DESTDIR}/stand
E 6
I 5

E 5
CC=	cc -traditional
C2=	/usr/libexec/c2
CPP=	cpp -traditional ${INCPATH} -DSTANDALONE -DAT386
D 5
CFLAGS=	-DSTANDALONE -DAT386 -O ${INCPATH}
E 5
I 5

E 5
E 3
RELOC=	70000
I 2
RELOC2=	70200
E 2
D 3

SRCS=	boot.c bootxx.c copy.c \
D 2
	sys.c conf.c prf.c  kbdcga.c \
	wd.c gets.c srt0.c \
	wdboot.c
E 2
I 2
	sys.c conf.c prf.c  kbd.c cga.c \
	wd.c fd.c gets.c srt0.c \
	wdbootblk.c fdbootblk.c
E 2
DUMMIES= confxx.c
D 2
DRIVERS= kbd.o cga.o wd.o disktab.o
E 2
I 2
DRIVERS= kbd.o cga.o wd.o fd.o
E 3
I 3
D 4
SRCS=	atoi.c boot.c bootxx.c cga.c conf.c confxx.c copy.c ctype_.c dev.c \
	fd.c fdbootblk.c getfile.c gets.c index.c kbd.c prf.c printf.c \
	srt0.c strcmp.c strcpy.c strlen.c strtol.c sys.c wd.c wdbootblk.c
E 4
I 4
D 5
SRCS=	boot.c bootxx.c cga.c conf.c confxx.c copy.c dev.c fd.c fdbootblk.c \
	getfile.c gets.c kbd.c prf.c printf.c srt0.c sys.c wd.c wdbootblk.c
E 4
DRIVERS=kbd.o cga.o wd.o fd.o
E 5
I 5

CFLAGS=	-DSTANDALONE -DAT386 -O ${INCPATH}

DRIVERS=cga.c fd.c kbd.c wd.c
D 6
SASRC=	bmap.c close.c dev.c getfile.c gets.c ioctl.c lseek.c open.c \
	printf.c read.c sys.c write.c
E 6
SRCS=	boot.c bootxx.c conf.c confxx.c copy.c fd.c fdbootblk.c prf.c \
	srt0.c wdbootblk.c ${DRIVERS} ${SASRC}
E 5
E 3
E 2
D 4
LIBSA=	libsa.a
E 4
I 4
D 6
LIBS=	libsa.a ${DESTDIR}/usr/lib/libc.a
E 6
I 6
D 9
LIBS=	${STAND}/obj/libsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
D 7
SMLIBS=	${STAND}/obj/libsmsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
E 7
I 7
D 8
SMLIBS=	${STAND}/smobj/libsmsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
E 8
I 8
SMLIBS=	${STAND}/small/obj/libsmsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
E 9
I 9
LIBS=	libsa/libsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
SMLIBS=	libsmsa/libsmsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
E 9
E 8
E 7
E 6
E 4

D 2
BOOTBLOCKS= bootwd
DISKUTILS= boot copy cat ls
E 2
I 2
BOOTBLOCKS= wdboot bootwd fdboot bootfd
D 3
DISKUTILS= boot copy cat ls mem
E 3
I 3
DISKUTILS= boot copy cat ls
E 3
E 2
ALL=	${BOOTBLOCKS} ${DISKUTILS}

D 6
STANDDIR= ${DESTDIR}/stand
I 3

E 6
E 3
all: ${ALL}

D 2
${LIBSA}: sys.o conf.o ${DRIVERS} prf.o gets.o
E 2
I 2
D 3
${LIBSA}: sys.o conf.o ${DRIVERS} prf.o gets.o getfile.o
E 3
I 3
D 4
${LIBSA}: atoi.o conf.o ctype_.o dev.o getfile.o gets.o index.o prf.o \
	printf.o _setjmp.o strcmp.o strcpy.o strlen.o strtol.o sys.o \
E 4
I 4
D 5
libsa.a: conf.o dev.o getfile.o gets.o prf.o printf.o sys.o \
E 4
	${DRIVERS}
E 5
I 5
D 6
libsa.a: conf.o prf.o ${DRIVERS:.c=.o} ${SASRC:.c=.o}
E 6
I 6
D 9
${STAND}/obj/libsa.a:
	cd ${STAND}; make
D 7
${STAND}/obj/libsmsa.a:
	cd ${STAND}; make LIB=smsa CFLAGS='-O -DSMALL'
E 7
I 7
D 8
${STAND}/smobj/libsmsa.a:
	cd ${STAND}; env MAKEOBJDIR=smobj make LIB=smsa CFLAGS='-O -DSMALL'
E 8
I 8
${STAND}/small/obj/libsmsa.a:
	cd ${STAND}/small; make
E 9
I 9
libsa/libsa.a::
	cd libsa; make
libsmsa/libsmsa.a::
	cd libsmsa; make
E 9
E 8
E 7

libdrive.a: conf.o prf.o ${DRIVERS:.c=.o}
E 6
E 5
E 3
E 2
D 4
	ar crv ${LIBSA} $?
	ranlib ${LIBSA}
E 4
I 4
	ar crv $@ $?
	ranlib $@
E 4
D 5

D 2
${DRIVERS}: # saio.h
E 2
I 2
${DRIVERS}:
E 2
D 3
	${CC} -c ${COPTS} $*.c
E 3
I 3
	${CC} -c ${CFLAGS} $*.c
E 5
E 3

D 2
test: test.o prf.o kbd.o cga.o srt0.o gets.o
	ld -N -o test srt0.o test.o kbd.o cga.o prf.o gets.o
	
t: test.o prf.o kbd.o cga.o relsrt0.o gets.o
	ld -N -T ${RELOC} -o t relsrt0.o test.o kbd.o cga.o prf.o gets.o
	
mem: mem.o prf.o kbd.o cga.o srt0.o gets.o
	ld -N -o mem srt0.o mem.o kbd.o cga.o prf.o gets.o
	
E 2
# startups

srt0.o: srt0.c
D 2
	${CC} -E -DLOCORE -DRELOC=0x${RELOC} ${COPTS} srt0.c | a386 -o srt0.o
E 2
I 2
	${CPP} -E -DLOCORE -DRELOC=0x${RELOC} srt0.c | ${AS} -o srt0.o
E 2

I 2
wsrt0.o: srt0.c
D 3
	${CPP} -E -DLOCORE -DSMALL -DRELOC=0x${RELOC} -DREL srt0.c | ${AS} -o wsrt0.o
E 3
I 3
	${CPP} -E -DLOCORE -DSMALL -DRELOC=0x${RELOC} -DREL srt0.c | \
	    ${AS} -o wsrt0.o
E 3

E 2
relsrt0.o: srt0.c
D 2
	${CC} -E -DLOCORE -DRELOC=0x${RELOC} -DREL ${COPTS} srt0.c | \
	a386 -o relsrt0.o
E 2
I 2
D 3
	${CPP} -E -DLOCORE -DRELOC=0x${RELOC} -DREL srt0.c | \
	${AS} -o relsrt0.o
E 3
I 3
	${CPP} -E -DLOCORE -DRELOC=0x${RELOC} -DREL srt0.c | ${AS} -o relsrt0.o
E 3
E 2

D 2
wdboot.o: wdboot.c ../h/disk.h ../32k/psr.h ../S375/devvm.h
	${CC} -E -DLOCORE -DRELOC=0x${RELOC} ${COPTS} wdboot.c | as -o wdboot.o
E 2
I 2
# block 0 boots
E 2

D 2
dtab.o: dtab.c ../h/disk.h
	${CC} -E -DLOCORE -DRELOC=0x${RELOC} -DDISKLAB ${COPTS} dtab.c | \
	as -o dtab.o
E 2
I 2
wdbootblk.o: wdbootblk.c 
D 3
	${CPP} -E -DLOCORE -DRELOC=0x${RELOC} wdbootblk.c | \
	as -o wdbootblk.o
E 3
I 3
	${CPP} -E -DLOCORE -DRELOC=0x${RELOC} wdbootblk.c | ${AS} -o $@
E 3
E 2

I 2
fdbootblk.o: fdbootblk.c 
D 3
	${CPP} -E -DLOCORE -DRELOC=0x${RELOC} fdbootblk.c | \
	as -o fdbootblk.o
E 3
I 3
	${CPP} -E -DLOCORE -DRELOC=0x${RELOC} fdbootblk.c | ${AS} -o $@
E 3
E 2

D 2
# bootable from tape

tpboot:	tpboot.o relsrt0.o ${LIBSA}
	ld -N -o tpboot -T ${RELOC} relsrt0.o tpboot.o ${LIBSA} -lc3
	strip tpboot

tpboot.o: boot.c ../h/param.h ../h/inode.h ../h/fs.h
tpboot.o: saio.h ../h/reboot.h ../h/vm.h 
	cp boot.c tpboot.c; chmod +w tpboot.c
	${CC} -c ${CFLAGS} -DJUSTASK tpboot.c
	rm -f tpboot.c

tpcopy:	copy.o tpsrt0.o ${LIBSA}
	ld -N -o tpcopy tpsrt0.o copy.o ${LIBSA} -lc3
	strip tpcopy

tpformat: format.o wdformat.o tpsrt0.o ${LIBSA}
	cp format.c tpformat.c; chmod +w tpformat.c
	${CC} -c ${CFLAGS} -DJUSTEXIT -DTP tpformat.c
	rm -f tpformat.c
	ld -N -o tpformat tpsrt0.o tpformat.o wdformat.o ${LIBSA} -lc3
	strip tpformat

tpdisklabel:	disklabel.o tpsrt0.o ${LIBSA}
	cp disklabel.c tpdisklabel.c; chmod +w tpdisklabel.c
	${CC} -c ${CFLAGS} -DJUSTEXIT -DTP tpdisklabel.c
	rm -f tpdisklabel.c
	ld -N -o tpdisklabel tpsrt0.o tpdisklabel.o ${LIBSA} -lc3

E 2
# bootable from floppy or real disks

D 3
boot:	boot.o relsrt0.o bootconf.o ${LIBSA}
D 2
	ld -N -T ${RELOC} -o boot relsrt0.o boot.o bootconf.o ${LIBSA} -lc3
E 2
I 2
	ld -N -T ${RELOC} -o boot relsrt0.o boot.o bootconf.o ${LIBSA} -lc
E 3
I 3
D 4
boot:	boot.o bootconf.o cga.o relsrt0.o ${LIBSA}
	ld -N -T ${RELOC} -o $@ boot.o bootconf.o cga.o relsrt0.o ${LIBSA}
E 4
I 4
boot:	boot.o bootconf.o cga.o relsrt0.o ${LIBS}
	ld -N -T ${RELOC} -o $@ boot.o bootconf.o cga.o relsrt0.o ${LIBS}
E 4
E 3
E 2

D 2
dlbl:	dlbl.o srt0.o bootconf.o ${LIBSA}
	ld -N -o dlbl srt0.o dlbl.o bootconf.o ${LIBSA} -lc3

E 2
bootconf.o: conf.o
D 3
	cp conf.c bootconf.c
E 3
I 3
	ln -s conf.c bootconf.c
E 3
	${CC} -c ${CFLAGS} -DBOOT bootconf.c
	rm -f bootconf.c

I 3
# utilities

E 3
D 4
cat:	cat.o srt0.o conf.o ${LIBSA}
D 2
	ld -N -o cat srt0.o cat.o conf.o ${LIBSA} -lc3
E 2
I 2
D 3
	ld -N -o cat srt0.o cat.o conf.o ${LIBSA} -lc
E 3
I 3
	ld -N -o $@ srt0.o cat.o conf.o ${LIBSA} -lc
E 4
I 4
cat:	cat.o srt0.o conf.o ${LIBS}
	ld -N -o $@ srt0.o cat.o conf.o ${LIBS}
E 4
E 3
E 2

D 4
ls:	ls.o srt0.o conf.o ${LIBSA}
D 2
	ld -N -o ls srt0.o ls.o conf.o ${LIBSA} -lc3
E 2
I 2
D 3
	ld -N -o ls srt0.o ls.o conf.o ${LIBSA} -lc
E 3
I 3
	ld -N -o $@ srt0.o ls.o conf.o ${LIBSA} -lc
E 4
I 4
ls:	ls.o srt0.o conf.o ${LIBS}
	ld -N -o $@ srt0.o ls.o conf.o ${LIBS}
E 4
E 3
E 2

D 4
copy:	copy.o srt0.o conf.o ${LIBSA}
D 2
	ld -N -o copy srt0.o copy.o conf.o ${LIBSA} -lc3
E 2
I 2
D 3
	ld -N -o copy srt0.o copy.o conf.o ${LIBSA} -lc
E 3
I 3
	ld -N -o $@ srt0.o copy.o conf.o ${LIBSA} -lc
E 4
I 4
copy:	copy.o srt0.o conf.o ${LIBS}
	ld -N -o $@ srt0.o copy.o conf.o ${LIBS}
E 4
E 3
E 2

D 2
format:	format.o wdformat.o srt0.o conf.o ${LIBSA}
	ld -N -o format srt0.o format.o wdformat.o conf.o ${LIBSA} -lc3

disklabel:	disklabel.o srt0.o conf.o ${LIBSA}
	ld -N -o disklabel srt0.o disklabel.o conf.o ${LIBSA} -lc3

icheck:	icheck.o srt0.o conf.o ${LIBSA}
	ld -N -o icheck srt0.o icheck.o conf.o ${LIBSA} -lc3

# bootstrap from ether

### not yet, rosin, not yet ###

E 2
I 2
D 3
mem: mem.o prf.o kbd.o cga.o srt0.o gets.o
	ld -N -o mem srt0.o mem.o kbd.o cga.o prf.o gets.o
	
E 3
E 2
# getting booted from disc

D 2
bootwd: wdboot.o bootxx.o confwd.o sm_wd.o sm_sys.o ${LIBSA}
	ld -N -T ${RELOC} wdboot.o bootxx.o confwd.o sm_sys.o sm_wd.o \
		${LIBSA} -lc3
E 2
I 2
wdboot: wdbootblk.o
	ld -N -T ${RELOC} wdbootblk.o
	cp a.out wdb
	rm -f wdboot
	strip a.out;dd if=a.out of=wdboot ibs=32 skip=1;rm -f a.out
	ls -l wdboot

D 3
bootwd: wdbootblk.o wsrt0.o bootxx.o confwd.o sm_wd.o sm_sys.o sm_cga.o ${LIBSA}
	ld -N -T ${RELOC2} wsrt0.o bootxx.o confwd.o sm_sys.o \
		sm_wd.o sm_cga.o ${LIBSA} -lc
E 3
I 3
D 4
bootwd: wdbootblk.o wsrt0.o bootxx.o confwd.o sm_wd.o sys.o sm_cga.o ${LIBSA}
E 4
I 4
D 6
bootwd: wdbootblk.o wsrt0.o bootxx.o confwd.o sm_wd.o sys.o sm_cga.o ${LIBS}
E 4
	ld -N -T ${RELOC2} wsrt0.o bootxx.o confwd.o sys.o sm_wd.o \
D 4
	    sm_cga.o ${LIBSA} -lc
E 4
I 4
	    sm_cga.o ${LIBS}
E 6
I 6
bootwd: wdbootblk.o wsrt0.o bootxx.o sm_confwd.o sm_wd.o sm_cga.o ${SMLIBS}
	ld -N -T ${RELOC2} wsrt0.o bootxx.o sm_confwd.o sm_wd.o \
	    sm_cga.o ${SMLIBS}
E 6
E 4
E 3
E 2
	size a.out
I 2
	cp a.out bwd
	rm -f bootwd
E 2
	strip a.out;dd if=a.out of=bootwd ibs=32 skip=1;rm -f a.out
	ls -l bootwd

D 2
bootcst: tprelsrt0.o bootxx.o confcst.o sm_cst.o sm_sba.o sm_sys.o ${LIBSA}
	ld -N -T ${RELOC} tprelsrt0.o bootxx.o confcst.o sm_sys.o \
		sm_cst.o sm_sba.o ${LIBSA} -lc3
	size a.out
	strip a.out;dd if=a.out of=bootcst ibs=32 skip=1;rm -f a.out
	ls -l bootcst
E 2
I 2
fdboot: fdbootblk.o
	ld -N -T ${RELOC} fdbootblk.o
	cp a.out fdb
	rm -f fdboot
	strip a.out;dd if=a.out of=fdboot ibs=32 skip=1;rm -f a.out
	ls -l fdboot
E 2

D 2
bootswd: relsrt0.o dtab.o bootxx.o confswd.o sm_swd.o sm_sba.o sm_sys.o ${LIBSA}
	ld -N -T ${RELOC} relsrt0.o sm_swd.o dtab.o bootxx.o confswd.o sm_sba.o \
		sm_sys.o ${LIBSA} -lc3
E 2
I 2
D 3
bootfd: fdbootblk.o wsrt0.o bootxx.o conffd.o fd.o sm_sys.o sm_cga.o ${LIBSA}
	ld -N -T ${RELOC2} wsrt0.o bootxx.o conffd.o sm_sys.o \
E 3
I 3
D 4
bootfd: fdbootblk.o wsrt0.o bootxx.o conffd.o fd.o sys.o sm_cga.o ${LIBSA}
E 4
I 4
D 6
bootfd: fdbootblk.o wsrt0.o bootxx.o conffd.o fd.o sys.o sm_cga.o ${LIBS}
E 4
	ld -N -T ${RELOC2} wsrt0.o bootxx.o conffd.o sys.o \
E 3
D 4
		fd.o sm_cga.o ${LIBSA} -lc
E 4
I 4
		fd.o sm_cga.o ${LIBS}
E 6
I 6
bootfd: fdbootblk.o wsrt0.o bootxx.o fd.o sm_cga.o sm_conffd.o ${SMLIBS}
	ld -N -T ${RELOC2} wsrt0.o bootxx.o fd.o sm_cga.o sm_conffd.o ${SMLIBS}
E 6
E 4
E 2
	size a.out
D 2
	strip a.out;dd if=a.out of=bootswd ibs=32 skip=1;rm -f a.out
	ls -l bootswd
E 2
I 2
	cp a.out bfd
	rm -f bootfd
	strip a.out; dd if=a.out of=bootfd ibs=32 skip=1;rm -f a.out
	ls -l bootfd
E 2

D 6
sm_wd.o: wd.o
D 3
	-rm -f sm_wd.c
	-ln -s wd.c sm_wd.c
E 3
I 3
	rm -f sm_wd.c
	ln -s wd.c sm_wd.c
E 3
	${CC} -S -DSMALL ${CFLAGS} sm_wd.c
D 2
	/lib/c2 -i sm_wd.s | as -o sm_wd.o
E 2
I 2
	${AS} sm_wd.s -o sm_wd.o
E 2
	rm -f sm_wd.s sm_wd.c
E 6
I 6
sm_conffd.o: conffd.c
	rm -f sm_conffd.c
	ln -s conffd.c sm_conffd.c
	${CC} -S -DSMALL ${CFLAGS} sm_conffd.c
	${AS} sm_conffd.s -o sm_conffd.o
	rm -f sm_conffd.s sm_conffd.c
E 6

I 2
D 6
sm_cga.o: cga.o
E 6
I 6
sm_confwd.o: confwd.c
	rm -f sm_confwd.c
	ln -s confwd.c sm_confwd.c
	${CC} -S -DSMALL ${CFLAGS} sm_confwd.c
	${AS} sm_confwd.s -o sm_confwd.o
	rm -f sm_confwd.s sm_confwd.c

sm_cga.o: cga.c
E 6
D 3
	-rm -f sm_cga.c
	-ln -s cga.c sm_cga.c
E 3
I 3
	rm -f sm_cga.c
	ln -s cga.c sm_cga.c
E 3
	${CC} -S -DSMALL ${CFLAGS} sm_cga.c
	${AS} sm_cga.s -o sm_cga.o
	rm -f sm_cga.s sm_cga.c

E 2
D 6
sm_cst.o: cst.o
D 3
	-rm -f sm_cst.c
	-ln -s cst.c sm_cst.c
E 3
I 3
	rm -f sm_cst.c
	ln -s cst.c sm_cst.c
E 3
	${CC} -S -DSMALL ${CFLAGS} sm_cst.c
D 3
	/lib/c2 -i sm_cst.s | as -o sm_cst.o
E 3
I 3
	${C2} -i sm_cst.s | ${AS} -o sm_cst.o
E 3
	rm -f sm_cst.s sm_cst.c
E 6
I 6
sm_wd.o: wd.c
	rm -f sm_wd.c
	ln -s wd.c sm_wd.c
	${CC} -S -DSMALL ${CFLAGS} sm_wd.c
	${AS} sm_wd.s -o sm_wd.o
	rm -f sm_wd.s sm_wd.c
E 6

D 6
sm_swd.o: swd.o
D 3
	-rm -f sm_swd.c
	-ln -s swd.c sm_swd.c
E 3
I 3
	rm -f sm_swd.c
	ln -s swd.c sm_swd.c
E 3
	${CC} -S -DSMALL ${CFLAGS} sm_swd.c
D 3
	/lib/c2 -i sm_swd.s | as -o sm_swd.o
E 3
I 3
	${C2} -i sm_swd.s | ${AS} -o sm_swd.o
E 3
	rm -f sm_swd.s sm_swd.c

D 2
sm_sba.o: sba.o
	-rm -f sm_sba.c
	-ln -s sba.c sm_sba.c
	${CC} -S -DSMALL ${CFLAGS} sm_sba.c
	/lib/c2 -i sm_sba.s | as -o sm_sba.o
	rm -f sm_sba.s sm_sba.c

E 2
D 3
sm_sys.o: sys.o
	-rm -f sm_sys.c
	-ln -s sys.c sm_sys.c
	${CC} -c -DSMALL ${CFLAGS} sm_sys.c
	-rm -f sm_sys.c
E 3
I 3
sys.o: sys.c
	${CC} -c -DSMALL ${CFLAGS} ${.ALLSRC}
E 3

E 6
I 3
D 4
_setjmp.o: _setjmp.s
	${CPP} -E -I../../../lib/libc/i386 _setjmp.s | ${AS} -o $@

E 4
E 3
confwd.o: confwd.c confxx.o
D 2
confswd.o: confswd.c confxx.o
confcst.o: confcst.c confxx.o
E 2
I 2
conffd.o: conffd.c confxx.o
E 2

confxx.o:
	touch confxx.o

confwd.c: confxx.c
D 3
	-rm -f confwd.c
	sed -e 's/XX/wd/' -e 's/xx/wd/g' <confxx.c >confwd.c
E 3
I 3
	rm -f confwd.c
	sed -e 's/io->i_dev/0/g'		< ${STAND}/dev.c > confwd.c
	sed -e 's/XX/wd/' -e 's/xx/wd/g'	< confxx.c >> confwd.c
E 3

D 2
confswd.c: confxx.c
	-rm -f confswd.c
	sed -e 's/XX/swd/' -e 's/xx/swd/g' <confxx.c >confswd.c
E 2
I 2
conffd.c: confxx.c
D 3
	-rm -f conffd.c
	sed -e 's/XX/fd/' -e 's/xx/fd/g' <confxx.c >conffd.c
E 3
I 3
	rm -f conffd.c
	sed -e 's/io->i_dev/0/g'		< ${STAND}/dev.c > conffd.c
	sed -e 's/XX/fd/' -e 's/xx/fd/g'	< confxx.c >> conffd.c
E 3
E 2

D 2
confcst.c: confxx.c
	-rm -f confcst.c
	echo "#define	TP" >confcst.c
	sed -e 's/XX/cst/' -e 's/xx/cst/g' <confxx.c >>confcst.c

E 2
D 3
# utilities

print:
	@pr makefile
	@ls -l | pr 
	@pr *.h *.c

E 3
clean:
D 3
	rm -f *.o *.exe *.i errs sm_*.c
	rm -f a.out boot cat tpboot tpcopy copy tpformat disklabel \
		tpdisklabel ls
E 3
I 3
D 4
	rm -f *.o *.exe *.i sm_*.c ${LIBSA}
E 4
I 4
D 6
	rm -f *.o *.exe *.i sm_*.c libsa.a
E 6
I 6
	rm -f *.o *.exe *.i sm_*.c libdrive.a
E 6
E 4
	rm -f a.out bfd bwd fdb wdb ${ALL}
E 3
	rm -f boot[a-wyz]? boot[a-wyz]?? boot[a-wyz]?.c boot[a-wyz]??.c \
		conf[a-wyz]?.c conf[a-wyz]??.c
	rm -f format core sboot bootconf.c
I 8
D 9
	cd ${STAND}; make clean
	cd ${STAND}/small; make clean
E 9
I 9
	cd libsa; make cleandir
	cd libsmsa; make cleandir
E 9
E 8

D 3
lint:
	lint ${COPTS} -hxbn boot.c ${SRCS} | \
	    grep -v 'possible pointer alignment' | \
	    grep -v 'struct/union .* never defined'
E 3
I 3
cleandir: clean
	rm -f ${MAN} tags .depend
E 3

I 3
depend: ${SRCS}
	mkdep ${INCPATH} -DSTANDALONE ${SRCS} ${DUMMIES}

E 3
install: ${ALL}
	install -c -s boot ${DESTDIR}
	cp ${DISKUTILS} ../dist/floppy
	cp ${TAPEUTILS} ../dist/tp
	cp ${BOOTBLOCKS} ${STANDDIR}
	cp ${DISKUTILS} ${STANDDIR}
D 3

depend:
	for i in ${SRCS} ${DUMMIES}; do \
	    ${CC} -M ${INCPATH} $$i | \
	    awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
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

# DO NOT DELETE THIS LINE -- make depend uses it

E 3
D 2

sys.o: sys.c ./../h/param.h /usr/include/machine/machparam.h ../h/signal.h
sys.o: /usr/include/sys/types.h ./../h/inode.h ./../h/fs.h ./../h/dir.h
sys.o: ./saio.h

conf.o: conf.c ./../h/param.h
conf.o: /usr/include/machine/machparam.h ../h/signal.h /usr/include/sys/types.h
conf.o: ./../h/inode.h ./../h/fs.h ./saio.h

prf.o: prf.c
prf.o: /usr/include/sys/types.h

format.o: format.c ./../h/param.h /usr/include/machine/machparam.h
format.o: ../h/signal.h /usr/include/sys/types.h ./../h/fs.h ./../h/inode.h
format.o: ./../h/dkbad.h ./saio.h

bootxx.o: bootxx.c ./../h/param.h /usr/include/machine/machparam.h
bootxx.o: ../h/signal.h /usr/include/sys/types.h ./../h/inode.h ./../h/fs.h
bootxx.o: /usr/include/sys/exec.h ./saio.h ./../h/reboot.h

confxx.o: confxx.c ./../machine/pte.h ./../h/param.h
confxx.o: /usr/include/machine/machparam.h ../h/signal.h
confxx.o: /usr/include/sys/types.h ./../h/inode.h ./../h/fs.h ./saio.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 2
E 1
