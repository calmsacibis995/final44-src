/*
 * new-old makefile converter
 */

.INSTALL.mkold2 = $(LIBDIR)

.SOURCE.h : $$(INCLUDEDIR)
.SOURCE.a : $$(LIBDIR)

mkold :: mkold.1 mkold.sh (BINDIR) (LIBDIR)

mkold2 :: mkold2.c -lx (PROFILE)

.MAIN : .CLEAR .ALL
