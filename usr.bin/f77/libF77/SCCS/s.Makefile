h12595
s 00001/00000/00065
d D 5.13 91/01/17 15:09:38 bostic 23 21
c kernel reorg
e
s 00001/00000/00065
d R 5.13 91/01/15 18:16:38 bostic 22 21
c kernel reorg
e
s 00015/00015/00050
d D 5.12 90/06/23 13:08:17 bostic 21 20
c build profiled version with ld -X flag, use -R flag for Version.c;
c other cleanups, from Chris Torek
e
s 00032/00093/00033
d D 5.11 90/05/11 12:53:24 bostic 20 19
c first pass for new make
e
s 00016/00015/00110
d D 5.10 90/03/22 11:23:11 bostic 19 18
c checked in for Kirk, his changes for obj directories
e
s 00002/00002/00123
d D 5.9 89/09/04 11:34:30 bostic 18 17
c typo
e
s 00094/00349/00031
d D 5.8 89/05/10 22:34:34 bostic 17 16
c major cleanup... I hate mkmf...
e
s 00001/00001/00379
d D 5.7 87/09/14 15:01:11 bostic 16 14
c remove Usef on make clean; bug report 4.3BSD/usr.lib/57
e
s 00250/00355/00025
d R 5.7 87/06/21 16:42:26 bostic 15 14
c new template
e
s 00001/00001/00379
d D 5.6 86/10/30 21:49:52 sam 14 13
c add -f on mv for Version
e
s 00001/00001/00379
d D 5.5 86/10/30 21:45:27 sam 13 11
c add Usef and mkvers to clean
e
s 00001/00001/00379
d R 5.5 86/10/30 21:13:46 sam 12 11
c remove Usef on clean
e
s 00002/00000/00378
d D 5.4 85/08/09 16:24:54 jerry 11 10
c add d_dprod for prod() under -r8
e
s 00015/00002/00363
d D 5.3 85/07/09 16:08:48 jerry 10 9
c Use -f to get around C bug
e
s 00000/00002/00365
d D 5.2 85/06/26 19:06:13 jerry 9 8
c move f77_abort() and no_lg.c to libI77.
e
s 00007/00002/00360
d D 5.1 85/06/07 23:34:08 kre 8 7
c Add copyright
e
s 00000/00006/00362
d D 1.7 85/06/07 11:50:44 jerry 7 6
c delete {cabs,d_sqrt,z_abs}.o from lib so get libm assembler versions.
e
s 00002/00000/00366
d D 1.6 85/06/04 21:23:42 libs 6 5
c add no_lg.{c,o} to check directly for -lg in f77_abort().
e
s 00000/00002/00366
d D 1.5 85/06/04 17:52:20 libs 5 4
c delete bit.c
e
s 00000/00004/00368
d D 1.4 85/05/06 14:22:03 libs 4 3
c delete sinh.[o,c], tanh.[o,c] as these duplicate ones in libm.a
e
s 00002/00000/00370
d D 1.3 85/03/28 10:59:09 ralph 3 2
c added trpfpe_.c
e
s 00002/00000/00368
d D 1.2 85/03/28 10:54:44 ralph 2 1
c added random_.c
e
s 00368/00000/00000
d D 1.1 83/05/20 14:54:17 nicklin 1 0
c date and time created 83/05/20 14:54:17 by nicklin
e
u
U
t
T
I 1
D 8
# Makefile for f77 math & startup lib, libF77.a
E 8
D 20
#
D 8
# %W% (Berkeley) %G%
E 8
I 8
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 20
#	%W% (Berkeley) %G%
D 20
#
# Makefile for f77 math & startup lib, libF77.a
E 20
E 8

