/*
 * example:	Glenn Fowler (config)		ulysses!gsf
 *
 * vmunix makefile
 */

#undef unix
#undef vax

IDENT		= TROILUS
RELEASE		= 4.2BSD
VERSION		= vm
MACHINE		= vax
NAME		= vmunix
SYS		= /sys
TIMEZONE	= 300
DST		= 1
MAXUSERS	= 24
VAX750		= 1
TROILUS		= 1
MTLERRM		= 1
MTRDREV		= 1
QUOTA		= 1
ARPIOCTL	= 1
FILE_SOCK	= 1
COMPAT		= 1
_USESTAT	= 1
CCA_PAGE	= 1
BTL_BLIT	= 1
HOMER		= 1
CACHE		= 1
INET		= 1

.SOURCE : $(SYS)/$(IDENT) $(SYS)/vaxuba $(SYS)/vaxmba $(SYS)/vaxif $(SYS)/vax $(SYS)/datakit $(SYS)/sys $(SYS)/netpup $(SYS)/netinet $(SYS)/netimp $(SYS)/netdecnet $(SYS)/net

.SOURCE.h : . ../h $(SYS)/$(IDENT) $(SYS)/h

C2		= /lib/c2
CCFLAGS		=

.OPTIONS : -u

$(NAME) :: locore.c param.c ioconf.c swap$(NAME).c \
	af.c if.c raw_cb.c raw_usrreq.c route.c if_ether.c \
	if_loop.c in.c in_pcb.c in_proto.c ip_icmp.c \
	ip_input.c ip_output.c raw_ip.c tcp_debug.c \
	tcp_input.c tcp_output.c tcp_subr.c tcp_timer.c \
	tcp_usrreq.c udp_usrreq.c init_main.c init_sysent.c \
	kern_acct.c kern_clock.c kern_descrip.c kern_exec.c \
	kern_exit.c kern_fork.c kern_mman.c kern_proc.c \
	kern_prot.c kern_resource.c kern_sig.c kern_subr.c \
	kern_synch.c kern_time.c kern_xxx.c quota_kern.c \
	quota_subr.c quota_sys.c quota_ufs.c subr_prf.c \
	subr_rmap.c subr_xxx.c sys_generic.c sys_inode.c \
	sys_process.c sys_socket.c tty.c tty_conf.c tty_pty.c \
	tty_subr.c tty_tty.c ufs_alloc.c ufs_bio.c ufs_bmap.c \
	ufs_dsort.c ufs_fio.c ufs_inode.c ufs_mount.c \
	ufs_nami.c ufs_subr.c ufs_syscalls.c ufs_tables.c \
	ufs_xxx.c uipc_domain.c uipc_mbuf.c uipc_pipe.c \
	uipc_proto.c uipc_socket.c uipc_socket2.c \
	uipc_syscalls.c uipc_usrreq.c vm_drum.c vm_mem.c \
	vm_mon.c vm_page.c vm_proc.c vm_pt.c vm_sched.c \
	vm_subr.c vm_sw.c vm_swap.c vm_swp.c vm_text.c tdk.c \
	Icache.c autoconf.c clock.c conf.c cons.c cpudata.c \
	dkbad.c flp.c in_cksum.c machdep.c mem.c \
	sys_machdep.c trap.c tu.c udiv.s ufs_machdep.c \
	urem.s vm_machdep.c if_ec.c if_uba.c dh.c dn.c \
	dz.c lp.c uba.c uda.c (VAX750) (TROILUS) (MTLERRM) \
	(MTRDREV) (QUOTA) (ARPIOCTL) (FILE_SOCK) (COMPAT) \
	(_USESTAT) (CCA_PAGE) (BTL_BLIT) (HOMER) (CACHE) (INET) 
	echo loading $(<)
	$(RM) $(RMFLAGS) $(<)
	if	test ! -r version.$(USER)
	then	echo 0 > version.$(USER)
	fi
	version=`<version.$(USER)`
	(( version = version + 1 ))
	echo "char version[] = \"$(IDENT:F=U) $(RELEASE) UNIX ($USER#$version) `date`\";" > vers.c
	$(CC) -c vers.c
	$(LD) -n -o $(<) -e start -x -T 80000000 $(*) vers.o
	echo $version > version.$(USER)
	echo rearranging symbols
	ignore symorder $(SYS)/$(MACHINE)/symbols.sort $(<)
	size $(<)
	chmod 755 $(<)

$(SYS)/$(MACHINE)/symbols.sort : symbols.raw
	grep -v '^#' $(>) | $(SED) 's/^	//' | sort -u > $(<)

locore.c : assym.s rpb.s scb.s locore.s ubglue.s
	cat $(*:N=*.s) > $(<)

locore.o : .IMPLICIT locore.c pcb.m
	$(CC) -E -DLOCORE $(CCFLAGS) $(>) > $(<:DBS=.i)
	$(AS) -o $(<) $(*:N=*.m) $(<:DBS=.i)
	$(RM) $(RMFLAGS) $(<:DBS=.i)

autoconf.o tu.o : (GENERIC)

af.o : (ARPIOCTL) (INET)

machdep.o : (MAXUSERS) (TIMEZONE) (DST)

assym.s : genassym
	$(>) > $(<)

genassym :: genassym.c (TIMEZONE) (DST) (MAXUSERS)

genassym.o swap$(NAME).o : .normal

param.o : .normal (TIMEZONE) (DST) (MAXUSERS)

tdk.o autoconf.o if_ec.o if_uba.o dh.o dn.o dz.o lp.o uba.o uda.o : .driver

$(NAME) : (USER)

(C2) : .NOEXPAND

.driver : .USE .IMPLICIT (CC) (CCFLAGS) (C2) (AS)
	$(CC) -c -S $(CCFLAGS) $(>)
	$(C2) -i $(<:BS=.s) | $(SED) -f $(SYS)/$(MACHINE)/asm.sed | $(AS) -o $(<)
	$(RM) $(RMFLAGS) $(<:BS=.s)

.normal : .USE .IMPLICIT (CC) (CCFLAGS)
	$(CC) -c $(CCFLAGS) -O $(>)

*.o : *.c (CC) (CCFLAGS) (C2) (AS)
	$(CC) -c -S $(CCFLAGS) $(>)
	$(C2) $(<:BS=.s) | $(SED) -f $(SYS)/$(MACHINE)/asm.sed | $(AS) -o $(<)
	$(RM) $(RMFLAGS) $(<:BS=.s)
