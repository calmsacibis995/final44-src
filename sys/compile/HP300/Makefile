IDENT=-DPICASSO -DHP380 -DHP370 -DHP360 -DHP350 -DHP340 -DHP330 -DHP320 -DLLC -DHDLC -DCCITT -DHPFPLIB -DKGDBRATE=19200 -DKGDBDEV=15*256+0 -DKGDB -DNKMEMCLUSTERS=512 -DKTRACE -DPANICBUTTON -DDIAGNOSTIC -DDEBUG -DMAPPEDCOPY -DCOMPAT_NOLABEL -DCOMPAT_OHPUX -DHPUXCOMPAT -DSYSVSHM -DCLUSTERED_PAGEOUT -DDEVPAGER -DVNODEPAGER -DSWAPPAGER -DTCP_COMPAT_42 -DCOMPAT_43 -DCD9660 -DUMAPFS -DNULLFS -DPORTAL -DFDESC -DKERNFS -DUNION -DPROCFS -DFIFO -DLFS -DNFS -DMFS -DFFS -DMROUTING -DMULTICAST -DINET -DQUOTA
PARAM=-DTIMEZONE=480 -DDST=1 -DMAXUSERS=16
DEBUG=-g
#	@(#)Makefile.hp300	8.2 (Berkeley) 1/23/94
#
# Makefile for 4.4 BSD
#
# This makefile is constructed from a machine description:
#	config machineid
# Most changes should be made in the machine description
#	/sys/conf/``machineid''
# after which you should do
#	 config machineid
# Machine generic makefile changes should be made in
#	/sys/conf/Makefile.``machinetype''
# after which config should be rerun for all machines of that type.
#
# N.B.: NO DEPENDENCIES ON FOLLOWING FLAGS ARE VISIBLE TO MAKEFILE
#	IF YOU CHANGE THE DEFINITION OF ANY OF THESE RECOMPILE EVERYTHING
#
# -DTRACE	compile in kernel tracing hooks
# -DQUOTA	compile in file system quotas


# DEBUG is set to -g by config if debugging is requested (config -g).
# PROF is set to -pg by config if profiling is requested (config -p).
AS=	as ${DEBUG}
CC=	cc ${DEBUG}
CPP=	cpp
LD=	ld
TOUCH=	touch -f -c

# source tree is located via $S relative to the compilation directory
S=	../..
HP300=	$S/hp300

INCLUDES= -I. -I$S -I$S/sys
COPTS=	${INCLUDES} ${IDENT} -DKERNEL -Dmc68020 -Dhp300 -DFPCOPROC
CFLAGS=	-O ${COPTS}

# compile rules: rules are named ${TYPE}_${SUFFIX}${CONFIG_DEP}
# where TYPE is NORMAL, DRIVER, or PROFILE}; SUFFIX is the file suffix,
# capitalized (e.g. C for a .c file), and CONFIG_DEP is _C if the file
# is marked as config-dependent.

NORMAL_C=	${CC} -c ${CFLAGS} ${PROF} $<
NORMAL_C_C=	${CC} -c ${CFLAGS} ${PROF} ${PARAM} $<

DRIVER_C=	${CC} -c ${CFLAGS} ${PROF} $<
DRIVER_C_C=	${CC} -c ${CFLAGS} ${PROF} ${PARAM} $<

PROFILE_C=	${CC} -S -c ${COPTS} $<; \
		sed -e s/_mcount/mcount/ -e s/subrmcount/subr_mcount/ <$*.s | \
		${AS} -o $@; \
		rm -f $*.s

NORMAL_S=	${CPP} ${COPTS} $< | ${AS} -o $@
NORMAL_S_C=	${CPP} ${COPTS} ${PARAM} $< | ${AS} -o $@