D 17
CFLAGS	      = -O
E 17
I 17
D 20
CFLAGS=	-O
FFLAGS=	-O
DEST=	${DESTDIR}/usr/lib
LIBRARY=libF77.a
LIBRARY_P=libF77_p.a
OPTIONS=-DUCBVAX
OBJS=	abort_.o besj0_.o besj1_.o besjn_.o besy0_.o besy1_.o besyn_.o \
	c_abs.o c_cos.o c_div.o c_exp.o c_log.o c_sin.o c_sqrt.o d_abs.o \
	d_acos.o d_asin.o d_atan.o d_atn2.o d_cnjg.o d_cos.o d_cosh.o \
	d_dim.o d_dprod.o d_exp.o d_imag.o d_int.o d_lg10.o d_log.o \
	d_mod.o d_nint.o d_prod.o d_sign.o d_sin.o d_sinh.o d_tan.o \
	d_tanh.o dbesj0_.o dbesj1_.o dbesjn_.o dbesy0_.o dbesy1_.o \
	dbesyn_.o derf_.o derfc_.o ef1asc_.o ef1cmc_.o erf_.o erfc_.o \
	exit_.o h_abs.o h_dim.o h_dnnt.o h_indx.o h_len.o h_mod.o h_nint.o \
	h_sign.o hl_ge.o hl_gt.o hl_le.o hl_lt.o i_abs.o i_dim.o i_dnnt.o \
	i_indx.o i_len.o i_mod.o i_nint.o i_sign.o l_ge.o l_gt.o l_le.o \
	l_lt.o lnblnk_.o long_.o main.o pow_ci.o pow_dd.o pow_di.o pow_hh.o \
	pow_ii.o pow_ri.o pow_zi.o pow_zz.o r_abs.o r_acos.o r_asin.o \
	r_atan.o r_atn2.o r_cnjg.o r_cos.o r_cosh.o r_dim.o r_exp.o \
	r_imag.o r_int.o r_lg10.o r_log.o r_mod.o r_nint.o r_sign.o r_sin.o \
	r_sinh.o r_sqrt.o r_tan.o r_tanh.o rand_.o random_.o range.o \
	rindex_.o s_cat.o s_cmp.o s_copy.o s_paus.o s_rnge.o s_stop.o \
	short_.o signal_.o subout.o traper_.o trapov_.o trpfpe_.o z_cos.o \
	z_div.o z_exp.o z_log.o z_sin.o z_sqrt.o
E 20
I 20
LIB=	F77
I 23
CFLAGS+=-I/sys
E 23
E 20
SRCS=	abort_.c besj0_.c besj1_.c besjn_.c besy0_.c besy1_.c besyn_.c \
	c_abs.c c_cos.c c_div.c c_exp.c c_log.c c_sin.c c_sqrt.c d_abs.c \
	d_acos.c d_asin.c d_atan.c d_atn2.c d_cnjg.c d_cos.c d_cosh.c \
	d_dim.c d_dprod.c d_exp.c d_imag.c d_int.c d_lg10.c d_log.c \
	d_mod.c d_nint.c d_prod.c d_sign.c d_sin.c d_sinh.c d_tan.c d_tanh.c \
	dbesj0_.c dbesj1_.c dbesjn_.c dbesy0_.c dbesy1_.c dbesyn_.c derf_.c \
	derfc_.c ef1asc_.c ef1cmc_.c erf_.c erfc_.c exit_.c h_abs.c \
	h_dim.c h_dnnt.c h_indx.c h_len.c h_mod.c h_nint.c h_sign.c hl_ge.c \
	hl_gt.c hl_le.c hl_lt.c i_abs.c i_dim.c i_dnnt.c i_indx.c i_len.c \
	i_mod.c i_nint.c i_sign.c l_ge.c l_gt.c l_le.c l_lt.c lnblnk_.c \
	long_.c main.c pow_ci.c pow_dd.c pow_di.c pow_hh.c pow_ii.c pow_ri.c \
	pow_zi.c pow_zz.c r_abs.c r_acos.c r_asin.c r_atan.c r_atn2.c \
	r_cnjg.c r_cos.c r_cosh.c r_dim.c r_exp.c r_imag.c r_int.c \
	r_lg10.c r_log.c r_mod.c r_nint.c r_sign.c r_sin.c r_sinh.c r_sqrt.c \
	r_tan.c r_tanh.c rand_.c random_.c range.c rindex_.c s_cat.c \
	s_cmp.c s_copy.c s_paus.c s_rnge.c s_stop.c short_.c signal_.c \
	subout.c traper_.c trapov_.c trpfpe_.c z_cos.c z_div.c z_exp.c \
	z_log.c z_sin.c z_sqrt.c
