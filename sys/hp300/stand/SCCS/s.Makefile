h43734
s 00000/00000/00138
d D 8.1 93/06/10 21:46:21 bostic 21 20
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00137
d D 7.20 93/05/24 22:50:34 mckusick 20 19
c change location of stand => stand.att
e
s 00006/00006/00132
d D 7.19 93/04/03 12:15:09 mckusick 19 18
c change relocation to allow for bigger MAXBSIZE
e
s 00013/00008/00125
d D 7.18 93/03/13 09:18:58 hibler 18 17
c new installation procedure
e
s 00008/00006/00125
d D 7.17 92/12/26 16:49:40 hibler 17 16
c Utah update (mostly disklabels)
e
s 00002/00003/00129
d D 7.16 92/10/11 10:01:32 bostic 16 15
c make kernel includes standard
e
s 00001/00001/00131
d D 7.15 92/07/25 10:32:59 bostic 15 14
c have to build mkboot and installboot to install anything
e
s 00001/00000/00131
d D 7.14 92/07/23 15:43:56 mckusick 14 13
c add dependencies for libsa
e
s 00006/00011/00125
d D 7.13 92/07/20 09:21:23 bostic 13 12
c minor cleanups, set permissions on installtion
e
s 00003/00003/00133
d D 7.12 92/06/27 12:50:34 mckusick 12 11
c need to run ./mkboot explicitly
e
s 00001/00001/00135
d D 7.11 92/06/18 21:43:01 hibler 11 10
c minor depend fix
e
s 00017/00010/00119
d D 7.10 92/06/18 21:33:39 hibler 10 9
c merge with latest Utah version
e
s 00002/00001/00127
d D 7.9 92/02/24 09:36:08 mckusick 9 8
c need libgnulib.a to get quads
e
s 00005/00005/00123
d D 7.8 91/05/08 21:56:05 bostic 8 7
c move libsa directory here
e
s 00001/00000/00127
d D 7.7 91/05/05 20:09:51 bostic 7 6
c clean library too
e
s 00009/00006/00118
d D 7.6 91/05/05 15:33:27 bostic 6 5
c make libsa in ../../stand
e
s 00041/00053/00083
d D 7.5 91/05/05 14:32:34 bostic 5 4
c integrate with common stand source, make look somewhat like other stand
c Makefiles
e
s 00001/00001/00135
d D 7.4 90/07/01 00:31:48 karels 4 3
c *hack hack*  include -I/usr/include so that param.h gets <machine/...> right
e
s 00010/00122/00126
d D 7.3 90/06/24 15:02:52 karels 3 2
c try to make this fly
e
s 00004/00004/00244
d D 7.2 90/05/25 16:16:45 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00248/00000/00000
d D 7.1 90/05/08 22:48:03 mckusick 1 0
c date and time created 90/05/08 22:48:03 by mckusick
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
# All rights reserved.
#
D 3
# %sccs.include.redist.c%
E 3
I 3
# %sccs.include.redist.sh%
E 3
#
E 5
#	%W% (Berkeley) %G%
D 5
#
E 5
I 5

E 5
D 3
LIBDIR=/lib
E 3
DESTDIR=
I 5
D 16
STAND=	../../stand
D 10
INCPATH=-I. -I${STAND} -I../../sys -I..
E 10
I 10
INCPATH=-I. -I${STAND} -I../.. -I../../sys -I..
E 10
VPATH=	${STAND}
E 16
I 16
D 17
INCPATH=-I../..
E 17
I 17
INCPATH=-I. -I../..
E 17
D 20
VPATH=	../../stand
E 20
I 20
VPATH=	../../stand.att
E 20
E 16
E 5

D 5
#CC=occ -Dconst= -Dvolatile= -Dsigned= -Dinline=
#AS=oas

CC=cc -Dconst=__const__ -Dvolatile=__volatile__ \
	-Dsigned=__signed__ -Dinline=__inline__ -fpcc-struct-return
E 5
I 5
D 10
CC=	cc -fpcc-struct-return
E 10
I 10
CC=cc
E 10
E 5
AS=as

