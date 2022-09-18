/*  
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	init_main.c,v $
 * Revision 2.24  89/08/02  08:02:52  jsb
 * 	Added a call to kern_prot_init (to initialize identity zone).
 * 	[89/07/31  17:08:00  jsb]
 * 
 * Revision 2.23  89/05/31  12:26:25  rvb
 * 	Stylistic change. [af]
 * 
 * Revision 2.22  89/05/30  10:31:16  rvb
 * 	No floats in Mips kernels.
 * 	[89/05/15            af]
 * 
 * Revision 2.21  89/04/22  15:19:19  gm0w
 * 	Changed to use INITIALIZE_VFS, INITIALIZE_QUOTA, NAME_CACHE_INIT
 * 	and SETUP_ROOTFS macros.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.20  89/04/18  16:41:59  mwyoung
 * 	Remove handling of default memory manager.
 * 	[89/04/01            mwyoung]
 * 
 * Revision 2.11.2.1  89/04/04  14:01:02  mwyoung
 * 	Remove handling of default memory manager.
 * 	[89/04/01            mwyoung]
 * 
 * Revision 2.19  89/03/09  19:27:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.18  89/02/25  14:17:49  gm0w
 * 	Removed include of seg.h as it no longer exists.
 * 	[89/02/18            mrt]
 * 
 * Revision 2.17  89/02/09  04:30:19  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.16  89/01/30  22:02:28  rpd
 * 	Added definitions of rootdev, dumpdev, dumplo, show_space.
 * 	(The declarations in <sys/systm.h> are "extern" now.)
 * 	[89/01/25  14:49:47  rpd]
 * 
 * Revision 2.15  89/01/23  22:01:38  af
 * 	Changes for I386: exl change to buffer initialization
 * 	[89/01/09            rvb]
 * 
 * Revision 2.14  89/01/18  00:33:33  jsb
 * 	Vnode support: call inode_pager_bootstrap from here (for unknown
 * 	reasons); mount root file system differently; start netisr thread
 * 	earlier; move around other initializations.
 * 	NFS support: added temporary mechanism for mounting NFS file system
 * 	as the root file system.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.13  89/01/15  16:16:28  rpd
 * 	Use simple_lock_addr when calling thread_sleep.
 * 	[89/01/15  14:45:20  rpd]
 * 
 * Revision 2.12  89/01/10  23:24:45  rpd
 * 	Use object_copyout instead of port_copyout.
 * 	[89/01/09  14:41:54  rpd]
 * 
 * Revision 2.11  88/12/19  02:32:55  mwyoung
 * 	Add task_name(), so that Mach tasks can set the task name
 * 	without compromising their cleanliness.
 * 	[88/12/12            mwyoung]
 * 	
 * 	Split up XPR initialization into two parts.
 * 	[88/11/22            mwyoung]
 * 
 * Revision 2.10  88/11/21  16:54:21  rvb
 * 	Alas the change below is really in the wrong place and must be
 * 	in cpu_up and cpu_down.  The problem is that we have not turned
 * 	on any other the other processors yet so avail_cpus is 1.
 * 	[88/11/09            rvb]
 * 
 * Revision 2.9  88/10/18  00:26:57  mwyoung
 * 	Only set printf_cpu_number if NCPU > 1 and machine_info.avail_cpus > 1
 * 	[88/10/13            rvb]
 * 
 * Revision 2.8  88/08/25  18:08:35  mwyoung
 * 	Fix up MACH_DEVICE support.
 * 	[88/08/16  00:20:04  mwyoung]
 * 
 * Revision 2.7  88/08/09  17:49:44  rvb
 * Have init_task turn on printf_cpu_number.
 * 
 * Revision 2.6  88/08/06  17:58:30  rpd
 * Eliminated use of kern/mach_ipc_defs.h.
 * 
 * Revision 2.5  88/07/17  17:39:45  mwyoung
 * Use new memory object types.  Convert to CMUCS conditional.
 * 
 * Split up use of kernel_only field.
 * Make MACH_EXCEPTION the default.
 * 
 * Restore device_pager_init call.
 * 
 * Revision 2.3.1.2  88/07/04  15:14:28  mwyoung
 * Use new memory object types.  Convert to CMUCS conditional.
 * 
 * Revision 2.3.1.1  88/06/28  20:11:29  mwyoung
 * Split up use of kernel_only field.
 * Make MACH_EXCEPTION the default.
 * 
 * Restore device_pager_init call.
 * 
 * 21-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Split up use of kernel_only field.
 *	Make MACH_EXCEPTION the default.
 *
 * 10-May-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Restore device_pager_init call.
 *
 * Revision 2.4  88/07/15  15:23:25  mja
 * Changed to include <sys/table.h> instead of <sys/syscalls.h> for
 * setmodes bit definitons;  simplified conditionals.
 * 
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH: MACH_TIME_NEW is now standard.
 *
 * 21-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	Set kernel_only for kernel task.
 *
 *  3-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Force the vm_map for the inode_ and device_ pager tasks to
 *	be the kernel map.
 *
 * 18-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Establish UMODE_NONICE as default (patched off for time-shared
 *	systems); make maximum process count a patchable variable.
 *	[ V5.1(XF23) ]
 *
 * 25-Jan-88  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Moved float_init() call to configure() in autoconf.c
 *
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Neither task_create nor thread_create return the data port
 *	any longer.
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed code to shuffle initial processes for idle threads;
 *	MACH doesn't need to make extra processes for them.
 *	Delinted.
 *
 * 12-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added device_pager startup.  Moved setting of ipc_kernel and
 *	kernel_only flags here.
 *
 *  9-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Follow thread_terminate with thread_halt_self for new thread
 *	termination logic; extra reference no longer necessary.
 *
 *  9-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Grab extra reference to first thread before terminating it.
 *
 *  4-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Name changes for exc interface.  set ipc_kernel in first thread
 *	for paranoia purposes.
 *
 * 19-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Eliminated MACH conditionals, purged history.
 *
 *  5-Nov-87  David Golub (dbg) at Carnegie-Mellon University
 *	start up network service thread.
 *
 *  9-Sep-87  Peter King (king) at NeXT
 *	MACH_VFS:  Add a call to vfs_init() in setup_main().
 *
 * 17-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS:  Support credentials record in u.
 *	      Convert to Sun quota system.
 *	      Add call to dnlc_init().  Remove nchinit() call.
 *	      Call swapconf() in binit().
 *
 * 27-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to initialize new u_maxuprc field to MAXUPRC in process
 *	0 at system startup time.
 *	[ V5.1(F1) ]
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE: added initialisation of remote wd for ITC RFS.
 *
 * 11-Feb-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Add UMODE variable to establish the default
 *	process modes for the system at boot time (and especially to
 *	allow this to be patched in).
 *
 * 02-Jan-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Split initialization into two parts since queue
 *	headers must now be valid before the possible multi-processor
 *	newproc() set up but the root file system isn't available until
 *	after.
 *	[V1(1)]
 *
 * 03-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RPAUSE:  Changed to initially enable all resource pause
 *	flags.
 *	[V1(1)]
 *
 * 08-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.
 *	[V1(1)].
 *
 * 20-Jan-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Added call to rfs_init() to initialize the remote file
 *	access mechanism (V3.04b).
 *
 */
 