E 17

D 17
DEST	      = $(DESTDIR)/usr/lib
E 17
I 17
D 20
all: Version ${LIBRARY} ${LIBRARY_P}
E 20
I 20
LDADD=		Version.o
CLEANFILES+=	Usef Version.o Version.c mkvers
E 20
E 17

D 17
DESTDIR	      =
E 17
I 17
D 20
${LIBRARY}: ${OBJS}
		@echo "Loading ${LIBRARY} ... "
D 18
		@ar cru ${LIBRARY} ${OBJS) Version
E 18
I 18
D 19
		@ar cru ${LIBRARY} ${OBJS} Version
E 18
		ranlib ${LIBRARY}
E 19
I 19
		@if [ -d obj ]; then cd obj; fi; \
			ar cru ${LIBRARY} ${OBJS} Version; \
			ranlib ${LIBRARY}
E 20
I 20
D 21
all: Usef Version.o
E 21
I 21
libF77.a libF77_p.a:: Version.o
E 21
E 20
E 19
E 17

D 17
EXTHDRS	      =
E 17
I 17
D 20
${LIBRARY_P}: ${OBJS}
		@echo "Loading ${LIBRARY_P} ... "
D 18
		@cd profiled; ar cru ../${LIBRARY_P} ${OBJS) Version
E 18
I 18
D 19
		@cd profiled; ar cru ../${LIBRARY_P} ${OBJS} Version
E 18
		ranlib ${LIBRARY_P}
E 19
I 19
		@if [ -d obj ]; then cd obj; fi; \
			cd profiled; ar cru ../${LIBRARY_P} ${OBJS} Version; \
			ranlib ../${LIBRARY_P}
E 19
E 17

D 17
FFLAGS	      = -O
E 17
I 17
D 19
Version: ${SRCS} mkvers
E 19
I 19
Version: ${SRCS} obj/mkvers
E 19
	@rm -f Version.c
D 19
	./mkvers ${LIBRARY} ${SRCS} > Version.c
E 19
I 19
	./obj/mkvers ${LIBRARY} ${SRCS} > Version.c
E 20
I 20
Version.o: Version.c
E 20
E 19
D 21
	${CC} -c Version.c
E 21
I 21
	${CC} -R -c Version.c
E 21
D 19
	mv -f Version.o Version
E 19
I 19
D 20
	mv -f obj/Version.o obj/Version
E 19
	@rm -f profiled/Version
D 19
	ln Version profiled/Version
E 19
I 19
	ln obj/Version profiled/Version
E 20
E 19
E 17

I 20
Version.c: mkvers ${SRCS}
	mkvers libF77.a ${.ALLSRC:M*.c} > ${.TARGET}

E 20
D 17
HDRS	      = opcodes.h
E 17
I 17
mkvers: mkvers.c
D 20
	@${CC} mkvers.c -o mkvers
E 20
I 20
	${CC} ${CFLAGS} ${.CURDIR}/mkvers.c -o ${.TARGET}
E 20
E 17

