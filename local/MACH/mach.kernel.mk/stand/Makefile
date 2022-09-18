# 
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# Copyright (c) 1987 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
######################################################################
# HISTORY
# $Log:	Makefile,v $
# Revision 2.5  89/02/26  14:16:52  gm0w
# 	Changes for cleanup.
# 
# Revision 2.4  88/08/08  13:40:48  rvb
# Simply things for cmu:  Define cmu target which turns on
# CS_DISK which is necessary to process CMU disk partition
# layouts.
# Define a bootbi which is a bootra but for BI buses
# 
#
# 18-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
#	Define bootbsd as boot, except that it does not need the
#	qvcons.c and qdcons.c which are ULTRIX code.
#	So use "boot" if you want qvss/qdss support on your boot
#	and have qvcons.c and qdcons.c in your stand dir.  Otherwise,
#	use "bootbsd" which would work identically except on uVaxen.
#
# 30-Jun-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Correct to install cons.o in $LIBSA and fix boothk rule
#	to use small version of autoconf.o.
#	[ V5.1(XF12) ]
#
# 09-May-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Added NEWSRC rule (for archiving).
#	[ V5.1(XF11) ]
#
# 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Added rules to build standalone kernel-mode debugger using
#	libkdb.a;  created new console I/O module so that it can be
#	shared with the debugger; fixed to use INCPATH in COPTS instead
#	of CFLAGS so that it is used for device driver compilations
#	also and added CARGS variable for specifying special
#	compilation flags on the command line;  moved RELOC to c4000
#	from c0000;  made standard boot include QVSS and QDSS (it won't
#	link without them) to replace special bootq; use small
#	autoconf.c versions for boothp and bootrq; flush special uVax
#	startup module.
#	[ V5.1(F8) ]
#
# 10-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
#	Added qd.o and build bootq instead of bootqv (bootq will boot
#	either with qvss or qdss).
#
#  7-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
#	Added 780boot which is "boot" massaged for a 780 floppy.
#
#  3-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
#	Added support for KA820 and carried over support for MicroVax.
#	libsa.a -> libvaxsa.a
#
######################################################################
#
# Copyright (c) 1980, 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	7.1 (Berkeley) 6/5/86
#
DESTDIR=/
INCPATH=-I. -I.. -I../h
CARGS=
CFLAGS=	-O -DSTANDALONE ${COPTS} 
COPTS= ${INCPATH} ${CARGS}
730OPTS=-O ${INCPATH} -DSTANDALONE -DVAX730
RELOC=	1c0000
KDBRELOC=1d0000

SRCS=	sys.c conf.c prf.c machdep.c \
	autoconf.c hp.c hpmaptype.c ht.c idc.c mba.c mt.c rk.c \
	rl.c tm.c ts.c up.c upmaptype.c uba.c uda.c ut.c \
	drtest.c format.c up.old.c hp.old.c ../vax/dkbad.c
DUMMIES= bootxx.c confxx.c
DRIVERS=hp.o hpmaptype.o ht.o idc.o mba.o mt.o \
	rk.o rl.o tm.o ts.o \
	up.o upmaptype.o uba.o uda.o ut.o \
	qvqd_stub.o
# These drivers don't have ecc correction and bad sector forwarding;
# they are placed in the file system boot area for 750's.  If your
# root has bad sectors you can try and squeeze the newer drivers in...
ODRIVERS=hp.old.o up.old.o
LIBSA=	libsa.a
LIBKDB=	../src/kdb/VAX/libkdb.a

ALL=	bootbi bootbsd 780boot boot tpboot copy tpcopy \
	format tpformat drtest boothp boothk bootup bootra bootrq bootrl \
	730boot 730copy 730format 730drtest

all: ${ALL}

cmu:
	make ${MFLAGS} CARGS=-DCS_DISK=1 all

${LIBSA}: sys.o conf.o autoconf.o ${DRIVERS} prf.o cons.o machdep.o dkbad.o
	ar crv ${LIBSA} $?
	@ranlib ${LIBSA}

${ODRIVERS} ${DRIVERS}: savax.h
	cc -c -S ${COPTS} $*.c
	/lib/c2 -i $*.s | as -o $*.o
	@rm -f $*.s