D 4
INCPATH=-I. -I../sys -I..
E 4
I 4
D 5
INCPATH=-I. -I/usr/include -I../sys -I..
E 4
D 2
CONS= -DDCACONSOLE -DITECONSOLE
E 2
I 2
CONS= -DDCACONSOLE -DITECONSOLE -DDCMCONSOLE
E 2
DEFS= -DSTANDALONE ${CONS} # -DROMPRF # -DDEBUG
COPTS=
CFLAGS=	-O ${INCPATH} ${DEFS} ${COPTS}
E 5
D 19
# RELOC=FFF80000 allows for boot prog up to 7F000 (520192) bytes long
RELOC=	FFF80000
E 19
I 19
# RELOC=FFF00000 allows for boot prog up to FF000 (1044480) bytes long
RELOC=	FFF00000
E 19

D 5
SRCS=	sys.c conf.c prf.c machdep.c autoconf.c \
	hpib.c nhpib.c fhpib.c rd.c ct.c scsi.c sd.c hil.c \
D 2
	cons.c ite.c ite_subr.c ite_dv.c ite_gb.c ite_rb.c ite_tc.c dca.c
E 2
I 2
	cons.c ite.c ite_subr.c ite_dv.c ite_gb.c ite_rb.c ite_tc.c dca.c dcm.c
E 2
DUMMIES=
DRIVERS=autoconf.o hpib.o nhpib.o fhpib.o rd.o ct.o scsi.o sd.o hil.o \
D 2
	cons.o ite.o ite_subr.o ite_dv.o ite_gb.o ite_rb.o ite_tc.o dca.o
E 2
I 2
	cons.o ite.o ite_subr.o ite_dv.o ite_gb.o ite_rb.o ite_tc.o dca.o dcm.o
E 2
LIBSA=	libsa.a
E 5
I 5
CONS= -DDCACONSOLE -DITECONSOLE -DDCMCONSOLE
D 17
DEFS= -DSTANDALONE ${CONS} # -DROMPRF
E 17
I 17
DEFS= -DSTANDALONE -DCOMPAT_NOLABEL ${CONS} # -DROMPRF
E 17
CFLAGS=	-O ${INCPATH} ${DEFS}
E 5

I 5
DRIVERS=autoconf.c cons.c ct.c dca.c dcm.c fhpib.c hil.c hpib.c ite.c \
D 10
	ite_dv.c ite_gb.c ite_rb.c ite_subr.c ite_tc.c nhpib.c rd.c \
E 10
I 10
	ite_dv.c ite_gb.c ite_hy.c ite_rb.c ite_subr.c ite_tc.c nhpib.c rd.c \
E 10
	scsi.c sd.c
D 6
SASRC=  bmap.c close.c dev.c getfile.c gets.c ioctl.c lseek.c open.c \
	printf.c read.c sys.c write.c
SRCS=	conf.c machdep.c prf.c ${SASRC} ${DRIVERS}
LIBS=	libsa.a ${DESTDIR}/usr/lib/libc.a
E 6
I 6
D 17
SRCS=	conf.c machdep.c prf.c ${DRIVERS}
E 17
I 17
SRCS=	conf.c label.c machdep.c prf.c ${DRIVERS}
E 17
D 8
LIBS=	${STAND}/obj/libsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
E 8
I 8
D 9
LIBS=	libsa/libsa.a libdrive.a ${DESTDIR}/usr/lib/libc.a
E 9
I 9
LIBS=	libsa/libsa.a libdrive.a ${DESTDIR}/usr/lib/libgnulib.a \
	${DESTDIR}/usr/lib/libc.a
E 9
E 8
E 6

E 5
D 15
ALL=	dboot nboot tboot tcopy
E 15
I 15
ALL=	dboot nboot tboot tcopy mkboot installboot
E 15

all: ${ALL}

D 5
${LIBSA}: sys.o conf.o ${DRIVERS} prf.o machdep.o
	ar crv ${LIBSA} $?
	ranlib ${LIBSA}
E 5
I 5
D 6
libsa.a: conf.o machdep.o prf.o ${DRIVERS:.c=.o} ${SASRC:.c=.o}
E 6
I 6
D 8
dboot nboot tboot tcopy: ${STAND}/obj/libsa.a libdrive.a
E 8
I 8
dboot nboot tboot tcopy: ${LIBS}
E 8