OBJS=cd9660_bmap.o cd9660_lookup.o cd9660_node.o cd9660_rrip.o \
	cd9660_util.o cd9660_vfsops.o cd9660_vnops.o init_main.o \
	init_sysent.o kern_acct.o kern_clock.o kern_descrip.o \
	kern_exec.o kern_exit.o kern_fork.o kern_ktrace.o kern_malloc.o \
	kern_physio.o kern_proc.o kern_prot.o kern_resource.o kern_sig.o \
	kern_subr.o kern_synch.o kern_sysctl.o kern_time.o kern_xxx.o \
	kern_lock.o subr_log.o subr_prf.o subr_prof.o subr_rmap.o \
	subr_xxx.o sys_generic.o sys_process.o sys_socket.o sysv_shm.o \
	tty.o tty_compat.o tty_conf.o tty_pty.o tty_subr.o tty_tty.o \
	uipc_domain.o uipc_mbuf.o uipc_proto.o uipc_socket.o \
	uipc_socket2.o uipc_syscalls.o uipc_usrreq.o vfs_bio.o \
	vfs_cache.o vfs_cluster.o vfs_conf.o vfs_init.o vfs_lookup.o \
	vfs_subr.o vfs_syscalls.o vfs_vnops.o dead_vnops.o \
	fdesc_vfsops.o fdesc_vnops.o fifo_vnops.o kernfs_vfsops.o \
	kernfs_vnops.o null_subr.o null_vfsops.o null_vnops.o \
	portal_vfsops.o portal_vnops.o procfs_subr.o procfs_vnops.o \
	procfs_vfsops.o procfs_note.o procfs_mem.o procfs_ctl.o \
	procfs_status.o procfs_regs.o procfs_fpregs.o spec_vnops.o \
	umap_subr.o umap_vfsops.o umap_vnops.o union_subr.o \
	union_vfsops.o union_vnops.o bpf.o bpf_filter.o if.o \
	if_ethersubr.o if_loop.o if_sl.o radix.o raw_cb.o raw_usrreq.o \
	route.o rtsock.o slcompress.o ccitt_proto.o llc_input.o \
	llc_output.o llc_subr.o llc_timer.o pk_llcsubr.o hd_debug.o \
	hd_input.o hd_output.o hd_subr.o hd_timer.o if_x25subr.o \
	pk_acct.o pk_debug.o pk_input.o pk_output.o pk_subr.o pk_timer.o \
	pk_usrreq.o if_ether.o igmp.o in.o in_pcb.o in_proto.o ip_icmp.o \
	ip_input.o ip_mroute.o ip_output.o raw_ip.o tcp_debug.o \
	tcp_input.o tcp_output.o tcp_subr.o tcp_timer.o tcp_usrreq.o \
	udp_usrreq.o nfs_bio.o nfs_node.o nfs_nqlease.o nfs_serv.o \
	nfs_socket.o nfs_srvcache.o nfs_subs.o nfs_syscalls.o \
	nfs_vfsops.o nfs_vnops.o ffs_alloc.o ffs_balloc.o ffs_inode.o \
	ffs_subr.o ffs_tables.o ffs_vfsops.o ffs_vnops.o lfs_alloc.o \
	lfs_bio.o lfs_balloc.o lfs_cksum.o lfs_debug.o lfs_inode.o \
	lfs_segment.o lfs_subr.o lfs_syscalls.o lfs_vfsops.o lfs_vnops.o \
	mfs_vfsops.o mfs_vnops.o ufs_bmap.o ufs_disksubr.o ufs_ihash.o \
	ufs_inode.o ufs_lockf.o ufs_lookup.o ufs_quota.o ufs_vfsops.o \
	ufs_vnops.o device_pager.o swap_pager.o vm_fault.o vm_glue.o \
	vm_init.o vm_kern.o vm_map.o vm_meter.o vm_mmap.o vm_object.o \
	vm_page.o vm_pageout.o vm_pager.o vm_swap.o vm_unix.o vm_user.o \
	vnode_pager.o autoconf.o clock.o conf.o dkbad.o in_cksum.o \
	kgdb_glue.o kgdb_stub.o machdep.o mem.o oc_cksum.o pmap.o \
	pmap_bootstrap.o sys_machdep.o trap.o vm_machdep.o hpux_float.o \
	procfs_machdep.o cons_conf.o grf_conf.o grf_machdep.o grf_dv.o \
	grf_gb.o grf_hy.o grf_rb.o grf_tc.o ite_dv.o ite_gb.o ite_hy.o \
	ite_rb.o ite_tc.o dcm.o if_le.o dma.o hpib.o fhpib.o nhpib.o \
	ct.o rd.o rd_compat.o scsi.o sd.o sd_compat.o st.o cons.o dca.o \
	grf.o hil.o hil_keymaps.o hil_subr.o ite.o ite_subr.o \
	hpux_compat.o hpux_net.o hpux_sig.o hpux_syscalls.o \
	hpux_sysent.o hpux_tty.o vn.o 