dkbad.o: ../vax/dkbad.c
	${CC} -c ${CFLAGS} ../vax/dkbad.c

# startups

srt0.o: srt0.c ../vax/mtpr.h ../vax/cpu.h
	cc -E -DRELOC=0x${RELOC} ${COPTS} srt0.c | as -o srt0.o

tpsrt0.o: srt0.c ../vax/mtpr.h ../vax/cpu.h
	cc -E -DRELOC=0x${RELOC} -DTP ${COPTS} srt0.c | as -o tpsrt0.o 

relsrt0.o: srt0.c ../vax/mtpr.h ../vax/cpu.h
	cc -E -DRELOC=0x${RELOC} -DREL ${COPTS} srt0.c | as -o relsrt0.o

kdbsrt0.o: kdbsrt0.c
	cc -E -DRELOC=0x${KDBRELOC} kdbsrt0.c | as
	mv a.out kdbsrt0.o

# bootable from tape

tpboot:	tpboot.o relsrt0.o ${LIBSA}
	ld -o tpboot.x -N -s -T ${RELOC} relsrt0.o tpboot.o ${LIBSA} -lc
	@dd if=tpboot.x of=tpboot ibs=32 skip=1 >/dev/null 2>&1
	@size tpboot.x
	@ls -lg tpboot; echo
	@rm -f tpboot.x

tpboot.o: boot.c ../h/param.h ../h/inode.h ../h/fs.h
tpboot.o: saio.h ../h/reboot.h ../h/vm.h 
	cp boot.c tpboot.c; chmod +w tpboot.c
	cc -c -O -I.. -DJUSTASK tpboot.c
	rm -f tpboot.c

tpcopy:	copy.o tpsrt0.o ${LIBSA}
	ld -o tpcopy.x -N -s tpsrt0.o copy.o ${LIBSA} -lc
	@dd if=tpcopy.x of=tpcopy ibs=32 skip=1 >/dev/null 2>&1
	@size tpcopy.x
	@ls -lg tpcopy; echo
	@rm -f tpcopy.x

tpformat: format.o tpsrt0.o confhpup.o ${LIBSA}
	cp format.c tpformat.c; chmod +w tpformat.c
	cc -c -O -I.. -DJUSTEXIT tpformat.c
	@rm -f tpformat.c
	@ld -o tpformat.x -N -s tpsrt0.o tpformat.o confhpup.o ${LIBSA} -lc
	@dd if=tpformat.x of=tpformat ibs=32 skip=1 >/dev/null 2>&1
	@size tpformat.x
	@ls -lg tpformat; echo
	@rm -f tpformat.x

# bootable from floppy or real disks

kdb:	kdbsrt0.o kdb.o ${LIBKDB}
	ld -N -T ${KDBRELOC} kdbsrt0.o kdb.o ${LIBKDB} ${LIBSA}
	mv a.out kdb
	@size kdb

bootbsd:boot.o relsrt0.o bootconf.o ${LIBSA}
	ld -o bootbsd -N -T ${RELOC} relsrt0.o boot.o bootconf.o ${LIBSA} -lc
	@size bootbsd
	@ls -lg bootbsd; echo

boot:	boot.o relsrt0.o bootconf.o qvcons.o qdcons.o ${LIBSA}
	ld -o boot -N -T ${RELOC} relsrt0.o boot.o bootconf.o qvcons.o qdcons.o ${LIBSA} -lc
	@size boot
	@ls -lg boot; echo

780boot: bootbsd
	cp bootbsd a.out
	@strip a.out
	@size a.out
	@dd if=a.out of=780boot ibs=32 skip=1 >/dev/null 2>&1
	@rm -f a.out
	@ls -lg 780boot; echo

qvcons.o: qvcons.c
	cc -c ${CFLAGS} qvcons.c

qdcons.o:qdcons.c
	cc -c ${CFLAGS} qdcons.c

bootconf.o: conf.o
	cp conf.c bootconf.c
	cc -c ${COPTS} -DBOOT bootconf.c
	@rm -f bootconf.c

regs: regs.o srt0.o bootconf.o ${LIBSA}
	ld -o regs -N srt0.o regs.o bootconf.o ${LIBSA} -lc
	@size regs
	@ls -lg regs; echo