D 8
${STAND}/obj/libsa.a:
	cd ${STAND}; make
E 8
I 8
D 17
libsa/libsa.a::
E 17
I 17
libsa/libsa.a: FRC
E 17
	cd libsa; make
E 8

D 17
libdrive.a: conf.o machdep.o prf.o ${DRIVERS:.c=.o}
E 17
I 17
libdrive.a: conf.o label.o machdep.o prf.o ${DRIVERS:.c=.o}
E 17
E 6
	ar crv $@ $?
	ranlib $@
E 5

${DRIVERS}: samachdep.h
D 5
	${CC} -c ${CFLAGS} $*.c
E 5

I 10
# depend on DEFS

D 17
machdep.o srt0.o: Makefile
E 17
I 17
label.o machdep.o srt0.o: Makefile
E 17
cons.o dca.o hil.o: Makefile
ite.o ite_subr.o ite_dv.o ite_gb.o ite_hy.o ite_rb.o ite_tc.o: Makefile

E 10
# startups

srt0.o: srt0.c
D 5
	${CC} -E ${INCPATH} ${DEFS} ${COPTS} srt0.c | ${AS} -o srt0.o
E 5
I 5
	${CC} -E ${INCPATH} ${DEFS} srt0.c | ${AS} -o srt0.o
E 5

tpsrt0.o: srt0.c
D 5
	${CC} -E ${INCPATH} ${DEFS} ${COPTS} -DTP srt0.c | ${AS} -o tpsrt0.o
E 5
I 5
	${CC} -E ${INCPATH} ${DEFS} -DTP srt0.c | ${AS} -o tpsrt0.o
E 5

# bootable from tape

D 5
tboot:	tboot.o srt0.o ${LIBSA}
D 3
	ld -N -T ${RELOC} -e begin srt0.o tboot.o -L${LIBDIR} ${LIBSA} -lc -o tboot
E 3
I 3
	ld -N -T ${RELOC} -e begin srt0.o tboot.o ${LIBSA} -lc -o tboot
E 5
I 5
tboot:	tboot.o srt0.o ${LIBS}
	ld -N -T ${RELOC} -e begin srt0.o tboot.o ${LIBS} -o $@
E 5
E 3
	@size tboot
D 19
	@echo tboot total size should not exceed 520192 bytes
E 19
I 19
	@echo tboot total size should not exceed 1044480 bytes
E 19

D 3
tboot.o: boot.c ../h/param.h ../ufs/inode.h ../ufs/fs.h
tboot.o: saio.h ../h/reboot.h ../h/vm.h
E 3
I 3
tboot.o: boot.o
E 3
	cp boot.c tboot.c; chmod +w tboot.c
D 5
	${CC} -c -O ${INCPATH} ${COPTS} -DJUSTASK tboot.c
E 5
I 5
D 10
	${CC} -c -O ${INCPATH} -DJUSTASK tboot.c
E 10
I 10
	${CC} -c ${CFLAGS} -DJUSTASK tboot.c
E 10
E 5
	rm -f tboot.c

D 5
tcopy:	copy.o tpsrt0.o ${LIBSA}
D 3
	ld -N -T ${RELOC} -e begin tpsrt0.o copy.o -L${LIBDIR} ${LIBSA} -lc -o tcopy
E 3
I 3
	ld -N -T ${RELOC} -e begin tpsrt0.o copy.o ${LIBSA} -lc -o tcopy
E 5
I 5
tcopy:	copy.o tpsrt0.o ${LIBS}
	ld -N -T ${RELOC} -e begin tpsrt0.o copy.o ${LIBS} -o $@
E 5
E 3
	@size tcopy
D 19
	@echo tcopy total size should not exceed 520192 bytes
E 19
I 19
	@echo tcopy total size should not exceed 1044480 bytes
E 19

# bootable from floppy or real disks

D 5
dboot:	boot.o srt0.o bootconf.o ${LIBSA}
D 3
	ld -N -T ${RELOC} -e begin -o dboot srt0.o boot.o bootconf.o -L${LIBDIR} ${LIBSA} -lc
E 3
I 3
	ld -N -T ${RELOC} -e begin -o dboot srt0.o boot.o bootconf.o ${LIBSA} -lc