CFILES=$S/isofs/cd9660/cd9660_bmap.c $S/isofs/cd9660/cd9660_lookup.c \
	$S/isofs/cd9660/cd9660_node.c $S/isofs/cd9660/cd9660_rrip.c \
	$S/isofs/cd9660/cd9660_util.c $S/isofs/cd9660/cd9660_vfsops.c \
	$S/isofs/cd9660/cd9660_vnops.c $S/kern/init_main.c \
	$S/kern/init_sysent.c $S/kern/kern_acct.c $S/kern/kern_clock.c \
	$S/kern/kern_descrip.c $S/kern/kern_exec.c $S/kern/kern_exit.c \
	$S/kern/kern_fork.c $S/kern/kern_ktrace.c $S/kern/kern_malloc.c \
	$S/kern/kern_physio.c $S/kern/kern_proc.c $S/kern/kern_prot.c \
	$S/kern/kern_resource.c $S/kern/kern_sig.c $S/kern/kern_subr.c \
	$S/kern/kern_synch.c $S/kern/kern_sysctl.c $S/kern/kern_time.c \
	$S/kern/kern_xxx.c $S/kern/kern_lock.c $S/kern/subr_log.c \
	$S/kern/subr_prf.c $S/kern/subr_prof.c $S/kern/subr_rmap.c \
	$S/kern/subr_xxx.c $S/kern/sys_generic.c $S/kern/sys_process.c \
	$S/kern/sys_socket.c $S/kern/sysv_shm.c $S/kern/tty.c \
	$S/kern/tty_compat.c $S/kern/tty_conf.c $S/kern/tty_pty.c \
	$S/kern/tty_subr.c $S/kern/tty_tty.c $S/kern/uipc_domain.c \
	$S/kern/uipc_mbuf.c $S/kern/uipc_proto.c $S/kern/uipc_socket.c \
	$S/kern/uipc_socket2.c $S/kern/uipc_syscalls.c \
	$S/kern/uipc_usrreq.c $S/kern/vfs_bio.c $S/kern/vfs_cache.c \
	$S/kern/vfs_cluster.c $S/kern/vfs_conf.c $S/kern/vfs_init.c \
	$S/kern/vfs_lookup.c $S/kern/vfs_subr.c $S/kern/vfs_syscalls.c \
	$S/kern/vfs_vnops.c $S/miscfs/deadfs/dead_vnops.c \
	$S/miscfs/fdesc/fdesc_vfsops.c $S/miscfs/fdesc/fdesc_vnops.c \
	$S/miscfs/fifofs/fifo_vnops.c $S/miscfs/kernfs/kernfs_vfsops.c \
	$S/miscfs/kernfs/kernfs_vnops.c $S/miscfs/nullfs/null_subr.c \
	$S/miscfs/nullfs/null_vfsops.c $S/miscfs/nullfs/null_vnops.c \
	$S/miscfs/portal/portal_vfsops.c $S/miscfs/portal/portal_vnops.c \
	$S/miscfs/procfs/procfs_subr.c $S/miscfs/procfs/procfs_vnops.c \
	$S/miscfs/procfs/procfs_vfsops.c $S/miscfs/procfs/procfs_note.c \
	$S/miscfs/procfs/procfs_mem.c $S/miscfs/procfs/procfs_ctl.c \
	$S/miscfs/procfs/procfs_status.c $S/miscfs/procfs/procfs_regs.c \
	$S/miscfs/procfs/procfs_fpregs.c $S/miscfs/specfs/spec_vnops.c \
	$S/miscfs/umapfs/umap_subr.c $S/miscfs/umapfs/umap_vfsops.c \
	$S/miscfs/umapfs/umap_vnops.c $S/miscfs/union/union_subr.c \
	$S/miscfs/union/union_vfsops.c $S/miscfs/union/union_vnops.c \
	$S/net/bpf.c $S/net/bpf_filter.c $S/net/if.c \
	$S/net/if_ethersubr.c $S/net/if_loop.c $S/net/if_sl.c \
	$S/net/radix.c $S/net/raw_cb.c $S/net/raw_usrreq.c \
	$S/net/route.c $S/net/rtsock.c $S/net/slcompress.c \
	$S/netccitt/ccitt_proto.c $S/netccitt/llc_input.c \
	$S/netccitt/llc_output.c $S/netccitt/llc_subr.c \
	$S/netccitt/llc_timer.c $S/netccitt/pk_llcsubr.c \
	$S/netccitt/hd_debug.c $S/netccitt/hd_input.c \
	$S/netccitt/hd_output.c $S/netccitt/hd_subr.c \
	$S/netccitt/hd_timer.c $S/netccitt/if_x25subr.c \
	$S/netccitt/pk_acct.c $S/netccitt/pk_debug.c \
	$S/netccitt/pk_input.c $S/netccitt/pk_output.c \
	$S/netccitt/pk_subr.c $S/netccitt/pk_timer.c \
	$S/netccitt/pk_usrreq.c $S/netinet/if_ether.c $S/netinet/igmp.c \
	$S/netinet/in.c $S/netinet/in_pcb.c $S/netinet/in_proto.c \
	$S/netinet/ip_icmp.c $S/netinet/ip_input.c \
	$S/netinet/ip_mroute.c $S/netinet/ip_output.c \
	$S/netinet/raw_ip.c $S/netinet/tcp_debug.c \
	$S/netinet/tcp_input.c $S/netinet/tcp_output.c \
	$S/netinet/tcp_subr.c $S/netinet/tcp_timer.c \
	$S/netinet/tcp_usrreq.c $S/netinet/udp_usrreq.c $S/nfs/nfs_bio.c \
	$S/nfs/nfs_node.c $S/nfs/nfs_nqlease.c $S/nfs/nfs_serv.c \
	$S/nfs/nfs_socket.c $S/nfs/nfs_srvcache.c $S/nfs/nfs_subs.c \
	$S/nfs/nfs_syscalls.c $S/nfs/nfs_vfsops.c $S/nfs/nfs_vnops.c \
	$S/ufs/ffs/ffs_alloc.c $S/ufs/ffs/ffs_balloc.c \
	$S/ufs/ffs/ffs_inode.c $S/ufs/ffs/ffs_subr.c \
	$S/ufs/ffs/ffs_tables.c $S/ufs/ffs/ffs_vfsops.c \
	$S/ufs/ffs/ffs_vnops.c $S/ufs/lfs/lfs_alloc.c \
	$S/ufs/lfs/lfs_bio.c $S/ufs/lfs/lfs_balloc.c \
	$S/ufs/lfs/lfs_cksum.c $S/ufs/lfs/lfs_debug.c \
	$S/ufs/lfs/lfs_inode.c $S/ufs/lfs/lfs_segment.c \
	$S/ufs/lfs/lfs_subr.c $S/ufs/lfs/lfs_syscalls.c \
	$S/ufs/lfs/lfs_vfsops.c $S/ufs/lfs/lfs_vnops.c \
	$S/ufs/mfs/mfs_vfsops.c $S/ufs/mfs/mfs_vnops.c \
	$S/ufs/ufs/ufs_bmap.c $S/ufs/ufs/ufs_disksubr.c \
	$S/ufs/ufs/ufs_ihash.c $S/ufs/ufs/ufs_inode.c \
	$S/ufs/ufs/ufs_lockf.c $S/ufs/ufs/ufs_lookup.c \
	$S/ufs/ufs/ufs_quota.c $S/ufs/ufs/ufs_vfsops.c \
	$S/ufs/ufs/ufs_vnops.c $S/vm/device_pager.c $S/vm/swap_pager.c \
	$S/vm/vm_fault.c $S/vm/vm_glue.c $S/vm/vm_init.c $S/vm/vm_kern.c \
	$S/vm/vm_map.c $S/vm/vm_meter.c $S/vm/vm_mmap.c \
	$S/vm/vm_object.c $S/vm/vm_page.c $S/vm/vm_pageout.c \
	$S/vm/vm_pager.c $S/vm/vm_swap.c $S/vm/vm_unix.c $S/vm/vm_user.c \
	$S/vm/vnode_pager.c $S/hp300/hp300/autoconf.c \
	$S/hp300/hp300/clock.c $S/hp300/hp300/conf.c \
	$S/hp300/hp300/dkbad.c $S/hp300/hp300/in_cksum.c \
	$S/hp300/hp300/kgdb_glue.c $S/hp300/hp300/kgdb_stub.c \
	$S/hp300/hp300/machdep.c $S/hp300/hp300/mem.c \
	$S/hp300/hp300/pmap.c $S/hp300/hp300/pmap_bootstrap.c \
	$S/hp300/hp300/sys_machdep.c $S/hp300/hp300/trap.c \
	$S/hp300/hp300/vm_machdep.c $S/hp300/hp300/procfs_machdep.c \
	$S/hp300/dev/cons_conf.c $S/hp300/dev/grf_conf.c \
	$S/hp300/dev/grf_machdep.c $S/hp300/dev/grf_dv.c \
	$S/hp300/dev/grf_gb.c $S/hp300/dev/grf_hy.c \
	$S/hp300/dev/grf_rb.c $S/hp300/dev/grf_tc.c \
	$S/hp300/dev/ite_dv.c $S/hp300/dev/ite_gb.c \
	$S/hp300/dev/ite_hy.c $S/hp300/dev/ite_rb.c \
	$S/hp300/dev/ite_tc.c $S/hp300/dev/dcm.c $S/hp300/dev/if_le.c \
	$S/hp300/dev/dma.c $S/hp300/dev/hpib.c $S/hp300/dev/fhpib.c \
	$S/hp300/dev/nhpib.c $S/hp300/dev/ct.c $S/hp300/dev/rd.c \
	$S/hp300/dev/rd_compat.c $S/hp300/dev/scsi.c $S/hp300/dev/sd.c \
	$S/hp300/dev/sd_compat.c $S/hp300/dev/st.c $S/hp/dev/cons.c \
	$S/hp/dev/dca.c $S/hp/dev/grf.c $S/hp/dev/hil.c \
	$S/hp/dev/hil_keymaps.c $S/hp/dev/hil_subr.c $S/hp/dev/ite.c \
	$S/hp/dev/ite_subr.c $S/hp/hpux/hpux_compat.c \
	$S/hp/hpux/hpux_net.c $S/hp/hpux/hpux_sig.c \
	$S/hp/hpux/hpux_syscalls.c $S/hp/hpux/hpux_sysent.c \
	$S/hp/hpux/hpux_tty.c $S/dev/vn.c swapvmunix.c \
	swapvgvmunix.c swaprdvmunix.c $S/hp300/hp300/swapgeneric.c 

