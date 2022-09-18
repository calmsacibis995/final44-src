/*
 * old-new makefile converter
 */

.INSTALL.mkcv1 = $(LIBDIR)
.INSTALL.mkcv2 = $(LIBDIR)

.SOURCE.h : $$(INCLUDEDIR)
.SOURCE.a : $$(LIBDIR)

MKCV = 1
YACCFLAGS =

mkcv :: mkcv.1 mkcv.sh (LIBDIR)

mkcv1 :: defs.h main.c doname.c misc.c files.c rules.c gram.y dyndep.c \
		-lx (MKCV) (PROFILE)

mkcv2 :: mkcv2.c -lx (PROFILE)

.MAIN : .CLEAR .ALL
