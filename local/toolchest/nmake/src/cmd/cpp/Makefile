/*
 * cpp makefile
 */

.INSTALL.cpp = $(LIBDIR)
.INSTALL.cppgen = .

.SOURCE.h : $$(INCLUDEDIR)
.SOURCE.a : $$(LIBDIR)

cpp :: README cpp.1 configure.h cpp.h cpy.y cpp.c scan.c \
	table.o malloc.c -lx (PROFILE)

cpy.o table.o : .READONLY

table.c : cppgen
	$(>) -t > $(<)

machdep.h : cppgen
	$(>) -m > $(<)

cppgen :: cppgen.c