E 5
I 5
dboot:	boot.o srt0.o bootconf.o ${LIBS}
	ld -N -T ${RELOC} -e begin srt0.o boot.o bootconf.o ${LIBS} -o $@ 
E 5
E 3
	@size dboot
	@echo dboot text+data size should not exceed 57344 bytes
D 19
	@echo dboot total size should not exceed 520192 bytes
E 19
I 19
	@echo dboot total size should not exceed 1044480 bytes
E 19

bootconf.o: conf.o
D 5
	cp conf.c bootconf.c
	${CC} -c ${INCPATH} ${COPTS} -DBOOT bootconf.c
E 5
	rm -f bootconf.c
I 5
	ln -s conf.c bootconf.c
D 10
	${CC} -c ${INCPATH} -DBOOT bootconf.c
E 10
I 10
	${CC} -c ${CFLAGS} -DBOOT bootconf.c
E 10
	rm -f bootconf.c
E 5

D 10
# non-secure boot
E 10
I 10
# non-secure boot (allows booting non-root owned or world writable kernels)
E 10

D 5
nboot:	nboot.o srt0.o bootconf.o ${LIBSA}
D 3
	ld -N -T ${RELOC} -e begin -o nboot srt0.o nboot.o bootconf.o -L${LIBDIR} ${LIBSA} -lc
E 3
I 3
	ld -N -T ${RELOC} -e begin -o nboot srt0.o nboot.o bootconf.o ${LIBSA} -lc
E 5
I 5
nboot:	nboot.o srt0.o bootconf.o ${LIBS}
	ld -N -T ${RELOC} -e begin -o nboot srt0.o nboot.o bootconf.o ${LIBS}
E 5
E 3
	@size nboot
	@echo nboot text+data size should not exceed 57344 bytes
D 19
	@echo nboot total size should not exceed 520192 bytes
E 19
I 19
	@echo nboot total size should not exceed 1044480 bytes
E 19

D 3
nboot.o: boot.c ../h/param.h ../ufs/inode.h ../ufs/fs.h
nboot.o: saio.h ../h/reboot.h ../h/vm.h
E 3
I 3
nboot.o: boot.o
E 3
D 5
	cp boot.c nboot.c; chmod +w nboot.c
	${CC} -c -O ${INCPATH} ${COPTS} -DINSECURE ${DEFS} nboot.c
E 5
	rm -f nboot.c
I 5
	ln -s boot.c nboot.c
D 10
	${CC} -c -O ${INCPATH} -DINSECURE ${DEFS} nboot.c
E 10
I 10
	${CC} -c ${CFLAGS} -DINSECURE nboot.c
E 10
	rm -f nboot.c
E 5

D 5
dcopy:   copy.o srt0.o conf.o ${LIBSA}
D 3
	ld -N -T ${RELOC} -e begin -o dcopy srt0.o copy.o conf.o -L${LIBDIR} ${LIBSA} -lc
E 3
I 3
	ld -N -T ${RELOC} -e begin -o dcopy srt0.o copy.o conf.o ${LIBSA} -lc
E 5
I 5
D 10
dcopy: copy.o srt0.o conf.o ${LIBS}
E 10
I 10
dcopy:	copy.o srt0.o conf.o ${LIBS}
E 10
	ld -N -T ${RELOC} -e begin -o dcopy srt0.o copy.o conf.o ${LIBS}
E 5
E 3

mkboot: mkboot.c
	${CC} ${CFLAGS} -o mkboot mkboot.c

D 18
installboot: installboot.c
	${CC} ${CFLAGS} -o installboot installboot.c
E 18
I 18
installboot: installboot.sh
	@rm -f installboot
	cp -p installboot.sh installboot
E 18

# utilities

D 5
print:
	@pr makefile
	@ls -l | pr 
	@pr *.h *.c

E 5
D 13
clean:
	rm -f *.o *.exe *.i errs make.out
E 13
I 13
clean cleandir:
	rm -f .depend *.o *.exe *.i errs make.out
E 13
	rm -f a.out boot cat tpboot tpcopy copy tpformat
	rm -f boot[a-z]? boot[a-wyz][a-z].c conf[a-wyz][a-z].c
