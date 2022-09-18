#
# @(#)Makefile.com 1.17 88/02/08
#
# This file is included by ../$(ARCH)/Makefile.
# It defines the rules needed to build the boot blocks and
# standalone programs.
######################################################################
# HISTORY
# $Log:	Makefile.com,v $
# Revision 2.2  89/07/12  00:09:56  jjc
# 	      Modified for CMU CS make.
# 	[88/11/14            jjc]
# 
#
######################################################################
#
# Certain symbols must be defined before this header file may be included:
#	$(ARCH)		target architecture (e.g., sun2, sun3)
#	$(TARGET_ARCH)	target machine flag (e.g., -mc68010, -mc68020)
#	$(ARCHDIR)	directory in which to find Makefile.arch (e.g., ../m68k)
#	$(BOOTBLOCKS)	list of machine-dependent targets
#
# All targets are built in ../$(ARCH)

ALL=	boot.$(ARCH) tpboot.$(ARCH) copy $(BOOTBLOCKS) installboot

BOOTDIR=..
SYSDIR=	../..
LIBXX=  libxx.a
LIBDIR=	../lib
ARCHDEST= ${LIBDIR}/${ARCH}
DRV_DIR= $(LIBDIR)/$(ARCH)
DRV_LIB= $(DRV_DIR)/libsa.a
SRT0=	srt0.o
BOOT_LIB=libboot.a
BBDRV_LIB= $(DRV_DIR)/libxx.a
BBSRT0=	srt0xx.o

COPTS=	-O
#if	CMU
#
#	Include header files from private include directory
#
CPPDEFS= -DCMUCS -DMACH_KDB -D$(ARCH) -DKERNEL -DUFS -DNFS -DINET -DNFS_BOOT -DNIMP=0
CPPINCS= -I$(BOOTDIR) -I$(BOOTDIR)/boot -I$(LIBDIR) -I$(BOOTDIR)/include/$(ARCH) -I$(BOOTDIR)/include
MACH_CPPINCS= -I$(BOOTDIR) -I$(BOOTDIR)/boot -I$(LIBDIR) -I$(SYSDIR)/$(ARCH) -I$(SYSDIR)
#else	CMU
#CPPDEFS= -D$(ARCH) -DKERNEL -DUFS -DNFS -DINET -DNFS_BOOT -DNIMP=0
#CPPINCS= -I$(BOOTDIR) -I$(BOOTDIR)/boot -I$(LIBDIR) -I$(SYSDIR)/$(ARCH) -I$(SYSDIR)
#endif	CMU
CPPBOOT= "-Dprintf=(*romp->v_printf)" "-Dputchar=(*romp->v_putchar)"
CPPDEBUG= -DDUMP_DEBUG -DNFSDEBUG -DRPCDEBUG -DDEBUG
CPPOPTS= $(CPPDEFS) $(CPPINCS) $(CPPDEBUG)
CFLAGS=	$(COPTS) $(CPPOPTS) $(CPPBOOT)
#if	CMU
LDFLAGS= -N -T $(BRELOC_$@) -e _start
#else	CMU
#LDFLAGS= -N -T $(BRELOC) -e _start
#endif	CMU

LDIR=	/usr/lib/lint
LINT1=	$(LDIR)/lint1
LCOPTS=	-C -Dlint $(CPPOPTS)
LOPTS=	-hxbn
LTAIL=	egrep -v 'genassym\.c' | \
	egrep -v 'struct/union .* never defined' | \
	egrep -v 'possible pointer alignment problem' ; true
RM=	rm -f

.PRECIOUS: $(BOOT_LIB) $(DRV_LIB) $(BBDRV_LIB)
#if	CMU
#else	CMU
#.KEEP_STATE:
#endif	CMU

# Header files that need to be present
HSRC=	cmap.h inode.h nfs.h seg.h systm.h vnode.h
# these header files may go away...the normal system headers should suffice
TMPHDRS= domain.h if.h if_ether.h inet.h iob.h protosw.h

HDIR=	../boot
#if	CMU
HDRS= $(HSRC;^;$(HDIR)/) $(TMPHDRS;^;$(HDIR)/)
#else	CMU
#HDRS=	$(HSRC:%.h=$(HDIR)/%.h) $(TMPHDRS:%.h=$(HDIR)/%.h)
#endif	CMU

# The boot library targets and specific rules for building them are
# in Makefiles that are included by this one.  The following symbols
# must be defined:
#	$(SYSOBJ)	list of kernel object files for libboot.a
#	$(CMNOBJ)	list of common object files for libboot.a
#	$(MACHOBJ)	list of machine-dependent object files for libboot.a
#	$(BRELOC)	text segment relocation for final stage boot
#	$(BBRELOC)	text segment relocation for boot blocks
#
# Object files that are loaded into $(BOOT_LIB)
OBJ= $(SYSOBJ) $(CMNOBJ) $(MACHOBJ) 

