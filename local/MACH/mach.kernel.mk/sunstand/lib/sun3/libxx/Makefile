#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.2  89/07/12  00:23:47  jjc
# 	Created for CMU CS make.
# 	[89/06/08            jjc]
# 
#

LIBSA=	libsa.a
LIBXX=	libxx.a
LIBS=	$(LIBSA) $(LIBXX)
BOOTDIR=../..
SYSDIR=	../../..
COPTS=	-O
#if	CMU
CPPDEFS= -DCMUCS -DMACH_KDB -D$(ARCH)
#else	CMU
#CPPDEFS= -D$(ARCH)
#endif	CMU
CPPDEF2=
#if	CMU
#
#	Get kernel include files from private include subdirectory 
#	instead of from the kernel
#
CPPINCS= -I.. -I$(BOOTDIR) -I$(BOOTDIR)/include/$(ARCH) -I$(BOOTDIR)/include
#else	CMU
#CPPINCS= -I.. -I$(BOOTDIR) -I$(SYSDIR)/$(ARCH) -I$(SYSDIR)
#endif	CMU
CPPBOOT= "-Dprintf=(*romp->v_printf)" "-Dputchar=(*romp->v_putchar)"
CPPOPTS= $(CPPDEFS) $(CPPDEF2) $(CPPINCS)
CFLAGS=	$(COPTS) $(CPPOPTS) $(CPPBOOT)

LINTOBJ= ../llib-lsa.ln
LDIR=	/usr/lib/lint
LINT1=	$(LDIR)/lint1
LCOPTS=	-C -Dlint $(CPPOPTS)
LOPTS=	-hxbn
LTAIL=	egrep -v 'genassym\.c' | \
	egrep -v 'struct/union .* never defined' | \
	egrep -v 'possible pointer alignment problem' ; true
RM=	rm -f

VPATH= :../../common:../../m68k:..

# Common object files
CMNOBJ=	ar.o chklabel.o common.o conf.o devio.o get.o idprom.o		\
	if_ec.o if_ie.o if_le.o inet.o sc.o sd.o se.o si.o spinning.o	\
	st.o standalloc.o sys.o tm.o xd.o xt.o xy.o

CMNDIR=	../../common

# The library also includes files in ../$(ARCH) and ../$(MACH)
OBJ= $(CMNOBJ) $(MACHOBJ) $(ARCHOBJ)

all: $(LIBXX)

include ../../m68k/Makefile.arch

$(LIBXX): $(LIBXX)($(OBJ))
	ar r $@ $?
	ranlib $@
	$(RM) $?
	mv $(LIBXX) ..

$(CMNOBJ): $$(@:.o=.c)
	$(CC) -DBOOTBLOCK $(CFLAGS) $(TARGET_ARCH) -c $(@:.o=.c)

clean:
	$(RM) *.o libxx.a