#include <mach_rfs.h>
#include <mach_device.h>
#include <mach_net.h>
#include <mach_xp.h>
#include <quota.h>
#include <vice.h>
#include <xpr_debug.h>
#include <cpus.h>
#include <mach_emulation.h>
#include <mach_nfs.h>

#include <cputypes.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)init_main.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/fs.h>
#include <sys/mount.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/inode.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/vm.h>
#include <sys/clist.h>
#include <sys/protosw.h>
#include <sys/quota.h>
#include <sys/dk.h>
#include <sys/table.h>
#include <machine/reg.h>
#include <machine/cpu.h>

#include <kern/thread.h>
#include <kern/task.h>
#include <mach/machine.h>
#include <kern/timer.h>
#include <sys/version.h>
#include <machine/pmap.h>
#include <mach/vm_param.h>
#include <vm/vm_page.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_object.h>
#include <mach/boolean.h>
#include <kern/sched_prim.h>
#include <kern/thread_swap.h>
#include <kern/zalloc.h>
#include <kern/kern_obj.h>
#include <kern/kern_port.h>
#include <kern/ipc_copyout.h>
#if	MACH_XP
#include <builtin/inode_pager.h>
#include <builtin/device_pager.h>
#include <mach/memory_object.h>
#endif	MACH_XP
#include <mach/task_special_ports.h>
#include <builtin/ux_exception.h>