include $(ARCHDIR)/Makefile.arch
include ../os/Makefile.os

#if	CMU
$(BOOT_LIB): $$@($(OBJ))
	ar r $@ $?
	ranlib $@
	$(RM) $?
#else	CMU
#$(BOOT_LIB): $$@($(OBJ))
#	?ar r $@ $?
#	ranlib $@
#	?$(RM) $?
#endif	CMU

# Standalone driver libraries
$(DRV_LIB) $(BBDRV_LIB): FRC
	cd $(LIBDIR)/$(ARCH); $(MAKE) $(MFLAGS) $(@F)


# boot: Standalone generic boot program -- get it from anywhere, boot anything.
#if	CMU
BOOT_OBJ_boot= boot.o
BRELOC_boot= $(BRELOC)
boot: $(SRT0) $$(BOOT_OBJ_$$@) $(BOOT_LIB) $(DRV_LIB) $(HDRS)
	$(LD) $(LDFLAGS) -o $@ $(SRT0) $(BOOT_OBJ_$@) $(BOOT_LIB) $(DRV_LIB) -lc
#else	CMU
#boot	:= BOOT_OBJ = boot.o
#boot: $(SRT0) $$(BOOT_OBJ) $(BOOT_LIB) $(DRV_LIB) $(HDRS)
#	$(LD) $(LDFLAGS) -o $@ $(SRT0) $(BOOT_OBJ) $(BOOT_LIB) $(DRV_LIB) $(DRV_LIB) -lc
#endif	CMU

# Other standalone programs.  Note that BOOT_LIB is loaded second, here.
#if	CMU
BOOT_OBJ_tpboot= tpboot.o
BOOT_OBJ_copy= copy.o
BRELOC_copy= $(LOAD)
copy: $(SRT0) $$(BOOT_OBJ_$$@) $(BOOT_LIB) $(DRV_LIB)
	$(LD) $(LDFLAGS) -o $@ $(SRT0) $(BOOT_OBJ_$@) $(DRV_LIB) $(BOOT_LIB) -lc

# Strip the a.out headers for tape boot blocks.
%.$(ARCH): %
	-cp $? $@.tmp; strip $@.tmp
	dd if=$@.tmp of=$@ ibs=32 skip=1; $(RM) $@.tmp
#else	CMU
#tpboot	:= BOOT_OBJ = tpboot.o
#copy	:= BOOT_OBJ = copy.o
#copy	:= BRELOC = $(LOAD)
#copy: $(SRT0) $$(BOOT_OBJ) $(BOOT_LIB) $(DRV_LIB)
#	$(LD) $(LDFLAGS) -o $@ $(SRT0) $(BOOT_OBJ) $(DRV_LIB) $(BOOT_LIB) -lc

## Strip the a.out headers for tape boot blocks.
#%.$(ARCH): %
#	-cp $< $@.tmp; strip $@.tmp
#	dd if=$@.tmp of=$@ ibs=32 skip=1; $(RM) $@.tmp
#endif	CMU

# Rules for building boot blocks
BB_OBJ= bootblk.o
#if	CMU
BRELOC_bootpr= $(BBRELOC)
BRELOC_bootsd= $(BBRELOC)
BRELOC_bootxd= $(BBRELOC)
BRELOC_bootxy= $(BBRELOC)
CONF_OBJ_bootpr= confpr.o
CONF_OBJ_bootsd= confsd.o
CONF_OBJ_bootxd= confxd.o
CONF_OBJ_bootxy= confxy.o

bootpr bootsd bootxd bootxy: \
		$(BBSRT0) $(BB_OBJ) $$(CONF_OBJ_$$@) $(BBDRV_LIB) ../boot/sizecheck
	$(LD) $(LDFLAGS) -o $@ $(BBSRT0) $(BB_OBJ) $(CONF_OBJ_$@) $(BBDRV_LIB) -lc
	chmod a+rwx ../boot/sizecheck
	../boot/sizecheck $@
#else	CMU
#bootpr bootsd bootxd bootxy := BRELOC = $(BBRELOC)
#bootpr := CONF_OBJ = confpr.o
#bootsd := CONF_OBJ = confsd.o
#bootxd := CONF_OBJ = confxd.o
#bootxy := CONF_OBJ = confxy.o
#
#bootpr bootsd bootxd bootxy: \
#		$(BBSRT0) $(BB_OBJ) $$(CONF_OBJ) $(BBDRV_LIB) ../boot/sizecheck
#	$(LD) $(LDFLAGS) -o $@ $(BBSRT0) $(BB_OBJ) $(CONF_OBJ) $(BBDRV_LIB) -lc
#	chmod a+rwx ../boot/sizecheck
#	../boot/sizecheck $@
#endif	CMU

