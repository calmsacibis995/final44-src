#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
# HISTORY
# $Log:	Makefile.com,v $
# Revision 2.2  89/07/12  00:18:31  jjc
# 	      Modified for CMU CS make.
# 	[88/11/14            jjc]
# 
#

#
# @(#)Makefile.com 1.14 88/02/08
#
# Standalone Library common makefile
#
# This file is included by ../$(ARCH)/Makefile and the target libraries
# are built in ../$(ARCH)

HDEST=	$(DESTDIR)/usr/include/stand
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

#if	CMU
.PRECIOUS: $(LIBS)
#else	CMU
#$(LIBSA) :=	LIB = $(LIBSA)
#$(LIBXX) :=	LIB = $(LIBXX)
#
#.PRECIOUS: $$(LIB)
#.KEEP_STATE:
#endif	CMU

# Header files that need to be present (and installed in /usr/include/stand)
HSRC=	ardef.h param.h saio.h sainet.h screg.h scsi.h sdreg.h sereg.h \
	sireg.h streg.h xderr.h

HDIR=	../stand
#if	CMU
HDRS=	$(HSRC;^;$(HDIR)/)
#else	CMU
#HDRS=	$(HSRC:%.h=$(HDIR)/%.h)
#.INIT:	$(HDRS)
#endif	CMU

# Common object files
CMNOBJ=	ar.o chklabel.o common.o conf.o devio.o get.o idprom.o		\
	if_ec.o if_ie.o if_le.o inet.o sc.o sd.o se.o si.o spinning.o	\
	st.o standalloc.o sys.o tm.o xd.o xt.o xy.o

#if	CMU
CMNOBJ_XX=	ar_xx.o chklabel_xx.o common_xx.o conf_xx.o devio_xx.o \
	get_xx.o idprom_xx.o if_ec_xx.o if_ie_xx.o if_le_xx.o inet_xx.o \
	sc_xx.o sd_xx.o se_xx.o si_xx.o spinning_xx.o st_xx.o standalloc_xx.o \
	sys_xx.o tm_xx.o xd_xx.o xt_xx.o xy_xx.o
#endif	CMU

CMNDIR=	../common
#if	CMU
CMNSRC= $(CMNOBJ;*;$(CMNDIR)/&.c)
#else	CMU
#CMNSRC=	$(CMNOBJ:%.o=$(CMNDIR)/%.c)
#endif	CMU

# When building library for boot blocks, define BOOTBLOCK
$(LIBXX) :=	CPPDEF2 = -DBOOTBLOCK


# The library also includes files in ../$(ARCH) and ../$(MACH)
OBJ= $(CMNOBJ) $(MACHOBJ) $(ARCHOBJ)

#if	CMU
$(LIBSA): $(LIBSA)($(OBJ))
	ar r $@ $?
	ranlib $@
	$(RM) $?

OBJ_XX= $(CMNOBJ_XX) $(MACHOBJ_XX) $(ARCHOBJ_XX)

$(LIBXX): $(LIBXX)($(OBJ_XX))
	ar r $@ $?
	ranlib $@
	$(RM) $?
#else	CMU
#$(LIBS): $$@($(OBJ))
#	ar r $@ $?
#	ranlib $@
#	?$(RM) $?
#endif	CMU

# Rules for common .c files
#if	CMU
$(CMNOBJ): $(CMNDIR)/$$(@:.o=.c)
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $(CMNDIR)/$(@:.o=.c)

$(CMNOBJ_XX): $(CMNDIR)/$$(@:_xx.o=.c)
	$(CC) -DBOOTBLOCK $(CFLAGS) $(TARGET_ARCH) -c -o $@ $(CMNDIR)/$(@:_xx.o=.c)

clean:
	$(RM) *.a *.o *.i core a.out $(LINTOBJ)
#else	CMU
#$$(LIB)(%.o): $(CMNDIR)/%.c
#	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $<
#	ar rv $(LIB) $%
#
#clean:
#	$(RM) *.a *.o *.i ../stand/*.h core a.out $(LINTOBJ)
#endif	CMU

lint: $(CMNDIR)/llib-lsa.c
	@-$(RM) $(LINTOBJ)
	@-(for i in $(CMNSRC) $(CMNDIR)/llib-lsa.c ; do \
		$(CC) -E $(LCOPTS) $$i | \
		$(LINT1) $(LOPTS) >> $(LINTOBJ); done ) 2>&1 | $(LTAIL)

install: install_h

install_h: $$(HDRS)
	-mkdir $(HDEST)
	@set -x; for i in $(HDRS); do \
		install -c -m 644 $$i $(HDEST)/$$i ; \
	done;