extern void	ux_handler();
extern void	service_timers();

long	cp_time[CPUSTATES];
int	dk_ndrive;
int	dk_busy;
long	dk_time[DK_NDRIVE];
long	dk_seek[DK_NDRIVE];
long	dk_xfer[DK_NDRIVE];
long	dk_wds[DK_NDRIVE];
#ifdef	mips
long	dk_mspw[DK_NDRIVE];
#else	mips
float	dk_mspw[DK_NDRIVE];
#endif	mips

long	tk_nin;
long	tk_nout;

dev_t	rootdev;		/* device of the root */
dev_t	dumpdev;		/* device to take dumps on */
long	dumplo;			/* offset into dumpdev */
int	show_space;
long	hostid;
char	hostname[MAXHOSTNAMELEN];
int	hostnamelen;
char	domainname[MAXDOMNAMELEN];
int	domainnamelen;

struct	timeval boottime;
struct	timeval time;
struct	timezone tz;			/* XXX */
int	hz;
int	phz;				/* alternate clock's frequency */
int	tick;
int	lbolt;				/* awoken once a second */

vm_map_t	kernel_pageable_map;
vm_map_t	mb_map;

int	cmask = CMASK;

/*
 *	Defaults for all processes
 */
#ifdef	CMUCS
int umodes  = UMODE_NONICE;
#else	CMUCS
int umodes  = UMODE_NONICE | UMODE_P_GID;
#endif	CMUCS
int maxuprc = MAXUPRC;		/* default maximum proccesses per user */

/*
 * Initialization code.
 * Called from cold start routine as
 * soon as a stack and segmentation
 * have been established.
 * Functions:
 *	clear and free user core
 *	turn on clock
 *	hand craft 0th process
 *	call all initialization routines
 *	fork - process 0 to schedule
 *	     - process 1 execute bootstrap
 *	     - process 2 to page out
 */
task_t		first_task;
thread_t	first_thread;

thread_t setup_main()
/*
 *	first_addr contains the first available physical address
 *	running in virtual memory on the interrupt stack
 *
 *	returns initial thread to run
 */
{
	extern vm_offset_t	virtual_avail;
	vm_offset_t		end_stack, cur_stack;
	int			i;
	extern void	initial_context();
	extern void	vm_mem_init();
#if	MACH_NET
	extern void	mach_net_init();
#endif	MACH_NET

	rqinit();
	sched_init();
#include <loop.h>

	vm_mem_init();

	init_timers();

#if	XPR_DEBUG
	xprbootstrap();
#endif	XPR_DEBUG

	startup(virtual_avail);

	machine_info.max_cpus = NCPUS;
	machine_info.memory_size = mem_size;
	machine_info.avail_cpus = 0;
	machine_info.major_version = KERNEL_MAJOR_VERSION;
	machine_info.minor_version = KERNEL_MINOR_VERSION;

	/*
	 *	Create stacks for other processors (the first
	 *	processor up uses a preallocated stack).
	 */

	cur_stack = kmem_alloc(kernel_map, NCPUS*INTSTACK_SIZE);
	end_stack = cur_stack + round_page(NCPUS*INTSTACK_SIZE);
	for (i = 0; i < NCPUS; i++) {
		if (machine_slot[i].is_cpu) {
			if (i != master_cpu) {
				interrupt_stack[i] = cur_stack;
				cur_stack += INTSTACK_SIZE;
			}
			else {
				/*
				 * Master cpu uses system intstack,
				 */
#ifndef	ibmrt
				interrupt_stack[i] = (vm_offset_t) &intstack[0];
#endif	ibmrt
			}
		}
		else {
			interrupt_stack[i] = (vm_offset_t) 0;
		}
	}

	cpu_up(master_cpu);	/* signify we are up */

	/*
	 *	Free up any stacks we really didn't need.
	 */

	cur_stack = round_page(cur_stack);
	if (end_stack != cur_stack)
		kmem_free(kernel_map, cur_stack, end_stack - cur_stack);

	/*
	 *	Initialize the task and thread subsystems.
	 */

	/*
	 * This is a convenient place to do this.  This
	 * keeps us from including user.h in thread.c
	 */
	{
#include <kern/mach_param.h>
		extern struct zone *u_zone;
		u_zone = zinit(sizeof(struct utask),
			THREAD_MAX * sizeof(struct utask),
			10 * sizeof(struct utask),
			FALSE, "u-areas");
	}
	ipc_bootstrap();
#if	MACH_NET
	mach_net_init();
#endif	MACH_NET
	task_init();
	thread_init();
	swapper_init();
	ipc_init();
	kern_prot_init();
	INITIALIZE_VFS;
	inode_pager_bootstrap();

	/*
	 *	Create proc[0]'s u area.
	 */

	(void) task_create(TASK_NULL, FALSE, &first_task);
	first_task->proc_index = 0;
	first_task->ipc_privilege = TRUE;
	first_task->kernel_ipc_space = TRUE;
	first_task->kernel_vm_space = TRUE;

	(void) thread_create(first_task, &first_thread);
	initial_context(first_thread);
	proc[0].task = first_task;
	proc[0].thread = first_thread;
	first_thread->state = TH_RUN;
	first_thread->user_suspend_count = 0;
	first_thread->user_stop_count = 0;
	first_thread->suspend_count = 0;
	first_thread->ipc_kernel = TRUE;
	(void) thread_resume(first_thread);

	/*
	 *	Tell the pmap system that our cpu is using the kernel pmap
	 */
	PMAP_ACTIVATE(kernel_pmap, first_thread, cpu_number());

	/*
	 *	Return to assembly code to start the first process.
	 */

	return(first_thread);
}