#
# The sun2 tftp boot block
# NOTE: The sun2/50 prom ethernet driver seems to be writing to location
# a0400 when it gets opened, so we change the relocation value to a
# slightly lower value to avoid getting our program overwritten.
#
#if	CMU
#
#	Don't support Sun 2 here
#
#else	CMU
#SUN2BBRELOC= 9e000
#SUN2BBSRCS= bootnd.c udp.c tftp.c
#SUN2BBFILES= ${SUN2BBSRCS:.c=.o}
#sun2.bb: ${BBSRT0} ${SUN2BBFILES} ${BBDRV_LIB} ../boot/sizecheck
#	ld ${LDFLAGS} -T ${SUN2BBRELOC} ${BBSRT0} ${SUN2BBFILES} \
#		${BBDRV_LIB} -lc
#	../boot/sizecheck
#	cp a.out b.out;strip b.out;dd if=b.out of=$@ ibs=32 skip=1
#endif	CMU


# Rules for files whose sources live here
BDIR= ../boot
#if	CMU
boot.o copy.o installboot.o tpboot.o bootblk.o confpr.o: $(BDIR)/$$(@:.o=.c)
	$(CC) $(CFLAGS) $(TARGET_ARCH) -DLOAD=0x$(LOAD) -c $(BDIR)/$(@:.o=.c)

# Rule for programs (e.g., installboot)
installboot: $(BDIR)/installboot.c
	$(CC) -o ../$(ARCH)/$@ -DMACH -O $(BDIR)/installboot.c
#else	CMU
#%.o: $(BDIR)/%.c
#	$(CC) $(CFLAGS) $(TARGET_ARCH) -DLOAD=0x$(LOAD) -c $<
#
## Rule for shell scripts (e.g., sizecheck)
#%: $(BDIR)/%.sh
#	cat $< > $@; chmod +x $@
#
## Rule for programs (e.g., installboot)
#%: $(BDIR)/%.c
#	$(CC) $(COPTS) $(CPPINCS) $(TARGET_ARCH) -o $@ $<
#endif	CMU

# Special rule for tpboot
# We need to use a special readfile, in order to eliminate
# non-block integral reads.  We then link this in before the standalone lib,
# so we pick up that version of readfile.

#if	CMU
BRELOC_tpboot= $(BRELOC)
tpboot: $(SRT0) $$(BOOT_OBJ_$$@) $(DRV_LIB) rdfil_tp.o
	$(LD) $(LDFLAGS) -o $@ $(SRT0) $(BOOT_OBJ_$@) rdfil_tp.o $(DRV_LIB)  -lc
#else	CMU
#tpboot: $(SRT0) $$(BOOT_OBJ) $(DRV_LIB) rdfil_tp.o
#	$(LD) $(LDFLAGS) -o $@ $(SRT0) $(BOOT_OBJ) rdfil_tp.o $(DRV_LIB)  -lc
#endif	CMU

RDFIL= ../os/readfile.c
rdfil_tp.o: $(RDFIL)
	$(CC) $(CFLAGS) $(TARGET_ARCH) -DLOAD=0x4000 -UNFS_BOOT $(RDFIL) -c -o rdfil_tp.o
	

# Configuration modules for boot blocks
CONF_SRC= $(BDIR)/confxx.c
#if	CMU
CONF_DRV_confsd.o = sddriver
CONF_DRV_confxd.o= xddriver
CONF_DRV_confxy.o= xydriver

confsd.o confxd.o confxy.o: $(CONF_SRC)
	$(CC) $(CFLAGS) -Dxxdriver=$(CONF_DRV_$@) $(TARGET_ARCH) -c -o $@ $(CONF_SRC)


clean:
	$(RM) *.a *.o *.i core a.out assym.s $(ALL)
#else	CMU
#confsd.o := CONF_DRV = sddriver
#confxd.o := CONF_DRV = xddriver
#confxy.o := CONF_DRV = xydriver
#
#confsd.o confxd.o confxy.o: $(CONF_SRC)
#	$(CC) $(CFLAGS) -Dxxdriver=$(CONF_DRV) $(TARGET_ARCH) -c -o $@ $(CONF_SRC)
#
#
#clean:
#	$(RM) *.a *.o *.i ../boot/*.h core a.out assym.s ../boot/sizecheck $(ALL)
#endif	CMU

install: install_h all dirs install_mdec
	install -c boot.$(ARCH) $(DESTDIR)/usr/stand
	install -c tpboot.$(ARCH) $(DESTDIR)/usr/stand
	install copy $(DESTDIR)/usr/stand
	install installboot $(DESTDIR)/usr/mdec

install_h: $$(HDRS)
	cd $(LIBDIR); $(MAKE) $(MFLAGS) $@

dirs:
	-mkdir $(DESTDIR)/usr/stand $(DESTDIR)/usr/mdec && \
		chown bin $(DESTDIR)/usr/stand $(DESTDIR)/usr/mdec && \
		chmod 755 $(DESTDIR)/usr/stand $(DESTDIR)/usr/mdec

lint:
	later
FRC:
