# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# Copyright (c) 1987 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#

#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.3  89/02/26  13:55:55  gm0w
# 	Changes for cleanup.
# 
# Revision 2.1.1.1  88/08/08  16:48:17  rvb
# Created. 
# 
#
#

# Copyright (c) 1980, 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	7.1 (Berkeley) 6/5/86
#
ALL=	hkboot hpboot htboot mtboot noboot raboot rlboot \
	upboot utboot tmboot tsboot tuboot \
	httoggle mttoggle tmtoggle tstoggle uttoggle \
	88boot avieboot r6boot

all: ${ALL}

r6boot: r6boot.s
	as r6boot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=r6boot conv=sync

88boot: 88boot.s
	as 88boot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=88boot conv=sync

hkboot: hkboot.s
	as hkboot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=hkboot conv=sync

hpboot: hpboot.s
	as hpboot.s
	@echo "[ Patching for EAGLE ]"
	@echo -n "Sector address of /boothp? "; \
        read n; n=0t"$$n"; nt=0t20; ns=0t48; \
	echo "cyl?W $$n%($$nt*$$ns); \
              stk?W ((($$n-(($$n%($$nt*$$ns))*$$nt*$$ns))%$$ns)*0t256)+($$n-(($$n%$$ns)*$$ns))" \
              | adb -w a.out
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=hpboot conv=sync

htboot: htboot.s
	as htboot.s
	nm -u a.out
	strip a.out
	dd if=a.out of=b.out bs=32 skip=1
	dd if=b.out of=htboot conv=sync

mtboot: mtboot.s
	as mtboot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=mtboot conv=sync

raboot: raboot.s
	as raboot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=raboot conv=sync

rlboot: rlboot.s
	as rlboot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=rlboot conv=sync

tmboot: tmboot.s
	as tmboot.s
	nm -u a.out
	strip a.out
	dd if=a.out of=b.out bs=32 skip=1
	dd if=b.out of=tmboot conv=sync

tsboot: tsboot.s
	as tsboot.s
	nm -u a.out
	strip a.out
	dd if=a.out of=b.out bs=32 skip=1
	dd if=b.out of=tsboot conv=sync

upboot: upboot.s
	as upboot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=upboot conv=sync

tuboot: tuboot.s
	as tuboot.s
	nm -u a.out
	strip a.out
	dd if=a.out of=b.out bs=32 skip=1
	dd if=b.out of=tuboot conv=sync

utboot: utboot.s
	as utboot.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=b.out
	dd if=b.out of=utboot conv=sync

httoggle: httoggle.s
	as httoggle.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=httoggle

mttoggle: mttoggle.s
	as mttoggle.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=mttoggle

tmtoggle: tmtoggle.s
	as tmtoggle.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=tmtoggle

tstoggle: tstoggle.s
	as tstoggle.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=tstoggle

uttoggle: uttoggle.s
	as uttoggle.s
	nm -u a.out
	strip a.out
	dd if=a.out bs=32 skip=1 of=uttoggle

noboot:
	echo | dd of=noboot conv=sync

clean:
	rm -f a.out b.out ${ALL}

install:
	cp *boot ${DESTDIR}/usr/mdec
	rm -f ${DESTDIR}/usr/mdec/mboot
	ln ${DESTDIR}/usr/mdec/htboot ${DESTDIR}/usr/mdec/mboot
	rm -f ${DESTDIR}/usr/mdec/uboot
	ln ${DESTDIR}/usr/mdec/hpboot ${DESTDIR}/usr/mdec/uboot