/*
 *	Sets the name for the given task.
 */
void task_name(s)
	char		*s;
{
	int		length = strlen(s);

	bcopy(s, u.u_comm,
		length >= sizeof(u.u_comm) ? sizeof(u.u_comm) :
			length + 1);
}

/* To allow these values to be patched, they're globals here */
struct rlimit vm_initial_limit_stack = { DFLSSIZ, MAXSSIZ };
struct rlimit vm_initial_limit_data = { DFLDSIZ, MAXDSIZ };
struct rlimit vm_initial_limit_core = { RLIM_INFINITY, RLIM_INFINITY };

main()
{
	register int i;
	register struct proc *p;
	struct fs *fs;
	int s;
	port_t		dummy_port;
	thread_t	th;
	extern void	idle_thread(), init_task(), vm_pageout();
	extern void	reaper_thread(), swapin_thread(), swapout_thread();
	extern void	netisr_thread();
	extern thread_t	newproc();
	thread_t	exc_th;

	/*
	 * set up system process 0 (swapper)
	 */
	p = &proc[0];
	/*
	 *	Now in thread context, switch to thread timer.
	 */
	s = splhigh();
	timer_switch(&current_thread()->system_timer);
	splx(s);
	p->p_stat = SRUN;
	p->p_flag |= SLOAD|SSYS;
	p->p_nice = NZERO;
	simple_lock_init(&p->siglock);
	p->sigwait = FALSE;
	p->exit_thread = THREAD_NULL;
	u.u_procp = p;
#if	defined(vax) || defined(ns32000)
	/*
	 * These assume that the u. area is always mapped 
	 * to the same virtual address. Otherwise must be
	 * handled when copying the u. area in newproc().
	 */
	u.u_nd.ni_iov = &u.u_nd.ni_iovec;
	u.u_ap = u.u_arg;
#endif
	u.u_nd.ni_iovcnt = 1;
	u.u_cmask = cmask;
	u.u_lastfile = -1;
	for (i = 0; i < sizeof(u.u_rlimit)/sizeof(u.u_rlimit[0]); i++)
		u.u_rlimit[i].rlim_cur = u.u_rlimit[i].rlim_max = 
		    RLIM_INFINITY;
	u.u_modes   = umodes;
	u.u_maxuprc = maxuprc;

	u.u_rlimit[RLIMIT_STACK] = vm_initial_limit_stack;
	u.u_rlimit[RLIMIT_DATA] = vm_initial_limit_data;
	u.u_rlimit[RLIMIT_CORE] = vm_initial_limit_core;

 	/*
	 *	Allocate a kernel submap for pageable memory
	 *	for temporary copying (table(), execve()).
	 */
	{
	    vm_offset_t	min, max;

	    kernel_pageable_map = kmem_suballoc(kernel_map,
						&min, &max,
						2*NCARGS,
						TRUE);
	}
	mfs_init();
	kallocinit();
	root_identity = alloc_identity();
	root_identity->id_ref++;
	u.u_identity = root_identity;
	for (i = 1; i < NGROUPS; i++)
		u.u_groups[i] = NOGROUP;
#if	QUOTA
	qtinit();
	INITIALIZE_QUOTA(p);
#endif	QUOTA
	timestamp_init();
	startrtclock();

	/*
	 *	Kick off the hourly service routine.
	 */
	timeout(service_timers, (caddr_t) 0, 3600*hz);

#ifdef	vax
#include <kg.h>
#if	NKG > 0
	startkgclock();
#endif	NKG > 0
#endif	vax

	/*
	 * Initialize tables, protocols, and set up well-known inodes.
	 */
#ifdef	multimax
	/* this is done in startup because ethernet driver initialization
		allocates mbufs. */
#else	multimax
	mbinit();
#endif	multimax
#if	MACH_RFS
	/*
	 *  RFS initialization part 1.
 	 *
	 *  Initialize all data structures which could not be handled at
	 *  compile-time.  This includes, in particular, the parallel process
	 *  table queue headers which must be valid before the newproc() call
	 *  below.
	 */
	rfs_init();
#endif	MACH_RFS
	cinit();
#include <sl.h>
#if	NSL > 0
	slattach();			/* XXX */
#endif
#if	NLOOP > 0
	loattach();			/* XXX */
#endif
	/*
	 * Block reception of incoming packets
	 * until protocols have been initialized.
	 */
	s = splimp();
	ifinit();
	domaininit();
	splx(s);
	pqinit();
	ihinit();
	bhinit();
	NAME_CACHE_INIT();
	/*
	 *	Create kernel idle cpu processes.  This must be done
 	 *	before a context switch can occur (and hence I/O can
	 *	happen in the binit() call).
	 */
	u.u_rdir = NULL;
	u.u_cdir = NULL;

	for (i = 0; i < NCPUS; i++) {
		if (machine_slot[i].is_cpu == FALSE)
			continue;
		(void) thread_create(first_task, &th);
		thread_bind(th, i);
		thread_start(th, idle_thread, THREAD_SYSTEMMODE);
		(void) thread_resume(th);
	}
	binit();
#ifdef	GPROF
	kmstartup();
#endif	GPROF

#if	defined(sun3) || defined(sun4)
	consconfig();	/* configure Sun console */
#endif	defined(sun3) || defined(sun4)

/* kick off timeout driven events by calling first time */
	recompute_priorities();
 	schedcpu();
	compute_mach_factor();

/* set up the root file system */
	(void) kernel_thread(first_task, netisr_thread);
	SETUP_ROOTFS();
#if	MACH_RFS
	/*
	 *  RFS initialization part 2.
	 *
	 *  Switch over to the local root.
	 */
	rfs_initroot();
#endif	MACH_RFS
#if	VICE
	u.u_rmtWd.dev = NODEV;
#endif	VICE
	/*
	 *  Default to pausing process on these errors.
	 */
	u.u_rpause = (URPS_AGAIN|URPS_NOMEM|URPS_NFILE|URPS_NOSPC);

#if	MACH_EMULATION
	eml_init();
#endif	MACH_EMULATION

	/*
	 * make init process
	 */

#if	XPR_DEBUG
	xprinit();
#endif	XPR_DEBUG

	th = newproc(0);
	/*
	 *	After calling start_init,
	 *	machine-dependent code must
	 *	set up stack as though a system
	 *	call trap occurred, then call
	 *	load_init_program.
	 */

#if	MACH_XP
	/*inode_pager*/ {
	thread_t	inode_th;
	vm_offset_t	min, max;

	inode_th = newproc(0);
	inode_th->task->map =
		kmem_suballoc(kernel_map, &min, &max,
				8 * PAGE_SIZE, FALSE);

	inode_th->ipc_kernel = TRUE;
	inode_th->task->ipc_privilege = TRUE;
	inode_th->task->kernel_vm_space = TRUE;
	inode_th->vm_privilege = TRUE;
	thread_swappable(inode_th, FALSE);
	thread_start(inode_th, inode_pager, THREAD_SYSTEMMODE);
	(void) thread_resume(inode_th);

	/*inode_pager*/ }

	/*device_pager*/ {
	thread_t	device_th;
	vm_offset_t	min, max;

	device_th = newproc(0);
	device_th->task->map =
		kmem_suballoc(kernel_map, &min, &max,
				8 * PAGE_SIZE, FALSE);

	device_th->ipc_kernel = TRUE;
	device_th->task->kernel_vm_space = TRUE;
	device_pager_init(device_th->task);
	thread_swappable(device_th, FALSE);
	thread_start(device_th, device_pager, THREAD_SYSTEMMODE);
	(void) thread_resume(device_th);
	/*device_pager*/ }
#endif	MACH_XP

#if	MACH_DEVICE
	{ /*device_server*/
	thread_t	device_io_th;
	extern void	device_loop();

	device_io_th = newproc(0);
	device_io_th->ipc_kernel = TRUE;
	device_io_th->task->kernel_vm_space = TRUE;
	device_io_th->task->ipc_privilege = TRUE;
	device_init(device_io_th->task);
	thread_swappable(device_io_th, FALSE);
	thread_start(device_io_th, device_loop, THREAD_SYSTEMMODE);
	(void) thread_resume(device_io_th);	
	/*device_server*/ }
#endif	MACH_DEVICE

	/*
	 *	Default exception server
	 */

	simple_lock_init(&ux_handler_init_lock);
	ux_exception_port = PORT_NULL;
	exc_th = newproc(0);
	thread_start(exc_th, ux_handler, THREAD_SYSTEMMODE);
	(void) thread_resume(exc_th);
	simple_lock(&ux_handler_init_lock);
	if (ux_exception_port == PORT_NULL) 
		thread_sleep((int) &ux_exception_port,
			simple_lock_addr(ux_handler_init_lock), FALSE);
	else
		simple_unlock(&ux_handler_init_lock);
	(void) task_set_exception_port(th->task, ux_exception_port);
	port_reference((kern_port_t) ux_exception_port);
	object_copyout(th->task, (kern_obj_t) ux_exception_port,
		       MSG_TYPE_PORT, &dummy_port);

	/*
	 *	Initial task
	 */

	thread_start(th, init_task, THREAD_SYSTEMMODE);
	(void) thread_resume(th);

	/*
	 *	Kernel daemon threads that don't need their own tasks
	 */

	(void) kernel_thread(first_task, vm_pageout);
	(void) kernel_thread(first_task, reaper_thread);
	(void) kernel_thread(first_task, swapin_thread);
	(void) kernel_thread(first_task, swapout_thread);

	u.u_procp->p_flag |= SLOAD|SSYS;
	task_name("kernel idle");
	(void) thread_terminate(current_thread());
	thread_halt_self();
	/*NOTREACHED*/
}