# load lines for config "xxx" will be emitted as:
# xxx: ${SYSTEM_DEP} swapxxx.o
#	${SYSTEM_LD_HEAD}
#	${SYSTEM_LD} swapxxx.o
#	${SYSTEM_LD_TAIL}
SYSTEM_OBJ=	locore.o ${OBJS} param.o ioconf.o vnode_if.o
#SYSTEM_DEP=	Makefile symbols.sort ${SYSTEM_OBJ} libkern.a
SYSTEM_DEP=	Makefile ${SYSTEM_OBJ} libkern.a
SYSTEM_LD_HEAD=	rm -f $@
SYSTEM_LD=	-@if [ X${DEBUG} = X-g ]; \
		then strip=-X; \
		else strip=-x; \
		fi; \
		echo ${LD} $$strip -n -o $@ -e start '$${SYSTEM_OBJ}' vers.o libkern.a; \
		${LD} $$strip -n -o $@ -e start ${SYSTEM_OBJ} vers.o libkern.a
#SYSTEM_LD_TAIL= @echo rearranging symbols;\
#		symorder symbols.sort $@;\
SYSTEM_LD_TAIL=	@size $@; chmod 755 $@; \
		[ X${DEBUG} = X-g ] && { \
		echo cp $@ $@.gdb; rm -f $@.gdb; cp $@ $@.gdb; \
		echo strip -d $@; strip -d $@; } || true

vmunix: ${SYSTEM_DEP} swapvmunix.o newvers
	${SYSTEM_LD_HEAD}
	${SYSTEM_LD} swapvmunix.o
	${SYSTEM_LD_TAIL}

swapvmunix.o: swapvmunix.c
	${NORMAL_C}

vgvmunix: ${SYSTEM_DEP} swapvgvmunix.o
	${SYSTEM_LD_HEAD}
	${SYSTEM_LD} swapvgvmunix.o
	${SYSTEM_LD_TAIL}

swapvgvmunix.o: swapvgvmunix.c
	${NORMAL_C}

rdvmunix: ${SYSTEM_DEP} swaprdvmunix.o
	${SYSTEM_LD_HEAD}
	${SYSTEM_LD} swaprdvmunix.o
	${SYSTEM_LD_TAIL}

swaprdvmunix.o: swaprdvmunix.c
	${NORMAL_C}

genvmunix: ${SYSTEM_DEP} swapgeneric.o
	${SYSTEM_LD_HEAD}
	${SYSTEM_LD} swapgeneric.o
	${SYSTEM_LD_TAIL}

swapgeneric.o: $S/hp300/hp300/swapgeneric.c
	${NORMAL_C}

all: vmunix vgvmunix rdvmunix genvmunix

libkern.a:
	-@if [ X${PROF} = X ]; \
	then ln -s $S/libkern/obj/libkern.a libkern.a; \
	else ln -s $S/libkern/obj/libkern_p.a libkern.a; \
	fi; \
	echo ln -s $S/libkern/obj/libkern.a libkern.a

newvers:
	sh $S/conf/newvers.sh
	${CC} $(CFLAGS) -c vers.c

clean:
	rm -f eddep *vmunix vmunix.gdb tags *.o locore.i [a-z]*.s \
		Errs errs linterrs makelinks

lint: /tmp param.c
	@lint -hbxn -DGENERIC -Dvolatile= ${COPTS} ${PARAM} -UKGDB \
	    ${HP300}/hp300/Locore.c ${CFILES} ${HP300}/hp300/swapgeneric.c \
	    ioconf.c param.c| \
	    grep -v 'struct/union .* never defined' | \
	    grep -v 'possible pointer alignment problem'

symbols.sort: ${HP300}/hp300/symbols.raw
	grep -v '^#' ${HP300}/hp300/symbols.raw \
	    | sed 's/^	//' | sort -u > symbols.sort

locore.o: assym.s ${HP300}/hp300/vectors.s ${HP300}/hp300/locore.s 
locore.o: ${HP300}/include/trap.h ${HP300}/include/psl.h ${HP300}/hp300/pte.h
locore.o: ${HP300}/include/cpu.h
	${CPP} -DLOCORE ${COPTS} ${HP300}/hp300/locore.s | ${AS} -o locore.o

# the following is necessary because autoconf.o depends on #if GENERIC
autoconf.o: Makefile

# the following are necessary because the files depend on the types of
# hp cpu's included in the system configuration
machdep.o sys_machdep.o pmap.o pmap_bootstrap.o trap.o dma.o: Makefile

# depend on network or filesystem configuration
uipc_proto.o vfs_conf.o locore.o: Makefile

# depend on maxusers
assym.s: Makefile

assym.s: genassym
	./genassym >assym.s