cat: cat.o srt0.o bootconf.o ${LIBSA}
	ld -o cat -N srt0.o cat.o bootconf.o ${LIBSA} -lc
	@size cat
	@ls -lg cat; echo

copy:	copy.o srt0.o conf.o ${LIBSA}
	ld -o copy -N srt0.o copy.o conf.o ${LIBSA} -lc
	@size copy

format:	format.o srt0.o confhpup.o ${LIBSA}
	ld -o format -N srt0.o format.o confhpup.o ${LIBSA} -lc
	@size format

drtest:	drtest.o srt0.o confhpup.o ${LIBSA}
	ld -o drtest -N srt0.o drtest.o confhpup.o ${LIBSA} -lc
	@size drtest

# for 730s minimize size to avoid microcode botch
# (won't load files larger than 12.5 Kbytes)

730boot.o: boot.o
	cp boot.c 730boot.c; chmod +w 730boot.c
	cc -c ${730OPTS} 730boot.c
	rm -f 730boot.c

730boot: 730boot.o relsrt0.o 730bootconf.o ${LIBSA}
	ld -o 730boot -N -T ${RELOC} relsrt0.o 730boot.o 730bootconf.o ${LIBSA} -lc
	@size 730boot

730bootconf.o: conf.o
	cp conf.c 730bootconf.c
	cc -c ${730OPTS} -DBOOT 730bootconf.c
	@rm -f 730bootconf.c

730copy: copy.o srt0.o 730conf.o ${LIBSA}
	ld -o 730copy -N srt0.o copy.o 730conf.o ${LIBSA} -lc
	@size 730copy

730drtest: drtest.o srt0.o confup.o ${LIBSA}
	ld -o 730drtest -N srt0.o drtest.o confup.o ${LIBSA} -lc
	@size 730drtest

730format: format.o srt0.o confup.o ${LIBSA}
	ld -o 730format -N srt0.o format.o confup.o ${LIBSA} -lc
	@size 730format

730conf.o: conf.o
	cp conf.c 730conf.c
	cc -c ${730OPTS} 730conf.c
	@rm -f 730conf.c

# bootstrap from ether

### not yet, rosin, not yet ###

# 15 sector disk boot

boothk: relsrt0.o boothk.o confrk.o smsys.o smprf.o sbiautoconf.o ${LIBSA}
	ld -o boothk.x -N -T ${RELOC} relsrt0.o boothk.o confrk.o smsys.o smprf.o sbiautoconf.o ${LIBSA} -lc
	@strip boothk.x
	@dd if=boothk.x of=boothk ibs=32 skip=1 >/dev/null 2>&1
	@size boothk.x
	@ls -lg boothk; echo
	@rm -f boothk.x

boothp: relsrt0.o boothp.o confhp.o hp.old.o smsys.o smprf.o sbiautoconf.o ${LIBSA}
	ld -o boothp.x -N -T ${RELOC} relsrt0.o boothp.o confhp.o hp.old.o smsys.o smprf.o sbiautoconf.o ${LIBSA} -lc
	@strip boothp.x
	@dd if=boothp.x of=boothp ibs=32 skip=1 >/dev/null 2>&1
	@size boothp.x
	@ls -lg boothp; echo
	@rm -f boothp.x

bootup: relsrt0.o bootup.o confup.o up.old.o smsys.o smprf.o sbiautoconf.o ${LIBSA}
	ld -o bootup.x -N -T ${RELOC} relsrt0.o bootup.o confup.o up.old.o smsys.o smprf.o sbiautoconf.o ${LIBSA} -lc
	@strip bootup.x
	@dd if=bootup.x of=bootup ibs=32 skip=1 >/dev/null 2>&1
	@size bootup.x
	@ls -lg bootup; echo
	@rm -f bootup.x

bootra: relsrt0.o bootra.o confra.o smsys.o smprf.o sbiautoconf.o ${LIBSA}
	ld -o bootra.x -N -T ${RELOC} relsrt0.o bootra.o confra.o smsys.o smprf.o sbiautoconf.o ${LIBSA} -lc
	@strip bootra.x
	@dd if=bootra.x of=bootra ibs=32 skip=1 >/dev/null 2>&1
	@size bootra.x
	@ls -lg bootra; echo
	@rm -f bootra.x