D 5
	rm -f format drtest core sboot bootconf.c
E 5
I 5
	rm -f format drtest core sboot bootconf.c nboot.c
E 5
D 6
	rm -f libsa.a mkboot tboot tcopy dboot nboot installboot *.lif
E 6
I 6
	rm -f libdrive.a mkboot tboot tcopy dboot nboot installboot *.lif
I 7
D 8
	cd ${STAND}; make clean
E 8
I 8
	cd libsa; make cleandir
E 8
E 7
E 6

D 13
lint:
D 5
	lint ${INCPATH} ${COPTS} -hxbn boot.c ${SRCS} | \
E 5
I 5
	lint ${INCPATH} -hxbn boot.c ${SRCS} | \
E 5
	    grep -v 'possible pointer alignment' | \
	    grep -v 'struct/union .* never defined'

install: mkboot installboot ${ALL}
E 13
I 13
D 18
install:
E 18
I 18
install: mkboot installboot ${ALL}
E 18
E 13
D 12
	mkboot dboot diskboot.lif
	mkboot nboot ndiskboot.lif
	mkboot tboot tcopy tapeboot.lif
E 12
I 12
	./mkboot dboot diskboot.lif
	./mkboot nboot ndiskboot.lif
	./mkboot tboot tcopy tapeboot.lif
E 12
D 13
	install -c -s installboot ${DESTDIR}/usr/mdec
	install -c -m 644 diskboot.lif ${DESTDIR}/usr/mdec/bootrd
E 13
I 13
D 18
	install -s -o bin -g bin -m 555 installboot ${DESTDIR}/usr/mdec
	install -o bin -g bin -m 444 diskboot.lif ${DESTDIR}/usr/mdec/bootrd
E 18
I 18
	install -o bin -g bin -m 555 installboot ${DESTDIR}/usr/mdec
	install -o bin -g bin -m 444 diskboot.lif ${DESTDIR}/usr/mdec/rdboot
	rm -f ${DESTDIR}/usr/mdec/bootrd
	ln ${DESTDIR}/usr/mdec/rdboot ${DESTDIR}/usr/mdec/bootrd
	rm -f ${DESTDIR}/usr/mdec/sdboot
	ln ${DESTDIR}/usr/mdec/rdboot ${DESTDIR}/usr/mdec/sdboot
E 18
E 13
	rm -f ${DESTDIR}/usr/mdec/bootsd
D 18
	ln ${DESTDIR}/usr/mdec/bootrd ${DESTDIR}/usr/mdec/bootsd
D 13
	install -c -m 644 tapeboot.lif ${DESTDIR}/usr/mdec/bootct
E 13
I 13
	install -o bin -g bin -m 444 tapeboot.lif ${DESTDIR}/usr/mdec/bootct
E 18
I 18
	ln ${DESTDIR}/usr/mdec/sdboot ${DESTDIR}/usr/mdec/bootsd
	install -o bin -g bin -m 444 tapeboot.lif ${DESTDIR}/usr/mdec/ctboot
E 18
E 13
D 10
	mv diskboot.lif ndiskboot.lif tapeboot.lif ${DESTDIR}/sys/hpdist/tp
E 10
I 10
#	mv diskboot.lif ndiskboot.lif tapeboot.lif ${DESTDIR}/sys/hpdist/tp
E 10

D 3
depend:
	for i in ${SRCS} ${DUMMIES}; do \
D 2
	    ${CC} -M ${INCPATH} $$i | \
E 2
I 2
	    ${CC} -M ${INCPATH} ${DEFS} $$i | \
E 2
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

sys.o : sys.c saio.h ../h/types.h ../h/param.h ../sys/syslimits.h \
  ../sys/types.h ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h ../ufs/inode.h ../ufs/dinode.h \
  ../ufs/fs.h ../ufs/dir.h ../sys/stat.h 

conf.o : conf.c saio.h ../h/types.h ../h/param.h ../sys/syslimits.h \
  ../sys/types.h ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h ../ufs/inode.h ../ufs/dinode.h \
  ../ufs/fs.h 

prf.o : prf.c ../h/param.h ../sys/syslimits.h ../sys/types.h \
  ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h 