genassym:
	${CC} ${INCLUDES} ${IDENT} ${PARAM} -Dmc68020 -Dhp300 -o genassym \
	    ${HP300}/hp300/genassym.c

depend: assym.s param.c vnode_if.h
	mkdep ${COPTS} ${CFILES} ioconf.c param.c
	mkdep -a -p ${INCLUDES} ${IDENT} ${PARAM} ${HP300}/hp300/genassym.c

links:
	egrep '#if' ${CFILES} | sed -f $S/conf/defines | \
	  sed -e 's/:.*//' -e 's/\.c/.o/' | sort -u > dontlink
	echo ${CFILES} | tr -s ' ' '\12' | sed 's/\.c/.o/' | \
	  sort -u | comm -23 - dontlink | \
	  sed 's,../.*/\(.*.o\),rm -f \1;ln -s ../GENERIC/\1 \1,' > makelinks
	sh makelinks && rm -f dontlink

tags:
	@echo "see $S/kern/Makefile for tags"

ioconf.o: ioconf.c
	${CC} -c ${CFLAGS} ioconf.c

param.c: $S/conf/param.c
	rm -f param.c
	cp $S/conf/param.c .

param.o: param.c Makefile
	${CC} -c ${CFLAGS} ${PARAM} param.c

vnode_if.c: $S/kern/vnode_if.sh $S/kern/vnode_if.src
	sh $S/kern/vnode_if.sh $S/kern/vnode_if.src
vnode_if.h: $S/kern/vnode_if.sh $S/kern/vnode_if.src
	sh $S/kern/vnode_if.sh $S/kern/vnode_if.src

cd9660_bmap.o: $S/isofs/cd9660/cd9660_bmap.c
	${NORMAL_C}

cd9660_lookup.o: $S/isofs/cd9660/cd9660_lookup.c
	${NORMAL_C}

cd9660_node.o: $S/isofs/cd9660/cd9660_node.c
	${NORMAL_C}

cd9660_rrip.o: $S/isofs/cd9660/cd9660_rrip.c
	${NORMAL_C}

cd9660_util.o: $S/isofs/cd9660/cd9660_util.c
	${NORMAL_C}

cd9660_vfsops.o: $S/isofs/cd9660/cd9660_vfsops.c
	${NORMAL_C}

cd9660_vnops.o: $S/isofs/cd9660/cd9660_vnops.c
	${NORMAL_C}

init_main.o: $S/kern/init_main.c
	${NORMAL_C}

init_sysent.o: $S/kern/init_sysent.c
	${NORMAL_C}

kern_acct.o: $S/kern/kern_acct.c
	${NORMAL_C}

kern_clock.o: $S/kern/kern_clock.c
	${NORMAL_C}

kern_descrip.o: $S/kern/kern_descrip.c
	${NORMAL_C}

kern_exec.o: $S/kern/kern_exec.c
	${NORMAL_C}

kern_exit.o: $S/kern/kern_exit.c
	${NORMAL_C}

kern_fork.o: $S/kern/kern_fork.c
	${NORMAL_C}

kern_ktrace.o: $S/kern/kern_ktrace.c
	${NORMAL_C}

kern_malloc.o: $S/kern/kern_malloc.c
	${NORMAL_C}

kern_physio.o: $S/kern/kern_physio.c
	${NORMAL_C}

kern_proc.o: $S/kern/kern_proc.c
	${NORMAL_C}

kern_prot.o: $S/kern/kern_prot.c
	${NORMAL_C}

kern_resource.o: $S/kern/kern_resource.c
	${NORMAL_C}

kern_sig.o: $S/kern/kern_sig.c
	${NORMAL_C}

kern_subr.o: $S/kern/kern_subr.c
	${NORMAL_C}

kern_synch.o: $S/kern/kern_synch.c
	${NORMAL_C}

kern_sysctl.o: $S/kern/kern_sysctl.c
	${NORMAL_C}

kern_time.o: $S/kern/kern_time.c
	${NORMAL_C}

kern_xxx.o: $S/kern/kern_xxx.c
	${NORMAL_C}

kern_lock.o: $S/kern/kern_lock.c
	${NORMAL_C}

subr_log.o: $S/kern/subr_log.c
	${NORMAL_C}

subr_prf.o: $S/kern/subr_prf.c
	${NORMAL_C}

subr_prof.o: $S/kern/subr_prof.c
	${NORMAL_C}

subr_rmap.o: $S/kern/subr_rmap.c
	${NORMAL_C}

subr_xxx.o: $S/kern/subr_xxx.c
	${NORMAL_C}

sys_generic.o: $S/kern/sys_generic.c
	${NORMAL_C}

sys_process.o: $S/kern/sys_process.c
	${NORMAL_C}

sys_socket.o: $S/kern/sys_socket.c
	${NORMAL_C}

sysv_shm.o: $S/kern/sysv_shm.c
	${NORMAL_C}

tty.o: $S/kern/tty.c
	${NORMAL_C}

tty_compat.o: $S/kern/tty_compat.c
	${NORMAL_C}

tty_conf.o: $S/kern/tty_conf.c
	${NORMAL_C}

tty_pty.o: $S/kern/tty_pty.c
	${NORMAL_C}

tty_subr.o: $S/kern/tty_subr.c
	${NORMAL_C}

tty_tty.o: $S/kern/tty_tty.c
	${NORMAL_C}

uipc_domain.o: $S/kern/uipc_domain.c
	${NORMAL_C}

uipc_mbuf.o: $S/kern/uipc_mbuf.c
	${NORMAL_C}

uipc_proto.o: $S/kern/uipc_proto.c
	${NORMAL_C}

uipc_socket.o: $S/kern/uipc_socket.c
	${NORMAL_C}

uipc_socket2.o: $S/kern/uipc_socket2.c
	${NORMAL_C}

uipc_syscalls.o: $S/kern/uipc_syscalls.c
	${NORMAL_C}

uipc_usrreq.o: $S/kern/uipc_usrreq.c
	${NORMAL_C}

vfs_bio.o: $S/kern/vfs_bio.c
	${NORMAL_C}