D 17
LIBRARY	      = libF77.a
E 17
I 17
D 20
clean:
D 19
	rm -f ${OBJS} Usef profiled/*.o ${LIBRARY} ${LIBRARY_P} Usef mkvers
E 19
I 19
	rm -f ${OBJS} obj/Usef profiled/*.o ${LIBRARY} ${LIBRARY_P} obj/mkvers
E 20
I 20
Usef: Usef.c
	${CC} ${CFLAGS} ${.CURDIR}/Usef.c -o ${.TARGET}
E 20
E 19
E 17

D 17
LIBRARY_P     = libF77_p.a
E 17
I 17
D 20
cleandir: clean
	rm -f ${MAN} tags .depend
E 20
I 20
trapov_.o trapov_.po: trapov_.c
D 21
	${CC} -S -DUCBVAX ${.CURDIR}/trapov_.c
E 21
I 21
	${CC} -S -DUCBVAX ${.CURDIR}/trapov_.c;
E 21
	(echo "g/.set	L[0-9][0-9]*,0x0$$/s/0x0/0xf10/"; echo "x") | \
	    ex - trapov_.s;
	${AS} trapov_.s -o ${.TARGET}
	rm -f trapov_.s
E 20
E 17

D 17
MAKEFILE      = Makefile
E 17
I 17
D 20
depend:
	mkdep ${SRCS}
E 20
I 20
.include <bsd.lib.mk>
E 20
E 17

D 17
OBJS	      = abort_.o \
		besj0_.o \
		besj1_.o \
		besjn_.o \
		besy0_.o \
		besy1_.o \
		besyn_.o \
D 5
		bit.o \
E 5
		c_abs.o \
		c_cos.o \
		c_div.o \
		c_exp.o \
		c_log.o \
		c_sin.o \
		c_sqrt.o \
D 7
		cabs.o \
E 7
		d_abs.o \
		d_acos.o \
		d_asin.o \
		d_atan.o \
		d_atn2.o \
		d_cnjg.o \
		d_cos.o \
		d_cosh.o \
		d_dim.o \
I 11
		d_dprod.o \
E 11
		d_exp.o \
		d_imag.o \
		d_int.o \
		d_lg10.o \
		d_log.o \
		d_mod.o \
		d_nint.o \
		d_prod.o \
		d_sign.o \
		d_sin.o \
		d_sinh.o \
D 7
		d_sqrt.o \
E 7
		d_tan.o \
		d_tanh.o \
		dbesj0_.o \
		dbesj1_.o \
		dbesjn_.o \
		dbesy0_.o \
		dbesy1_.o \
		dbesyn_.o \
		derf_.o \
		derfc_.o \
		ef1asc_.o \
		ef1cmc_.o \
		erf_.o \
		erfc_.o \
		exit_.o \
		h_abs.o \
		h_dim.o \
		h_dnnt.o \
		h_indx.o \
		h_len.o \
		h_mod.o \
		h_nint.o \
		h_sign.o \
		hl_ge.o \
		hl_gt.o \
		hl_le.o \
		hl_lt.o \
		i_abs.o \
		i_dim.o \
		i_dnnt.o \
		i_indx.o \
		i_len.o \
		i_mod.o \
		i_nint.o \
		i_sign.o \
		l_ge.o \
		l_gt.o \
		l_le.o \
		l_lt.o \
		lnblnk_.o \
		long_.o \
		main.o \
I 6
D 9
		no_lg.o \
E 9
E 6
		pow_ci.o \
		pow_dd.o \
		pow_di.o \
		pow_hh.o \
		pow_ii.o \
		pow_ri.o \
		pow_zi.o \
		pow_zz.o \
		r_abs.o \
		r_acos.o \
		r_asin.o \
		r_atan.o \
		r_atn2.o \
		r_cnjg.o \
		r_cos.o \
		r_cosh.o \
		r_dim.o \
		r_exp.o \
		r_imag.o \
		r_int.o \
		r_lg10.o \
		r_log.o \
		r_mod.o \
		r_nint.o \
		r_sign.o \
		r_sin.o \
		r_sinh.o \
		r_sqrt.o \
		r_tan.o \
		r_tanh.o \
		rand_.o \
I 2
		random_.o \
E 2
		range.o \
		rindex_.o \
		s_cat.o \
		s_cmp.o \
		s_copy.o \
		s_paus.o \
		s_rnge.o \
		s_stop.o \
		short_.o \
		signal_.o \
D 4
		sinh.o \
E 4
		subout.o \
D 4
		tanh.o \
E 4
		traper_.o \
		trapov_.o \
I 3
		trpfpe_.o \
E 3
D 7
		z_abs.o \
E 7
		z_cos.o \
		z_div.o \
		z_exp.o \
		z_log.o \
		z_sin.o \
		z_sqrt.o
E 17
I 17
D 20
install: ${MAN}
	install -o bin -g bin -m 644 ${LIBRARY} ${DEST}/${LIBRARY}
	ranlib -t ${DEST}/${LIBRARY}
	install -o bin -g bin -m 644 ${LIBRARY_P} ${DEST}/${LIBRARY_P}
	ranlib -t ${DEST}/${LIBRARY_P}
E 20
I 20
# 'Usef' is part of a kuldge to get around a bug in the C compiler.
D 21
# C (sec. 9.10 of C ref manual) should round the return value of
# functions of type float from double to float.  It doesn't, so f77
# truncates it losing a half bit of accuracy.  See file Test_float
# for a test.  When it is fixed, get rid of Usef & the extraneous
# stores in pow_ri, r_dim, r_mod, r_nint.
E 21
I 21
# C (sec. 9.10 of C ref manual) should round the return value of functions of
# type float from double to float.  It doesn't, so f77 truncates it losing a
# half bit of accuracy.  See file Test_float for a test.  When it is fixed,
# get rid of Usef & the extraneous stores in pow_ri, r_dim, r_mod, r_nint.
E 21
E 20
E 17

D 17
OLDDIR	      = $(DESTDIR)/usr/old/lib
E 17
I 17
D 20
tags: ${SRCS}
	ctags ${SRCS}
E 20
I 20
D 21
.c.o:
E 21
I 21
.if (${MACHINE} == "vax" || ${MACHINE} == "tahoe")
.c.o: Usef
E 21
	${CC} `Usef ${.PREFIX}` ${CFLAGS} -c ${.IMPSRC} -o ${.TARGET}
D 21
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 21
I 21
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 21
E 20
E 17

D 17
OPTIONS	      = -DUCBVAX
E 17
I 17
D 20
trapov_.o: trapov_.c
	${CC} -S $(OPTIONS) trapov_.c;
	(echo "g/.set	L[0-9][0-9]*,0x0$$/s/0x0/0xf10/"; echo "x") \
		| ex - trapov_.s;
	as trapov_.s -o trapov_.o;
D 19
	mv trapov_.o profiled/trapov_.o
E 19
I 19
	mv obj/trapov_.o profiled/trapov_.o
E 19
	rm trapov_.s
	${CC} -S $(OPTIONS) trapov_.c
	(echo "g/.set	L[0-9][0-9]*,0x0$$/s/0x0/0xf10/"; echo "x") \
		| ex - trapov_.s
	as trapov_.s -o trapov_.o
	rm trapov_.s
E 20
I 20
D 21
.c.po:
E 21
I 21
.c.po: Usef
E 21
	${CC} -p `Usef ${.PREFIX}` ${CFLAGS} -c ${.IMPSRC} -o ${.TARGET}
D 21
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}
E 20
E 17

E 21
I 21
	@${LD} -X -r ${.TARGET}
	@mv a.out ${.TARGET}
.endif
E 21
D 17
PRINT	      = pr

SRCS	      = abort_.c \
		besj0_.c \
		besj1_.c \
		besjn_.c \
		besy0_.c \
		besy1_.c \
		besyn_.c \
D 5
		bit.c \
E 5
		c_abs.c \
		c_cos.c \
		c_div.c \
		c_exp.c \
		c_log.c \
		c_sin.c \
		c_sqrt.c \
D 7
		cabs.c \
E 7
		d_abs.c \
		d_acos.c \
		d_asin.c \
		d_atan.c \
		d_atn2.c \
		d_cnjg.c \
		d_cos.c \
		d_cosh.c \
		d_dim.c \
I 11
		d_dprod.c \
E 11
		d_exp.c \
		d_imag.c \
		d_int.c \
		d_lg10.c \
		d_log.c \
		d_mod.c \
		d_nint.c \
		d_prod.c \
		d_sign.c \
		d_sin.c \
		d_sinh.c \
D 7
		d_sqrt.c \
E 7
		d_tan.c \
		d_tanh.c \
		dbesj0_.c \
		dbesj1_.c \
		dbesjn_.c \
		dbesy0_.c \
		dbesy1_.c \
		dbesyn_.c \
		derf_.c \
		derfc_.c \
		ef1asc_.c \
		ef1cmc_.c \
		erf_.c \
		erfc_.c \
		exit_.c \
		h_abs.c \
		h_dim.c \
		h_dnnt.c \
		h_indx.c \
		h_len.c \
		h_mod.c \
		h_nint.c \
		h_sign.c \
		hl_ge.c \
		hl_gt.c \
		hl_le.c \
		hl_lt.c \
		i_abs.c \
		i_dim.c \
		i_dnnt.c \
		i_indx.c \
		i_len.c \
		i_mod.c \
		i_nint.c \
		i_sign.c \
		l_ge.c \
		l_gt.c \
		l_le.c \
		l_lt.c \
		lnblnk_.c \
		long_.c \
		main.c \
I 6
D 9
		no_lg.c \
E 9
E 6
		pow_ci.c \
		pow_dd.c \
		pow_di.c \
		pow_hh.c \
		pow_ii.c \
		pow_ri.c \
		pow_zi.c \
		pow_zz.c \
		r_abs.c \
		r_acos.c \
		r_asin.c \
		r_atan.c \
		r_atn2.c \
		r_cnjg.c \
		r_cos.c \
		r_cosh.c \
		r_dim.c \
		r_exp.c \
		r_imag.c \
		r_int.c \
		r_lg10.c \
		r_log.c \
		r_mod.c \
		r_nint.c \
		r_sign.c \
		r_sin.c \
		r_sinh.c \
		r_sqrt.c \
		r_tan.c \
		r_tanh.c \
		rand_.c \
I 2
		random_.c \
E 2
		range.c \
		rindex_.c \
		s_cat.c \
		s_cmp.c \
		s_copy.c \
		s_paus.c \
		s_rnge.c \
		s_stop.c \
		short_.c \
		signal_.c \
D 4
		sinh.c \
E 4
		subout.c \
D 4
		tanh.c \
E 4
		traper_.c \
		trapov_.c \
I 3
		trpfpe_.c \
E 3
D 7
		z_abs.c \
E 7
		z_cos.c \
		z_div.c \
		z_exp.c \
		z_log.c \
		z_sin.c \
		z_sqrt.c

all:		$(LIBRARY) $(LIBRARY_P)

$(LIBRARY):	$(OBJS) Version
		@echo -n "Loading $(LIBRARY) ... "
		@ar cru $(LIBRARY) $(OBJS) Version
		@ranlib $(LIBRARY)
		@echo "done"

$(LIBRARY_P):	$(OBJS) Version
		@echo -n "Loading $(LIBRARY_P) ... "
		@cd profiled; ar cru ../$(LIBRARY_P) $(OBJS) Version
		@ranlib $(LIBRARY_P)
		@echo "done"

Version:	$(SRCS) mkvers
		@rm -f Version.c
		./mkvers $(LIBRARY) $(SRCS) > Version.c
		$(CC) -c Version.c
D 14
		mv Version.o Version
E 14
I 14
		mv -f Version.o Version
E 14
		@rm -f profiled/Version
		ln Version profiled/Version

mkvers:		mkvers.c
		@$(CC) mkvers.c -o mkvers

D 13
clean:;		@rm -f $(OBJS) profiled/*.o $(LIBRARY) $(LIBRARY_P)
E 13
I 13
D 16
clean:;		@rm -f $(OBJS) profiled/*.o $(LIBRARY) $(LIBRARY_P) Usef mkvers
E 16
I 16
clean:;		@rm -f $(OBJS) Usef profiled/*.o $(LIBRARY) $(LIBRARY_P) Usef mkvers
E 16
E 13

depend:;	@echo Construct dependencies manually

extract:;	@ar xo $(DEST)/$(LIBRARY); rm -f __.SYMDEF
		@cd profiled; -ar xo $(DEST)/$(LIBRARY_P); rm -f __.SYMDEF

index:;		@ctags -wx $(HDRS) $(SRCS)

install:	$(LIBRARY) $(LIBRARY_P)
		@-mv $(DEST)/$(LIBRARY) $(OLDDIR)/$(LIBRARY)
		install -m 644 $(LIBRARY) $(DEST)/$(LIBRARY)
		ranlib $(DEST)/$(LIBRARY)
		@-mv $(DEST)/$(LIBRARY_P) $(OLDDIR)/$(LIBRARY_P)
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

trapov_.o:	trapov_.c
		cc -S $(OPTIONS) trapov_.c;
		(echo "g/.set	L[0-9][0-9]*,0x0$$/s/0x0/0xf10/"; echo "x") \
			| ex - trapov_.s;
		as trapov_.s -o trapov_.o;
		mv trapov_.o profiled/trapov_.o
		rm trapov_.s
		cc -S $(OPTIONS) trapov_.c
		(echo "g/.set	L[0-9][0-9]*,0x0$$/s/0x0/0xf10/"; echo "x") \
			| ex - trapov_.s
		as trapov_.s -o trapov_.o
		rm trapov_.s
I 10

E 17
D 20
#	'Usef' is part of a kuldge to get around a bug in the C compiler.
#	C (sec. 9.10 of C ref manual) should round the return value of
#	functions of type float from double to float.  It doesn't, so f77
#	truncates it losing a half bit of accuracy.  See file Test_float
#	for a test.  When it is fixed, get rid of Usef & the extraneous stores
#	in  pow_ri, r_dim, r_mod, r_nint .

D 17
$(OBJS):	Usef
E 17
I 17
${OBJS}: Usef
E 17

D 17
Usef:		Usef.c
		cc -O Usef.c -o Usef
E 17
I 17
Usef: Usef.c
	${CC} -O Usef.c -o Usef
E 17

E 10
.c.o:
D 10
		$(CC) -p $(CFLAGS) -c $*.c
E 10
I 10
D 17
		$(CC) -p `Usef $*` $(CFLAGS) -c $*.c
E 10
		-ld -x -r $*.o
		mv a.out profiled/$*.o
D 10
		$(CC) $(CFLAGS) -c $*.c
E 10
I 10
		$(CC) `Usef $*` $(CFLAGS) -c $*.c
E 10
		-ld -x -r $*.o
		mv a.out $*.o
E 17
I 17
D 19
	@${CC} -p `Usef $*` ${CFLAGS} -c $*.c
E 19
I 19
	@${CC} -p `obj/Usef $*` ${CFLAGS} -c $*.c
	@-ld -x -r -o profiled/$*.o $*.o
	${CC} `obj/Usef $*` ${CFLAGS} -c $*.c
E 19
	@-ld -x -r $*.o
D 19
	@mv a.out profiled/$*.o
	${CC} `Usef $*` ${CFLAGS} -c $*.c
	@-ld -x -r $*.o
	@mv a.out $*.o
E 19
I 19
	@if [ -d obj ]; then cd obj; fi; mv a.out $*.o
E 20
E 19
E 17
E 1
