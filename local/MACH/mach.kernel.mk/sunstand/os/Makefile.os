#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile.os,v $
# Revision 2.2  89/07/12  01:10:10  jjc
# 	      Modified for CMU CS make.
# 	[88/11/14            jjc]
# 
#

#
# @(#)Makefile.os 1.9 88/02/08
#
# This file is included by ../boot/Makefile.com
# It defines the targets and rules needed to build the common
# sources for the boot os library.
#
# The target library is built in ../$(ARCH)

# Standalone boot os object files
CMNDIR=	../os

CMNOBJ=	auth_kern.o authunix_prot.o bdev_vnodeops.o clnt_kudp.o		\
	common.o conf.o devio.o dprint.o heap_kmem.o if.o if_subr.o	\
	in_pcb.o in_proto.o in.o iob.o inet.o ip_input.o kern_prot.o	\
	kern_subr.o kudp_fastsend.o nfs_subr.o nfs_vfsops.o		\
	nfs_vnodeops.o nfs_xdr.o pmap_kgetport.o readfile.o route.o	\
	standalloc.o subr_kudp.o subr_xxx.o udp_boot.o udp_usrreq.o	\
	ufs_bmap.o ufs_dir.o ufs_inode.o ufs_machdep.o ufs_subr.o	\
	ufs_vfsops.o ufs_vnodeops.o uipc_domain.o uipc_mbuf.o		\
	uipc_socket.o uipc_socket2.o vfs.o vfs_bio.o vfs_conf.o		\
	vfs_generic.o vfs_lookup.o vfs_pathname.o vfs_sys.o		\
	vfs_syscalls.o vfs_vnode.o xdr_mbuf.o

CMNHDRS= ../boot/cmap.h ../boot/domain.h ../boot/if.h ../boot/if_ether.h \
	../boot/imp.h ../boot/inet.h ../boot/inode.h ../boot/iob.h \
	../boot/nfs.h ../boot/param.h ../boot/protosw.h ../boot/seg.h \
	../boot/systm.h ../boot/vnode.h ../lib/stand/ardef.h \
	../lib/stand/param.h   ../lib/stand/sainet.h  ../lib/stand/saio.h \
	../sun3/SYS.h
#if	CMU
#else	CMU
#.INIT: $(CMNHDRS)
#endif	CMU

#if	CMU
# Kernel objects built from private copy of SunOS kernel sources
SYSOBJ= af.o bootparam_xdr.o mountxdr.o pmap_rmt.o rpc_prot.o \
 clnt_perror.o pmap_prot.o xdr.o xdr_array.o xdr_mem.o xdr_reference.o
#else	CMU
# Kernel objects built directly from the system hierarchy
#SYSOBJ= af.o bootparam_xdr.o mountxdr.o pmap_rmt.o rpc_prot.o
#endif	CMU


# Rules for standalone boot os .c files
#if	CMU
$(CMNOBJ): $(CMNDIR)/$$(@:.o=.c)
	$(CC) $(CFLAGS) -DLOAD=0x4000 $(TARGET_ARCH) -c $(CMNDIR)/$(@:.o=.c)

# Rules for kernel .c files
$(SYSOBJ): $(CMNDIR)/$$(@:.o=.c)
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $(CMNDIR)/$(@:.o=.c)
#else	CMU
#$$(BOOT_LIB)(%.o): $(CMNDIR)/%.c
#	$(CC) $(CFLAGS) -DLOAD=0x4000 $(TARGET_ARCH) -c $<
#
## Rules for kernel .c files
#$$(BOOT_LIB)(%.o): $(SYSDIR)/net/%.c
#	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $<
#$$(BOOT_LIB)(%.o): $(SYSDIR)/rpcsvc/%.c
#	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $<
#$$(BOOT_LIB)(%.o): $(SYSDIR)/rpc/%.c
#	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $<
#
#.DEFAULT:
#	sccs get -G$@ $@
#endif	CMU

# DO NOT DELETE THIS LINE -- make depend uses it