bootrl: relsrt0.o bootrl.o confrl.o smsys.o smprf.o sbiautoconf.o ${LIBSA}
	ld -o bootrl.x -N -T ${RELOC} relsrt0.o bootrl.o confrl.o smsys.o smprf.o sbiautoconf.o ${LIBSA} -lc
	@strip bootrl.x
	@dd if=bootrl.x of=bootrl ibs=32 skip=1 >/dev/null 2>&1
	@size bootrl.x
	@ls -lg bootrl; echo
	@rm -f bootrl.x

bootrq: relsrt0.o bootra.o confra.o smsys.o smprf.o qbusautoconf.o ${LIBSA}
	ld -o bootrq.x -N -T ${RELOC} relsrt0.o bootra.o confra.o smsys.o smprf.o qbusautoconf.o ${LIBSA} -lc
	@strip bootrq.x
	@dd if=bootrq.x of=bootrq ibs=32 skip=1 >/dev/null 2>&1
	@size bootrq.x
	@ls -lg bootrq; echo
	@rm bootrq.x

bootavie: relsrt0.o bootavie.o confra.o smsys.o smprf.o ${LIBSA}
	ld -o bootavie.x -N -T ${RELOC} relsrt0.o bootavie.o confra.o smsys.o smprf.o ${LIBSA} -lc
	@strip bootavie.x
	@dd if=bootavie.x of=bootavie ibs=32 skip=1 >/dev/null 2>&1
	@size bootavie.x
	@ls -lg bootavie; echo
	@rm -f bootavie.x

bootbi: relsrt0.o bootra.o confra.o smsys.o smprf.o biautoconf.o ${LIBSA}
	ld -o bootbi.x -N -T ${RELOC} relsrt0.o bootra.o confra.o smsys.o smprf.o biautoconf.o ${LIBSA} -lc
	@strip bootbi.x
	@dd if=bootbi.x of=bootbi ibs=32 skip=1 >/dev/null 2>&1
	@size bootbi.x
	@ls -lg bootbi; echo
	@rm -f bootbi.x

boothp.o: boothp.c bootxx.o
boothk.o: boothk.c bootxx.o
bootup.o: bootup.c bootxx.o
bootra.o: bootra.c bootxx.o
bootrl.o: bootrl.c bootxx.o

bootxx.o:
	touch bootxx.o

autoconf.o: autoconf.c
	cc -c ${COPTS} -DVAXBI -DVAXQBUS -DVAXSBI -S autoconf.c
	/lib/c2 -i autoconf.s | as -o $@
	@rm -f autoconf.s

sbiautoconf.o: autoconf.c
	cc -c ${INCPATH} -DSMALL -DVAXSBI -S autoconf.c
	/lib/c2 -i autoconf.s | as -o $@
	@rm -f autoconf.s

qbusautoconf.o: autoconf.c
	cc -c ${INCPATH} -DSMALL -DVAXQBUS -S autoconf.c
	/lib/c2 -i autoconf.s | as -o $@
	@rm -f autoconf.s

biautoconf.o: autoconf.c
	cc -c ${INCPATH} -DSMALL -DVAXBI -S autoconf.c
	/lib/c2 -i autoconf.s | as -o $@
	@rm -f autoconf.s

smsys.o: sys.c
	-@rm -f smsys.c
	-@ln -s sys.c smsys.c
	cc -c -DSMALL ${CFLAGS} smsys.c
	-@rm -f smsys.c

smprf.o: prf.c
	-@rm -f smprf.c
	-@ln -s prf.c smprf.c
	cc -c -DSMALL ${CFLAGS} smprf.c
	-@rm -f smprf.c

boothk.c: bootxx.c
	-rm -f boothk.c
	sed -e 's/xx/hk/g' <bootxx.c >boothk.c
boothp.c: bootxx.c
	-rm -f boothp.c
	sed -e 's/xx/hp/g' <bootxx.c >boothp.c
bootup.c: bootxx.c
	-rm -f bootup.c
	sed -e 's/xx/up/g' <bootxx.c >bootup.c
bootra.c: bootxx.c
	-rm -f bootra.c
	sed -e 's/xx/ra/g' <bootxx.c >bootra.c