vfs_cache.o: $S/kern/vfs_cache.c
	${NORMAL_C}

vfs_cluster.o: $S/kern/vfs_cluster.c
	${NORMAL_C}

vfs_conf.o: $S/kern/vfs_conf.c
	${NORMAL_C}

vfs_init.o: $S/kern/vfs_init.c
	${NORMAL_C}

vfs_lookup.o: $S/kern/vfs_lookup.c
	${NORMAL_C}

vfs_subr.o: $S/kern/vfs_subr.c
	${NORMAL_C}

vfs_syscalls.o: $S/kern/vfs_syscalls.c
	${NORMAL_C}

vfs_vnops.o: $S/kern/vfs_vnops.c
	${NORMAL_C}

dead_vnops.o: $S/miscfs/deadfs/dead_vnops.c
	${NORMAL_C}

fdesc_vfsops.o: $S/miscfs/fdesc/fdesc_vfsops.c
	${NORMAL_C}

fdesc_vnops.o: $S/miscfs/fdesc/fdesc_vnops.c
	${NORMAL_C}

fifo_vnops.o: $S/miscfs/fifofs/fifo_vnops.c
	${NORMAL_C}

kernfs_vfsops.o: $S/miscfs/kernfs/kernfs_vfsops.c
	${NORMAL_C}

kernfs_vnops.o: $S/miscfs/kernfs/kernfs_vnops.c
	${NORMAL_C}

null_subr.o: $S/miscfs/nullfs/null_subr.c
	${NORMAL_C}

null_vfsops.o: $S/miscfs/nullfs/null_vfsops.c
	${NORMAL_C}

null_vnops.o: $S/miscfs/nullfs/null_vnops.c
	${NORMAL_C}

portal_vfsops.o: $S/miscfs/portal/portal_vfsops.c
	${NORMAL_C}

portal_vnops.o: $S/miscfs/portal/portal_vnops.c
	${NORMAL_C}

procfs_subr.o: $S/miscfs/procfs/procfs_subr.c
	${NORMAL_C}

procfs_vnops.o: $S/miscfs/procfs/procfs_vnops.c
	${NORMAL_C}

procfs_vfsops.o: $S/miscfs/procfs/procfs_vfsops.c
	${NORMAL_C}

procfs_note.o: $S/miscfs/procfs/procfs_note.c
	${NORMAL_C}

procfs_mem.o: $S/miscfs/procfs/procfs_mem.c
	${NORMAL_C}

procfs_ctl.o: $S/miscfs/procfs/procfs_ctl.c
	${NORMAL_C}

procfs_status.o: $S/miscfs/procfs/procfs_status.c
	${NORMAL_C}

procfs_regs.o: $S/miscfs/procfs/procfs_regs.c
	${NORMAL_C}

procfs_fpregs.o: $S/miscfs/procfs/procfs_fpregs.c
	${NORMAL_C}

spec_vnops.o: $S/miscfs/specfs/spec_vnops.c
	${NORMAL_C}

umap_subr.o: $S/miscfs/umapfs/umap_subr.c
	${NORMAL_C}

umap_vfsops.o: $S/miscfs/umapfs/umap_vfsops.c
	${NORMAL_C}

umap_vnops.o: $S/miscfs/umapfs/umap_vnops.c
	${NORMAL_C}

union_subr.o: $S/miscfs/union/union_subr.c
	${NORMAL_C}

union_vfsops.o: $S/miscfs/union/union_vfsops.c
	${NORMAL_C}

union_vnops.o: $S/miscfs/union/union_vnops.c
	${NORMAL_C}

bpf.o: $S/net/bpf.c
	${NORMAL_C}

bpf_filter.o: $S/net/bpf_filter.c
	${NORMAL_C}

if.o: $S/net/if.c
	${NORMAL_C}

if_ethersubr.o: $S/net/if_ethersubr.c
	${NORMAL_C}

if_loop.o: $S/net/if_loop.c
	${NORMAL_C}

if_sl.o: $S/net/if_sl.c
	${NORMAL_C}

radix.o: $S/net/radix.c
	${NORMAL_C}

raw_cb.o: $S/net/raw_cb.c
	${NORMAL_C}

raw_usrreq.o: $S/net/raw_usrreq.c
	${NORMAL_C}

route.o: $S/net/route.c
	${NORMAL_C}

rtsock.o: $S/net/rtsock.c
	${NORMAL_C}

slcompress.o: $S/net/slcompress.c
	${NORMAL_C}

ccitt_proto.o: $S/netccitt/ccitt_proto.c
	${NORMAL_C}

llc_input.o: $S/netccitt/llc_input.c
	${NORMAL_C}

llc_output.o: $S/netccitt/llc_output.c
	${NORMAL_C}

llc_subr.o: $S/netccitt/llc_subr.c
	${NORMAL_C}

llc_timer.o: $S/netccitt/llc_timer.c
	${NORMAL_C}

pk_llcsubr.o: $S/netccitt/pk_llcsubr.c
	${NORMAL_C}

hd_debug.o: $S/netccitt/hd_debug.c
	${NORMAL_C}

hd_input.o: $S/netccitt/hd_input.c
	${NORMAL_C}

hd_output.o: $S/netccitt/hd_output.c
	${NORMAL_C}

hd_subr.o: $S/netccitt/hd_subr.c
	${NORMAL_C}

hd_timer.o: $S/netccitt/hd_timer.c
	${NORMAL_C}

if_x25subr.o: $S/netccitt/if_x25subr.c
	${NORMAL_C}

pk_acct.o: $S/netccitt/pk_acct.c
	${NORMAL_C}

pk_debug.o: $S/netccitt/pk_debug.c
	${NORMAL_C}

pk_input.o: $S/netccitt/pk_input.c
	${NORMAL_C}

pk_output.o: $S/netccitt/pk_output.c
	${NORMAL_C}

pk_subr.o: $S/netccitt/pk_subr.c
	${NORMAL_C}

pk_timer.o: $S/netccitt/pk_timer.c
	${NORMAL_C}