machdep.o : machdep.c ../sys/param.h ../sys/syslimits.h ../sys/types.h \
  ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h 

autoconf.o : autoconf.c samachdep.h ../sys/param.h ../sys/syslimits.h \
  ../sys/types.h ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h ../hpdev/device.h ../hpdev/grfvar.h 

hpib.o : hpib.c ../h/reboot.h ../hpdev/device.h hpibvar.h saio.h \
  ../h/types.h ../h/param.h ../sys/syslimits.h ../sys/types.h ../sys/signal.h \
  /usr/include/machine/trap.h /usr/include/machine/machparam.h \
  /usr/include/machine/endian.h /usr/include/machine/machlimits.h \
  ../ufs/inode.h ../ufs/dinode.h ../ufs/fs.h samachdep.h 

nhpib.o : nhpib.c ../sys/param.h ../sys/syslimits.h ../sys/types.h \
  ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h ../hpdev/nhpibreg.h hpibvar.h 

fhpib.o : fhpib.c ../sys/param.h ../sys/syslimits.h ../sys/types.h \
  ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h ../hpdev/fhpibreg.h hpibvar.h 

rd.o : rd.c saio.h ../h/types.h ../h/param.h ../sys/syslimits.h \
  ../sys/types.h ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h ../ufs/inode.h ../ufs/dinode.h \
  ../ufs/fs.h samachdep.h ../hpdev/rdreg.h 

ct.o : ct.c ../h/types.h ../hpdev/ctreg.h saio.h ../h/param.h \
  ../sys/syslimits.h ../sys/types.h ../sys/signal.h \
  /usr/include/machine/trap.h /usr/include/machine/machparam.h \
  /usr/include/machine/endian.h /usr/include/machine/machlimits.h \
  ../ufs/inode.h ../ufs/dinode.h ../ufs/fs.h samachdep.h 

scsi.o : scsi.c ../h/types.h ../h/reboot.h ../hpdev/device.h \
  ../hpdev/scsireg.h ../sys/ioctl.h scsivar.h saio.h ../h/param.h \
  ../sys/syslimits.h ../sys/types.h ../sys/signal.h \
  /usr/include/machine/trap.h /usr/include/machine/machparam.h \
  /usr/include/machine/endian.h /usr/include/machine/machlimits.h \
  ../ufs/inode.h ../ufs/dinode.h ../ufs/fs.h samachdep.h 

sd.o : sd.c saio.h ../h/types.h ../h/param.h ../sys/syslimits.h \
  ../sys/types.h ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h ../ufs/inode.h ../ufs/dinode.h \
  ../ufs/fs.h samachdep.h ../hpdev/scsireg.h ../sys/ioctl.h 

hil.o : hil.c samachdep.h 

cons.o : cons.c ../sys/param.h ../sys/syslimits.h ../sys/types.h \
  ../sys/signal.h /usr/include/machine/trap.h \
  /usr/include/machine/machparam.h /usr/include/machine/endian.h \
  /usr/include/machine/machlimits.h samachdep.h /usr/include/machine/cons.h 

ite.o : ite.c samachdep.h 

ite_subr.o : ite_subr.c samachdep.h 

ite_dv.o : ite_dv.c samachdep.h 

ite_gb.o : ite_gb.c samachdep.h 

ite_rb.o : ite_rb.c samachdep.h 

ite_tc.o : ite_tc.c samachdep.h 

dca.o : dca.c 
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 3
I 3
depend: ${SRCS}
D 5
	mkdep ${INCPATH} -DSTANDALONE ${SRCS} ${DUMMIES}
E 5
I 5
D 10
	mkdep ${INCPATH} -DSTANDALONE ${SRCS}
E 10
I 10
D 11
	mkdep ${INCPATH} ${DEFS} ${SRCS} mkboot.c installboot.c
E 11
I 11
	mkdep ${INCPATH} ${DEFS} ${SRCS}
E 11
D 18
	mkdep -a -p ${INCPATH} ${DEFS} mkboot.c installboot.c
E 18
I 18
	mkdep -a -p ${INCPATH} ${DEFS} mkboot.c
E 18
I 14
	cd libsa; make depend
I 17

FRC:
E 17
E 14
E 10
E 5
E 3
E 1
