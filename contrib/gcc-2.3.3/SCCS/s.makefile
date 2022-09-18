h03037
s 00017/00009/00022
d D 8.2 94/01/25 12:55:17 bostic 2 1
c reconfigure per architecture before each compile
e
s 00031/00000/00000
d D 8.1 94/01/22 05:57:02 bostic 1 0
c date and time created 94/01/22 05:57:02 by bostic
e
u
U
t
T
I 1
#Build for 4.4BSD

D 2
all:

E 2
# Currently support 'hp300', 'luna68k', 'sparc', 'mips-dec' architectures.
D 2

	rm -f tm.h
E 2
I 2
all:
E 2
.if ${MACHINE} == "hp300"
D 2
	ln -s config/hp3bsd.h tm.h
E 2
I 2
	rm -f aux-output.c; ln -s config/m68k.c aux-output.c
	rm -f md; ln -s config/m68k.md md
	rm -f tconfig.h; ln -s config/xm-m68k.h tconfig.h
	rm -f tm.h; ln -s config/hp3bsd.h tm.h
E 2
.elif ${MACHINE} == "luna68k"
D 2
	ln -s config/luna68k.h tm.h
E 2
I 2
	rm -f aux-output.c; ln -s config/m68k.c aux-output.c
	rm -f md; ln -s config/m68k.md md
	rm -f tconfig.h; ln -s config/xm-m68k.h tconfig.h
	rm -f tm.h; ln -s config/luna68k.h tm.h
E 2
.elif ${MACHINE} == "mips"
D 2
	ln -s config/mips-dec-bsd.h tm.h
E 2
I 2
	rm -f aux-output.c; ln -s config/mips.c aux-output.c
	rm -f md; ln -s config/mips.md md
	rm -f tconfig.h; ln -s config/xm-mips.h tconfig.h
	rm -f tm.h; ln -s config/mips-dec-bsd.h tm.h
E 2
.elif ${MACHINE} == "sparc"
D 2
	ln -s config/sparcbsd.h tm.h
E 2
I 2
	rm -f aux-output.c; ln -s config/sparc.c aux-output.c
	rm -f md; ln -s config/sparc.md md
	rm -f tconfig.h; ln -s config/xm-sparc.h tconfig.h
	rm -f tm.h; ln -s config/sparcbsd.h tm.h
E 2
.endif
D 2

E 2
	make -f Makefile LANGUAGES="c"
	make -f Makefile stage1
	make -f Makefile "CC=stage1/xgcc -Bstage1/" LANGUAGES="c"
	make -f Makefile stage2
	make -f Makefile "CC=stage2/xgcc -Bstage2/" "CFLAGS+=-O2" \
	    LANGUAGES="c c++"

clean:
	make -f Makefile clean
	rm -rf stage1 stage2
	rm -f cccp.0 g++.0 gcc.0

install:
	make -f Makefile install
E 1