pk_usrreq.o: $S/netccitt/pk_usrreq.c
	${NORMAL_C}

if_ether.o: $S/netinet/if_ether.c
	${NORMAL_C}

igmp.o: $S/netinet/igmp.c
	${NORMAL_C}

in.o: $S/netinet/in.c
	${NORMAL_C}

in_pcb.o: $S/netinet/in_pcb.c
	${NORMAL_C}

in_proto.o: $S/netinet/in_proto.c
	${NORMAL_C}

ip_icmp.o: $S/netinet/ip_icmp.c
	${NORMAL_C}

ip_input.o: $S/netinet/ip_input.c
	${NORMAL_C}

ip_mroute.o: $S/netinet/ip_mroute.c
	${NORMAL_C}

ip_output.o: $S/netinet/ip_output.c
	${NORMAL_C}

raw_ip.o: $S/netinet/raw_ip.c
	${NORMAL_C}

tcp_debug.o: $S/netinet/tcp_debug.c
	${NORMAL_C}

tcp_input.o: $S/netinet/tcp_input.c
	${NORMAL_C}

tcp_output.o: $S/netinet/tcp_output.c
	${NORMAL_C}

tcp_subr.o: $S/netinet/tcp_subr.c
	${NORMAL_C}

tcp_timer.o: $S/netinet/tcp_timer.c
	${NORMAL_C}

tcp_usrreq.o: $S/netinet/tcp_usrreq.c
	${NORMAL_C}

udp_usrreq.o: $S/netinet/udp_usrreq.c
	${NORMAL_C}

nfs_bio.o: $S/nfs/nfs_bio.c
	${NORMAL_C}

nfs_node.o: $S/nfs/nfs_node.c
	${NORMAL_C}

nfs_nqlease.o: $S/nfs/nfs_nqlease.c
	${NORMAL_C}

nfs_serv.o: $S/nfs/nfs_serv.c
	${NORMAL_C}

nfs_socket.o: $S/nfs/nfs_socket.c
	${NORMAL_C}

nfs_srvcache.o: $S/nfs/nfs_srvcache.c
	${NORMAL_C}

nfs_subs.o: $S/nfs/nfs_subs.c
	${NORMAL_C}

nfs_syscalls.o: $S/nfs/nfs_syscalls.c
	${NORMAL_C}

nfs_vfsops.o: $S/nfs/nfs_vfsops.c
	${NORMAL_C}

nfs_vnops.o: $S/nfs/nfs_vnops.c
	${NORMAL_C}

ffs_alloc.o: $S/ufs/ffs/ffs_alloc.c
	${NORMAL_C}

ffs_balloc.o: $S/ufs/ffs/ffs_balloc.c
	${NORMAL_C}

ffs_inode.o: $S/ufs/ffs/ffs_inode.c
	${NORMAL_C}

ffs_subr.o: $S/ufs/ffs/ffs_subr.c
	${NORMAL_C}

ffs_tables.o: $S/ufs/ffs/ffs_tables.c
	${NORMAL_C}

ffs_vfsops.o: $S/ufs/ffs/ffs_vfsops.c
	${NORMAL_C}

ffs_vnops.o: $S/ufs/ffs/ffs_vnops.c
	${NORMAL_C}

lfs_alloc.o: $S/ufs/lfs/lfs_alloc.c
	${NORMAL_C}

lfs_bio.o: $S/ufs/lfs/lfs_bio.c
	${NORMAL_C}

lfs_balloc.o: $S/ufs/lfs/lfs_balloc.c
	${NORMAL_C}

lfs_cksum.o: $S/ufs/lfs/lfs_cksum.c
	${NORMAL_C}

lfs_debug.o: $S/ufs/lfs/lfs_debug.c
	${NORMAL_C}

lfs_inode.o: $S/ufs/lfs/lfs_inode.c
	${NORMAL_C}

lfs_segment.o: $S/ufs/lfs/lfs_segment.c
	${NORMAL_C}

lfs_subr.o: $S/ufs/lfs/lfs_subr.c
	${NORMAL_C}

lfs_syscalls.o: $S/ufs/lfs/lfs_syscalls.c
	${NORMAL_C}

lfs_vfsops.o: $S/ufs/lfs/lfs_vfsops.c
	${NORMAL_C}

lfs_vnops.o: $S/ufs/lfs/lfs_vnops.c
	${NORMAL_C}

mfs_vfsops.o: $S/ufs/mfs/mfs_vfsops.c
	${NORMAL_C}

mfs_vnops.o: $S/ufs/mfs/mfs_vnops.c
	${NORMAL_C}

ufs_bmap.o: $S/ufs/ufs/ufs_bmap.c
	${NORMAL_C}

ufs_disksubr.o: $S/ufs/ufs/ufs_disksubr.c
	${NORMAL_C}

ufs_ihash.o: $S/ufs/ufs/ufs_ihash.c
	${NORMAL_C}

ufs_inode.o: $S/ufs/ufs/ufs_inode.c
	${NORMAL_C}

ufs_lockf.o: $S/ufs/ufs/ufs_lockf.c
	${NORMAL_C}

ufs_lookup.o: $S/ufs/ufs/ufs_lookup.c
	${NORMAL_C}

ufs_quota.o: $S/ufs/ufs/ufs_quota.c
	${NORMAL_C}

ufs_vfsops.o: $S/ufs/ufs/ufs_vfsops.c
	${NORMAL_C}

ufs_vnops.o: $S/ufs/ufs/ufs_vnops.c
	${NORMAL_C}

device_pager.o: $S/vm/device_pager.c
	${NORMAL_C}

swap_pager.o: $S/vm/swap_pager.c
	${NORMAL_C}

vm_fault.o: $S/vm/vm_fault.c
	${NORMAL_C}

vm_glue.o: $S/vm/vm_glue.c
	${NORMAL_C}

vm_init.o: $S/vm/vm_init.c
	${NORMAL_C}

vm_kern.o: $S/vm/vm_kern.c
	${NORMAL_C}

vm_map.o: $S/vm/vm_map.c
	${NORMAL_C}