void init_task()
{
	task_name("init");
	start_init();
}

/*
 * Initialize hash links for buffers.
 */
bhinit()
{
	register int i;
	register struct bufhd *bp;

	for (bp = bufhash, i = 0; i < BUFHSZ; i++, bp++)
		bp->b_forw = bp->b_back = (struct buf *)bp;
}

/*
 * Initialize the buffer I/O system by freeing
 * all buffers and setting all device buffer lists to empty.
 */
binit()
{
	register struct buf *bp, *dp;
	register int i;
	int base, residual;

	for (dp = bfreelist; dp < &bfreelist[BQUEUES]; dp++) {
		dp->b_forw = dp->b_back = dp->av_forw = dp->av_back = dp;
		dp->b_flags = B_HEAD;
	}
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
	for (i = 0; i < nbuf; i++) {
		bp = &buf[i];
		bp->b_dev = NODEV;
		bp->b_bcount = 0;
#if	EXL
/* The actual allocation is one page per buffer.	--- csy	*/
		bp->b_un.b_addr = buffers + i * PAGE_SIZE;
#else	EXL
	        bp->b_un.b_addr = buffers + i * MAXBSIZE;
#endif	EXL
 		if (i < residual)
			bp->b_bufsize = (base + 1) * page_size;
		else
			bp->b_bufsize = base * page_size;
		binshash(bp, &bfreelist[BQ_AGE]);
		bp->b_flags = B_BUSY|B_INVAL;
		brelse(bp);
	}
}

/*
 * Initialize clist by freeing all character blocks, then count
 * number of character devices. (Once-only routine)
 */
cinit()
{
	register int ccp;
	register struct cblock *cp;

	ccp = (int)cfree;
	ccp = (ccp+CROUND) & ~CROUND;
	for(cp=(struct cblock *)ccp; cp < &cfree[nclist-1]; cp++) {
		cp->c_next = cfreelist;
		cfreelist = cp;
		cfreecount += CBSIZE;
	}
}