bootrl.c: bootxx.c
	-rm -f bootrl.c
	sed -e 's/xx/rl/g' <bootxx.c >bootrl.c

confrk.o: confrk.c confxx.o
confhp.o: confhp.c confxx.o
confup.o: confup.c confxx.o
confra.o: confra.c confxx.o
confrl.o: confrl.c confxx.o

confxx.o:
	touch confxx.o

confrk.c: confxx.c
	-rm -f confrk.c
	sed -e 's/XX/hk/' -e 's/xx/rk/g' <confxx.c >confrk.c
confhp.c: confxx.c
	-rm -f confhp.c
	sed -e 's/XX/hp/' -e 's/xx/hp/g' <confxx.c >confhp.c
confup.c: confxx.c
	-rm -f confup.c
	sed -e 's/XX/up/' -e 's/xx/up/g' <confxx.c >confup.c
confra.c: confxx.c
	-rm -f confra.c
	sed -e 's/XX/ra/' -e 's/xx/ra/g' <confxx.c >confra.c
confrl.c: confxx.c
	-rm -f confrl.c
	sed -e 's/XX/rl/' -e 's/xx/rl/g' <confxx.c >confrl.c

# utilities

print:
	@pr makefile
	@ls -l | pr 
	@pr *.h *.c

clean:
	rm -f *.o *.exe *.i errs
	rm -f [ab].out boot cat tpboot tpcopy copy tpformat
	rm -f boot[a-z]? boot[a-wyz][a-z].c conf[a-wyz][a-z].c
	rm -f format drtest core sboot bootconf.c
	rm -f 730boot 730copy 730drtest 730format 780boot
	rm -f bootavie bootbsd bootbi
	rm -f libsa.a kdb

lint:
	lint ${COPTS} -hxbn boot.c ${SRCS} | \
	    grep -v 'possible pointer alignment' | \
	    grep -v 'struct/union .* never defined'

install: ${ALL}
	cp boot ${DESTDIR}/boot
	cp format ${DESTDIR}/format
	cp copy ${DESTDIR}/copy
	cp drtest ${DESTDIR}/drtest
	strip ${DESTDIR}/format ${DESTDIR}/copy ${DESTDIR}/drtest
	cp pcs750.bin ${DESTDIR}/pcs750.bin
	cp tpcopy ../dist/tp/copy
	cp tpboot ../dist/tp/boot
	cp tpformat ../dist/tp/format
	cp boot a.out; strip a.out; \
		dd if=a.out of=../floppy/boot bs=32 skip=1; rm a.out
	cp 730boot a.out; strip a.out; \
		dd if=a.out of=../cassette/boot.730 bs=32 skip=1; rm a.out
	cp ../floppy/boot ../cassette/boot.750
	cp ../floppy/boot ../consolerl/boot
	cp copy a.out; strip a.out; \
		dd if=a.out of=../floppy/copy bs=32 skip=1; rm a.out
	cp 730copy a.out; strip a.out; \
		dd if=a.out of=../cassette/copy.730 bs=32 skip=1; rm a.out
	cp ../floppy/copy ../cassette/copy.750
	cp ../floppy/copy ../consolerl/copy
	cp format a.out; strip a.out; \
		dd if=a.out of=../floppy/format bs=32 skip=1; rm a.out
	cp 730format a.out; strip a.out; \
		dd if=a.out of=../cassette/format.730 bs=32 skip=1; rm a.out
	cp ../floppy/format ../cassette/format.750
	cp ../floppy/format ../consolerl/format
	cp drtest a.out; strip a.out; \
		dd if=a.out of=../floppy/drtest bs=32 skip=1; rm a.out
	cp 730drtest a.out; strip a.out; \
		dd if=a.out of=../cassette/drtest.730 bs=32 skip=1; rm a.out
	cp ../floppy/drtest ../cassette/drtest.750
	cp ../floppy/drtest ../consolerl/drtest
	cp bootbi bootup boothk boothp bootra bootrl bootrq ${DESTDIR}/usr/mdec


#  Display any newly modified files

NEWSRC=.

NEWSRC: ${NEWSRC}

${NEWSRC}: Makefile *.[csh]
	@echo $?


depend:
	for i in ${SRCS} ${DUMMIES}; do \
	    cc -M ${INCPATH} $$i | \
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

# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