vm_meter.o: $S/vm/vm_meter.c
	${NORMAL_C}

vm_mmap.o: $S/vm/vm_mmap.c
	${NORMAL_C}

vm_object.o: $S/vm/vm_object.c
	${NORMAL_C}

vm_page.o: $S/vm/vm_page.c
	${NORMAL_C}

vm_pageout.o: $S/vm/vm_pageout.c
	${NORMAL_C}

vm_pager.o: $S/vm/vm_pager.c
	${NORMAL_C}

vm_swap.o: $S/vm/vm_swap.c
	${NORMAL_C}

vm_unix.o: $S/vm/vm_unix.c
	${NORMAL_C}

vm_user.o: $S/vm/vm_user.c
	${NORMAL_C}

vnode_pager.o: $S/vm/vnode_pager.c
	${NORMAL_C}

autoconf.o: $S/hp300/hp300/autoconf.c
	${NORMAL_C}

clock.o: $S/hp300/hp300/clock.c
	${NORMAL_C}

conf.o: $S/hp300/hp300/conf.c
	${NORMAL_C}

dkbad.o: $S/hp300/hp300/dkbad.c
	${NORMAL_C}

in_cksum.o: $S/hp300/hp300/in_cksum.c
	${NORMAL_C}

kgdb_glue.o: $S/hp300/hp300/kgdb_glue.c
	${NORMAL_C} -fno-defer-pop

kgdb_stub.o: $S/hp300/hp300/kgdb_stub.c
	${NORMAL_C}

machdep.o: $S/hp300/hp300/machdep.c
	${NORMAL_C_C}

mem.o: $S/hp300/hp300/mem.c
	${NORMAL_C}

oc_cksum.o: $S/hp300/hp300/oc_cksum.s
	${NORMAL_S}

pmap.o: $S/hp300/hp300/pmap.c
	${NORMAL_C}

pmap_bootstrap.o: $S/hp300/hp300/pmap_bootstrap.c
	${CC} -c ${CFLAGS} $<

sys_machdep.o: $S/hp300/hp300/sys_machdep.c
	${NORMAL_C}

trap.o: $S/hp300/hp300/trap.c
	${NORMAL_C}

vm_machdep.o: $S/hp300/hp300/vm_machdep.c
	${NORMAL_C}

hpux_float.o:
	-cp $S/hp300/hp300/hpux_float.o .

procfs_machdep.o: $S/hp300/hp300/procfs_machdep.c
	${NORMAL_C}

cons_conf.o: $S/hp300/dev/cons_conf.c
	${NORMAL_C}

grf_conf.o: $S/hp300/dev/grf_conf.c
	${NORMAL_C}

grf_machdep.o: $S/hp300/dev/grf_machdep.c
	${NORMAL_C}

grf_dv.o: $S/hp300/dev/grf_dv.c
	${NORMAL_C}

grf_gb.o: $S/hp300/dev/grf_gb.c
	${NORMAL_C}

grf_hy.o: $S/hp300/dev/grf_hy.c
	${NORMAL_C}

grf_rb.o: $S/hp300/dev/grf_rb.c
	${NORMAL_C}

grf_tc.o: $S/hp300/dev/grf_tc.c
	${NORMAL_C}

ite_dv.o: $S/hp300/dev/ite_dv.c
	${NORMAL_C}

ite_gb.o: $S/hp300/dev/ite_gb.c
	${NORMAL_C}

ite_hy.o: $S/hp300/dev/ite_hy.c
	${NORMAL_C}

ite_rb.o: $S/hp300/dev/ite_rb.c
	${NORMAL_C}

ite_tc.o: $S/hp300/dev/ite_tc.c
	${NORMAL_C}

dcm.o: $S/hp300/dev/dcm.c
	${DRIVER_C}

if_le.o: $S/hp300/dev/if_le.c
	${DRIVER_C}

dma.o: $S/hp300/dev/dma.c
	${DRIVER_C}

hpib.o: $S/hp300/dev/hpib.c
	${NORMAL_C}

fhpib.o: $S/hp300/dev/fhpib.c
	${DRIVER_C}

nhpib.o: $S/hp300/dev/nhpib.c
	${DRIVER_C}

ct.o: $S/hp300/dev/ct.c
	${NORMAL_C}

rd.o: $S/hp300/dev/rd.c
	${NORMAL_C}

rd_compat.o: $S/hp300/dev/rd_compat.c
	${NORMAL_C}

scsi.o: $S/hp300/dev/scsi.c
	${DRIVER_C}

sd.o: $S/hp300/dev/sd.c
	${NORMAL_C}

sd_compat.o: $S/hp300/dev/sd_compat.c
	${NORMAL_C}

st.o: $S/hp300/dev/st.c
	${NORMAL_C}

cons.o: $S/hp/dev/cons.c
	${NORMAL_C}

dca.o: $S/hp/dev/dca.c
	${DRIVER_C}

grf.o: $S/hp/dev/grf.c
	${NORMAL_C}

hil.o: $S/hp/dev/hil.c
	${DRIVER_C}

hil_keymaps.o: $S/hp/dev/hil_keymaps.c
	${NORMAL_C}

hil_subr.o: $S/hp/dev/hil_subr.c
	${NORMAL_C}

ite.o: $S/hp/dev/ite.c
	${NORMAL_C}

ite_subr.o: $S/hp/dev/ite_subr.c
	${NORMAL_C}

hpux_compat.o: $S/hp/hpux/hpux_compat.c
	${NORMAL_C}

hpux_net.o: $S/hp/hpux/hpux_net.c
	${NORMAL_C}

hpux_sig.o: $S/hp/hpux/hpux_sig.c
	${NORMAL_C}

hpux_syscalls.o: $S/hp/hpux/hpux_syscalls.c
	${NORMAL_C}

hpux_sysent.o: $S/hp/hpux/hpux_sysent.c
	${NORMAL_C}

hpux_tty.o: $S/hp/hpux/hpux_tty.c
	${NORMAL_C}

vn.o: $S/dev/vn.c
	${NORMAL_C}

